; crt0-ti84.s - TIOS assembly program header
        .module crt0
        .globl _main  

        .area _HEADER (ABS)  

        .org #0x9D93
        .dw #0x6DBB
        call gsinit  
        jp _main  

        .org 0x9D9B

        .area _HOME  
        .area _CODE  
        .area _GSINIT  
        .area _GSFINAL  
        .area _DATA  
        .area _BSEG  
        .area _BSS  
        .area _HEAP  
        .area _CODE  

__clock::  
        ld a,#2  
        ret ; needed somewhere...  

        .area _GSINIT  
gsinit::  
        .area _GSFINAL  
        ret
