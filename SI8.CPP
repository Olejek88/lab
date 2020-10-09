#include <dos.h>
#include <mem.h>
#include <math.h>
#include "si.h"
#include "service.h"

#include "..\lib\7186e.h"

#define	byte	unsigned char

extern	void ULOGW (char* string, ...);		// log file function
static	byte	CRC (char* in, byte count, byte* crc);	// crc calculation function
static	byte	SendData (unsigned adr, unsigned func, byte* data, byte nbytes);	// send/recieve data function
unsigned owenCRC16(unsigned char* packet, unsigned length);
static unsigned	hPort2=5;		// SI8 port handler
static	int	result=0;		// read/write result
//----------------------------------------------------------------------------------------------------
// [Thread] Get/Set all values from all SI
void SI8Connection ()
{
 //int	adr=0;			// address on modbus
 byte	data[100];		// input/output buffer
 byte	temp[10]={0};
 unsigned value=0;
 double	val=0.0,del=0.0;
 int 	iret,si=0;
 iret=InstallCom(hPort2,9600L,8,0,1);
 if(iret==0) ULOGW ("[si8] initial port 2 success!");
 else   ULOGW ("[si8] there is an error code %d when initial port 2",iret);

 //dev	D681
 for (si=0;si<1;si++)
	{
	 //1	DCNT	C173	DEC_dot0| SGND	-9999999….. 9999999
	 //2	DSPD	8FC2	DEC_dot0	0… 9999999
	 //3	DTMR	E69C	CLK_frm		0….99999595999
	 if (SIdevice[si].type==1)
	 if (SendData (SIdevice[si].adr, COM_DCNT, data, 0))
		{
		 value=data[1]*1000000+data[2]*100000+data[3]*10000+data[4]*1000+data[5]*100+data[6]*10+data[7];
		 if (data[0]==0) del=1;
		 if (data[0]==1) del=10;
		 if (data[0]==2) del=100;
		 if (data[0]==3) del=1000;
		 //del=(float)pow (10,data[0]);
		 //data[0]=0; data[8]=0;
		 //val=(float)atof ((char *)data);
		 if (del) val=value/(float)del;
		 VwaterHV=val;		// cold water consumption
		 ULOGW ("[si8] [1][%f]",V1);
		}
	 if (SIdevice[si].type>1)
		{
		 if (SendData (SIdevice[si].adr, PV, data, 0))
			{
			 temp[3]=(data[0]*16+data[1]);
			 temp[2]=(data[2]*16+data[3]);
			 temp[1]=(data[4]*16+data[5]);
			 temp[0]=0x0;
			 val=*(float *)temp;
			 ULOGW ("[trm][%d] PV: [%x][%x][%x][%x] %f",SIdevice[si].adr,temp[0],temp[1],temp[2],temp[3],val);
			 if (SIdevice[si].adr==2)
				LwaterHol=value; // refrigirator level
			 if (SIdevice[si].adr==3)
				LwaterHV=value;	 // cold water level
			 if (SIdevice[si].adr==4)
				LwaterGV=value;	 // warm water level
			 if (SIdevice[si].adr==5)
				TwaterHV=value;	 // temp cold
			 if (SIdevice[si].adr==6)
				TwaterGV=value;	 // temp warm
			 if (SIdevice[si].adr==7)
				TwaterHol=value; // temp refrigirator
			}
		 if (SendData (SIdevice[si].adr, LuPV, data, 0))
			{
			 temp[3]=(data[0]*16+data[1]);
			 temp[2]=(data[2]*16+data[3]);
			 temp[1]=(data[4]*16+data[5]);
			 temp[0]=0;
			 val=*(float *)temp;
			 ULOGW ("[trm][%d] LuPV: [%x][%x][%x][%x] %f",SIdevice[si].adr,temp[0],temp[1],temp[2],temp[3],value);
			}
		}
	 Delay (1000);
	}

 ULOGW ("[si8] close COM%d [srv] port",hPort2);
 RestoreCom(hPort2);
}
//------------------------------------------------------------------------------------------
// function send data to SRVousilitel
byte SendData (unsigned adr, unsigned func, byte* data, byte nbytes)

