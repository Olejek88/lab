#include <stdio.h>
#include <dos.h>
#include <stdarg.h>
#include <string.h>

#include "service.h"
#include "..\lib\7186e.h"

#define	byte	unsigned char
#define	uint	unsigned int

#define MAIN_FILE	"data.log"
#define XML_FILE	"data.xml"

FILE    *Dat;
void ULOGW (char* string, ...);		// log file function
FILE	*Log;

extern	char	mainlog[100];			// main log file
extern	byte	FinishWork;
//void ULOGW (char* string, ...);		// log file function

byte WriteDataFile ();
byte WriteDataFile2 ();
uint ParseFile (char* buf, char* param);

//----------------------------------------------------------------------------------------------------
// [Thread] service thread
void ServiceThread ()
{
 WriteDataFile ();
 WriteDataFile2 ();
}
//----------------------------------------------------------------------------------------------------
// get data from SQL and save to CSV(0)/XML(1) file
byte WriteDataFile ()
{
/* char   buf[300],date[50];
 Dat =  fopen(XML_FILE,"w");
 struct date dat;
 struct time tim;
 getdate (&dat);
 gettime (&tim);

 sprintf (date,"%d-%02d-%02d %02d:%02d:%02d",dat.da_year,dat.da_mon,dat.da_day,tim.ti_hour,tim.ti_min,tim.ti_sec);

 sprintf (buf,"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"); fprintf (Dat, buf);
 sprintf (buf,"<date>%s</date>\n",date); fprintf (Dat, buf);

 sprintf (buf,"<stats>\n"); fprintf (Dat, buf);
 sprintf (buf,"</stats>\n"); fprintf (Dat, buf);

 sprintf (buf,"<inputs>\n"); fprintf (Dat, buf);
 sprintf (buf,"</inputs>\n"); fprintf (Dat, buf);

 sprintf (buf,"<values>\n"); fprintf (Dat, buf);
 //sprintf (buf,"<value =\"T_water_stolv\" value=\"%f\" time=\"%s\">\n",T_water_stolv,date); fprintf (Dat, buf);
 sprintf (buf,"</values>\n"); fprintf (Dat, buf);

 fclose (Dat);*/
 return 1;
}
//----------------------------------------------------------------------------------------------------
// get data from SQL and save to CSV(0)/XML(1) file
byte WriteDataFile2 ()
{
/* char   buf[300],date[50];
 Dat =  fopen(MAIN_FILE,"w");
 struct date dat;
 struct time tim;
 getdate (&dat);
 gettime (&tim);
 sprintf (date,"%d-%02d-%02d %02d:%02d:%02d",dat.da_year,dat.da_mon,dat.da_day,tim.ti_hour,tim.ti_min,tim.ti_sec);
 //sprintf (buf,"%s\tP=%.4f,L=%.4f,V=%.4f|Tp=%.2f,(Ti=%.3f,To=%.3f),[Ta=%.4f],(Tpr=%.2f,Tst=%.2f),V(%.2f,%.2f,%.2f,%.2f)\n",date,P_par_tech,L_water_bak_accum,V_water_bak_accum,T_par_in_heater,T_water_in_heater,T_water_out_heater,T_water_bak_accum,T_water_prach,T_water_stolv,V1_dushCGTS,V2_dushPFI,V3_stol,V4_prach);
 fprintf (Dat, buf);
 fclose (Dat);*/
 return 1;
}
//----------------------------------------------------------------------------------------------------
// log/output function
void ULOGW (char* string, ...)
{
 char 	buf[300],dates[200],buf3[100],buf4[100];
 struct date dat;
 struct time tim;
 TIME_DATE	tm;
 FILE_DATA	fd;
 GetTimeDate (&tm);
// OS7_FileDateTimeMode=2;
 strncpy (fd.fname,mainlog,12);
 sprintf (dates,"%d-%02d-%02d %02d:%02d:%02d",tm.year,tm.month,tm.day,tm.hour,tm.minute,tm.sec);

// OS7_OpenWriteFile (0);
 va_list arg;
 va_start(arg, string);
 vsprintf(buf4,string, arg);
 va_end(arg);

 sprintf (buf,"%s\t%s\n",dates,buf4);
 //_snprintf (buf,sizeof(buf)-1,"%s %s %s\n",buf2,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds,buf4);
 //fprintf (Log, buf);
 printf ("%s",buf);
// OS7_WriteFile (0,buf,sizeof(buf));
// OS7_CloseWriteFile (0,&fd);
}
