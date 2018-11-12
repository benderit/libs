# Makefile for World project

run: main.o lib.so lib2.so
	gcc main.o -ldl -o run

main.o: main.c
	gcc -Wall -c main.c

libloader.so: loader.o
	gcc -shared -o libloader.so loader.o -ldl

loader.o: loader.c
	gcc -Wall -fPIC -c loader.c

lib.so: lib.o
	gcc -shared -o lib.so lib.o

lib.o: lib.c
	gcc -Wall -fPIC -c lib.c

lib2.so: lib2.o
	gcc -shared -o lib2.so lib2.o

lib2.o: lib2.c
	gcc -Wall -fPIC -c lib2.c

clean:
	rm -f *.o *.so run
