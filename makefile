GTK_CFLAGS = $(shell pkg-config --cflags gtk+-3.0)
GTK_LDFLAGS = $(shell pkg-config --libs gtk+-3.0)

Sixt: file.o chaine.o calculus.o initialize.o chained_list.o smartFunctions.o IHM.o getter.o
	gcc file.o chaine.o calculus.o smartFunctions.o initialize.o  chained_list.o  getter.o IHM.o  $(GTK_LDFLAGS) $(GTK_CFLAGS) -o Sixt

chained_list.o: chained_list.h chained_list.c calculus.o
	gcc -c -Wall chained_list.c

chaine.o: chaine.h chaine.c
	gcc -c -Wall chaine.c

getter.o: getter.c getter.h
	gcc -c -Wall getter.c

file.o: file.c chaine.h chained_list.h file.h initialize.h
	gcc -c -Wall file.c

calculus.o: calculus.h calculus.c chained_list.h
	gcc -c -Wall calculus.c

smartFunctions.o: calculus.h chained_list.h smartFunctions.h smartFunctions.c
	gcc -c -Wall smartFunctions.c

initialize.o: initialize.h initialize.c chaine.h file.h chained_list.h
	gcc -c -Wall initialize.c

IHM.o : calculus.h chained_list.h initialize.h getter.h IHM.c IHM.h
	gcc  -c -Wall IHM.c $(GTK_CFLAGS)

clean:
	rm -f *.o *~ core Sixt
