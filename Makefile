all: machine

machine: bins/main.o bins/myio.o bins/parse.o bins/logic.o bins/tapescreen.o
	gcc bins/main.o bins/myio.o bins/parse.o bins/logic.o bins/tapescreen.o -o machine

bins/main.o: main.c libs/structs.h
	gcc main.c -c -o bins/main.o

bins/myio.o: libs/myio.h libs/myio.c
	gcc libs/myio.c -c -o bins/myio.o

bins/parse.o: libs/parse.h libs/parse.c libs/structs.h
	gcc libs/parse.c -c -o bins/parse.o

bins/logic.o: libs/logic.h libs/logic.c libs/structs.h
	gcc libs/logic.c -c -o bins/logic.o

bins/tapescreen.o: libs/tapescreen.h libs/tapescreen.c
	gcc libs/tapescreen.c -c -o bins/tapescreen.o

clear:
	rm -f bins/*.o

install: clear machine
	$(shell cp machine /usr/local/bin/maitu4)
	$(info cp machine /usr/local/bin/maitu4)
	$(info App installed succesfull with name maitu4)