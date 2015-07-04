//*****************************************************************
// 		The following file contains Json Object Creation and 
// 		parsing function definitions made specifically for Villanova 
//		Seacats - Roboboat 2014 Competition. 
// 
//		The header and C file for cJSON is included in the same 
//		folder, which contains descriptions of the function calls 
//		made by this file. The C and header file is licensed under
//		the MIT license (free to use). 
// 
//		Author: Gin Siu Cheng 
// 		Last Modified: 7/11/2014 @ 10:54PM
//*****************************************************************
// Make sure to revise the following:
// 1. Acoustic Pinger: 
// 		a. course
//		b. team
//		c. datum


#include <stdio.h> 
#include <stdlib.h> 
#include "cJSON.h" 
#include "jsonFunct.h" 

// Some Useful Variables
const char color1[] = "red"; 
const char color2[] = "white"; // Never Used
const char color3[]= "green"; 
const char color4[] = "blue"; 
const char color5[] = "yellow"; 
const char color6[] = "black"; 
const char symbol1[] = "cruciform"; 
const char symbol2[] = "triangle"; 
const char symbol3[] = "circle"; 

//*****************************************************************
//		 Parsing Section of the Code
//*****************************************************************

// Obstacle Avoidance Task Json Object Parsing Functions
// Entrance Gate: 1, 2, 3
// Exit Gates: 4, 5, 6 (x, y, z)
int obstacleParse_Entrance(char *str){ 
	if(str == NULL){
		printf("Error: Passed NULL as Input Argument\n");
		return -1; 
	}	
	else{
		cJSON *tmp = cJSON_Parse(str); char numConv[1];
		if(!tmp){ 
			printf("Error before: [%s]\n",cJSON_GetErrorPtr());
			return -1; 
		} 
		else {
			char *gateInfo = cJSON_GetObjectItem(tmp,"gateCode")->valuestring; 
			numConv[0]=gateInfo[1];
			switch(atoi(numConv)){ 
				case 1: {
					return 1; 
					break;
				} 
				case 2: {
					return 2; 
					break;
				} 
				case 3: {
					return 3; 
					break; 
				}
				default: {
					return 0; 
					break; 
				}
			}
		}
	}
}

int obstacleParse_Exit(char *str){ 
	if(str == NULL){
		printf("Error: Passed NULL as Input Argument\n");
		return -1; 
	}	
	else{
		cJSON *tmp = cJSON_Parse(str); 
		if(!tmp){ 
			printf("Error before: [%s]\n",cJSON_GetErrorPtr());
			return -1; 
		} 
		else{
			char *gateInfo = cJSON_GetObjectItem(tmp,"gateCode")->valuestring; 
			if(gateInfo[3]=='X'||gateInfo[4]=='X'){
				return 4; 
			}
			else if(gateInfo[3]=='Y'||gateInfo[4]=='Y'){
				return 5; 
			}
			else if(gateInfo[3]=='Z'||gateInfo[4]=='Z'){
				return 6; 
			}
			else{
				return 0; 
			}
		}
	}
}

// Docking Task Json Object Parsing Function
// Cross: 1, Triangle: 2, Circle: 3 
int dockingParse(char *str){ 
	if(str == NULL){
		printf("Error: Passed NULL as Input Argument\n");
		return -1; 
	}	
	else{
		cJSON *tmp = cJSON_Parse(str); 
		if(!tmp){ 
			printf("Error before: [%s]\n",cJSON_GetErrorPtr());
			return -1; 
		} 
		else{
			char *symbolStr = cJSON_GetObjectItem(tmp,"dockingBay")->valuestring; 
			if(strcmp(symbolStr,symbol1)==0){ 
				return 1; 
			}
			else if(strcmp(symbolStr,symbol2)==0){ 
				return 2; 
			}
			else if(strcmp(symbolStr,symbol3)==0){ 
				return 3; 
			}
			else{ 
				return 0; 
			}
			cJSON_Delete(tmp);
		}
	}
}

