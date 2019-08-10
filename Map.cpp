#include "Common.h"
#include "Map.h"

typedef int Priority;

Priority randomPriority() {
    return rand();
}

struct Node {
    Key clave;
    Value valor;
    Priority prioridad;
    Node* hijoIzq;
    Node* hijoDer;
};

struct MapRepr {
    Node* raiz;
    int tam;
};

Map emptyM() {
    MapRepr* m = new MapRepr;
    m->tam = 0;
    m->raiz = NULL;
    return m;
}

int sizeM(Map m) {
    return m->tam;
}

bool lookupM(Map m, Key k, Value& v) {
    Node* p = m->raiz;
    while(p!= NULL && p->clave != k){
        if(k<p->clave){
            p=p->hijoIzq;
        }else {
            p=p->hijoDer;
        }
    }
    if (p!=NULL){
            v = p->valor;
        }
    return p!=NULL;
}





void intercambiarValores(Node* a, Node* b){
    Node* tmp = new Node;                   //****** crea nuevo nodo para recordar valores del nodo a
    tmp-> valor=a->valor;
    tmp-> clave=a->clave;
    tmp-> prioridad=a->prioridad;

    a->valor=b->valor;                      //****** le asigna los valores del nodo b al nodo a
    a->clave=b->clave;
    a->prioridad=b->prioridad;

    b->valor=tmp->valor;                    //****** le asigna los valores del nodo a al nodo b
    b->clave=tmp->clave;
    b->prioridad=tmp->prioridad;

    delete tmp;                             //***** borra el nodo que se usó para recordar los valores
}

void rotarIzqSi(Node* padre){
    if ((padre->prioridad) < (padre->hijoIzq->prioridad)){
        Node* hijo=padre->hijoIzq;
        Node* x= hijo -> hijoIzq;
        Node* y= hijo -> hijoDer;
        Node* z= padre->hijoDer;

        intercambiarValores(padre, hijo);

        padre->hijoIzq = x;
        padre->hijoDer =hijo;
        hijo-> hijoIzq=y;
        hijo-> hijoDer=z;
    }
}

void rotarDerSi(Node* padre){
    if((padre->prioridad) < (padre->hijoDer->prioridad)){
        Node* hijo= padre->hijoDer;
        Node* x= padre->hijoIzq;
        Node* y= hijo->hijoIzq;
        Node* z= hijo->hijoDer;

        intercambiarValores(padre,hijo);

        padre->hijoIzq=hijo;
        padre->hijoDer=z;
        hijo->hijoIzq=x;
        hijo->hijoDer=y;
    }
}

Node* insertN(Node* n, Key k, Value v, int& a){
    if(n == NULL){
        Node* n2= new Node;
        n2->valor=v;
        n2->clave=k;
        n2->prioridad=randomPriority();
        n2->hijoIzq=NULL;
        n2->hijoDer=NULL;
        a=1;
        return n2;
    }else if (n->clave==k){
        n->valor=v;
        a=0;
        return n;
    }else if (n->clave > k){
        n->hijoIzq=insertN(n->hijoIzq,k,v,a);
        rotarIzqSi(n);                              //balanceo si rompe el invariante de treap(prioridad)
        return n;
    }else {
        n->hijoDer=insertN(n->hijoDer, k,v,a);
        rotarDerSi(n);                              //balanceo si rompe el invariante de treap(prioridad)
        return n;
    }
}

void insertM(Map m, Key k, Value v) {
    int tamN;
    m->raiz=insertN(m->raiz,k,v,tamN);
    m->tam=m->tam+tamN;                 //Suma 1 si el elemento a insertar no estaba en el treap
}

Node* borrarMin(Node* n,Key &k,Value &v){
    //PRECONDICIÓN: n!NULL
    if (n->hijoIzq==NULL){
        Node*tmp =n->hijoDer;
        k=n->clave;
        v=n->valor;
        delete n;
        return tmp;
    }else{
        n->hijoIzq=borrarMin(n->hijoIzq,k,v);
        return n;
    }
}


Node* borrarRaiz(Node* n){
    //PRECONDICIÓN: (n!NULL)
    if((n->hijoDer)==NULL){                    //************Caso 1: No existe hijo derecho
        Node* tmp= n->hijoIzq;
        delete n;
        return tmp;
    }else {
        Key k;
        Value v;
        n->hijoDer=borrarMin(n->hijoDer,k,v); // elemento "min" es devuelto por referencia
        n->clave=k;
        n->valor=v;
        return n;
    }

}

Node* borrarNodo(Node* n, int x, int& a){

    if (n==NULL){                               //***** caso base: no existe el elemento
        a=0;
        return n;
    }else if (x > n->clave){
        n->hijoDer=borrarNodo(n->hijoDer,x,a);  //***** Recursión sobre hijo derecho
        return n;
    }else if (x < n->clave){                    //***** Recursión sobre hijo izquierdo
        n->hijoIzq=borrarNodo(n->hijoIzq,x,a);
        return n;
    }else
        n=borrarRaiz(n);
        a=1;
        return n;
    }
}





void removeM(Map m, Key k) {
    int a;
    m->raiz=borrarNodo(m->raiz,k,a);
    m->tam=m->tam-a;
}


void deleteNodo(Node* n){
    if(n==NULL){
        return;
    }
    deleteNodo(n->hijoIzq);
    deleteNodo(n->hijoDer);
    delete n; //free (n)
}

void destroyM(Map m) {
    deleteNodo(m->raiz);
    delete m;
}



