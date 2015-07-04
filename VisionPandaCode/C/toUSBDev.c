/* unixUSB.c */ 
/*1684 for lego  {128,3,32 ,3,244,1} beep*/
#ifdef _WIN32 || _WIN64
/*Windows support to be added*/
int usbInit(int vendorID){return -1;}
int usbWrite(int handle,char * input, int length){return -1;}
int usbRead(int handle,char * output, int length){return -1;}
#else
#include <usb.h>
#include <stdio.h>

int LIBUSB_Configuration=1;
int LIBUSB_Interface=1;
int     sendingEndpoint     = 1;
int     readingEndpoint     = 130;
int     timeout             = 1000;
int numDev=0;
usb_dev_handle **usb_devices;
struct usb_device **descriptor;
int usbInit(int vendorID)
{ 
	int i;
	system("echo host > /sys/devices/platform/musb_hdrc/mode");
	struct usb_bus *busses;
	int tentative=-1;
	for(i=0;i<numDev;i++)
	{
		if (descriptor[i]->descriptor.idVendor==vendorID)
			tentative=i;
	}
	if(tentative==-1)
	{
	usb_init();
	usb_find_busses();
	usb_find_devices();
	busses = usb_get_busses();
    	struct usb_bus *bus;
	char buffer[100];
	for (bus = busses; bus; bus = bus->next) {
    		struct usb_device *dev;
    
    		for (dev = bus->devices; dev; dev = dev->next) {

 		if (dev->descriptor.idVendor == vendorID)
    			{
				printf("found device!\n");
				tentative=newIndex();
				descriptor[tentative]=dev;
				usb_devices[tentative]=usb_open(dev);
				usb_get_string_simple(usb_devices[tentative],dev->descriptor.iSerialNumber,buffer,100);
				printf("MAC=%s\n",buffer);
				usb_set_configuration(usb_devices[tentative],LIBUSB_Configuration);
				usb_claim_interface(usb_devices[tentative],dev->config->interface->altsetting->bInterfaceNumber);
				usb_reset(usb_devices[tentative]);


    			}
    
    		}
    	}
	}



return tentative; 
}

int usbWrite(int handle,char * input, int length)
{
	if (handle==-1)
	{
		printf("Handle does not exist!\n");
		exit(1);	
	}
	/*int i;
	printf("input=");
	for (i=0;i<length;i++)
		printf("%d ", input[i]);
	printf("\n");*/
	return usb_bulk_write(usb_devices[handle],1,(const unsigned char *)input,length,1000);
}
int usbRead(int handle,char * output, int length)
{
	if (handle==-1)
	{
		printf("Handle does not exist!\n");
		exit(1);	
	}
	return usb_bulk_read(usb_devices[handle],readingEndpoint,output,length,1000);
}

int newIndex()
{   
    numDev++;

    if (!usb_devices||!descriptor)
    {
        usb_devices = realloc(NULL,numDev*sizeof(struct usb_dev_handle *));
	descriptor = realloc(NULL,numDev*sizeof(struct usb_device));
    }
    else
    {
	usb_devices = realloc(usb_devices,numDev*sizeof(struct usb_dev_handle *));
	descriptor = realloc(descriptor,numDev*sizeof(struct usb_device));
    }
    if (!usb_devices||!descriptor)
        error("Realoc error when creating new sockets!");
    return (numDev-1);
}

#endif
