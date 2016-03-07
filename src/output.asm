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
;;
;; Some of these functions were taken in part or in whole from Kevin Horowitz's
;; Axe Parser routines.

	.module output

        .area _DATA

.nlist
.include "ti83plus.inc"
.list

        .area _CODE

;; void CNewLine();
_CNewLine::
	bcall _newline
	ret

;; void CDispChar(uint8_t c);
_CDispChar::
	pop bc
        pop hl
        push hl
        push bc

	ld a,l
	bcall _PutC
	ret

;; void CDispStr(const uint8_t *s);
_CDispStr::
	pop bc
        pop hl
        push hl
        push bc

	bcall _PutS
	ret

;; void CDispInt(uint16_t i);
_CDispInt::
        pop bc
        pop hl
        push hl
        push bc

        bcall _DispHL
        ret

;; void CDispTok(uint8_t tok);
_CDispTok::
        pop hl
        pop de
        push de
        push hl

        ld d,#0
        bcall _PutTokString
        ret

;; void CDisp2ByteTok(uint8_t tok1, uint8_t tok2);
_CDisp2ByteTok::
        pop hl
        pop de
        push de
        push hl

        bcall _PutTokString
        ret

;; void CTextChar(uint8_t c);
_CTextChar::
	pop bc
        pop hl
        push hl
        push bc

	ld a,l
	bcall _VPutMap
	ret


;; void CTextStr(const uint8_t *s);
_CTextStr::
	pop bc
        pop hl
        push hl
        push bc

	bcall _VPutS
	ret

;; void CTextInt(uint16_t i);
_CTextInt::
        pop bc
        pop hl
        push hl
        push bc

        bcall _SetXXXXOP2
        bcall _OP2ToOP1
        ld a,#5
        bcall _DispOP1A
        ret

;; void CTextTok(uint8_t tok);
_CTextTok::
        ld hl,#2  ; _Get_Tok_Strng expects a pointer to a token
        add hl,sp ; but the C function takes a value

        bcall _GET_TOK_STRNG
        ld b,a  ; number of characters to display
        ld hl,#OP3
        bcall _VPutSN
        ret

;; as it happens, the process for displaying 1-byte/2-byte tokens is the same
;; the C wrappers are different because they have different signatures

;; void CText2ByteTok(uint8_t tok1, uint8_t tok2);
_CText2ByteTok::
        jp _CTextTok

