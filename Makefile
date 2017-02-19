# Makefile-9 : générique

# Nom de l'executable
EXE=tp4
MAKEDEPFILE=Dependencies-$(EXE)

SOURCES=$(wildcard *.c)
OBJETS=$(SOURCES: objets/%.c=%.o)

# Nom du compilateur
CC=gcc
MAKEDEP=gcc -M -MF $(MAKEDEPFILE)

# Options pour le compilateur
#  -g : deboguage
#  -I : include
#  -O : optimisation
CFLAGS=-std=c99


.PHONY: all build clean depend list reset

all: depend build

build: bin/$(EXE)

bin/$(EXE): $(OBJETS)
	@echo "Edition de liens"
	$(CC) -o $@ $(OBJETS) $(CFLAGS)

%.o : %.c
	$(CC) $*.c -c $(CFLAGS)

clean:
	\rm -f *~

reset: clean
	\rm -f *.o

list:
	@ls *.c *.h
	@echo SOURCES=$(SOURCES)
	@echo OBJETS=$(OBJETS)

# exemple de dependences calculees
#proj-main.o: proj-main.c proj-cloner.h
#proj-cloner.o: proj-cloner.c proj-cloner.h proj-fils.h
#proj-fils.o: proj-fils.c proj-fils.h

depend:
	@echo "Calcul des dépendances"
	$(MAKEDEP) $(CFLAGS) $(SOURCES)

-include $(MAKEDEPFILE)
