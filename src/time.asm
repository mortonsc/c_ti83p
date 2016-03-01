;; This file implements functions for using the calculator's clock and timers.
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
;; The timer functions are based off of example code from wikiti.brandonw.net.

        .module time

        .globl _CWaitSecs

        .area _DATA

.nlist
.include "ti83plus.inc"
.list

        .area _CODE

;; void CWaitSecs(uint8_t secs);
_CWaitSecs::
        push ix
        ld ix,#0
        add ix,sp

        di
        ld a,#0x47  ; set timer 1 to run at 8Hz
        out (0x30),a
        xor a        ; don't loop or generate an interrupt
        out (0x31),a
        ld a,4(ix)
        sla a       ; multiply time by 8 to get number of ticks
        sla a
        sla a
        out (0x32),a ; set how many ticks to wait
        jr WaitLoop

_CWaitCentis::
        push ix
        ld ix,#0
        add ix,sp

        di
        ld a,#0x42 ; set timer 1 to run at ~100Hz
        out (0x30),a
        xor a
        out (0x31),a
        ld a,4(ix)
        out (0x32),a
        jr WaitLoop

_CWaitMillis::
        push ix
        ld ix,#0
        add ix,sp

        di
        ld a,#0x41 ; set timer 1 to run at ~993Hz
        out (0x30),a
        xor a
        out (0x31),a
        ld a,4(ix)
        cp #143      ; if >142 millis, enough error to add another tick
        jr nz,SetTicks
        inc a
SetTicks:
        out (0x32),a
        jr WaitLoop

WaitLoop:
        in a,(4)
        bit 5,a     ; tells if the timer is done
        jr z,WaitLoop
        xor a
        out (0x30),a ; turn the timer off
        out (0x31),a

        ei
        pop ix
        ret
