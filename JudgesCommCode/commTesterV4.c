//**************************************************************************************
//		Simple program to test custom curl functions for communications with the judge's
//		server. Made specifically for Villanova Roboboat 2014. The current 
//		IP Address has been set to the demoserver so it can still be 
// 		tested (if the demoserver is still functional), however during the 
//		competition the communications module was connected to the 
//		Roboboat-2014 network and connected to the IP address: 192.168.1.40:9000		
//
// 		Note: The demoserver returns correct for everything you request and als
//		static links were set in each GET/POST command shown below to avoid the need
//		to type them into the command line each time. An obvious drawback is the need
//		to recompile each time, however it reduces the chance of typos made by users
//		if a scanf was used inplace. 
//
// 		Use the makefile to create the executable or use the following command
//		to compile: 
//		gcc -o commTester_Demo commTester.c cJSON.c curlFunct.c jsonFunct.c -lcurl -lm
//		
//		Author: Gin Siu Cheng 
//		Edited: Adam DeAngelo
// 		Last date modified: 6/29/2015, 11:00AM
//**************************************************************************************

#include <stdio.h> 
#include "curlFunct.h"
#include "jsonFunct.h"

int main(){

	// General Variables for placeholding
	char *str; 
	int value1 = 0, value2 = 0; 
	
	printf("Program Started:\n\n");

	// Request Docking 
	printf("Request Docking Info:\n");
	str = server_requestGET("http//ec2-52-7-253-202.compute-1.amazonaws.com/automatedDocking/courseB/VU");//demoserver.roboboat.felixpageau.com/automatedDocking/courseA/VU");
	if(str == NULL){ 
		printf("Request Not Executed\n");
	} else{ 
		printf("main:%s\n\n",str);
		value1 = dockingParse(str);
		printf("Docking Symbol:%d\n",value1);
		value1 = 0; 
		printf("\n\n");
	}

	// Request Obstacle Course
	printf("Request Obestacle Entrance/Exit:\n");
	str = server_requestGET("http//ec2-52-7-253-202.compute-1.amazonaws.com/obstacleAvoidance/courseB/VU");//demoserver.roboboat.felixpageau.com/obstacleAvoidance/courseA/VU"); 
	if(str == NULL){ 
		printf("Request Not Executed\n");
	} else{ 
		printf("main:%s\n\n",str);
		value1 = obstacleParse_Entrance(str);
		value2 = obstacleParse_Exit(str); 
		printf("Entrance:%d, Exit:%d\n",value1,value2);
		value1 = 0; value2 = 0; 
		printf("\n\n");
	}


	// Activate Light 
	//printf("Activate Light Array:\n");
	//str = server_requestPOSTLight("demoserver.roboboat.felixpageau.com/lightSequence/activate/courseA/VU");
	//if(str == NULL){ 
	//	printf("Request Not Executed\n");
	//} else{ 
	//	printf("main:%s\n\n",str);
	//	value1 = validParse(str);
	//	printf("Answer(True=1,False=0):%d\n",value1); 
	//	value1 = 0; 
	//	printf("\n\n");
	//} 

	// Post Light Answer 
	//printf("Post Light Answer:\n");
	//char *lightStr = lightObject(3,4,1); 
	//str = server_requestPOST("demoserver.roboboat.felixpageau.com/lightSequence/report/courseA/VU", lightStr);
	//if(str == NULL){ 
	//	printf("Request Not Executed\n");
	//} else{ 
	//	printf("main:%s\n\n",str);
	//	value1 = validParse(str);
	//	printf("Answer(True=1,False=0):%d\n",value1);
	//	value1 = 0; 
	//	printf("\n\n");
	//}


	// Post Acoustic Answer
	printf("Post Acoustic Answer:\n");
	char *acousticStr = acousticObject(4, 36.80281, -76.19152); 
	str = server_requestPOST("http//ec2-52-7-253-202.compute-1.amazonaws.com/pinger/courseB/VU");//"demoserver.roboboat.felixpageau.com/pinger/courseA/VU", acousticStr);
	if(str == NULL){ 
		printf("Request Not Executed\n");
	} else{ 
		printf("main:%s\n\n",str);
		value1 = validParse(str);
		printf("Answer(True=1,False=0):%d\n",value1);
		value1 = 0; 
		printf("\n\n");
	}

return 0; 
}
