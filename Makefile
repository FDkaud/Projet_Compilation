CC = gcc
FLEX = ./flex

LIBS = -lm 
CCFLAGS = -Wall -ggdb

OBJ = analyseur_lexical_flex.o util.o analyseur_syntaxique.o

all: compilateur

compilateur: compilateur.c $(OBJ)
	$(CC) $(CCFLAGS) -o compilateur compilateur.c $(OBJ)

analyseur_lexical_flex.c: analyseur_lexical.flex
	$(FLEX) -o $@ $^

analyseur_lexical_flex.o: analyseur_lexical_flex.c
	$(CC) $(CCFLAGS) -c $^

analyseur_syntaxique.o: analyseur_syntaxique.c analyseur_syntaxique.h
	$(CC) $(CCFLAGS) -c $^

util.o: util.c
	$(CC) $(CCFLAGS) -c $^

.PHONY : clean

clean:
	- rm -f $(OBJ)
	- rm -f compilateur
	- rm -f analyseur_lexical_flex.c
