Sixt: file.o chaine.o calculus.o
	gcc -o Sixt file.o chaine.o

chaine.o: chaine.h chaine.c
	gcc -c -Wall chaine.c

file.o: file.c chaine.h chained_list.h file.h
	gcc -c -Wall file.c

calculus.o: calculus.h calculus.c chained_list.h
	gcc -c -Wall calculus.c
