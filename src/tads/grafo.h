#ifndef TADS_GRAFO_H_
#define TADS_GRAFO_H_
#define INFINITO -1

typedef struct{
	void* vertice;
}DicionarioItem;

typedef struct{
	DicionarioItem* items;
	int total;
	int capacidade;
}DicionarioVertices;

typedef struct{
	DicionarioVertices* dicionario;
	int** mapa;
	int qtdVertices;
	int qtdArestas;
}Grafo;


Grafo* criaGrafo();
void insereCaminho(Grafo* grafo, void* origem, void* destino, int peso);

// obrigatória implementação externa
// import da implementação externa deve vir antes da presente classe
int getIndice(DicionarioVertices* dicionario, void* vertice);
int isMapped(DicionarioVertices* dicionario, void* vertice);

#endif /* TADS_GRAFO_H_ */
