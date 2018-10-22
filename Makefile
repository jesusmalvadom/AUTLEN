CC = gcc

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

all: alfabeto estado palabra

all-test: alfabeto-test estado-test vector-test palabra-test

pre:
	@mkdir $(OBJ_FOLDER)

alfabeto:
	@echo Compilando modulo de alfabeto...
	@$(CC) -c $(LIBRARIES)$(ALFABETO).c -o $(OBJ_FOLDER)$(ALFABETO).o

estado:
	@echo Compilando modulo de estado...
	@$(CC) -c $(LIBRARIES)$(ESTADO).c -o $(OBJ_FOLDER)$(ESTADO).o

palabra:
	@echo Compilando modulo de palabra...
	@$(CC) -c $(LIBRARIES)$(PALABRA).c -o $(OBJ_FOLDER)$(PALABRA).o

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


.PHONY : clean all
clean :
	@rm -rf $(TESTING)pruebas_$(ALFABETO)/*.o
	@rm -rf $(TESTING)pruebas_$(ESTADO)/*.o
	@rm -rf $(TESTING)pruebas_$(PALABRA)/*.o
	@rm -rf $(OBJ_FOLDER)









