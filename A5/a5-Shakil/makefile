OBJ = main.o connect.o escape.o flyer.o hero.o interact.o view.o 
EXE = a5
CC = gcc -Wall 

$(EXE):	$(OBJ)
	$(CC) -o $(EXE) $(OBJ)

main.o:	main.c defs.h
	$(CC) -c main.c

connect.o:	connect.c defs.h
	$(CC) -c connect.c

escape.o: escape.c defs.h
	$(CC) -c escape.c

flyer.o: flyer.c defs.h
	$(CC) -c flyer.c

hero.o: hero.c defs.h
	$(CC) -c hero.c

interact.o: interact.c defs.h
	$(CC) -c interact.c

view.o: view.c defs.h
	$(CC) -c view.c

clean:
	rm -f $(EXE) $(OBJ)

