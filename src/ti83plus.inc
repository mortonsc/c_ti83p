;-----------------------------------------------------------------------------
; TI-83 Plus Include File by Brandon Wilson
;-----------------------------------------------------------------------------
; 06/27/2005
;-----------------------------------------------------------------------------
; This TI-83 Plus include file includes all known page 0x1B and page 0x1F ROM
;  calls as well as flag, keyboard, and character equates.
;-----------------------------------------------------------------------------
; Modified 02/23/2016 by Scott Morton to be compatible with asz80,
;-----------------------------------------------------------------------------

;System Variable Equates
;------------------------------
XSCLt			.equ 2
YSCLt			.equ 3
XMINt			.equ 0x0A
XMAXt			.equ 0x0B
YMINt			.equ 0x0C
YMAXt			.equ 0x0D
TMINt			.equ 0x0E
TMAXt			.equ 0x0F
THETMINt		.equ 0x10
THETMAXt		.equ 0x11
TBLMINt			.equ 0x1A
PLOTSTARTt		.equ 0x1B
NMAXt			.equ 0x1D
NMINt			.equ 0x1F
TBLSTEPt		.equ 0x21
TSTEPt			.equ 0x22
THETSTEPt		.equ 0x23
DELTAXt			.equ 0x26
DELTAYt			.equ 0x27
XFACTt			.equ 0x28
YFACTt			.equ 0x29
FINNt			.equ 0x2B
FINIt			.equ 0x2C
FINPVt			.equ 0x2D
FINPMTt			.equ 0x2E
FINFVt			.equ 0x2F
FINPYt			.equ 0x30
FINCYt			.equ 0x31
PLOTSTEPt		.equ 0x34
XRESt			.equ 0x36

;Run indicators
;------------------------------------
busyPause		.equ 0b10101010
busyNormal		.equ 0b11110000

;Banked Call Equates/Macros
;-----------------------------------------------
rBR_CALL		.equ 0x28	;NEEDED FOR APPS
BRT_JUMP0		.equ 0x50

.macro  bcall   xxxx
        rst #0x28
        .dw xxxx
.endm

.macro  bjump   xxxx
        call #0x50
        .dw xxxx
.endm

;Common Restart Routines
;------------------------------
rOP1TOOP2		.equ 0x08
rFINDSYM		.equ 0x10
rPUSHREALO1		.equ 0x18
rMOV9TOOP1		.equ 0x20
rFPADD			.equ 0x30

;Error Handler Equates/Macros
;-------------------------------------------
APP_PUSH_ERRORH		.equ 0x59
APP_POP_ERRORH		.equ 0x5C

.macro  AppOnErr xxxx
        ld hl,#xxxx
        call #0x59
.endm

.macro  AppOffErr
        call #0x5C
.endm

;Page 0x1B ROM Calls
;--------------------------------
_JErrorNo		.equ 0x4000
_FontHook		.equ 0x4003
_call_character_hook	.equ 0x4006 ;calls character(localize) hook
_ldHLind		.equ 0x4009 ;l=a=(hl),h=(hl+1)
_CpHLDE			.equ 0x400C
_DivHLBy10		.equ 0x400F
_DivHLByA		.equ 0x4012
_kdbScan		.equ 0x4015
_GetCSC			.equ 0x4018 ;key board scan codes
_coorMon		.equ 0x401B ;
_Mon			.equ 0x401E ;system monitor, customized through the context vectors
_monForceKey		.equ 0x4021 ;
_sendKPress		.equ 0x4024
_JForceCmdNoChar	.equ 0x4027
_JForceCmd		.equ 0x402A ;
_sysErrHandler		.equ 0x402D ;loads error context? sp=(onSP)
_newContext		.equ 0x4030 ;(kbdKey)=0, loads context, restores page in 0x4000-0x7fff
_newContext0		.equ 0x4033 ;loads context
_cxPutAway		.equ 0x4036 ;
_cxPutAway2		.equ 0x4039 ;same but also does a B_CALL CanAlphIns
_cxPPutAway		.equ 0x403C
_cxSizeWind		.equ 0x403F
_cxErrEP		.equ 0x4042
_cxMain			.equ 0x4045
_monErrHand		.equ 0x4048 ;installs errorhandler to start of ROM call, loads error context, jumps to mon
_AppInit		.equ 0x404B ;loads vector data at hl to cxMain and the rest of the vectors
_resetRam		.equ 0x404E
_lcd_busy		.equ 0x4051 ;wait till bit 1 of port 2 is set
_Min			.equ 0x4054 ;op1 = lowest number between op1 and op2
_Max			.equ 0x4057 ;op1 = highest number between op1 and op2
_Trunc			.equ 0x4060
_InvSub			.equ 0x4063
_Times2			.equ 0x4066
_Plus1			.equ 0x4069 ;op1=op1+1
_Minus1			.equ 0x406C
_FPSub			.equ 0x406F
_FPAdd			.equ 0x4072
_DToR			.equ 0x4075
_RToD			.equ 0x4078
_Cube			.equ 0x407B
_TimesPt5		.equ 0x407E
_FPSquare		.equ 0x4081
_FPMult			.equ 0x4084 ;op1=op1*op2
_LJRND			.equ 0x4087 ;adjusts op1 if 0s precede the actual number... rounding? when.
_InvOP1SC		.equ 0x408A
_InvOP1S		.equ 0x408D
_InvOP2S		.equ 0x4090
_frac			.equ 0x4093
_fprecip		.equ 0x4096
_fpdiv			.equ 0x4099
_SqRoot			.equ 0x409C
_RndGuard		.equ 0x409F
_RnFx			.equ 0x40A2
_int			.equ 0x40A5
_Round			.equ 0x40A8
_LnX			.equ 0x40AB
_LogX			.equ 0x40AE
_LJNORND		.equ 0x40B1 ;like _LJRND but no rounding
_EToX			.equ 0x40B4
_TenX			.equ 0x40B7
_SinCosRad		.equ 0x40BA
_Sin			.equ 0x40BD
_cos			.equ 0x40C0
_Tan			.equ 0x40C3
_SinHCosH		.equ 0x40C6
_TanH			.equ 0x40C9
_cosh			.equ 0x40CC
_SinH			.equ 0x40CF
_ACosRad		.equ 0x40D2
_ATanRad		.equ 0x40D5
_ATan2Rad		.equ 0x40D8
_ASinRad		.equ 0x40DB
_ACos			.equ 0x40DE
_ATan			.equ 0x40E1
_ASin			.equ 0x40E4
_ATan2			.equ 0x40E7
_ATanH			.equ 0x40EA
_ASinH			.equ 0x40ED
_ACosH			.equ 0x40F0
_PtoR			.equ 0x40F3
_RToP			.equ 0x40F6
_HLTimes9		.equ 0x40F9
_CkOP1Cplx		.equ 0x40FC
_CkOP1Real		.equ 0x40FF
_Angle			.equ 0x4102
_COP1Set0		.equ 0x4105
_CpOP4OP3		.equ 0x4108
_Mov9OP2Cp		.equ 0x410B
_AbsO1O2Cp		.equ 0x410E
_cpop1op2		.equ 0x4111
_OP3ToOP4		.equ 0x4114
_OP1ToOP4		.equ 0x4117
_OP2ToOP4		.equ 0x411A
_OP4ToOP2		.equ 0x411D
_OP1ToOP3		.equ 0x4123
_OP5ToOP2		.equ 0x4126
_OP5ToOP6		.equ 0x4129
_OP5ToOP4		.equ 0x412C
_OP1ToOP2		.equ 0x412F
_OP6ToOP2		.equ 0x4132
_OP6ToOP1		.equ 0x4135
_OP4ToOP1		.equ 0x4138
_OP5ToOP1		.equ 0x413B
_OP3ToOP1		.equ 0x413E
_OP6ToOP5		.equ 0x4141
_OP4ToOP5		.equ 0x4144
_OP3ToOP5		.equ 0x4147
_OP2ToOP5		.equ 0x414A
_OP2ToOP6		.equ 0x414D
_OP1ToOP6		.equ 0x4150
_OP1ToOP5		.equ 0x4153
_OP2ToOP1		.equ 0x4156
_Mov11B			.equ 0x4159
_Mov10B			.equ 0x415C
_Mov9B			.equ 0x415F
_mov9B2			.equ 0x4162 ;points to _mov9B
_Mov8B			.equ 0x4165
_Mov7B			.equ 0x4168
_Mov7B2			.equ 0x416b ;same pointer as _Mov7B
_OP2ToOP3		.equ 0x416E
_OP4ToOP3		.equ 0x4171
_OP5ToOP3		.equ 0x4174
_OP4ToOP6		.equ 0x4177
_Mov9ToOP1		.equ 0x417A
_Mov9OP1OP2		.equ 0x417D
_Mov9ToOP2		.equ 0x4180
_MovFrOP1		.equ 0x4183
_OP4Set1		.equ 0x4186
_OP3Set1		.equ 0x4189
_OP2Set8		.equ 0x418C
_OP2Set5		.equ 0x418F
_OP2SetA		.equ 0x4192
_OP2Set4		.equ 0x4195
_OP2Set3		.equ 0x4198
_OP1Set1		.equ 0x419B
_OP1Set4		.equ 0x419E
_OP1Set3		.equ 0x41A1
_OP3Set2		.equ 0x41A4
_OP1Set2		.equ 0x41A7
_OP2Set2		.equ 0x41AA
_OP2Set1		.equ 0x41AD
_Zero16D		.equ 0x41B0
_OP5Set0		.equ 0x41B3
_OP4Set0		.equ 0x41B6
_OP3Set0		.equ 0x41B9
_OP2Set0		.equ 0x41BC
_OP1Set0		.equ 0x41BF
_OPSet0			.equ 0x41C2 ;hl = location to write floating point 0
_ZeroOP1		.equ 0x41C5
_ZeroOP2		.equ 0x41C8
_ZeroOP3		.equ 0x41CB
_ZeroOP			.equ 0x41CE
_ClrLp			.equ 0x41D1
_ShRAcc			.equ 0x41D4 ;move high nibble in a to low nibble
_ShLAcc			.equ 0x41D7 ;move low nibble in a to high nibble
_ShR18			.equ 0x41DA ;insert a 0 nibble at high nibble of (hl), shift 9 bytes 1 nibble to right
_SHR18A			.equ 0x41DD ;insert low nibble in a at high nibble of (hl), shift 9 bytes 1 nibble to right
_SHR16			.equ 0x41E0 ;insert a 0 nibble at highnibble of (hl), shift 8 bytes 1 nibble to right
_SHR14			.equ 0x41E3 ;insert low nibble in a at high nibble of (hl), shift 7 bytes 1 nibble to right
_SHL16			.equ 0x41E6 ;insert nibble of 0 in low nibble of (hl), shift 8 bytes (before and including (hl)) to the left 1 nibble
_SHL14			.equ 0x41E9 ;insert low nibble of a in low nibble of (hl), shift 7 bytes (before and including (hl)) to the left 1 nibble
_SRDO1			.equ 0x41EC
_SHRDRND		.equ 0x41EF
_MANTPA			.equ 0x41F2 ;adds the value of a to hl which points to the end of the bcd 7 bytes long
_ADDPROP		.equ 0x41F5 ;adds the value of a to hl which points to the end of the bcd (b bytes long)
_ADDPROPLP		.equ 0x41F8 ;adds the value of a and carry to hl which points to the end of the bcd (b bytes long)
_ADD16D 		.equ 0x41FB ;adds the bcd numbers at (hl-7) and (de-7)
_ADD14D			.equ 0x41FE ;adds the bcd numbers at (hl-6) and (de-6)
_SUB16D			.equ 0x4201 ;subtracts bcd numbers at (hl-7) and (de-7)
_SUB14D			.equ 0x4204 ;subtracts bcd numbers at (hl-6) and (de-6)
_OP2ExOP6		.equ 0x4207
_OP5ExOP6		.equ 0x420A
_OP1ExOP5		.equ 0x420D
_OP1ExOP6		.equ 0x4210
_OP2ExOP4		.equ 0x4213
_OP2ExOP5		.equ 0x4216
_OP1ExOP3		.equ 0x4219
_OP1ExOP4		.equ 0x421C
_OP1ExOP2		.equ 0x421F
_ExLp			.equ 0x4222
_CkOP1C0		.equ 0x4225
_CkOP1FP0		.equ 0x4228
_CkOP2FP0		.equ 0x422B
_PosNo0Int		.equ 0x422E
_CKPosInt		.equ 0x4231
_CKInt			.equ 0x4234
_CKOdd			.equ 0x4237
_CKOP1M			.equ 0x423A
_GETCONOP1		.equ 0x423D ;a=0 opX=57.29577951308232 (1 radian in degrees)
_GETCONOP2		.equ 0x4240 ;a=1 opX=1.570796326794897 (90 deg = pi/2)
				  ;a=2 opX=.7853981633974483 (45 deg = pi/4)
				  ;a=3 opX=.4342944819032518 (log e)
				  ;a=4 opX=3.141592653589800 (pi)
				  ;a=5 opX=.0174532925199433 (pi/180 = 1 degree in radians)
				  ;a=6 opX=2.302585092994046 (ln 10)
