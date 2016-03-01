/*
 * This is a collection of C wrappers for useful assembly routines
 * for TI-83+ series graphing calculators.
 *
 * Most function names are prefixed with "C", so that the implementation can
 * distinguish between them and ROM calls that might have an identical name.
 *
 * This header file contains declarations for all functions included
 * in the library, along with #defines for special characters, keycodes,
 * and calculator tokens. It also contains variables that let you access
 * certain useful locations in RAM.
 *
 * In order to use the functions in this header, you require the compiled
 * c_ti83p.lib file. This header should have come bundled either with it
 * or with the source files necessary to generate it.
 *
 * Copyright (C) 2016 Scott Morton  (mortonsc@umich.edu)
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, if you link this library in unmodified form with
 * other files to produce an executable, this library does not by itself cause
 * the resulting executable to be covered by the GNU General Public License.
 * This exception does not however invalidate any other reasons why
 * the executable file might be covered by the GNU General Public License.
 */

#ifndef _TI_84_PLUS_INC_H_
#define _TI_84_PLUS_INC_H_ 1

#include <stdint.h>

/*
 * These two variables specify the location where large text will be displayed.
 * Calling PutC or PutS will change their values.
 */
__at 0x844C uint8_t curCol;
__at 0x844B uint8_t curRow;

/*
 * These two variables specify the location where small text will be displayed.
 * Calling PutMap or VPutS will change their values.
 * Note that their values are measured in pixels, so if you want to go to
 * a new row of text, incrementing penRow will not be sufficient.
 */
__at 0x86D7 uint8_t penCol;
__at 0x86D8 uint8_t penRow;

/* width of the screen, in pixels */
#define SCREEN_WIDTH 96
/* height of the screen, in pixels */
#define SCREEN_HEIGHT 64

/*
 * number of bytes in a buffer (one byte per eight pixels)
 */
#define BUFFER_SIZE 768


/*
 * plotSScreen stores the current contents of the graph screen.
 * Each pixel is represented by a single bit: 1 for on, 0 for off.
 * Each row of the screen corresponds to 12 contiguous bytes.
 * The first bit represents the leftmost pixel of the top row.
 * plotSScreen is useful as a buffer to modify the screen,
 * so that it can be updated all at once.
 */
__at 0x9340 uint8_t plotSScreen[BUFFER_SIZE];


/*
 * Regions of RAM safe for program usage.
 *
 * To have a variable stored in one of these regions,
 * specify it using __at, for example:
 * __at APP_BACKUP_SCREEN int16_t num;
 * __at SAVE_S_SCREEN uint8_t arr2d[4][7];
 */

/*
 * appBackUpScreen is reserved by the calculator for use by user programs,
 * so it's a good place if you need extra memory, or to store another version
 * of the screen.
 *
 * appBackUpScreen contains 768 bytes (=BUFFER_SIZE).
 */
#define APP_BACKUP_SCREEN 0x9872

/*
 * saveSSCreen is only used by the calculator if automatic power down
 * is on. If you disable APD it can be used for more additional memory.
 *
 * saveSScreen contains 768 bytes (=BUFFER_SIZE).
 */
#define SAVE_S_SCREEN 0x86EC

/*
 * statVars is used by the calculator only for statistics computations.
 * It contains 531 bytes.
 */
#define STAT_VARS 0x8A3A


/**********System Routines**********/

/*
 * Updates the LCD to reflect the contents of plotSScreen.
 *
 * Note that there are asm programs available that will do this much faster;
 * one of them, fastcopy, is included with this library
 */
void CGrBufCpy();

/* clears the LCD */
void CClrLCDFull();

/* Moves text position to the next line of the screen */
void CNewLine();

/* prints c in the large font */
void CPutC(uint8_t c);
/* prints s in the large font */
void CPutS(const uint8_t *s);
/* prints i in the large font */
void CPutInt(uint16_t i);

/* prints c in the small font */
void CPutMap(uint8_t c);
/* prints s in the small font */
void CVPutS(const uint8_t *s);

/* waits for the user to press a key, then returns the keycode */
uint8_t CGetKey();

/*
 * if the user is currently pressing a key, returns its keycode
 * note that this function uses different codes than GetKey()
 */
uint8_t CGetCSC();

/*
 * Any text printed after TextInvertOn is called will appear inverted
 * (white on black), until TextInvertOff is called.
 */
void CTextInvertOn();
void CTextInvertOff();

/*
 * Any text printed after CTextWriteOn is called will be drawn to the buffer
 * instead of the LCD, until CTextWriteOff is called.
 */
void CTextWriteOn();
void CTextWriteOff();

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
 * Only has an effect on calculators newer than the TI-83+.
 */
