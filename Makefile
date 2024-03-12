CC=gcc
FLAGS=-Wall -g

PROJECT_DIR=${PWD}
SDL_LIB_DIR=${PROJECT_DIR}/lib
SDL_INC_DIR=${PROJECT_DIR}/include

LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I${SDL_INC_DIR}
PROG=jeu

all: jeu
jeu: main.o fonctions.o menu.o entite.o
	${CC} main.o entite.o fonctions.o menu.o -o bin/${PROG} ${LIBS} ${INCS} ${FLAGS}
	./bin/jeu
	make clean

main.o: main.c src/fonctions.h src/menu.h
	${CC} -c main.c

fonctions.o: src/fonctions.c
	${CC} -c src/fonctions.c

menu.o: src/menu.c src/fonctions.h
	${CC} -c src/menu.c

entite.o: src/entite.c src/entite.h
	${CC} -c src/entite.c

clean:
	rm -f *.o

msproper: clean
	rm -i bin/${PROG}
