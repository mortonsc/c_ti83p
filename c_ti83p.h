#ifndef _TI_84_PLUS_INC_H_
#define _TI_84_PLUS_INC_H_ 1

/*
 * Copyright (c) 2016 Scott Morton
 * This is free software released under the MIT license.
 * For more information, see the LICENSE.txt file
 * which should be bundled with this source.
 */

/*
 * This is a collection of C wrappers for useful assembly routines
 * for TI-83+ series graphing calculators.
 *
 * All function names are prefixed with "C", so that the implementation can
 * distinguish between them and ROM calls that might have an identical name.
 */

/* special TI large font character codes */
#define L_RECUR_N    '\x01'
#define L_RECUR_U    '\x02'
#define L_RECUR_V    '\x03'
#define L_RECUR_W    '\x04'
#define L_CONVERT    '\x05'
#define L_SQ_UP      '\x06'
#define L_SQ_DOWN    '\x07'
#define L_INTEGRAL   '\x08'
#define L_CROSS      '\x09'
#define L_BOX_ICON   '\x0A'
#define L_CROSS_ICON '\x0B'
#define L_DOT_ICON   '\x0C'
#define L_SUB_T      '\x0D'
#define L_CUBE_R     '\x0E'
#define L_HEX_F      '\x0F'
#define L_ROOT       '\x10'
#define L_INVERSE    '\x11'
#define L_SQUARE     '\x12'
#define L_ANGLE      '\x13'
#define L_DEGREE     '\x14'
#define L_RADIAN     '\x15'
#define L_TRANSPOSE  '\x16'
#define L_L_EQ       '\x17'
#define L_N_EQ       '\x18'
#define L_G_EQ       '\x19'
#define L_NEG        '\x1A'
#define L_EXPONENT   '\x1B'
#define L_STORE      '\x1C'
#define L_TEN        '\x1D'
#define L_UP_ARROW   '\x1E'
#define L_DOWN_ARROW '\x1F'
#define L_FOURTH     '\x24'
#define L_PLUS_SIGN  '\x2B'
#define L_L_T        '\x3C'
#define L_EQ         '\x3D'
#define L_G_T        '\x3E'
#define L_THETA      '\x5B'
#define L_INV_EQ     '\x7F'

/* GetCSC keycodes */
#define skDown      0x01
#define skLeft      0x02
#define skRight     0x03
#define skUp        0x04
#define skEnter     0x09
#define skAdd       0x0A
#define skSub       0x0B
#define skMul       0x0C
#define skDiv       0x0D
#define skPower     0x0E
#define skClear     0x0F
#define skChs       0x11
#define sk3	        0x12
#define sk6	        0x13
#define sk9	        0x14
#define skRParen    0x15
#define skTan       0x16
#define skVars      0x17
#define skDecPnt    0x19
#define sk2         0x1A
#define sk5         0x1B
#define sk8         0x1C
#define skLParen    0x1D
#define skCos       0x1E
#define skPrgm      0x1F
#define skStat      0x20
#define sk0	        0x21
#define sk1	        0x22
#define sk4         0x23
#define sk7         0x24
#define skComma     0x25
#define skSin       0x26
#define skMatrix    0x27
#define skGraphvar  0x28
#define skStore     0x2A
#define skLn        0x2B
#define skLog       0x2C
#define skSquare    0x2D
#define skRecip     0x2E
#define skMat       0x2F
#define skAlpha     0x30
#define skGraph     0x31
#define skTrace     0x32
#define skZoo       0x33
#define skWindow    0x34
#define skYEqu      0x35
#define sk2nd       0x36
#define skMode      0x37
#define skDel       0x38

/*
 * These two variables specify the location where large text will be displayed.
 * Calling PutC or PutS will change their values.
 */
__at 0x844C unsigned char curCol;
__at 0x844B unsigned char curRow;

/*
 * These two variables specify the location where small text will be displayed.
 * Calling PutMap or VPutS will change their values.
 * Note that their values are measured in pixels, so if you want to go to
 * a new row of text, incrementing penRow will not be sufficient.
 */
__at 0x86D7 unsigned char penCol;
__at 0x86D8 unsigned char penRow;

/*
 * number of bytes in a buffer
 * equal to (SCREEN_WIDTH*SCREEN_HEIGHT) / 8
 */
#define BUFFER_SIZE 768

/* width of the screen, in pixels */
#define SCREEN_WIDTH 96
/* height of the screen, in pixels */
#define SCREEN_HEIGHT 64

/*
 * This area of RAM stores the current contents of the graph screen.
 * Each pixel is represented by a single bit: 1 for on, 0 for off.
 * Each row of the screen corresponds to 12 contiguous bytes.
 * The first bit represents the leftmost pixel of the top row.
 *
 * plotSScreen is useful as a buffer to modify the screen,
 * so that it can be updated all at once.
 */
__at 0x9340 unsigned char plotSScreen[BUFFER_SIZE];

/*
 * This block of RAM is unused by the calculator, so it's useful as backup
 * memory, or to store another version of the screen.
 */
__at 0x9872 unsigned char appBackUpScreen[BUFFER_SIZE];

/*
 * This block of RAM is only used by the calculator is automatic power down
 * is on. If you disable APD it can be used for more additional memory.
 */
__at 0x86EC unsigned char saveSScreen[BUFFER_SIZE];

/*
 * Updates the LCD to reflect the contents of plotSScreen.
 *
 * Note that there are asm programs available that will do this much faster;
 * one of them, fastcopy, is included with this library
 */
void CGrBufCpy();

/* clears the LCD */
void CClrLCDFull();

void CNewLine();

/* prints c in the large font */
void CPutC(char c);
/* prints s in the large font */
void CPutS(const char *s);

/* prints c in the small font */
void CPutMap(char c);
/* prints s in the small font */
void CVPutS(const char *s);

/* waits for the user to press a key, then returns the keycode */
unsigned char CGetKey();

/*
 * if the user is currently pressing a key, returns its keycode
 * note that this function uses different codes than GetKey()
 */
unsigned char CGetCSC();

/*
 * Any text printed after TextInvertOn is called will appear inverted
 * (white on black), until TextInvertOff is called.
 */
void CTextInvertOn();
void CTextInvertOff();

/*
 * While LowerCase mode is on, the user can enter lowercase characters by
 * pressing [Alpha] twice.
 * Note that LowerCase does *not* need to be on in order to print lowercase
 * letters using functions like PutC. It only affects the user's ability
 * to input lowercase letters.
 */
void CLowerCaseOn();
void CLowerCaseOff();

/*
 * Turn the run indicator on or off. The run indicator is the little animation
 * in the upper right corner that plays while the calculator is performing
 * calculations or waiting for input.
 */
void CRunIndicatorOn();
void CRunIndicatorOff();

/*
 * Enable/disable automatic power down (APD). This is mainly useful because
 * saveSScreen is only usable for memory if APD is disabled.
 * ALWAYS remember to turn APD back on before the program terminates.
 */
void CEnableAPD();
void CDisableAPD();

/*
 * Enable/disable running the CPU at 15MHz. (It defaults to 6MHz.)
 * The TI83+ is not capable of running at 15MHz, so these functions do nothing.
 */
void CEnable15MHz();
void CDisable15MHz();

/*
 * Copies the contents of plotSScreen to the LCD.
 * Identical in behavior to GrBufCopy(), but faster.
 */
void FastCopy();

#endif
