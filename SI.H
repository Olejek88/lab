
// SI8 & TRM200 & TRM202
struct SIdevices
	{
	 unsigned	adr;
	 // 1 - SI8
	 // 2 - TRM200
	 // 3 - TRM202
	 unsigned	type;
    };
struct SIdevices SIdevice[] =
	{{4, 3}};
/*	{ {1, 1},
	  {2, 2},
	  {3, 2},
	  {4, 2},
	  {5, 3},
	  {6, 3},
	  {7, 3}}; */
// SI8
#define		COM_DCNT	0xC173
#define		COM_DSPD	0x8FC2
#define		COM_DTMR	0xE69C
// TRM 200 & 202
#define		PV		0xB8DF
#define		LuPV		0xB257

// constants
extern 	float	LwaterHol;		// refrigirator level
extern 	float	LwaterHV;		// cold water level
extern 	float   LwaterGV;		// warm water level

extern 	float   TwaterHV;		// temp cold
extern 	float   TwaterGV;		// temp warm
extern 	float   TwaterHol;		// temp refrigirator

extern 	float   VwaterHV;		// cold water consumption


struct SIcomCRC
	{
	 unsigned	DCNT;
	 unsigned	DSPD;
	 unsigned	DTMR;
	};

SIcomCRC	SIcrc[] =
	{{	0xA818, 0xD5F5, 0x92C6},
	{ 0xE71A, 0x9AF7, 0xDDC4},
	{ 0xDDE4, 0xA009, 0xE73A},
	{ 0x791E, 0x04F3, 0x43C0},
	{ 0x43E0, 0x3E0D, 0x793E},
	{ 0x0CE2, 0x710F, 0x363C},
	{ 0x361C, 0x4BF1, 0x0CC2},
	{ 0xCA41, 0xB7AC, 0xF09F}};
// параметры

//--------------------------------------------------------------------------------------------------------
extern float	V1;
