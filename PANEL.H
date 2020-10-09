#define ReadHoldingRegisters	0x3
#define ReadInputRegisters	0x4
#define PresetSingleRegister  	0x5
#define PresetMultiCoils  	0xF
#define PresetMultiRegister  	0x10

// constants
extern float   LwaterHol;		// refrigirator level
extern float   LwaterHV;		// cold water level
extern float   LwaterGV;		// warm water level

extern float   TwaterHV;		// temp cold
extern float   TwaterGV;		// temp warm
extern float   TwaterHol;		// temp refrigirator

extern float   VwaterHV;		// cold water consumption

extern float   tZLwaterHol;		// current input refrigirator level
extern float   tZLwaterHV;		// current input cold water level
extern float   tZLwaterGV;		// current input warm water level
extern float   tZTwaterHV;		// current input cold water temp
extern float   tZTwaterGV;		// current input warm water temp

extern float   ZLwaterHol;		// input refrigirator level
extern float   ZLwaterHV;		// input cold water level
extern float   ZLwaterGV;		// input warm water level
extern float   ZTwaterHV;		// input cold water temp
extern float   ZTwaterGV;		// input warm water temp

extern unsigned char 	oTen12;		// in ten 1-2
extern unsigned char 	oTen34;		// in ten 3-4
extern unsigned char 	oTen56;		// in ten 5-6
extern unsigned char 	oVent;		// on ventilation system
extern unsigned char 	oSA1;		// automat-hand switch 1
extern unsigned char 	oSA2;		// automat-hand switch 2
extern unsigned char 	oSA3;		// automat-hand switch 3
extern unsigned char 	oSA4;		// automat-hand switch 4
extern unsigned char 	oOpenZD3;	// open ZD3
extern unsigned char 	oCloseZD3;	// close ZD3
extern unsigned char 	oOpenZD4;	// open ZD4
extern unsigned char   oCloseZD4;	// close ZD4
extern unsigned char   oOnM1;		// on M1
extern unsigned char 	oOffM1;		// off M1
extern unsigned char 	oOpenZD5;	// open ZD5
extern unsigned char   oCloseZD5;	// close ZD5
extern unsigned char   oOnM3;		// on M3
extern unsigned char   oOffM3;		// off M3

extern unsigned char 	Ten1;		// in ten 1
extern unsigned char 	Ten2;		// in ten 2
extern unsigned char 	Ten3;		// in ten 3
extern unsigned char 	Ten4;		// in ten 4
extern unsigned char 	Ten5;		// in ten 5
extern unsigned char 	Ten6;		// in ten 6
extern unsigned char 	Vent;		// on ventilation system
extern unsigned char 	SA1;		// automat-hand switch 1
extern unsigned char 	SA2;		// automat-hand switch 2
extern unsigned char 	OpenZD1;	// open ZD1
extern unsigned char 	OpenZD2;	// open ZD2
extern unsigned char 	OpenZD3;	// open ZD3
extern unsigned char 	CloseZD3;	// close ZD3
extern unsigned char 	OpenZD4;	// open ZD4
extern unsigned char   CloseZD4;	// close ZD4
extern unsigned char 	OpenZD5;	// open ZD4
extern unsigned char   CloseZD5;	// close ZD4
extern unsigned char   CloseGV;	// close ZD5

extern unsigned char   Ready;		// ready to start
extern unsigned char   StartFR;	// start frozing
extern unsigned char   StartFillHV;	// start fill HV
extern unsigned char   StartWM;	// start heating
extern unsigned char   StartFillGV;	// start fill GV
extern unsigned char   StopController;	// stop controller

extern unsigned 	CMMD1;	// control word
extern unsigned 	RFRD1;	// output speed
extern unsigned 	ETAD1;	// status word
extern unsigned 	ERRD1;	// fault code
extern unsigned	SMIL1;	// minimum speed
extern unsigned 	SMAL1;	// maximum speed
extern unsigned	SPAL1;	// acceleration speed data
extern unsigned 	SPAT1;	// acceleration time delta
extern unsigned 	LFr1;	// frequency reference
extern unsigned 	LCr1;	// current in the motor
extern unsigned 	Opr1;	// motor power
extern unsigned 	ETI1;	// extended status word
extern unsigned 	LRS1;	// extended status word

extern unsigned 	CMMD2;	// control word
extern unsigned 	RFRD2;	// output speed
extern unsigned 	ETAD2;	// status word
extern unsigned 	ERRD2;	// fault code
extern unsigned	SMIL2;	// minimum speed
extern unsigned 	SMAL2;	// maximum speed
extern unsigned	SPAL2;	// acceleration speed data
extern unsigned 	SPAT2;	// acceleration time delta
extern unsigned 	LFr2;	// frequency reference
extern unsigned 	LCr2;	// current in the motor
extern unsigned 	Opr2;	// motor power
extern unsigned 	ETI2;	// extended status word
extern unsigned 	LRS2;	// extended status word

extern unsigned 	CMMD3;	// control word
extern unsigned 	RFRD3;	// output speed
extern unsigned 	ETAD3;	// status word
extern unsigned 	ERRD3;	// fault code
extern unsigned	SMIL3;	// minimum speed
extern unsigned 	SMAL3;	// maximum speed
extern unsigned	SPAL3;	// acceleration speed data
extern unsigned 	SPAT3;	// acceleration time delta
extern unsigned 	LFr3;	// frequency reference
extern unsigned 	LCr3;	// current in the motor
extern unsigned 	Opr3;	// motor power
extern unsigned 	ETI3;	// extended status word
extern unsigned 	LRS3;	// extended status word

extern unsigned char	errorLowLevelHv;
extern unsigned char	errorHighLevelHv;
extern unsigned char	errorHighTempHv;
extern unsigned char	errorLowTempHv;
extern unsigned char	errorLowLevelGv;
extern unsigned char	errorHighLevelGv;
extern unsigned char	errorHighTempGv;
extern unsigned char	errorLowTempGv;
