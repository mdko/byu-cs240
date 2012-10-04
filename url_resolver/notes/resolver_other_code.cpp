if (strncmp(relative,home,1)==0){
		*pathLocation = '\0';
		strcat(base,relative);
	}
	else if (strncmp(relative,relSelf,1)==0){
		strcat(base,relative);
	}
	/*else if (strncmp(relative,sameDir,2)==0){
		*lastSlash = '\0';
		strcat(base,relative+1);									//add 1 to address of relative so we concat everything thing in relative starting from slash, not the period
	}
	else if (strncmp(relative,upDir,2)==0){
		*lastSlash = '\0';
		lastSlash = strrchr(base,'/');								//find second to last slash (easy because we said last slash was null in line above)
		*lastSlash = '\0';											//modify end of base so we concat starting where we want
		strcat(base,relative+2);									//add 2 to address so we don't concat '..'
	}*/
	else{
		*(lastSlash+1) = '\0';										//if none of the above (eg "images/nasdaq.jpg"), same as if "./"
		strcat(base,relative);										//we want to keep the slash, because the above doesn't start with a slash
	}
