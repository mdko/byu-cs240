//url_resolver.cpp
//read in, resolve, and output absolute urls
#include <iostream>
#include <cstring>
using namespace std;

const char* home = "/";
const char* relSelf = "#";
const char* sameDir = "./";
const char* upDir = "../";

int main(int argc, char * argv[]){									
	//argv[] is an array of char pointers, should have 3 elements
	if (argc != 3){; 
		cout << "USAGE: Number of arguments is incorrect" << endl;
		return -1;
	}
	char * base = argv[1];
	char * relative = argv[2];											
	//base_url is a pointer to same address that the pointer in argv[1] points to
	
	char rel[100];													
	//make an array because before I was going into the memory space of arg[2] and deleting it
	memcpy(rel,relative,strlen(relative)+1);
	relative = &rel[0];												
	//so I can use this address for pointer arithmetic later
	char* netLocation = base+7;
	if ((strchr(netLocation,'/'))==NULL)							
	//"<scheme>"+"://"=7
		strcat(base,"/");
	char* pathLocation = strchr(netLocation,'/');					
	//start at where netLocation points to, then scan c-string for first '/'--that is where path starts
	char* lastSlash = strrchr(base,'/');							
	//pointer to last '/'
	
	while (strncmp(relative,".",1)==0){
		if (strncmp(relative,sameDir,2)==0){
			*lastSlash = '\0';
			relative += 2;								
		}
		else if (strncmp(relative,upDir,2)==0){
			*lastSlash = '\0';
			lastSlash = strrchr(base,'/');
			*lastSlash = '\0';
			relative += 3;
		}
	}
	if (strncmp(relative,home,1)==0){
		if ((strncmp(base,"file://",7))==0)
			*(base+7)='\0';
		else
			*pathLocation = '\0';
		strcat(base,rel);
	}
	else if (strncmp(relative,relSelf,1)==0){
		strcat(base,relative);
	}
	else{
		*lastSlash = '\0';											
		//if none of the above (eg "images/nasdaq.jpg"), same as if "./"
		strcat(base,"/");
		strcat(base,relative);										
		//we want to keep the slash, because the above doesn't start with a slash
	}
	cout << base << endl;
	return 0;
}
