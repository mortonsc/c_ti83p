;; This file contains C wrappers for simple calculator functions
;; that only require a few lines of assembly.
;; Most of them are either bare ROM calls or else set a system flag.
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


	.module ti83plus
	.optsdcc -mz80

	.globl _CGrBufCpy
	.globl _CClrLCDFull
	.globl _CNewLine
	.globl _CPutC
	.globl _CPutS
        .globl _CPutInt
	.globl _CPutMap
	.globl _CVPutS
	.globl _CGetKey
	.globl _CGetCSC
	.globl _CTextInvertOn
	.globl _CTextInvertOff
	.globl _CLowerCaseOn
	.globl _CLowerCaseOff
	.globl _CRunIndicatorOn
	.globl _CRunIndicatorOff
	.globl _CEnableAPD
	.globl _CDisableAPD
	.globl _CEnable15MHz
	.globl _CDisable15MHz

	.area _DATA

.nlist
.include "ti83plus.inc"
.list

	.area _CODE

_CGrBufCpy::
        bcall _GrBufCpy
	ret

_CClrLCDFull::
        bcall _ClrLCDFull
	ret


_CNewLine::
	bcall _newline
	ret

_CPutC::
	push	ix
	ld	ix,#0
	add	ix,sp

	ld a,4(ix)
	bcall _PutC

	pop	ix
	ret


_CPutS::
	push	ix
	ld	ix,#0
	add	ix,sp

	ld l,4(ix)
	ld h,5(ix)
	bcall _PutS
	pop	ix
	ret

_CPutInt:
        push ix
        ld ix,#0
        add ix,sp

        ld l,4(ix)
        ld h,5(ix)
        bcall _DispHL
        pop ix
        ret

_CPutMap::
	push	ix
	ld	ix,#0
	add	ix,sp

	ld a,4(ix)
	bcall _PutMap
	pop	ix
	ret


_CVPutS::
	push	ix
	ld	ix,#0
	add	ix,sp

	ld l,4(ix)
	ld h,5(ix)
	bcall _VPutS

	pop	ix
	ret


_CGetKey::
	bcall _getkey
	ld l,a
	ret


_CGetCSC::
        bcall _GetCSC
	ld l,a
	ret


_CTextInvertOn::
	set textInverse,textFlags(iy)
	ret


_CTextInvertOff::
	res textInverse,textFlags(iy)
	ret


_CLowerCaseOn::
	set lwrCaseActive,appLwrCaseFlag(iy)
	ret


_CLowerCaseOff::
	res lwrCaseActive,appLwrCaseFlag(iy)
	ret


_CRunIndicatorOn::
	bcall _RunIndicOn
	ret


_CRunIndicatorOff::
	bcall _RunIndicOff
	ret


_CEnableAPD::
        bcall _EnableApd
	ret


_CDisableAPD::
	bcall _DisableApd
	ret


_CEnable15MHz::
	in a,(2)
	and #0x80
	ret z ; No CPU governor on this calc
	rlca
	out (0x20),a ; port 20 controls CPU speed
	ret

_CDisable15MHz::
	ld a,#0
	out (0x20),a
	ret


