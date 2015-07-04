//*****************************************************************
// 		The following file contains Json Object Creation and 
// 		parsing function prototypes made specifically for Villanova 
//		Seacats - Roboboat 2014 Competition. Function Definitions 
//		are found in the .c file 
// 
//		The header and C file for cJSON is included in the same 
//		folder, which contains descriptions of the function calls 
//		made by this file. The C and header file is licensed under
//		the MIT license (free to use). 
// 
//		Author: Gin Siu Cheng 
// 		Last Modified: 7/11/2014 @ 10:54PM
// 
//*****************************************************************

//***************************************************************
//		Json Parse Functions 
//***************************************************************
int obstacleParse_Entrance(char *str);

int obstacleParse_Exit(char *str);

int dockingParse(char *str); 

int validParse(char *str); 

//****************************************************************
//		Json Object Creation Functions
//****************************************************************
char *acousticObject(int buoyColor, float latitude, float longitude); 

char *beginStr;

char *lightObject(int firstColor, int secondColor, int thirdColor); 

