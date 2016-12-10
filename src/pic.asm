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

        .module pic

        .area _DATA

.nlist
.include "ti83plus.inc"
.list

        .area _CODE

;; Functions for working with PicVars


PicName:
    .db tVarPict,0,0,0,0,0,0,0    ; pic number goes in 2rd byte
PicSize:
    .db 0,0             ; recall code needs somewhere to store size

;; unsigned char *CRecallPic(unsigned char picNo);
_CRecallPic::
    pop de  ; return address
    pop hl  ; picNo
    push hl
    push de
    ld a,l
    dec a
    ld (#PicName+1),a
    ld hl,#PicName
    ld de,#PicSize
    ld a,#PictObj
    jp RecallVar

;; unsigned char *CCreatePic(uint8_t picNo);
_CCreatePic::
    pop de  ; return address
    pop hl  ; picNo
    push hl
    push de
    ld a,l
    dec a
    ld (#PicName+1),a
    ld hl,#PicName
    ld bc,#756  ; pics are always the same size
    ld a,#PictObj
    ld de,#_CreatePict
    jp CreateVar

;; void CArchivePic(unsigned char picNo);
_CArchivePic::
    pop de  ; return address
    pop hl  ; picNo
    push hl
    push de
    ld a,l
    dec a
    ld (#PicName+1),a
    ld hl,#PicName
    ld a,#PictObj
    jp ArchiveVar

;; void CDeletePic(unsigned char picNo)
_CDeletePic::
    pop de  ; return address
    pop hl  ; picNo
    push hl
    push de
    ld a,l
    dec a
    ld (#PicName+1),a
    ld hl,#PicName
    ld a,#PictObj
    jp DeleteVar

