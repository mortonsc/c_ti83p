;; This file implements functions for creating and modifying programs.
;;
;; Copyright (C) 2016 Scott Morton (mortonsc@umich.edu)
;;
;; This library is free software: you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.
;;
;; This library is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this library.  If not, see <http://www.gnu.org/licenses/>.
;;
;; As a special exception, if you link this library in unmodified form with
;; other files to produce an executable, this library does not by itself cause
;; the resulting executable to be covered by the GNU General Public License.
;; This exception does not however invalidate any other reasons why
;; the executable file might be covered by the GNU General Public License.

        .module prgm

        .area _DATA

.nlist
.include "ti83plus.inc"
.list

        .area _CODE

;; void *CRecallPrgm(const uint8_t *name, uint16_t *size);
_CRecallPrgm::
        pop bc ;; return address 
        pop hl ;; *name
        pop de ;; *size
        push de
        push hl
        push bc
        ld a,#ProgObj
        jmp RecallVar


;; expects: *name in hl, var type token in a, pointer for size in de
RecallVar:
        push de
        dec hl
        rst rMOV9TOOP1
        ld (OP1),a
        bcall _ChkFindSym
        jr c,RecallFailed
        ld a,b
        or a ; check if archived
        jr z,VarInRam
        AppOnErr UnarchiveFailed
        rst rPUSHREALO1     ; not sure if _Arc_Unarc destroys OP1
        bcall _Arc_Unarc
        bcall _PopRealO1
        AppOffErr
        bcall _ChkFindSym   ; find the new address
                            ; _Arc_Unarc maybe does this for us?
VarInRam:
        pop hl      ; get *size
        ex de,hl    ; move address to hl (return value)
        ldi         ; store size in second argument
        ldi
        ret
UnarchiveFailed:
        bcall _PopRealO1
RecallFailed:
        pop hl
        ld hl,#0; return null for var address
        ret

;; void *CCreatePrgm(const uint8_t *name, uint16_t size);
_CCreatePrgm
        ld hl,#_CreateProg
        ld (CreateVar),hl
        pop de ;; return address 
        pop hl ;; *name
        pop bc ;; size
        push bc
        push hl
        push de
        ld a,#ProgObj
        jmp CreateVar

;; void *CCreateProtPrgm(const uint8_t *name, uint16_t size);
_CCreateProtPrgm
        ld hl,#_CreateProtProg
        ld (CreateVar),hl
        pop de ;; return address 
        pop hl ;; *name
        pop bc ;; size
        push bc
        push hl
        push de
        ld a,#ProtProgObj
        jmp CreateVar

;; expects: *name in hl, var type token in a, size in bc,
;;          bcall for creating in CreateVar
CreateVar:
        push bc
        dec hl
        rst rMOV9TOOP1
        ld (OP1),a
        bcall _ChkFindSym
        jr c,MakeNewVar
        bcall _DelVarArc    ; delete the AppVar if it exists
MakeNewVar:
        pop bc
        AppOnErr InsufficientMem
        rst rBR_CALL        ; call bcall stored in next two bytes
CreateVar:
        .dw #_JError        ; should be overwritten
        AppOffErr
        ex de,hl ; now hl contains address
        ld (hl),c ; store the size in the first two bytes of the new object
        inc hl
        ld (hl),b
        inc hl ; return the address of the data
        ret
InsufficientMem:
        ld hl,#0 ; failed to create var, so return null
        ret

;; void CArchivePrgm(const uint8_t *name);
_CArchivePrgm::
        push ix
        ld ix,#0
        add ix,sp
        ld l,4(ix)
        ld h,5(ix)
        call FindPrgmH
        jr c,ArchivePrgmRet ; doesn't exist
        ld a,b
        or a   ; check if the var is already archived
        jr nz,ArchivePrgmRet
        AppOnErr ArchivePrgmRet
        bcall _Arc_Unarc
        AppOffErr
ArchivePrgmRet:
        pop ix
        ret

;; void CDeletePrgm(const uint8_t *name);
_CDeletePrgm::
        pop bc ;; return address 
        pop hl ;; *name
        push hl
        push bc
        ld a,#ProgObj
        jmp RecallVar

;;  expects: *name in hl, var type token in a
DeleteVar::
        dec hl
        rst rMOV9TOOP1
        ld (OP1),a
        bcall _ChkFindSym
        jr c,DeletePrgmRet ; var doesn't exist (maybe not necessary?)
        bcall _DelVarArc
DeletePrgmRet:
        ret
