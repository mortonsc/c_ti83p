;; This file implements functions for creating and modifying picture variables.
;;
;; Copyright (C) 2016 Scott Morton
;;
;; This program is free software: you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 3 of the License, or
;; (at your option) any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this program.  If not, see <http://www.gnu.org/licenses/>.

        .module picvars
        .optsdcc -mz80

        .globl _CRecallPic
        .globl _CStorePic

        .area _DATA

.nlist
.include "ti83plus.inc"
.list

        .area _CODE

;; finds a picture variable
;; Inputs: a = picNo (1 for Pic1, etc)
;; Outputs: same as FindSym
;; destroys: all
FindPicH:
        dec a ; Pic1 is 0x00, Pic2 is 0x01, etc.
        ld (#PicName+2),a ; set which picture we want to load
        ld hl,#PicName
        rst rMOV9TOOP1
        rst rFINDSYM
        ret
PicName:
        .db PictObj,tVarPict,0,0

_CRecallPic::
	push	ix
	ld	ix,#0
	add	ix,sp
        ld a,4(ix)
        call FindPicH
        jr c,PicNotFound
        ld a,b
        or a ; check if pic is in RAM (not archived)
        jr z,PicInRam
        bcall _Arc_Unarc
PicInRam:
        ex de,hl    ; move address of pic to hl
        inc hl
        inc hl  ; first 2 bytes are the size of the image
        jr CRecallPicRet
PicNotFound:
        ld h,#0
        ld l,#0
CRecallPicRet:
        pop ix
        ret

_CStorePic::
        push ix
        ld ix,#0
        add ix,sp

        ld a,4(ix)
        call FindPicH
        jr c,CreatePic
        bcall _DelVarArc ; delete the var if it exists
CreatePic:
        bcall _CreatePict ; stores address in de
        ld a,#0xF4 ; store size of image in first 2 bytes
                   ; and in bc, which is the counter for copying
        ld (de),a
        ld c,a
        inc de
        ld a,#0x02
        ld (de),a
        ld b,a
        inc de

        ld l,5(ix)
        ld h,6(ix)
        ldir  ; copy data from argument pointer to the new image

        pop ix
        ret

