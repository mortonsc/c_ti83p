;; This file implements functions for creating and modifying AppVars.
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

        .module appvar

        .globl _CRecallAppVar
        .globl _CCreateAppVar
        .globl _CArchiveAppVar
        .globl _CDeleteAppVar

        .area _DATA

.nlist
.include "ti83plus.inc"
.list

        .area _CODE

;; finds a AppVar with the name given as a c-string
;; inputs: hl = address of string containing name
;; outputs: same as FindSym
;; destroys: all
FindAppVarH:
        ; the format of an AppVar name is AppVarObj followed by a
        ; null-terminated string (unless it fills the whole 8 bytes)
        ; so it's easiest to simply load the string directly into OP1
        dec hl
        rst rMOV9TOOP1
        ld a,#AppVarObj
        ld (OP1),a
        bcall _ChkFindSym
        ret

;; void *CRecallAppVar(const uint8_t *name, int *size);
_CRecallAppVar::
        push ix
        ld ix,#0
        add ix,sp
        ld l,4(ix)
        ld h,5(ix)
        call FindAppVarH
        jr c,AppVarNotFound
        ld a,b
        or a ; check if AppVar is archived
        jr z,AppVarInRam
        push ix ; _Arc_Unarc destroys all regs
        bcall _PushRealO1
        bcall _Arc_Unarc
        bcall _PopRealO1
        pop ix
        bcall _ChkFindSym ; find the new address of the var
AppVarInRam:
        ex de,hl ; move address of var to hl
        ld e,6(ix)
        ld d,7(ix)
        ldi ; store size of var in second argument
        ldi ; and return the address of actual contents
        pop ix
        ret
AppVarNotFound:
        ld l,#0 ; return null for var address
        ld h,#0 ; and leave the second argument alone
        pop ix
        ret

;; void *CCreateAppVar(const uint8_t *name, int size);
_CCreateAppVar::
        push ix
        ld ix,#0
        add ix,sp
        ld l,4(ix)
        ld h,5(ix)
        call FindAppVarH
        jr c,MakeNewVar
        push ix ; DelVarArc destroys regs
        bcall _DelVarArc ; delete the AppVar if it exists
        pop ix
MakeNewVar:
        ld l,6(ix)
        ld h,7(ix) ; load the desired size
        push hl ; save the size
        bcall _CreateAppVar
        pop hl
        ex de,hl ; now hl contains address, de contains size
        ld (hl),e ; store the size in the first two bytes of the new object
        inc hl
        ld (hl),d
        inc hl ; return the address of the data
        pop ix
        ret

;; void CArchiveAppVar(const uint8_t *name);
_CArchiveAppVar::
        push ix
        ld ix,#0
        add ix,sp
        ld l,4(ix)
        ld h,5(ix)
        call FindAppVarH
        jr c,ArchiveAppVarRet ; var doesn't exist
        ld a,b
        or a   ; check if the var is already archived
        jr nz,ArchiveAppVarRet
        bcall _Arc_Unarc
ArchiveAppVarRet:
        pop ix
        ret

;; void CDeleteAppVar(const uint8_t *name);
_CDeleteAppVar::
        push ix
        ld ix,#0
        add ix,sp
        ld l,4(ix)
        ld h,5(ix)
        call FindAppVarH
        jr c,DeleteAppVarRet ; var doesn't exist
        bcall _DelVarArc
DeleteAppVarRet:
        pop ix
        ret

