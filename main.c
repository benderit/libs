#include "lib.h"
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <dlfcn.h>
//#define N 256

void find_so (char *lib1, char *lib2){
	DIR *dir;
	int i=0;
	char *str;
	struct dirent *entry;

	dir = opendir(".");
	if (!dir) {
		perror("diropen");
		exit(1);
	}

	while ( (entry = readdir(dir)) != NULL) {
		str = entry->d_name;
		str+=strlen(str)-3;
		if(str[0] == '.') if(str[1] == 's') if(str[2] == 'o'){
			i++;
			if(i==1) strcpy(lib1, entry->d_name);
				else{
					strcpy(lib2, entry->d_name);
					break;
				}
		}
	}
	closedir(dir);
}

char * execute(char * libname, char * arg){
        void * lib;
        char * (*fun)(char *);
        lib = dlopen(libname, RTLD_LAZY);
        if (!lib) {
                printf("cannot open library\n");
                return 0;
        }
        fun = dlsym(lib, "processString");

        if (fun == NULL ) {
                printf("cannot load function\n");
        } else {
		return fun(arg);
        }
        dlclose(lib);
	
	return "";
}

void parse_file(char * argfile, char * lib1, char * lib2){
        FILE *file;
        char arr[N];
	printf("\nparsing file %s\n", argfile);
	
        file = fopen(argfile, "r");
	while(fgets(arr, N, file) != NULL){
                printf("\nLine from file: %s\n", arr);
		printf("lib1: %s\n", execute(lib1, arr));
		printf("lib2: %s\n", execute(lib2, arr));
        }

        fclose(file);
}

int main(int argc, char *argv[]) {
        if (argc < 2) { //проверка на кол-во введенных параметров
                fprintf (stderr, "Please input text filename to parse\n");
                return 1;
        }

	char *lib1 = (char *) malloc(sizeof(char)*N);
	char *lib2 = (char *) malloc(sizeof(char)*N);
	lib1+=2;
	lib2+=2;

	find_so(lib1, lib2);
	printf("\nUsing libs to operate: %s, %s\n\n", lib1, lib2);

	lib1-=2;
	lib2-=2;

	lib1[0]='.';lib1[1]='/';
	lib2[0]='.';lib2[1]='/';

	parse_file(argv[1], lib1, lib2);

        free(lib1);
        free(lib2);
	return 0;
}
