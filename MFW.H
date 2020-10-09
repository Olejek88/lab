/*
  Last modified By Tim Tsai, Mon, 22 December 2008 05:28:22 GMT
*/
/*
  in user's program must use #include "tcpip.h" before #include "xs.h"
*/
#ifndef _TCPIP_H_
#include "tcpip.h"
#endif

#ifndef _XS_H_
#define _XS_H_

#undef _XS_

#define _XS_	9314	/* for XS09314.lib */

#define VARIABLE_SOCKET_NO
/*#define SOCKETS NCONNS*/         /* define the maximum number of sockets */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	unsigned port;
	int	socket;
	int	state;
	int 	connect;
	void (*CallBackFun)(int skt,int mode);
} TCP_SERVER,*pTCP_SERVER;

typedef struct {
	char *ip;
	unsigned port;
	int	socket;
	int	tmpState;
	int 	bConnected;
	int	iConnectTryCount;	
	long	lConnetTimeout;		
	long	ltmpT;
	void	(*CallBackFun)(int skt,int mode);
	void	(*LoopFun)(int skt);
} TCP_CLIENT,*pTCP_CLIENT;	

#define MAX_SERVER_NUMBER	32
#define MAX_CLIENT_NUMBER	48
#define MAX_UDP_NUMBER		32 
#define MAX_ICMP_NUMBER		16 
#define MAX_UNLOCK_IP_NUMBER	16

/* User program must support these two variables */
extern pTCP_SERVER pTcpServer[MAX_SERVER_NUMBER];
extern int TcpServerNumber;
extern pTCP_CLIENT pTcpClient[MAX_CLIENT_NUMBER];
extern int TcpClientNumber;

/* User program must support these three functions */
void XS_UserInit(int argc,char *argv[]);
void UserLoop(void);
void XS_UserEnd(void);	/* [12/24/2003] add */

extern int QuitMain; /* Set QuitMain to 1 will end the program. */
extern void (*pXS_UserInit)(int argc,char *argv[]); /* Default set to the function "UserInit" */
extern void (*pXS_UserEnd)(void); /* Default set to the function "UserEnd" */

#ifdef VARIABLE_SOCKET_NO
	extern char *SocketType;
	extern int *Socket_Idx;
	extern struct sockaddr_in *s_in;
#else
	extern char SocketType[32];	/* [93/04/06] */
	extern int Socket_Idx[32];
	extern struct sockaddr_in s_in[32];
#endif

extern int MaxSocketNo; /* The socket number supported by the library.[2004/04/01]add */
extern long CurrentLoopTimeTicks; //[2005/09/21]

int XS_CloseSocket(int socket);

#define XS_GetLibVersion	XS_GetVersion
void XS_GetVersion(char *ver);
/*
  Get the version(in string) of X-Server.
  the first version is 0.9.001 will get the string "0.9.001".
*/

void XS_GetLibDate(char *date);
/* ver. 0.9.003 ,[2004/04/02]add
  Get the library date(in string) of X-Server.
*/

extern long DhcpLeaseTime;
/* 
  DhcpLeaseTime: unit is sec. 
  default value is 0, will set the lease time to 1 day(86400 secs).
*/


/*-----------------------------------------------------------------------------*/
/* XS09100 (Ver. 0.9.100)*/
//extern unsigned char DnsIp[2][Iid_SZ];
/*
  If get DNS server IP adrress from DHCP server will be stroed into DnsIp.
*/

void XS_Install_DHCP_Client(void);
/*
  for use DHCP client function:
  1.call "Install_DHCP_Client();"
*/

int XS_AddServer(TCP_SERVER *server);
int XS_RemoveServer(TCP_SERVER *server);

int XS_AddClient(TCP_CLIENT *client);
int XS_RemoveClient(TCP_CLIENT *client);

/* for SMTP(send E-mail) */
extern TCP_CLIENT SmtpClient;
extern char *SMTP_MyName;
extern char *SMTP_MyEmailAddr;
extern char *SMTP_DestEmailAddr[5];
extern int SMTP_DestEmailAddrNo;
extern char *SMTP_Subject;
extern char *SMTP_MailData;
int XS_SendMail(void);

/* for timer function */
int DT_AddTimer(long repeat,long dt,int id,void (*fun)(void));
int DT_DeleteTimer(int id,int number);
int DT_DeleteTimerByFun(void (*fun)(void),int number); /*[2006/10/02] Add */

int DT2_AddTimer(long dt,int id,void (*fun)(void));
int DT2_DeleteTimer(int id);
int DT2_DeleteTimerByFun(void (*fun)(void)); /*[2006/10/02] add*/

