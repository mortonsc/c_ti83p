#ifndef _TI_84_PLUS_INC_H_
#define _TI_84_PLUS_INC_H_ 1

/* special TI font character codes */
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

__at 0x844C unsigned char curCol;
__at 0x844B unsigned char curRow;

__at 0x86D7 unsigned char penCol;
__at 0x86D8 unsigned char penRow;

/* number of bytes in a buffer */
/* equal to (SCREEN_WIDTH * SCREEN_HEIGHT) / 8 */
#define BUFFER_SIZE 768
/* width of the screen, in pixels */
#define SCREEN_WIDTH 96
/* height of the screen, in pixels */
#define SCREEN_HEIGHT 64

__at 0x9340 unsigned char plotSScreen[BUFFER_SIZE];
__at 0x9872 unsigned char appBackUpScreen[BUFFER_SIZE];
__at 0x86EC unsigned char saveSScreen[BUFFER_SIZE];

void GrBufCpy() __naked;

void ClrLCDFull() __naked;
void NewLine() __naked;

void PutC(char c);
void PutS(const char *s);

void PutMap(char c);
void VPutS(const char *s);

unsigned char GetKey() __naked;

void TextInvertOn() __naked;
void TextInvertOff() __naked;

void LowerCaseOn() __naked;
void LowerCaseOff() __naked;

void EnableAPD() __naked;
void DisableAPD() __naked;

#endif
