;; This file implements functions for creating and modifying programs.
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

        .module err

        .area _DATA

.nlist
.include "ti83plus.inc"
.list

        .area _CODE

;; void CThrowError(Error err);
_CThrowError::
        ;; we're not returning, so it's ok to mess up the stack
        pop hl
        pop hl
        ld a,l
        bjump _JError

;; void CThrowCustomError(const uint8_t *err_message);
_CThrowCustomError::
        pop hl
        pop hl
        ld de,#appErr1
        ld bc,#14
        ldir
        bjump _ErrCustom1

