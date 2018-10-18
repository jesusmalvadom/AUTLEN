
#include "stack.h"


struct _Stack {
	
    /* COMPONENTES QUE UTILICES PARA IMPLEMENTAR LA PILA COMO POR EJEMPLO top PARA APUNTAR A LA CIMA O item PARA GUARDAR LOS DATOS EN LA PILA */
    /* CUIDADO... EL TIPO DE DATO GUARDADO EN LA PILA (POR EJEMPLO SI item ES UNA COLECCION) DEBE SER void * (LA COLECCIÓN LO SERÁ DE PUNTEROS TIPO void *  */
	int top;
	void ** items;
    /* ESTOS SON LOS PUNTEROS A LAS FUNCIONES NECESARIAS DE MANIPULACIÓN DEL DATO */
    destroy_element_function_type   destroy_element_function;
    copy_element_function_type      copy_element_function;
    print_element_function_type     print_element_function;
};

/**------------------------------------------------------------------
Inicializa la pila reservando memoria y almacenando los tres punteros a funcion pasados como parametro (el primero para destruir elementos, el segundo para copiar elementos y el tercero para imprimir elementos). Salida: NULL si ha habido error o la pila si ha ido bien
------------------------------------------------------------------*/
Stack * stack_ini(destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3){
	Stack * stack = (Stack *) malloc(sizeof(Stack));
	if(!stack) return NULL;
	stack->top = -1;
	stack->items = NULL; /* Reservamos memoria al pushear */
	stack->destroy_element_function = f1;
	stack->copy_element_function = f2;
	stack->print_element_function = f3;
	return stack;
}
/**------------------------------------------------------------------
Elimina la pila Entrada: la pila que se va a eliminar
------------------------------------------------------------------*/
void stack_destroy(Stack * s){
	int i;
	if(!s) return;
	for (i=0; i <= s->top; i++){
		if(s->items[i]) (s->destroy_element_function)(s->items[i]);
	}
	s->top = -1;
	if(s->items) free(s->items);
	free(s);
	return;
}
/**------------------------------------------------------------------
Inserta un elemento en la pila. Entrada: un elemento y la pila donde insertarlo. Salida: NULL si no logra insertarlo o la pila resultante si lo logra
------------------------------------------------------------------*/
Stack * stack_push(Stack * s, const void * elem){
	/*Casos de error*/
	if(!s) return NULL;
	/*Pila llena*/
	if (stack_isFull(s)) return NULL;
	
	s->top++;
	/*Reservar memoria s->items*/
	s->items = realloc(s->items, sizeof(void*)*(s->top+1));	
	s->items[s->top] = (s->copy_element_function)(elem);
	if(!s->items[s->top]) return NULL;
	return s;
}
/**------------------------------------------------------------------
Extrae un elemento en la pila. Entrada: la pila de donde extraerlo. Salida: NULL si no logra extraerlo o el elemento extraido si lo logra. Notese que la pila quedara modificada
------------------------------------------------------------------*/
void * stack_pop(Stack * s){
	void * it;
	
	/*Casos de error*/
	if(!s) return NULL;
	if(!s->items){
		return NULL;
	} 
	/*Pila vacía*/
	/*if (stack_isEmpty(s)) return NULL;*/
	
	it = s->items[s->top];
	s->items[s->top] = NULL;
	s->items = realloc(s->items, sizeof(void*)*(s->top));	

	s->top--;
	return it;
}
/**------------------------------------------------------------------
Copia un elemento (reservando memoria) sin modificar el top de la pila. 
Entrada: la pila de donde copiarlo. 
Salida: NULL si no logra copiarlo o el elemento si lo logra
------------------------------------------------------------------*/
void * stack_top(const Stack *s){
	if(!s) return NULL;
	return s->copy_element_function(s->items[s->top]);
}
/**------------------------------------------------------------------
Comprueba si la pila esta vacia. 
Entrada: pila. Salida: 
TRUE si está vacía o FALSE si no lo esta
------------------------------------------------------------------*/
Bool stack_isEmpty(const Stack *s){ 
	if(!s) return FALSE;
	return (s->top < 0) ? TRUE : FALSE;
}
/**------------------------------------------------------------------
Comprueba si la pila esta llena. 
Entrada: pila. Salida: TRUE si está llena o FALSE si no lo esta
Recuerda, esta función es típica en cualquier implementación de stack, pero en la que se te pide que realices debería devolver siempre FALSE
------------------------------------------------------------------*/
Bool stack_isFull(const Stack *s) {
	if(!s) return FALSE;
	return FALSE;
}
/**------------------------------------------------------------------
Imprime toda la pila, colocando el elemento en la cima al principio de la impresión (y un elemento por línea). 
Entrada: pila y fichero donde imprimirla. 
Salida: Devuelve el número de caracteres escritos (este valor de retorno es irrelevante)
------------------------------------------------------------------*/
int stack_print(FILE* pf, const Stack *s){
	int i;
	if(!pf || !s) return -1;
	if(!s->items) return -1;
	for(i=s->top; i>=0; i--) {
		(s->print_element_function)(pf, s->items[i]);
	}
	return i;
}

/**------------------------------------------------------------------
Tamaño de la pila
Entrada: pila. 
Salida: Devuelve el número de elementos de la pila (0 si está vacío, -1 si hay algún error)
------------------------------------------------------------------*/
int stack_size(const Stack* s){
	if(!s) return -1;
	return (s->top+1);
}

