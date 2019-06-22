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

void populaGrafo(Grafo* grafo, char* arquivo) {

	int i, lines = lineCount(arquivo);
	for (i = 1; i <= lines; i++) {
		char* linha = readLine(arquivo, i);

		if (linha == NULL)
			exit(1);

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
			if (grafo->mapa[i][j] == -1)
				printf("-   ");
			else
				printf("%i   ", grafo->mapa[i][j]);
		}
		printf("\n");
	}
}


int main() {
	Grafo* grafo = criaGrafo();
	populaGrafo(grafo, "./src/resources/exemplo2.txt");
	printMapa(grafo);

	return EXIT_SUCCESS;
}
