;-----> Copy the gbuf to the screen (fast)
;Input: nothing
;Output: graph buffer is copied to the screen
; code by Joe Wingbermuehle
; taken from http://wikiti.brandonw.net/index.php?title=Z80_Routines:Graphic:Fastcopy
; retrieved 2 Feb 2016
; modified to be SDCC-compatible
        .globl _FastCopy
        .area OSEG

_FastCopy:
        di
        ld a,#0x80
        out (#0x10),a

        ;; ld hl,gbuf-12-(-(12*64)+1)
        ld hl,#0x9633

        ld a,#0x20
        ld c,a
        inc hl
        dec hl
fastCopyAgain:
        ld b,#64
        inc c
        ld de,#-767
        out (#0x10),a
        add hl,de
        ld de,#10
fastCopyLoop:
        add hl,de
        inc hl
        inc hl
        inc de
        ld a,(hl)
        out (#0x11),a
        dec de
        djnz fastCopyLoop
        ld a,c
        cp #0x2B+1
        jr nz,fastCopyAgain
        ret
