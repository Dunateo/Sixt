Sixt: file.o chaine.o calculus.o intitialize.o main.o
	gcc -o Sixt file.o chaine.o calculus.o intitialize.o main.o

chaine.o: chaine.h chaine.c
	gcc -c -Wall chaine.c

file.o: file.c chaine.h chained_list.h file.h
	gcc -c -Wall file.c

calculus.o: calculus.h calculus.c chained_list.h
	gcc -c -Wall calculus.c

initialize.o: initialize.c initialize.h chaine.h file.h chained_list.h
	gcc -c -Wall initialize.c

main.o: calculus.h chained_list.h initialize.h
	gcc -c -Wall main.c
