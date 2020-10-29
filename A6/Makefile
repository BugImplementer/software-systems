# Make file to build polynomial application

polyapp: polyapp.o poly.o utils.o
	gcc -o polyapp polyapp.o poly.o utils.o

polyapp.o: polyapp.c poly.h	utils.h
	gcc -c polyapp.c

poly.o: poly.c utils.h
	gcc -c poly.c

utils.o: utils.c
	gcc -c utils.c

# Just a useful aspect of having a make file.
clean:
	rm -f polyapp polyapp.o poly.o utils.o
