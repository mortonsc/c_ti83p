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

        .module keyboard

        .area _DATA

.nlist
.include "ti83plus.inc"
.list

        .area _CODE

;; uint8_t CGetKey();
_CGetKey::
        bcall _getkey
        ld l,a
        ret


;; uint8_t CGetCSC();
_CGetCSC::
        bcall _GetCSC
	ld l,a
	ret

;; bool CIsKeyPressed(uint8_t key);
_CIsKeyPressed::
        push ix
        ld ix,#0
        add ix,sp

        di
        ld c,#0x01 ; keyboard port
        ld a,#0xFF ; clear the port
        out (c),a

        ld hl,#masks ; find the group mask corresponding to this key
        push hl
        ld a,4(ix)
        dec a
        ld d,#0
        ld e,a
        srl e ; divide by 8 to get the bit of the group
        srl e
        srl e
        add hl,de
        ld b,(hl)
        out (c),b

        pop hl
        in b,(c)
        ld e,#0x07 ; mask to take mod 8
        and e
        ld e,a  ; e now contains bit number of key
        add hl,de
        ld a,(hl) ; store key_mask in a
        ld c,a
        or b    ; key_mask | output is identical to key_mask iff key pressed
        cp c    ; z if key pressed, nz otherwise

        ei
        pop ix
        ld l,#0
        ret nz
        inc l
        ret

masks:
        .db 0xFE
        .db 0xFD
        .db 0xFB
        .db 0xF7
        .db 0xEF
        .db 0xDF
        .db 0xBF
        .db 0x7F

