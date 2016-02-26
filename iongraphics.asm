;; This file contains some of the graphics routines used in the ION shell.
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
;; along with this library  If not, see <http://www.gnu.org/licenses/>.
;;
;; As a special exception, if you link this library in unmodified form with
;; other files to produce an executable, this library does not by itself cause
;; the resulting executable to be covered by the GNU General Public License.
;; This exception does not however invalidate any other reasons why
;; the executable file might be covered by the GNU General Public License.
;;
;; The routines themselves were written by Joe Wingbermuehle,
;; and were copied directly the source on wikiti.brandonw.net,
;; modified in the week of 20 Feb 2016 only to make them compatible
;; with sdasz80 and not require any ION includes.


        .globl _FastCopy
        .globl _PutLargeSprite

        .area DATA

.nlist
.include "ti83plus.inc"
.list

        .area CODE

;; void FastCopy();
;-----> Copy the gbuf to the screen (fast)
;Input: nothing
;Output: graph buffer is copied to the screen
_FastCopy::
        di
        ld a,#0x80
        out (0x10),a

        ld hl, #plotSScreen-12-(-(12*64)+1)

        ld a,#0x20
        ld c,a
        inc hl
        dec hl
fastCopyAgain:
        ld b,#64
        inc c
        ld de,#-767
        out (0x10),a
        add hl,de
        ld de,#10
fastCopyLoop:
        add hl,de
        inc hl
        inc hl
        inc de
        ld a,(hl)
        out (0x11),a
        dec de
        djnz fastCopyLoop
        ld a,c
        cp #0x2B+1
        jr nz,fastCopyAgain
        ret

;; void PutLargeSprite(unsigned char x, unsigned char y, LargeSprite *sprite);
_PutLargeSprite::
        ; wrapper for largeSprite; takes C arguments from the stack and stores
        ; them in the appropriate registers.
        push ix
        ld ix,#0
        add ix,sp

        ld a,4(ix)
        ld d,5(ix) ; this argument will go in l later
        ld l,6(ix)
        ld h,7(ix)
        ld b,(hl) ; first element of struct is height
        inc hl
        ld c,(hl) ; then width
        inc hl  ; finally the actual sprite contents

        push hl ; largeSprite takes the address in ix
        pop ix ; ok because we don't need the value of ix after this
        ld l,d
        call largeSpriteH

        pop ix
        ret

;=======================
;LargeSprite
;by Joe Wingbermuehle
;=======================
;Does:   Copy a sprite to the gbuf
;Input:  ix=sprite address, a='x', l='y', b='height' (in pixels), c='width' (in bytes, e.g. 2 would be 16)
;Output: The sprite is copied to the gbuf
;-----------------------
largeSpriteH:
        di
        ex   af,af'

        ld   a,c
        push   af
        ex   af,af'

        ld   e,l
        ld   h,#0
        ld   d,h
        add   hl,de
        add   hl,de
        add   hl,hl
        add   hl,hl
        ld   e,a
        and   #0x07
        ld   c,a
        srl   e
        srl   e
        srl   e
        add   hl,de
        ld   de, #plotSScreen
        add   hl,de
largeSpriteLoop1:
        push   hl
largeSpriteLoop2:
        ld   d,(ix)
        ld   e,#0x00
        ld   a,c
        or   a
        jr   z,largeSpriteSkip1
largeSpriteLoop3:
        srl   d
        rr   e
        dec   a
        jr   nz,largeSpriteLoop3
largeSpriteSkip1:
        ld   a,(hl)
        xor   d
        ld   (hl),a
        inc   hl
        ld   a,(hl)
        xor   e
        ld   (hl),a
        inc   ix
        ex   af,af'

        dec   a
        push   af
        ex   af,af'

        pop   af
        jr   nz,largeSpriteLoop2
        pop   hl
        pop   af
        push   af
        ex   af,af'

        ld   de,#0x0C
        add   hl,de
        djnz   largeSpriteLoop1
        pop   af
        ret
