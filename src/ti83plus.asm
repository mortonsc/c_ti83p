;; This file contains C wrappers for simple calculator functions
;; that only require a few lines of assembly.
;; Most of them are either bare ROM calls or else set a system flag.
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


	.module ti83plus
	.optsdcc -mz80

	.globl _CGrBufCpy
	.globl _CClrLCDFull
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

;; void CGrBufCpy();
_CGrBufCpy::
        bcall _GrBufCpy
	ret

;; void CClrLCDFull();
_CClrLCDFull::
        bcall _ClrLCDFull
	ret

;; void CTextInvertOn();
_CTextInvertOn::
	set textInverse,textFlags(iy)
	ret


;; void CTextInvertOff();
_CTextInvertOff::
	res textInverse,textFlags(iy)
	ret

;; void CTextWriteOn();
_CTextWriteOn::
	set textWrite,sGrFlags(iy)
	ret

;; void CTextWriteOff();
_CTextWriteOff::
	res textWrite,sGrFlags(iy)
	ret

;; void CLowerCaseOn();
_CLowerCaseOn::
	set lwrCaseActive,appLwrCaseFlag(iy)
	ret


;; void CLowerCaseOff();
_CLowerCaseOff::
	res lwrCaseActive,appLwrCaseFlag(iy)
	ret


;; void CRunIndicatorOn();
_CRunIndicatorOn::
	bcall _RunIndicOn
	ret


;; void CRunIndicatorOff();
_CRunIndicatorOff::
	bcall _RunIndicOff
	ret


;; void CEnableAPD();
_CEnableAPD::
        bcall _EnableApd
	ret


;; void CDisableAPD();
_CDisableAPD::
	bcall _DisableApd
	ret


;; void CEnable15MHz();
_CEnable15MHz::
	in a,(2)
	and #0x80
	ret z ; No CPU governor on this calc
	rlca
	out (0x20),a ; port 20 controls CPU speed
	ret

;; void CDisable15MHz();
_CDisable15MHz::
	ld a,#0
	out (0x20),a
	ret


