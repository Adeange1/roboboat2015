//******************************************************************************
// 		Header file for custom curl function calls to perform HTTP 
//		GET/POST to the judges server made specifically for 
//		Villanova Seacats - Roboboat 2014 Competition.
//
//		Associated C file should be in the same folder. See c file 
//		for function specifics.
//
// 		**IMPORTANT: Make sure to have libcurl installed on your 
//		platform before attempting to compile and run. Simple install 
// 		command (linux):
//		sudo apt-get install libcurl4-gnutls-dev 
//		
//		Author: Gin Siu Cheng 
// 		Last date modified: 7/12/2014, 2:42AM 
//******************************************************************************

// Function to use when data received, it writes the data to a str variable
size_t static write_callback_funct(void *buffer,
                        size_t size,
                        size_t nmemb,
                        void *userp);

// HTTP GET Method to get info about the course (docking,obstacle)
// should return NULL if no data obtained
// Example function call: 
// char *content = server_requestGET("http://demoserver.roboboat.felixpageau.com/obstacleAvoidance/courseA/AUVSI");
char *server_requestGET(char *url); 

// HTTP POST Method to report light sequence
// and report acoustic buoy color and location 
// returns NULL if no data obtained 
// Example function call: 
// char *content = server_requestPOST("http://demoserver.roboboat.felixpageau.com/lightSequence/report/courseA/AUVSI", "{"sequence":["red","green","blue"]});
char *server_requestPOST(char *url, char *jsonStr);

// HTTP POST Method to activate light sequence
// returns NULL if no data obtained
// There isn't much difference between this function and
// the one above, just one less input (since Json Object
// not needed to activate light)
// Example function call: 
// char *content = server_requestPOSTLight("http://demoserver.roboboat.felixpageau.com/lightSequence/activate/courseA/AUVSI");
char *server_requestPOSTLight(char *url);
