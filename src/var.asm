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



;; Function bodies (generic in the type of variable)

;; expects: *name in hl, var type token in a, pointer for size in de
RecallVar::
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
;;          bcall for creating in de
CreateVar::
        ;; this function is done in a weird way
        ;; (storing size in code area, etc)
        ;; because normal ways all crashed for unclear reasons
        ;; (something to do with the error handler)
        ld (#CreateVarBcall),de
        ld (#VarSize),bc
        dec hl
        rst rMOV9TOOP1
        ld (OP1),a
        bcall _ChkFindSym
        jr c,MakeNewVar
        push ix
        bcall _DelVarArc    ; delete the AppVar if it exists
        pop ix
MakeNewVar:
        AppOnErr InsufficientMem
        ld hl,(#VarSize)
        rst rBR_CALL    ; call bcall stored in next two bytes
CreateVarBcall:
        .dw #_JError    ; caller overwrites
AfterBcall:
        AppOffErr
        ld bc,(#VarSize)
        ex de,hl ; now hl contains address
        ld (hl),c ; store the size in the first two bytes of the new object
        inc hl
        ld (hl),b
        inc hl ; return the address of the data
        ret
InsufficientMem:
        ld hl,#0 ; failed to create var, so return null
        ret
VarSize:
        .dw #0x0000  ; variable

;; expects: *name in hl, var type token in a
ArchiveVar::
        dec hl
        rst rMOV9TOOP1
        ld (OP1),a
        bcall _ChkFindSym
        jr c,ArchiveVarRet ; doesn't exist
        ld a,b
        or a   ; check if the var is already archived
        jr nz,ArchiveVarRet
        push ix
        AppOnErr ArchiveVarErr
        bcall _Arc_Unarc
        AppOffErr
ArchiveVarErr:
        pop ix
ArchiveVarRet:
        ret

;;  expects: *name in hl, var type token in a
DeleteVar::
        dec hl
        rst rMOV9TOOP1
        ld (OP1),a
        bcall _ChkFindSym
        jr c,DeleteVarRet ; var doesn't exist (maybe not necessary?)
        push ix     ; _DelVarArc destroys ix
        bcall _DelVarArc
        pop ix
DeleteVarRet:
        ret
