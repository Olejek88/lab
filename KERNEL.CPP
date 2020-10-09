#define MAIN_LOG	""

#include <dos.h>
#include <stdio.h>

#include "kernel.h"
#include "service.h"
#include "..\lib\7186e.h"

void dispatcher ();		// dispatcher
extern void ULOGW (char* string, ...);	// log file function
void GetAllIOStatus ();		// [Thread] Get all input/output status/values
void MainAlgorithm ();		// [Thread] Main algorithm thread
void loadNVRAM ();		// load from NVRAM function
extern void PanelConnection ();	// [Thread] Get/Set all input/output values from/to panel
extern void SI8Connection ();	// [Thread] Get/Set all input/output values from/to servoprivod
extern void ATVConnection ();	// [Thread] Get/Set all input/output values from/to servoprivod
extern void DCONConnection ();	// [Thread] Get/Set all input/output values from/to servoprivod

extern void ServiceThread ();	// [Thread] Service thread

extern FILE *Log;
//----------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
 char 	dates[200];
 TIME_DATE	tm;
 char	serial[50];
 unsigned libv;

 InitLib ();
 LedOn();
 GetTimeDate (&tm);
 sprintf (dates,"%d-%02d-%02d %02d:%02d:%02d",tm.year,tm.month,tm.day,tm.hour,tm.minute,tm.sec);
 GetSerialNumber (serial);
 ULOGW ("serial number: %d",serial);
 libv=GetLibVersion ();
 ULOGW ("library version: %d.%d",libv/256,libv%256);
 sprintf (mainlog,"%02d%02d%02d.log",tm.hour,tm.minute,tm.sec);
 ULOGW ("uaiz lab v0.0.8 started");

 ULOGW ("load from NVRAM");

 libv=2;
 while (libv)
	{
	 //SI8Connection ();
	 //Delay (1000);
	 PanelConnection ();
	 Delay (1000);
	 //ATVConnection ();
	 //Delay (1000);
	 //DCONConnection ();
	 Delay (1000);
	 MainAlgorithm ();
	 libv--;
	}
  //SetConfiguration ();	// set project/system configuration
  //CheckIO ();				// test input/output modules
// dispatcher ();		// start dispatcher
 ULOGW ("uaiz gvs kernel finished");
 Delay (10000);
 LedOff();
 return 0;
}
//--------------------------------------------------------------------
void loadNVRAM ()
{
 int 	iTemp;
 iTemp=ReadNVRAM  (0);
 if (iTemp>0)
	 tZLwaterHol=iTemp/100;
 iTemp=ReadNVRAM  (1);
 if (iTemp>0)
	 tZLwaterHV=iTemp/100;
 iTemp=ReadNVRAM  (2);
 if (iTemp>0)
	 tZLwaterGV=iTemp/100;
 iTemp=ReadNVRAM  (3);
 if (iTemp>0)
	 tZTwaterHV=iTemp/100;
 iTemp=ReadNVRAM  (4);
 if (iTemp>0)
	 tZTwaterGV=iTemp/100;
}
//--------------------------------------------------------------------
void MainAlgorithm ()
{
 float Lhyst=0.1;
/*
 if (LwaterHol<tZLwaterHol) 	// refrigirator level
 if (LwaterHo) 	// refrigirator level

 if (LwaterHV<1)	// cold water level
 if (LwaterHV>2)	// cold water level

 if (LwaterGV<1)	// warm water level
 if (LwaterGV>2)	// warm water level

 if (TwaterHV>10)	// temp cold
 if (TwaterGV<90)	// temp warm
 if (TwaterHol>10)	// temp refrigirator

 //??float   VwaterHV;		// cold water consumption

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

 if ()
 */
}
//----------------------------------------------------------------------------------------------------
void dispatcher (void)
{
 WorkEnable=1;			// work enable
 WorkEnable=0;			// disable all work
}
//----------------------------------------------------------------------------------------------------
// [Thread] Get all input/output status/values
void GetAllIOStatus ()
{
}

