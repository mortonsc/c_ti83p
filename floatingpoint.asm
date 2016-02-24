;; Code Copyright (c) 2016 Scott Morton
;; This is free software, released under the MIT license.
;; See the bundled LICENSE.txt for more information.

;; This file contains functions for working with floating point values
;; and the calculator's floating point variables

        .module floatingpoint
        .optsdcc -mz80

        .globl _CGetAnsFP

        .area _DATA

.nlist
.include "ti83plus.inc"
.list

        .area _CODE

_CGetAnsFP::
        bcall _AnsName ; stores the name of Ans in OP1
        rst rFINDSYM
        and #0x1f  ; FindSym stores the type in a, but bits 5-7 are garbage
        jr nz,AnsNotFP ; 0x00 is type code for real floating point
        ex de,hl ; de stores the address, which is what we want
        ret
AnsNotFP:
        ld h,#0 ; return null if ans is not real fp
        ld l,#0
        ret

_CGetVarFP::
        push ix
        ld ix,#0
        add ix,sp
        ld a,4(ix)
        ld (RealVarName+1),a
        ld hl,#RealVarName
        rst rMOV9TOOP1
        rst rFINDSYM
        jr c,VarDoesNotExist
        ex de,hl ; load address into return value
        jr GetVarFPRet
VarDoesNotExist:
        ld h,#0 ; return NULL
        ld l,#0
GetVarFPRet:
        pop ix
        ret
RealVarName:
        .db RealObj,0,0,0 ; second byte holds variable identifier


