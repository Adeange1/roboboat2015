//******************************************************************************************
//	Author: Gin Siu Cheng 	
// 
//  Program that faciliates communication between Speedgoat and Lidar-Pandaboard 
//	The program does the following: 
//	1. Connects to a usb port (with a serial adapter attached)
//  2. Sets up the required baudrate and 8N1 settings 
//  3. Sends a message to the Speedgoat regarding the color of a buoy detected 
//  4. Waits for a confirmation from the Speedgoat that it received the message, else
//     re-sends the message till it receives a confirmation
//  
//  This program will be incorporated into a S-Function
//  
//	Version: 2.0			Date: 6/18/2014
//******************************************************************************************

#include <stdio.h> 		/* Standard I/O definitions */
#include <stdlib.h> 	
#include <unistd.h> 	/* UNIX standard function definitions */ 
#include <termios.h> 	/* POSIX terminal control definitions */ 
#include <errno.h> 		/* Error number definitions */ 
#include <fcntl.h> 		/* File control definitions */ 


int main(){ 
	
// Variables to include in the global section of the S-Function
	int fd, i; // file descriptor for usb port and 
	char readBuffer[6];
	char sendBuffer[] = "MSG:0 Color:0\r\n";
// Open USB Port for writting and setting up baud rate and 8N1
// This section should be placed into MDLSTART
	
	fd = open("/dev/ttyUSB0",O_RDWR | O_NOCTTY | O_NDELAY);
				
	if (fd == -1){ // file pter for serial not established
		printf("Can't Open Serial Port.Exiting Program...\n"); 
		return 0; 
	} 	
	else{ // file pter for usb port established
		struct termios options;  
		if(tcgetattr(fd,&options)<0){ // can't get current options for usb port
			printf("Cant get term attributes. Exiting Program...\n"); 
			return 0; 
		}
		else{ // got current options for usb port 
			cfsetispeed(&options,B115200); // Set IO baud rates to 115200
			cfsetospeed(&options,B115200); 
			
		    // 8N1
			//options.c_cflag &= ~PARENB; // Enable Parity
			options.c_cflag &= ~CSTOPB; // Stop Bit
			options.c_cflag &= ~CSIZE; // Character size
			options.c_cflag |= CS8; // 8 bits
		      
	
	      // Local Mode and Serial Data Receive
			options.c_cflag |= CREAD | CLOCAL; // turn on read and ignore ctrl lines 
		
			if(tcsetattr(fd,TCSANOW,&options)<0){ // if can't set attributes 
				printf("Can't set term attributes. Exiting Program...\n");
				return 0; 
			}
			
			fcntl(fd,F_SETFL,0);
		}
	}
// Write to usb port after received color of buoy
// This part of the code should be placed into MDLOUTPUTS
		int input = 2; char color[1];
		sprintf(color,"%d",input); printf("input:%c\n",color[0]);
		sendBuffer[12]=color[0]; 
		printf("%s\n", sendBuffer);
		 /*
		while(1){	 
			read(fd,readBuffer,sizeof(readBuffer));
			printf("%s\n",readBuffer);
		      	if(readBuffer[0] == 'M' &&
		      	   readBuffer[1] == 'S' &&
		           readBuffer[2] == 'G' &&
		           readBuffer[3] == 'S'){		
				printf("Message Received\n");break;
			} 
		}*/
		while(1){ 
			read(fd,readBuffer,sizeof(readBuffer));
			write(fd,&sendBuffer,sizeof(sendBuffer));  
			printf("Message Sent\n");
		}





// Close file descriptor to USB Port
// This part of the code should be placed into MDLTERMINATES	
	close(fd);

return 0; 
}