void CEnable15MHz();
void CDisable15MHz();

/*******FLOATING POINT OPERATIONS****/

/*
 * A floating point number, as represented by the calculator.
 * Generally you will not want to touch the internals of the struct directly.
 */
typedef struct {
    uint8_t sign;
    uint8_t exponent;
    uint8_t significand[7];
} FloatingPoint;

/*
 * If a real floating point number is stored in the Ans variable,
 * returns a pointer to it.
 * Otherwise returns NULL.
 */
FloatingPoint *CGetAnsFP();

/*
 * If the variable with the given name exists, returns a pointer to it.
 * Otherwise returns NULL.
 * Valid variable names are capital letters 'A' - 'Z' and L_THETA.
 */
FloatingPoint *CGetVarFP(uint8_t var_name);

/*
 * Returns a pointer to the variable with the given name.
 * If it does not exist, it is created.
 * If it does exist, its value is not necessarily preserved.
 */
FloatingPoint *CMakeVarFP(uint8_t var_name);

/*
 * Adds the contents of add1 to add2 and stores the result in sum.
 * Any or all the arguments may be identical.
 */
void CAddFP(FloatingPoint *add1, FloatingPoint *add2, FloatingPoint *sum);

/*
 * Subtracts the contents of sub2 from sub1 and stores the result in diff.
 * Any of all the arguments may be identical.
 */
void CSubFP(FloatingPoint *sub1, FloatingPoint *sub2, FloatingPoint *diff);

/*
 * Multiplies the contents of fac1 by fac2 and stores the result in prod.
 * Any or all the arguments may be identical.
 */
void CMultFP(FloatingPoint *fac1, FloatingPoint *fac2, FloatingPoint *prod);

/*
 * Divides the contents of dividend by divisor and stores the result in quot.
 * Any or all of the arguments may be identical.
 * The divisor must not be 0.
 */
void CDivFP(FloatingPoint *dividend, FloatingPoint *divisor,
                                            FloatingPoint *quot);
/*
 * Converts fp to an integer. If the exponent of fp is greater than 3,
 * returns INT16_MAX.
 */
int16_t CFPToInt(FloatingPoint *fp);

/********Picture Variables********/

/* picture variables don't record the bottom row of pixels */
#define PIC_SIZE_BYTES (96*63)/8


/*
 * Returns a pointer to the picture variable picNo, if it exists.
 * If it is archived, unarchives it.
 * A picture is bitmap of PIC_SIZE bytes.
 * pic0 on the calculator corresponds to picNo = 10.
 * If the requested picture variable does not exist, returns NULL.
 */
uint8_t *CRecallPic(uint8_t picNo);

/*
 * Creates the given Picture variable and returns a pointer to it.
 * If the picture var already exists, it is overwritten, even if
 * it is archived; if it does not, it is created.
 * If there is not enough space in memory to produce the new picture,
 * returns NULL.
 * The contents of the newly created picture are undefined.
 */
uint8_t *CCreatePic(uint8_t picNo);

/*
 * If Picture variable picNo exists and is not archived, archives it.
 * Otherwise has no effect.
 * Renders any pointers to this Pic invalid.
 */
void CArchivePic(uint8_t picNo);

/*
 * If Picture variable picNo exists, deletes it, even if it is archived.
 * Otherwise has no effect.
 * Any previously obtained pointers to this pic are rendered invalid,
 * and remain so even if it is subsequently recreated.
 */
void CDeletePic(uint8_t picNo);


/**********Graphics Routines************/

/*
 * Struct representing a sprite that can be printed with PutSprite.
 * It always has a width of 8 pixels.
 * contents is an array containing the image, represented as a bitmap.
 */
typedef struct {
    uint8_t height; /* in pixels */
    const uint8_t *contents; /* pointer to array of length height */
} Sprite;

/*
 * Struct representing a sprite that can be printed with PutLargeSprite.
 * Identical to a Sprite, except it may have arbitrary width.
 */
typedef struct {
    uint8_t height; /* in pixels */
    uint8_t width; /* in bytes, so width of 2 corresponds to 16 pixels*/
    const uint8_t *contents; /* pointer to array of length height*width */
} LargeSprite;

/*
 * Copies the contents of plotSScreen to the LCD.
 * Identical in behavior to GrBufCopy(), but faster.
 */
void FastCopy();

/*
 * Copies sprite to plotSScreen with the upper-left corner at position x,y.
 * The sprite is XOR'd with the current contents of plotSScreen.
 * Requires that there is enough space in the buffer to fit the whole sprite;
 * that is, this function does not "clip" sprites.
 */
