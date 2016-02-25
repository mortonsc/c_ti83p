;; Code Copyright (c) 2016 Scott Morton
;; This is free software, released under the MIT license.
;; See the bundled LICENSE.txt for more information.

;; This file contains functions for working with floating point values
;; and the calculator's floating point variables

        .module floatingpoint
        .optsdcc -mz80

        .globl _CGetAnsFP
        .globl _CGetVarFP
        .globl _CMakeVarFP
        .globl _CAddFP
        .globl _CSubFP
        .globl _CMultFP
        .globl _CDivFP

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

;; Finds the real variable with the given name.
;; Input: a = name of var ('A' - 'Z' or theta)
;; Output: same as FindSym
;; destroys: all
LookUpVarH:
        ld (RealVarName+1),a
        ld hl,#RealVarName
        rst rMOV9TOOP1
        rst rFINDSYM
        ret
RealVarName:
        .db RealObj,0,0,0 ; second byte holds variable identifier

;; Copies the contents of OP1 into (de)
;; Input: de = destination address
;; destroys: de,hl,bc
LoadFromOP1H:
        ld hl,#OP1
        ld b,#9
        ld c,#0
        ldir
        ret

;; FloatingPoint *CGetAnsFP();
_CGetVarFP::
        push ix
        ld ix,#0
        add ix,sp
        ld a,4(ix)
        call LookUpVarH
        jr c,VarDoesNotExist
        ex de,hl ; load address into return value
        jr GetVarFPRet
VarDoesNotExist:
        ld h,#0 ; return NULL
        ld l,#0
GetVarFPRet:
        pop ix
        ret

;; FloatingPoint *CMakeVarFP(char var_name);
_CMakeVarFP::
        push ix
        ld ix,#0
        add ix,sp
        ld a,4(ix)
        call LookUpVarH
        jr nc,VarExists
        bcall _CreateReal ; stores address in de
VarExists:
        ld hl,#FloatingPoint0
        ld b,#9
        ld c,#0
        push de ; preserve de, as ldir decreases it by 9
        ldir  ; initialize value to 0.0
        pop hl
        pop ix
        ret
FloatingPoint0:
        .db 0,0x80,0,0,0,0,0,0,0

;; void CAddFP(FloatingPoint *add1, FloatingPoint *add2, FloatingPoint *sum);
_CAddFP::
        push ix
        ld ix,#0
        add ix,sp
        ld l,4(ix) ; load first argument
        ld h,5(ix)
        rst rMOV9TOOP1
        ld l,6(ix) ; load second argument
        ld h,7(ix)
        bcall _Mov9ToOP2
        rst rFPADD
        ld e,8(ix) ; load return destination
        ld d,9(ix)
        call LoadFromOP1H
        pop ix
        ret

;; void CSubFP(FloatingPoint *sub1, FloatingPoint *sub2, FloatingPoint *diff);
_CSubFP::
        push ix
        ld ix,#0
        add ix,sp
        ld l,4(ix) ; load first argument
        ld h,5(ix)
        rst rMOV9TOOP1
        ld l,6(ix) ; load second argument
        ld h,7(ix)
        bcall _Mov9ToOP2
        bcall _FPSub
        ld e,8(ix) ; load return destination
        ld d,9(ix)
        call LoadFromOP1H
        pop ix
        ret

;; void CMultFP(FloatingPoint *fac1, FloatingPoint *fac2, FloatingPoint *prod);
_CMultFP::
        push ix
        ld ix,#0
        add ix,sp
        ld l,4(ix) ; load first argument
        ld h,5(ix)
        rst rMOV9TOOP1
        ld l,6(ix) ; load second argument
        ld h,7(ix)
        bcall _Mov9ToOP2
        bcall _FPMult
        ld e,8(ix) ; load return destination
        ld d,9(ix)
        call LoadFromOP1H
        pop ix
        ret

;; void CDivFP(FloatingPoint *dividend, FloatingPoint *divisor,
;;                                          FloatingPoint *quot);
_CDivFP::
        push ix
        ld ix,#0
        add ix,sp
        ld l,4(ix) ; load first argument
        ld h,5(ix)
        rst rMOV9TOOP1
        ld l,6(ix) ; load second argument
        ld h,7(ix)
        bcall _Mov9ToOP2
        bcall _fpdiv
        ld e,8(ix) ; load return destination
        ld d,9(ix)
        call LoadFromOP1H
        pop ix
        ret

