#include "lib.h"

extern char * processString(char * s){
	char *str = (char *) malloc(sizeof(char)*N);
	int i;

	for(i=0;i<strlen(s);i++) str[i+1]=s[i];
	
	str[0]='"';
	str[i]='"';
	str[i+1]=0;

	return str;
}
