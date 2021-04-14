#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Exercícios sobre Teblas de Hash que usam chaining para tratamento de colisões
#define SIZE 1000

typedef struct no {
	char matricula[6];
	struct no* next;
} No;

typedef No *HashTableC[SIZE];

int hash (char matricula[6]){
	int k = 0;
	for(int i = 0; i < 6; i++){
		k += matricula[i];
	}
	return (k % SIZE);
}

int insert (HashTableC t, char matricula[6]){
	int i, k;
	i = hash(matricula);
	No *aux = t[i];
	No *ant = NULL;
	while(aux != NULL){
		if(strcmp(aux->matricula,matricula) == 0) return 1;
		else{
			ant = aux;
			aux = aux->next;
		}
	}
	aux = malloc(sizeof(struct no));
	if(aux == NULL) return 1;
	strcpy(aux->matricula,matricula);
	aux->next = NULL;
	if(ant == NULL) t[i] = aux;
	else ant->next = aux;
	return 0;
}

int removeHTC (HashTableC t, char* m){
	int k = hash(m);
	No *aux = t[k];
	puts("debug1");
	No* ant = NULL;
	puts("debug1");
	while(aux != NULL && (strcmp(aux->matricula,m) != 0)){
		ant = aux;
		aux = aux->next;
		puts("debug1");
	}
	puts("debug1");
	if(aux == NULL) return 1; //Insucesso
	else if(strcmp(aux->matricula,m) == 0){
		if(ant == NULL){
			ant = aux->next;
			t[k] = ant;
		} else {
			ant->next = aux->next;
		}
	}
	free(aux);

	return 0;
}

int procura (HashTableC t, char* m){
	int found = 0;
	int k = hash(m);
	No *aux = t[k];
	while(aux != NULL && (found == 0)){
		if(strcmp(aux->matricula,m) == 0) found = 1;
		else aux = aux->next;
	}
	return found;
}

float loadFactorC (HashTableC t){
	int c = 0;
	for(int i = 0; i < SIZE; i++){
		if(t[i] != NULL) c++;
	}
	float res = (float) c / SIZE;
	return res;
}

void printHashTableC(HashTableC t){
	No *aux;
	for(int i = 0; i < SIZE; i++){
		aux = t[i];
		printf("index %d -> ",i);
		while(aux != NULL){
			printf("matricula = %s -> ",aux->matricula);
			aux = aux->next;
		}
		printf("NULL\n");
	}
}

void initHashTableC (HashTableC t){
	for(int i = 0; i < SIZE; i++){
		t[i] = NULL; 
	}
}

void main (){
	char matricula1[6] = "2931TI";
	int k = hash(matricula1);
	printf("k = %d\n",k);

	HashTableC t;
	initHashTableC(t);

	int s = insert(t,matricula1);
	printf("s = %d\n",s);	

	printHashTableC(t);

	float lFc = loadFactorC(t);
	printf("loadFactor = %f\n",lFc);

	/*
	int sR = removeHTC(t,matricula1);
	printHashTableC(t);	
	printf("sR = %d\n",sR);*/

	int f = procura(t,"2931TI");
	if(f == 1) puts("Encontrou");
	else puts("Não encontrou");
}