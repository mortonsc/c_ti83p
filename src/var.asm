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

        .module var

        .area _DATA

.nlist
.include "ti83plus.inc"
.list

        .area _CODE

;; Functions for working with programs

;; void *CRecallPrgm(const uint8_t *name, uint16_t *size);
_CRecallPrgm::
        pop bc  ; return address 
        pop hl  ; *name
        pop de  ; *size
        push de
        push hl
        push bc
        ld a,#ProgObj
        jp RecallVar


;; void CArchivePrgm(const uint8_t *name);
_CArchivePrgm::
        pop bc ;; return address 
        pop hl ;; *name
        push hl
        push bc
        ld a,#ProgObj
        jp ArchiveVar

;; void *CCreatePrgm(const uint8_t *name, uint16_t size);
_CCreatePrgm::
        ld hl,#_CreateProg
        ld (CreateVarBcall),hl
        pop de  ; return address 
        pop hl  ; *name
        pop bc  ; size
        push bc
        push hl
        push de
        ld a,#ProgObj
        jp CreateVar

;; void *CCreateProtPrgm(const uint8_t *name, uint16_t size);
_CCreateProtPrgm::
        ld hl,#_CreateProtProg
        ld (CreateVarBcall),hl
        pop de  ; return address 
        pop hl  ; *name
        pop bc  ; size
        push bc
        push hl
        push de
        ld a,#ProtProgObj
        jp CreateVar

;; void CDeletePrgm(const uint8_t *name);
_CDeletePrgm::
        pop bc ;; return address 
        pop hl ;; *name
        push hl
        push bc
        ld a,#ProgObj
        jp DeleteVar

;; Functions for working with AppVars

;; void *CRecallAppVar(const uint8_t *name, uint16_t *size)
_CRecallAppVar::
        pop bc  ; return address
        pop hl  ; *name
        pop de  ; *size
        push de
        push hl
        push bc
        ld a,#AppVarObj
        jp RecallVar

;; void CCreateAppVar(const uint8_t *name, uint16_t size)
_CCreateAppVar::
        ld hl,#_CreateAppVar
        ld (CreateVarBcall),hl
        pop de  ; return address
        pop hl  ; *name
        pop bc  ; size
        push bc
        push hl
        push de
        ld a,#AppVarObj
        jp CreateVar

;; void CArchiveAppVar(const uint8_t *name);
_CArchiveAppVar::
        pop bc ;; return address 
        pop hl ;; *name
        push hl
        push bc
        ld a,#AppVarObj
        jp ArchiveVar

;; void CDeleteAppVar(const uint8_t *name);
_CDeleteAppVar::
        pop bc ;; return address 
        pop hl ;; *name
        push hl
        push bc
        ld a,#AppVarObj
        jp DeleteVar

;; Functions for working with PicVars
PicName:
    .db tVarPict,0,0    ; pic number goes in 3rd byte
PicSize:
    .db 0,0             ; recall code needs somewhere to store size

;; unsigned char *CRecallPic(unsigned char picNo);
_CRecallPic::
    pop hl  ; return address
    pop af  ; picNo
    push af
    push hl
    dec a
    ld (#PicName+1),a
    ld hl,#PicName
    ld de,#PicSize
    ld a,#PictObj
    jp RecallVar

;; unsigned char *CCreatePic(unsigned char picNo);
_CCreatePic::
    pop hl  ; return address
    pop af  ; picNo
    push af
    push hl
    dec a
    ld (#PicName+1),a
    ld hl,#_CreatePict
    ld (CreateVarBcall),hl
    ld hl,#PicName
    ld bc,#756  ; pics are always the same size
    ld a,#PictObj
    jp CreateVar

;; void CArchivePic(unsigned char picNo);
_CArchivePic::
    pop hl  ; return address
    pop af  ; picNo
    push af
    push hl
    dec a
    ld (#PicName+1),a
    ld hl,#PicName
    ld a,#PictObj
    jp ArchiveVar

;; void CDeletePic(unsigned char picNo)
_CDeletePic::
    pop hl  ; return address
    pop af  ; picNo
    push af
    push hl
    dec a
    ld (#PicName+1),a
    ld hl,#PicName
    ld a,#PictObj
    jp DeleteVar

;; Function bodies (generic in the type of variable)

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
        push ix         ; _Arc_Unarc destroys ix
        AppOnErr RecallUnarchiveFailed
        bcall _Arc_Unarc
        AppOffErr
        pop ix
VarInRam:
        pop hl      ; get *size
        ex de,hl    ; move address to hl (return value)
        ldi         ; store size in second argument
        ldi
        ret
RecallUnarchiveFailed:
        pop ix
RecallFailed:
        pop de
        ld hl,#0; return null for var address
        ret

;; expects: *name in hl, var type token in a, size in bc,
;;          bcall for creating in CreateVarBcall
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
CreateVarBcall:
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

;; expects: *name in hl, var type token in a
ArchiveVar:
        dec hl
        rst rMOV9TOOP1
        ld (OP1),a
        bcall _ChkFindSym
        jr c,ArchiveVarRet ; doesn't exist
        ld a,b
        or a   ; check if the var is already archived
        jr nz,ArchiveVarRet
        AppOnErr ArchiveVarRet
        bcall _Arc_Unarc
        AppOffErr
ArchiveVarRet:
        ret

;;  expects: *name in hl, var type token in a
DeleteVar::
        dec hl
        rst rMOV9TOOP1
        ld (OP1),a
        bcall _ChkFindSym
        jr c,DeleteVarRet ; var doesn't exist (maybe not necessary?)
        bcall _DelVarArc
DeleteVarRet:
        ret
