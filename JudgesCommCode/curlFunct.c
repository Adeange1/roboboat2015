//************************************************************************
// 		C file for custom curl function calls to 
//		perform HTTP GET/POST to the judges server made specifically for 
//		Villanova Seacats - Roboboat 2014 Competition. 
//		
//		Associated C file should be in the same folder. 
//
// 		**IMPORTANT: Make sure to have libcurl installed on your 
//		platform before attempting to compile and run. Simple install 
// 		command (linux):
//		sudo apt-get install libcurl4-gnutls-dev
//		
//		Author: Gin Siu Cheng 
//		Edited: Adam DeAngelo
// 		Last date modified: 6/29/2015, 11:05AM 
//***********************************************************************
#include <curl/curl.h> 
#include <curl/easy.h> 
#include <string.h> 
#include "curlFunct.h"

// Function to use when data received, it writes the data to a str variable
size_t static write_callback_funct(void *buffer, size_t size, size_t nmemb, void *userp){
    char **response_ptr =  (char**)userp;
    *response_ptr = strndup(buffer, (size_t)(size *nmemb));
}

// HTTP GET Method to get info about the course (docking,obstacle)
// should return NULL if no data obtained
// Example function call: 
// char *content = server_requestGET("http://demoserver.roboboat.felixpageau.com/obstacleAvoidance/courseA/AUVSI");
char *server_requestGET(char *url){ 
	// Handle to Curl Object and function return code (res)
	CURL *curl_handle; 
	CURLcode res; 

	// HTTP Response Code
	int http_code; 

	// Pointer to response from server 
	char *response = NULL; 

	// Initial curl and set url 
	curl_handle = curl_easy_init(); 
	if(curl_handle){
		// Set URL and HTTP
		curl_easy_setopt(curl_handle, CURLOPT_URL, url); 
		curl_easy_setopt(curl_handle, CURLOPT_HTTPGET, 1); 

		// set callback function to return the data 
		// passing the pointer to the response as the callback parameter
		curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback_funct);
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &response); 
		
		// Perform request and check for errors 
		res = curl_easy_perform(curl_handle);
		curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &http_code);

		// Check Curl Return 
		if(res != CURLE_OK){
			printf("Note: Write to application Error is OK!\n"); // Will be fixed in later code verions
			fprintf(stderr,"curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
			// Can't Connect To Server Error
			if(res == CURLE_COULDNT_CONNECT){
				response = NULL; 
				printf("Error Connecting to Host.\n"); 
				return response; 
			}
		}

		// Check HTTP Status Code
		if(http_code != 200){
			if(http_code == 503)
				printf("RETRY Request\n");
			response = NULL; 
			printf("Error, Status Code: %d\n",http_code);
		}

		// Clean Up Curl
		curl_easy_cleanup(curl_handle);
	}
	return response; 
}

// HTTP POST Method to report light sequence
// and report acoustic buoy color and location 
// returns NULL if no data obtained 
// Example function call: 
// char *content = server_requestPOST("http://demoserver.roboboat.felixpageau.com/lightSequence/report/courseA/AUVSI", "{"sequence":["red","green","blue"]});
char *server_requestPOST(char *url, char *jsonStr){ 
	// Handle to Curl Object and function return code (res)
	CURL *curl_handle; 
	CURLcode res; 

	// Pointer to response from server
	char *response = NULL; 

	// HTTP Code 
	int http_code; 

	// Change Content-Type to Application/Json
	struct curl_slist *headers = NULL; 
	headers = curl_slist_append(headers, "Content-Type: application/json");

	// Create Curl Object
	curl_handle = curl_easy_init(); 
	if(curl_handle){ 
		// Set URL and other parameters
		curl_easy_setopt(curl_handle, CURLOPT_URL, url); 
		curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, jsonStr); 

		// set callback function to return the data 
		// passing the pointer to the response as the callback parameter
		curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback_funct);
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &response);

		// Set Post Length and Header (Content-Type in this case only)
		curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, (long)strlen(jsonStr));
		curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers);

		// Perform request and check status
		res = curl_easy_perform(curl_handle);
		curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &http_code);

		// Check CURL Return
		if(res != CURLE_OK){
			printf("Note: Write to application Error is OK!\n");
			fprintf(stderr,"curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
			// Can't Connect to Server Error
			if(res == CURLE_COULDNT_CONNECT){
				response = NULL; 
				printf("Error Connecting to Host.\n"); 
				return response; 
			}
		}

		// Check HTTP Status Code
		if(http_code != 200){
			if(http_code == 503)
				printf("RETRY Request\n"); 
			//response = NULL; 
			printf("Error, Status Code: %d\n",http_code);
		}

		// Clean Up Curl
		curl_easy_cleanup(curl_handle);
	}
	return response; 
}
 

// HTTP POST Method to activate light sequence
// returns NULL if no data obtained
// There isn't much difference between this function and
// the one above, just one less input (since Json Object
// not needed to activate light)
// Example function call: 
// char *content = server_requestPOSTLight("http://demoserver.roboboat.felixpageau.com/lightSequence/activate/courseA/AUVSI")
char *server_requestPOSTLight(char *url){ 
	// Handle to Curl Object
	CURL *curl_handle; 
	CURLcode res; 

	// Pointer to resposne from server
	char *response = NULL; 

	// HTTP CODE
	int http_code; 

	// Change Content-Type 
	struct curl_slist *headers = NULL; 
	headers = curl_slist_append(headers, "Content-Type: application/json");

	// Create Curl Object
	curl_handle = curl_easy_init(); 
	if(curl_handle){ 
		// Set URL
		curl_easy_setopt(curl_handle, CURLOPT_URL, url); 
		curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, ""); 

		// Set Writeback Funct
		curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback_funct);
		curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &response);

		// Set Post Length/Headers
		curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, 0);
		curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers);

		// Perform request and check status
		res = curl_easy_perform(curl_handle);
		curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &http_code);

		// Check CURL 
		if(res != CURLE_OK){
			printf("Note: Write to application Error is OK!\n");
			fprintf(stderr,"curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
			// Error Connecting to server
			if(res == CURLE_COULDNT_CONNECT){
				response = NULL; 
				printf("Error Connecting to Host.\n"); 
				return response; 
			}
		}

		// Check HTTP Code
		if(http_code != 200){
			if(http_code == 503)
				printf("RETRY Request\n");
			response = NULL; 
			printf("Error, Status Code: %d\n",http_code);
		}
		// Clean Up Curl
		curl_easy_cleanup(curl_handle);
	}
	return response; 
}