void PutSprite(uint8_t x, uint8_t y, const Sprite *sprite);

/*
 * Copies sprite to plotSScreen with the upper-left corner at position x,y.
 * The sprite is XOR'd with the current contents of plotSScreen.
 * Requires that there is enough space in the buffer to fit the whole sprite;
 * that is, this function does not "clip" sprites.
 */
void PutLargeSprite(uint8_t x, uint8_t y, const LargeSprite *sprite);

/********AppVar Routines********/

/*
 * If an AppVar with the given name exists, returns a pointer to its
 * first byte of data and stores its size (in bytes) in *size.
 * Otherwise returns NULL.
 * If the AppVar exists but is archived, it is unarchived.
 */
void *CRecallAppVar(const uint8_t *name, uint16_t *size);

/*
 * Creates a new AppVar with the given name and size, and returns a pointer
 * to its first byte of data. If an AppVar with the same name already exists,
 * it is deleted, including if it is archived.
 * The contents of the newly created AppVar are undefined.
 * If there is not enough memory to create the AppVar, returns NULL.
 *
 * Any pointers that previously pointed to an AppVar of this name
 * (obtained by RecallAppVar(), for example) are no longer valid
 * after a call to this function.
 */
void *CCreateAppVar(const uint8_t *name, uint16_t size);

/*
 * If an AppVar with the given name exists and is not archived,
 * archives it. Otherwise does nothing.
 */
void CArchiveAppVar(const uint8_t *name);

/*
 * If an AppVar with the given name exists, deletes it, even if it is archived.
 * Any pointers to an AppVar of this name become invalid, and remain so even
 * if it is subsequently recreated.
 */
void CDeleteAppVar(const uint8_t *name);

/*******Program Variables********/


/*
 * If a program with the given name exists, returns a pointer to its contents
 * and stores its size in size. Otherwise returns NULL.
 * If the program is archived, unarchives it.
 */
uint8_t *CRecallPrgm(const uint8_t *name, uint16_t *size);

/*
 * Creates a new program of the given name and size, and returns a pointer
 * to its contents. If a program already exists with the same name, it is
 * deleted, even if it is archived.
 * If there is not enough memory to create the new program, returns NULL.
 *
 * This function should be used if you intend to create a TI-Basic program
 * editable by the user; if you want to create an assembly/machine code
 * program, use CCreateProtPrgm to prevent the user from editing it.
 */
uint8_t *CCreatePrgm(const uint8_t *name, uint16_t size);

/*
 * Same as CCreatePrgm, except the created program cannot be modified by the
 * user. Always use this for programs containing machine code.
 */
uint8_t *CCreateProtPrgm(const uint8_t *name, uint16_t size);

/*
 * If a program with the given name exists, archives it.
 * Otherwise does nothing.
 */
void CArchivePrgm(const uint8_t *name);

/*
 * If a program with the given name exists, deletes it, even if it is archived.
 * Otherwise has no effect.
 */
void CDeletePrgm(const uint8_t *name);

/***********Random Numbers***************/

/*
 * Returns a pseudo-random integer, 0 <= n < max.
 */
uint8_t CRandInt(uint8_t max);

/**********Time*******/

/*
 * Struct to hold a time, used by CGetTime.
 */
typedef struct {
        uint8_t seconds;
        uint8_t minutes;
        uint8_t hours;
} Time;

/*
 * Stores the current time, according to the calculator's clock, in time.
 * Hours are always given in the 24hr format, so 3p.m. is represented as 15.
 *
 * This function is not available on the basic TI-83+.
 */
void CGetTime(Time *time);

/*
 * Waits for the given number of seconds.
 * The maximum allowable value for secs is 31; if a larger value is given,
 * the function will return instantly.
 *
 * This function is not available on the basic TI-83+.
 */
void CWaitSecs(uint8_t secs);

/*
 * Waits for the given number of centiseconds.
 * (A centisecond is 1/100 of a second.)
 *
 * This function is not available on the basic TI-83+.
 */
void CWaitCentis(uint8_t centis);

/*
 * Waits for the given number of milliseconds.
 * (A millisecond is 1/1000 of a second.)
 *
 * This function is not available on the basic TI-83+.
 */
void CWaitMillis(uint8_t millis);


/* Everything from here on out is contants taken from ti83plus.inc */

/*
 * these two tokens have to appear at the beginning of any
 * compiled assembly program for it to run
 */
#define t2ByteTok   0xBB
#define tasmCmp    0x6D

#define tAdd 0x70
#define tSub 0x71
#define tLT 0x6B
#define tGT 0x6C
#define tLBrack 0x06
#define tRBrack 0x07
#define tLBrace 0x08
#define tRBrace 0x09
#define tDecPt 0x3A
#define tComma  0x2B