{
 // byte && 0xf + 0x47
 // # 0xd
 byte out[100],in[100],dt[50],cnt=0;
 unsigned crc=0;
 byte count=3;
 unsigned bytes=0;
 byte	res=0,i=0;
 if (adr<1) return 0;

 //23 47 48 48 47 53 48 4E 4A 51 4F 48 4F 0D
 //23 47 48 48 47 4F 56 53 49 54 4C 56 4C 0D
 //23 47 48 48 47 55 4D 50 53 50 49 53 4D 0D

 out[0]=0x23;			// # start
 out[1]=((adr&0xf0)>>4);	// adr high
 out[2]=((byte)adr&0xf);	// adr low

 out[3]=((0x10&0xf0)>>4);	// high
 out[4]=(0x10&0xf);		// low

 out[5]=((func&0xf000)>>12);	// hash
 out[6]=((func&0xf00)>>8);	// hash
 out[7]=((func&0xf0)>>4);	// hash
 out[8]=(func&0xf);		// hash
 dt[0]=0x4; dt[1]=0x10; dt[2]=0xb8; dt[3]=0xdf;
 dt[2]=func>>8; dt[3]=func&0xff;
 crc=owenCRC16(dt,4);
 //ULOGW ("[si8] crc=%x",crc);
 if (func==COM_DCNT) crc=SIcrc[adr-1].DCNT;
 if (func==COM_DSPD) crc=SIcrc[adr-1].DSPD;
 if (func==COM_DTMR) crc=SIcrc[adr-1].DTMR;

 out[9]= ((crc/256)&0xf0)>>4;	// crc high
 out[10]=(crc/256)&0xf;		// crc low
 out[11]=((crc%256)&0xf0)>>4;	// crc high
 out[12]=(crc%256)&0xf;		// crc low
 ULOGW ("[si8] send[14] %x %x %x %x %x %x %x %x %x %x %x %x %x %x",out[0],out[1],out[2],out[3],out[4],out[5],out[6],out[7],out[8],out[9],out[10],out[11],out[12],out[13]);

 for (i=1; i<=12; i++) out[i]+=0x47;
 out[13]=0xd;
 //ULOGW ("[si8] send[14]%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",out[0],out[1],out[2],out[3],out[4],out[5],out[6],out[7],out[8],out[9],out[10],out[11],out[12],out[13]);
 for (i=0; i<=13; i++) ToCom (hPort2,out[i]);

// res=ToComBufn (hPort2,out, 14);
// if (res) ULOGW ("[si8] send to panel success [%d]",nbytes);
// else	 ULOGW ("[si8] error send to si8 [%d]",res);

 Delay (200);
 bytes=DataSizeInCom(hPort2);
 //if (bytes<25) ULOGW ("[si8] recieve %d bytes",bytes);
 if (bytes>50) return 0;
 res=ReadComn (hPort2,in,bytes);

 if (bytes)
	{
	 if (bytes>20) ULOGW ("[si8] recieve [%d] %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",bytes,in[0],in[1],in[2],in[3],in[4],in[5],in[6],in[7],in[8],in[9],in[10],in[11],in[12],in[13],in[14],in[15],in[16],in[17],in[18],in[19],in[20],in[21]);
	 else ULOGW ("[si8] recieve [%d] %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",bytes,in[0],in[1],in[2],in[3],in[4],in[5],in[6],in[7],in[8],in[9],in[10],in[11],in[12],in[13],in[14],in[15]);
	 //for (byte i=0; i<bytes; i++) ULOGW ("[si8] in[%d]=%x (%x)",i,in[i],in[i]-0x80);
	 cnt=0;
	 for (i=0; i<bytes; i++) if (in[i]>0x80) in[i]=in[i]-0x80;

	 if (in[0]==0x23)
	 for (i=1; i<bytes; i++)
		{
		 if (in[i]>=0x47) dt[cnt]=(in[i]-0x47);
		 else dt[cnt]=0;
		 //ULOGW ("[si8] dt[%d]=%x",cnt,dt[cnt]);
		 cnt++;
		}
	 memcpy (data,dt+8,8); data[8]=0;
	 crc=0;
	 return 1;
	}
 if (!res)
	{
	 ULOGW ("[si8] error recieve from SI8 [%d]",bytes);
	 if (hPort2) RestoreCom(hPort2);
	 InstallCom(hPort2,115200L,8,0,1);
	 count--;
	}

 return 0;
}
//----------------------------------------------------------------------------------------------------
unsigned owenCRC16(unsigned char* packet, unsigned length)
{
	size_t i, j;
	unsigned short crc;
	crc = 0;
	for (i = 0; i < length; ++i)
	{
	 unsigned char b = packet[i];
	 for (j=0; j<8; ++j, b<<=1)
		{
		 if ((b^(crc>>8)) & 0x80)
			{
				crc <<= 1;
				crc ^= 0x8F57;
			}
			else
				crc <<= 1;
		}
	}
	return crc;
}
//----------------------------------------------------------------------------------------------------