/* for system loop function */
int XS_AddSystemLoopFun(void (*LoopFun)(void));
int XS_RemoveSystemLoopFun(void (*LoopFun)(void));


/*-----------------------------------------------------------------------------*/
/* XS09101 (Ver. 0.9.101)*/
extern char FILE_NOT_FOUND[];
extern char FILE_IS_TEXT[];
extern char FILE_IS_TEXT_NoLength[];
extern char FILE_IS_IMAGE[];
extern char FILE_IS_APPLICATION[];
extern char FILE_UPLOAD[];
extern char FILE_UPLOAD_END[];
extern int SizeOfFileNotFound;

#if _XS_ < 9300
	extern char *ImageFileType[];
	extern char *ApplicationFileType[];
#endif

extern TCP_SERVER XS_HttpServer;
enum METHOD {_GET=1,_POST};

void XS_Http_StartHttpServer(void); /*[2006/09/26] add*/

int XS_WriteSocket(int skt,char *buf,int len);
int XS_ReadSocket(int skt,char *buf,int len); /*[2009/12/07] add*/
void XS_Http_SetDefaultFile(char *fname);
int XS_Http_AddCgi(char *name,void (*cgifun)(int skt));
int XS_Http_AddPathCgi(char *name,void (*cgifun)(int skt)); /*[2008/02/04]*/

extern void (*SocketCloseCallBackFun)(int);

void XS_main( int argc, char *argv[] );

int XS_CloseSocket(int socket);

/* for port 10000 command*/ 
#ifndef  _TCPREADDATA_
#define  _TCPREADDATA_
typedef struct t_TcpReadData{
	int Comport;
	int Socket;
	int Length;
	char* ReadUartChar;
}TCPREADDATA, *PTCPREADDATA;
#endif

#define MAX_CMD_NUMBER	40 
extern int (*pXS_Port10kCmd[MAX_CMD_NUMBER])(PTCPREADDATA p);
extern TCP_SERVER Port10K;
extern unsigned char *PasswordMsg; /* default is NULL*/ 
extern const char MsgCmdOk[];
extern int MsgCmdOk_len;

extern const char MsgCmdError[];
extern int MsgCmdError_len;


/*
  command "00" for set password 
*/
#if _XS_ < 9311
/* XS 0.9.3.11 or later Remove these Password functions.*/
extern int bNeedPassword; 
extern int iPassworBlock; /* default value is 6 */
extern int iPassworAddr;	/* default value is 250 */ 
extern int (*pXS_CheckPassword)(PTCPREADDATA p);
int XS_CheckPassword(PTCPREADDATA p);
int XS_SetPassword_00(PTCPREADDATA p);
#endif

int TcpFlush(void);
int TcpPuts(int skt,int mode,char *str);
int TcpPrint(int skt,int mode,char *fmt,...);

void ResetCrc16(void);
unsigned ReadCrc16(void);
void UpdateCrc16(unsigned char data);
void MakeCRC16Table(void);

/* command 17 */ 
int XS_Inport_17(PTCPREADDATA p);

/* command 18 */ 
int XS_Outport_18(PTCPREADDATA p);

/* command 33 */
int XS_LoadFile_33(PTCPREADDATA p);

#ifndef _PORT10K_CMD33_
	#define _PORT10K_CMD33_ 
	typedef struct {
		char *cmd;
		int (*fun)(int);
	}CMD33 ;
#endif
extern CMD33 Cmd_33[]; /* only 5 items in Cmd_33[]*/ 
extern int (*Cmd33_WriteFileHeader)(FILE_DATA *fdata);
extern int (*Cmd33_WriteFileData)(char *data,int no);
extern int (*Cmd33_FinishFileHeader)(void);

void XS_ChangeToX600Fs(void);
void XS_ChangeToOs7Fs(void);
char *X600Fs_GetTmpBuf(void);

void XS_HttpUseOs7Fs(void);
void XS_HttpUseX600Fs(void);

extern void (*fpXS_StartPort10K)(int skt); /* [2007/01/16] add*/
extern unsigned MaxPort10KCmdNumber;	/* [2007/06/05] add */

/*
  For UDP socket 
*/

typedef struct{
	int	socket;
	unsigned MyPort;
	char *RemoteIp; 
	unsigned RemotePort;
	int fNonBlock;
	int fEnableBroadcast;
	int status; 
	void (*CallBackFun)(int skt);
} UDP_SOCKET, *pUDP_SOCKET; 

extern pUDP_SOCKET pUdpSocket[MAX_UDP_NUMBER];
int XS_AddUdpSocket(UDP_SOCKET *UdpSocket);
int XS_RemoveUdpSocket(UDP_SOCKET *UdpSocket);

