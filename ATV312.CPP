/*
i6070 panel function: 7000 modbus module

Compiler: BC++ 3.1,
	  Turbo C++ 1.01(3.01)

Compile mode: Large

Project: Client.c
	 ..\lib\7186el.Lib

[29-may-2014] Olejek
*/
#include "main.h"
#include "atv312.h"
//#include "kernel.h"

//extern void ULOGW (char* string, ...);
extern void ULOGW (char* string, ...);	// log file function

static int hPort2=4;	// port number
//int ModbusRTU_Answer(int adr, unsigned char count);
static int ModbusATV_Read(int adr, int start, int count, unsigned char *iRecv, int func);
static int ModbusATV_Write(int adr, int start, int count, byte len, byte *iSend, int func);
unsigned CRC (const byte* const Data, const byte DataSize);
unsigned CRC16 (const byte *nData, unsigned wLength);
//----------------------------------------------------------------------------------------------------
// [Thread] Get/Set all input/output values from/to panel
void ATVConnection ()
{
 int 	adr=0x1;					// address on modbus
 int 	iReadSuccess=0;
 byte	data[150];				// output buffer
 byte	data2[150];				// output buffer
 int 	iret;

 iret=InstallCom(hPort2,115200L,8,0,1);
 if(iret==0)
	ULOGW ("[atv] open atv312 port success");
 else
	ULOGW ("[atv] there is an error code %d when initial com-port",iret);
 
 for (adr=0; adr<sizeof(ATV_modbus_adr);adr++)
	{
	 iReadSuccess=ModbusATV_Read(adr,ATV_modbus_adr[adr]+1,1,data,ReadHoldingRegisters);
	 if (iReadSuccess) ULOGW ("[atv] read all signals failed error code: %d",iReadSuccess);
	 memcpy (&ATV_value[adr],data,4);
	}
 for (adr=0; adr<sizeof(ATV_modbus_adr);adr++)
	{
	 memcpy (&CMMD1+4*adr,ATV_value+adr,4);
	}
 RestoreCom(hPort2);
}
//--------------------------------------------------------------------------------------------------------------------
// Modbus read coils/registers function
int ModbusATV_Read(int adr, int start, int count, unsigned char *iRecv, int func)
{
 byte data[40];		// data array
 unsigned	crc=0;
 int		res=0;
 int		bytes=0;

 data[0]=adr;
 data[1]=func;
 data[2]=start/256;
 data[3]=start%256;
 data[4]=count/256;
 data[5]=count%256;
 crc = CRC16 (data, 6);

 data[6]=crc%256;
 data[7]=crc/256;
 res=ToComBufn (hPort2,(char *)data, 5+count);
 ULOGW ("[atv] (0x%x) (0x%x) (0x%x 0x%x) (0x%x 0x%x) [0x%x 0x%x]",data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]);

 if (res) ULOGW ("[atv] send to panel success");
 else	 ULOGW ("[atv] error send to ATV312 [%d]",res);

 Delay (1000);
 bytes=DataSizeInCom(hPort2);

 ULOGW ("[atv] recieve %d bytes",bytes);
 res=ReadComn (hPort2,(char *)iRecv,bytes);
 if (res==-1)
	 ULOGW ("[atv] error recieve from atv312 [%d]",res);
 if (bytes)
	{
	 if (iRecv[2]>2)
		{
		 crc = CRC16 (data, iRecv[2]+3);
		 ULOGW ("[atv] crc=%x [%x][%x] data=[%x][%x]",crc,crc/256,crc%256,iRecv[iRecv[2]+3],iRecv[iRecv[2]+4]);
		}
	}
 return 0;
}
//--------------------------------------------------------------------------------------------------------------------
int ModbusATV_Write(int adr, int start, int count, byte len, byte *iSend, int func)
{
 byte 		data[40];		// data array
 unsigned	crc=0;		//(* CRC checksum *)
 byte		res=0,i=0;
 unsigned	bytes=0;

 data[0]=adr;
 data[1]=func;
 if (func==PresetMultiRegister)
	{
	 data[2]=start/256;
	 data[3]=start%256;
	 data[4]=count/256;
	 data[5]=count%256;
	 data[6]=len;
	 for (i=0; i<len; i++) data[7+i]=iSend[i];
	 crc = CRC16 (data, 7+len);
	 data[7+len]=crc%256;
	 data[7+len+1]=crc/256;
	 ULOGW ("[atv] (0x%x)(0x%x) (0x%x 0x%x)(0x%x 0x%x)(0x%x) 0x%x[0x%x 0x%x]",data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9]);
	 res=ToComBufn (hPort2,data, 9+len);
	 ULOGW ("[atv] rs=(0x%d)",res);

	}
 if (func==PresetSingleRegister)
	{
	 data[2]=start/256;
	 data[3]=start%256;
	 for (i=0; i<len; i++) data[4+i]=iSend[i];
	 crc = CRC16 (data, 4+len);
	 data[4+len]=crc%256;
	 data[4+len+1]=crc/256;
	 ULOGW ("[atv] (0x%x) (0x%x) (0x%x 0x%x) (0x%x 0x%x) [0x%x 0x%x]",data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7]);
	 res=ToComBufn (hPort2,data, 6+len);
	}

 if (res) ULOGW ("[atv] send to panel success");
 else
        {
	 ULOGW ("[atv] error send to panel [%d]",res);
	}
 Delay (3000);
 bytes=DataSizeInCom(hPort2);
 ULOGW ("[atv] recieve %d bytes",bytes);
 res=ReadComn (hPort2,iSend,bytes);
 if (!res)
	{
	 ULOGW ("[atv] error recieve from panel [%d]",res);
	}
 if (bytes)
	{
	 ULOGW ("[atv] rd (0x%x) (0x%x) (0x%x 0x%x) (0x%x 0x%x) (0x%x 0x%x 0x%x 0x%x ... )",data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9]);
	 if (iSend[5]>2)
		{
		 crc = CRC16 (data, iSend[2]*2+3);
		 ULOGW ("[atv] crc=%x [%x][%x] data=[%x][%x]",crc,crc/256,crc%256,iSend[iSend[2]+3],iSend[iSend[2]+4]);
		}
	}
 return 0;
}
//--------------------------------------------------------------------------------------------------------------------
/*
unsigned int CalcCRC(unsigned int c,unsigned int crc)
{
 int count,flg;
 for (count=0;count<8;count++)
    {
     flg=crc&0x8000;
     crc<<=1;
     if(((c)&0x80)!=0)crc+=1;
	 if(flg!=0)crc^=0x1021;
	    c<<=1;
    }
 return crc;
}*/

unsigned CRC16 (const byte *nData, unsigned wLength)
{
static const WORD wCRCTable[] = {
0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };

byte nTemp;
unsigned wCRCWord = 0xFFFF;

   while (wLength--)
   {
      nTemp = *nData++ ^ wCRCWord;
      wCRCWord >>= 8;
      wCRCWord ^= wCRCTable[nTemp];
   }
   return wCRCWord;

}
