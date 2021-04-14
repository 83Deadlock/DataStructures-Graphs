#include <stdio.h>
#include <stdlib.h>

#define NV 6 	//Numero de vertices
#define NE 0	//Peso da aresta nao existe
#define NEd 10	//Numero de arestas

#define BRANCO 		0	//Não-visitados
#define CINZENTO 	1	//orla
#define PRETO 		2	//Visitados

//Definição da Matriz de Adjacência
typedef int GraphMat [NV][NV];

//Definição da Lista de Adjacência
typedef struct edge {
	int dest;	//destino da aresta
	int cost;	//peso da aresta
	struct edge *next;
} *EList;

typedef EList Graph[NV];

//Definição do Vector de Adjacência
typedef struct edgeV{
	int dest;	//destino da aresta
	int cost; 	//peso da aresta
} EdgeV;

typedef struct vect{
	int vertices [NV+1];
	EdgeV edges [NEd];
} GraphVect;

//Passar de uma Matriz de Adjacência para uma Lista de Adjacência
void matToList(GraphMat gm, Graph g){
	int i, j;
	EList tmp;

	for(i = 0; i < NV; i++){
		g[i] = NULL;

		for(j = NV-1; j >= 0; j--){
			if(gm[i][j] != NE){
				tmp = malloc(sizeof(struct edge));
				tmp->dest = j;
				tmp->cost = gm[i][j];
				tmp->next = g[i];
				g[i] = tmp;
			}
		}
	}
}

//Passar de uma Lista de Adjacência para uma Matriz de Adjacência
void ListToMat(Graph g, GraphMat gm){
	EList aux;
	for(int i = 0; i < NV; i++){
		for(int j = 0; j < NV; j++) gm[i][j] = 0;
		aux = g[i];
		while(aux != NULL){
			gm[i][aux->dest] = aux->cost;
			aux = aux->next;
		}
	}
}

//Passar de uma Lista de Adjacência para um Vector de Adjacência
void listToVect (Graph g, GraphVect *gv){
	int i, k;
	EList aux;

	for(i = k = 0; i < NV; i++){
		gv->vertices[i] = k;
		for(aux = g[i]; aux != NULL; aux = aux->next){
			gv->edges[k].dest = aux->dest;
			gv->edges[k].cost = aux->cost;
			k++;
		}
	}
	gv->vertices[i]=k;
}

//Passar de um Vector de Adjacência para uma Lista de Adjacência
void VectToList (GraphVect *gv, Graph g){
	int i,k;
	EList aux;

	for(i = 0; i < NV; i++){
		g[i] = NULL;
		for(k = gv->vertices[i+1]-1;k >= gv->vertices[i]; k--){
			aux = malloc(sizeof(struct edge));
			aux->dest = gv->edges[k].dest;
			aux->cost = gv->edges[k].cost;
			aux->next = g[i];
			g[i] = aux;
		}
	}
}

//Numero de arestas numa Lista de Adjacência
int nArestasM(GraphMat g){
	int r = 0;
	for(int i = 0; i < NV; i++){
		for(int j = 0; j < NV; j++){
			if(g[i][j]) r++;
		}
	}
	return r;
}

//Numero de arestas numa Lista de Adjacência
int nArestasL(Graph g){
	int r = 0;
	EList aux;
	for(int i = 0; i < NV; i++){
		for(aux = g[i]; aux != NULL; aux = aux->next){
			r++;
		}
	}
	return r;
}

//Peso de uma aresta numa Matriz de adjacência
int edgeWMat (GraphMat g, int o, int d, int *w){
	*w = g[o][d];
	return (*w != NE);
}

//Peso de uma aresta numa Lista de adjacência
int edgeW (Graph g, int o, int d, int *w){
	EList aux;
	int found = 0;
	for(aux = g[o]; (aux != NULL) && !found; aux = aux->next){
		found = (aux->dest == d);
	}
	if(found) *w = aux->cost;
	return found;
}

//Peso de uma aresta num Vector de adjacência
int edgeWVect (GraphVect g, int o, int d, int *w){
	int k;
	int found = 0;
	for(k = g->vertices[o]; (k < g->vertices[o+1]) && !found; k++){
		found = (g->edges[k].dest == d);
	}
	if(found) *w = g->edges[k].cost;
	return found;
}

//Grau de entrada de um vértice numa Matriz de adjacência
int indegreeVMat (GraphMat g, int v){
	int r = 0;
	for(int i = 0; i < NV; i++){
		if(g[i][v] != NE) r++;
	}
	return r;
}

