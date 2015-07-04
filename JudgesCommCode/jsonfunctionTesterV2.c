//************************************************************************************
//		Simple program to test custom json functions for the Roboboat 2014 
//		competition. 
//
// 		Use the makefile to create the executable or use the following command
//		to compile: 
//		gcc -o jsonTester jsonTester.c cJSON.c jsonFunct.c -lm
//		
//		Interesting thing to note is even if there are trailing numbers
//		behind the json object, the parse is still successful and the numbers
//		are ignored.
//
//		Author: Gin Siu Cheng 
//		Edited: Adam DeAngelo
// 		Last date modified: 6/29/2015, 11:10AM
//************************************************************************************

#include <stdio.h> 
#include <string.h> 
#include "cJSON.h"
#include "jsonFunct.h"

int main(){ 
	// All Needed Variables For Test 
	int value; 
	char str[] ="{\"success\":true}";
	char str2[] = "{\"success\":false}";
	char str3[] = "{\"dockingBay\":\"cruciform\"}"; 
	char str4[] = "{\"dockingBay\":\"triangle\"}";
	char str5[] = "{\"dockingBay\":\"circle\"}"; 
	char str6[] = "{\"gateCode\":\"(3,X)\"}";
	char str7[] = "{\"gateCode\":\"(3,Y)\"}";
	char str8[] = "{\"gateCode\":\"(3,Z)\"}";
	char *acousticStr, *lightStr; 

	// Valid Parse Function Test 
	printf("Valid Function Test (True,False):\n");
	value = validParse(str); 
	printf("Main Function Value: %d\n",value); 
	value = validParse(str2); 
	printf("Main Function Value: %d\n\n",value); 

	// Docking Parse Test 
	printf("Docking Parse Test:\n");
	printf("Server:%s\n",str3);
	value = dockingParse(str3);
	printf("FirstSymbol(cruciform=1):%d\n",value);
	printf("Server:%s\n",str4);
	value = dockingParse(str4);
	printf("SecondSymbol(triangle=2):%d\n",value);
	printf("Server:%s\n",str5);
	value = dockingParse(str5);
	printf("ThirdSymbol(circle=3):%d\n\n",value);

	// Obstance Entrance and Exit Test 
	printf("Obstance Entrance and Exit Test\n"); 
	value = obstacleParse_Entrance(str6); 
	printf("Main Function: Entrance: %d\n",value); 
	value = obstacleParse_Exit(str6); 
	printf("Main Function: Exit: %d\n\n",value);
	value = obstacleParse_Entrance(str7); 
	printf("Main Function: Entrance: %d\n",value); 
	value = obstacleParse_Exit(str7); 
	printf("Main Function: Exit: %d\n\n",value);
	value = obstacleParse_Entrance(str8); 
	printf("Main Function: Entrance: %d\n",value); 
	value = obstacleParse_Exit(str8); 
	printf("Main Function: Exit: %d\n\n",value);

	// Acoustic Object Creation 
	printf("Acoustic Object Creation Test\n");
	acousticStr = acousticObject(3, 40.689249, -74.044500); 
	printf("StrLen:%zu\nContent:\n%s\n\n",strlen(acousticStr), acousticStr);

	// Light Object Creation 
	/*printf("Light Object Creation\n");
	lightStr = lightObject(1,3,3); 
	printf("StrLen:%zu\nContent:\n%s\n",strlen(lightStr),lightStr);*/

return 0; 
}