// Success Checker Json Object Parsing Function 
// 0 = False (Fail), 1 = True (Success), -1 = ERROR
int validParse(char *str){ 
	if(str == NULL){
		printf("Error: Passed NULL as Input Argument\n");
		return -1; 
	}	
	else{
		cJSON *tmp = cJSON_Parse(str); 
		char *outputString; 
		int answer = 0; 
		if(!tmp){ 
			printf("Error before: [%s]\n",cJSON_GetErrorPtr());
			return -1; 
		}
		else{ 
			outputString = cJSON_PrintUnformatted(tmp); 
			answer = cJSON_GetObjectItem(tmp,"success")->valueint; 
			//printf("validParse return: %d\n",answer); 
			cJSON_Delete(tmp); 
			return answer; 
		}
	}
}

//*****************************************************************
// 		Json Object Creation 
//***************************************************************** 

// Acoustic Beacon Task Json Object Creator Function 
char *acousticObject(int buoyColor, float latitude, float longitude){ 
	cJSON *acousticItem, *positions; // JSON Object for Acoustic Task 
	char *outputString; 
	acousticItem = cJSON_CreateObject(); 
	cJSON_AddStringToObject(acousticItem, "course", "courseA"); // MAKE SURE TO REVISE THIS
	cJSON_AddStringToObject(acousticItem, "team", "VU"); // MAKE SURE TO REVISE THIS
	switch(buoyColor){
			cJSON_AddStringToObject(acousticItem, "buoyColor", color1); 
			break; 
		// Green
		case 3: 
			cJSON_AddStringToObject(acousticItem, "buoyColor", color3);
			break; 
		// Blue
		case 4: 
			cJSON_AddStringToObject(acousticItem, "buoyColor", color4);
			break; 
		// Yellow 
		case 5: 
			cJSON_AddStringToObject(acousticItem, "buoyColor", color5);
			break; 
		// Black 
		case 6: 
			cJSON_AddStringToObject(acousticItem, "buoyColor", color6);			
			break; 
		// Guess Blue
		default: 
			cJSON_AddStringToObject(acousticItem, "buoyColor", color4);
			break; 
	}
	cJSON_AddItemToObject(acousticItem, "buoyPosition", positions=cJSON_CreateObject());
	cJSON_AddStringToObject(positions, "datum", "WGS84"); 
	cJSON_AddNumberToObject(positions, "latitude", latitude); 
	cJSON_AddNumberToObject(positions, "longitude", longitude);
	outputString = cJSON_PrintUnformatted(acousticItem); 
	cJSON_Delete(acousticItem); 
	printf("acousticObjectCreated:%s\n",outputString);
	return outputString; 
}

/* char *lightObject(int firstColor, int secondColor, int thirdColor){ 
	cJSON *lightItem, *colorArray; 
	char *outputString; 
	const char *colorSeq[3]; // Const String Array 

	switch(firstColor){ 
		case 1: // Red
			colorSeq[0] = color1; 
			break; 
		case 3: // Green 
			colorSeq[0] = color3; 
			break; 
		case 4: // Blue
			colorSeq[0] = color4; 
			break; 
		case 5: // Yellow
			colorSeq[0] = color5;  
			break; 
		default: // Guess = Blue
			colorSeq[0] = color4; 
			break; 

	}

	switch(secondColor){ 
				case 1: // Red
			colorSeq[1] = color1; 
			break; 
		case 3: // Green 
			colorSeq[1] = color3; 
			break; 
		case 4: // Blue
			colorSeq[1] = color4; 
			break; 
		case 5: // Yellow
			colorSeq[1] = color5; 
			break; 
		default: // Guess = Blue
			colorSeq[1] = color4; 
			break; 
	}

	switch(thirdColor){ 
		case 1: // Red
			colorSeq[2] = color1; 
			break; 
		case 3: // Green 
			colorSeq[2] = color3; 
			break; 
		case 4: // Blue
			colorSeq[2] = color4; 
			break; 
		case 5: // Yellow
			colorSeq[2] = color5; 
			break; 
		default: // Guess = Blue
			colorSeq[2] = color4; 
			break; 
	}

	// Create the Json Object Here After Creating Color String Array
	lightItem = cJSON_CreateObject(); 
	cJSON_AddItemToObject(lightItem, "sequence", colorArray = cJSON_CreateStringArray(colorSeq,3));
	outputString = cJSON_PrintUnformatted(lightItem);
	cJSON_Delete(lightItem);
	printf("lightObjectCreated:%s\n",outputString);
	return outputString;
}*/