/*
For UDP search function(the same as VCOM320 or later version.) 
*/
char *GetModuleName(void);	/* User's program must support this function */ 
char *GetAliasName(void);	/* User's program must support this function */ 
extern UDP_SOCKET XS_UdpSearch;

/*
  for COM port 
*/
#ifndef _XS_COMPORT_
#define _XS_COMPORT_

typedef struct ComPort COMPORT, *pCOMPORT;

struct ComPort{
  int Port;	// 0:COM0, 1:COM1,...
  char *Buf;
  unsigned Bufsize;
  char EndChar; 
  unsigned TriggerLevel;
  long Timeout;
  long StartTimeTicks;
  long LastTimeTicks;
  long MasterTimeout;
  long MasterStartTimeTicks; 
  unsigned Size; 
  int (*ReadComn)(unsigned char *buf,int n);
  void (*CallbackFun)(pCOMPORT, int mode);
  pCOMPORT next; 
#if _XS_ >=	9312
  unsigned char *pbTimeOut;	//[2007/03/09] add (XS_09312)
#endif   
#if _XS_ >=	9313
  unsigned char FTL;	//[2007/12/31] add (XS_09313)
#endif
};
#endif

void XS_AddComPort(pCOMPORT pcomport);
void XS_RemoveComPort(pCOMPORT pcomport);

/* for ICMP socket */
#ifndef _ICMP_SOCKET_
#define _ICMP_SOCKET_
typedef struct{
	int	socket;
	char *RemoteIp; 
	int status; 
	void (*CallBackFun)(int skt);
} ICMP_SOCKET, *pICMP_SOCKET; 
#endif

extern pICMP_SOCKET pIcmpSocket[MAX_ICMP_NUMBER];

int XS_AddIcmpSocket(ICMP_SOCKET *IcmpSocket);
int XS_RemoveIcmpSocket(ICMP_SOCKET *IcmpSocket);

/*----------------------------------*/
/*
 For XS library Ver. 0.9.3.00
*/
#define MAX_PING_SOCKET_NO	6

#ifndef XS_PING_H 
#define XS_PING_H
typedef struct {
	int mode;
	int icmpId;
	unsigned id;
	unsigned seq;
	int length;
	int ReplyCnt;
	int PingCnt;
	int cnt;
	long period,LastSt;
	unsigned char ip[16];
	void (*CallBackFun)(int skt,int mode); //[2008/12/22] 
} PING_STATUS;
#endif

/*
  底下的 XS_IcmpSocket[]/XS_PingStatus[] 成對使用。 
*/

extern ICMP_SOCKET XS_IcmpSocket[MAX_PING_SOCKET_NO];
extern PING_STATUS XS_PingStatus[MAX_PING_SOCKET_NO];
int XS_AddPing(char *IpStr,unsigned id,unsigned startSeq,int PingLength,unsigned PingCnt,long PingPeriod);
int XS_StopPing(int PingId);


void XS_SetupFun(char *cmd);
void XS_SetUserSetupFun(void (*UserDoCmdFun)(char *cmd));
void XS_SetSearchCmdFun(int (*UserSearchCmdFun)(char *cmd));
void XS_SetDoCmdFun(void (*UserDoCmd)(int idx,char *value));

int XS_StartSocket(void);
void XS_StopSocket(void);
void XS_SocketLoopFun(void);

char *XS_GetOsVer(void);
/*
  Get the version of MiniOS7.
*/

#ifdef VARIABLE_SOCKET_NO
	extern long *SocketLastTimeTicks; //[2006/11/06]
#else
	extern long SocketLastTimeTicks[NCONNS]; /* [2006/07/25] Add */
#endif
extern long AnySocketLastTimeTicks; /*[2006/07/26] Add */

extern int bForTheSameClientIP;
extern unsigned long AcceptedClientIp;

/*
  Functions for the function pointer "XS_dPrint".
  *** only for BC++/TC++/TC , CAN NOT WORK with MSC ***
*/
extern int (*XS_dPrint)(const char *fmt,...);
int XS_dPrintFlush(void);
void XS_Set_dPrint(int (*printFun)(const char *fmt,...));
void XS_Reset_dPrint(void);
void XS_Set_dPrintToSocket(int skt);
/*
1. By default, XS_dPrint=_dPrint, so call XS_dPrint() is call _dPrint().
2. When want to use XS_dPrint() to write data to TCP socket,
   call XS_Set_dPrintToSocket(skt); first. The XS_dPrint() will send the message
   to that socket.(Send to buffer first, if the buffer is full or call
   XS_dPrintFlush() will send the data to that socket.)
   If call XS_Set_dPrintToSocket(skt2); set the output socket to another one,
   it also flush the buffer first. 
*/

