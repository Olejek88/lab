/*
Serial.c: Retrieves the 64-bit hardware unique serial number.

Compiler: BC++ 3.1,
          Turbo C++ 1.01(3.01) (free from http://cc.codegear.com/free/cpp)
          MSC 6.0,
          MSVC 1.52.

Compile mode: Large

Project: serial.c
         ..\..\Lib\(8000e.Lib, 7188el.Lib or 7186el.Lib)

Hardware: i-7188/uPAC-7186/i-8000

Detail description:
    The 64-bit hardware unique serial number is used to 
    protect use's software. Not every controller equips it. 
    You must check the detail specifics of the contorller. 
    
    You can type command 'Ver' under 7188> or i-8000> prompt to 
    list the number. If the controller doesn't equip a unique number,
    it shows 5A 5A 5A 5A 5A 5A 5A 5A. 

[Oct 30, 2008] by Liam
*/

#include <conio.h>
#include <stdio.h>
#include "7186e.h"
#include "Tcpip32.h"
#include "MFW.h"
#include "MBTCP_XS.h"

void main(void)
{
    char cProtectID[8]={0x01, 0xF1, 0x61, 0x52, 0x0A, 0x00, 0x00, 0x11};
    char cSerialNumber[8];
    int bSerialNumOk;
    int i, iRet;

    unsigned char Array_DI[100];
    unsigned char Array_DO[100];
    int Array_AI[100];
    int Array_AO[100];
    InitLib();

InitModbus(Array_DI,Array_DO,Array_AI,Array_AO);

		//Giving initial values.
		Array_DI[0]=1;
		Array_DO[10]=0;
		Array_AI[5]=100;
		Array_AO[20]=-500;

    bSerialNumOk=1;     // Assume the ID is ok at beginning.
    iRet=GetSerialNumber(cSerialNumber);
    if(iRet==NoError)
    {
	for(i=0; i<8; i++)
        {          
            if(cSerialNumber[i]!=cProtectID[i])
            {
                bSerialNumOk=0;
                break;
            }
        }
    }
    
    if(bSerialNumOk)
        Print("ID Ok!\r\n");    
    else 
        Print("ID error!\r\n");
}