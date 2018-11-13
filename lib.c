#include "lib.h"

extern char * processString(char * s){
	char *str = (char *) malloc(sizeof(char)*N);
	int i, j;

	j=strlen(s)-2;
	for(i=0;i<strlen(s);i++){
		str[i]=s[j];
		j-=1;
	}
	str[i+1]=0;

	return str;
}
