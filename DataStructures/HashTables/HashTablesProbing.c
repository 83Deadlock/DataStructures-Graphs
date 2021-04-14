#include <stdio.h>
#include <stdlib.h>

#define SIZE 7
#define STATUS_FREE 0
#define STATUS_USED 1
#define STATUS_DELETED 2

typedef struct bucket {
	int status;
	int key, info;
} Bucket;

typedef Bucket HashTableP[SIZE];


void initTab(HashTableP h){
	int i ;
	for(i =0; i<SIZE; i++){
		 h[i].status=STATUS_FREE;
		 h[i].key = 0;					//Assuming 0 will never be the key
		 h[i].info = 0;
	}
}

int hash(int k, int size){
	return (k%SIZE);
}

int find_probe (HashTableP h, int k){
	int p = hash(k,SIZE);
	int count;
	int tmp;

	for(count = SIZE; count > 0 && h[p].status == STATUS_USED && h[p].key != k; count--){
		p = (p+1)%SIZE;
	}
	if(h[p].key != k){
		if(count == 0) p = -1;
		else{
			tmp = p;
			while(count > 0 && h[p].status != STATUS_FREE && h[p].key != k){
				count--;
				p=(p+1)%SIZE;
			}
			if(h[p].key != k) p = tmp;
		}
	}
	return p;
}

int lookup (HashTableP h, int k, int *i){
	int p = find_probe(h,k);
	int found;
	if(p>=0 && h[p].key == k && h[p].status == STATUS_USED){
		*i = h[p].info;
		found = 1;
	} else {
		found = 0;
	}
	return found;
}

int update (HashTableP h, int k, int i){
	int p = find_probe(h,k);
	int r;
	if(p<0) r = 0;
	else if(h[p].key == k){
		h[p].info = i;
		h[p].status = STATUS_USED;
		r = 1;
	} else {
		h[p].status = STATUS_USED;
		h[p].key = k;
		h[p].info = i;
		r = 2;
	}
	return r;
}

int delete (HashTableP h, int k){
	int p = find_probe(h,k);
	int r = 0;

	if(p>= 0 && h[p].key == k && h[p].status == STATUS_USED) h[p].status = STATUS_DELETED;
	else r = 1;

	return r;
}

void printHashTableP(HashTableP h){
	for(int i = 0; i < SIZE; i++){
		printf("index %d -> ",i);
		printf("key = %d | info = %d | status = ",h[i].key,h[i].info);
		if(h[i].status == STATUS_USED) printf("USED\n");
		else if(h[i].status == STATUS_FREE) printf("FREE\n");
		else if(h[i].status == STATUS_DELETED) printf("DELETED\n");
	}
}

void main(){
	HashTableP h;
	initTab(h);

	int r = 0;
	r = update(h,1,1);
	puts("1,1");
	if(r == 0) puts("falhou!");
	else if(r == 1) puts("atualizada!");
	else if(r == 2) puts("adicionada!");

	puts("\n****\n");

	r = update(h,15,15);
	puts("15,15");
	if(r == 0) puts("falhou!");
	else if(r == 1) puts("atualizada!");
	else if(r == 2) puts("adicionada!");

	puts("\n****\n");

	r = update(h,14,14);
	puts("14,14");
	if(r == 0) puts("falhou!");
	else if(r == 1) puts("atualizada!");
	else if(r == 2) puts("adicionada!");

	puts("\n****\n");

	r = update(h,3,3);
	puts("3,3");
	if(r == 0) puts("falhou!");
	else if(r == 1) puts("atualizada!");
	else if(r == 2) puts("adicionada!");

	puts("\n****\n");

	r = update(h,9,9);
	puts("9,9");
	if(r == 0) puts("falhou!");
	else if(r == 1) puts("atualizada!");
	else if(r == 2) puts("adicionada!");

	puts("\n****\n");

	r = update(h,5,5);
	puts("5,5");
	if(r == 0) puts("falhou!");
	else if(r == 1) puts("atualizada!");
	else if(r == 2) puts("adicionada!");

	puts("\n****\n");

	r = update(h,27,27);
	puts("27,27");
	if(r == 0) puts("falhou!");
	else if(r == 1) puts("atualizada!");
	else if(r == 2) puts("adicionada!");

	puts("\n****\n");

	printHashTableP(h);
}