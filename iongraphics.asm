;; These are some of the graphics routines used in the ION shell.
;; The routines themselves were written by Joe Wingbermuehle.
;; These are copied directly the source on wikiti.brandonw.net,
;; modified only to make them compatible with sdasz80 syntax
;; and to refer to the graph buffer using the name in ti83plus.inc.


;-----> Copy the gbuf to the screen (fast)
;Input: nothing
;Output: graph buffer is copied to the screen
        .globl _FastCopy
        .globl _PutLargeSprite

        .area DATA

.nlist
.include "ti83plus.inc"
.list

        .area CODE

_FastCopy::
        di
        ld a,#0x80
        out (0x10),a

        ld hl, #_plotSScreen-12-(-(12*64)+1)

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

; wrapper for largeSprite; takes C arguments from the stack and stores in the
; appropriate registers.
_PutLargeSprite::
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
        ld   de, #_plotSScreen
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
