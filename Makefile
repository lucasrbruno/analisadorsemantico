fileH = headers/
fileC = src/

objetos = main.o automato.o lexico.o utils.o sintatico.o

tp1:	$(objetos)
	gcc $(objetos) -o tp1

main.o:	$(fileC)main.c
	gcc -c -g -Wall -O3 $(fileC)main.c

utils.o:	$(fileH)utils.h	$(fileC)utils.c
	gcc -c -g -Wall -O3 $(fileC)utils.c
	
lexico.o:	$(fileH)lexico.h $(fileC)lexico.c
	gcc -c -g -Wall -O3 $(fileC)lexico.c
	
automato.o:	$(fileH)automato.h $(fileC)automato.c
	gcc -c -g -Wall -O3 $(fileC)automato.c

sintatico.o: $(fileH)sintatico.h $(fileC)sintatico.c
	gcc -c -g -Wall -O3 $(fileC)sintatico.c

clean:
	rm -rf *.o
