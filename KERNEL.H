// constants
float	LwaterHol;		// refrigirator level
float	LwaterHV;		// cold water level
float   LwaterGV;		// warm water level

float   TwaterHV;		// temp cold
float   TwaterGV;		// temp warm
float   TwaterHol;		// temp refrigirator

float   VwaterHV;		// cold water consumption

float   tZLwaterHol;		// current input refrigirator level
float   tZLwaterHV;		// current input cold water level
float   tZLwaterGV;		// current input warm water level
float   tZTwaterHV;		// current input cold water temp
float   tZTwaterGV;		// current input warm water temp

float   ZLwaterHol;		// input refrigirator level
float   ZLwaterHV;		// input cold water level
float   ZLwaterGV;		// input warm water level
float   ZTwaterHV;		// input cold water temp
float   ZTwaterGV;		// input warm water temp

unsigned char 	oOpenZD5;	// open ZD5 (A5-RL0)
unsigned char   oCloseZD5;	// close ZD5 (A5-RL1)
unsigned char   res1;		// reserved
unsigned char   oOnM3;		// on M3 (A5-RL3)
unsigned char   oOffM3;		// off M3 (A5-RL4)
unsigned char 	oTen12;		// in ten 1-2 (A5-RL5)
unsigned char 	oTen34;		// in ten 3-4 (A5-RL6)
unsigned char 	oTen56;		// in ten 5-6 (A5-RL7)
unsigned char 	oVent;		// on ventilation system (A5-RL8)

unsigned char   oOnM1;		// on M1 (A4-RL0)
unsigned char 	oOffM1;		// off M1 (A4-RL1)
unsigned char   oOnM2;		// on M2 (A4-RL2)
unsigned char   oOffM2;		// off M2 (A4-RL3)
unsigned char   res2;		// reserved
unsigned char 	oOpenZD3;	// open ZD3 (A4-RL5)
unsigned char 	oCloseZD3;	// close ZD3 (A4-RL6)
unsigned char 	oOpenZD4;	// open ZD4 (A4-RL7)
unsigned char   oCloseZD4;	// close ZD4 (A4-RL8)

unsigned char 	SA2;		// automat-hand switch 2 (A3-DI0)
unsigned char 	OpenZD5;	// open ZD5 (A3-DI1)
unsigned char   CloseZD5;	// close ZD5 (A3-DI2)
unsigned char   OnM3;		// on M3 (A3-DI3)
unsigned char 	Ten1;		// in ten 1 (A3-DI4)
unsigned char 	Ten2;		// in ten 2 (A3-DI5)
unsigned char 	Ten3;		// in ten 3 (A3-DI6)
unsigned char 	Ten4;		// in ten 4 (A3-DI7)
unsigned char 	Ten5;		// in ten 5 (A3-DI8)
unsigned char 	Ten6;		// in ten 6 (A3-DI9)
unsigned char 	Vent;		// on ventilation system (A3-DI10)
unsigned char   CloseGV;	// close GV (A3-DI11)

unsigned char 	SA1;		// automat-hand switch 1 (A2-DI0)
unsigned char 	OpenZD1;	// open ZD1 (A2-DI1)
unsigned char 	OpenZD2;	// open ZD2 (A2-DI2)
unsigned char 	OpenZD3;	// open ZD3 (A2-DI3)
unsigned char 	CloseZD3;	// close ZD3 (A2-DI4)
unsigned char 	OpenZD4;	// open ZD4 (A2-DI5)
unsigned char   CloseZD4;	// close ZD4 (A2-DI6)
unsigned char   OnM1;		// on M1 (A2-AI7)
unsigned char   OnM2;		// on M2 (A2-AI8)

unsigned char   Ready;		// ready to start
unsigned char   StartFR;	// start frozing
unsigned char   StartFillHV;	// start fill HV
unsigned char   StartWM;	// start heating
unsigned char   StartFillGV;	// start fill GV
unsigned char   StopController;	// stop controller

unsigned 	CMMD1;	// control word
unsigned 	RFRD1;	// output speed
unsigned 	ETAD1;	// status word
unsigned 	ERRD1;	// fault code
unsigned	SMIL1;	// minimum speed
unsigned 	SMAL1;	// maximum speed
unsigned	SPAL1;	// acceleration speed data
unsigned 	SPAT1;	// acceleration time delta
unsigned 	LFr1;	// frequency reference
unsigned 	LCr1;	// current in the motor
unsigned 	Opr1;	// motor power
unsigned 	ETI1;	// extended status word
unsigned 	LRS1;	// extended status word

unsigned 	CMMD2;	// control word
unsigned 	RFRD2;	// output speed
unsigned 	ETAD2;	// status word
unsigned 	ERRD2;	// fault code
unsigned	SMIL2;	// minimum speed
unsigned 	SMAL2;	// maximum speed
unsigned	SPAL2;	// acceleration speed data
unsigned 	SPAT2;	// acceleration time delta
unsigned 	LFr2;	// frequency reference
unsigned 	LCr2;	// current in the motor
unsigned 	Opr2;	// motor power
unsigned 	ETI2;	// extended status word
unsigned 	LRS2;	// extended status word

unsigned 	CMMD3;	// control word
unsigned 	RFRD3;	// output speed
unsigned 	ETAD3;	// status word
unsigned 	ERRD3;	// fault code
unsigned	SMIL3;	// minimum speed
unsigned 	SMAL3;	// maximum speed
unsigned	SPAL3;	// acceleration speed data
unsigned 	SPAT3;	// acceleration time delta
unsigned 	LFr3;	// frequency reference
unsigned 	LCr3;	// current in the motor
unsigned 	Opr3;	// motor power
unsigned 	ETI3;	// extended status word
unsigned 	LRS3;	// extended status word

unsigned char	errorLowLevelHv;
unsigned char	errorHighLevelHv;
unsigned char	errorHighTempHv;
unsigned char	errorLowTempHv;
unsigned char	errorLowLevelGv;
unsigned char	errorHighLevelGv;
unsigned char	errorHighTempGv;
unsigned char	errorLowTempGv;

// output 
unsigned	A2;
unsigned	A3;
unsigned	A4;
unsigned	A5;

// global variables
char	mainlog[100];		// main log file

unsigned char	WorkEnable=1;		// work flag
unsigned char	StatusFinish=0;		// exit by errors
unsigned	currentregim;		// 0 - test

float	V1;