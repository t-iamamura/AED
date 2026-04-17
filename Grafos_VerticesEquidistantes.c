//--------------------------------------------------------------
// Thales Iamamura
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// INFORME O NRO DO GRUPO CONFORME PLANILHA DIVULGADA
int grupo() {
	return 26;
}

// ESCREVA O NROUSP AQUI
int nroUSP1() {
	return 11915727;
}

// E O SEGUNDO NROUSP AQUI, SE HOUVER
int nroUSP2() {
	return 0;
}

// elemento da lista de resposta - NAO ALTERE ESTA DEFINICAO
typedef struct estr {
	int adj; // um nro. de vertice
	struct estr *prox;
} NO;


// funcoes principais	

void largura (NO* g[], int V, int n, int distancias[]){
	int visitados[V+1];
	int fila[V+1];
	int inicio = 0;
	int fim = 0;
	
	for(int i = 1; i <=V; i++){
		distancias[i] = -1;
		visitados[i] = 0;
	}
	
	// coloca n na fila
	fila[fim++] = n;
	visitados[n] = 1;
	distancias[n] = 0;
	
	// percorre a fila
	while(inicio<fim){
		int atual = fila[inicio++];
		NO* p = g[atual];
		while (p){
			if(visitados[p->adj] != 1){
				fila[fim++] = p->adj;
				visitados[p->adj] = 1;
				distancias[p->adj] = distancias[atual] + 1;
			}
			p = p->prox;
		}
	}
}

NO *equidistantes(int V, int A, int ij[], int v1, int v2)
{
	
	// criacao do grafo
	NO* g[V+1];
	for (int i = 1; i <= V; i++){
		g[i] = NULL;
	}

	// montagem das arestas
	for (int j = 0; j < 2*A; j = j+2){
		int n1 = ij[j];
		int n2 = ij[j+1];

		// coloca n2 em n1
		NO* novo1 = (NO*)malloc(sizeof(NO));
		novo1->adj = n2;
		novo1->prox = g[n1];
		g[n1] = novo1;

		// coloca n1 em n2
		NO* novo2 = (NO*)malloc(sizeof(NO));
		novo2->adj = n1;
		novo2->prox = g[n2];
		g[n2] = novo2;
	}
	int distv1 [V+1];
	int distv2 [V+1];
	largura(g, V, v1, distv1);
	largura(g, V, v2, distv2);
	NO* resp = NULL;
	for (int k = 1; k <= V; k++){
		if(distv1[k] == distv2[k]){
			NO*novo = (NO*)malloc(sizeof(NO));
			novo->adj = k;
			novo->prox = resp;
			resp = novo;
		}
	}
	return resp;
}
