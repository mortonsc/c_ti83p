;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.5.0 #9253 (Dec  6 2015) (Linux)
; This file was generated Mon Feb 22 17:33:01 2016
;--------------------------------------------------------
	.module ti84plus
	.optsdcc -mz80

;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _CGrBufCpy
	.globl _CClrLCDFull
	.globl _CNewLine
	.globl _CPutC
	.globl _CPutS
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
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA

.include "ti83plus.inc"

; ram data
;--------------------------------------------------------
	.area _INITIALIZED
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
;	---------------------------------
; Function GrBufCpy
; ---------------------------------
_CGrBufCpy::
        bcall #_GrBufCpy
	ret
;	---------------------------------
; Function ClrLCDFull
; ---------------------------------
_CClrLCDFull::
        bcall #_ClrLCDFull
	ret

;	---------------------------------
; Function NewLine
; ---------------------------------
_CNewLine::
	bcall #_newline
	ret
;	---------------------------------
; Function PutC
; ---------------------------------
_CPutC::
	push	ix
	ld	ix,#0
	add	ix,sp

	ld a,4(ix)
	bcall #_PutC

	pop	ix
	ret

;	---------------------------------
; Function PutS
; ---------------------------------
_CPutS::
	push	ix
	ld	ix,#0
	add	ix,sp

	ld l,4(ix)
	ld h,5(ix)
	bcall #_PutS
	pop	ix
	ret

;	---------------------------------
; Function PutMap
; ---------------------------------
_CPutMap::
	push	ix
	ld	ix,#0
	add	ix,sp

	ld a,4(ix)
	bcall #_PutMap
	pop	ix
	ret

;	---------------------------------
; Function VPutS
; ---------------------------------
_CVPutS::
	push	ix
	ld	ix,#0
	add	ix,sp

	ld l,4(ix)
	ld h,5(ix)
	bcall #_VPutS

	pop	ix
	ret

;	---------------------------------
; Function GetKey
; ---------------------------------
_CGetKey::
	bcall #_getkey
	ld l,a
	ret

;	---------------------------------
; Function GetCSC
; ---------------------------------
_CGetCSC::
        bcall #_GetCSC
	ld l,a
	ret

;	---------------------------------
; Function TextInvertOn
; ---------------------------------
_CTextInvertOn::
	set 3,5(iy)
	ret

;	---------------------------------
; Function TextInvertOff
; ---------------------------------
_CTextInvertOff::
	res 3,5(iy)
	ret

;	---------------------------------
; Function LowerCaseOn
; ---------------------------------
_CLowerCaseOn::
	set 3,0x24(iy)
	ret

;	---------------------------------
; Function LowerCaseOff
; ---------------------------------
_CLowerCaseOff::
	res 3,0x24(iy)
	ret

;	---------------------------------
; Function RunIndicatorOn
; ---------------------------------
_CRunIndicatorOn::
	set 0,0x12(iy)
	ret

;	---------------------------------
; Function RunIndicatorOff
; ---------------------------------
_CRunIndicatorOff::
	res 0,0x12(iy)
	ret

;	---------------------------------
; Function EnableAPD
; ---------------------------------
_CEnableAPD::
        bcall #_EnableApd
	ret

;	---------------------------------
; Function DisableAPD
; ---------------------------------
_CDisableAPD::
	bcall #_DisableApd
	ret

;	---------------------------------
; Function Enable15MHz
; ---------------------------------
_CEnable15MHz::
	in a,(2)
	and #0x80
	ret z ; No CPU governor on this calc
	rlca
	out (#0x20),a
	ret

;	---------------------------------
; Function Disable15MHz
; ---------------------------------
_CDisable15MHz::
	ld a,#0
	out (#0x20),a
	ret
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
