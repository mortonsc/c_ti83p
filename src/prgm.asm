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

        .module prgm

        .area _DATA

.nlist
.include "ti83plus.inc"
.list

        .area _CODE

;; Functions for working with programs

;; void *CRecallPrgm(const uint8_t *name, uint16_t *size);
_CRecallPrgm::
        pop bc  ; return address
        pop hl  ; *name
        pop de  ; *size
        push de
        push hl
        push bc
        ld a,#ProgObj
        jp RecallVar


;; void CArchivePrgm(const uint8_t *name);
_CArchivePrgm::
        pop bc ;; return address
        pop hl ;; *name
        push hl
        push bc
        ld a,#ProgObj
        jp ArchiveVar

;; void *CCreatePrgm(const uint8_t *name, uint16_t size);
_CCreatePrgm::
        pop de  ; return address
        pop hl  ; *name
        pop bc  ; size
        push bc
        push hl
        push de
        ld a,#ProgObj
        ld de,#_CreateProg
        jp CreateVar

;; void *CCreateProtPrgm(const uint8_t *name, uint16_t size);
_CCreateProtPrgm::
        pop de  ; return address
        pop hl  ; *name
        pop bc  ; size
        push bc
        push hl
        push de
        ld a,#ProtProgObj
        ld de,#_CreateProtProg
        jp CreateVar

;; void CDeletePrgm(const uint8_t *name);
_CDeletePrgm::
        pop bc ;; return address
        pop hl ;; *name
        push hl
        push bc
        ld a,#ProgObj
        jp DeleteVar

