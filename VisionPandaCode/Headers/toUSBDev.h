/*#include <usb.h>
#include <stdio.h>*/
int usbInit(int vendorID);
int usbWrite(int handle,char * input, int length);
int usbRead(int handle, char * output, int length);
