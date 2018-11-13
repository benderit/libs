#include "lib.h"
#include <dirent.h>
#include <dlfcn.h>

void find_so (char * lib1,  char * lib2){
	DIR *dir;
	int i=0;
	char *str;
	struct dirent *entry;

	dir = opendir(".");
	if (!dir) {
		perror("diropen");
		exit(1);
	}

        lib1[0]='.';lib1[1]='/';
        lib2[0]='.';lib2[1]='/';

	while ((entry = readdir(dir))){
		str = entry->d_name+strlen(entry->d_name)-3;
		if((str[0] == '.') && (str[1] == 's') && (str[2] == 'o')){
			i++;
			if(i==1) strcpy(lib1+=2, entry->d_name);
				else{
					strcpy(lib2+=2, entry->d_name);
					break;
				}
		}
	}
	if (i < 2){
		printf("Can't find 2 libs...exit\n");
		exit(1);
	}
	
	lib1-=2; lib2-=2;
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

        if (fun) return fun(arg); else printf("cannot load function\n");

        dlclose(lib);
	
	return 0;
}

void parse_file(char * argfile, char * lib1, char * lib2){
        FILE *file;
        char arr[N];
	printf("\nParsing file %s\n", argfile);
	
        file = fopen(argfile, "r");
	if (!file){ 
		printf("File not found...exit.\n");
		exit(1);
	}

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
	char lib1[N], lib2[N];

	find_so(lib1, lib2);
	printf("\nUsing libs to operate: %s, %s\n\n", lib1, lib2);
	parse_file(argv[1], lib1, lib2);

	return 0;
}
