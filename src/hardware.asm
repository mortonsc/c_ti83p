;; This file implements functions for getting hardware information.
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

        .module hardware

        .area _DATA

.nlist
.include "ti83plus.inc"
.list

        .area _CODE

;; Model CGetCalcModel();
_CGetCalcModel::
        in a,(2)
        ld b,a
        and #0x80
        jr z,TI83PlusBasic
        in a,(0x21)
        and #3
        jr z,TI84PlusBasic
        bit 5,b
        jr z,TI83PlusSE
        ;; calculator is 84+SE
        ld l,#3
        ret
TI83PlusBasic:
        ld l,#0
        ret
TI83PlusSE:
        ld l,#1
        ret
TI84PlusBasic:
        ld l,#2
        ret

;; void CResetContrast();
_CResetContrast::
        ld a,(contrast)
        add a,#0xD8
        call _LCD_BUSY_QUICK
        out (0x10),a
        ret

;; void CSetContrast(uint8_t level);
_CSetContrast::
        push ix
        ld ix,#0
        add ix,sp

        ld a,4(ix)
        cp #0x40
        jr nc,SetContrastRet
        add a,#0xC0
        call _LCD_BUSY_QUICK
        out (0x10),a
SetContrastRet:
        pop ix
        ret

;; void CLCDOn();
_CLCDOn::
        ld a,#3
        call _LCD_BUSY_QUICK
        out (0x10),a
        ret

;; void CLCDOff();
_CLCDOff::
        ld a,#2
        call _LCD_BUSY_QUICK
        out (0x10),a
        ret

;; bool CIsBatteryLow();
_CIsBatteryLow::
        ld l,#0
        in a,(2)
        bit 0,a
        ret nz ; batteries are good
        inc l
        ret    ; batteries are low

