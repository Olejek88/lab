#define ReadHoldingRegisters		0x3
#define PresetSingleRegister  		0x6 	// 5!
#define PresetMultiRegister  		0x16
#define ReadDeviceIdentification	0x43

// constants
extern unsigned 	CMMD1;	// control word
extern unsigned 	RFRD1;	// output speed
extern unsigned 	ETAD1;	// status word
extern unsigned 	ERRD1;	// fault code
extern unsigned		SMIL1;	// minimum speed
extern unsigned 	SMAL1;	// maximum speed
extern unsigned		SPAL1;	// acceleration speed data
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
extern unsigned		SMIL2;	// minimum speed
extern unsigned 	SMAL2;	// maximum speed
extern unsigned		SPAL2;	// acceleration speed data
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
extern unsigned		SMIL3;	// minimum speed
extern unsigned 	SMAL3;	// maximum speed
extern unsigned		SPAL3;	// acceleration speed data
extern unsigned 	SPAT3;	// acceleration time delta
extern unsigned 	LFr3;	// frequency reference
extern unsigned 	LCr3;	// current in the motor
extern unsigned 	Opr3;	// motor power
extern unsigned 	ETI3;	// extended status word
extern unsigned 	LRS3;	// extended status word

struct	ATV
	{
	 unsigned	adr;
	};
struct	ATV	atv_devices[] = {{1},{2},{3}};


unsigned	ATV_modbus_adr[]={8601,8604,8603,8606,8607,8609,8611,8613,8502,3204,3211,3206,3250,
				  8601,8604,8603,8606,8607,8609,8611,8613,8502,3204,3211,3206,3250,
				  8601,8604,8603,8606,8607,8609,8611,8613,8502,3204,3211,3206,3250};
unsigned	ATV_value[50];