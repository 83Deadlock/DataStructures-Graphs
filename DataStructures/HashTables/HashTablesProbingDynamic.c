#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STATUS_FREE 0
#define STATUS_USED 1
#define STATUS_DELETED 2

typedef struct entryO {
	int status;
	char* key;
	void* info;
} EntryOAdd;

typedef struct hashT {
	int size;
	int used;
	EntryOAdd *table;
} *HashTableOAddr;

int hash (int s, char* k){
	int r = 0;
	for(int i = 0; k[i] != '\0'; i++){
		r += k[i];
	}
	return (r%s);
}

void initHashTableOAddr(HashTableOAddr h){
	struct hashT new;
	new.size = 10;
	new.table = malloc(new.size * (sizeof(EntryOAdd)));
	for(int i = 0; i < new.size; i++){
		new.table[i].status = 0;
		new.table[i].key = malloc(sizeof(char) * 30);
		strcpy(new.table[i].key,"");
	}
	h->size = new.size;
	h->used = 0;
	h->table = new.table;
}

void insert(HashTableOAddr h, void* info, char* key){

	int i = hash(h->size,key);
	int tam = 0;
	int r = 0;
	int a = 1;

	while(tam != h->size && a){
		if((h->table[i].status == STATUS_FREE || h->table[i].status == STATUS_DELETED) && r == 0){
			r = i;
		}
		if(h->table[i].status == STATUS_USED){
			if(strcmp(h->table[i].key,key) == 0) {
				a = 0;
				r = i;
			}
		}
		i++;
		tam++;
		if(i >= h->size) i = 0;
	}
	if(a != 0){
		h->table[r].key = malloc(sizeof(char) * strlen(key));
		strcpy(h->table[r].key,key);
		h->table[r].status = STATUS_USED;
		h->table[r].info = info;
		h->used++;
	} else if (a == 0){
		h->table[r].key = malloc(sizeof(char) * strlen(key));
		strcpy(h->table[r].key,key);
		h->table[r].status = STATUS_USED;
		h->table[r].info = info;
	}
}

float loadFactor (HashTableOAddr h){
	float r = (float) h->used/h->size;
	return r;
}

void doubleTable(HashTableOAddr h){
	struct hashT new;
	new.size = h->size * 2;
	new.used = h->used;
	new.table = malloc(new.size * (sizeof(EntryOAdd)));
	int u = h->used;

	int i;
	for(i = 0; i < new.size; i++) new.table[i].status = 0;
	for(i = 0; i < h->size; i++){
		if(h->table[i].status == 1) insert(&new,h->table[i].info, h->table[i].key);
	}
	free(h->table);
	h->size *= 2;
	h->used = u;
	h->table = new.table;
}

void removeHT(HashTableOAddr h, char* key){
	int i = hash(h->size,key);
	int tam = 0;
	int r = 0;
	int a = 1;

	while(tam != h->size && a){
		if(h->table[i].status == STATUS_FREE || h->table[i].status == STATUS_DELETED);
		else if(h->table[i].status == STATUS_USED){
			if(strcmp(key,h->table[i].key) == 0) {
				a = 0;
				r = i;
			}
		}
		i++;
		tam++;
		if(i >= h->size) i = 0;
	}
	if(a == 0){
		h->table[r].status = STATUS_DELETED;
	}
	else{
		puts("A key não existe");
	}
}

void printHashTableOAddr(HashTableOAddr h){
	printf("\n\nsize = %d ||| used = %d\n\n",h->size,h->used);
	for(int i = 0; i < h->size; i++){
		printf("index %d -> ",i);
		printf("key = %s | info = %p | status = ",h->table[i].key,(h->table[i].info));
		if(h->table[i].status == STATUS_USED) printf("USED\n");
		else if(h->table[i].status == STATUS_FREE) printf("FREE\n");
		else if(h->table[i].status == STATUS_DELETED) printf("DELETED\n");
	}
}

void remApagados(HashTableOAddr h){
	int del = 0;
	for(int i = 0; i < h->size; i++){
		if(h->table[i].status == STATUS_DELETED){
			del++;
			h->table[i].status = STATUS_FREE;
		}
	}
	h->used = (h->used - del);
}

int procura(HashTableOAddr h, char* key){
	int found = 0;
	for(int i = 0;i < h->size && found == 0; i++){
		if(h->table[i].key != NULL){
			if((strcmp(h->table[i].key,key) == 0) && (h->table[i].status == STATUS_USED)) found = 1;
		}
	}
	return found;
}

void add(HashTableOAddr h, void* info, char* key){
	if((loadFactor(h)*100) > 75.00){
		doubleTable(h);
	}
	insert(h,info,key);
}

void main(){
	HashTableOAddr h;
	initHashTableOAddr(h);

	int a = 1;
	add(h,&a,"um");

	printHashTableOAddr(h);

	int b = 2;
	add(h,&b,"dois");
	printHashTableOAddr(h);

	float lf = loadFactor(h);
	printf("LoadFactor = %.2f \n",(lf*100));

	int c = 3;
	add(h,&c,"tres");

	int d = 4;
	add(h,&d,"quatro");

	int e = 5;
	add(h,&e,"cinco");

	int f = 6;
	add(h,&f,"seis");

	int g = 7;
	add(h,&g,"sete");

	int i = 8;
	add(h,&i,"oito");
	printHashTableOAddr(h);
	lf = loadFactor(h);
	printf("LoadFactor = %.2f \n",(lf*100));

	int j = 9;
	add(h,&j,"nove");
	add(h,&g,"oito"); //valor em key = oito e key = sete tem de ser igual (mesmo apontador)
	printHashTableOAddr(h);
	lf = loadFactor(h);
	printf("LoadFactor = %.2f \n",(lf*100));

	puts("remove oito");
	removeHT(h,"oito");
	printHashTableOAddr(h);
	lf = loadFactor(h);
	printf("LoadFactor = %.2f \n",(lf*100));

	puts("remApagados");
	remApagados(h);
	printHashTableOAddr(h);
	lf = loadFactor(h);
	printf("LoadFactor = %.2f \n",(lf*100));

	puts("procura um");
	int t = procura(h,"um");
	if(t == 1) puts("encontrou");
	else puts("não encontrou");

	puts("procura vinte");
	t = procura(h,"vinte");
	if(t == 1) puts("encontrou");
	else puts("não encontrou");
}