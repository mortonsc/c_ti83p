;; This routine is taken from WikiTI
;; (http://wikiti.brandonw.net/index.php?title=Z80_Routines:Graphic:Fastcopy#Double-buffered_copy)
;; retrieved 21 Feb 2016
;; I modified it slightly in order to make it SDCC compatible,
;; and to always read/write from the same buffers.
;; I claim no copyright over this code.

;-------------------------------------------------------------------------------
;
; === DoubleBufferFlip ===
;
;  Sends data to the LCD driver by comparing the new frame (DE) with the
;  old one (HL) and only sending the bytes which have been altered.
;
;  The front-buffer (HL) is updated to keep in-sync with the back-buffer (DE).
;
; INPUTS:
;
;  REGISTERS
;  * HL - Address of front-buffer (holding current contents of the display).
;  * DE - Address of back-buffer (holding new contents of the display).
;
; OUTPUTS:
;
;  MEMORY
;  * (HL) - Synchronised with (DE)
;
;
; DESTROYED:
;
;  REGISTERS
;  * AF, BC
;
;-------------------------------------------------------------------------------
        .globl _DoubleBufferFlip

        .area DATA

_plotSScreen     = 0x9340
_appBackUpScreen = 0x9872

        .area OSEG

_DoubleBufferFlip:

        ;; MODIFIED: set src to appBackUpScreen, dst to plotSScreen
        ld      hl,#_plotSScreen
        ld      de,#_appBackUpScreen
        ;-------------------------------------------------------------------
        ; We will be writing to the LCD in Y auto-decrement mode, so
        ; set the mode first and then add 767 to the buffer addresses,
        ; since we will be reading them backwards.
        ;-------------------------------------------------------------------
        ld      c, #0x10              ; [7] command port number.
        ld      a, #0x06              ; [7]
        ;in      f, (c)              ; [12] wait on LCD.
        ;jp      m, #0x-2              ; [10]
        inc     a                   ; waste time waiting for LCD
        dec     a
        out     (#0x10), a            ; [11] set y auto-decrement
        ld      bc, #767             ; [10]
        add     hl, bc              ; [11]
        ex      de, hl              ; [4] front-buffer <-> back-buffer
        add     hl, bc              ; [11]
        ex      de, hl              ; [4] back-buffer <-> front-buffer

        ;-------------------------------------------------------------------
        ; The accumulator will be used to hold the current row command
        ; which will be sent to the LCD at the beginning of each line.
        ; This value will be kept on the stack through most of the code
        ; since we only need it every now and then. C will contain the
        ; LCD command port ($10) for the entire routine.
        ;-------------------------------------------------------------------
        ld      a, #0xbf              ; [7] row command counter.
        ld      c, #0x10              ; [7] command port number.

        ;-------------------------------------------------------------------
        ; This is the beginning of the outer loop which we come into at
        ; the start of each line. We load B with 12 to serve as a column
        ; counter. This is why we go backwards - so we can use DJNZ in
        ; the inner loop and then offset B to get the set-column command
        ; when we need it. At this point we also output the row command
        ; before pushing AF.
        ;-------------------------------------------------------------------
_nextLine:
        ld      b, #0x0c              ; [7] reset column counter.
        ;in      f, (c)              ; [12] wait on LCD.
        ;jp      m, #0x-2              ; [10]
        inc     a                   ; waste time waiting for LCD
        dec     a
        out     (c), a              ; [12] output set row command.
        push    af                  ; [11]

        ;-------------------------------------------------------------------
        ; This is where we compare two buffer bytes to see if we need
        ; to write anything. If we don't, we keep looping until we do or
        ; we reach the end of the line.
        ;-------------------------------------------------------------------
_testByte:
        ld      a, (de)             ; [7] load new byte
        cp      (hl)                ; [7] compare existing
        jr      nz, _putByte        ; [12/7]
        dec     de                  ; [6]
        dec     hl                  ; [6]
        djnz    _testByte           ; [13/8]

        ;-------------------------------------------------------------------
        ; This is the tail of the outer loop (the row loop). We pop
        ; the row counter and see if there are any more lines left to
        ; process. If there aren't we play nice with TI-OS and reset
        ; x auto-increment mode before returning. We also reset HL and
        ; DE to their input values.
        ;-------------------------------------------------------------------
_loopTail:
        pop     af                  ; [10]
        dec     a                   ; [4]
        jp      m, _nextLine        ; [10]
        ;in      f, (c)              ; [12]
        ;jp      m, #0x-2              ; [10]
        inc     a                   ; waste time waiting for LCD
        dec     a
        ld      a, #0x05              ; [7] reset x auto-increment
        out     (c), a              ; [11]
        inc     hl                  ; [6]
        inc     de                  ; [6]
        ret                         ; [10]

        ;-------------------------------------------------------------------
        ; We come here when a difference has been found between a byte in
        ; the front and back buffers. We offset B (the column counter)
        ; to get the column command and then send it to the LCD.
        ;-------------------------------------------------------------------
_putByte:
        ld      a, #0x1f              ; [7]
        add     a, b                ; [4]
        ;in      f, (c)              ; [12]
        ;jp      m, #0x-2              ; [10]
        inc     a                   ; waste time waiting for LCD
        dec     a
        out     (c), a              ; [12] set column

        ;-------------------------------------------------------------------
        ; Here we update the front buffer, load the byte to send to the
        ; LCD, wait for the LCD to become ready, and then send it.
        ;-------------------------------------------------------------------
_streamPut:
        ld      a, (de)             ; [7] load byte to send.
        ld      (hl), a             ; [7] update front-buffer.
        dec     de                  ; [6]
        dec     hl                  ; [6]
        ;in      f, (c)              ; [12] wait on LCD.
        ;jp      m, #0x-2              ; [10]
        inc     a                   ; waste time waiting for LCD
        dec     a
        out     (#0x11), a            ; [11]
        djnz    _streamChk          ; [13/8]
        jp      _loopTail           ; [10]

        ;-------------------------------------------------------------------
        ; Finally, we get here when we have just sent a byte to the LCD
        ; and there are still more bytes left in this line. Rather than
        ; going back to the inner loop, we check to see if the next byte
        ; also needs to be sent. Doing this saves us the need to output
        ; the column command between consecutive writes.
        ;-------------------------------------------------------------------
_streamChk:
        ld      a, (de)             ; [7]
        cp      (hl)                ; [7]
        jp      nz, _streamPut + 1  ; [10]
        dec     de                  ; [6]
        dec     hl                  ; [6]
        djnz    _testByte           ; [13/8]
        jp      _loopTail           ; [10]
