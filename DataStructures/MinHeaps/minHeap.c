#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define maxH 100

//Definição da estrutura de uma minHeap na Pergunta 9
typedef struct mHeap {
	int tamanho;
	int heap [maxH];
} *MinHeap;

//Definição da estrutura de uma árvore binária na Pergunta 5
typedef struct nodo {
	int val;
	struct nodo *esq, *dir;
} Nodo, *Tree;

//Definição de uma minHeap dinâmica de inteiros
typedef struct minHeapD {
	int size;
	int used;
	int *values;
} *MinHeapD;

void swapH (int h[], int a, int b){
	int t = h[a];
	h[a] = h[b];
	h[b] = t;
}

void bubbleUp (int h[], int N){
	int i = N;
	while((h[i] < h[(i-1)/2]) && i > 0){
		swapH(h,i,(i-1)/2);
		i = (i-1)/2;
	}
}

void bubbleDown (int h[], int N){
	int i = 0, f;
	while(2 * i + 2 < N){
		if(h[(2*i)+2] < h[(2*i)+1]){
			f = (2*i) + 2;
		} else {
			f = (2*i) + 1;
		}
		if(h[f] >= h[i]) break;
		swapH(h,i,f);
		i = f;
	}
	if((2*i)+1 < N && h[(2*i)] < h[i]) swapH(h,i,(2*i)+1);
}

int addH (MinHeap m, int x){
	int r = 0;
	if(m -> tamanho == maxH) r = 1;
	else {
		m->heap[m->tamanho] = x;
		bubbleUp(m->heap,m->tamanho);
		m->tamanho++;
	}
	return r;
}

int removeH (MinHeap m, int *x){
	int r = 0;
	if(m->tamanho == 0) r = 1;
	else {
		*x = m->heap[0];
		m->tamanho--;
		if(m->tamanho == 0);
		else{
			m->heap[0] = m->heap[m->tamanho];
			bubbleDown(m->heap,m->tamanho);
		}
	}
	return r;
}

void printHeap (MinHeap m){
	printf("[");
	for(int i = 0; i < m->tamanho; i++){
		printf("%d",m->heap[i]);
		if(i+1 == m->tamanho);
		else printf(", ");
	}
	printf("]\n");
}

void printTreeAux(Tree root, int space){ 
    // Base case 
    if (root == NULL) 
        return; 
  
    // Increase distance between levels 
    space += 3; 
  
    // Process right child first 
    printTreeAux(root->dir, space); 
  
    // Print current node after space 
    // count 
    printf("\n"); 
    for (int i = 3; i < space; i++) 
        printf(" "); 
    printf("%d\n", root->val); 
  
    // Process left child 
    printTreeAux(root->esq, space); 
} 

void printTree(Tree t){
	printTreeAux(t,0);
}

//5.- Converte uma minHeap representada em array numa minHeap representada numa árvore binária
Tree heapToTree(MinHeap m, int inicio){
	if(inicio >= m->tamanho) return NULL;
	Tree t = malloc(sizeof(struct nodo));
	if(t == NULL) return NULL;
	t->val = m->heap[inicio];
	t->esq = heapToTree(m,(2*inicio)+1);
	t->dir = heapToTree(m,(2*inicio)+2);
	return t;
}

//Função auxiliar que descobre a posição do valor x que foi adicionado à heap h
int newPos(int h[], int N, int x){
	int i = 0;
	for(; i < N; i++){
		if(h[i] == x) break;
	}
	return i;
}

//9.- Altera a posição pos da minHeap m para o valor 'valor'
//fazendo as devidas alterações para preservar as propriedades de uma MinHeap
int muda (MinHeap m, int pos, int valor){
	int r = 0;
	if((m->tamanho <= pos) || (pos < 0)) r = 1;
	else{ 
		m->heap[pos] = valor;
		bubbleUp(m->heap,pos);
		int i = newPos(m->heap, pos, valor);
		bubbleDown(m->heap+i,m->tamanho-pos+1);
	}
	return r;
}

