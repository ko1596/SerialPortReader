#include <Windows.h>
#include <stdio.h>
 
HANDLE hCom;
 
int main(void)
{
	hCom = CreateFile(TEXT("com5"),//set COM5
		GENERIC_READ, //allow read
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, 
		NULL);
 
	if (hCom == INVALID_HANDLE_VALUE)
	{
		printf("open COM unsucessus!\n");
		return FALSE;
	}
	else
	{
		printf("open COM sucessused!\n");
	}
 
	SetupComm(hCom, 1024, 1024); //input and outputbuffer
 
	/*********************************setting time out**************************************/
	COMMTIMEOUTS TimeOuts;

	TimeOuts.ReadIntervalTimeout = MAXDWORD;
	TimeOuts.ReadTotalTimeoutMultiplier = 1;
	TimeOuts.ReadTotalTimeoutConstant = 100;

	TimeOuts.WriteTotalTimeoutMultiplier = 1;
	TimeOuts.WriteTotalTimeoutConstant = 1;/
	SetCommTimeouts(hCom, &TimeOuts);
 
	/*****************************************setting Serial Port***************************/
	DCB dcb;
	GetCommState(hCom, &dcb);
	dcb.BaudRate = 115200; //set bit rate to 115200
	dcb.ByteSize = 8; //set byte size
	dcb.Parity = NOPARITY; //set parity
	dcb.StopBits = ONESTOPBIT; //set stop bit
	SetCommState(hCom, &dcb);
 
	DWORD wCount;//the real byte size
	boolean bReadStat;
 
	char str[1] = { 0 };
 
	while (1)
	{
		//PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR); //clear buffer
		bReadStat = ReadFile(hCom, str, sizeof(str), &wCount, NULL);
 
		if (!bReadStat)
		{
			printf("read COM fail!");
			return FALSE;
		}
		else
		{
			str[1] = '\0';
			printf("%c", str[0]);
		}
	}
 
	CloseHandle(hCom);
}