#include "Common.h"
#include "Stack.h"
/********************************************
    .En la siguiente implementación de Stack se utilizó LinkedList
    .
    *********************************************/

struct Nodo {
    int valor;
    Nodo* siguiente;
};

struct StackRepr {
    int tam;
    Nodo* tope;
};

Stack emptyS() {
    StackRepr* s = new StackRepr;
    s->tam=0;
    s->tope =NULL;
    return s;
}

int sizeS(Stack s) {
    return s->tam;
}

void pushS(Stack s, int x) {
    Nodo* newNode = new Nodo;
    newNode->valor = x;
    newNode->siguiente = s->tope;
    s->tope = newNode;
    s->tam++;
}

int topS(Stack s) {
    return s->tope->valor;
}

void popS(Stack s) {
    Nodo* tmp = s->tope->siguiente;
    delete s->tope;
    s->tope= tmp;
    s->tam--;
}


void destroyS(Stack s) {
    while(s->tope != NULL)
    {
        popS(s);
    }
    delete s;
    s = NULL;
}

