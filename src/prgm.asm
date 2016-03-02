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

;; finds a program with the name given as a c-string
;; inputs: hl = address of string containing name
;; outputs: same as FindSym
;; destroys: all
FindPrgmH:
        dec hl
        rst rMOV9TOOP1
        ld a,#ProgObj
        ld (OP1),a
        bcall _ChkFindSym
        ret

;; void *CRecallPrgm(const uint8_t *name, uint16_t *size);
_CRecallPrgm::
        push ix
        ld ix,#0
        add ix,sp
        ld l,4(ix)
        ld h,5(ix)
        call FindPrgmH
        jr c,PrgmFailed
        ld a,b
        or a ; check if archived
        jr z,PrgmInRam
        AppOnErr UnarchivePrgmFailed
        push ix ; _Arc_Unarc destroys all regs
        rst rPUSHREALO1
        bcall _Arc_Unarc
        bcall _PopRealO1
        pop ix
        AppOffErr
        bcall _ChkFindSym ; find the new address
PrgmInRam:
        ex de,hl ; move address to hl
        ld e,6(ix)
        ld d,7(ix)
        ldi ; store size in second argument
        ldi ; and return the address of actual contents
        pop ix
        ret
UnarchivePrgmFailed:
        bcall _PopRealO1
        pop ix
PrgmFailed:
        ld hl,#0; return null for var address
        pop ix
        ret

;; CreatePrgm and CreateProtPrgm are nearly identical, so they jump to a
;; shared body, and push a flag to indicate what kind of program to make.

;; void *CCreatePrgm(const uint8_t *name, uint16_t size);
_CCreatePrgm::
        push ix
        ld ix,#0
        add ix,sp
        ld a,#1
        or a  ; reset zero flag
        push af
        jr CreatePrgm

;; void *CCreateProtPrgm(const uint8_t *name, uint16_t size);
_CCreateProtPrgm::
        push ix
        ld ix,#0
        add ix,sp
        xor a  ; set zero flag
        push af

CreatePrgm:
        ld l,4(ix)
        ld h,5(ix)
        call FindPrgmH
        jr c,MakeNewPrgm
        push ix ; DelVarArc destroys regs
        bcall _DelVarArc ; delete the program if it exists
        pop ix
MakeNewPrgm:
        pop af ; recall what kind of program to make
        AppOnErr InsufficientMem
        ld l,6(ix)
        ld h,7(ix) ; load the desired size
        push hl ; save the size
        jr z,MakeProtPrgm
        bcall _CreateProg
        jr InitPrgm
MakeProtPrgm:
        ld a,#ProtProgObj
        ld (OP1),a
        bcall _CreateProtProg
InitPrgm:
        pop hl
        ex de,hl ; now hl contains address, de contains size
        ld (hl),e ; store the size in the first two bytes of the new object
        inc hl
        ld (hl),d
        inc hl ; return the address of the data
        pop ix
        ret
InsufficientMem:
        ld hl,#0 ; failed to create program, return null
        pop ix
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
        push ix
        ld ix,#0
        add ix,sp
        ld l,4(ix)
        ld h,5(ix)
        call FindPrgmH
        jr c,DeletePrgmRet ; var doesn't exist
        bcall _DelVarArc
DeletePrgmRet:
        pop ix
        ret