//Grau de saída nde um vértice uma Matriz de adjacência
int outdegreeVMat (GraphMat g, int v){
	int r = 0;
	for(int i = 0; i < NV; i++){
		if(g[v][i] != NE) r++;
	}
	return r;
}

//Maior número de arestas com destino comum
int indegreeMat (GraphMat g){
	int r = 0;
	int curr;
	for(int j = 0; j < NV; j++){
		curr = 0;
		for(int i = 0; i < NV; i++){
			if(g[i][j]) curr++;
		}
		if(curr > r) r = curr;
	}
	return r;
}

//Maior número de arestas com origem comum
int outdegreeMat (GraphMat g){
	int r = 0;
	int curr;
	for(int i = 0; i < NV; i++){
		curr = 0;
		for(int j = 0; j < NV; j++){
			if(g[i][j]) curr++;
		}
		if(curr > r) r = curr;
	}
	return r;
}

//Grau de entrada de um vértice numa Lista de adjacência
int indegreeVL (Graph g, int v){
	int r = 0;
	EList aux;

	for(int i = 0; i < NV; i++){
		for(aux = g[i]; aux != NULL; aux = aux->next){
			if(aux->dest == v) r++;
		}
	}
	return r;
}

//Grau de saída de um vértice numa Lista de adjacência
int outdegreeVL (Graph g, int v){
	int r = 0;
	EList aux;

	for(aux = g[v]; aux != NULL; aux = aux->next) r++;

	return r;
}

//Auxiliar para ver o maior valor de um array
int maxArr (int v[]){
	int max = 0;

	for(int i = 0; i < NV; i++){
		if(v[i] > max) max = v[i];
	}

	return max;
}

//Maior número de arestas com destino comum
int indegreeL (Graph g){
	int destinos[NV];
	for(int i = 0; i < NV; i++) destinos[i] = 0;

	EList aux;
	for(int j = 0; j < NV; j++){
		aux = g[j];
		while(aux != NULL){
			dest[aux->destinos]++;
			aux = aux->next;
		}
	}

	return (maxArr(destinos));
}

//Maior número de arestas com origem comum
int outdegreeL (Graph g){
	int r = 0;
	int curr;
	EList aux;
	for(int i = 0; i < NV; i++){
		curr = 0;
		aux = g[i];
		while(aux != NULL){
			curr++;
			aux = aux->next;
		}
		if(r < curr) r = curr;
	}
	return r;
}

//Grau de entrada de um vértice num Vector de adjacência
int indegreeVVect (GraphVect g, int v){
	int r = 0;
	Elist aux;

	for(int i = 0; i < NEd; i++){
		if(g->edges[i].dest == v) r++;
	}
	return r;
}

//Grau de saída de um vértice num Vector de adjacência
int outdegreeVVect (GraphVect g, int v){
	return (g->vertices[v+1] - g->vertices[v]);
}

//Maior número de arestas com destino comum
int indegreeVect (GraphVect g){
	int destinos[NV];
	for(int i = 0; i < NV; i++) destinos[i] = 0;

	for(int j = 0; j < NEd; j++){
		destinos[g->edges[j].dest]++;
	}

	return (maxArr(destinos));
}

//Maior número de arestas com origem comum
int outdegreeVect (GraphVect g){
	int origens[NV];
	for(int i = 0; i < NV; i++) origens[i] = 0;

	for(int j = 0; j < NV; j++){
		origens[j] = outdegreeVVect(j);
	}

	return (maxArr(origens));
}

//Verifica se existe a aresta (o,d) numa Matriz de Adjacência
int haArestaM (GraphMat g, int o, int d){
	return (g[o][d]);
}

//Verifica se existe a aresta (o,d) numa Lista de Adjacência
int haArestaL (Graph g, int o, int d){
	EList aux = g[o];
	int found = 0;
	while(aux != NULL && !found){
		if(aux->dest == d) found = 1;
		else{
			aux = aux->next;
		}
	}
	return found;
}

//Verifica se existe a aresta (o,d) num Vector de Adjacência
int haArestaV (GraphVect g, int o, int d){
	int inf = g->vertices[o];
	int sup = vertices[o+1] - 1;
	int found = 0;

	for(int i = inf; i <= sup && !found; i++){
		if(g->edges[i].dest == d) found = 1;
	}

	return found;
}

