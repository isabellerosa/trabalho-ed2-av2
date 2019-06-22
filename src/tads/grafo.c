#include <stdlib.h>
#include "grafo.h"
#define DICIONARIO_CONST 100

int** criaMapa(int qtdVertices) {
	int i, j;
	int **m = (int**) malloc(qtdVertices * sizeof(int*));

	for (i = 0; i < qtdVertices; i++) {
		m[i] = (int*) malloc(qtdVertices * sizeof(int));
		for (j = 0; j < qtdVertices; j++) {
			m[i][j] = INFINITO;
		}
	}
	return m;
}

void aumentaCapacidadeMapa(Grafo* grafo) {
	int i, j;
	int capacidade = grafo->dicionario->capacidade;
	int capacidadeNova = capacidade + DICIONARIO_CONST;
	grafo->mapa = (int**) realloc(grafo->mapa, capacidadeNova * sizeof(int*));

	for (i = 0; i < capacidadeNova; i++) {
		grafo->mapa[i] = (int*) realloc(grafo->mapa[i], capacidadeNova * sizeof(int));
		for (j = 0; j < capacidadeNova; j++) {
			if (i >= capacidade || j >= capacidade)
				grafo->mapa[i][j] = INFINITO;
		}
	}

}

DicionarioVertices* criaDicionario() {
	DicionarioVertices* dicionario = (DicionarioVertices*) malloc(
			sizeof(DicionarioVertices));
	dicionario->items = (DicionarioItem*) malloc(
			sizeof(DicionarioItem) * DICIONARIO_CONST);
	dicionario->capacidade = DICIONARIO_CONST;
	dicionario->total = 0;

	return dicionario;
}

Grafo* criaGrafo() {
	Grafo* grafo = (Grafo*) malloc(sizeof(Grafo));
	grafo->qtdVertices = 0;
	grafo->qtdArestas = 0;
	grafo->mapa = criaMapa(DICIONARIO_CONST);
	grafo->dicionario = criaDicionario();

	return grafo;
}

void map(DicionarioVertices* dicionario, void* vertice) {
	//se dicionario estiver cheio, aumenta sua capacidade segundo constante
	if (dicionario->total == dicionario->capacidade) {
		dicionario->items = (DicionarioItem*) realloc(dicionario->items,
				sizeof(DicionarioItem*)
						* (dicionario->capacidade + DICIONARIO_CONST));
		dicionario->capacidade += DICIONARIO_CONST;
	}
	//insere vertice no dicionario
	dicionario->items[dicionario->total].vertice = vertice;
	dicionario->total++;
}

int insertPath(Grafo* graph, int origin, int destination, int w8) {
	if (origin > graph->dicionario->capacidade)
		return -1;

	if (destination > graph->dicionario->capacidade)
		return 1;

	graph->mapa[origin][destination] = w8;
	graph->qtdArestas++;
	return 0;
}

void insereCaminho(Grafo* grafo, void* origem, void* destino, int peso) {
	int verticesNovos = 0;
	// mapeia origem e destino caso n�o estejam mapeados
	if (!isMapped(grafo->dicionario, origem)) {
		map(grafo->dicionario, origem);
		verticesNovos++;
	}

	if (!isMapped(grafo->dicionario, destino)) {
		map(grafo->dicionario, destino);
		verticesNovos++;
	}

	// pega seus indices
	int iOrigem = getIndice(grafo->dicionario, origem);
	int iDestino = getIndice(grafo->dicionario, destino);

	// insere caminho no grafo
	insertPath(grafo, iOrigem, iDestino, peso);
	grafo->qtdVertices += verticesNovos;

	// mapa precisar de mais linhas e colunas, crie
	if (grafo->qtdVertices+2 > grafo->dicionario->capacidade) {
		aumentaCapacidadeMapa(grafo);
	}
}