//12.- Função que calcula o maior elemento da heap sem a percorrer necessariamente toda
int maxHeap (MinHeap m, int *max){
	if(m->tamanho <= 0) return 1; //Se a heap estiver vazia, não existe um elemento maior

	int j = m->tamanho - 1; //Vamos começar pelo último elemento da heap (garantidamente no último nível)
	*max = m->heap[j]; //O seu valor vai ser assumido como o maior

	double n = (log(m->tamanho)); //Esta cena é feita para saber quanto é log2(#elems_da_heap)
	double d = (log(2));		  //Isto é feito para sabermos qual o nível em que se encontra o último elemento
								  //Apenas nos interessam os elementos que estão nesse nível (último)
	int l = (n/d)/1;			  //O C não tem uma função log2, então faz-se log(x)/log(2) para saber log2(x)
								  //A divisão por 1 é apenas para passar o número para um int, arredondando sempre para baixo
	j--;				//Vamos olhar para o penúltimo elemento
	n = (log(j+1));		
	d = (log(2));
	int la = (n/d)/1;	//Calcular o seu nível

	while((j >= 0) && (la == l)){ //Se o elemento existir na heap (j>=0) e o seu nível for o último (la == l)
		if(m->heap[j] > *max) *max = m->heap[j];
			//Se o elemento for maior que o max anterior, assumir que max = valor deste elemento
		j--; //Elemento anterior
		n = (log(j+1));
		d = (log(2));
		int la = (n/d)/1; //Calcular o nível do novo elemento
	}

	return 0;
}

//26.-a) Função que verifica se o cmainho da raiz até todas as folhas de uma heap é crescente
int minHeapOK (MinHeap m){
	int i = (m->tamanho) -1;
	int r = 0;
	while(i > 0 && r == 0){
		if(m->heap[(i-1)/2] > m->heap[i]) {
			r = 1;
			printf("pai -> %d\n",m->heap[(i-1)/2]);
			printf("filho -> %d\n",m->heap[i]);
		}
		else i--;
	}
	return r;
}



MinHeapD initMinHeapD (){
	MinHeapD h = malloc(sizeof(struct minHeapD));
	h->size = 1;
	h->used = 0;
	h->values = malloc(sizeof(int)*h->size);
	return h;
}

//BubbleUpH é a BubbleUp para MinHeaps Dinâmicas
void bubbleUpD (MinHeapD h, int N){
	int i = N;
	while((h->values[i] < h->values[(i-1)/2]) && i > 0){
		swapH(h->values,i,(i-1)/2);
		i = (i-1)/2;
	}
}

//BubbleDownH é a BubbleDown para MinHeaps Dinâmicas
void bubbleDownD (MinHeapD h, int N){
	int i = 0, f;
	while(2 * i + 2 < N){
		if(h->values[(2*i)+2] < h->values[(2*i)+1]){
			f = (2*i) + 2;
		} else {
			f = (2*i) + 1;
		}
		if(h->values[f] >= h->values[i]) break;
		swapH(h->values,i,f);
		i = f;
	}
	if((2*i)+1 < N && h->values[(2*i)] < h->values[i]) swapH(h->values,i,(2*i)+1);
}

int addD (MinHeapD h, int x){
	int r = 0;

	if(h->used == h->size){
		h->size *= 2;
		h->values = realloc(h->values,sizeof(int)*h->size);
		if(h->values == NULL) r = 1;
	}
	
	h->values[h->used] = x;
	bubbleUpD(h,h->used);
	h->used++;
	
	return r;
}

int removeD (MinHeapD h, int *x){
	int r = 0;
	if(h->used == 0) r = 1;
	else {
		*x = h->values[0];
		h->used--;
		if(h->used == 0){
			h->size = 1;
			h->values =  realloc(h->values,sizeof(int)*h->size);
			if(h->values == NULL) r = 1;
		}
		else{
			if(h->used < (double) (h->size/2)/1){
				h->size /= 2;
				h->values = realloc(h->values,sizeof(int)*h->size);
				if(h->values == NULL) r = 1;
			}
			h->values[0] = h->values[h->used];
			bubbleDownD(h,h->used);
		}
	}
	return r;
}

void printHeapD (MinHeapD h){
	printf("[");
	for(int i = 0; i < h->used; i++){
		printf("%d",h->values[i]);
		if(i+1 == h->used);
		else printf(", ");
	}
	printf("]\n");
}

//19.- Calcula um array ordenado com so elementos da min-heap
// tem que alocar espaço para o array resultado e destruir o conteúdo da min-heap
int* ordenados(MinHeapD h){
	
	int *novo = malloc(sizeof(int)*h->used);
	int i = 0;
	while(h->used != 0){
		removeD(h,&novo[i++]);
	}
	return novo;
}

//23.- HeapToTree
Tree hToTAux (MinHeapD h, int r){
	Tree new;
	if (r >= h->used) return NULL;
	new = malloc (sizeof (struct nodo));
	new->val = h->values[r];
	new->esq = hToTAux (h, 2*r+1);
	new->dir = hToTAux (h, 2*r+2);
	return new;
}

