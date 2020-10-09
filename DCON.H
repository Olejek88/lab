
#define ReadHoldingRegisters		0x3
#define PresetSingleRegister  		0x6 	// 5!
#define PresetMultiRegister  		0x16
#define ReadDeviceIdentification	0x43

#define	SetAllDO0	"#AA00"
#define	SetAllDO8	"#AA0A"
#define	SetAllDOB	"#AA0B"

#define	SetDO0		"#AA1"
#define	SetDO8		"#AAA"
#define	SetDOB		"#AAB"

#define ReadCounter	"#AA"
#define ReadDI		"$AA6"
#define ReadFirmware	"$AAF"
#define ReadName	"$AAM"
#define ReadProtocol	"$AAP"

#define	SetDOchannels	"@AA"
#define CR 0xd

struct ICPdevices
	{
	 unsigned	adr;
	 char		type;
	 char		name[10];
	 unsigned	curDO;
	 unsigned	DO;
    };
struct ICPdevices ICPdevice[] =
	{ {2, 1, "7051", 0x0, 0x0},
	  {3, 1, "7051", 0x0, 0x0},
	  {4, 2, "7061", 0x0, 0x0},
	  {5, 2, "7061", 0x0, 0x0}};


extern unsigned char 	oOpenZD5;	// open ZD5 (A5-RL0)
extern unsigned char   oCloseZD5;	// close ZD5 (A5-RL1)
extern unsigned char   res1;		// reserved
extern unsigned char   oOnM3;		// on M3 (A5-RL3)
extern unsigned char   oOffM3;		// off M3 (A5-RL4)
extern unsigned char 	oTen12;		// in ten 1-2 (A5-RL5)
extern unsigned char 	oTen34;		// in ten 3-4 (A5-RL6)
extern unsigned char 	oTen56;		// in ten 5-6 (A5-RL7)
extern unsigned char 	oVent;		// on ventilation system (A5-RL8)

extern unsigned char   oOnM1;		// on M1 (A4-RL0)
extern unsigned char 	oOffM1;		// off M1 (A4-RL1)
extern unsigned char   oOnM2;		// on M2 (A4-RL2)
extern unsigned char   oOffM2;		// off M2 (A4-RL3)
extern unsigned char   res2;		// reserved
extern unsigned char 	oOpenZD3;	// open ZD3 (A4-RL5)
extern unsigned char 	oCloseZD3;	// close ZD3 (A4-RL6)
extern unsigned char 	oOpenZD4;	// open ZD4 (A4-RL7)
extern unsigned char   oCloseZD4;	// close ZD4 (A4-RL8)

extern unsigned char 	SA2;		// automat-hand switch 2 (A3-DI0)
extern unsigned char 	OpenZD5;	// open ZD5 (A3-DI1)
extern unsigned char   CloseZD5;	// close ZD5 (A3-DI2)
extern unsigned char   OnM3;		// on M3 (A3-DI3)
extern unsigned char 	Ten1;		// in ten 1 (A3-DI4)
extern unsigned char 	Ten2;		// in ten 2 (A3-DI5)
extern unsigned char 	Ten3;		// in ten 3 (A3-DI6)
extern unsigned char 	Ten4;		// in ten 4 (A3-DI7)
extern unsigned char 	Ten5;		// in ten 5 (A3-DI8)
extern unsigned char 	Ten6;		// in ten 6 (A3-DI9)
extern unsigned char 	Vent;		// on ventilation system (A3-DI10)
extern unsigned char   CloseGV;	// close GV (A3-DI11)

extern unsigned char 	SA1;		// automat-hand switch 1 (A2-DI0)
extern unsigned char 	OpenZD1;	// open ZD1 (A2-DI1)
extern unsigned char 	OpenZD2;	// open ZD2 (A2-DI2)
extern unsigned char 	OpenZD3;	// open ZD3 (A2-DI3)
extern unsigned char 	CloseZD3;	// close ZD3 (A2-DI4)
extern unsigned char 	OpenZD4;	// open ZD4 (A2-DI5)
extern unsigned char   CloseZD4;	// close ZD4 (A2-DI6)
extern unsigned char   OnM1;		// on M1 (A2-AI7)
extern unsigned char   OnM2;		// on M2 (A2-AI8)