/*
 [2006/08/09] add, for UDP-Search function
*/
int StrToIp4(char *str,unsigned char *ip);
int StrToMac(char *str,unsigned char *mac);
extern void (*SaveDhcp)(void);
extern void (*SaveAlias)(unsigned char *);

/*
 [2006/08/24]
*/

extern int XS_TcpStatus;
/*
XS_TcpStatus:
0: DOES NOT start tcpip driver yet.
1: use IP address stored in EEPROM.
2: use DHCP to get the IP address.
3: Try to use DHCP but fail, and use the IP address stored in EEPROM.
*/

/*
 [2006/11/21] Add function for COM PORT setting used in UDP search
*/
#ifndef _COM_DATA_
#define _COM_DATA_
typedef struct COM_DATA {
  unsigned long baud;
  char databit;
  char parity;
  char stopbit;
  unsigned char sum;
} *pCOM_DATA,COM_DATA;
#endif

extern COM_DATA *XS_ComData; /* default value is NULL */
extern int XS_MaxComPortNo; /* default value is 0 */
extern void (*XS_SaveComData)(int port); /* default value is NULL */
extern int (*XS_CmdToPort)(unsigned char cmdport);/* default value is NULL */
int XS_SetComPort(unsigned port,char *cmd,int savemode);
/* 
 For UDP search function to support COM PORT setting, the user's program must support:
 1. function XS_CmdToPort() for transfer cmd to com port index.
 2. function XS_SaveComData() for save com port setting value to EEPROM(or other device).
 3. set the vaule of XS_MaxComPortNo.
 4. set the value XS_ComData to the array that store the com port setting value. 
 cmd="BaudRate.Parity.DataBits.StopBits"
 Any value between "15" to "921600" will be assign to the "baud rate".
 'n','e','O','m','s' are used for setting 'Parity'.
 '5','6','7','8' are used for setting 'Data Bits".
 '1','2' are used for setting "Stop Bits"
[example]
  for set the COM3 to 115200,E,7,2, the command in UDP search is
  CMD="COM3=115200.7.E.2"
  The library function will call  port=XS_CmdToPort(CMD[3]); to get the com port index.
  Then it call XS_SetComPort(port,CMD+5); to process the setting.
  In XS_SetComPort() if savemode=1, then it will call  XS_SaveComData(port) to 
save the value to EEPROM. 

If the program need not to set the COM PORT in the UDP search function, just 
IGNORE these variables.
 
*/

/*[XS-09311] Add---------------------------------------------------------------*/
#if _XS_ >= 9311
	void XS_SoftReset(void);

	int XS_IfNeedOsPassword(void);
	int XS_CheckOsPassword(void *pass,int len);
	int XS_SetOsPassword(void *pass,int len);
	extern int (*fpXS_GetLockStatus)(int skt);
	
	extern int (*fpXS_IfNeedPassword)(void);
	extern int (*fpXS_CheckPassword)(void *pass,int len);
	extern int (*fpXS_SetPassword)(void *pass,int len);
	extern int bXS_NeedOsPassword;

	extern DWORD SerialLong;
	
	//extern const char szKey[];
	unsigned Enc20_Decode(const char szEncoded[], const char szPublicKey[], char szPW[]);
	/*
	 char szEncoded[]   : ~ 84 bytes + 1 NULL, encoded password
	 char szPublicKey[] : Public key from 7188E, + 1 NULL
	 char szPW[]        :  1 ~ 30 bytes + 1 NULL, decoded password
	*/	 
	unsigned Enc20_Encode(const char szSerNum4[], const char szPW[], const char szPublicKey[], char szEncoded[]);
	// char szSerNum4[]    : 4-byte serial number (or string) + 1 NULL
	// char szPW[]        : password string, 1 ~ 30 bytes + 1 NULL
	// char szPublicKey[] : Public key from 7188E, + 1 NULL
	// char szEncoded[]   : 84 bytes + 1 NULL

#endif
/*----------------------------------------------------------------------------*/

/*[XS-09312] Add---------------------------------------------------------------*/
extern int (*XS_GetHighRamMode)(void); /* [2007/06/05] add */
/*
 return value: 
 0 --> high ram is ENABLED. 
 != 0 --> high ram is DISABLED.
*/
extern void (*XS_SetHighRam)(int mode); /* [2007/06/05] add */
/*
 For 7186EX/C837/C812 ... that support high ram, must set these two functions pointer
 for the port 10000 command "33dir [B]" to work.
 
 Just add the following two lines in UserInit().
 
  XS_GetHighRamMode=GetHighRamMode;
  XS_SetHighRam=SetHighRam;
*/
/*----------------------------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif	/* _XS_H_*/
