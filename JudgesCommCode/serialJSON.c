//************************************************************************************
// 		C file to facilicate serial communication between Speedgoat 
//		and the pandaboard. Speedgoat sends a JSON string in the following 
//		form: {"SGR":0,"Lat":+000.000000,"Long":+000.000000,"C1":0,"C2":0,"C3":0}  
//		where SGR is the request number: 
//		0 = No Request
//		1 = Gate Info Request
//		2 = Docking Info Request 
// 		3 = Light Activation Request
//		4 = Light Seq Post Request
//		5 = Acoustic Post Request
//		C1 to 3 are colors for the light sequence and C1 alone would be the buoy color
//		if a request of 5 was given. Lat/Long are GPS data for Request 5
//
//		The code perform HTTP GET/POST to the judges server using the custom curl functs
//	 	calls. Made specifically for Villanova Seacats - Roboboat 2014 Competition. 
//		
//		Note: if light has been successfully activated (req#3), a default msg stating
//		that the light is activated will be sent to Speedgoat and the server won't be pinged again.
//		This is a quick fix to prevent speedgoat from pinging the server a lot in a short 
//		duration of time to activate the light. If we want to ping the light activation again,
//		a reset request must be used (Request 0 resets lightActivated variable)
//
//		Associated C file should be in the same folder. 
//
//		Compile the file using the makefile to create the executable or the following command: 
//		gcc -o serialJSON_A serialJSON.c cJSON.c curlFunct.c jsonFunct.c -lcurl -lm
//
// 		**IMPORTANT: Make sure to have libcurl installed on your 
//		platform before attempting to compile and run. Simple install 
// 		command (linux):
//		sudo apt-get install libcurl4-gnutls-dev 
//		
//		***ALSO SEE LINE 118 for further details on editing IP/PORT
//
//		Author: Gin Siu Cheng 
//		Edited: Adam DeAngelo
// 		Last date modified: 6/29/2015, 11:09AM 
//***************************************************************************************

// Standard #includes.
#include <stdio.h>    /* Standard input/output definitions */
#include <stdlib.h> 
#include <stdint.h>   /* Standard types */
#include <string.h>   /* String function definitions */
#include <unistd.h>   /* UNIX standard function definitions */
#include <fcntl.h>    /* File control definitions */
#include <errno.h>    /* Error number definitions */
#include <termios.h>  /* POSIX terminal control definitions */
#include "jsonFunct.h"
#include "curlFunct.h"
#include "cJSON.h"

int main(){
	
	// General Variables
	int fdSG, objPresent=0, i=0, j=0, lightActivated = 0; 
	int data1=0, data2=0; 
	char sendBuffer[]="CP:0 Dat1:0 Dat2:0 \r\n";  
	char readBuffer[100], placeHolder[1];
	char *str, *lightStr, *acousticStr; 

	// Serial Json Message Variables
	int SGR=0, color1=0, color2=0, color3=0; 
	float latitude=0, longitude=0;

//**************************************************
//		Set serial communications setting 
//		betw. Pandaboard and Speedgoat 
//**************************************************
	// Open Serial Port
	fdSG = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);	
	// If port not opened
	if(fdSG == -1){ 
		printf("Can't Connect to Speedgoat USB0. Exiting Program...\n"); 
		return -1;  
	} 
	
	// Set Paramenters
	else{ 
		struct termios options; 
		
		// Get Port Attributes
		// If can't get attributes
		if(tcgetattr(fdSG,&options)<0){ 
			printf("Can't get SG Serial Attributes. Exiting Program...\n"); 
			return -1; 
		}
		
		// Set Port Attributes
		else{ 
			// Set IO Baud Rate
			cfsetospeed(&options,B115200); 
			cfsetispeed(&options,B115200); 
			
			// 7E1
			options.c_cflag |= PARENB;
			options.c_cflag &= ~PARODD; 
			options.c_cflag &= ~CSTOPB;
			options.c_cflag &= ~CSIZE; 
			options.c_cflag |= CS7;

			options.c_cflag |= (CREAD|CLOCAL);	
			
			// Set Attributes Now
			// If attributes can't be set
			if(tcsetattr(fdSG,TCSANOW,&options)<0){ 
				printf("Can't set SG Serial Attributes. Exiting Program...\n");
				return -1;  
			}
			else{
				// Read Delay, 0 = Default Setting
				fcntl(fdSG,F_SETFL,0);
			}
		}
	}
