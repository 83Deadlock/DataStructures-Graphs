#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct avl {
	int bal;
	int key, info;
	struct avl *left, *right;
} *AVLTree;

#define LEFT 1
#define BAL 0
#define RIGHT -1

AVLTree rotateRight (AVLTree a){
	AVLTree b = a->left;
	a->left = b->right;
	b->right = a;
	return b;
}

AVLTree rotateLeft (AVLTree a){
	AVLTree b = a->right;
	a->right = b->left;
	b->left = a;
	return b;
}

AVLTree fixRight(AVLTree a){
	AVLTree b, c;
	b = a->right;
	if(b->bal == RIGHT){
		a->bal = b->bal = BAL;
		a = rotateLeft(a);
	} else {
		c = b->left;
		switch(c->bal){
			case LEFT: 	a->bal = BAL;
					   	b->bal = RIGHT;
					   	break;

			case RIGHT: a->bal = LEFT;
						b->bal = BAL;
						break;

			case BAL: 	a->bal = b->bal = BAL;
		}
		c->bal = BAL;
		a->right = rotateRight(b);
		a = rotateLeft(a);
	}
	return a;
}

AVLTree fixLeft(AVLTree a){
	AVLTree b, c;
	b = a->left;
	if(b->bal == LEFT){
		a->bal = b->bal = BAL;
		a = rotateRight(a);
	} else {
		c = b->right;
		switch(c->bal){
			case LEFT: 	a->bal = RIGHT;
					   	b->bal = BAL;
					   	break;

			case RIGHT: a->bal = BAL;
						b->bal = LEFT;
						break;

			case BAL: 	a->bal = b->bal = BAL;
		}
		c->bal = BAL;
		a->left = rotateLeft(b);
		a = rotateRight(a);
	}
	return a;
}

AVLTree updateAVLRec (AVLTree a, int k, int i, int * g, int *u){
	if(a == NULL){								//Árvore inicial estava vazia
		a = malloc(sizeof(struct avl));

		a->key = k;
		a->info = i;
		a->bal = BAL;
		a->left = a->right = NULL;

		*g = 1; *u = 0;

	} else if(a->key == k){
		a->info = i;

		*g = 0; 
		*u = 1;

	} else if(a->key > k){

		a->left = updateAVLRec(a->left,k,i,g,u);

		if(*g == 1){
			switch(a->bal){
				case LEFT:	a = fixLeft(a);
							*g = 0;
							break;

				case BAL: 	a->bal = LEFT;
							break;

				case RIGHT:	a->bal = BAL; 
							*g = 0;
							break;
			}
		}
	} else {
		a->right = updateAVLRec(a->right,k,i,g,u);
		if(*g == 1){
			switch(a->bal){
				case RIGHT:	a = fixRight(a);
							*g = 0;
							break;

				case BAL: 	a->bal = RIGHT;
						  	break;

				case LEFT: 	a->bal = BAL;
							*g = 0;
							break;
			}
		}
	}
	return a;
}

int updateAVL (AVLTree *a, int k, int i){ //Se a árvore foi atualizada, u fica a 1. Se adicionamos um novo nodo, u fica a 0
	int g, u;
	*a = updateAVLRec(*a,k,i,&g,&u);
	return u;
}

char* convertDefs(int b){
	char* s;
	if(b == -1){
		s = malloc(sizeof(char)*5);
		strcpy(s,"RIGHT");
	} else if(b == 0){
		s = malloc(sizeof(char)*3);
		strcpy(s,"BAL");
	} else {
		s = malloc(sizeof(char)*4);
		strcpy(s,"LEFT");
	}
}

void printTreeAux(AVLTree root, int space){ 
    // Base case 
    if (root == NULL) 
        return; 
  
    // Increase distance between levels 
    space += 10; 
  
    // Process right child first 
    printTreeAux(root->right, space); 
  
    // Print current node after space 
    // count 
    printf("\n"); 
    for (int i = 3; i < space; i++) 
        printf(" "); 
    printf("key = %d || info = %d || Bal = %s\n", root->key,root->info,convertDefs(root->bal)); 
  
    // Process left child 
    printTreeAux(root->left, space); 
} 

void printTree(AVLTree t){
	printTreeAux(t,0);
}

int maxA (int l, int r){
	if(l > r){
		return l;
	}
	else{
		return r;
	}
}

int altura (AVLTree t){
	int r = 0;
	while(t != NULL){
		r++;
		if(t->bal == RIGHT){
			t = t->right;
		} else {
			t = t->left;
		}
	}
	return r;
}

AVLTree maisProfundo (AVLTree t){
	if(t == NULL) return NULL;
	else {
		while(t->left != NULL || t->right != NULL){
			if(t->bal == LEFT) t = t->left;
			else t = t->right;
		}
	}
	return t;
}

void main(){
	
	AVLTree a = NULL;
	int u;

	puts("adicionando k = 20 e info = 20");
	u = updateAVL(&a,20,20);
	if(u == 0) puts("foi criado um novo nodo");
	else if(u == 1) puts("atualizou-se um nodo");

	puts("\n\n\n");

	puts("adicionando k = 40 e info = 40");
	u = updateAVL(&a,40,40);
	if(u == 0) puts("foi criado um novo nodo");
	else if(u == 1) puts("atualizou-se um nodo");

	puts("\n\n\n");

	puts("adicionando k = 10 e info = 10");
	u = updateAVL(&a,10,10);
	if(u == 0) puts("foi criado um novo nodo");
	else if(u == 1) puts("atualizou-se um nodo");

	puts("\n\n\n");

	puts("adicionando k = 50 e info = 50");
	u = updateAVL(&a,50,50);
	if(u == 0) puts("foi criado um novo nodo");
	else if(u == 1) puts("atualizou-se um nodo");

	puts("\n\n\n");

	puts("adicionando k = 30 e info = 30");
	u = updateAVL(&a,30,30);
	if(u == 0) puts("foi criado um novo nodo");
	else if(u == 1) puts("atualizou-se um nodo");

	puts("\n\n\n");

	puts("adicionando k = 15 e info = 15");
	u = updateAVL(&a,15,15);
	if(u == 0) puts("foi criado um novo nodo");
	else if(u == 1) puts("atualizou-se um nodo");

	puts("adicionando k = 29 e info = 29");
	u = updateAVL(&a,29,29);
	if(u == 0) puts("foi criado um novo nodo");
	else if(u == 1) puts("atualizou-se um nodo");

	printTree(a);
	
	/*int alturaT = altura(a);
	printf("Altura = %d\n",alturaT);

	puts("\n\n\n\n\n\n\n NODO MAIS PROFUNDO\n\n\n\n\n");
	printTree(maisProfundo(a));*/

}