/* legoUSB.c */ 
#include "toUSBDev.h"
#ifdef _WIN32 || _WIN64
int motorControl(int handle, double port, double power, double tach, char hold){return -1;}
int initLego(){return -1;}
#else
#include <usb.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int motorWaitUntil(int handle,int port);
void wait(int milliseconds);
int initLego()
{
	int handle;
	handle=usbInit(1684);
	char command[21] = {0,0,77,111,116,111,114,67,111,110,116,114,111,108,50,49,46,114,120,101,0};
	wait(100);	
	usbWrite(handle,command,sizeof(command));
	wait(1000);	
	return handle;
}
int motorControl(int handle, double port, double power, double tach, char hold)
{ 
	unsigned char command[17]={128,9,1,13,52,0,0,0,0,0,0,0,0,0,0,0,0};
	if (tach >99999 || tach<0)
		tach=0;
	command[4]=49+3*((int)tach==0);
	command[5]=48+(int)port;
	if (power<0)
		power=100+-1*power;
	sprintf(command+6,"%3d%6d",(int)power,(int)tach);
	command[15]=50;
	int i;
	usbWrite(handle,command,17);
	if (port==3||port==4)
		port=0;
	else if(port==5)
		port=1;
	
	if (tach>0 && hold=='W')
		motorWaitUntil(handle,(int)port);
	return 0;




}

int motorWaitUntil(int handle,int port)
{
	int i;
	unsigned char command[7] = {128,9,1,3,51,0,0};
	command[5]=port+48;
	unsigned char command2[5] = {0,19,0,0,1};
	unsigned char buf[64];
	usbRead(handle,buf,64);/*flushes a message*/
	memset( buf, 0, sizeof(buf) );
	do
	{
	wait(10);	
	usbWrite(handle,command,sizeof(command));
	wait(10);	
	usbWrite(handle,command2,sizeof(command2));
	wait(10);	
	usbRead(handle,buf,64);
	}while (buf[0]!=2 || buf[1]!=19 || buf[5]!=port+48||buf[6]!=49);


	printf("val=");

	for (i=0;i<20;i++)
	printf("%d ",buf[i]);
	printf("\n");
	unsigned char command3[7] = {128,9,1,1,51,51,0};
	usbWrite(handle,command3,sizeof(command3));	fflush(stdout);
	wait(10);	/*final relaxation pause...*/
	return 0;
}

void wait ( int milliseconds )
{
  clock_t endwait;
  endwait = clock () + (milliseconds * CLOCKS_PER_SEC)/1000 ;
  while (clock() < endwait) {}
}

#endif
