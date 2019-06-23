/**
 * Escreva um programa em C que leia um grafo G (a partir de um arquivo
 * texto) e um vértice inicial v e encontre o caminho mínimo desde v até todos os
 * outros vértices de G.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file/read.h"
#include "vertice.h"
#include "tads/grafo.h"
#define FALSE 0
#define TRUE 1

Vertice* getVertice(DicionarioVertices* dicionario, int indice) {
	if (isMapped(dicionario, dicionario->items[indice].vertice))
		return (Vertice*) dicionario->items[indice].vertice;
	return NULL;
}


int menorDistancia(Grafo* grafo, int* distancia, int* visitado) {
	int i, menorDistancia = INFINITO;
	int vertice = -1;

	for (i = 0; i < grafo->qtdVertices; i++) {
		if (visitado[i] == FALSE && menorDistancia <= INFINITO) {
			menorDistancia = distancia[i];
			vertice = i;
			continue;
		}

		if (visitado[i] == FALSE && distancia[i] >= 0
				&& distancia[i] < menorDistancia) {
			menorDistancia = distancia[i];
			vertice = i;
		}
	}
	return vertice;
}


int* dijkstra(Grafo* grafo, Vertice* inicio) {
	int* distancia = (int*) malloc(sizeof(int) * grafo->qtdVertices);
	int* isVisitado = (int*) malloc(sizeof(int) * grafo->qtdVertices);

	// inicializa array com informacao dos vertices visitados e das distancias
	int i, j;
	for (i = 0; i < grafo->qtdVertices; i++) {
		distancia[i] = INFINITO;
		isVisitado[i] = FALSE;
	}

	distancia[getIndice(grafo->dicionario, inicio)] = 0;

	for (i = 0; i < grafo->qtdVertices; i++) {
		int indiceMaisProx = menorDistancia(grafo, distancia, isVisitado);

		isVisitado[indiceMaisProx] = TRUE;

		for (j = 0; j < grafo->qtdVertices; j++) {

			if (!isVisitado[j] && grafo->mapa[indiceMaisProx][j] != INFINITO) {

				distancia[j] = distancia[indiceMaisProx]
						+ grafo->mapa[indiceMaisProx][j];
			}
		}
	}

	return distancia;
}


void populaGrafo(Grafo* grafo, char* arquivo) {

	int i, lines = lineCount(arquivo);
	for (i = 1; i <= lines; i++) {
		char* linha = readLine(arquivo, i);

		Vertice* origem = (Vertice*) malloc(sizeof(Vertice));
		origem->id = strtok(linha, " ")[0];

		Vertice* destino = (Vertice*) malloc(sizeof(Vertice));
		destino->id = strtok(NULL, " ")[0];

		int peso = strtol(strtok(NULL, " "), NULL, 10);

		insereCaminho(grafo, origem, destino, peso);
	}

}


void printMapa(Grafo* grafo) {
	int i, j;

	printf("   |");

	for (i = 0; i < grafo->dicionario->total; i++) {
		printf("%c   ", ((Vertice*) grafo->dicionario->items[i].vertice)->id);
	}

	printf("\n");

	for (i = 0; i < grafo->qtdVertices; i++) {
		printf("%c  |", ((Vertice*) grafo->dicionario->items[i].vertice)->id);

		for (j = 0; j < grafo->qtdVertices; j++) {
			if (grafo->mapa[i][j] == INFINITO)
				printf("-   ");
			else
				printf("%i   ", grafo->mapa[i][j]);
		}
		printf("\n");
	}
}


int main() {
	Grafo* grafo = criaGrafo();
	populaGrafo(grafo, "./src/resources/exemplo3.txt");
	printMapa(grafo);

	printf("\n");

	int* solucao = dijkstra(grafo, getVertice(grafo->dicionario, 0));
	int i;
	for (i = 0; i < grafo->qtdVertices; i++) {
		printf("%i - %c | ", solucao[i], getVertice(grafo->dicionario, i)->id);
	}

	return EXIT_SUCCESS;
}
