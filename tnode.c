#include <stdio.h>
#include <stdlib.h>
#include "tnode.h"

typedef struct tnode{
	TNODE *left;
	TNODE *right;
	TNODE *parent;
	void *value;
	int debugFlag;
	void(*displayMethod)(void *, FILE *);
	void(*freeMethod)(void *);
}TNODE;

TNODE *newTNODE(void *v, TNODE *l,TNODE *r, TNODE *p){
	TNODE *newNode;
	newNode = (TNODE *)malloc(sizeof(TNODE));
	newNode->left = l;
	newNode->right = r;
	newNode->parent = p;
	newNode->value = v;
	newNode->displayMethod = NULL;
	newNode->freeMethod = NULL;
	newNode->debugFlag = 0;
	return newNode;
} 
void setTNODEdisplay(TNODE *n, void (*d)(void *value,FILE *fp)){
	n->displayMethod = d;
}
void setTNODEfree(TNODE *n, void(*f)(void *value)){
	n->freeMethod = f;
}
void *getTNODEvalue(TNODE *n){
	return n->value;
}
void setTNODEvalue(TNODE *n, void *replacement){
	n->value = replacement;
}
TNODE *getTNODEleft(TNODE *n){
	return n->left;
}
void setTNODEleft(TNODE *n, TNODE *replacement){
	n->left = replacement;
}
TNODE *getTNODEright(TNODE *n){
	return n->right;
}
void setTNODEright(TNODE *n, TNODE *replacement){
	n->right = replacement;
}
TNODE *getTNODEparent(TNODE *n){
	return n->parent;
}
void setTNODEparent(TNODE *n, TNODE *replacement){
	n->parent = replacement;
}
void displayTNODE(TNODE *n,FILE *fp){
	if(n->debugFlag > 0){
		if(n->displayMethod != NULL)
			n->displayMethod(n->value,fp);
		fprintf(fp,"&%p",n);
	}
	else{
		if(n->displayMethod == NULL)
			fprintf(fp,"&%p",n->value);
		else
			n->displayMethod(n->value,fp);
	}
}
int debugTNODE(TNODE *n, int level){
	int temp = -1;
	temp = n->debugFlag;
	n->debugFlag = level;
	return temp;	
}
void freeTNODE(TNODE *n){
	if(n->value != NULL){
		if(n->freeMethod != NULL)
			n->freeMethod(n->value);
		else
			free(n->value);
	}
//	if(n->freeMethod != NULL)
//		n->freeMethod(n);
//	else
		free(n);
}
