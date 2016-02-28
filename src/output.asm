;; This file contains functions for displaying text and other values.
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

	.globl _CNewLine
	.globl _CPutC
	.globl _CPutS
        .globl _CPutInt
	.globl _CPutMap
	.globl _CVPutS

        .area _DATA

.nlist
.include "ti83plus.inc"
.list

        .area _CODE

;; void CNewLine();
_CNewLine::
	bcall _newline
	ret

;; void CPutC(char c);
_CPutC::
	push	ix
	ld	ix,#0
	add	ix,sp

	ld a,4(ix)
	bcall _PutC

	pop	ix
	ret


;; void CPutS(const char *s);
_CPutS::
	push	ix
	ld	ix,#0
	add	ix,sp

	ld l,4(ix)
	ld h,5(ix)
	bcall _PutS
	pop	ix
	ret

;; void CPutInt(int i);
_CPutInt::
        push ix
        ld ix,#0
        add ix,sp

        ld l,4(ix)
        ld h,5(ix)
        bcall _DispHL
        pop ix
        ret

;; void CPutMap(char c);
_CPutMap::
	push	ix
	ld	ix,#0
	add	ix,sp

	ld a,4(ix)
	bcall _PutMap
	pop	ix
	ret


;; void CVPutS(const char *s);
_CVPutS::
	push	ix
	ld	ix,#0
	add	ix,sp

	ld l,4(ix)
	ld h,5(ix)
	bcall _VPutS

	pop	ix
	ret

