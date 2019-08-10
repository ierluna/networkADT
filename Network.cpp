#include "Common.h"
#include "Stack.h"
#include "Map.h"
#include "Network.h"

struct NetworkRepr {
    Map flechas;
    Stack acciones;
};

Network emptyN() {
    Network n = new NetworkRepr;
    n->flechas = emptyM();
    n->acciones = emptyS();
    return n;
}


void addN(Network net, Id id) {
    insertM(net->flechas,id,id);
    pushS(net->acciones,id);
}

bool elemN(Network net, Id id) {
    Id tmp;
    return lookupM(net->flechas, id, tmp);

}

void connectN(Network net, Id id1, Id id2) {
    Id i1 = id1;
    Id i2 = NULL;

    lookupM(net->flechas, i1, i2);
    while(i1!= i2){
        i1 = i2;
        lookupM(net->flechas, i1, i2);
    }
    Id y1 = id2;
    Id y2 = NULL;

    lookupM(net->flechas, y1, y2);
    while(y1 != y2){
        y1 = y2;
        lookupM(net->flechas, y1, y2);
    }
    if (i2 != y2){
        insertM(net->flechas, i2, y2);
    }
    pushS(net->acciones, i2);
}



bool connectedN(Network net, Id id1, Id id2) {
    Id i1 = id1;
    Id i2;

    lookupM(net->flechas, i1, i2);
    while(i1 != i2){
        i1 = i2;
        lookupM(net->flechas, i1, i2);
    }
    Id i3 = id2;
    Id i4;

    lookupM(net->flechas, i3, i4);
    while(i3!= i4){
        i3 = i4;
        lookupM(net->flechas, i3, i4);
    }

    return (i2 == i4);
}

void undoN(Network net) {
    Id ultimaAccion = topS(net->acciones);
    Id v;

    popS(net->acciones);
    lookupM(net->flechas, ultimaAccion, v);
    if (ultimaAccion != v){
        insertM(net->flechas, ultimaAccion, ultimaAccion);
    } else {
        removeM(net->flechas, ultimaAccion);
    }
}


void destroyN(Network net) {
    destroyM(net->flechas);
    destroyS(net->acciones);
    delete net;
}