Tree heapDToTree (MinHeapD h) {
	return hToTAux(h,0);
}

//Esta main implementa alguns testes
void main (){
	int r,x;
	Tree t;
	MinHeap m = malloc(sizeof(struct mHeap)); //MinHeaps com array estático
	/*                             Testes do add*/
	r = addH(m,1);
	if(r == 1) puts("falhou!");
	
	r = addH(m,2);
	if(r == 1) puts("falhou!");

	r = addH(m,3);
	if(r == 1) puts("falhou!");

	r = addH(m,4);
	if(r == 1) puts("falhou!");

	r = addH(m,5);
	if(r == 1) puts("falhou!");

	r = addH(m,6);
	if(r == 1) puts("falhou!");

	r = addH(m,7);
	if(r == 1) puts("falhou!");
	
	printHeap(m);

	/**/

	/*								Teste do remove
	removeH(m,&x);
	printf("valor removido = %d\n",x);
	
	printHeap(m);
	*/	

	/*								Teste do muda
	r = muda(m,1,8);
	if(r == 1) puts("falhou!");	

	printHeap(m);
	*/

	/*								Teste do maxHeap
	int max;
	r = maxHeap(m,&max);
	if(r == 1) puts("falhou!");

	printHeap(m);	
	printf("Max = %d\n",max);
	*/

	/*								Teste do heapToTree
	t = heapToTree(m,0);
	printTree(t);
	*/

	/*								Teste do minHeapOK*/
	r = minHeapOK(m);
	if(r == 1) puts("not ok!");
	/**/

	MinHeapD heapD = initMinHeapD();

	/*                             Testes do add
	r = addD(heapD,1);
	if(r == 1) puts("falhou!");
	
	r = addD(heapD,2);
	if(r == 1) puts("falhou!");

	r = addD(heapD,3);
	if(r == 1) puts("falhou!");

	r = addD(heapD,4);
	if(r == 1) puts("falhou!");

	r = addD(heapD,5);
	if(r == 1) puts("falhou!");

	r = addD(heapD,6);
	if(r == 1) puts("falhou!");

	r = addD(heapD,7);
	if(r == 1) puts("falhou!");
	
	printHeapD(heapD);

	*/	

	/*								Teste do remove
	printf("tamanho inicial = %d\n\n",heapD->size);
	printf("Usados inicial = %d\n\n",heapD->used);

	removeD(heapD,&x);
	printf("valor removido = %d\n",x);
	printHeapD(heapD);

	removeD(heapD,&x);
	printf("valor removido = %d\n",x);
	printHeapD(heapD);

	removeD(heapD,&x);
	printf("valor removido = %d\n",x);
	printHeapD(heapD);

	removeD(heapD,&x);
	printf("valor removido = %d\n",x);
	printHeapD(heapD);

	removeD(heapD,&x);
	printf("valor removido = %d\n",x);
	printHeapD(heapD);

	removeD(heapD,&x);
	printf("valor removido = %d\n",x);
	printHeapD(heapD);

	removeD(heapD,&x);
	printf("valor removido = %d\n",x);
	printHeapD(heapD);

	printf("tamanho final = %d\n\n",heapD->size);
	printf("Usados final = %d\n\n",heapD->used);
	*/

	/*								Teste do ordenados
	removeD(heapD,&x);
	printf("valor removido = %d\n",x);
	printHeapD(heapD);

	int size = heapD->used;
	int *order = ordenados(heapD);
	printf("[");
	for(int i = 0; i < size; i++){
		printf("%d",order[i]);
		if(i+1 != size) printf(", ");
	}
	printf("]\n");
	*/

	/*								Teste pergunta 23
	int *valores = malloc(sizeof(int) * 100);
	valores[0] = 4;
	valores[1] = 10;
	valores[2] = 21;
	valores[3] = 45;
	valores[4] = 13;
	valores[5] = 25;
	valores[6] = 22;
	valores[7] = 60;
	valores[8] = 100;
	valores[9] = 20;

	int s = 100;
	int u = 10;
	heapD->size = s;
	heapD->used = u;
	heapD->values = valores;

	removeD(heapD,&x);
	printf("valor removido = %d\n",x);

	printHeapD(heapD);

	removeD(heapD,&x);
	printf("valor removido = %d\n",x);

	printHeapD(heapD);

	*/

	/*							Teste heapDToTree
	t = heapDToTree(heapD);
	printTree(t);
	*/
}