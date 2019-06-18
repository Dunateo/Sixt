Sixt: file.o chaine.o calculus.o initialize.o main.o chained_list.o smartFunctions.o
	gcc -o Sixt file.o chaine.o calculus.o smartFunctions.o initialize.o  chained_list.o main.o

chained_list.o: chained_list.h chained_list.c
	gcc -c -Wall chained_list.c

chaine.o: chaine.h chaine.c
	gcc -c -Wall chaine.c

file.o: file.c chaine.h chained_list.h file.h initialize.h
	gcc -c -Wall file.c

calculus.o: calculus.h calculus.c chained_list.h
	gcc -c -Wall calculus.c

smartFunctions.o: calculus.h chained_list.h smartFunctions.h smartFunctions.c
	gcc -c -Wall smartFunctions.c

initialize.o: initialize.h initialize.c chaine.h file.h chained_list.h
	gcc -c -Wall initialize.c

main.o: calculus.h chained_list.h initialize.h smartFunctions.h main.c
	gcc -c -Wall main.c

clean:
	rm -f *.o *~ core Sixt
