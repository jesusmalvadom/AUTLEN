CC = gcc -g

LIBRARIES = lib/
OBJ_FOLDER = $(LIBRARIES)obj/

TESTING = 

ALFABETO = alfabeto
ALFABETO_DEPS = 

ESTADO = estado
ESTADO_DEPS = 

PALABRA = palabra
PALABRA_DEPS = 

VECTOR = vector
VECTOR_DEPS = 

AFND = afnd
AFND_DEPS = 



all: pre alfabeto estado palabra afnd

all-test: pre alfabeto-test estado-test vector-test palabra-test afnd-test

pre:
	@mkdir -p $(OBJ_FOLDER)

alfabeto:
	@echo Compilando modulo de alfabeto...
	@$(CC) -c $(LIBRARIES)$(ALFABETO).c -o $(OBJ_FOLDER)$(ALFABETO).o

estado:
	@echo Compilando modulo de estado...
	@$(CC) -c $(LIBRARIES)$(ESTADO).c -o $(OBJ_FOLDER)$(ESTADO).o

palabra:
	@echo Compilando modulo de palabra...
	@$(CC) -c $(LIBRARIES)$(PALABRA).c -o $(OBJ_FOLDER)$(PALABRA).o

afnd:
	@echo Compilando modulo del AFND...
	@$(CC) -c $(LIBRARIES)afnd.c -o $(OBJ_FOLDER)afnd.o
	@ar cr $(OBJ_FOLDER)afnd.a $(OBJ_FOLDER)palabra.o $(OBJ_FOLDER)estado.o $(OBJ_FOLDER)alfabeto.o $(OBJ_FOLDER)afnd.o
	



alfabeto-test: alfabeto
	@echo Compilando tester del modulo del alfabeto...
	@$(CC) -o pruebas_$(ALFABETO) $(OBJ_FOLDER)$(ALFABETO).o $(LIBRARIES)$(ALFABETO)-test.c

estado-test: estado
	@echo Compilando tester del modulo del estado...
	@$(CC) -o pruebas_$(ESTADO) $(OBJ_FOLDER)$(ESTADO).o $(LIBRARIES)$(ESTADO)-test.c

palabra-test: palabra
	@echo Compilando tester del modulo del palabra...
	@$(CC) -o pruebas_$(PALABRA) $(OBJ_FOLDER)$(PALABRA).o $(LIBRARIES)$(PALABRA)-test.c

vector-test: estado
	@echo Compilando tester del modulo de vector...
	@$(CC) -o pruebas_$(VECTOR) $(OBJ_FOLDER)$(ESTADO).o $(LIBRARIES)$(VECTOR)-test.c

afnd-test: afnd
	@echo Compilando tester del modulo del AFND...
	@$(CC) -o pruebas_$(AFND) $(LIBRARIES)$(AFND)-test.c $(OBJ_FOLDER)$(AFND).a


.PHONY : clean all
clean :
	@rm -rf $(OBJ_FOLDER)
	@rm -rf pruebas_*
	@rm *.dot