printf("All Set, Beginning Program\n"); 

// Program runs forever till request of 10 comes in
// Make sure to edit the following: 
// 	1. IP ADDR and PORT 
//		a. Line 135  --> Case 1
//		b. Line 167 --> Case 2
// 		c. Line 197 --> Case 3
//		d. Line 234 --> Case 4
//		e. Line 264 --> Case 5

	while(1){

		// Clean Up - Default Values for all 
		str = NULL; lightStr = NULL, acousticStr = NULL; 
		placeHolder[0]='0';
		sendBuffer[3]='0'; sendBuffer[10]='0'; sendBuffer[17]='0'; 
		longitude = 0; latitude = 0; 
		color1 = 0; color2 = 0; color3 = 0; 
		objPresent = 0; 
		data1 = 0; data2 = 0; 

		// Clear readBuffer
		for(i=0;i<100;i++){ 
			readBuffer[i]='0'; 
		}

		// Read from Speedgoat
		read(fdSG,&readBuffer,sizeof(readBuffer)); 
		printf("Recved from SG..."); 

		// Check for Json Object 
		for(i=0;i<strlen(readBuffer);i++){ 
			if(readBuffer[i]=='{'||readBuffer[i]=='}')
				objPresent++; 
		}

		// If Json Object Present in Serial Message
		// Parse it to get the request info
		if(objPresent==2){ 
					//printf("Got JSON Object From SG\n");
					// Initialization
					cJSON *tmp = cJSON_Parse(readBuffer); 

					// Parse Info 
					SGR = cJSON_GetObjectItem(tmp,"SGR")->valueint; 

					switch(SGR){ 
						// No Request
						case 0: { 
							printf("No Request: Sending Default Message to SG\n"); 
							write(fdSG,sendBuffer,sizeof(sendBuffer)); 
							lightActivated = 0; 
							break; 
						}

						// Gate Info
						case 1: {

							// Perform Request
							printf("\n\nRequesting Gate Info:\n");
							str = server_requestGET("192.168.1.40:9000/obstacleAvoidance/courseA/VU");
							if(str == NULL){ 
								printf("Error in gate request:\n\n");
								write(fdSG,sendBuffer,sizeof(sendBuffer)); 
								printf("Default Message Sent.\n"); 
							} else{
								printf("Received From Server:%s\n\n",str); 

								// Get Gate Info from String
								data1 = obstacleParse_Entrance(str); 
								data2 = obstacleParse_Exit(str);

								// Edit Default Message 
								sprintf(placeHolder,"%1d",data1); 
								sendBuffer[10]=placeHolder[0]; 
								sprintf(placeHolder,"%1d",data2); 
								sendBuffer[17]=placeHolder[0]; 
								sendBuffer[3]='1';

								// Send Message 
								write(fdSG,sendBuffer,sizeof(sendBuffer)); 
								printf("Gate Info Message Sent.\n");
							}
							break; 
						}

						// Docking Info
						case 2: { 
							// Perform Request
							printf("Requesting Docking Info:\n");
							str = server_requestGET("192.168.1.40:9000/automatedDocking/courseA/VU");
							if(str == NULL){ 
								printf("Error in docking request:\n\n");
								write(fdSG,sendBuffer,sizeof(sendBuffer)); 
								printf("Default Message Sent.\n"); 
							} else{
								printf("Received From Server:%s\n\n",str); 

								// Get Docking Info from String
								data1 = dockingParse(str);

								// Edit Default Message
								sprintf(placeHolder,"%1d",data1); 
								sendBuffer[10]=placeHolder[0]; 
								sendBuffer[3]='1';

								// Send Message 
								write(fdSG,sendBuffer,sizeof(sendBuffer)); 
								printf("Dock Info Message Sent.\n");
							}
							break;
						}

						// Activate Light Array
						/*case 3: { 
							// Perform Request
							if(lightActivated==0){ // Light Not Activated Yet
								printf("Activating Light Now:\n"); 
								str = server_requestPOSTLight("192.168.1.40:9000/lightSequence/activate/courseA/VU");
								if(str == NULL){ 
									printf("Error in light Activation:\n\n");
									// Send Default MSG
									write(fdSG,sendBuffer,sizeof(sendBuffer)); 
									printf("Default Message Sent.\n"); 
								} else{
									printf("Received From Server:%s\n\n",str); 

									// Validate 
									data1 = validParse(str);
									if(data1==1)
										lightActivated = 1; 
									// Edit Default Message
									sprintf(placeHolder,"%1d",data1); 
									sendBuffer[10]=placeHolder[0]; 
									sendBuffer[3]='1';

									// Send Message
									write(fdSG,sendBuffer,sizeof(sendBuffer)); 
									printf("\n\nLight Activation Message Sent.\n");
								}
							} else { // Light Already Activated
								printf("\nLight Already Activated,default activated msg.\n");
								sendBuffer[10]='1';
								sendBuffer[3]='1';
								write(fdSG,sendBuffer,sizeof(sendBuffer)); 
							}
							break; 
						}

						// Post Light Sequence
						case 4: { 
							printf("\n\n\nPosting Light Sequence Now:\n");
							// Get Colors For POST Request
							color1 = cJSON_GetObjectItem(tmp,"C1")->valueint; 
							color2 = cJSON_GetObjectItem(tmp,"C2")->valueint; 
							color3 = cJSON_GetObjectItem(tmp,"C3")->valueint; 
		
							// Create Json String 
							lightStr = lightObject(color1, color2, color3);

							// Perform Post
							str = server_requestPOST("192.168.1.40:9000/lightSequence/report/courseA/VU",lightStr);
							if(str == NULL){ 
								printf("Error in light post:\n\n");
								write(fdSG,sendBuffer,sizeof(sendBuffer)); 
								printf("Default Message Sent.\n"); 
							} else{ 
								// Validate 
								data1 = validParse(str);

								// Edit Default Message
								sprintf(placeHolder,"%1d",data1); 
								sendBuffer[10]=placeHolder[0]; 
								sendBuffer[3]='1';

								// Send Message 
								write(fdSG,sendBuffer,sizeof(sendBuffer)); 
								printf("Light Validatio Message Sent.\n");
							}*/
							break; 
						}

						// Post Acoustic Buoy Info
						case 5: { 
							printf("Posting Acoustic Buoy Info Now:\n");
							latitude = cJSON_GetObjectItem(tmp,"Lat")->valuedouble;
							longitude = cJSON_GetObjectItem(tmp,"Long")->valuedouble; 
							color1 = cJSON_GetObjectItem(tmp,"C1")->valueint; 
							acousticStr = acousticObject(color1, latitude, longitude); 
							str = server_requestPOST("192.168.1.40:9000/pinger/courseA/VU",acousticStr);
							if(str == NULL){ 
								printf("Error in acoustic post:\n\n");
								write(fdSG,sendBuffer,sizeof(sendBuffer)); 
								printf("Default Message Sent.\n"); 
							} else{ 
								// Validate 
								data1 = validParse(str);

								// Edit Default Message
								sprintf(placeHolder,"%1d",data1); 
								sendBuffer[10]=placeHolder[0]; 
								sendBuffer[3]='1';

								// Send Message 
								write(fdSG,sendBuffer,sizeof(sendBuffer)); 
								printf("\n\nAcoustic Validation Message Sent.\n");
							}
							break; 
						}

						// End Program 
						case 10:{ 
							printf("Exiting Program...\n");
							goto EXIT; 
							break; 
						}

						// Bad Request
						default: {
							printf("Error: Request Number Invalid. Sending Error Code 2\n");
							sendBuffer[3]='2'; // Error Code of 2 in CP
							write(fdSG,sendBuffer,sizeof(sendBuffer)); 
							printf("Error Message Sent.\n");
							break; 
						}
					}
					// Delete Json Object
					cJSON_Delete(tmp);
		}

		// Default Message, if bad message - no json
		else{
			printf("Bad Message (No Json Object): Sending Default Message\n"); 
			write(fdSG,sendBuffer,sizeof(sendBuffer)); 
			printf("Default Message Sent.\n");
		}

		// Flushing IO Port 
		tcflush(fdSG,TCIOFLUSH);

	}  

EXIT:
close(fdSG);
return 0;
}
