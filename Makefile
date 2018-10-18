CC = gcc

LIBRARIES = lib/

OBJ_FOLDER = $(LIBRARIES)obj/

ALFABETO = alfabeto
ALFABETO_DEPS = 

all: alfabeto

all-test: alfabeto-test 

pre:
	@mkdir $(OBJ_FOLDER)

alfabeto:
	@echo Compilando modulo de alfabeto...
	@$(CC) -c $(LIBRARIES)$(ALFABETO).c -o $(OBJ_FOLDER)$(ALFABETO).o

alfabeto-test: alfabeto
	@echo Compilando tester del modulo del alfabeto...
	@$(CC) -o $(LIBRARIES)$(ALFABETO)-test $(OBJ_FOLDER)$(ALFABETO).o $(LIBRARIES)$(ALFABETO)-test.c

.PHONY : clean all
clean :
	@rm -f $(LIBRARIES)test_$(ALFABETO)
	@rm -f $(OBJ_FOLDER)*.o