/* special TI large font character codes   */
/* other characters are identical to ASCII */
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


/* CGetKey keycodes */
#define kRight			 0x001
#define kLeft			 0x002
#define kUp			 0x003
#define kDown			 0x004
#define kEnter			 0x005
#define kAlphaEnter		 0x006
#define kAlphaUp		 0x007
#define kAlphaDown		 0x008
#define kClear			 0x009
#define kDel			 0x00A
#define kIns			 0x00B
#define kRecall			 0x00C
#define kLastEnt		 0x00D
#define kBOL			 0x00E
#define kEOL			 0x00F
#define kSelAll			 0x010
#define kUnselAll		 0x011
#define kLtoTI82		 0x012
#define kBackup			 0x013
#define kRecieve		 0x014
#define kLnkQuit		 0x015
#define kTrans			 0x016
#define kRename			 0x017
#define kOverw			 0x018
#define kOmit			 0x019
#define kCont			 0x01A
#define kSendID			 0x01B
#define kSendSW			 0x01C
#define kYes			 0x01D
#define kNoWay			 0x01E
#define kvSendType		 0x01F
#define kOverWAll		 0x020
#define kNo			 0x025
#define kKReset			 0x026
#define kApp			 0x027
#define kDoug			 0x028
#define kListflag		 0x029
#define menuStart		 0x02B
#define kAreYouSure		 0x02B
#define kAppsMenu		 0x02C
#define kPrgm			 0x02D
#define kZoom			 0x02E
#define kDraw			 0x02F
#define kSPlot			 0x030
#define kStat			 0x031
#define kMath			 0x032
#define kTest			 0x033
#define kChar			 0x034
#define kVars			 0x035
#define kMem			 0x036
#define kMatrix			 0x037
#define kDist			 0x038
#define kAngle			 0x039
#define kList			 0x03A
#define kCalc			 0x03B
#define kFin			 0x03C
#define menuEnd			 kFin
#define kCatalog		 0x03E
#define kInputDone		 0x03F
#define kOff			 kInputDone
#define kQuit			 0x040
#define appStart		 kQuit
#define kLinkIO			 0x041
#define kMatrixEd		 0x042
#define kStatEd			 0x043
#define kGraph			 0x044
#define kMode			 0x045
#define kPrgmEd			 0x046 /*PROGRAM EDIT*/
#define kPrgmCr			 0x047 /*PROGRAM CREATE*/
#define kWindow			 0x048 /*RANGE EDITOR*/
#define k			     0x049 /*EQUATION EDITOR*/
#define kTable			 0x04A /*TABLE EDITOR*/
#define kTblSet			 0x04B /*TABLE SET*/
#define kChkRAM			 0x04C /*CHECK RAM*/
#define kDelMem			 0x04D /*DELETE MEM*/
#define kResetMem		 0x04E /*RESET MEM*/
#define kResetDef		 0x04F /*RESET DEFAULT*/
#define kPrgmInput		 0x050 /*PROGRAM INPUT*/
#define kZFactEd		 0x051 /*ZOOM FACTOR EDITOR*/
#define kError			 0x052 /*ERROR*/
#define kSolveTVM		 0x053 /*TVM SOLVER*/
#define kSolveRoot		 0x054 /*SOLVE EDITOR*/
#define kStatP			 0x055 /*stat plot*/
#define kInfStat		 0x056 /*Inferential Statistic*/
#define kFormat			 0x057 /*FORMAT*/
#define kExtApps		 0x058 /*External Applications.     NEW*/
#define kNewApps		 0x059 /*New Apps for Cerberus.*/
#define append			 kNewApps
#define echoStart1		 0x05A
#define kTrace			 0x05A
#define kZFit			 0x05B
#define kZIn			 0x05C
#define kZOut			 0x05D
#define kZPrev			 0x05E
#define kBox			 0x05F
#define kDecml			 0x060
#define kSetZm			 0x061
#define kSquar			 0x062
#define kStd			 0x063
#define kTrig			 0x064
#define kUsrZm			 0x065
#define kZSto			 0x066
#define kZInt			 0x067
#define kZStat			 0x068
#define echoStart2		 0x069
#define kSelect			 0x069
#define kCircl			 0x06A
#define kClDrw			 0x06B
#define kLine			 0x06C
#define kPen			 0x06D
#define kPtChg			 0x06E
#define kPtOff			 0x06F
#define kPtOn			 0x070
#define kVert			 0x071
#define kHoriz			 0x072
#define kText			 0x073
#define kTanLn			 0x074
#define kEval			 0x075
#define kInters			 0x076
#define kDYDX			 0x077
#define kFnIntg			 0x078
#define kRootG			 0x079
#define kDYDT			 0x07A
#define kDXDT			 0x07B
#define kDRDo			 0x07C
#define KGFMin			 0x07D
#define KGFMax			 0x07E
#define EchoStart		 0x07F
#define kListName		 0x07F
#define kAdd			 0x080
#define kSub			 0x081
#define kMul			 0x082
#define kDiv			 0x083
#define kExpon			 0x084
#define kLParen			 0x085
#define kRParen			 0x086
#define kLBrack			 0x087
#define kRBrack			 0x088
#define kShade			 0x089
#define kStore			 0x08A
#define kComma			 0x08B
#define kChs			 0x08C
#define kDecPnt			 0x08D
#define k0			 0x08E
#define k1			 0x08F
#define k2			 0x090
#define k3			 0x091
#define k4			 0x092
#define k5			 0x093
#define k6			 0x094
#define k7			 0x095
#define k8			 0x096
#define k9			 0x097
#define kEE			 0x098
#define kSpace			 0x099
#define kCapA			 0x09A
#define kCapB			 0x09B
#define kCapC			 0x09C
#define kCapD			 0x09D
#define kCapE			 0x09E
#define kCapF			 0x09F
#define kCapG			 0x0A0
#define kCapH			 0x0A1
#define kCapI			 0x0A2
#define kCapJ			 0x0A3
#define kCapK			 0x0A4
#define kCapL			 0x0A5
#define kCapM			 0x0A6
#define kCapN			 0x0A7
#define kCapO			 0x0A8
#define kCapP			 0x0A9
#define kCapQ			 0x0AA
#define kCapR			 0x0AB
#define kCapS			 0x0AC
#define kCapT			 0x0AD
#define kCapU			 0x0AE
#define kCapV			 0x0AF
#define kCapW			 0x0B0
#define kCapX			 0x0B1
#define kCapY			 0x0B2
#define kCapZ			 0x0B3
#define kVarx			 0x0B4
#define kPi			 0x0B5
#define kInv			 0x0B6
#define kSin			 0x0B7
#define kASin			 0x0B8
#define kCos			 0x0B9
#define kACos			 0x0BA
#define kTan			 0x0BB
#define kATan			 0x0BC
#define kSquare			 0x0BD
#define kSqrt			 0x0BE
#define kLn			 0x0BF
#define kExp			 0x0C0
#define kLog			 0x0C1
#define kALog			 0x0C2
#define kToABC			 0x0C3
#define kClrTbl			 0x0C4
#define kAns			 0x0C5
#define kColon			 0x0C6
#define kNDeriv			 0x0C7
#define kFnInt			 0x0C8
#define kRoot			 0x0C9
#define kQuest			 0x0CA
#define kQuote			 0x0CB
#define kTheta			 0x0CC
#define kIf			 0x0CD
#define kThen			 0x0CE
#define kElse			 0x0CF
#define kFor			 0x0D0
#define kWhile			 0x0D1
#define kRepeat			 0x0D2
#define kEnd			 0x0D3
#define kPause			 0x0D4
#define kLbl			 0x0D5
#define kGoto			 0x0D6
#define kISG			 0x0D7
#define kDSL			 0x0D8
#define kMenu			 0x0D9
#define kExec			 0x0DA
#define kReturn			 0x0DB
#define kStop			 0x0DC
#define kInput			 0x0DD
#define kPrompt			 0x0DE
#define kDisp			 0x0DF
#define kDispG			 0x0E0
#define kDispT			 0x0E1
#define kOutput			 0x0E2
#define kGetKey			 0x0E3
#define kClrHome		 0x0E4
#define kPrtScr			 0x0E5
#define kSinH			 0x0E6
#define kCosH			 0x0E7
#define kTanH			 0x0E8
#define kASinH			 0x0E9
#define kACosH			 0x0EA
#define kATanH			 0x0EB
#define kLBrace			 0x0EC
#define kRBrace			 0x0ED
#define kI			 0x0EE
#define kCONSTeA		 0x0EF
#define kPlot3			 0x0F0
#define kFMin			 0x0F1
#define kFMax			 0x0F2
#define kL1A			 0x0F3
#define kL2A			 0x0F4
#define kL3A			 0x0F5
#define kL4A			 0x0F6
#define kL5A			 0x0F7
#define kL6A			 0x0F8
#define kunA			 0x0F9
#define kvnA			 0x0FA
#define kwnA			 0x0FB


#endif /* _TI_84_PLUS_INC_H_ */
