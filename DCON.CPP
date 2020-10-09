/*
i6070 panel function: 7000 modbus module

Compiler: BC++ 3.1,
	  Turbo C++ 1.01(3.01)

Compile mode: Large

Project: Client.c
	 ..\lib\7186el.Lib

[29-may-2014] Olejek
*/
#include <string.h>
#include "main.h"
#include "dcon.h"

extern void ULOGW (char* string, ...);	// log file function

static int hPort2=3;	// port number
static int DCON_RW(int adr, byte *iRecv, char *func);
unsigned char CRC (const byte *nData, unsigned wLength);
//----------------------------------------------------------------------------------------------------
// [Thread] Get/Set all input/output values from/to panel
void DCONConnection ()
{
 int 	adr=0x1;		// address on modbus
 int 	iReadSuccess=0;
 byte	data[150];		// output buffer
 int 	iret;

 iret=InstallCom(hPort2,9600L,8,0,1);
 if(iret==0)
	ULOGW ("[dcon] open DCON port success");
 else
	ULOGW ("[dcon] there is an error code %d when initial com-port %d",iret,hPort2);

 for (adr=0; adr<4;adr++)
	{
	 sprintf (data,"");
	 iret=DCON_RW (ICPdevice[adr].adr, data, ReadName);
	 if (!iret)
		sprintf (ICPdevice[adr].name,"%s",data);
	 ULOGW ("[dcon][%d] module name: [%s]",ICPdevice[adr].adr,ICPdevice[adr].name);

	 if (ICPdevice[adr].type==2)
		{
		 if (ICPdevice[adr].adr==4)
			 ICPdevice[adr].DO=oOnM1+oOffM1*2+oOnM2*4+oOffM2*8+res2*16+oOpenZD3*32+oCloseZD3*64+oOpenZD4*128+oCloseZD4*256;
		 if (ICPdevice[adr].adr==5)
			 ICPdevice[adr].DO=oOpenZD5+oCloseZD5*2+res1*4+oOnM3*8+oOffM3*16+oTen12*32+oTen34*64+oTen56*128+oVent*256;
		 sprintf (data,"%02x",ICPdevice[adr].DO);
		 if (ICPdevice[adr].DO!=ICPdevice[adr].curDO)
			{
			 sprintf (data,"%02d",ICPdevice[adr].DO);
			 iret=DCON_RW (ICPdevice[adr].adr, data, SetDOchannels);
			 if (!iret)
				 ICPdevice[adr].curDO=ICPdevice[adr].DO;
			}
		 if (iReadSuccess) ULOGW ("[dcon] write all signals failed error code: %d",iReadSuccess);
		}
	 if (ICPdevice[adr].type==1)
		{
		 sprintf (data,"");
		 DCON_RW (ICPdevice[adr].adr, data, ReadDI);
		 if (ICPdevice[adr].adr==2)
			{
			 SA1=data[0]&0x1;		// automat-hand switch 1 (A2-DI0)
			 OpenZD1=(data[0]&0x2)>>1;	// open ZD1 (A2-DI1)
			 OpenZD2=(data[0]&0x4)>>2;	// open ZD2 (A2-DI2)
			 OpenZD3=(data[0]&0x8)>>3;	// open ZD3 (A2-DI3)
			 CloseZD3=(data[0]&0x10)>>4;	// close ZD3 (A2-DI4)
			 OpenZD4=(data[0]&0x20)>>5;	// open ZD4 (A2-DI5)
			 CloseZD4=(data[0]&0x40)>>6; 	// close ZD4 (A2-DI6)
			 OnM1=(data[0]&0x80)>>7;	// on M1 (A2-AI7)
			 OnM2=data[1]&0x1;		// on M2 (A2-AI8)
			}
		 if (ICPdevice[adr].adr==3)
			{
			 SA2=data[3]&0x1;		// automat-hand switch 2 (A3-DI0)
			 OpenZD5=(data[3]&0x2)>>1;	// open ZD5 (A3-DI1)
			 CloseZD5=(data[3]&0x4)>>2;	// close ZD5 (A3-DI2)
			 OnM3=(data[3]&0x8)>>3;		// on M3 (A3-DI3)
			 Ten1=(data[3]&0x10)>>4;	// in ten 1 (A3-DI4)
			 Ten2=(data[3]&0x20)>>5;	// in ten 2 (A3-DI5)
			 Ten3=(data[3]&0x40)>>6;	// in ten 3 (A3-DI6)
			 Ten4=(data[3]&0x80)>>7;	// in ten 4 (A3-DI7)
			 Ten5=data[2]&0x1;		// in ten 5 (A3-DI8)
			 Ten6=(data[2]&0x2)>>1;		// in ten 6 (A3-DI9)
			 Vent=(data[2]&0x4)>>2;		// on ventilation system (A3-DI10)
			 CloseGV=(data[2]&0x8)>>3;	// close GV (A3-DI11)
			 ULOGW ("[dcon] DI:(%s)",data);
			}
		}
	}
 RestoreCom(hPort2);
}
//--------------------------------------------------------------------------------------------------------------------
int DCON_RW(int adr, byte *iSend, char *func)
{
 byte 		data[40];		// data array
 byte 		data2[40];		// data array
 byte		crc=0;		//(* CRC checksum *)
 byte		res=0;
 unsigned	bytes=0;

 sprintf (data2,"%s",func);
 data2[1]=48+adr/10;
 data2[2]=48+adr%10;
 if (strlen(iSend)>0)
	{
	 sprintf (data,"%s%s",data2,iSend);
	 //crc=CRC (data,strlen(data));
	 //sprintf (data,"%s%c%c%c",data,(crc/10)+47,(crc%10)+47,CR);
	}
 ULOGW ("[dcon] send(%d) (%s)",strlen(data2)+1,data2);
 sprintf (data,"%s%c",data2,CR);
 res=ToComBufn (hPort2,data,strlen(data));

 if (!res)// ULOGW ("[dcon] send to icpdas success");
	ULOGW ("[dcon] error send to panel [%d]",res);
 Delay (1000);
 bytes=DataSizeInCom(hPort2);
 ULOGW ("[dcon] recieve %d bytes",bytes);
 res=ReadComn (hPort2,data,bytes);
 if (!res)
	 ULOGW ("[dcon] error recieve from panel [%d]",res);
 if (bytes)
	{
	 for (crc=0;crc<bytes;crc++)
		 if (data[crc]==CR) data[crc]=0;
	 ULOGW ("[dcon] rd(%d) (%s)",bytes,data);
	 //crc = CRC (data, bytes-3);
	 //ULOGW ("[dcon] crc=%x data=[%x][%x]",crc,iSend[iSend[2]+3],iSend[iSend[2]+4]);
	 memcpy (iSend,data+3,5);
	}
 return 0;
}
//--------------------------------------------------------------------------------------------------------------------
unsigned char CRC (const byte *nData, unsigned wLength)
{
 byte nTemp;
 byte wCRC = 0x0;

 while (wLength--)
   {
      nTemp += *nData++;
   }
// wCRC&=0xff;
 return wCRC;
}