//Verifica se existe um Caminho entre os vertices o e d numa Lista de Adjacência
int haCaminhoAuxL(Graph g, int o, int d, int v[]){
	EList aux;
	v[o] = 1;
	if(o == d) return 1;
	for(aux = g[o]; aux != NULL; aux = aux->next){
		if((v[aux->dest] == 0) && (haCaminhoAuxL(g,aux->destino,d,v))) return 1;
	}
	return 0;
}

int haCaminhoL (Graph g, int o, int d){
	int v[NV];
	for(int i = 0; i < NV; i++) v[i] = 0;
		return (haCaminhoAuxL(g,o,d,v));
}

//Dada uma origem, percorrer todos os vértices alcançáveis e retorna o número de vértices alcançáveis
int travessiaDepthFirstAux(Graph g, int o, int v[]){
	int r = 0;
	EList aux;
	v[o] = 1;

	for(aux = g[o]; aux != NULL; aux = aux->next){
		if(v[aux->dest] == 0){
			r += travessiaDepthFirstAux(g,aux->dest,v);
		}
	}
	return r;
}

int travessiaDepthFirst(Graph g, int o){
	int v[NV];
	for(int i = 0; i < NV; i++) v[i] = 0;
	return(travessiaDepthFirstAux(g,o,v));
}

int travessiaBreadthFirst(Graph g, int o){
	int cor[NV], i, tamOrla = 0, v, r = 0;
	int orla[NV], inicioO, fimO;
	EList aux;

	for(i = 0; i < NV; i++) cor[i] = BRANCO;
	inicioO = fimO = 0;
	cor[o] = CINZENTO;
	orla[fimO++] = o;
	tamOrla++;

	while(inicioO != fimO){
		v = orla[inicioO++];
		cor[v] = PRETO;
		tamOrla--;
		r++;
		for(aux = g[v]; aux != NULL; aux = aux->next){
			if(cor[aux->dest] == BRANCO){
				orla[fimO++] = aux->dest;
				cor[aux->dest] = CINZENTO;
				tamOrla++;
			}
		}
	}
	return r;
}

void printMatrix(GraphMat g){
	puts("\n\n----Matriz de Adjacência----\n\n");
			printf("      [ 0 ][ 1 ][ 2 ][ 3 ][ 4 ][ 5 ]\n");
	for(int i = 0; i < NV; i++){
			printf("[ %d ] ",i);
		for(int j = 0; j < NV; j++){
			printf("[ %d ]",g[i][j]);
		}
		printf("\n");
	}
}

void printList(Graph g){
	puts("\n\n----Lista de Adjacência----\n\n");
		printf("[src] -> [des]\n");
	EList aux;
	for(int i = 0; i < NV; i++){
		printf("[ %d ] -> ",i);
		for(aux = g[i]; aux != NULL; aux = aux->next){
			printf("dest [ %d ] -> ",aux->dest);
		}
		printf("NULL\n");
		printf("         ");
		for(aux = g[i]; aux != NULL; aux = aux->next){
			printf("cost [ %d ] -> ",aux->cost);
		}
		printf("NULL\n");
	}
}

void printVect (GraphVect gv){
	puts("\n\n----Vector de Adjacência----\n\n");
	int i;
	printf("            ");
	for(i = 0; i < NV+1; i++){
		printf("  %d  ",i);
	}

	printf("\nvertices -> ");
	for(i = 0; i < NV+1; i++){
		printf("| %d |",gv.vertices[i]);
	}

	printf("\n\nedges -> ");
	for(i = 0; i < NEd; i++){
		printf("| %d |",gv.edges[i].dest);
	}
	printf("\n         ");
	for(i = 0; i < NEd; i++){
		printf("| %d |",gv.edges[i].cost);
	}
	printf("\n");
}

void main(){
	GraphMat gm = {{NE, 2, 7, NE, NE, NE},
				   {NE, NE, NE, 1, NE, NE},
				   {NE, NE, NE, NE, NE, 1},
				   {5, NE, NE, NE, 8, NE},
				   {3, NE, NE, NE, NE, NE},
				   {4, NE, NE, 3, 2, NE}};

	printMatrix(gm);

	Graph g;

	matToList(gm,g);
	printList(g);

	int n = nArestasL(g);
	printf("\n\nHá %d arestas\n",n);

	GraphVect gv;

	listToVect(g,&gv);
	printVect(gv);

}