_PIDIV2			.equ 0x4243 ;not code, but a pointer to:	.db 0x80,0x15,0x70,0x79,0x63,0x26,0x79,0x48,0x97
_PIDIV4			.equ 0x4246 ;				.db 0x7f,0x78,0x53,0x98,0x16,0x33,0x97,0x44,0x83
_ExpToHex		.equ 0x424F
_OP1ExpToDec		.equ 0x4252
_ckop2pos		.equ 0x4255
_CkOP1Pos		.equ 0x4258
_ClrOP2S		.equ 0x425B
_ClrOP1S		.equ 0x425E
_FDIV100		.equ 0x4261 ;op1=op1/100
_FDIV10			.equ 0x4264 ;op1=op1/10
_DecO1Exp		.equ 0x4267 ;decrease exponent by 1, this can go from 0 to FF
_INCO1EXP		.equ 0x426A ;op1=op1*10
_INCEXP			.equ 0x426d ;hl points to the floating point's exponent to be multiplied by 10
_CkValidNum		.equ 0x4270
_GETEXP			.equ 0x4273 ;a=op1's exponent, carry set if negative exponent, z if e0
_HTimesL		.equ 0x4276
_EOP1NotReal		.equ 0x4279
_ThetaName		.equ 0x427C
_RName			.equ 0x427F
_REGEQNAME		.equ 0x4282
_RECURNNAME		.equ 0x4285
_XName			.equ 0x4288
_YName			.equ 0x428B
_TName			.equ 0x428E
_REALNAME		.equ 0x4291
_SETesTOfps		.equ 0x4294 ;moves the word at fps to es
_markTableDirty		.equ 0x4297 ;looks up table variable and marks VAT entry as "dirty" or selected
_OP1MOP2EXP		.equ 0x429A ;op1's exponent = op1's expoent - op2's exponent
_OP1EXPMinusE		.equ 0x429D ;a=(op1+1)-e
_CHKERRBREAK		.equ 0x42A0
_isA2ByteTok		.equ 0x42A3
_GETLASTENTRY		.equ 0x42A6
_GETLASTENTRYPTR	.equ 0x42A9
_REGCLRCHNG		.equ 0x42AC
_RESETWINTOP		.equ 0x42AF ;takes into account grfsplitoverride and grfsplit flags
_SetYUp			.equ 0x42B2 ;loads 7 to port 10... what does this do?
_SetXUp			.equ 0x42B5 ;loads 5 to port 10...
_ISO1NONTLSTorPROG	.equ 0x42B8 ;checks if op1 contains a list, program, group, or appvar obj name
_ISO1NONTEMPLST		.equ 0x42BB ;checks if op1 contains a list (why would op1+1 contain 01, or 0d for a var name?)
_IS_A_LSTorCLST		.equ 0x42BE ;checks if a = 1 or 0x0D
_CHK_HL_999		.equ 0x42C1 ;returns nc if less than 999, throws invalid dim error if greater than or equal to 999
_equ_or_newequ		.equ 0x42C4
_errd_op1notpos		.equ 0x42C7
_ErrD_OP1Not_R		.equ 0x42CA
_ErrD_OP1NotPosInt 	.equ 0x42CD
_ErrD_OP1_LE_0		.equ 0x42D0
_ErrD_OP1_0		.equ 0x42D3
_FINDSYM_GET_SIZE 	.equ 0x42D6 ;like findsym, but on output hl is the size of the variable
_STO_STATVAR		.equ 0x42d9
_Rcl_StatVar		.equ 0x42DC
_CkOP2Real		.equ 0x42DF
_GET_X_INDIRECT		.equ 0x42E2 ;what ever this is, it uses the imathptrX locations
_MemChk			.equ 0x42E5
_CMPPRGNAMLEN1		.equ 0x42E8 ;what do these do?
_CMPPRGNAMLEN		.equ 0x42EB
_FINDPROGSYM		.equ 0x42EE ;find the program whose name is in op1 (see chkfindsym in SDK)
_ChkFindSym		.equ 0x42F1
_FindSym		.equ 0x42F4
_InsertMem		.equ 0x42F7
_INSERTMEMA		.equ 0x42FA ;not sure how this differs from insertmem
_EnoughMem		.equ 0x42FD
_CMPMEMNEED		.equ 0x4300
_CREATEPVAR4		.equ 0x4303
_CREATEPVAR3		.equ 0x4306
_CREATEVAR3		.equ 0x4309
_CreateCplx		.equ 0x430C
_CreateReal		.equ 0x430F
_CreateTempRList	.equ 0x4312
_CreateRList		.equ 0x4315
_CREATETCLIST		.equ 0x4318
_CreateCList		.equ 0x431B
_CreateRMat		.equ 0x4321
_CreateTempString	.equ 0x4324
_CreateStrng		.equ 0x4327
_Create0Equ		.equ 0x432A
_CreateTempEqu		.equ 0x432D
_CreateEqu		.equ 0x4330
_CreatePict		.equ 0x4333
_CreateGDB		.equ 0x4336
_CreateProg		.equ 0x4339
_CHKDEL			.equ 0x433C
_CHKDELA		.equ 0x433F
_ADJPARSER		.equ 0x4342
_ADJMATH		.equ 0x4345
_ADJM7			.equ 0x4348
_DELMEMA		.equ 0x434B
_GET_FORM_NUM		.equ 0x434E
_DelVar			.equ 0x4351
_DELVARIO		.equ 0x4354
_DelMem			.equ 0x4357
_DELVAR3D		.equ 0x435A
_DELVAR3C		.equ 0x435D
_DELVAR3DC		.equ 0x4360 ;may be incorrect
_DataSizeA		.equ 0x4369
_DataSize		.equ 0x436C
_POPMCPLXO1		.equ 0x436F
_POPMCPLX		.equ 0x4372
_MOVCPLX		.equ 0x4375
_popOP5			.equ 0x4378
_popOP3			.equ 0x437B
_popOP1			.equ 0x437E
_PopRealO6		.equ 0x4381
_PopRealO5		.equ 0x4384
_PopRealO4		.equ 0x4387
_PopRealO3		.equ 0x438A
_PopRealO2		.equ 0x438D
_PopRealO1		.equ 0x4390
_PopReal		.equ 0x4393
_FPOPCPLX		.equ 0x4396
_FPOPREAL		.equ 0x4399
_FPOPFPS		.equ 0x439C
_DeallocFPS		.equ 0x439F
_DeallocFPS1		.equ 0x43a2
_AllocFPS		.equ 0x43A5
_AllocFPS1		.equ 0x43A8
_PushRealO6		.equ 0x43AB
_PushRealO5		.equ 0x43AE
_PushRealO4		.equ 0x43B1
_PushRealO3		.equ 0x43B4
_PushRealO2		.equ 0x43B7
_PushRealO1		.equ 0x43BA
_PushReal		.equ 0x43BD
_PushOP5		.equ 0x43C0
_PushOP3		.equ 0x43C3
_PUSHMCPLXO3		.equ 0x43C6
_PushOP1		.equ 0x43C9
_PUSHMCPLXO1		.equ 0x43CC
_PUSHMCPLX		.equ 0x43CF
_ExMCplxO1		.equ 0x43D2
_Exch9			.equ 0x43D5
_CpyTo1FPS11		.equ 0x43D8
_CpyTo2FPS5		.equ 0x43DB
_CpyTo1FPS5		.equ 0x43DE
_CpyTo2FPS6		.equ 0x43E1
_CpyTo1FPS6		.equ 0x43E4
_CpyTo2FPS7		.equ 0x43E7
_CpyTo1FPS7		.equ 0x43EA
_CpyTo1FPS8		.equ 0x43ED
_CpyTo2FPS8		.equ 0x43F0
_CpyTo1FPS10		.equ 0x43F3
_CpyTo1FPS9		.equ 0x43F6
_CpyTo2FPS4		.equ 0x43F9
_CpyTo6FPS3		.equ 0x43FC
_CpyTo6FPS2		.equ 0x43FF
_CpyTo2FPS3		.equ 0x4402
_CPYCTO1FPS3		.equ 0x4405
_CpyTo1FPS3		.equ 0x4408
_CPYFPS3		.equ 0x440B
_CpyTo1FPS4		.equ 0x440E
_CpyTo3FPS2		.equ 0x4411
_CpyTo5FPST		.equ 0x4414
_CpyTo6FPST		.equ 0x4417
_CpyTo4FPST		.equ 0x441A
_CpyTo3FPST		.equ 0x441D
_CpyTo2FPST		.equ 0x4420
_CpyTo1FPST		.equ 0x4423
_CPYFPST		.equ 0x4426
_CpyStack		.equ 0x4429
_CpyTo3FPS1		.equ 0x442C
_CpyTo2FPS1		.equ 0x442F
_CpyTo1FPS1		.equ 0x4432
_CPYFPS1		.equ 0x4435
_CpyTo2FPS2		.equ 0x4438
_CpyTo1FPS2		.equ 0x443B
_CPYFPS2		.equ 0x443E
_CpyO3ToFPST		.equ 0x4441
_CpyO2ToFPST		.equ 0x4444
_CpyO6ToFPST		.equ 0x4447
_CpyO1ToFPST		.equ 0x444A
_CpyToFPST		.equ 0x444D
_CpyToStack		.equ 0x4450
_CpyO3ToFPS1		.equ 0x4453
_CpyO5ToFPS1		.equ 0x4456
_CpyO2ToFPS1		.equ 0x4459
_CpyO1ToFPS1		.equ 0x445C
_CpyToFPS1		.equ 0x445F
_CpyO2ToFPS2		.equ 0x4462
_CpyO3ToFPS2		.equ 0x4465
_CpyO6ToFPS2		.equ 0x4468
_CpyO1ToFPS2		.equ 0x446B
_CpyToFPS2		.equ 0x446E
_CpyO5ToFPS3		.equ 0x4471
_CpyO2ToFPS3		.equ 0x4474
_CpyO1ToFPS3		.equ 0x4477
_CpyToFPS3		.equ 0x447A
_CpyO1ToFPS6		.equ 0x447D
_CpyO1ToFPS7		.equ 0x4480
_CpyO1ToFPS5		.equ 0x4483
_CpyO2ToFPS4		.equ 0x4486
_CpyO1ToFPS4		.equ 0x4489
_ErrNotEnoughMem 	.equ 0x448C
_FPSMINUS9		.equ 0x448F
_HLMINUS9		.equ 0x4492
_ErrOverflow		.equ 0x4495
_ErrDivBy0		.equ 0x4498
_ErrSingularMat		.equ 0x449B
_ErrDomain		.equ 0x449E
_ErrIncrement		.equ 0x44A1
_ErrNon_Real		.equ 0x44A4
_ErrSyntax		.equ 0x44A7
_ErrDataType		.equ 0x44AA
_ErrArgument		.equ 0x44AD
_ErrDimMismatch		.equ 0x44B0
_ErrDimension		.equ 0x44B3
_ErrUndefined		.equ 0x44B6
_ErrMemory		.equ 0x44B9
_ErrInvalid		.equ 0x44BC
_ErrBreak		.equ 0x44BF
_ErrStat		.equ 0x44C2
_ErrSignChange		.equ 0x44C5
_ErrIterations		.equ 0x44C8
_ErrBadGuess		.equ 0x44CB
_ErrTolTooSmall		.equ 0x44CE
_ErrStatPlot		.equ 0x44D1
_ErrLinkXmit		.equ 0x44D4
_JError			.equ 0x44D7
_noErrorEntry		.equ 0x44DA
_pushErrorHandleR	.equ 0x44DD
_popErrorHandleR	.equ 0x44E0
_strcopy		.equ 0x44E3
_strCat			.equ 0x44E6
_isInSet		.equ 0x44E9
_sDone			.equ 0x44EC
_serrort		.equ 0x44EF
_sNameEq		.equ 0x44F2
_sUnderScr		.equ 0x44F5
_sFAIL			.equ 0x44F8
_sName			.equ 0x44FB
_sOK			.equ 0x44FE
_PutMap			.equ 0x4501
_PutC			.equ 0x4504
_DispHL			.equ 0x4507
_PutS			.equ 0x450A
_putpsb			.equ 0x450D
_PutPS			.equ 0x4510
_wputps			.equ 0x4513
_putbuf			.equ 0x4516
_putbuf1		.equ 0x4519
_wputc			.equ 0x451C
_wputs			.equ 0x451F
_wputsEOL		.equ 0x4522 ;displays string in HL in big font, and uses ... if too long
_wdispEOL		.equ 0x4525
_whomeup		.equ 0x4528
_setNumWindow		.equ 0x452B ;based on current cursor position, sets winleft and similar (for input prompts)
_newline		.equ 0x452E
_moveDown		.equ 0x4531
_scrollUp		.equ 0x4534
_shrinkWindow		.equ 0x4537
_moveUp			.equ 0x453A
_scrollDown		.equ 0x453D
_ClrLCDFull		.equ 0x4540
_ClrLCD			.equ 0x4543
_ClrScrnFull		.equ 0x4546
_ClrScrn		.equ 0x4549
_ClrTxtShd		.equ 0x454C
_ClrWindow		.equ 0x454F
_EraseEOL		.equ 0x4552
_EraseEOW		.equ 0x4555
_HomeUp			.equ 0x4558
_getcurloc		.equ 0x455B
_VPutMap		.equ 0x455E
_VPutS			.equ 0x4561
_VPutSN			.equ 0x4564
_vputsnG		.equ 0x4567
_vputsnT		.equ 0x456A
_RunIndicOn		.equ 0x456D
_RunIndicOff		.equ 0x4570
_saveCmdShadow		.equ 0x4573
_saveShadow		.equ 0x4576
_rstrShadow		.equ 0x4579
_rstrpartial		.equ 0x457C
_rstrCurRow		.equ 0x457F
_rstrUnderMenu		.equ 0x4582
_rstrbotrow		.equ 0x4585
_saveTR			.equ 0x4588 ;save top right corner of LCD so 2nd arrow can be displayed, indicinuse flag must be set
_restoreTR		.equ 0x458b ;restore top right corner of LCD destroyed by an arrow. indicinuse flag must be set
_GetKeyPress		.equ 0x458E
_GetTokLen		.equ 0x4591 ;input: hl=pointer to token. output: a=lenght of string, hl=pointer to string on page 1
_GET_TOK_STRNG		.equ 0x4594 ;input: hl=pointer to token. output: op3=string of the token, a=length of string
_GETTOKSTRING		.equ 0x4597 ;input: DE=token. output: hl=pointer to the string on page 1
_PUTBPATBUF2		.equ 0x459A
_PUTBPATBUF		.equ 0x459D
_putbPAT		.equ 0x45A0
_put0xcCeckScrolL	.equ 0x45A3
_DispEOL		.equ 0x45A6
_fdispEOL		.equ 0x45A9
_MAKEROWCMD		.equ 0x45AC
_TOTOSTRP		.equ 0x45AF
_SETVARNAME		.equ 0x45B2
_DispDone		.equ 0x45B5
_finishoutput		.equ 0x45B8
_curBlink		.equ 0x45BB
_CursorOff		.equ 0x45BE
_hideCursor		.equ 0x45C1
_CursorOn		.equ 0x45C4
_showCursor		.equ 0x45C7
_KeyToString		.equ 0x45CA
_PULLDOWNCHK		.equ 0x45CD ;something wrong here
_MenuCatCommon		.equ 0x45D0
_ZIfCatalog		.equ 0x45D3
_ZIfMatrixMenu		.equ 0x45D6 ;_loadCurCat
_LoadMenuNum		.equ 0x45D9
_LoadMenuNumL		.equ 0x45DC
_MenCatRet		.equ 0x45DF ;restores display as though a menu were just cleared (restores some flags too)
_MenuEdKey		.equ 0x45E5
_notalphnum		.equ 0x45EB
_SaveSavedFlags		.equ 0x45EE
_SetMenuFlags		.equ 0x45F1
_RstrSomeFlags		.equ 0x45F4
_RstrOScreen		.equ 0x45F7 ;restores saveSScreen to the display
_SaveOScreen		.equ 0x45FA ;stores display in saveSScreen
_dispListName		.equ 0x45FD ;_SeeIfErrorCx
_AdrMRow		.equ 0x4606
_AdrMEle		.equ 0x4609
_GETMATOP1A		.equ 0x460C
_GETM1TOOP1		.equ 0x460F
_GETM1TOP1A		.equ 0x4612
_GetMToOP1		.equ 0x4615
_PUTTOM1A		.equ 0x4618
_PUTTOMA1		.equ 0x461B
_PutToMat		.equ 0x461E
_MAT_EL_DIV		.equ 0x4621
_CMATFUN		.equ 0x4624
_ROWECH_POLY		.equ 0x4627
_ROWECHELON		.equ 0x462A
_AdrLEle		.equ 0x462D
_GETL1TOOP1		.equ 0x4630
_GETL1TOP1A		.equ 0x4633
_GetLToOP1		.equ 0x4636
_GETL1TOOP2		.equ 0x4639
_GETL1TOP2A		.equ 0x463C
_GETL2TOP1A		.equ 0x463F
_PUTTOLA1		.equ 0x4642
_PutToL			.equ 0x4645
_MAXMINLST		.equ 0x4648
_LLOW			.equ 0x464B
_LHIGH			.equ 0x464E
_LSUM			.equ 0x4651
CUMSUM			.equ 0x4654
_ToFrac			.equ 0x4657
_SEQSET			.equ 0x465A
_SEQSOLVE		.equ 0x465D
_CMP_NUM_INIT		.equ 0x4660
_BinOPExec		.equ 0x4663
_EXMEAN1		.equ 0x4666
_SET2MVLPTRS		.equ 0x4669
_SETMAT1		.equ 0x466C
_CREATETLIST		.equ 0x466F
_UnOPExec		.equ 0x4672
_ThreeExec		.equ 0x4675
_RESTOREERRNO		.equ 0x4678
_FourExec		.equ 0x467B
_FiveExec		.equ 0x467E
_CPYTO2ES1		.equ 0x4681
_CPYTO6ES1		.equ 0x4684
_CPYTO1ES1		.equ 0x4687
_CPYTO3ES1		.equ 0x468A
_CPYTO3ES2		.equ 0x468D
_CPYTO2ES2		.equ 0x4690
_CPYTO1ES2		.equ 0x4693
_CPYTO2ES3		.equ 0x4696
_CPYTO1ES3		.equ 0x4699
_CPYTO3ES4		.equ 0x469C
_CPYTO6ES3		.equ 0x469F
_CPYTO2ES4		.equ 0x46A2
_CPYTO1ES4		.equ 0x46A5
_CPYTO2ES5		.equ 0x46A8
_CPYTO1ES5		.equ 0x46AB
_CPYTO4EST		.equ 0x46AE
_CPYTO2EST		.equ 0x46B1
_CPYTO1EST		.equ 0x46B4
_CPYTO2ES6		.equ 0x46B7
_CPYTO1ES6		.equ 0x46BA
_CPYTO2ES7		.equ 0x46BD
_CPYTO1ES7		.equ 0x46C0
_CPYTO2ES8		.equ 0x46C3
_CPYTO1ES8		.equ 0x46C6
_CPYTO1ES9		.equ 0x46C9
_CPYTO2ES9		.equ 0x46CC
_CPYTO2ES10		.equ 0x46CF
_CPYTO1ES10		.equ 0x46D2
_CPYTO2ES11		.equ 0x46D5
_CPYTO1ES11		.equ 0x46D8
_CPYTO2ES12		.equ 0x46DB
_CPYTO1ES12		.equ 0x46DE
_CPYTO2ES13		.equ 0x46E1
_CPYTO1ES13		.equ 0x46E4
_CPYTO1ES14		.equ 0x46E7
_CPYTO1ES16		.equ 0x46EA
_CPYTO1ES17		.equ 0x46ED
_CPYTO1ES18		.equ 0x46F0
_CPYTO1ES15		.equ 0x46F3
_CPYTO2ES15		.equ 0x46F6
_CPYO1TOEST		.equ 0x46F9
_CPYO1TOES1		.equ 0x46FC
_CPYO6TOES1		.equ 0x46FF
_CPYO6TOES3		.equ 0x4702
_CPYO1TOES2		.equ 0x4705
_CPYO2TOES2		.equ 0x4708
_CPYO1TOES3		.equ 0x470B
_CPYO1TOES4		.equ 0x470D
_CPYO1TOES5		.equ 0x4711
_CPYO1TOES6		.equ 0x4714
_CPYO1TOES7		.equ 0x4717
_CPYO2TOES4		.equ 0x471A
_CPYO2TOES5		.equ 0x471D
_CPYO2TOES6		.equ 0x4720
_CPYO2TOES7		.equ 0x4723
_CPYO2TOES8		.equ 0x4726
_CPYO2TOES9		.equ 0x4729
_CPYO1TOES8		.equ 0x472C
_CPYO1TOES9		.equ 0x472F
_CPYO1TOES10		.equ 0x4732
_CPYO1TOES11		.equ 0x4735
_CPYO1TOES12		.equ 0x4738
_CPYO1TOES13		.equ 0x473B
_CPYO1TOES14		.equ 0x473E
_CPYO1TOES15		.equ 0x4741
_EVALF3A		.equ 0x4744
_GetK			.equ 0x4747 ;?
_setTitlE		.equ 0x474A
_dispVarVal		.equ 0x474D
_RecallEd		.equ 0x4750 ;_setupBuffer
_createNumEditBuf	.equ 0x4753
;0x4756
_CallCommon		.equ 0x4759
_CommonKeys		.equ 0x475C
_Leftmore		.equ 0x475F
_fDel			.equ 0x4762
_fClear			.equ 0x4765
_finsDisp		.equ 0x4768 ;Michael says _FinsDisp02 .equ 0x4768 (something's not right)
_FinsDisp02		.equ 0x476B ;_setIndicator
_closeeditbufnor	.equ 0x476E
_releaseBuffer		.equ 0x4771
_varnameToOP1hl		.equ 0x4774
_nameToOP1		.equ 0x4777
_numPPutAway		.equ 0x477A
_numRedisp		.equ 0x477D
_numError02		.equ 0x4780
_Load_SFont		.equ 0x4783
_SFont_Len		.equ 0x4786
_InitNumVec		.equ 0x4789
_SetXXOP1		.equ 0x478C
_SetXXOP2		.equ 0x478F
_SetXXXXOP2		.equ 0x4792
_UCLineS		.equ 0x4795
_CLine			.equ 0x4798
_CLineS			.equ 0x479B
_XRootY			.equ 0x479E
_YToX			.equ 0x47A1
_ZmStats		.equ 0x47A4
_POINT_STAT_HLP		.equ 0x47A7
_DRAWSPLOT		.equ 0x47AA
_INITNEWTRACEP		.equ 0x47AD
_SPLOTCOORD		.equ 0x47B0
_SPLOTRIGHT		.equ 0x47B3
_SPLOTLEFT		.equ 0x47B6
_CMPBOXINFO		.equ 0x47B9
_NEXTPLOT		.equ 0x47BC
_PREVPLOT		.equ 0x47BF
_CLRPREVPLOT		.equ 0x47C2
_PUT_INDEX_LST		.equ 0x47C5
_GET_INDEX_LST		.equ 0x47C8
_HEAP_SORT		.equ 0x47CB
_StoGDB2		.equ 0x47CE
_RclGDB2		.equ 0x47D1
_CircCmd		.equ 0x47D4
_GrphCirc		.equ 0x47D7
_Mov18B			.equ 0x47DA
_DarkLine		.equ 0x47DD
_ILine			.equ 0x47E0
_IPoint			.equ 0x47E3
_XYRNDBOTH		.equ 0x47E5
_XYRND			.equ 0x47E8
_CheckTOP		.equ 0x47EC
_CheckXY		.equ 0x47EF
_DarkPnt		.equ 0x47F2
_CPointS		.equ 0x47F5
_WTOV			.equ 0x47F8
_VtoWHLDE		.equ 0x47FB
_Xitof			.equ 0x47FE
_YftoI			.equ 0x4801
_XftoI			.equ 0x4804
_TraceOff		.equ 0x4807
_GrRedisp		.equ 0x480A
_GDISPTOKEN		.equ 0x480D
_GRDECODA		.equ 0x4810
_LABCOOR		.equ 0x4813
_COORDISP		.equ 0x4816 ;draws X & Y coordinates (or R and theta if PolarGC)
_TMPEQUNOSRC		.equ 0x4819
_GRLABELS		.equ 0x481C
_YPIXSET		.equ 0x481F
_XPIXSET		.equ 0x4822
_COPYRNG		.equ 0x4825
_VALCUR			.equ 0x4828
_GRPUTAWAY		.equ 0x482B
_RSTGFLAGS		.equ 0x482E
_GRReset		.equ 0x4831
_XYCENT			.equ 0x4834
_ZOOMXYCMD		.equ 0x4837
_CPTDELY		.equ 0x483A
_CPTDELX		.equ 0x483D
_SetFuncM		.equ 0x4840
_SetSeqM		.equ 0x4843
_SetPolM		.equ 0x4846
_SetParM		.equ 0x4849
_ZmInt			.equ 0x484C
_ZmDecml		.equ 0x484F
_ZmPrev			.equ 0x4852
_ZmUsr			.equ 0x4855
_SETUZM			.equ 0x4858
_ZmFit			.equ 0x485B
_ZmSquare		.equ 0x485E
_ZmTrig			.equ 0x4861
_SetXMinMax		.equ 0x4864
_ZooDefault		.equ 0x4867
_GrBufCpy		.equ 0x486A
_DRAWSPLITLINE		.equ 0x486D
_RestoreDisp		.equ 0x4870
_FNDDB			.equ 0x4873
_AllEq			.equ 0x4876
_fndallseleq		.equ 0x4879
_NEXTEQ			.equ 0x487C
_PREVEQ			.equ 0x487F
_BLINKGCUR		.equ 0x4882
_NBCURSOR		.equ 0x4885
_STATMARK		.equ 0x4888
_CHKTEXTCURS		.equ 0x488B
_Regraph		.equ 0x488E
_DOREFFLAGS02		.equ 0x4891 ;something wrong here
INITNSEQ		.equ 0x4894
_YRES			.equ 0x4897 ;_PLOTPTXY2
_Ceiling		.equ 0x489A ;ceil(OP1)
_PutXY			.equ 0x489D ;draws X & Y coordinates (regardless of PolarGC)
_PUTEQUNO		.equ 0x48A0
_PDspGrph		.equ 0x48A3
_HorizCmd		.equ 0x48A6
_VertCmd		.equ 0x48A9
_LineCmd		.equ 0x48AC
_UnLineCmd		.equ 0x48AF
_PointCmd		.equ 0x48B2
_PixelTest		.equ 0x48B5
_PixelCmd  		.equ 0x48B8
_TanLnF			.equ 0x48BB
_DRAWCMD_INIT		.equ 0x48BE
_DrawCmd		.equ 0x48C1
_SHADECMD		.equ 0x48C4
_InvCmd			.equ 0x48C7
_STATSHADE		.equ 0x48CA
_dspmattable		.equ 0x48CD
_dsplsts		.equ 0x48D0
_closeEditBuf		.equ 0x48D3
_parseEditBuf		.equ 0x48D6
_putsm			.equ 0x48D9
_DspCurTbl		.equ 0x48DC
_DSPGRTBL		.equ 0x48DF
_zeroTemplate		.equ 0x48E2
_settblrefs		.equ 0x48E5
_dispTblBot		.equ 0x48E8
_DispTblTop		.equ 0x48EB
_dispTblbody		.equ 0x48EE
_VPUTBLANK		.equ 0x48F1
_TBLTRACE		.equ 0x48F4
_dispListNameY		.equ 0x48F7
_CurNameLength		.equ 0x48FA
_NameToBuf		.equ 0x48FD
_jpromptcursor		.equ 0x4900
_BufLeft		.equ 0x4903
_BufRight		.equ 0x4906
_bufInsert		.equ 0x4909
_bufQueu0xeCar		.equ 0x490C
_BufReplace		.equ 0x490F
_BufDelete		.equ 0x4912
_BUFPEEK		.equ 0x4915
_BUFPEEK1		.equ 0x4918
_BUFPEEK2		.equ 0x491B
_BUFPEEK3		.equ 0x491E
_BufToBtm		.equ 0x4921
_setupEditEqu		.equ 0x4924
_BufToTop		.equ 0x4927
_isEditFull		.equ 0x492A
_IsEditEmpty		.equ 0x492D
_IsAtTop		.equ 0x4930
_IsAtBtm		.equ 0x4933
_BufClear		.equ 0x4936
_JcursorFirst		.equ 0x4939
_JcursorLast		.equ 0x493C
_CursorLeft		.equ 0x493F
_cursorRight		.equ 0x4942
_cursorUp		.equ 0x4945
_CursorDown		.equ 0x4948
_cursorToOffset		.equ 0x494B
_InsDisp		.equ 0x494E
_FDISPBOL1		.equ 0x4951
_FDISPBOL		.equ 0x4954
_DispEOW		.equ 0x4957
_DispHead		.equ 0x495A
_DispTail		.equ 0x495D
_PutTokString		.equ 0x4960
_setupEditCmd		.equ 0x4963
_setEmptyEditEqu	.equ 0x4966
_SetEmptyEditPtr	.equ 0x4969
_CloseEditEqu		.equ 0x496C
_GetPrevTok		.equ 0x496F
_getkey			.equ 0x4972
_canIndic		.equ 0x4975
_LCD_DRIVERON		.equ 0x4978
_DFMIN2			.equ 0x497B
_formDisp		.equ 0x497E
_formMatrix		.equ 0x4981
_wscrollLeft		.equ 0x4984
_wscrollUp		.equ 0x4987
_wscrollDown		.equ 0x498A
_wscrollRight		.equ 0x498D
_FormEReal		.equ 0x4990
_formERealTOK		.equ 0x4993
_FormDCplx		.equ 0x4996
_FormReal		.equ 0x4999
_formScrollUp		.equ 0x499C
_setwinabove		.equ 0x499F
_disarmScroll		.equ 0x49A2
_OP1toEdit		.equ 0x49A5
_MinToEdit		.equ 0x49A8
_rclVarToEdit		.equ 0x49AB
_rclVarToEditPtR	.equ 0x49AE
_RCLENTRYTOEDIT		.equ 0x49B1
_rclToQueue		.equ 0x49B4 ;recalls bytes at OP1 into edit buffer
_FORMTOTOK		.equ 0x49B7
_DISP_INTERVAL		.equ 0x49BA
_DisplstName		.equ 0x49BD
_dispSLstNameHL		.equ 0x49C0
_EditEqu		.equ 0x49C3
_closeEquField		.equ 0x49C6
_AutoSelect		.equ 0x49C9
_DISPYEOS		.equ 0x49CC
_dispNumEOS		.equ 0x49CF
_setupdispeq		.equ 0x49D2
_DispForward		.equ 0x49D5
_DispYPrompt2		.equ 0x49D8
_stringwidth		.equ 0x49DB
_dispErrorScreen	.equ 0x49DE ;displays top row of error screen (error message)
_POPCX			.equ 0x49E1 ;moves 14 bytes at cxPrev to cxMain, 15th byte goes to replace appflags
_loadnoeentry		.equ 0x49E4
_SaveScreen		.equ 0x49E7
_RETSCREEN		.equ 0x49EA
_RetScreenErr		.equ 0x49ED
_CheckSplitFlag		.equ 0x49F0
_SolveRedisp		.equ 0x49F3
_SolveDisp		.equ 0x49F6
_itemName		.equ 0x49F9
_SetNorm_Vals		.equ 0x49FC
;0x49FF
_ConvKeyToTok		.equ 0x4A02
;0x4A05
;0x4A08
_TokToKey		.equ 0x4A0B
;0x4A0E
_GETVARCMD		.equ 0x4A11
_SendVarCmd		.equ 0x4A14
;0x4A17
keyscnlnk		.equ 0x4A1A
;0x4A1D
_DelRes			.equ 0x4A20
_ConvLcToLr		.equ 0x4A23
_RedimMat		.equ 0x4A26
_IncLstSize		.equ 0x4A29
_InsertList		.equ 0x4A2C
_dellistel		.equ 0x4A2F
_EditProg		.equ 0x4A32
_CloseProg		.equ 0x4A35
_ClrGraphRef		.equ 0x4A38
_FixTempCnt		.equ 0x4A3B
_SAVEDATA		.equ 0x4A3E
_RESTOREDATA		.equ 0x4A41
_FindAlphaUp		.equ 0x4A44
_FindAlphaDn		.equ 0x4A47
_CmpSyms		.equ 0x4A4A
_CREATETEMP		.equ 0x4A4D
_CleanAll		.equ 0x4A50
_MoveToNextSym		.equ 0x4A53 ;input: hl=pointer to type byte of VAT entry. output: hl = pointer to next entry's type byte
_ConvLrToLc		.equ 0x4A56
_TblScreenDn		.equ 0x4A59 ;something is not right here
_TblScreenUp		.equ 0x4A5C
_SCREENUP		.equ 0x4A5F
_ScreenUpDown		.equ 0x4A62
_ZifRclHandler		.equ 0x4A65
_zifrclkapp		.equ 0x4A68
_rclkeyRtn		.equ 0x4A6B
_RCLKEY			.equ 0x4A6B
_RCLREGEQ_CALL		.equ 0x4A6E
_RCLREGEQ		.equ 0x4A71
_initNamePrompt		.equ 0x4A74
_NamePrompt2		.equ 0x4A77
_CATALOGCHK		.equ 0x4A7A
_clrTR			.equ 0x4A7D
_QUAD			.equ 0x4A80
_GRAPHQUAD		.equ 0x4A83
_BC2NOREAL		.equ 0x4A86
;0x4A89
_ErrNonReal		.equ 0x4A8C
_WRITE_TEXT		.equ 0x4A8F
_FORSEQINIT		.equ 0x4A92
_GRPHPARS		.equ 0x4A95
_PLOTPARS		.equ 0x4A98
_ParseInp		.equ 0x4A9B
_PARSEOFF		.equ 0x4A9E
_PARSESCAN		.equ 0x4AA1
_GETPARSE		.equ 0x4AA4
_SAVEPARSE		.equ 0x4AA7
_InitPFlgs		.equ 0x4AAA
_CKENDLINERR		.equ 0x4AAD
_OP2Set60		.equ 0x4AB0
_GETSTATPTR		.equ 0x4AB3
_CMP_STATPTR		.equ 0x4AB6
_VARSYSADR		.equ 0x4AB9
_StoSysTok		.equ 0x4ABC
_StoAns			.equ 0x4ABF
_StoTheta		.equ 0x4AC2
_StoR			.equ 0x4AC5
_StoY			.equ 0x4AC8
_StoN			.equ 0x4ACB
_StoT			.equ 0x4ACE
_StoX			.equ 0x4AD1
_StoOther		.equ 0x4AD4
_RclAns			.equ 0x4AD7
_RclY			.equ 0x4ADA
_RclN			.equ 0x4ADD
_RclX			.equ 0x4AE0
_RclVarSym		.equ 0x4AE3
_RclSysTok		.equ 0x4AE6
_StMatEl		.equ 0x4AE9
_STLSTVECEL		.equ 0x4AEC
_ConvOP1		.equ 0x4AEF
_Find_Parse_Formula	.equ 0x4AF2
_PARSE_FORMULA		.equ 0x4AF5
;0x4AF8
;0x4AFB
;0x4AFE
;0x4B01
;0x4B04
;0x4B07
;0x4B0A
_CreatePair		.equ 0x4B0D
_PUSHNUM		.equ 0x4B10
_INCCURPCERREND		.equ 0x4B13
_ERREND			.equ 0x4B16
_COMMAERRF		.equ 0x4B19
_COMMAERR		.equ 0x4B1C
_STEQARG2		.equ 0x4B1F
_STEQARG		.equ 0x4B22
_INPARG			.equ 0x4B25
_STEQARG3		.equ 0x4B28
_NXTFETCH		.equ 0x4B2B
_CKFETCHVAR		.equ 0x4B2E
_FETCHVARA		.equ 0x4B31
_FETCHVAR		.equ 0x4B34
_CKENDLIN		.equ 0x4B37
_CKENDEXP		.equ 0x4B3A
_CKPARSEND		.equ 0x4B3D
_STOTYPEARG		.equ 0x4B40
_ConvDim		.equ 0x4B43
_ConvDim00		.equ 0x4B46
_AHEADEQUAL		.equ 0x4B49
_PARSAHEADS		.equ 0x4B4C
_PARSAHEAD		.equ 0x4B4F
_AnsName		.equ 0x4B52
_STOCMPREALS		.equ 0x4B55
_GETDEPTR		.equ 0x4B58
_PUSH2BOPER		.equ 0x4B5B ;push the value in bc onto the operator stack
_POP2BOPER		.equ 0x4B5E ;pop 2 bytes on the operator stack to bc
_PUSHOPER		.equ 0x4B61 ;push the value in a onto the operator stack
_POPOPER		.equ 0x4B64 ;pop 1 byte on the operator stack to a
_FIND_E_UNDEF		.equ 0x4B67
_STTMPEQ		.equ 0x4B6A
_FINDEOL		.equ 0x4B6D
_BRKINC			.equ 0x4B70
_INCFETCH		.equ 0x4B73
_CURFETCH		.equ 0x4B76
_Random			.equ 0x4B79
_StoRand		.equ 0x4B7C
_RandInit		.equ 0x4B7F
_resetStacks		.equ 0x4B82 ;(onsp)->(errsp), (fpbase)->(fps), (opbase)->(ops)
_Factorial		.equ 0x4B85
_YONOFF			.equ 0x4B88
_EQSELUNSEL		.equ 0x4B8B
_ITSOLVER		.equ 0x4B8E
_GRITSOLVER		.equ 0x4B91
_ITSOLVERB		.equ 0x4B94
_ITSOLVERNB		.equ 0x4B97
_ExTest_INT		.equ 0x4B9A
_DIST_FUN		.equ 0x4BAD
_LogGamma		.equ 0x4BA0
_OneVar			.equ 0x4BA3
_ONEVARS_0		.equ 0x4BA6
_ORDSTAT		.equ 0x4BA9
_INITSTATANS2		.equ 0x4BAC
_ANOVA_SPEC		.equ 0x4BAF
_OutputExpr		.equ 0x4BB2
_CentCursor		.equ 0x4BB5
_TEXT			.equ 0x4BB8
_FINISHSPEC		.equ 0x4BBB
_TRCYFUNC		.equ 0x4BBE
_RCL_SEQ_X		.equ 0x4BC1
_RCLSEQ2		.equ 0x4BC4
_GRPPutAway		.equ 0x4BC7
_CKVALDELX		.equ 0x4BCA
_CKVALDELTA		.equ 0x4BCD
_GrBufClr		.equ 0x4BD0
_GRBUFCPY_V		.equ 0x4BD3
_FNDSELEQ		.equ 0x4BD6
_CLRGRAPHXY		.equ 0x4BD9
_NEDXT_Y_STYLE		.equ 0x4BDC
_PLOTPT			.equ 0x4BDF
_NEWINDEP		.equ 0x4BE2
_Axes			.equ 0x4BE5
_setPenX		.equ 0x4BE8
_setPenY		.equ 0x4BEB
_setPenT		.equ 0x4BEE
_TAN_EQU_DISP		.equ 0x4BF1
_PutAns			.equ 0x4BF4
_DispOP1A		.equ 0x4BF7
_MATHTANLN		.equ 0x4BFA
_ENDDRAW		.equ 0x4BFD
_SetTblGraphDraw	.equ 0x4C00
;0x4C03
;0x4C06
;0x4C09
;0x4C0C
;0x4C0F
;0x4C12
;0x4C15
;0x4C18
;0x4C1B
;0x4C1E
;0x4C21
;0x4C24
;0x4C27
;0x4C2A
;0x4C2D
_MemClear		.equ 0x4C30
_MemSet			.equ 0x4C33
_ReloadAppEntryVecs	.equ 0x4C36
_PointOn		.equ 0x4C39
;0x4C3C
_StrLength		.equ 0x4C3F
;0x4C42
_getRomPage		.equ 0x4C45
_FindAppUp		.equ 0x4C48
_FindAppDn		.equ 0x4C4B
_FindApp		.equ 0x4C4E
_ExecuteApp		.equ 0x4C51
;0x4C54
;0x4C57
;0x4C5A
;0x4C5D
_IBounds		.equ 0x4C60
_IOffset		.equ 0x4C63
_DrawCirc2		.equ 0x4C66
_CanAlphIns		.equ 0x4C69
cxRedisp		.equ 0x4C6C
_GetBaseVer		.equ 0x4C6F
_OPSet0DE		.equ 0x4C72 ;loads a floating point 0 to location de
_AppGetCbl		.equ 0x4C75
_AppGetCalc		.equ 0x4C78
_SaveDisp		.equ 0x4C7B
_SetIgnoreKey  		.equ 0x4C7E ;set 1,(iy+0x28) / ret
_SetSendThisKeyBack	.equ 0x4C81 ;set 2,(iy+0x28) / ld (kbdKey),a / ret
_DisableApd		.equ 0x4C84
_EnableApd		.equ 0x4C87 ;set apdable,(iy+apdflags)
;0x4C8A
_set2IY34		.equ 0x4C8D ;set 2,(iy+34) / ret
_forcecmd		.equ 0x4C90
_ApdSetup		.equ 0x4C93
_Get_NumKey		.equ 0x4C96
;0x4C99
;0x4C9C
;0x4C9F
_ReleaseSedit		.equ 0x4CA2
_initsmalleditline	.equ 0x4CA5
_startsmalledit		.equ 0x4CA8
;0x4CAB
_SGetTokString		.equ 0x4CAE
_LoadPattern	 	.equ 0x4CB1
_SStringLength		.equ 0x4CB4
;?
_initsmalleditBox	.equ 0x4CDB
;?
_ClearRow		.equ 0x4CED
;?
_AppScreenUpDown	.equ 0x4D26
_AppScreenUpDown1	.equ 0x4D29
;?
_initsmalleditlinevar	.equ 0x4D2F
_initsmalleditlineop1	.equ 0x4D32
_initsmalleditboxvar	.equ 0x4D35
_initsmalleditboxop1	.equ 0x4D38
;?
_AppStartMouse		.equ 0x4D47
_AppEraseMouse		.equ 0x4D53
;?
_ClearRect		.equ 0x4D5C
_InvertRect		.equ 0x4D5F
_FillRect		.equ 0x4D62
_AppUpdateMouse		.equ 0x4D65
;?
_initcellbox		.equ 0x4D6E
_drawcell		.equ 0x4D71
;?
_invertcell		.equ 0x4D77
_setcelloverride	.equ 0x4D7A
_DrawRectBorder		.equ 0x4D7D
_ClearCell		.equ 0x4D80
_covercell		.equ 0x4D83
_EraseRectBorder	.equ 0x4D86
_FillRectPattern	.equ 0x4D89
_DrawRectBorderClear	.equ 0x4D8C
;?
_IBoundsFull		.equ 0x4D98
_DisplayImage		.equ 0x4D9B
;?
_CPoint			.equ 0x4DC8
_DeleteApp		.equ 0x4DCB
_setmodecellflag	.equ 0x4DD1
_resetmodecellflag	.equ 0x4DD4
_ismodecellset		.equ 0x4DD7
_getmodecellflag	.equ 0x4DDA
;?
_CellBoxManager		.equ 0x4DE0
_startnewcell		.equ 0x4DE3
;?
_CellCursorHandle	.equ 0x4DE9
;?
_ClearCurCell		.equ 0x4DF2
_drawcurcell		.equ 0x4DF5
_invertcurcell		.equ 0x4DF8
_covercurcell		.equ 0x4DFB
_BlinkCell		.equ 0x4DFE
_BlinkCellNoLookUp	.equ 0x4E01
_BlinkCurCell		.equ 0x4E04
_BlinkCellToOn		.equ 0x4E07
_BlinkCellToOnNoLookUp	.equ 0x4E0A
_BlinkCurCellToOn	.equ 0x4E0D
_BlinkCellToOff		.equ 0x4E10
_BlinkCellToOffNoLookUp .equ 0x4E13
_BlinkCurCellToOff	.equ 0x4E16
;?
_startsmalleditreturn	.equ 0x4E1F
;?
_CellkHandle		.equ 0x4E28
_errchkalphabox		.equ 0x4E2B
;?
_eraseallcells		.equ 0x4E3A
_iscurmodecellset	.equ 0x4E3D
;?
_initalphabox		.equ 0x4E43
;?
_drawblnkcell		.equ 0x4E4C
_ClearBlnkCell		.equ 0x4E4F
_invertblnkcell		.equ 0x4E52
;?
_CreateAppVar		.equ 0x4E6A
_CreateProtProg		.equ 0x4E6D
;?
_ExecutePrgm		.equ 0x4E7C
;?
_RecAByteIO		.equ 0x4F03
_SrchVLstUp		.equ 0x4F0F
_SrchVLstDn		.equ 0x4F12
;?
_FlashWriteDisable	.equ 0x4F3C
;?
_Disp			.equ 0x4F45
;0x4F48
;0x4F4B
;0x4F4E
_GetHookByte		.equ 0x4F51
;0x4F54
_cursorhook		.equ 0x4F57
;0x4F5A
;0x4F5D
_setCursorHook		.equ 0x46F0 ;enable cursor hook
;0x4F63
_SetGetKeyHook		.equ 0x4F66
_ClrCursorHook		.equ 0x4F69
;0x4F6C
_ClrRawKeyHook  .equ 0x4F6F
;0x4F72
;0x4F75
_getkeyhook		.equ 0x4F78
_SetGetcscHook		.equ 0x4F7B
_ClrGetKeyHook		.equ 0x4F7E
;0x4F81 run link assist hook?
;0x4F84 enable link assist hook?
;0x4F87 disable link assist hook?
;0x4F8A
;0x4F8D enable catalog hook
;0x4F90 disable catalog hook
;0x4F93 enable character hook
;0x4F96 loads 0x0109 to localLanguage and resets bit 1 of iy+0x35
_SetTokenHook		.equ 0x4F99
_ClearTokenHook		.equ 0x4F9C
;0x4F9F ld hl,92c6 / ld a,(92c5) / res 2,a / cp (hl) / ret
;0x4FA2 hl=11*(92fc)+92c9 / ld a,(hl) / and 0xF / cp 2 / ret
;0x4FA5
_Bit_VertSplit		.equ 0x4FA8
_SetcxMainHook		.equ 0x4FAB
_ClrHomeScreenHook	.equ 0x4FAE
_SetWindowHook		.equ 0x4FB1 ;enable wind/tblset/tvmsol cxMain hook
;0x4FB4 disable wind/tblset/tvmsol cxMain hook
_SetGraphModeHook .equ   0x4FB7;enable graph cxMain hook
;0x4FBA disable graph cxMain
_DelVarArc		.equ 0x4FC6
_DelVarNoArc		.equ 0x4FC9
_SetAllPlots		.equ 0x4FCC
_SetYeditHook     	.equ 0x4FCF  ;enable cxMain y= hook
;0x4FD2 disable cxMain y= hook
_Arc_Unarc		.equ 0x4FD8
;0x4FDE takes ROM page in a as input
_SetFontHook		.equ 0x4FE4
_ClrFontHook		.equ 0x4FE7
_SetRegraphHook		.equ 0x4FEA
;0x4FED disable graphing hook
;0x4FF0
_SetTraceHook		.equ 0x4FF3
;0x4FF6
;0x4FF9
;0x4FFC
;0x4FFF
_JForceGraphNoKey	.equ 0x5002
_JForceGraphKey		.equ 0x5005
_PowerOff		.equ 0x5008
_GetKeyRetOff		.equ 0x500B ;same as getkey, only returns kOff if 2nd+on is pressed
;0x500E
;0x5011
_Ar0xcCk			.equ 0x5014
_FlashToRam		.equ 0x5017
_LoadDEIndPaged		.equ 0x501A
_LoadCIndPaged		.equ 0x501D
_SetupPagedPtr		.equ 0x5020
_PagedGet		.equ 0x5023
_SetParserHook		.equ 0x5026
_ClearParserHook	.equ 0x5029
_SetAppChangeHook 	.equ 0x502C
_ClearAppChangeHook	.equ 0x502F
;0x5032 enable graphics hook
;0x5035 disable graphics hook
;0x5038
;0x503B
;0x503E
;0x5041
;0x5044 enable catalog hook
;0x5047 disable catalog hook
;0x504A enable mode cxMain hook
;0x504D disable mode cxMain hook
;0x5050
;0x5053
;0x5056
;0x5059
;0x505C
;0x505F
;0x5062
_dispMenuTitle		.equ 0x5065
;0x506B enable putaway hook
;0x506E disable putaway hook
_BufCpy			.equ 0x5071
_BufClr			.equ 0x5074
;0x5077
;0x507A
;0x507D
;0x5080
_SetMenuHook		.equ 0x5083
_ClearMenuHook		.equ 0x5086
_getBCOffsetIX		.equ 0x5089 ;ld a,(ix+bc); ix and bc preserved
;0x508C
_ForceFullScreen	.equ 0x508F
_FindAppNumPages	.equ 0x509B
_FormBase		.equ 0x50AA
;?
_Chk_Batt_Low		.equ 0x50B3
;?
_GetAppBasePage		.equ 0x50BC ;input: a=one of an app's pages. output: a=app's first page
_SetExSpeed		.equ 0x50BF
;?
_SetLinkHook		.equ 0x50CE
;0x50D1
_TwoVarSet		.equ 0x50D4
;?
_GetSysInfo		.equ 0x50DD
;?
_NZIf83Plus		.equ 0x50E0
;?
_InvertTextInsMode	.equ 0x5122
;?
_GetDate                .equ 0x514F ; not on basic TI-83+
;?
_GetTime                .equ 0x515B ; not on basic TI-83+
;?
_ClrWindowAndFlags	.equ 0x517F
;?
_IsOP1ResID		.equ 0x51B8
;?
_ChkHelpHookVer		.equ 0x51CA
_Disp32			.equ 0x51CD
;?
_LoadA5			.equ 0x5242
;?
_EnableUSBHook		.equ 0x528A
_DisableUSBHook		.equ 0x528D

;Page 0x1F ROM Calls
;--------------------------------
bootbtf			.equ 0x8000
;0x8000
;0x8003
;0x8006
;0x8009
;0x800C
;0x800F
;0x8012
;0x8015
_MD5Final		.equ 0x8018
_RSAValidate		.equ 0x801B
_cmpStr			.equ 0x801E ;BigNumCompare
_WriteAByte		.equ 0x8021
_EraseFlash		.equ 0x8024
_ZeroToCertificate	.equ 0x802A
_GetCertificateEnd	.equ 0x802D
_Mult8By8		.equ 0x8042
_Mult16By8		.equ 0x8045
_Div16By8		.equ 0x8048
_Div16By16		.equ 0x804B
_LoadAIndPaged		.equ 0x8051
_GetCertificateStart	.equ 0x8057
_GetFieldSize		.equ 0x805A
_EraseCertificateSector .equ 0x8060
_getSerial		.equ 0x807E ;GetCalcSerial
;0x8081 ;definitely a routine
_EraseFlashPage		.equ 0x8084
_WriteFlashUnsafe	.equ 0x8087
_dispBootVer		.equ 0x808A
_MD5Init		.equ 0x808D
_MD5Update		.equ 0x8090
;0x8093 ;definitely a routine
;0x8096 ;definitely a routine
;0x8099 ;definitely a routine
_CheckOSValidated	.equ 0x809C
_SetupAppPubKey		.equ 0x809F
_SigModR		.equ 0x80A2
_TransformHash		.equ 0x80A5
;0x80A8 ;definitely a routine
;0x80AB ;definitely a routine
;0x80AE ;can't figure it out, deals with certificate page
_Div32By16		.equ 0x80B1
;0x80B4 ;can't figure it out, deals with flash a lot
_getBootVer		.equ 0x80B7
_getHardwareVersion	.equ 0x80BA
_xorA			.equ 0x80BD ;xor a
_bignumpowermod17	.equ 0x80C0
_WriteFlash		.equ 0x80C9
_SetFlashLowerBound	.equ 0x80CF

;RAM Equates
;--------------------------------
ramStart		.equ 0x8000
appData			.equ 0x8000
ramCode			.equ 0x8100
ramCodeEnd		.equ 0x822F
baseAppBrTab		.equ 0x8230 ;table of base pages for apps on page <20
bootTemp		.equ 0x8251
appSearchPage		.equ 0x82A3
tempSwapArea		.equ 0x82A5
appID			.equ 0x838D
ramReturnData		.equ 0x83ED
arcInfo			.equ 0x83EE
savedArcInfo		.equ 0x8406
appInfo			.equ 0x8432
appBank_jump		.equ 0x843C
appPage			.equ 0x843E
kbdScanCode		.equ 0x843F
kbdKey			.equ 0x8844
kbdGetKy		.equ 0x8445
keyExtend		.equ 0x8446
EXTECHO			.equ keyExtend
contrast		.equ 0x8447
apdSubTimer		.equ 0x8448
apdTimer		.equ 0x8449
curTime			.equ 0x844A
curRow			.equ 0x844B
curCol			.equ 0x844C
curOffset		.equ 0x844D
curUnder		.equ 0x844E
curY			.equ 0x844F
curType			.equ 0x8450
curXRow			.equ 0x8451
prevDData		.equ 0x8452
lFont_record		.equ 0x845A
sFont_record		.equ 0x8462
tokVarPtr		.equ 0x846A
tokLen			.equ 0x846C
indicMem		.equ 0x846E ;eight bytes used by _saveTR and _restoreTR to store image in top right corner
indicCounter		.equ 0x8476
indicBusy		.equ 0x8477
OP1			.equ 0x8478
OP1M			.equ 0x847A
OP2			.equ 0x8483
OP2M			.equ 0x8485
OP2EXT			.equ 0x848C
OP3			.equ 0x848E
OP3M			.equ 0x8490
OP4			.equ 0x8499
OP4M			.equ 0x849B
OP5			.equ 0x84A4
OP5M			.equ 0x84A6
OP6			.equ 0x84AF
OP6M			.equ 0x84B1
OP6EXT			.equ 0x84B8
progToEdit		.equ 0x84BF
nameBuff		.equ 0x84C7
equ_edit_save		.equ 0x84D2
iMathPtr1		.equ 0x84D3
iMathPtr2		.equ 0x84D5
iMathPtr3		.equ 0x84D7
iMathPtr4		.equ 0x84D9
iMathPtr5		.equ 0x84DB
chkDelPtr1		.equ 0x84DD
chkDelPtr2		.equ 0x84DF
insDelPtr		.equ 0x84E1
upDownPtr		.equ 0x84E3
fOutDat			.equ 0x84E5
asm_data_ptr1		.equ 0x84EB
asm_data_ptr2		.equ 0x84ED
asm_sym_ptr1		.equ 0x84EF
asm_sym_ptr2		.equ 0x84F1
asm_ram			.equ 0x84F3
asm_ind_call		.equ 0x8507
textShadow		.equ 0x8508
textShadCur		.equ 0x8588
textShadTop		.equ 0x858A
textShadAlph		.equ 0x858B
textShadIns		.equ 0x858C
cxMain			.equ 0x858D
cxPPutAway		.equ 0x858F
cxPutAway		.equ 0x8591
cxErrorEP		.equ 0x8595
cxSizeWind		.equ 0x8597
cxPage			.equ 0x8599
cxCurApp		.equ 0x859A
cxPrev			.equ 0x859B ;12 bytes are shadows of cxMain through cxCurApp and appFlags
monQH			.equ 0x85AA
monQT			.equ 0x85AB
monQueue		.equ 0x85AC
onSP			.equ 0x85BC
promptRow		.equ 0x85C0
promptCol		.equ 0x85C1
promptIns		.equ 0x85C2
promptShift		.equ 0x85C3
promptRet		.equ 0x85C4
promptValid		.equ 0x85C6
promptTop		.equ 0x85C8
promptCursor		.equ 0x85CA
promptTail		.equ 0x85CC
promptBtm		.equ 0x85CE
varType			.equ 0x85D0
varCurrent		.equ 0x85D1
varClass		.equ 0x85D9
CatalogCurrent		.equ 0x85DA ;word at this location starting with 0x6007 corresponds to what is highlighted in catalog
menuActive		.equ 0x85DC
menuAppDepth		.equ 0x85DD
MenuCurrent		.equ 0x85DE
ProgCurrent		.equ 0x85E8
userMenuSA		.equ 0x85FE
ioPrompt		.equ 0x865F
dImageWidth		.equ 0x8660
ioFlag			.equ 0x8670
sndRecState		.equ 0x8672
ioErrState		.equ 0x8673
header			.equ 0x8674
ioData			.equ 0x867D
ioNewData		.equ 0x8689
bakHeader		.equ 0x868B
penCol			.equ 0x86D7
penRow			.equ 0x86D8
rclQueue		.equ 0x86D9
rclQueueEnd		.equ 0x86DB
errNo			.equ 0x86DD
errSP			.equ 0x86DE
errOffset		.equ 0x86E0
saveSScreen		.equ 0x86EC
bstCounter		.equ 0x89EE
flags			.equ 0x89F0
appFlagsAddr		.equ 0x89FD
statVars		.equ 0x8A3A
anovaf_vars		.equ 0x8C17
infVars			.equ 0x8C4D
curGStyle		.equ 0x8D17
curGY			.equ 0x8D18
curGX			.equ 0x8D19
curGY2			.equ 0x8D1A
curGX2			.equ 0x8D1B
freeSaveY		.equ 0x8D1C
freeSaveX		.equ 0x8D1D
XOffset			.equ 0x8DA1
YOffset			.equ 0x8DA2
lcdTallP		.equ 0x8DA3
pixWideP		.equ 0x8DA4
pixWide_m_1		.equ 0x8DA5
pixWide_m_2		.equ 0x8DA6
lastEntryPTR		.equ 0x8DA7 ;pointer to the next available byte in the entry stack
lastEntryStk		.equ 0x8DA9 ;the start of entry stack (note last entry is not in the stack, it is in the program '#'.)  This is a stack of strings.  first 2 bytes are length, followed by string. 2nd from last entry is first in this stack.
numLastEntries		.equ 0x8E29 ;number of entries you can back-track through minus one
currLastEntry		.equ 0x8E2A ;counter used by OS to keep tract of which entry was just displayed by pressing 2nd+enter
curInc			.equ 0x8E67
uXmin			.equ 0x8E7E
uXmax			.equ 0x8E87
uXscl			.equ 0x8E90
uYmin			.equ 0x8E99
uYmax			.equ 0x8EA2
uYscl			.equ 0x8EAB
uThetMin		.equ 0x8EB4
uThetMax		.equ 0x8EBD
uThetStep		.equ 0x8EC6
uTmin			.equ 0x8ECF
uTmax			.equ 0x8ED8
uTStep			.equ 0x8EE1
uPlotStart		.equ 0x8EEA
unMax			.equ 0x8EF3
uu0			.equ 0x8EFC
uv0			.equ 0x8F05
unMin			.equ 0x8F0E
uu02			.equ 0x8F17
uv02			.equ 0x8F20
uw0			.equ 0x8F29
uPlotStep		.equ 0x8F32
uXres			.equ 0x8F3B
uw02			.equ 0x8F44
Xmin			.equ 0x8F50
Xmax			.equ 0x8F59
Xscl			.equ 0x8F62
Ymin			.equ 0x8F6B
Ymax			.equ 0x8F74
Yscl			.equ 0x8F7D
ThetaMin		.equ 0x8F86
ThetaMax		.equ 0x8F8F
ThetaStep		.equ 0x8F98
TminPar			.equ 0x8FA1
TmaxPar			.equ 0x8FAA
Tstep			.equ 0x8FB3
PlotStart		.equ 0x8FBC
nMax			.equ 0x8FC5
u0			.equ 0x8FCE
v0			.equ 0x8FD7
nMin			.equ 0x8FE0
u02			.equ 0x8FE9
v02			.equ 0x8FF2
w0			.equ 0x8FFB
PlotStep		.equ 0x9004
XresO			.equ 0x900D
w02			.equ 0x9016
un1			.equ 0x901F
un2			.equ 0x9028
vn1			.equ 0x9031
vn2			.equ 0x903A
wn1			.equ 0x9043
wn2			.equ 0x904C
fin_N			.equ 0x9055
fin_I			.equ 0x905E
fin_PV			.equ 0x9067
fin_PMT			.equ 0x9070
fin_FV			.equ 0x9079
fin_PY			.equ 0x9082
fin_CY			.equ 0x908B
cal_N			.equ 0x9094
cal_I			.equ 0x909D
cal_PV			.equ 0x90A6
cal_PMT			.equ 0x90AF
cal_FV			.equ 0x90B8
cal_PY			.equ 0x90C1
smallEditRAM		.equ 0x90D3
XFact			.equ 0x913F
YFact			.equ 0x9148
Xres_int		.equ 0x9151
deltaX			.equ 0x9152
deltaY			.equ 0x915B
shortX			.equ 0x9164
shortY			.equ 0x916D
lower			.equ 0x9176
upper			.equ 0x917F
XOutSym			.equ 0x918C
XOutDat			.equ 0x918E
YOutSym			.equ 0x9190
YOutDat			.equ 0x9192
inputSym		.equ 0x9194
inputDat		.equ 0x9196
prevData		.equ 0x9198
TblMin			.equ 0x92B3
TblStep			.equ 0x92BC
ES			.equ 0x9302 ;bottom of the es
EST			.equ 0x9305 ;current height of the es
plotSScreen		.equ 0x9340
seed1			.equ 0x9640
seed2			.equ 0x9649
cmdShadow		.equ 0x966E
cmdShadCur		.equ 0x96EE
cmdShadAlph		.equ 0x96F0
cmdShadIns		.equ 0x96F1
cmdCursor		.equ 0x96F2
editTop			.equ 0x96F4
editCursor		.equ 0x96F6
editTail		.equ 0x96F8
editBtm			.equ 0x96FA
editSym			.equ 0x9706
editDat			.equ 0x9708
y1LineType		.equ 0x9776 ;these bytes define the line type for functions which are graphed
y2LineType		.equ 0x9777
y3LineType		.equ 0x9778
y4LineType		.equ 0x9779
y5LineType		.equ 0x977A
y6LineType		.equ 0x977B
y7LineType		.equ 0x977C
y8LineType		.equ 0x977D
y9LineType		.equ 0x977E
y0LineType		.equ 0x977F
para1LineType		.equ 0x9780
para2LineType		.equ 0x9781
para3LineType		.equ 0x9782
para4LineType		.equ 0x9783
para5LineType		.equ 0x9784
para6LineType		.equ 0x9785
polar1LineType		.equ 0x9786
polar2LineType		.equ 0x9787
polar3LineType		.equ 0x9788
polar4LineType		.equ 0x9789
polar5LineType		.equ 0x978A
polar6LineType		.equ 0x978B
secULineType		.equ 0x978C
secVLineType		.equ 0x978D
secWLineType		.equ 0x978E
winTop			.equ 0x97A5
winBtm			.equ 0x97A6
winLeftEdge		.equ 0x97A7
winLeft			.equ 0x97A8
winAbove		.equ 0x97AA
winRow			.equ 0x97AC
winCol			.equ 0x97AE
fmtDigits		.equ 0x97B0
fmtString		.equ 0x97B1
fmtConv			.equ 0x97F2
fmtLeft			.equ 0x9804
fmtIndex		.equ 0x9806
fmtMatSym		.equ 0x9808
fmtMatMem		.equ 0x980A
EQS			.equ 0x980C
tSymPtr1		.equ 0x9818
tSymPtr2		.equ 0x981A
chkDelPtr3		.equ 0x981C
chkDelPtr4		.equ 0x981E
tempMem			.equ 0x9820
fpBase			.equ 0x9822
FPS			.equ 0x9824
OPBase			.equ 0x9826
OPS			.equ 0x9828
pTempCnt		.equ 0x982A
cleanTmp		.equ 0x982C
pTemp                   .equ 0x982E ;end of symbol table
progPtr			.equ 0x9830
newDataPtr		.equ 0x9832
pagedCount		.equ 0x9834
pagedPN			.equ 0x9835
pagedGetPtr		.equ 0x9836
pagedPutPtr		.equ 0x9838
pagedBuf		.equ 0x983A
appErr1			.equ 0x984D
appErr2			.equ 0x985A
flashByte1		.equ 0x9867
flashByte2		.equ 0x9868
freeArcBlock		.equ 0x9869
arcPage			.equ 0x986B
arcPtr			.equ 0x986C
appRawKeyHandle		.equ 0x9870
appBackUpScreen		.equ 0x9872
customHeight		.equ 0x9B72
localLanguage		.equ 0x9B73
;0x9B78 some hook
cursorHookPtr		.equ 0x9B7C
;0x9B80 some hook
rawKeyHookPtr		.equ 0x9B84
rawKeyHookPtrPage	.equ 0x9B86 ;1 byte - page hook is on
getKeyHookPtr		.equ 0x9B88
cxMainHookPtr		.equ 0x9B8C
;0x9B90 cxMain Wind/TblSet/TVMSol hook
;0x9B94 cxMain Graph hook
;0x9B98 cxMain y= hook
fontHookPtr		.equ 0x9B9C
;0x9BA0 graphing hook
;0x9BA4 graphics hook
;0x9BA8 tracer hook
parserHookPtr .equ 0x9BAC
;0x9BB0 app change hook
;0x9BB4 catalog hook
;0x9BB8 cxMain mode hook
;0x9BBC putaway hook
;0x9BC0 cxMain stat hook
;0x9BC4 catalog? hook ; are there two?
tokenHookPtr		.equ 0x9BC8
;0x9BCC character hook
restartClr		.equ 0x9BD0 ;link hook?
baseAppBrTab2		.equ 0x9C06 ;table of base pages for apps on page >=20; there are two because the SE added new pages.
localTokStr		.equ 0x9D65
keyForStr		.equ 0x9D76
keyToStrRam		.equ 0x9D77
sedMonSp		.equ 0x9D88
bpSave			.equ 0x9D8A
userMem			.equ 0x9D95
symTable		.equ 0xFE66

;System Flags
;----------------------------------------------------------------------
ioDelFlag		.equ 0x0
inDelete		.equ 0		;1 = DELETE SCREEN

trigFlags		.equ 0x0	;Trigonometry mode settings
trigDeg			.equ 2		;1=degrees, 0=radians

kbdFlags		.equ 0x0	;Keyboard scan
kbdSCR			.equ 3		;1=scan code ready
kbdKeyPress		.equ 4		;1=key has been pressed

doneFlags		.equ 0x0	;display "Done"
donePrgm		.equ 5		;1=display "Done" after prgm
;----------------------------------------------------------------------
editFlags		.equ 0x1
editOpen		.equ 2		;1=edit buffer is open

ansFlags		.equ 1
AnsScroll		.equ 3		;1=answer can scroll, seems must be reset in order to move about edit buffer

monFlags		.equ 0x1	 ;monitor flags
monAbandon		.equ 4		;1=don't start any long process in put away (#715)
;----------------------------------------------------------------------
plotFlags		.equ 0x2	;plot generation flags
plotLoc 		.equ 1		;0=bkup & display, 1=display only
plotDisp		.equ 2		;1=plot is in display, 0=text in display

grfModeFlags	.equ 0x2	;graph mode settings
grfFuncM		.equ 4		;1=function graph
grfPolarM		.equ 5		;1=polar graph
grfParamM		.equ 6		;1=parametric graph
grfRecurM		.equ 7		;1=RECURSION graph
;----------------------------------------------------------------------
graphFlags		.equ 0x3
graphDraw		.equ 0		;0=graph is valid, 1=redraw graph(dirty)
graphCursor		.equ 2
;----------------------------------------------------------------------
grfDBFlags		.equ 0x4
grfDot			.equ 0		;0=line, 1=dot
grfSimul		.equ 1		;0=sequential, 1=simultaneous
grfGrid 		.equ 2		;0=no grid, 1=grid
grfPolar		.equ 3		;0=rectangular, 1=polar coordinates
grfNoCoord		.equ 4		;0=display coordinates, 1=off
grfNoAxis		.equ 5		;0=axis, 1=no axis
grfLabel		.equ 6		;0=off, 1=axis label
;----------------------------------------------------------------------
textFlags		.equ 0x5	;Text output flags
textEraseBelow		.equ 1		;1=erase line below small char
textScrolled		.equ 2		;1=screen scrolled
textInverse		.equ 3		;1=display inverse bit-map
textInsMode		.equ 4		;0=overstrike, 1=insert mode
;----------------------------------------------------------------------
ParsFlag2		.equ 0x7	;PARSER flags
numOP1			.equ 0		;1=RESULT IN OP1, 0=NO RESULT
;----------------------------------------------------------------------
newDispF		.equ 0x8	;Derivative mode flags
preClrForMode		.equ 0		;1=HELP BLINK ON MODE SCREEN

apdFlags		.equ 0x8	;Automatic power-down
apdAble 		.equ 2		;1=APD enabled
apdRunning		.equ 3		;1=APD clock running
;----------------------------------------------------------------------
web_err_mask		.equ 0x60
;----------------------------------------------------------------------
onFlags 		.equ 0x9	;on key flags
onRunning		.equ 3		;1=calculator is running
onInterrupt		.equ 4		;1=on key interrupt request

statFlags		.equ 0x9	;statistics flags
statsValid		.equ 6		;1=stats are valid
;----------------------------------------------------------------------
fmtFlags		.equ 0x0A	;numeric format flags
fmtExponent		.equ 0	 	;1=show exponent, 0=no exponent
fmtEng			.equ 1	 	;1=engineering notion, 0=scientific
fmtHex			.equ 2	 	;1=hexadecimal
fmtOct			.equ 3	 	;1=octal
fmtBin			.equ 4	 	;1=binary

numMode			.equ 0x0A
fmtReal			.equ 5
fmtRect			.equ 6
fmtPolar		.equ 7

realMode		.equ 5
rectMode		.equ 6
polarMode		.equ 7
;					;if Hex and Oct both = 1
;					; then Bin=0 means >Frac
;					; Bin=1 means >DMS
fmtBaseMask		.equ  0b00011100	; mask to base flags
fmtBaseShift		.equ  2		; offset to base flags
;
;       CHECK IF THESE ARE USED BY NUMFORM,
;
;               	.equ  6
;               	.equ  7
;----------------------------------------------------------------------
fmtOverride		.equ 0x0B	;copy of fmtFlags with conversion override
;----------------------------------------------------------------------
fmtEditFlags		.equ 0x0C	;numeric editing flags
fmtEdit			.equ 0		;1=format number for editing

curFlags		.equ 0x0C	;Cursor
curAble 		.equ 2		;1=cursor flash is enabled
curOn			.equ 3		;1=cursor is showing
curLock 		.equ 4		;1=cursor is locked off

cmdFlags		.equ 0x0C	;command editor flags
cmdVirgin		.equ 5		;1=nothing has been typed in cmd bfr
;----------------------------------------------------------------------
appFlags		.equ 0x0D	;application flags
appWantIntrpt		.equ 0		;1=want ON key interrupts
appTextSave		.equ 1		;1=save characters in textShadow
appAutoScroll		.equ 2		;1=auto-scroll text on last line
appMenus		.equ 3		;1=process keys that bring up menus, 0=check Lock menu flag
appLockMenus		.equ 4		;1=ignore menu keys, 0=switch to home screen and bring up menu
appCurGraphic		.equ 5		;1=graphic cursor
appCurWord		.equ 6		;1=text cursor covers entire word
appExit 		.equ 7		;1=application handles [EXIT] key itself

appWantIntrptF		.equ 1<<appWantIntrpt
appTextSaveF		.equ 1<<appTextSave
appAutoScrollF		.equ 1<<appAutoScroll
appMenusF		.equ 1<<appMenus
appLockMenusF		.equ 1<<appLockMenus
appCurGraphicF		.equ 1<<appCurGraphic
appCurWordF		.equ 1<<appCurWord
appExitF		.equ 1<<appExit
;----------------------------------------------------------------------
seqFlags		.equ 0x0F	;Sequential Graph flags
webMode			.equ 0		;0 = NORMAL SEQ MODE, 1 = WEB MODE
webVert			.equ 1
sequv			.equ 2		;U vs V
seqvw			.equ 3		;V vs W
sequw			.equ 4		;U vs W
;----------------------------------------------------------------------
promptFlags		.equ 0x11	;prompt line flags
promptEdit		.equ 0		;1=editing in prompt buffer
;----------------------------------------------------------------------
indicFlags		.equ 0x12	;Indicator flags
indicRun		.equ 0		;1=run indicator ON
indicInUse		.equ 1		;indicator save area in use=1, free=0 ;resetting will disable 2nd while in _getkey
indicOnly		.equ 2		;interrupt handler only checks run indicator

shiftFlags		.equ 0x12	;[2nd] and [ALPHA] flags
shift2nd		.equ 3		;1=[2nd] has been pressed
shiftAlpha		.equ 4		;1=[ALPHA] has been pressed
shiftLwrAlph		.equ 5		;1=lower case, 0=upper case
shiftALock		.equ 6		;1=alpha lock has been pressed
shiftKeepAlph		.equ 7		;1=cannot cancel alpha shift
;----------------------------------------------------------------------
tblFlags		.equ 0x13	;table flags.
autoFill		.equ 4		;1=prompt, 0=fillAuto
autoCalc		.equ 5		;1=prompt, 0=CalcAuto
reTable			.equ 6		;0=table is ok, 1=must recompute table.
;----------------------------------------------------------------------
sGrFlags		.equ 0x14
grfSplit		.equ 0		;1=Split Graph, 0=Normal
vertSplit		.equ 1		;1=Vertical (left-right) Split
grfSChanged		.equ 2		;1=Graph just changed Split <-> normal
grfSplitOverride	.equ 3		;1 = ignore graph split flag if set
write_on_graph		.equ 4		;1 = TEXT OR .equ WRITING TO GRAPH SCREEN
g_style_active		.equ 5		;1 = GRAPH STYLES ARE ENABLED, USE THEM
cmp_mod_box		.equ 6		;1 = DOING MOD BOX PLOT COMPUTATION
textWrite		.equ 7
;----------------------------------------------------------------------
newIndicFlags		.equ 0x15
extraIndic		.equ 0
saIndic			.equ 1
;----------------------------------------------------------------------
smartFlags		.equ 0x17
smarter_mask		.equ 3
smarter_test		.equ 1
smartGraph		.equ 0
smartGraph_inv		.equ 1
;----------------------------------------------------------------------
varTypeMask		.equ 0x1F	;is this a flag byte?
varGraphRef		.equ 6
;----------------------------------------------------------------------
asm_Flag1		.equ 0x21	;ASM CODING
asm_Flag2		.equ 0x22	;ASM CODING
asm_Flag3		.equ 0x23	;ASM CODING
;----------------------------------------------------------------------
getSendFlg		.equ 0x24
comFailed		.equ 1		;1 = Get/Send Communication Failed

appLwrCaseFlag		.equ 0x24
lwrCaseActive		.equ 3
;----------------------------------------------------------------------
groupFlags		.equ 0x26
inGroup			.equ 1		;1 = IN GROUP CONTEXT
;----------------------------------------------------------------------
APIFlg			.equ 0x28
appAllowContext		.equ 0           ;App wants context changes to happen
;1 set to ignore a key after returning from rawkeyhook
;2 set to
;3
;4
;5
;6
;7 set if you wish _getkey to return koff instead of turning the calc off, see _GetKeyRetOff
;----------------------------------------------------------------------
apiFlg3			.equ 0x2A
;----------------------------------------------------------------------
apiFlg4			.equ 0x2B
fullScrnDraw		.equ 2		;DRAW INTO LAST ROW/COL OF SCREEN
;----------------------------------------------------------------------
xapFlag0		.equ 0x2E	;external app flags
xapFlag1		.equ 0x2F
xapFlag2		.equ 0x30
xapFlag3		.equ 0x31
;----------------------------------------------------------------------
fontFlags		.equ 0x32
fracDrawLFont		.equ 2
fracTallLFont		.equ 3
customFont		.equ 7
;----------------------------------------------------------------------
hookflags1		.equ 0x33
;----------------------------------------------------------------------
hookflags2		.equ 0x34
rawkeyflag		.equ 5
;----------------------------------------------------------------------
hookflags3		.equ 0x35
;----------------------------------------------------------------------
hookflags4		.equ 0x36
;----------------------------------------------------------------------
plotFlag3		.equ 0x3C
bufferOnly		.equ 0
useFastCirc		.equ 4

;Character Font Equates
;-------------------------------
LrecurN			.equ 0x001
LrecurU			.equ 0x002
LrecurV			.equ 0x003
LrecurW			.equ 0x004
Lconvert		.equ 0x005
LsqUp			.equ 0x006
LsqDown			.equ 0x007
Lintegral		.equ 0x008
Lcross			.equ 0x009
LboxIcon 		.equ 0x00A
LcrossIcon 		.equ 0x00B
LdotIcon 		.equ 0x00C
LsubT   		.equ 0x00D ;small capital T for parametric mode.
LcubeR  		.equ 0x00E ;slightly different 3 for cubed root.
LhexF			.equ 0x00F
Lroot			.equ 0x010
Linverse		.equ 0x011
Lsquare			.equ 0x012
Langle			.equ 0x013
Ldegree			.equ 0x014
Lradian			.equ 0x015
Ltranspose		.equ 0x016
LLE			.equ 0x017
LNE			.equ 0x018
LGE			.equ 0x019
Lneg			.equ 0x01A
Lexponent		.equ 0x01B
Lstore			.equ 0x01C
Lten			.equ 0x01D
LupArrow		.equ 0x01E
LdownArrow		.equ 0x01F
Lspace			.equ 0x020
Lexclam			.equ 0x021
Lquote			.equ 0x022
Lpound			.equ 0x023
Lfourth			.equ 0x024
Lpercent		.equ 0x025
Lampersand		.equ 0x026
Lapostrophe		.equ 0x027
LlParen			.equ 0x028
LrParen			.equ 0x029
Lasterisk		.equ 0x02A
LplusSign		.equ 0x02B
Lcomma			.equ 0x02C
Ldash			.equ 0x02D
Lperiod			.equ 0x02E
Lslash			.equ 0x02F
L0			.equ 0x030
L1			.equ 0x031
L2			.equ 0x032
L3			.equ 0x033
L4			.equ 0x034
L5			.equ 0x035
L6			.equ 0x036
L7			.equ 0x037
L8			.equ 0x038
L9			.equ 0x039
Lcolon			.equ 0x03A
Lsemicolon		.equ 0x03B
LLT			.equ 0x03C
LEQ			.equ 0x03D
LGT			.equ 0x03E
Lquestion		.equ 0x03F
LatSign			.equ 0x040
LcapA			.equ 0x041
LcapB			.equ 0x042
LcapC			.equ 0x043
LcapD			.equ 0x044
LcapE			.equ 0x045
LcapF			.equ 0x046
LcapG			.equ 0x047
LcapH			.equ 0x048
LcapI			.equ 0x049
LcapJ			.equ 0x04A
LcapK			.equ 0x04B
LcapL			.equ 0x04C
LcapM			.equ 0x04D
LcapN			.equ 0x04E
LcapO			.equ 0x04F
LcapP			.equ 0x050
LcapQ			.equ 0x051
LcapR			.equ 0x052
LcapS			.equ 0x053
LcapT			.equ 0x054
LcapU			.equ 0x055
LcapV			.equ 0x056
LcapW			.equ 0x057
LcapX			.equ 0x058
LcapY			.equ 0x059
LcapZ			.equ 0x05A
Ltheta			.equ 0x05B
Lbackslash		.equ 0x05C
LrBrack			.equ 0x05D
Lcaret			.equ 0x05E
Lunderscore		.equ 0x05F
Lbackquote		.equ 0x060
La			.equ 0x061
Lb			.equ 0x062
Lc			.equ 0x063
;; Ld			.equ 0x064 ; sdasz80 doesn't like this one
Le			.equ 0x065
Lf			.equ 0x066
Lg			.equ 0x067
Lh			.equ 0x068
Li			.equ 0x069
Lj			.equ 0x06A
Lk			.equ 0x06B
Ll			.equ 0x06C
Lm			.equ 0x06D
Ln			.equ 0x06E
Lo			.equ 0x06F
Lp			.equ 0x070
Lq			.equ 0x071
Lr			.equ 0x072
Ls			.equ 0x073
Lt			.equ 0x074
Lu			.equ 0x075
Lv			.equ 0x076
Lw			.equ 0x077
Lx			.equ 0x078
Ly			.equ 0x079
Lz			.equ 0x07A
LlBrace			.equ 0x07B
Lbar			.equ 0x07C
LrBrace			.equ 0x07D
Ltilde			.equ 0x07E
LinvEQ			.equ 0x07F
Lsub0			.equ 0x080
Lsub1			.equ 0x081
Lsub2			.equ 0x082
Lsub3			.equ 0x083
Lsub4			.equ 0x084
Lsub5			.equ 0x085
Lsub6			.equ 0x086
Lsub7			.equ 0x087
Lsub8			.equ 0x088
Lsub9			.equ 0x089
LcapAAcute		.equ 0x08A
LcapAGrave		.equ 0x08B
LcapACaret		.equ 0x08C
LcapADier		.equ 0x08D
LaAcute			.equ 0x08E
LaGrave			.equ 0x08F
LaCaret			.equ 0x090
LaDier			.equ 0x091
LcapEAcute		.equ 0x092
LcapEGrave		.equ 0x093
LcapECaret		.equ 0x094
LcapEDier		.equ 0x095
LeAcute			.equ 0x096
LeGrave			.equ 0x097
LeCaret			.equ 0x098
LeDier			.equ 0x099
LcapIAcute		.equ 0x09A
LcapIGrave		.equ 0x09B
LcapICaret		.equ 0x09C
LcapIDier		.equ 0x09D
LiAcute			.equ 0x09E
LiGrave			.equ 0x09F
LiCaret			.equ 0x0A0
LiDier			.equ 0x0A1
LcapOAcute		.equ 0x0A2
LcapOGrave		.equ 0x0A3
LcapOCaret		.equ 0x0A4
LcapODier		.equ 0x0A5
LoAcute			.equ 0x0A6
LoGrave			.equ 0x0A7
LoCaret			.equ 0x0A8
LoDier			.equ 0x0A9
LcapUAcute		.equ 0x0AA
LcapUGrave		.equ 0x0AB
LcapUCaret		.equ 0x0AC
LcapUDier		.equ 0x0AD
LuAcute			.equ 0x0AE
LuGrave			.equ 0x0AF
LuCaret			.equ 0x0B0
LuDier			.equ 0x0B1
LcapCCed		.equ 0x0B2
LcCed			.equ 0x0B3
LcapNTilde		.equ 0x0B4
LnTilde			.equ 0x0B5
Laccent			.equ 0x0B6
Lgrave			.equ 0x0B7
Ldieresis		.equ 0x0B8
LquesDown		.equ 0x0B9
LexclamDown		.equ 0x0BA
Lalpha			.equ 0x0BB
Lbeta			.equ 0x0BC
Lgamma			.equ 0x0BD
LcapDelta		.equ 0x0BE
Ldelta			.equ 0x0BF
Lepsilon		.equ 0x0C0
LlBrack 		.equ 0x0C1
Llambda			.equ 0x0C2
Lmu			.equ 0x0C3
Lpi			.equ 0x0C4
Lrho			.equ 0x0C5
LcapSigma		.equ 0x0C6
Lsigma			.equ 0x0C7
Ltau			.equ 0x0C8
Lphi			.equ 0x0C9
LcapOmega		.equ 0x0CA
LxMean			.equ 0x0CB
LyMean			.equ 0x0CC
LsupX			.equ 0x0CD
Lellipsis		.equ 0x0CE
Lleft			.equ 0x0CF
Lblock			.equ 0x0D0
Lper			.equ 0x0D1
Lhyphen			.equ 0x0D2
Larea			.equ 0x0D3
Ltemp			.equ 0x0D4
Lcube			.equ 0x0D5
Lenter			.equ 0x0D6
LimagI			.equ 0x0D7
Lphat			.equ 0x0D8
Lchi			.equ 0x0D9
LstatF			.equ 0x0DA
Llne			.equ 0x0DB
LlistL			.equ 0x0DC
LfinanN 		.equ 0x0DD
L2_r_paren 		.equ 0x0DE
LblockArrow     	.equ 0x0DF
LcurO   		.equ 0x0E0
LcurO2  		.equ 0x0E1
LcurOcapA       	.equ 0x0E2
LcurOa  		.equ 0x0E3
LcurI   		.equ 0x0E4
LcurI2  		.equ 0x0E5
LcurIcapA       	.equ 0x0E6
LcurIa  		.equ 0x0E7
LGline          	.equ 0x0E8 ; = 0
LGthick         	.equ 0x0E9 ; = 1
LGabove			.equ 0x0EA ; = 2
kRight			.equ 0x001
kLeft			.equ 0x002
kUp			.equ 0x003
kDown			.equ 0x004
kEnter			.equ 0x005
kAlphaEnter		.equ 0x006
kAlphaUp		.equ 0x007
kAlphaDown		.equ 0x008
kClear			.equ 0x009
kDel			.equ 0x00A
kIns			.equ 0x00B
kRecall			.equ 0x00C
kLastEnt		.equ 0x00D
kBOL			.equ 0x00E
kEOL			.equ 0x00F

kSelAll			.equ 0x010
kUnselAll		.equ 0x011
kLtoTI82		.equ 0x012
kBackup			.equ 0x013
kRecieve		.equ 0x014
kLnkQuit		.equ 0x015
kTrans			.equ 0x016
kRename			.equ 0x017
kOverw			.equ 0x018
kOmit			.equ 0x019
kCont			.equ 0x01A
kSendID			.equ 0x01B
kSendSW			.equ 0x01C
kYes			.equ 0x01D
kNoWay			.equ 0x01E
kvSendType		.equ 0x01F
kOverWAll		.equ 0x020
kNo			.equ 0x025
kKReset			.equ 0x026
kApp			.equ 0x027
kDoug			.equ 0x028
kListflag		.equ 0x029
menuStart		.equ 0x02B
kAreYouSure		.equ 0x02B
kAppsMenu		.equ 0x02C
kPrgm			.equ 0x02D
kZoom			.equ 0x02E
kDraw			.equ 0x02F
kSPlot			.equ 0x030
kStat			.equ 0x031
kMath			.equ 0x032
kTest			.equ 0x033
kChar			.equ 0x034
kVars			.equ 0x035
kMem			.equ 0x036
kMatrix			.equ 0x037
kDist			.equ 0x038
kAngle			.equ 0x039
kList			.equ 0x03A
kCalc			.equ 0x03B
kFin			.equ 0x03C
menuEnd			.equ kFin
kCatalog		.equ 0x03E
kInputDone		.equ 0x03F
kOff			.equ kInputDone
kQuit			.equ 0x040
appStart		.equ kQuit
kLinkIO			.equ 0x041
kMatrixEd		.equ 0x042
kStatEd			.equ 0x043
kGraph			.equ 0x044
kMode			.equ 0x045
kPrgmEd			.equ 0x046 ;PROGRAM EDIT
kPrgmCr			.equ 0x047 ;PROGRAM CREATE
kWindow			.equ 0x048 ;RANGE EDITOR
kYequ			.equ 0x049 ;EQUATION EDITOR
kTable			.equ 0x04A ;TABLE EDITOR
kTblSet			.equ 0x04B ;TABLE SET
kChkRAM			.equ 0x04C ;CHECK RAM
kDelMem			.equ 0x04D ;DELETE MEM
kResetMem		.equ 0x04E ;RESET MEM
kResetDef		.equ 0x04F ;RESET DEFAULT
kPrgmInput		.equ 0x050 ;PROGRAM INPUT
kZFactEd		.equ 0x051 ;ZOOM FACTOR EDITOR
kError			.equ 0x052 ;ERROR
kSolveTVM		.equ 0x053 ;TVM SOLVER
kSolveRoot		.equ 0x054 ;SOLVE EDITOR
kStatP			.equ 0x055 ;stat plot
kInfStat		.equ 0x056 ;Inferential Statistic
kFormat			.equ 0x057 ;FORMAT
kExtApps		.equ 0x058 ;External Applications.     NEW
kNewApps		.equ 0x059 ;New Apps for Cerberus.
append			.equ kNewApps
echoStart1		.equ 0x05A
kTrace			.equ 0x05A
kZFit			.equ 0x05B
kZIn			.equ 0x05C
kZOut			.equ 0x05D
kZPrev			.equ 0x05E
kBox			.equ 0x05F
kDecml			.equ 0x060
kSetZm			.equ 0x061
kSquar			.equ 0x062
kStd			.equ 0x063
kTrig			.equ 0x064
kUsrZm			.equ 0x065
kZSto			.equ 0x066
kZInt			.equ 0x067
kZStat			.equ 0x068
echoStart2		.equ 0x069
kSelect			.equ 0x069
kCircl			.equ 0x06A
kClDrw			.equ 0x06B
kLine			.equ 0x06C
kPen			.equ 0x06D
kPtChg			.equ 0x06E
kPtOff			.equ 0x06F
kPtOn			.equ 0x070
kVert			.equ 0x071
kHoriz			.equ 0x072
kText			.equ 0x073
kTanLn			.equ 0x074
kEval			.equ 0x075
kInters			.equ 0x076
kDYDX			.equ 0x077
kFnIntg			.equ 0x078
kRootG			.equ 0x079
kDYDT			.equ 0x07A
kDXDT			.equ 0x07B
kDRDo			.equ 0x07C
KGFMin			.equ 0x07D
KGFMax			.equ 0x07E
EchoStart		.equ 0x07F
kListName		.equ 0x07F
kAdd			.equ 0x080
kSub			.equ 0x081
kMul			.equ 0x082
kDiv			.equ 0x083
kExpon			.equ 0x084
kLParen			.equ 0x085
kRParen			.equ 0x086
kLBrack			.equ 0x087
kRBrack			.equ 0x088
kShade			.equ 0x089
kStore			.equ 0x08A
kComma			.equ 0x08B
kChs			.equ 0x08C
kDecPnt			.equ 0x08D
k0			.equ 0x08E
k1			.equ 0x08F
k2			.equ 0x090
k3			.equ 0x091
k4			.equ 0x092
k5			.equ 0x093
k6			.equ 0x094
k7			.equ 0x095
k8			.equ 0x096
k9			.equ 0x097
kEE			.equ 0x098
kSpace			.equ 0x099
kCapA			.equ 0x09A
kCapB			.equ 0x09B
kCapC			.equ 0x09C
kCapD			.equ 0x09D
kCapE			.equ 0x09E
kCapF			.equ 0x09F
kCapG			.equ 0x0A0
kCapH			.equ 0x0A1
kCapI			.equ 0x0A2
kCapJ			.equ 0x0A3
kCapK			.equ 0x0A4
kCapL			.equ 0x0A5
kCapM			.equ 0x0A6
kCapN			.equ 0x0A7
kCapO			.equ 0x0A8
kCapP			.equ 0x0A9
kCapQ			.equ 0x0AA
kCapR			.equ 0x0AB
kCapS			.equ 0x0AC
kCapT			.equ 0x0AD
kCapU			.equ 0x0AE
kCapV			.equ 0x0AF
kCapW			.equ 0x0B0
kCapX			.equ 0x0B1
kCapY			.equ 0x0B2
kCapZ			.equ 0x0B3
kVarx			.equ 0x0B4
kPi			.equ 0x0B5
kInv			.equ 0x0B6
kSin			.equ 0x0B7
kASin			.equ 0x0B8
kCos			.equ 0x0B9
kACos			.equ 0x0BA
kTan			.equ 0x0BB
kATan			.equ 0x0BC
kSquare			.equ 0x0BD
kSqrt			.equ 0x0BE
kLn			.equ 0x0BF
kExp			.equ 0x0C0
kLog			.equ 0x0C1
kALog			.equ 0x0C2
kToABC			.equ 0x0C3
kClrTbl			.equ 0x0C4
kAns			.equ 0x0C5
kColon			.equ 0x0C6
kNDeriv			.equ 0x0C7
kFnInt			.equ 0x0C8
kRoot			.equ 0x0C9
kQuest			.equ 0x0CA
kQuote			.equ 0x0CB
kTheta			.equ 0x0CC
kIf			.equ 0x0CD
kThen			.equ 0x0CE
kElse			.equ 0x0CF
kFor			.equ 0x0D0
kWhile			.equ 0x0D1
kRepeat			.equ 0x0D2
kEnd			.equ 0x0D3
kPause			.equ 0x0D4
kLbl			.equ 0x0D5
kGoto			.equ 0x0D6
kISG			.equ 0x0D7
kDSL			.equ 0x0D8
kMenu			.equ 0x0D9
kExec			.equ 0x0DA
kReturn			.equ 0x0DB
kStop			.equ 0x0DC
kInput			.equ 0x0DD
kPrompt			.equ 0x0DE
kDisp			.equ 0x0DF
kDispG			.equ 0x0E0
kDispT			.equ 0x0E1
kOutput			.equ 0x0E2
kGetKey			.equ 0x0E3
kClrHome		.equ 0x0E4
kPrtScr			.equ 0x0E5
kSinH			.equ 0x0E6
kCosH			.equ 0x0E7
kTanH			.equ 0x0E8
kASinH			.equ 0x0E9
kACosH			.equ 0x0EA
kATanH			.equ 0x0EB
kLBrace			.equ 0x0EC
kRBrace			.equ 0x0ED
kI			.equ 0x0EE
kCONSTeA		.equ 0x0EF
kPlot3			.equ 0x0F0
kFMin			.equ 0x0F1
kFMax			.equ 0x0F2
kL1A			.equ 0x0F3
kL2A			.equ 0x0F4
kL3A			.equ 0x0F5
kL4A			.equ 0x0F6
kL5A			.equ 0x0F7
kL6A			.equ 0x0F8
kunA			.equ 0x0F9
kvnA			.equ 0x0FA
kwnA			.equ 0x0FB

LGbelow			.equ 0x0EB ; = 3
LGpath			.equ 0x0EC ; = 4
LGanimate		.equ 0x0ED ; = 5
LGdot			.equ 0x0EE ; = 6
LUpBlk			.equ 0x0EF ;Up arrow and Block in solver
LDnBlk			.equ 0x0F0 ;Down arrow and Block in solver
LcurFull		.equ 0x0F1 ;note: must be last char (PutMap checks)

;Keypress Equates
;-------------------------------
kRight			.equ 0x001
kLeft			.equ 0x002
kUp			.equ 0x003
kDown			.equ 0x004
kEnter			.equ 0x005
kAlphaEnter		.equ 0x006
kAlphaUp		.equ 0x007
kAlphaDown		.equ 0x008
kClear			.equ 0x009
kDel			.equ 0x00A
kIns			.equ 0x00B
kRecall			.equ 0x00C
kLastEnt		.equ 0x00D
kBOL			.equ 0x00E
kEOL			.equ 0x00F

kSelAll			.equ 0x010
kUnselAll		.equ 0x011
kLtoTI82		.equ 0x012
kBackup			.equ 0x013
kRecieve		.equ 0x014
kLnkQuit		.equ 0x015
kTrans			.equ 0x016
kRename			.equ 0x017
kOverw			.equ 0x018
kOmit			.equ 0x019
kCont			.equ 0x01A
kSendID			.equ 0x01B
kSendSW			.equ 0x01C
kYes			.equ 0x01D
kNoWay			.equ 0x01E
kvSendType		.equ 0x01F
kOverWAll		.equ 0x020
kNo			.equ 0x025
kKReset			.equ 0x026
kApp			.equ 0x027
kDoug			.equ 0x028
kListflag		.equ 0x029
menuStart		.equ 0x02B
kAreYouSure		.equ 0x02B
kAppsMenu		.equ 0x02C
kPrgm			.equ 0x02D
kZoom			.equ 0x02E
kDraw			.equ 0x02F
kSPlot			.equ 0x030
kStat			.equ 0x031
kMath			.equ 0x032
kTest			.equ 0x033
kChar			.equ 0x034
kVars			.equ 0x035
kMem			.equ 0x036
kMatrix			.equ 0x037
kDist			.equ 0x038
kAngle			.equ 0x039
kList			.equ 0x03A
kCalc			.equ 0x03B
kFin			.equ 0x03C
menuEnd			.equ kFin
kCatalog		.equ 0x03E
kInputDone		.equ 0x03F
kOff			.equ kInputDone
kQuit			.equ 0x040
appStart		.equ kQuit
kLinkIO			.equ 0x041
kMatrixEd		.equ 0x042
kStatEd			.equ 0x043
kGraph			.equ 0x044
kMode			.equ 0x045
kPrgmEd			.equ 0x046 ;PROGRAM EDIT
kPrgmCr			.equ 0x047 ;PROGRAM CREATE
kWindow			.equ 0x048 ;RANGE EDITOR
kYequ			.equ 0x049 ;EQUATION EDITOR
kTable			.equ 0x04A ;TABLE EDITOR
kTblSet			.equ 0x04B ;TABLE SET
kChkRAM			.equ 0x04C ;CHECK RAM
kDelMem			.equ 0x04D ;DELETE MEM
kResetMem		.equ 0x04E ;RESET MEM
kResetDef		.equ 0x04F ;RESET DEFAULT
kPrgmInput		.equ 0x050 ;PROGRAM INPUT
kZFactEd		.equ 0x051 ;ZOOM FACTOR EDITOR
kError			.equ 0x052 ;ERROR
kSolveTVM		.equ 0x053 ;TVM SOLVER
kSolveRoot		.equ 0x054 ;SOLVE EDITOR
kStatP			.equ 0x055 ;stat plot
kInfStat		.equ 0x056 ;Inferential Statistic
kFormat			.equ 0x057 ;FORMAT
kExtApps		.equ 0x058 ;External Applications.     NEW
kNewApps		.equ 0x059 ;New Apps for Cerberus.
append			.equ kNewApps
echoStart1		.equ 0x05A
kTrace			.equ 0x05A
kZFit			.equ 0x05B
kZIn			.equ 0x05C
kZOut			.equ 0x05D
kZPrev			.equ 0x05E
kBox			.equ 0x05F
kDecml			.equ 0x060
kSetZm			.equ 0x061
kSquar			.equ 0x062
kStd			.equ 0x063
kTrig			.equ 0x064
kUsrZm			.equ 0x065
kZSto			.equ 0x066
kZInt			.equ 0x067
kZStat			.equ 0x068
echoStart2		.equ 0x069
kSelect			.equ 0x069
kCircl			.equ 0x06A
kClDrw			.equ 0x06B
kLine			.equ 0x06C
kPen			.equ 0x06D
kPtChg			.equ 0x06E
kPtOff			.equ 0x06F
kPtOn			.equ 0x070
kVert			.equ 0x071
kHoriz			.equ 0x072
kText			.equ 0x073
kTanLn			.equ 0x074
kEval			.equ 0x075
kInters			.equ 0x076
kDYDX			.equ 0x077
kFnIntg			.equ 0x078
kRootG			.equ 0x079
kDYDT			.equ 0x07A
kDXDT			.equ 0x07B
kDRDo			.equ 0x07C
KGFMin			.equ 0x07D
KGFMax			.equ 0x07E
EchoStart		.equ 0x07F
kListName		.equ 0x07F
kAdd			.equ 0x080
kSub			.equ 0x081
kMul			.equ 0x082
kDiv			.equ 0x083
kExpon			.equ 0x084
kLParen			.equ 0x085
kRParen			.equ 0x086
kLBrack			.equ 0x087
kRBrack			.equ 0x088
kShade			.equ 0x089
kStore			.equ 0x08A
kComma			.equ 0x08B
kChs			.equ 0x08C
kDecPnt			.equ 0x08D
k0			.equ 0x08E
k1			.equ 0x08F
k2			.equ 0x090
k3			.equ 0x091
k4			.equ 0x092
k5			.equ 0x093
k6			.equ 0x094
k7			.equ 0x095
k8			.equ 0x096
k9			.equ 0x097
kEE			.equ 0x098
kSpace			.equ 0x099
kCapA			.equ 0x09A
kCapB			.equ 0x09B
kCapC			.equ 0x09C
kCapD			.equ 0x09D
kCapE			.equ 0x09E
kCapF			.equ 0x09F
kCapG			.equ 0x0A0
kCapH			.equ 0x0A1
kCapI			.equ 0x0A2
kCapJ			.equ 0x0A3
kCapK			.equ 0x0A4
kCapL			.equ 0x0A5
kCapM			.equ 0x0A6
kCapN			.equ 0x0A7
kCapO			.equ 0x0A8
kCapP			.equ 0x0A9
kCapQ			.equ 0x0AA
kCapR			.equ 0x0AB
kCapS			.equ 0x0AC
kCapT			.equ 0x0AD
kCapU			.equ 0x0AE
kCapV			.equ 0x0AF
kCapW			.equ 0x0B0
kCapX			.equ 0x0B1
kCapY			.equ 0x0B2
kCapZ			.equ 0x0B3
kVarx			.equ 0x0B4
kPi			.equ 0x0B5
kInv			.equ 0x0B6
kSin			.equ 0x0B7
kASin			.equ 0x0B8
kCos			.equ 0x0B9
kACos			.equ 0x0BA
kTan			.equ 0x0BB
kATan			.equ 0x0BC
kSquare			.equ 0x0BD
kSqrt			.equ 0x0BE
kLn			.equ 0x0BF
kExp			.equ 0x0C0
kLog			.equ 0x0C1
kALog			.equ 0x0C2
kToABC			.equ 0x0C3
kClrTbl			.equ 0x0C4
kAns			.equ 0x0C5
kColon			.equ 0x0C6
kNDeriv			.equ 0x0C7
kFnInt			.equ 0x0C8
kRoot			.equ 0x0C9
kQuest			.equ 0x0CA
kQuote			.equ 0x0CB
kTheta			.equ 0x0CC
kIf			.equ 0x0CD
kThen			.equ 0x0CE
kElse			.equ 0x0CF
kFor			.equ 0x0D0
kWhile			.equ 0x0D1
kRepeat			.equ 0x0D2
kEnd			.equ 0x0D3
kPause			.equ 0x0D4
kLbl			.equ 0x0D5
kGoto			.equ 0x0D6
kISG			.equ 0x0D7
kDSL			.equ 0x0D8
kMenu			.equ 0x0D9
kExec			.equ 0x0DA
kReturn			.equ 0x0DB
kStop			.equ 0x0DC
kInput			.equ 0x0DD
kPrompt			.equ 0x0DE
kDisp			.equ 0x0DF
kDispG			.equ 0x0E0
kDispT			.equ 0x0E1
kOutput			.equ 0x0E2
kGetKey			.equ 0x0E3
kClrHome		.equ 0x0E4
kPrtScr			.equ 0x0E5
kSinH			.equ 0x0E6
kCosH			.equ 0x0E7
kTanH			.equ 0x0E8
kASinH			.equ 0x0E9
kACosH			.equ 0x0EA
kATanH			.equ 0x0EB
kLBrace			.equ 0x0EC
kRBrace			.equ 0x0ED
kI			.equ 0x0EE
kCONSTeA		.equ 0x0EF
kPlot3			.equ 0x0F0
kFMin			.equ 0x0F1
kFMax			.equ 0x0F2
kL1A			.equ 0x0F3
kL2A			.equ 0x0F4
kL3A			.equ 0x0F5
kL4A			.equ 0x0F6
kL5A			.equ 0x0F7
kL6A			.equ 0x0F8
kunA			.equ 0x0F9
kvnA			.equ 0x0FA
kwnA			.equ 0x0FB

;THIS KEY MEANS THAT IT IS A 2 BYTE KEYCODE
;THERE ARE 2 OF THESE KEYS; BE CAREFUL WITH USAGE
;------------------------------------------------
kExtendEcho2		.equ 0x0FC

;THIS KEY MEANS THAT THE KEY PRESS IS ONE THAT ECHOS
;INTO A BUFFER, AND IT IS A 2 BYTE KEY CODE, GO LOOK AT
;(EXTECHO) FOR THE KEY VALUE
;------------------------------------------------------
kExtendEcho		.equ 0x0FE

kE1BT			.equ 0
kDrawInv		.equ kE1BT
kDrawF			.equ kE1BT+1
kPixelOn		.equ kE1BT+2
kPixelOff		.equ kE1BT+3
kPxlTest		.equ kE1BT+4
kRCGDB			.equ kE1BT+5
kRCPic			.equ kE1BT+6
kSTGDB			.equ kE1BT+7
kSTPic			.equ kE1BT+8
kAbs			.equ kE1BT+9
kTEqu			.equ kE1BT+10 ;==
kTNoteQ			.equ kE1BT+11 ;<>
kTGT			.equ kE1BT+12 ;>
kTGTE			.equ kE1BT+13 ;>=
kTLT			.equ kE1BT+14 ;<
kTLTE			.equ kE1BT+15 ;<=
kAnd			.equ kE1BT+16
kOr			.equ kE1BT+17
kXor			.equ kE1BT+18
kNot			.equ kE1BT+19
kLR1			.equ kE1BT+20
kXRoot			.equ kE1BT+21
kCube			.equ kE1BT+22
kCbRt			.equ kE1BT+23 ;Cube ROOT
kToDec			.equ kE1BT+24
kCubicR			.equ kE1BT+25
kQuartR			.equ kE1BT+26
kPlot1			.equ kE1BT+27
kPlot2			.equ kE1BT+28
kRound			.equ kE1BT+29
kIPart			.equ kE1BT+30
kFPart			.equ kE1BT+31
kInt			.equ kE1BT+32
kRand			.equ kE1BT+33
kNPR			.equ kE1BT+34
kNCR			.equ kE1BT+35
kXFactorial		.equ kE1BT+36
kRad			.equ kE1BT+37
kDegr			.equ kE1BT+38 ;DEGREES CONV
kAPost			.equ kE1BT+39
kToDMS			.equ kE1BT+40
kRToPo			.equ kE1BT+41 ;R
kRToPr			.equ kE1BT+42
kPToRx			.equ kE1BT+43
kPToRy			.equ kE1BT+44
kRowSwap		.equ kE1BT+45
kRowPlus		.equ kE1BT+46
kTimRow			.equ kE1BT+47
kTRowP			.equ kE1BT+48
kSortA			.equ kE1BT+49
kSortD			.equ kE1BT+50
kSeq			.equ kE1BT+51
kMin			.equ kE1BT+52
kMax			.equ kE1BT+53
kMean			.equ kE1BT+54
kMedian			.equ kE1BT+55
kSum			.equ kE1BT+56
kProd			.equ kE1BT+57
kDet			.equ kE1BT+58
kTransp			.equ kE1BT+59
kDim			.equ kE1BT+60
kFill			.equ kE1BT+61
kIdent			.equ kE1BT+62
kRandm			.equ kE1BT+63
kAug			.equ kE1BT+64
kOneVar			.equ kE1BT+65
kTwoVar			.equ kE1BT+66
kLR			.equ kE1BT+67
kLRExp			.equ kE1BT+68
kLRLn			.equ kE1BT+69
kLRPwr			.equ kE1BT+70
kMedMed			.equ kE1BT+71
kQuad			.equ kE1BT+72
kClrLst			.equ kE1BT+73
kHist			.equ kE1BT+74
kxyLine			.equ kE1BT+75
kScatter		.equ kE1BT+76
kmRad			.equ kE1BT+77
kmDeg			.equ kE1BT+78
kmNormF			.equ kE1BT+79
kmSci			.equ kE1BT+80
kmEng			.equ kE1BT+81
kmFloat			.equ kE1BT+82
kFix			.equ kE1BT+83
kSplitOn		.equ kE1BT+84
kFullScreen		.equ kE1BT+85
kStndrd			.equ kE1BT+86
kParam			.equ kE1BT+87
kPolar			.equ kE1BT+88
kSeqG			.equ kE1BT+89
kAFillOn		.equ kE1BT+90
kAFillOff		.equ kE1BT+91
kACalcOn		.equ kE1BT+92
kACalcOff		.equ kE1BT+93
kFNOn			.equ kE1BT+94
kFNOff			.equ kE1BT+95
kPlotsOn		.equ kE1BT+96
kPlotsOff		.equ kE1BT+97
kPixelChg		.equ kE1BT+98
kSendMBL		.equ kE1BT+99
kRecvMBL		.equ kE1BT+100
kBoxPlot		.equ kE1BT+101
kBoxIcon		.equ kE1BT+102
kCrossIcon		.equ kE1BT+103
kDotIcon		.equ kE1BT+104
kE2BT			.equ kE1BT+105
kSeqential		.equ kE2BT
kSimulG			.equ kE2BT+1
kPolarG			.equ kE2BT+2
kRectG			.equ kE2BT+3
kCoordOn		.equ kE2BT+4
kCoordOff		.equ kE2BT+5
kDrawLine		.equ kE2BT+6
kDrawDot		.equ kE2BT+7
kAxisOn			.equ kE2BT+8
kAxisOff		.equ kE2BT+9
kGridOn			.equ kE2BT+10
kGridOff		.equ kE2BT+11
kLblOn			.equ kE2BT+12
kLblOff			.equ kE2BT+13
kL1			.equ kE2BT+14
kL2			.equ kE2BT+15
kL3			.equ kE2BT+16
kL4			.equ kE2BT+17
kL5			.equ kE2BT+18
kL6			.equ kE2BT+19

;These keys are laid on top of existing keys to
;enable localization in the inferential stats editor.
;----------------------------------------------------
kinfData		.equ kL1
kinfStats		.equ kL1+1
kinfYes			.equ kL1+2
kinfNo			.equ kL1+3
kinfCalc		.equ kL1+4
kinfDraw		.equ kL1+5
kinfAlt1ne		.equ kL1+6
kinfAlt1lt		.equ kL1+7
kinfAlt1gt		.equ kL1+8
kinfAlt2ne		.equ kL1+9
kinfAlt2lt		.equ kL1+10
kinfAlt2gt		.equ kL1+11
kinfAlt3ne		.equ kL1+12
kinfAlt3lt		.equ kL1+13
kinfAlt3gt		.equ kL1+14
kinfAlt4ne		.equ kL1+15
kinfAlt4lt		.equ kL1+16
kinfAlt4gt		.equ kL1+17
kinfAlt5ne		.equ kL1+18
kinfAlt5lt		.equ kL1+19
kinfAlt5gt		.equ kL1+20
kinfAlt6ne		.equ kL1+21
kinfAlt6lt		.equ kL1+22
kinfAlt6gt		.equ kL1+23
kMatA			.equ kE2BT+20
kMatB			.equ kE2BT+21
kMatC			.equ kE2BT+22
kMatD			.equ kE2BT+23
kMatE			.equ kE2BT+24
kXmin			.equ kE2BT+25
kXmax			.equ kE2BT+26
kXscl			.equ kE2BT+27
kYmin			.equ kE2BT+28
kYmax			.equ kE2BT+29
kYscl			.equ kE2BT+30
kTmin			.equ kE2BT+31
kTmax			.equ kE2BT+32
kTStep			.equ kE2BT+33
kOmin			.equ kE2BT+34
kOmax			.equ kE2BT+35
kOStep			.equ kE2BT+36
ku0			.equ kE2BT+37
kv0			.equ kE2BT+38
knMin			.equ kE2BT+39
knMax			.equ kE2BT+40
kDeltaY			.equ kE2BT+41
kDeltaX			.equ kE2BT+42
kZXmin			.equ kE2BT+43
kZXmax			.equ kE2BT+44
kZXscl			.equ kE2BT+45
kZYmin			.equ kE2BT+46
kZYmax			.equ kE2BT+47
kZYscl			.equ kE2BT+48
kZTmin			.equ kE2BT+49
kZTmax			.equ kE2BT+50
kZTStep			.equ kE2BT+51
kZOmin			.equ kE2BT+52
kZOmax			.equ kE2BT+53
kZOStep			.equ kE2BT+54
kZu0			.equ kE2BT+55
kZv0			.equ kE2BT+56
kZnMin			.equ kE2BT+57
kZnMax			.equ kE2BT+58
kDelLast		.equ kE2BT+59
kSinReg			.equ kE2BT+60
kConstE			.equ kE2BT+61
kPic1			.equ kE2BT+62
kPic2			.equ kE2BT+63
kPic3			.equ kE2BT+64
kDelVar			.equ kE2BT+65
kGetCalc		.equ kE2BT+66
kRealM			.equ kE2BT+67
kPolarM			.equ kE2BT+68
kRectM			.equ kE2BT+69
kuv			.equ kE2BT+70 ;U vs V
kvw			.equ kE2BT+71 ;V vs W
kuw			.equ kE2BT+72 ;U vs W
kFinPMTend		.equ kE2BT+73
kFinPMTbeg		.equ kE2BT+74
kGraphStyle		.equ kE2BT+75
kExprOn			.equ kE2BT+76
kExprOff		.equ kE2BT+77
kStatA			.equ kE2BT+78
kStatB			.equ kE2BT+79
kStatC			.equ kE2BT+80
kCorr			.equ kE2BT+81
kStatD			.equ kE2BT+82
kStatE			.equ kE2BT+83
kRegEq			.equ kE2BT+84
kMinX			.equ kE2BT+85
kQ1			.equ kE2BT+86
kMD			.equ kE2BT+87
kQ3			.equ kE2BT+88
kMaxX			.equ kE2BT+89
kStatX1			.equ kE2BT+90
kStatY1			.equ kE2BT+91
kStatX2			.equ kE2BT+92
kStatY2			.equ kE2BT+93
kStatX3			.equ kE2BT+94
kStatY3			.equ kE2BT+95
kTblMin			.equ kE2BT+96
kTblStep		.equ kE2BT+97
kSetupLst		.equ kE2BT+98
kClrAllLst		.equ kE2BT+99
kLogistic		.equ kE2BT+100
kZTest			.equ kE2BT+101
kTTest			.equ kE2BT+102
k2SampZTest		.equ kE2BT+103
k2SampTTest		.equ kE2BT+104
k1PropZTest		.equ kE2BT+105
k2PropZTest		.equ kE2BT+106
kChiTest		.equ kE2BT+107
k2SampFTest		.equ kE2BT+108
kZIntVal		.equ kE2BT+109
kTIntVal		.equ kE2BT+110
k2SampTInt		.equ kE2BT+111
k2SampZInt		.equ kE2BT+112
k1PropZInt		.equ kE2BT+113
k2PropZInt		.equ kE2BT+114
kDNormal		.equ kE2BT+115
kInvNorm		.equ kE2BT+116
kDT			.equ kE2BT+117
kChi			.equ kE2BT+118
kDF			.equ kE2BT+119
kBinPDF			.equ kE2BT+120
kBinCDF			.equ kE2BT+121
kPoiPDF			.equ kE2BT+122
kPoiCDF			.equ kE2BT+123
kun			.equ kE2BT+124
kvn			.equ kE2BT+125
kwn			.equ kE2BT+126
kRecn			.equ kE2BT+127
kPlotStart		.equ kE2BT+128
kZPlotStart		.equ kE2BT+129 ;recursion n
kXFact			.equ kE2BT+130 ;PlotStart
kYFact			.equ kE2BT+131 ;ZPlotStart
kANOVA			.equ kE2BT+132 ;XFact
kMaxY			.equ kE2BT+133 ;YFact
kWebOn			.equ kE2BT+134 ;MinY
kWebOff			.equ kE2BT+135 ;MaxY
kTblInput		.equ kE2BT+136 ;WEB ON
kGeoPDF			.equ kE2BT+137 ;WEB OFF
kGeoCDF			.equ kE2BT+138 ;WEB OFF
kShadeNorm		.equ kE2BT+139
kShadeT			.equ kE2BT+140
kSh0xadeCi		.equ kE2BT+141
kShadeF			.equ kE2BT+142
kPlotStep		.equ kE2BT+143
kZPlotStep		.equ kE2BT+144
kLinRegtTest		.equ kE2BT+145
KMGT			.equ kE2BT+146 ;VERT SPLIT
kSelectA		.equ kE2BT+147
kZFitA			.equ kE2BT+148
kE2BT_End		.equ kZFitA

;More 2 Byte Keys
;------------------------------------
kE2BT2			.equ 0
kGDB1			.equ kE2BT2
kGDB2			.equ kE2BT2+1
kGDB3			.equ kE2BT2+2
kY1			.equ kE2BT2+3
kY2			.equ kE2BT2+4
kY3			.equ kE2BT2+5
kY4			.equ kE2BT2+6
kY5			.equ kE2BT2+7
kY6			.equ kE2BT2+8
kY7			.equ kE2BT2+9
kY8			.equ kE2BT2+10
kY9			.equ kE2BT2+11
kY0			.equ kE2BT2+12
kX1T			.equ kE2BT2+13
kY1T			.equ kE2BT2+14
kX2T			.equ kE2BT2+15
kY2T			.equ kE2BT2+16
kX3T			.equ kE2BT2+17
kY3T			.equ kE2BT2+18
kX4T			.equ kE2BT2+19
kY4T			.equ kE2BT2+20
kX5T			.equ kE2BT2+21
kY5T			.equ kE2BT2+22
kX6T			.equ kE2BT2+23
kY6T			.equ kE2BT2+24
kR1			.equ kE2BT2+25
kR2			.equ kE2BT2+26
kR3			.equ kE2BT2+27
kR4			.equ kE2BT2+28
kR5			.equ kE2BT2+29
kR6			.equ kE2BT2+30
kGDB4			.equ kE2BT2+31
kGDB5			.equ kE2BT2+32
kGDB6			.equ kE2BT2+33
kPic4			.equ kE2BT2+34
kPic5			.equ kE2BT2+35
kPic6			.equ kE2BT2+36
kGDB7			.equ kE2BT2+37
kGDB8			.equ kE2BT2+38
kGDB9			.equ kE2BT2+39
kGDB0			.equ kE2BT2+40
kPic7			.equ kE2BT2+41
kPic8			.equ kE2BT2+42
kPic9			.equ kE2BT2+43
kPic0			.equ kE2BT2+44
kStatN			.equ kE2BT2+45
kXMean			.equ kE2BT2+46
kConj			.equ kE2BT2+47
kReal			.equ kE2BT2+48
kFAngle			.equ kE2BT2+49
kLCM			.equ kE2BT2+50
kGCD			.equ kE2BT2+51
kRandInt		.equ kE2BT2+52
kRandNorm		.equ kE2BT2+53
kToPolar		.equ kE2BT2+54
kToRect			.equ kE2BT2+55
kYMean			.equ kE2BT2+56
kStdX			.equ kE2BT2+57
kStdX1			.equ kE2BT2+58
kw0			.equ kE2BT2+59
kMatF			.equ kE2BT2+60
kMatG			.equ kE2BT2+61
kMatRH			.equ kE2BT2+62
kMatI			.equ kE2BT2+63
kMatJ			.equ kE2BT2+64
kYMean1			.equ kE2BT2+65
kStdY			.equ kE2BT2+66
kStdY1			.equ kE2BT2+67
kMatToLst		.equ kE2BT2+68
kLstToMat		.equ kE2BT2+69
kCumSum			.equ kE2BT2+70
kDeltaLst		.equ kE2BT2+71
kStdDev			.equ kE2BT2+72
kVariance		.equ kE2BT2+73
kLength			.equ kE2BT2+74
kEquToStrng		.equ kE2BT2+75
kStrngToEqu		.equ kE2BT2+76
kExpr			.equ kE2BT2+77
kSubStrng		.equ kE2BT2+78
kInStrng		.equ kE2BT2+79
kStr1			.equ kE2BT2+80
kStr2			.equ kE2BT2+81
kStr3			.equ kE2BT2+82
kStr4           	.equ kE2BT2+83
kStr5           	.equ kE2BT2+84
kStr6           	.equ kE2BT2+85
kStr7           	.equ kE2BT2+86
kStr8           	.equ kE2BT2+87
kStr9           	.equ kE2BT2+88
kStr0           	.equ kE2BT2+89
kFinN           	.equ kE2BT2+90
kFinI           	.equ kE2BT2+91
kFinPV          	.equ kE2BT2+92
kFinPMT         	.equ kE2BT2+93
kFinFV          	.equ kE2BT2+94
kFinPY          	.equ kE2BT2+95
kFinCY          	.equ kE2BT2+96
kFinFPMT        	.equ kE2BT2+97
kFinFI          	.equ kE2BT2+98
kFinFPV         	.equ kE2BT2+99
kFinFN          	.equ kE2BT2+100
kFinFFV         	.equ kE2BT2+101
kFinNPV         	.equ kE2BT2+102
kFinIRR         	.equ kE2BT2+103
kFinBAL         	.equ kE2BT2+104
kFinPRN         	.equ kE2BT2+105
kFinINT         	.equ kE2BT2+106
kSumX           	.equ kE2BT2+107
kSumX2          	.equ kE2BT2+108
kFinToNom       	.equ kE2BT2+109
kFinToEff       	.equ kE2BT2+110
kFinDBD         	.equ kE2BT2+111
kStatVP         	.equ kE2BT2+112
kStatZ          	.equ kE2BT2+113
kStatT          	.equ kE2BT2+114
kStatChi        	.equ kE2BT2+115
kStatF          	.equ kE2BT2+116
kStatDF         	.equ kE2BT2+117
kStatPhat       	.equ kE2BT2+118
kStatPhat1      	.equ kE2BT2+119
kStatPhat2      	.equ kE2BT2+120
kStatMeanX1     	.equ kE2BT2+121
kStatMeanX2     	.equ kE2BT2+122
kStatStdX1      	.equ kE2BT2+123
kStatStdX2      	.equ kE2BT2+124
kStatStdXP		.equ kE2BT2+125
kStatN1			.equ kE2BT2+126
kStatN2			.equ kE2BT2+127
kStatLower		.equ kE2BT2+128
kStatUpper		.equ kE2BT2+129
kuw0			.equ kE2BT2+130
kImag			.equ kE2BT2+131
kSumY			.equ kE2BT2+132
kXres			.equ kE2BT2+133
kStat_s			.equ kE2BT2+134
kSumY2			.equ kE2BT2+135
kSumXY			.equ kE2BT2+136
kuXres			.equ kE2BT2+137
kModBox			.equ kE2BT2+138
kNormProb		.equ kE2BT2+139
kNormalPDF		.equ kE2BT2+140
kTPDF			.equ kE2BT2+141
kChiPDF			.equ kE2BT2+142
kFPDF			.equ kE2BT2+143
kMinY			.equ kE2BT2+144 ;MinY
kRandBin		.equ kE2BT2+145
kRef			.equ kE2BT2+146
kRRef			.equ kE2BT2+147
kLRSqr			.equ kE2BT2+148
kBRSqr			.equ kE2BT2+149
kDiagOn			.equ kE2BT2+150
kDiagOff		.equ kE2BT2+151
kun1			.equ kE2BT2+152 ;FOR RCL USE WHEN GOTTEN FROM 82
kvn1			.equ kE2BT2+153 ;FOR RCL USE WHEN GOTTEN FROM 82
k83_00End		.equ kvn1 ;end of original keys...
kArchive		.equ k83_00End + 1
kUnarchive		.equ k83_00End + 2
kAsm			.equ k83_00End + 3 ;Asm(
kAsmPrgm		.equ k83_00End + 4 ;AsmPrgm
kAsmComp		.equ k83_00End + 5 ;AsmComp(
kcapAAcute		.equ k83_00End + 6
kcapAGrave		.equ k83_00End + 7
kcapACaret		.equ k83_00End + 8
kcapADier		.equ k83_00End + 9
kaAcute			.equ k83_00End + 10
kaGrave			.equ k83_00End + 11
kaCaret			.equ k83_00End + 12
kaDier			.equ k83_00End + 13
kcapEAcute		.equ k83_00End + 14
kcapEGrave		.equ k83_00End + 15
kcapECaret		.equ k83_00End + 16
kcapEDier		.equ k83_00End + 17
keAcute			.equ k83_00End + 18
keGrave			.equ k83_00End + 19
keCaret			.equ k83_00End + 20
keDier			.equ k83_00End + 21
kcapIAcute		.equ k83_00End + 22
kcapIGrave		.equ k83_00End + 23
kcapICaret		.equ k83_00End + 24
kcapIDier		.equ k83_00End + 25
kiAcute			.equ k83_00End + 26
kiGrave			.equ k83_00End + 27
kiCaret			.equ k83_00End + 28
kiDier			.equ k83_00End + 29
kcapOAcute		.equ k83_00End + 30
kcapOGrave		.equ k83_00End + 31
kcapOCaret		.equ k83_00End + 32
kcapODier		.equ k83_00End + 33
koAcute			.equ k83_00End + 34
koGrave			.equ k83_00End + 35
koCaret			.equ k83_00End + 36
koDier			.equ k83_00End + 37
kcapUAcute		.equ k83_00End + 38
kcapUGrave		.equ k83_00End + 39
kcapUCaret		.equ k83_00End + 40
kcapUDier		.equ k83_00End + 41
kuAcute			.equ k83_00End + 42
kuGrave			.equ k83_00End + 43
kuCaret			.equ k83_00End + 44
kuDier			.equ k83_00End + 45
kcapCCed		.equ k83_00End + 46
kcCed			.equ k83_00End + 47
kcapNTilde		.equ k83_00End + 48
knTilde			.equ k83_00End + 49
kaccent			.equ k83_00End + 50
kgrave			.equ k83_00End + 51
kdieresis		.equ k83_00End + 52
kquesDown		.equ k83_00End + 53
kexclamDown     	.equ k83_00End + 54
kalpha          	.equ k83_00End + 55
kbeta           	.equ k83_00End + 56
kgamma          	.equ k83_00End + 57
kcapDelta		.equ k83_00End + 58
kdelta			.equ k83_00End + 59
kepsilon		.equ k83_00End + 60
klambda			.equ k83_00End + 61
kmu			.equ k83_00End + 62
kpi2			.equ k83_00End + 63
krho			.equ k83_00End + 64
kcapSigma		.equ k83_00End + 65
ksigma			.equ k83_00End + 66
ktau			.equ k83_00End + 67
kphi			.equ k83_00End + 68
kcapOmega		.equ k83_00End + 69
kphat			.equ k83_00End + 70
kchi2			.equ k83_00End + 71
kstatF2			.equ k83_00End + 72
kLa			.equ k83_00End + 73
kLb			.equ k83_00End + 74
kLc			.equ k83_00End + 75
kLd			.equ k83_00End + 76
kLe			.equ k83_00End + 77
kLf			.equ k83_00End + 78
kLg			.equ k83_00End + 79
kLh			.equ k83_00End + 80
kLi			.equ k83_00End + 81
kLj			.equ k83_00End + 82
kLk			.equ k83_00End + 83
kLl			.equ k83_00End + 84
kLm			.equ k83_00End + 85
kLsmalln		.equ k83_00End + 86
kLo			.equ k83_00End + 87
kLp			.equ k83_00End + 88
kLq			.equ k83_00End + 89
kLsmallr		.equ k83_00End + 90
kLs			.equ k83_00End + 91
kLt			.equ k83_00End + 92
kLu			.equ k83_00End + 93
kLv			.equ k83_00End + 94
kLw			.equ k83_00End + 95
kLx			.equ k83_00End + 96
kLy			.equ k83_00End + 97
kLz			.equ k83_00End + 98
kGarbageC		.equ k83_00End + 99 ;GarbageCollect
kE2BT2_End		.equ kGarbageC

;TI-83 Plus Context Equates
;---------------------------------------------
cxCmd			.equ kQuit ;home screen
cxMatEdit		.equ kMatrixEd ;matrix editor
cxPrgmEdit		.equ kPrgmEd ;program editor
cxEquEdit		.equ kYequ ;equation editor
cxGrRange		.equ kWindow ;graph range editor
cxGrZfact		.equ kZFactEd ;graph zoom factors editor
cxGraph			.equ kGraph ;graph mode
cxStatEdit		.equ kStatEd ;statistics list editor
cxPrgmInput		.equ kPrgmInput ;programmed input
cxError			.equ kError ;error handler
cxLinkIO		.equ kLinkIO ;LINK I/O interface
cxMem			.equ kResetMem ;reset memory
cxDefMem		.equ kResetDef ;reset default
cxRAMApp		.equ kChkRAM ;RAM usage screen
cxMode			.equ kMode ;mode settings screen
cxErase			.equ kDelMem ;memory erase
cxPrgmCreate		.equ kPrgmCr ;PROGRAM CREATE
cxTableEditor		.equ kTable ;TABLE EDITOR
cxTableSet		.equ kTblSet ;TABLE SET UP
cxStatPlot		.equ kStatP ;STAT PLOTS
cxInfStat		.equ kInfStat ;Inferential Statistic
cxFormat		.equ kFormat ;FORMAT CONTEXT
cxSolveTVM		.equ kSolveTVM ;Solve TVM
cxSolveRoot		.equ kSolveRoot ;Solve Root
lastOldApp		.equ kExtApps ;external applications
cxextapps		.equ kExtApps
cxNewApps		.equ kNewApps ;new cerberus applications
cxGroup			.equ cxNewApps+0 ;1st new app.
cxUnGroup		.equ cxNewApps+1 ;2nd new app.
lastNewApp		.equ cxUnGroup ;last new app for this ver

;Scan Code Equates
;-------------------------------
skDown			.equ 0x01
skLeft			.equ 0x02
skRight			.equ 0x03
skUp			.equ 0x04
skEnter			.equ 0x09
skAdd			.equ 0x0A
skSub			.equ 0x0B
skMul			.equ 0x0C
skDiv			.equ 0x0D
skPower			.equ 0x0E
skClear			.equ 0x0F
skChs			.equ 0x11
sk3			.equ 0x12
sk6			.equ 0x13
sk9			.equ 0x14
skRParen		.equ 0x15
skTan			.equ 0x16
skVars			.equ 0x17
skDecPnt		.equ 0x19
sk2			.equ 0x1A
sk5			.equ 0x1B
sk8			.equ 0x1C
skLParen		.equ 0x1D
skCos			.equ 0x1E
skPrgm			.equ 0x1F
skStat			.equ 0x20
sk0			.equ 0x21
sk1			.equ 0x22
sk4			.equ 0x23
sk7			.equ 0x24
skComma			.equ 0x25
skSin			.equ 0x26
skMatrix		.equ 0x27
skGraphvar		.equ 0x28
skStore			.equ 0x2A
skLn			.equ 0x2B
skLog			.equ 0x2C
skSquare		.equ 0x2D
skRecip			.equ 0x2E
skMath			.equ 0x2F
skAlpha			.equ 0x30
skGraph			.equ 0x31
skTrace			.equ 0x32
skZoom			.equ 0x33
skWindow		.equ 0x34
skYEqu			.equ 0x35
sk2nd			.equ 0x36
skMode			.equ 0x37
skDel			.equ 0x38

;Tokens
;----------------------------------------------------
EOSSTART		.equ 0

;DISPLAY CONVERSIONS COME IMMEDIATELY BEFORE 'TSTORE'
;
DCONV			.equ 0x01
;
tToDMS			.equ DCONV ;0x01
tToDEC			.equ DCONV+1 ;0x02
tToAbc			.equ DCONV+2 ;0x03 > A b/c
;
tStore			.equ DCONV+3 ;0x04 Lstore 01
;
tBoxPlot		.equ 0x05
;
BRACKS			.equ 0x06
;
tLBrack			.equ BRACKS ;0x06 '['
tRBrack			.equ BRACKS+1 ;0x07 ']'
tLBrace			.equ BRACKS+2 ;0x08 '{'
tRBrace			.equ BRACKS+3 ;0x09 '}'
;
tPOST1			.equ BRACKS+4
;
tFromRad		.equ tPOST1 ;0x0A Lradian
tFromDeg		.equ tPOST1+1 ;0x0B Ldegree
tRecip			.equ tPOST1+2 ;0x0C Linverse
tSqr			.equ tPOST1+3 ;0x0D Lsquare
tTrnspos		.equ tPOST1+4 ;0x0E Ltranspose
tCube			.equ tPOST1+5 ;0x0F '^3'
;
tLParen			.equ 0x10 ;0x10 '('
tRParen			.equ 0x11 ;0x11 ')'
;
IMUN			.equ 0x12
;
tRound			.equ IMUN ;0x12 'round'
tPxTst			.equ IMUN+1 ;0x13 'PXL-TEST'
tAug			.equ IMUN+2 ;0x14 'aug'
tRowSwap		.equ IMUN+3 ;0x15 'rSwap'
tRowPlus		.equ IMUN+4 ;0x16 'rAdd'
tmRow			.equ IMUN+5 ;0x17 'multR'
tmRowPlus		.equ IMUN+6 ;0x18 'mRAdd'
tMax			.equ IMUN+7 ;0x19 'max'
tMin			.equ IMUN+8 ;0x1A 'min'
tRToPr			.equ IMUN+9 ;0x1B 'R>Pr
tRToPo			.equ IMUN+10 ;0x1C 'R>Po
tPToRx			.equ IMUN+11 ;0x1D 'P>Rx
tPToRy			.equ IMUN+12 ;0x1E 'P>Ry
tMedian			.equ IMUN+13 ;0x1F 'MEDIAN
tRandM			.equ IMUN+14 ;0x20 'randM'
tMean			.equ IMUN+15 ;0x21
tRoot			.equ IMUN+16 ;0x22 'ROOT'
tSeries			.equ IMUN+17 ;0x23 'seq'
tFnInt			.equ IMUN+18 ;0x24 'fnInt'
tNDeriv			.equ IMUN+19 ;0x25 'fnIr'
tEvalF			.equ IMUN+20 ;0x26
tFmin			.equ IMUN+21 ;0x27
tFmax			.equ IMUN+22 ;0x28
;
tEOSEL			.equ IMUN+23
;
tSpace			.equ tEOSEL ;0x29 ' '
tString			.equ tEOSEL+1 ;0x2A '"'
tComma			.equ tEOSEL+2 ;0x2B ','
;
tii			.equ 0x2C ;i

;Postfix Functions
;-----------------------------------------
tPost			.equ 0x2D
;
tFact			.equ tPost ;0x2D '!'
;
tCubicR			.equ 0x2E
tQuartR			.equ 0x2F

;Number Tokens
;---------------------------------------
NUMS			.equ 0x30
;
t0			.equ NUMS ;0x30
t1			.equ NUMS+1 ;0x31
t2			.equ NUMS+2 ;0x32
t3			.equ NUMS+3 ;0x33
t4			.equ NUMS+4 ;0x34
t5			.equ NUMS+5 ;0x35
t6			.equ NUMS+6 ;0x36
t7			.equ NUMS+7 ;0x37
t8			.equ NUMS+8 ;0x38
t9			.equ NUMS+9 ;0x39
tDecPt			.equ NUMS+10 ;0x3A
tee			.equ NUMS+11 ;0x3B

;Binary OP
;-------------------------------------------
tOr			.equ 0x3C ;0x3C '_or_'
tXor			.equ 0x3D ;0x3D
;
tColon			.equ 0x3E ;0x3E ':'
tEnter			.equ 0x3F ;0x3F Lenter
;
tAnd			.equ 0x40 ;0x40 '_and_'

;Letter Tokens
;--------------------------------------
LET			.equ 0x41
tA			.equ LET ;0x41
tB			.equ LET+1 ;0x42
tC			.equ LET+2 ;0x43
tD			.equ LET+3 ;0x44
tE			.equ LET+4 ;0x45
tF			.equ LET+5 ;0x46
tG			.equ LET+6 ;0x47
tH			.equ LET+7 ;0x48
tI			.equ LET+8 ;0x49
tJ			.equ LET+9 ;0x4A
tK			.equ LET+10 ;0x4B
tL			.equ LET+11 ;0x4C
tM			.equ LET+12 ;0x4D
tN			.equ LET+13 ;0x4E
tO			.equ LET+14 ;0x4F
tP			.equ LET+15 ;0x50
tQ			.equ LET+16 ;0x51
tR			.equ LET+17 ;0x52
tS			.equ LET+18 ;0x53
tT			.equ LET+19 ;0x54
tU			.equ LET+20 ;0x55
tV			.equ LET+21 ;0x56
tW			.equ LET+22 ;0x57
tX			.equ LET+23 ;0x58
tY			.equ LET+24 ;0x59
tZ			.equ LET+25 ;0x5A
tTheta			.equ LET+26 ;0x5B

;These Var Tokens Are 1st Of A Double Token
;------------------------------------------

vToks			.equ LET+27

;User Matrix Token, 2nd Token Needed For Name
;
tVarMat			.equ vToks ;0x5C
;
;User List Token, 2nd Token Needed For Name
;
tVarLst			.equ vToks+1 ;0x5D
;
;User Equation Token, 2nd Token Needed For Name
;
tVarEqu			.equ vToks+2 ;0x5E
tProg			.equ vToks+3 ;0x5F
;
;User Pict Token, 2nd Token Needed For Name
;
tVarPict		.equ vToks+4 ;0x60
;
;User GDB Token, 2nd Token Needed For Name
;
tVarGDB			.equ vToks+5 ;0x61
tVarOut			.equ vToks+6 ;0x62
tVarSys			.equ vToks+7 ;0x63

;Mode Setting Commands
;-------------------------------------------------
MODESA			.equ vToks+8 ;0x64
tRad			.equ MODESA ;0x64 'Radian'
tDeg			.equ MODESA+1 ;0x65 'Degree'
tNormF			.equ MODESA+2 ;0x66 'Normal'
tSci			.equ MODESA+3 ;0x67 'Sci'
tEng			.equ MODESA+4 ;0x68 'Eng'
tFloat			.equ MODESA+5 ;0x69 'Float'
CMPS			.equ 0x6A
tEQ			.equ CMPS ;0x6A '=='
tLT			.equ CMPS+1 ;0x6B '<'
tGT			.equ CMPS+2 ;0x6C '>'
tLE			.equ CMPS+3 ;0x6D LLE
tGE			.equ CMPS+4 ;0x6E LGE
tNE			.equ CMPS+5 ;0x6F LNE

;Binary OP
;---------------------------------------
tAdd			.equ 0x70 ;0x70 '+'
tSub			.equ 0x71 ;0x71 '-'
tAns			.equ 0x72 ;0x72

;Mode Setting Commands
;-------------------------------------------------------
MODES			.equ 0x73
tFix			.equ MODES ;0x73 'Fix_'
tSplitOn		.equ MODES+1 ;0x74
tFullScreen		.equ MODES+2 ;0x75
tStndrd			.equ MODES+3 ;0x76 'Func'
tParam			.equ MODES+4 ;0x77 'Param'
tPolar			.equ MODES+5 ;0x78 'Pol'
tSeqG			.equ MODES+6 ;0x79
tAFillOn		.equ MODES+7 ;0x7A 'AUTO FILL ON'
tAFillOff		.equ MODES+8 ;0x7B
tACalcOn		.equ MODES+9 ;0x7C
tACalcOff		.equ MODES+10 ;0x7D 'AutoFill OFF'

;Graph Format Tokens Are 2 Byte Tokens
;----------------------------------------
tGFormat		.equ MODES+11 ;0x7E
tBoxIcon		.equ 0x7F
tCrossIcon		.equ 0x80
tDotIcon		.equ 0x81

;(More) Binary OP
;---------------------------------------
tMul			.equ 0x82 ;0x82 '*'
tDiv			.equ 0x83 ;0x83 '/'

;Some Graph Commands
;------------------------------------------------------
GRCMDS			.equ 0x84
tTrace			.equ GRCMDS ; 0x84 'Trace'
tClDrw			.equ GRCMDS+1 ; 0x85 'ClDrw'
tZoomStd		.equ GRCMDS+2 ; 0x86 'ZStd'
tZoomtrg		.equ GRCMDS+3 ; 0x87 'Ztrg'
tZoomBox		.equ GRCMDS+4 ; 0x88 'ZBOX'
tZoomIn			.equ GRCMDS+5 ; 0x89 'ZIn'
tZoomOut		.equ GRCMDS+6 ; 0x8A 'ZOut'
tZoomSqr		.equ GRCMDS+7 ; 0x8B 'ZSqr'
tZoomInt		.equ GRCMDS+8 ; 0x8C 'ZInt'
tZoomPrev		.equ GRCMDS+9 ; 0x8D 'ZPrev'
tZoomDec		.equ GRCMDS+10 ; 0x8E 'ZDecm'
tZoomStat		.equ GRCMDS+11 ; 0x8F 'ZStat
tUsrZm			.equ GRCMDS+12 ; 0x90 'ZRcl'
tPrtScrn		.equ GRCMDS+13 ; 0x91 'PrtScrn'
tZoomSto		.equ GRCMDS+14 ; 0x92  ZOOM STORE
tText			.equ GRCMDS+15 ; 0x93

;Binary OP (Combination & Permutation)
;-------------------------------------------------
tnPr			.equ GRCMDS+16 ;0x94 '_nPr_'
tnCr			.equ GRCMDS+17 ;0x95 '_nCr_'

;More Graph Commands
;--------------------------------------------------
tYOn			.equ GRCMDS+18 ;0x96 'FnOn_'
tYOff			.equ GRCMDS+19 ;0x97 'FnOff_'
tStPic			.equ GRCMDS+20 ;0x98 'StPic_'
tRcPic			.equ GRCMDS+21 ;0x99 'RcPic_'
tStoDB			.equ GRCMDS+22 ;0x9A 'StGDB_'
tRclDB			.equ GRCMDS+23 ;0x9B 'RcGDB_'
tLine			.equ GRCMDS+24 ;0x9C 'Line'
tVert			.equ GRCMDS+25 ;0x9D 'Vert_'
tPtOn			.equ GRCMDS+26 ;0x9E 'PtOn'
tPtOff			.equ GRCMDS+27 ;0x9F 'PtOff'

;Token A0 Cannot Be An EOS Function Since Low MULT=A0 Already
;------------------------------------------------------------
tPtChg			.equ GRCMDS+28 ;0xA0 'PtChg'
tPXOn			.equ GRCMDS+29 ;0xA1
tPXOff			.equ GRCMDS+30 ;0xA2
tPXChg			.equ GRCMDS+31 ;0xA3
tShade			.equ GRCMDS+32 ;0xA4 'Shade'
tCircl			.equ GRCMDS+33 ;0xA5 'Circl'
tHorz			.equ GRCMDS+34 ;0xA6 'HORIZONTAL'
tTanLn			.equ GRCMDS+35 ;0xA7 'TanLn'
tDrInv			.equ GRCMDS+36 ;0xA8 'DrInv_'
tDrawF			.equ GRCMDS+37 ;0xA9 'DrawF_'
tVarStrng		.equ 0x0AA

;Functions with No Arguments
;--------------------------------------------------
NOARG			.equ 0x0AB
tRand			.equ NOARG ;0xAB 'rand'
tPi			.equ NOARG+1 ;0xAC  Lpi
tGetKey			.equ NOARG+2 ;0xAD 'getKy'
tAPost			.equ tGetKey+1 ;APOSTROPHY
tQuest			.equ tAPost+1 ;QUESTION MARK
UNARY			.equ tQuest+1 ;0xB0
tChs			.equ UNARY ;0xB0
tInt			.equ UNARY+1 ;0xB1
tAbs			.equ UNARY+2 ;0xB2
tDet			.equ UNARY+3 ;0xB3
tIdent			.equ UNARY+4 ;0xB4
tDim			.equ UNARY+5 ;0xB5
tSum			.equ UNARY+6 ;0xB6
tProd			.equ UNARY+7 ;0xB7
tNot			.equ UNARY+8 ;0xB8
tIPart			.equ UNARY+9 ;0xB9
tFPart			.equ UNARY+10 ;0xBA

;New 2 Byte Tokens
;------------------------------------------
t2ByteTok		.equ 0x0BB
UNARYLR			.equ UNARY+12
tSqrt			.equ UNARYLR ;0xBC
tCubRt			.equ UNARYLR+1 ;0xBD
tLn			.equ UNARYLR+2 ;0xBE
tExp			.equ UNARYLR+3 ;0xBF
tLog			.equ UNARYLR+4 ;0xC0
tALog			.equ UNARYLR+5 ;0xC1
tSin			.equ UNARYLR+6 ;0xC2
tASin			.equ UNARYLR+7 ;0xC3
tCos			.equ UNARYLR+8 ;0xC4
tACos			.equ UNARYLR+9 ;0xC5
tTan			.equ UNARYLR+10 ;0xC6
tATan			.equ UNARYLR+11 ;0xC7
tSinH			.equ UNARYLR+12 ;0xC8
tASinH			.equ UNARYLR+13 ;0xC9
tCoshH			.equ UNARYLR+14 ;0xCA
tACosH			.equ UNARYLR+15 ;0xCB
tTanH			.equ UNARYLR+16 ;0xCC
tATanH			.equ UNARYLR+17 ;0xCD

;Some Programming Commands
;------------------------------------------------------
PROGTOK			.equ UNARYLR+18
tIf			.equ PROGTOK ;0xCE
tThen			.equ PROGTOK+1 ;0xCF
tElse			.equ PROGTOK+2 ;0xD0
tWhile			.equ PROGTOK+3 ;0xD1
tRepeat			.equ PROGTOK+4 ;0xD2
tFor			.equ PROGTOK+5 ;0xD3
tEnd			.equ PROGTOK+6 ;0xD4
tReturn			.equ PROGTOK+7 ;0xD5
tLbl			.equ PROGTOK+8 ;0xD6 'Lbl_'
tGoto			.equ PROGTOK+9 ;0xD7 'Goto_'
tPause			.equ PROGTOK+10 ;0xD8 'Pause_'
tStop			.equ PROGTOK+11 ;0xD9 'Stop'
tISG			.equ PROGTOK+12 ;0xDA 'IS>'
tDSL			.equ PROGTOK+13 ;0xDB 'DS<'
tInput			.equ PROGTOK+14 ;0xDC 'Input_'
tPrompt			.equ PROGTOK+15 ;0xDD 'Prompt_'
tDisp			.equ PROGTOK+16 ;0xDE 'Disp_'
tDispG			.equ PROGTOK+17 ;0xDF 'DispG'
tOutput			.equ PROGTOK+18 ;0xE0 'Outpt'
tClLCD			.equ PROGTOK+19 ;0xE1 'ClLCD'
tConst			.equ PROGTOK+20 ;0xE2 'Fill'
tSortA			.equ PROGTOK+21 ;0xE3 'sortA_'
tSortD			.equ PROGTOK+22 ;0xE4 'sortD_'
tDispTab		.equ PROGTOK+23 ;0xE5 'Disp Table
tMenu			.equ PROGTOK+24 ;0xE6 'Menu'
tSendMBL		.equ PROGTOK+25 ;0xE7 'SEND'
tGetMBL			.equ PROGTOK+26 ;0xE8 'GET'

;Stat Plot Commands
;------------------------------------------------------
statPCmd		.equ PROGTOK+27
tPlotOn			.equ statPCmd ;0xE9 ' PLOTSON'
tPlotOff		.equ statPCmd+1 ;0xEA ' PLOTSOFF
tListName		.equ 0x0EB ;LIST DESIGNATOR
tPlot1			.equ 0x0EC
tPlot2			.equ 0x0ED
tPlot3			.equ 0x0EE
tUnused01		.equ 0x0EF ;available?
tPower			.equ 0x0F0 ;'^'
tXRoot			.equ 0x0F1 ;LsupX,Lroot
STATCMD			.equ 0x0F2
tOneVar			.equ STATCMD ;0xF2 'OneVar_'
tTwoVar			.equ STATCMD+1 ;0xF3
tLR			.equ STATCMD+2 ;0xF4 'LinR(A+BX
tLRExp			.equ STATCMD+3 ;0xF5 'ExpR_'
tLRLn			.equ STATCMD+4 ;0xF6 'LnR_'
tLRPwr			.equ STATCMD+5 ;0xF7 'PwrR_'
tMedMed			.equ STATCMD+6 ;0xF8
tQuad			.equ STATCMD+7 ;0xF9
tClrLst			.equ STATCMD+8 ;0xFA 'CLEAR LIST
tClrTbl			.equ STATCMD+9 ;0xFB CLEAR TABLE
tHist			.equ STATCMD+10 ;0xFC 'Hist_'
txyLine			.equ STATCMD+11 ;0xFD 'xyline_'
tScatter		.equ STATCMD+12 ;0xFE 'Scatter_'
tLR1			.equ STATCMD+13 ;0xFF 'LINR(AX+B

;2nd Half Of Graph Format Tokens
;----------------------------------------------
;           Format settings commands
;
GFMT			.equ 0
tSeq			.equ GFMT ; 'SeqG'
tSimulG			.equ GFMT+1 ; 'SimulG'
tPolarG			.equ GFMT+2 ; 'PolarGC'
tRectG			.equ GFMT+3 ; 'RectGC'
tCoordOn		.equ GFMT+4 ; 'CoordOn'
tCoordOff		.equ GFMT+5 ; 'CoordOff'
tDrawLine		.equ GFMT+6 ; 'DrawLine'
tDrawDot		.equ GFMT+7 ; 'DrawDot'
tAxisOn			.equ GFMT+8 ; 'AxesOn'
tAxisOff		.equ GFMT+9 ; 'AxesOff'
tGridOn			.equ GFMT+10 ; 'GridOn'
tGridOff		.equ GFMT+11 ; 'GridOff'
tLblOn			.equ GFMT+12 ; 'LabelOn'
tLblOff			.equ GFMT+13 ; 'LabelOff'
tWebOn			.equ GFMT+14 ; 'WebOn'
tWebOff			.equ GFMT+15 ; 'WebOFF'
tuv			.equ GFMT+16 ; U vs V
tvw			.equ GFMT+17 ; V vs W
tuw			.equ GFMT+18 ; U vs W

;2nd Half Of User Matrix Tokens
;-------------------------------------
tMatA			.equ 0x00 ;MAT A
tMatB			.equ 0x01 ;MAT B
tMatC			.equ 0x02 ;MAT C
tMatD			.equ 0x03 ;MAT D
tMatE			.equ 0x04 ;MAT E
tMatF			.equ 0x05 ;MAT F
tMatG			.equ 0x06 ;MAT G
tMatH			.equ 0x07 ;MAT H
tMatI			.equ 0x08 ;MAT I
tMatJ			.equ 0x09 ;MAT J

;2nd Half Of User List Tokens
;--------------------------------------
tL1			.equ 0x00 ;LIST 1
tL2			.equ 0x01 ;LIST 2
tL3			.equ 0x02 ;LIST 3
tL4			.equ 0x03 ;LIST 4
tL5			.equ 0x04 ;LIST 5
tL6			.equ 0x05 ;LIST 6

;2nd Half Of User Equation Tokens
;----------------------------------
;  "Y" EQUATIONS HAVE BIT 4 SET
;
tY1			.equ 0x10 ;Y1
tY2			.equ 0x11 ;Y2
tY3			.equ 0x12 ;Y3
tY4			.equ 0x13 ;Y4
tY5			.equ 0x14 ;Y5
tY6			.equ 0x15 ;Y6
tY7			.equ 0x16 ;Y7
tY8			.equ 0x17 ;Y8
tY9			.equ 0x18 ;Y9
tY0			.equ 0x19 ;Y0

;Param Equations Have Bit 5 Set
;-----------------------------------
tX1T			.equ 0x20 ;X1t
tY1T			.equ 0x21 ;Y1t
tX2T			.equ 0x22 ;X2t
tY2T			.equ 0x23 ;Y2t
tX3T			.equ 0x24 ;X3t
tY3T			.equ 0x25 ;Y3t
tX4T			.equ 0x26 ;X4t
tY4T			.equ 0x27 ;Y4t
tX5T			.equ 0x28 ;X5t
tY5T			.equ 0x29 ;Y5t
tX6T			.equ 0x2A ;X6t
tY6T			.equ 0x2B ;Y6t

;Polar Equations Have Bit 6 Set
;----------------------------------
tR1			.equ 0x40 ;R1
tR2			.equ 0x41 ;R2
tR3			.equ 0x42 ;R3
tR4			.equ 0x43 ;R4
tR5			.equ 0x44 ;R5
tR6			.equ 0x45 ;R6

;Recursion Equations Have Bit 7 Set
;----------------------------------
tun			.equ 0x80 ;Un
tvn			.equ 0x81 ;Vn
twn			.equ 0x82 ;Wn

;2nd Half Of User Picture Tokens
;------------------------------------
tPic1			.equ 0x00 ;PIC1
tPic2			.equ 0x01 ;PIC2
tPic3			.equ 0x02 ;PIC3
tPic4			.equ 0x03 ;PIC4
tPic5			.equ 0x04 ;PIC5
tPic6			.equ 0x05 ;PIC6
tPic7			.equ 0x06 ;PIC7
tPic8			.equ 0x07 ;PIC8
tPic9			.equ 0x08 ;PIC9
tPic0			.equ 0x09 ;PIC0

;2nd Half Of User Graph Database Tokens
;--------------------------------------
tGDB1			.equ 0x00 ;GDB1
tGDB2			.equ 0x01 ;GDB2
tGDB3			.equ 0x02 ;GDB3
tGDB4			.equ 0x03 ;GDB4
tGDB5			.equ 0x04 ;GDB5
tGDB6			.equ 0x05 ;GDB6
tGDB7			.equ 0x06 ;GDB7
tGDB8			.equ 0x07 ;GDB8
tGDB9			.equ 0x08 ;GDB9
tGDB0			.equ 0x09 ;GDB0

;2nd Half Of String Vars
;------------------------------
tStr1			.equ 0x00
tStr2			.equ 0x01
tStr3			.equ 0x02
tStr4			.equ 0x03
tStr5			.equ 0x04
tStr6			.equ 0x05
tStr7			.equ 0x06
tStr8			.equ 0x07
tStr9			.equ 0x08
tStr0			.equ 0x09

;2nd Half Of System Output Only Variables
;-----------------------------------------------------------------
;OPEN			.equ 0x00
tRegEq			.equ 0x01 ;REGRESSION EQUATION
tStatN			.equ 0x02 ;STATISTICS N
tXMean			.equ 0x03 ;X MEAN
tSumX			.equ 0x04 ;SUM(X)
tSumXSqr		.equ 0x05 ;SUM(X^2)
tStdX			.equ 0x06 ;STANDARD DEV X
tStdPX			.equ 0x07 ;STANDARD DEV POP X
tMinX			.equ 0x08 ;Min X VALUE
tMaxX			.equ 0x09 ;Max X VALUE
tMinY			.equ 0x0A ;Min Y VALUE
tMaxY			.equ 0x0B ;Max Y VALUE
tYmean			.equ 0x0C ;Y MEAN
tSumY			.equ 0x0D ;SUM(Y)
tSumYSqr		.equ 0x0E ;SUM(Y^2)
tStdY			.equ 0x0F ;STANDARD DEV Y
tStdPY			.equ 0x10 ;STANDARD DEV POP Y
tSumXY			.equ 0x11 ;SUM(XY)
tCorr			.equ 0x12 ;CORRELATION
tMedX			.equ 0x13 ;MED(X)
tQ1			.equ 0x14 ;1ST QUADRANT OF X
tQ3			.equ 0x15 ;3RD QUADRANT OF X
tQuadA			.equ 0x16 ;1ST TERM OF QUAD POLY REG/ Y-INT
tQuadB			.equ 0x17 ;2ND TERM OF QUAD POLY REG/ SLOPE
tQuadC			.equ 0x18 ;3RD TERM OF QUAD POLY REG
tCubeD			.equ 0x19 ;4TH TERM OF CUBIC POLY REG
tQuartE			.equ 0x1A ;5TH TERM OF QUART POLY REG
tMedX1			.equ 0x1B ;x1 FOR MED-MED
tMedX2			.equ 0x1C ;x2 FOR MED-MED
tMedX3			.equ 0x1D ;x3 FOR MED-MED
tMedY1			.equ 0x1E ;y1 FOR MED-MED
tMedY2			.equ 0x1F ;y2 FOR MED-MED
tMedY3			.equ 0x20 ;y3 FOR MED-MED
tRecurn			.equ 0x21	;RECURSION N
tStatP			.equ 0x22
tStatZ			.equ 0x23
tStatT			.equ 0x24
tStatChi		.equ 0x25
tStatF			.equ 0x26
tStatDF			.equ 0x27
tStatPhat		.equ 0x28
tStatPhat1		.equ 0x29
tStatPhat2		.equ 0x2A
tStatMeanX1		.equ 0x2B
tStatStdX1		.equ 0x2C
tStatN1			.equ 0x2D
tStatMeanX2		.equ 0x2E
tStatStdX2		.equ 0x2F
tStatN2			.equ 0x30
tStatStdXP		.equ 0x31
tStatLower		.equ 0x32
tStatUpper		.equ 0x33
tStat_s			.equ 0x34
tLRSqr			.equ 0x35 ;r^2
tBRSqr			.equ 0x36 ;R^2

;These next tokens are only used to access the data
;they are display only and the user cannot access them at all
;------------------------------------------------------------
tF_DF			.equ 0x37 ;ANOFAV FACTOR DF
tF_SS			.equ 0x38 ;ANOFAV FACTOR SS
tF_MS			.equ 0x39 ;ANOFAV FACTOR MS
tE_DF			.equ 0x3A ;ANOFAV ERROR DF
tE_SS			.equ 0x3B ;ANOFAV ERROR SS
tE_MS			.equ 0x3C ;ANOFAV ERROR MS

;2nd Half Of System Input/Output Variables
;------------------------------------------------
;      SYSTEM VARIABLE EQUATES
;
tuXscl			.equ 0
tuYscl			.equ 1
tXscl			.equ 2
tYscl			.equ 3
tRecuru0		.equ 4 ;U 1ST INITIAL COND
tRecurv0		.equ 5 ;V 1ST INITIAL COND
tun1			.equ 6 ;U(N-1); NOT USED
tvn1			.equ 7 ;V(N-1); NOT USED
tuRecuru0		.equ 8 ;
tuRecurv0		.equ 9 ;
tXmin			.equ 0x0A
tXmax			.equ 0x0B
tYmin			.equ 0x0C
tYmax			.equ 0x0D
tTmin			.equ 0x0E
tTmax			.equ 0x0F
tThetaMin		.equ 0x10
tThetaMax		.equ 0x11
tuXmin			.equ 0x12
tuXmax			.equ 0x13
tuYmin			.equ 0x14
tuYmax			.equ 0x15
tuThetMin		.equ 0x16
tuThetMax		.equ 0x17
tuTmin			.equ 0x18
tuTmax			.equ 0x19
tTblMin			.equ 0x1A
tPlotStart		.equ 0x1B
tuPlotStart		.equ 0x1C
tnMax			.equ 0x1D
tunMax			.equ 0x1E
tnMin			.equ 0x1F
tunMin			.equ 0x20
tTblStep		.equ 0x21
tTStep			.equ 0x22
tThetaStep		.equ 0x23
tuTStep			.equ 0x24
tuThetStep		.equ 0x25
tDeltaX			.equ 0x26
tDeltaY			.equ 0x27
tXFact			.equ 0x28
tYFact			.equ 0x29
tTblInput		.equ 0x2A
tFinN			.equ 0x2B
tFinI			.equ 0x2C
tFinPV			.equ 0x2D
tFinPMT			.equ 0x2E
tFinFV			.equ 0x2F
tFinPY			.equ 0x30
tFinCY			.equ 0x31
tRecurw0		.equ 0x32 ;w0(1)
tuRecurw0		.equ 0x33
tPlotStep		.equ 0x34
tuPlotStep		.equ 0x35
tXres			.equ 0x36
tuXres			.equ 0x37
tRecuru02		.equ 0x38 ;u0(2)
tuRecuru02		.equ 0x39
tRecurv02		.equ 0x3C ;v0(2)
tuRecurv02		.equ 0x3D
tRecurw02		.equ 0x3E ;w0(2)
tuRecurw02		.equ 0x3F

;2nd Byte Of t2ByteTok Tokens
;------------------------------
tFinNPV			.equ 0x00
tFinIRR			.equ 0x01
tFinBAL			.equ 0x02
tFinPRN			.equ 0x03
tFinINT			.equ 0x04
tFinToNom		.equ 0x05
tFinToEff		.equ 0x06
tFinDBD			.equ 0x07
tLCM			.equ 0x08
tGCD			.equ 0x09
tRandInt		.equ 0x0A
tRandBin		.equ 0x0B
tSubStrng		.equ 0x0C
tStdDev			.equ 0x0D
tVariance		.equ 0x0E
tInStrng		.equ 0x0F
tDNormal		.equ 0x10
tInvNorm		.equ 0x11
tDT			.equ 0x12
tChI			.equ 0x13
tDF			.equ 0x14
tBINPDF			.equ 0x15
tBINCDF			.equ 0x16
tPOIPDF			.equ 0x17
tPOICDF			.equ 0x18
tGEOPDF			.equ 0x19
tGEOCDF			.equ 0x1A
tNormalPDF		.equ 0x1B
tTPDF			.equ 0x1C
tChiPDF			.equ 0x1D
tFPDF			.equ 0x1E
tRandNorm		.equ 0x1F
tFinFPMT		.equ 0x20
tFinFI			.equ 0x21
tFinFPV			.equ 0x22
tFinFN			.equ 0x23
tFinFFV			.equ 0x24
tConj			.equ 0x25
tReal			.equ 0x26
tImag			.equ 0x27
tAngle			.equ 0x28
tCumSum			.equ 0x29
tExpr			.equ 0x2A
tLength			.equ 0x2B
tDeltaLst		.equ 0x2C
tRef			.equ 0x2D
tRRef			.equ 0x2E
tToRect			.equ 0x2F
tToPolar		.equ 0x30
tConste			.equ 0x31
tSinReg			.equ 0x32
tLogistic		.equ 0x33
tLinRegTTest		.equ 0x34
tShadeNorm		.equ 0x35
tShadeT			.equ 0x36
tSh0xadeCi		.equ 0x37
tShadeF			.equ 0x38
tMatToLst		.equ 0x39
tLstToMat		.equ 0x3A
tZTest			.equ 0x3B
tTTest			.equ 0x3C
t2SampZTest		.equ 0x3D
t1PropZTest		.equ 0x3E
t2PropZTest		.equ 0x3F
tChiTest		.equ 0x40
tZIntVal		.equ 0x41
t2SampZInt		.equ 0x42
t1PropZInt		.equ 0x43
t2PropZInt		.equ 0x44
tGraphStyle		.equ 0x45
t2SampTTest		.equ 0x46
t2SampFTest		.equ 0x47
tTIntVal		.equ 0x48
t2SampTInt		.equ 0x49
tSetupLst		.equ 0x4A
tFinPMTend		.equ 0x4B
tFinPMTbeg		.equ 0x4C
tRealM			.equ 0x4D
tPolarM			.equ 0x4E
tRectM			.equ 0x4F
tExprOn			.equ 0x50
tExprOff		.equ 0x51
tClrAllLst		.equ 0x52
tGetCalc		.equ 0x53
tDelVar			.equ 0x54
tEquToStrng		.equ 0x55
tStrngToEqu		.equ 0x56
tDelLast		.equ 0x57
tSelect			.equ 0x58
tANOVA			.equ 0x59
tModBox			.equ 0x5A
tNormProb		.equ 0x5B
tMGT			.equ 0x64 ;VERTICAL SPLIT
tZFit			.equ 0x65 ;ZOOM FIT
tDiag_on		.equ 0x66 ;DIANOSTIC DISPLAY ON
tDiag_off		.equ 0x67 ;DIANOSTIC DISPLAY OFF
tOkEnd2v0		.equ 0x67 ;end of 2byte tokens for version 0.
tArchive		.equ 0x68 ;archive
tUnarchive		.equ 0x69 ;unarchive
tasm			.equ 0x6A
tasmComp		.equ 0x6B	;asm compile
tasmPrgm		.equ 0x6C	;signifies a program is asm
tasmCmp			.equ 0x6D	;asm program is compiled
tLcapAAcute		.equ 0x6E
tLcapAGrave		.equ 0x6F
tLcapACaret		.equ 0x70
tLcapADier		.equ 0x71
tLaAcute		.equ 0x72
tLaGrave		.equ 0x73
tLaCaret		.equ 0x74
tLaDier			.equ 0x75
tLcapEAcute		.equ 0x76
tLcapEGrave		.equ 0x77
tLcapECaret		.equ 0x78
tLcapEDier		.equ 0x79
tLeAcute		.equ 0x7A
tLeGrave		.equ 0x7B
tLeCaret		.equ 0x7C
tLeDier			.equ 0x7D
tLcapIGrave		.equ 0x7F
tLcapICaret		.equ 0x80
tLcapIDier		.equ 0x81
tLiAcute		.equ 0x82
tLiGrave		.equ 0x83
tLiCaret		.equ 0x84
tLiDier			.equ 0x85
tLcapOAcute		.equ 0x86
tLcapOGrave		.equ 0x87
tLcapOCaret		.equ 0x88
tLcapODier		.equ 0x89
tLoAcute		.equ 0x8A
tLoGrave		.equ 0x8B
tLoCaret		.equ 0x8C
tLoDier			.equ 0x8D
tLcapUAcute		.equ 0x8E
tLcapUGrave		.equ 0x8F
tLcapUCaret		.equ 0x90
tLcapUDier		.equ 0x91
tLuAcute		.equ 0x92
tLuGrave		.equ 0x93
tLuCaret		.equ 0x94
tLuDier			.equ 0x95
tLcapCCed		.equ 0x96
tLcCed			.equ 0x97
tLcapNTilde		.equ 0x98
tLnTilde		.equ 0x99
tLaccent		.equ 0x9A
tLgrave			.equ 0x9B
tLdieresis		.equ 0x9C
tLquesDown		.equ 0x9D
tLexclamDown		.equ 0x9E
tLalpha			.equ 0x9F
tLbeta			.equ 0x0A0
tLgamma			.equ 0x0A1
tLcapDelta		.equ 0x0A2
tLdelta			.equ 0x0A3
tLepsilon		.equ 0x0A4
tLlambda		.equ 0x0A5
tLmu			.equ 0x0A6
tLpi			.equ 0x0A7
tLrho			.equ 0x0A8
tLcapSigma		.equ 0x0A9
tLphi			.equ 0x0AB
tLcapOmega		.equ 0x0AC
tLphat			.equ 0x0AD
tLchi			.equ 0x0AE
tLstatF			.equ 0x0AF
tLa			.equ 0x0B0
tLb			.equ 0x0B1
tLc			.equ 0x0B2
tLd			.equ 0x0B3
tLsmalle		.equ 0x0B4
tLf			.equ 0x0B5
tLsmallg		.equ 0x0B6
tLh			.equ 0x0B7
tLi			.equ 0x0B8
tLj			.equ 0x0B9
tLk			.equ 0x0BA
tLl			.equ 0x0BC
tLm			.equ 0x0BD
tLsmalln		.equ 0x0BE
tLo			.equ 0x0BF
tLp			.equ 0x0C0
tLq			.equ 0x0C1
tLsmallr		.equ 0x0C2
tLs			.equ 0x0C3
tLsmallt		.equ 0x0C4
tLu			.equ 0x0C5
tLv			.equ 0x0C6
tLw			.equ 0x0C7
tLx			.equ 0x0C8
tLy			.equ 0x0C9
tLz			.equ 0x0CA
tLsigma			.equ 0x0CB
tLtau			.equ 0x0CC
tLcapIAcute		.equ 0x0CD
tGarbagec		.equ 0x0CE
LastToken		.equ 0x0CE ;tLAST TOKEN IN THIS VERSION...

;Data Type Equates
;---------------------------------------------------------------------
RealObj			.equ 0
ListObj			.equ 1
MatObj			.equ 2
EquObj			.equ 3
StrngObj		.equ 4
ProgObj			.equ 5
ProtProgObj		.equ 6
PictObj			.equ 7
GDBObj			.equ 8
UnknownObj		.equ 9
UnknownEquObj		.equ 0x0A
NewEquObj		.equ 0x0B
CplxObj			.equ 0x0C
CListObj		.equ 0x0D
UndefObj		.equ 0x0E
WindowObj		.equ 0x0F
ZStoObj			.equ 0x10
TblRngObj		.equ 0x11
LCDObj			.equ 0x12
BackupObj		.equ 0x13
AppObj			.equ 0x14	;application, only used in menus/link
AppVarObj		.equ 0x15	;application variable
TempProgObj		.equ 0x16 ;program, home deletes when finished
GroupObj		.equ 0x17 ;group.

;I/O Equates
;---------------------------------------------------
D0D1_bits		.equ 0x03
D0LD1L			.equ 0x03
D0LD1H			.equ 0x01
D0HD1L			.equ 0x02
D0HD1H			.equ 0x00
bport			.equ 0 ;4-bit link port (I/O)

;Device Codes
;-----------------------------------------------------------------
TI82DEV			.equ 0x82
PC82DEV			.equ 0x02
MAC82DEV		.equ 0x12
TI83FDEV		.equ 0x73
LINK83FDEV		.equ 0x23
TI83DEV			.equ 0x83
PC83DEV			.equ 0x03
MAC83DEV		.equ 0x13
TI85DEV			.equ 0x95 ;different than real 85 so me talk
PC85DEV			.equ 0x05
MAC85DEV		.equ 0x15
TI73DEV			.equ 0x74 ;device x3 is always an 83
PC73DEV			.equ 0x07
MAC73DEV		.equ 0x17
LINK73FDEV		.equ 0x23
PC83FDEV		.equ 0x23

;System Error Codes
;-----------------------------------------------------------
E_EDITF			.equ 7 ;allow re-entering application
E_EDIT			.equ 1<<E_EDITF
E_Mask			.equ 0x7F
E_Overflow		.equ 1+E_EDIT
E_DivBy0		.equ 2+E_EDIT
E_SingularMat		.equ 3+E_EDIT
E_Domain		.equ 4+E_EDIT
E_Increment		.equ 5+E_EDIT
E_Break			.equ 6+E_EDIT
E_NonReal		.equ 7+E_EDIT
E_Syntax		.equ 8+E_EDIT
E_DataType		.equ 9+E_EDIT
E_Argument		.equ 10+E_EDIT
E_DimMismatch		.equ 11+E_EDIT
E_Dimension		.equ 12+E_EDIT
E_Undefined		.equ 13+E_EDIT
E_Memory		.equ 14+E_EDIT
E_Invalid		.equ 15+E_EDIT
E_IllegalNest		.equ 16+E_EDIT
E_Bound			.equ 17+E_EDIT
E_GraphRange		.equ 18+E_EDIT
E_Zoom			.equ 19+E_EDIT
E_Label			.equ 20
E_Stat			.equ 21
E_Solver		.equ 22+E_EDIT
E_Singularity		.equ 23+E_EDIT
E_SignChange		.equ 24+E_EDIT
E_Iterations		.equ 25+E_EDIT
E_BadGuess		.equ 26+E_EDIT
E_StatPlo		.equ 27
E_TolTooSmall		.equ 28+E_EDIT
E_Reserved		.equ 29+E_EDIT
E_Mode			.equ 30+E_EDIT
E_LnkErr		.equ 31+E_EDIT
E_LnkMemErr		.equ 32+E_EDIT
E_LnkTransErr		.equ 33+E_EDIT
E_LnkDupErr		.equ 34+E_EDIT
E_LnkMemFull		.equ 35+E_EDIT
E_Unknown		.equ 36+E_EDIT
E_Scale			.equ 37+E_EDIT
E_IdNotFound		.equ 38
E_NoMode		.equ 39+E_EDIT
E_Validation		.equ 40
E_Length		.equ 41+E_EDIT
E_Application		.equ 42+E_EDIT
E_AppErr1		.equ 43+E_EDIT
E_AppErr2		.equ 44+E_EDIT
E_ExpiredApp		.equ 45
E_BadAdd		.equ 46
E_Archived		.equ 47+E_EDIT
E_Version		.equ 48
E_ArchFull		.equ 49
E_Variable		.equ 50+E_EDIT
E_Duplicate		.equ 51+E_EDIT
HigErrNum		.equ 51
;Obsolete error numbers 34 ;first LINK error
E_LinkIOChkSum		.equ 34
E_LinkIOTimeOut		.equ 35
E_LinkIOBusy		.equ 36
E_LinkIOVer		.equ 37

;Equates To RAM Locations For Stat Vars
;----------------------------------------------------------------
FPLEN			.equ 9 ;Length of a floating-point number.
StatN			.equ statVars
XMean			.equ StatN + FPLEN
SumX			.equ XMean + FPLEN
SumXSqr			.equ SumX + FPLEN
StdX			.equ SumXSqr + FPLEN
StdPX			.equ StdX + FPLEN
MinX			.equ StdPX + FPLEN
MaxX			.equ MinX + FPLEN
MinY			.equ MaxX + FPLEN
MaxY			.equ MinY + FPLEN
YMean			.equ MaxY + FPLEN
SumY			.equ YMean + FPLEN
SumYSqr			.equ SumY + FPLEN
StdY			.equ SumYSqr + FPLEN
StdPY			.equ StdY + FPLEN
SumXY			.equ StdPY + FPLEN
Corr			.equ SumXY + FPLEN
MedX			.equ Corr + FPLEN
Q1			.equ MedX + FPLEN
Q3			.equ Q1 + FPLEN
QuadA			.equ Q3 + FPLEN
QuadB			.equ QuadA + FPLEN
QuadC			.equ QuadB + FPLEN
CubeD			.equ QuadC + FPLEN
QuartE			.equ CubeD + FPLEN
MedX1			.equ QuartE + FPLEN
MedX2			.equ MedX1 + FPLEN
MedX3			.equ MedX2 + FPLEN
MedY1			.equ MedX3 + FPLEN
MedY2			.equ MedY1 + FPLEN
MedY3			.equ MedY2 + FPLEN
PStat			.equ MedY3 + 2*FPLEN
ZStat			.equ PStat + FPLEN
TStat			.equ ZStat + FPLEN
ChiStat			.equ TStat + FPLEN
FStat			.equ ChiStat + FPLEN
DF			.equ FStat + FPLEN
Phat			.equ DF + FPLEN
Phat1			.equ Phat + FPLEN
Phat2			.equ Phat1 + FPLEN
MeanX1			.equ Phat2 + FPLEN
StdX1			.equ MeanX1 + FPLEN
StatN1			.equ StdX1 + FPLEN
MeanX2			.equ StatN1 + FPLEN
StdX2			.equ MeanX2 + FPLEN
StatN2			.equ StdX2 + FPLEN
StdXP2			.equ StatN2 + FPLEN
SLower			.equ StdXP2 + FPLEN
SUpper			.equ SLower + FPLEN
SStat			.equ SUpper + FPLEN
F_DF			.equ anovaf_vars
F_SS			.equ F_DF + FPLEN
F_MS			.equ F_SS + FPLEN
E_DF			.equ F_MS + FPLEN
E_SS			.equ E_DF + FPLEN
E_MS			.equ E_SS + FPLEN
