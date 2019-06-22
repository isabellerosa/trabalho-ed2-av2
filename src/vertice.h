#ifndef VERTICE_H_
#define VERTICE_H_

#include "tads/grafo.h"

typedef struct{
	char id;
}Vertice;

int getIndice(DicionarioVertices* dicionario, void* v){
	int i;

	Vertice* vertice = (Vertice*) v;

	for(i=0; i<dicionario->total; i++){
		if(((Vertice*) dicionario->items[i].vertice)->id == vertice->id)
			return i;
	}

	return -1;
}


int isMapped(DicionarioVertices* dicionario, void* vertice){
	if (getIndice(dicionario, vertice) > -1)
		return 1;

	return 0;
}


#endif /* VERTICE_H_ */
