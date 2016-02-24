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
 *al to (SCREEN_WIDTH*SCREEN_HEIGHT) / 8
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
/* prints i in the larget font */
void CPutInt(int i);

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
    unsigned char sign;
    unsigned char exponent;
    unsigned char significand[7];
} FloatingPoint;

/*
 * If a real floating point number is stored in the Ans variable,
 * returns a pointer to it.
 * Otherwise returns NULL.
 */
FloatingPoint *CGetAnsFP();
FloatingPoint *CGetVarFP(char var_name);

void CAddFP(FloatingPoint *add1, FloatingPoint *add2, FloatingPoint *sum);
void CSubFP(FloatingPoint *sub1, FloatingPoint *sub2, FloatingPoint *diff);
void CMultFP(FloatingPoint *fac1, FloatingPoint *fac2, FloatingPoint *prod);
void CDivFP(FloatingPoint *dividend, FloatingPoint *divisor,
                                            FloatingPoint *quot);

/*******GRAPHICS ROUTINES********/

/* picture variables don't record the bottom row of pixels */
#define PIC_SIZE_BYTES (96*63)/8

/*
 * Returns a pointer to the picture variable picNo, if it exists.
 * A picture is bitmap of PIC_SIZE bytes.
 * pic0 on the calculator corresponds to picNo = 10.
 * If the ested picture variable does not exist, returns NULL.
 */
unsigned char *CRecallPic(unsigned char picNo);

/*
 * Stores the data at pic in the picture variable picNo.
 * A picture is bitmap of PIC_SIZE bytes.
 * pic0 on the calculator corresponds to picNo = 10.
 * If the picture var exists, it is overwritten; if it does not, it is created.
 */
void CStorePic(unsigned char picNo, unsigned char *pic);

/*
 * Copies the contents of plotSScreen to the LCD.
 * Identical in behavior to GrBufCopy(), but faster.
 */
void FastCopy();


/* Everything from here on out is contants taken from ti83plus.inc */

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


#endif
