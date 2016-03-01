;; This file contains functions for generating random numbers.
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
;; along with this library.  If not, see <http://www.gnu.org/licenses/>.
;;
;; As a special exception, if you link this library in unmodified form with
;; other files to produce an executable, this library does not by itself cause
;; the resulting executable to be covered by the GNU General Public License.
;; This exception does not however invalidate any other reasons why
;; the executable file might be covered by the GNU General Public License.
;;
;; The ionRandom function is taken directly from the source of
;; Joe Wingbermuehle's Ion shell, with modifications to make it Ion-independent
;; and sdasz80-compatible.

        .module rand

        .globl _CRandInt

        .area _DATA

.nlist
.include "ti83plus.inc"
.list

        .area _CODE

;; Generates a seed for the RNG
;; Inputs: none
;; Outputs: new seed stored in rand_seed, is_seeded set to 1
;; Destroys: de, hl, a
GenSeedH:
        bcall _Random   ; grab a couple bytes from the calc's rand function
        ld de,#rand_seed ; hardly perfect, but it should be good enough
        ld hl,#OP1+3
        ldi
        ldi
        ld a,#1
        ld (is_seeded),a
        ret

;; uint8_t CRandInt(uint8_t max);
_CRandInt::
        push ix
        ld ix,#0
        add ix,sp

        ld a,(is_seeded)
        call z,GenSeedH

        ld b,4(ix)
        call ionRandom
        ld l,a

        pop ix
        ret

;-----> Generate a random number
; input b=upper bound
; ouput a=answer 0<=a<b
; all registers are preserved except: af and bc
ionRandom:
	push	hl
	push	de
	ld	hl,(rand_seed)
	ld	a,r
	ld	d,a
	ld	e,(hl)
	add	hl,de
	add	a,l
	xor	h
	ld	(rand_seed),hl
	sbc	hl,hl
	ld	e,a
	ld	d,h
randomLoop:
	add	hl,de
	djnz	randomLoop
	ld	a,h
	pop	de
	pop	hl
	ret

rand_seed:
        .dw #0x0000
is_seeded:
        .db #0x00

