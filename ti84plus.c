#include <string.h>
#include "ti84plus.h"

/*
 * Copyright (c) 2016 Scott Morton
 * This is free software released under the MIT license.
 * For more information, see the LICENSE.txt file
 * which should be bundled with this source.
 */

/*
 * These functions are mostly C wrappers for various ROM calls.
 * A few turn flags on or off.
 * The sequence
 *      rst #0x28
 *      .dw #0xNNNN
 * calls the ROM function located at address NNNN.
 */

void GrBufCpy() __naked
{
    __asm
        rst #0x28
        .dw #0x486A
        ret
    __endasm;
}

void ClrLCDFull() __naked
{
    __asm
        rst #0x28
        .dw #0x4540
        ret
    __endasm;
}

void NewLine() __naked
{
    __asm
        rst #0x28
        .dw #0x452E
        ret
    __endasm;
}

void PutC(char c)
{
    c;

    __asm
        ld a,4(ix)
        rst #0x28
        .dw #0x4504
    __endasm;
}

void PutS(char *s)
{
    /* stop compiler from complaining about unused variable */
    s;

    __asm
        ld l,4(ix)
        ld h,5(ix)
        rst #0x28
        .dw #0x450A
    __endasm;
}

void PutMap(char c)
{
    c;

    __asm
        ld a,4(ix)
        rst #0x28
        .dw #0x4501
    __endasm;
}

void VPutS(char *s)
{
    s;

    __asm
        ld l,4(ix)
        ld h,5(ix)
        rst #0x28
        .dw #0x4561
    __endasm;
}

unsigned char GetKey() __naked
{
    __asm
        rst #0x28
        .dw #0x4972
        ld l,a
        ret
    __endasm;
}

unsigned char GetCSC() __naked
{
    __asm
        rst #0x28
        .dw #0x4018
        ld l,a
        ret
    __endasm;
}

void TextInvertOn() __naked
{
    __asm
        set 3,5(iy)
        ret
    __endasm;
}

void TextInvertOff() __naked
{
    __asm
        res 3,5(iy)
        ret
    __endasm;
}

void LowerCaseOn() __naked
{
    __asm
        set 3,0x24(iy)
        ret
    __endasm;
}

void LowerCaseOff() __naked
{
    __asm
        res 3,0x24(iy)
        ret
    __endasm;
}

void RunIndicatorOn() __naked
{
    __asm
        set 0,0x12(iy)
        ret
    __endasm;
}

void RunIndicatorOff() __naked
{
    __asm
        res 0,0x12(iy)
        ret
    __endasm;
}

void EnableAPD() __naked
{
    __asm
        rst #0x28
        .dw #0x4C87
        ret
    __endasm;
}

void DisableAPD() __naked
{
    __asm
        rst #0x28
        .dw #0x4C84
        ret
    __endasm;
}

/*
 * Code taken from wikiti (https://www.cemetech.net/forum/viewtopic.php?t=7087)
 */
void Enable15MHz() __naked
{
    __asm
        in a,(2)
        and #0x80
        ret z ; No CPU governor on this calc
        rlca
        out (#0x20),a
        ret
    __endasm;
}

