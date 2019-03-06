#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bst.h"
#include "queue.h"

typedef struct bst{
	int(*comparator)(void *,void *);
	void(*display)(void *,FILE *);
	void(*swapper)(TNODE *,TNODE *);
	void(*free)(void *);
	int size;
	int debug;
	int numNodes;
	TNODE *root;
}BST;

BST *newBST(int (*c)(void *,void *)){
	BST *newBST;
	newBST = (BST *)malloc(sizeof(BST));
	newBST->comparator = c;
	newBST->root = NULL;
	newBST->display = NULL;
	newBST->swapper = NULL;
	newBST->free = NULL;
	newBST->size = 0;	
	newBST->debug = 0;
	newBST->numNodes = 0;
	return newBST;
}
void setBSTdisplay(BST *t, void (*d)(void *, FILE *)){
	t->display = d;
}
void setBSTswapper(BST *t, void (*s)(TNODE *, TNODE *)){
	t->swapper = s;
}
void setBSTfree(BST *t, void (*f)(void *)){
	t->free = f;
}
TNODE *getBSTroot(BST *t){
	return t->root;
}
void setBSTroot(BST *t, TNODE *replacement){
//	if(t->root == NULL){
//		t->root = replacement;
//		setTNODEparent(t->root,t->root);
//		return;
//	}
//	TNODE *temp = t->root;
/*	temp = getTNODEleft(temp);
	if(temp != NULL)
		setTNODEparent(temp,replacement);
	temp = t->root;
	temp = getTNODEright(temp);
	if(temp != NULL)
		setTNODEparent(temp,replacement);	
	t->root = replacement;
*/
	t->root = replacement;
	setTNODEparent(t->root,t->root);
	return;
}
void setBSTsize(BST *t, int s){
	t->size = s;
}
TNODE *insertBST(BST *t, void *value){
	TNODE *y = NULL;
	TNODE *x = getBSTroot(t);
	TNODE *new = NULL;
	while(x != NULL){
		y = x;
		if(t->comparator(value,getTNODEvalue(y)) < 0){
			x = getTNODEleft(x);
		}
		else
			x = getTNODEright(x);
	}
	new = newTNODE(value,NULL,NULL,y);
	if(y == NULL){
		setBSTroot(t,new);
	}
	else if(t->comparator(getTNODEvalue(new),getTNODEvalue(y)) < 0)
		setTNODEleft(y,new);
	else
		setTNODEright(y,new);
	if(new != getBSTroot(t))
		setTNODEparent(new,y);
	setBSTsize(t,sizeBST(t)+1);
	setTNODEdisplay(new,t->display);
	setTNODEfree(new,t->free);
	return new;
}
void *findBST(BST *t, void *key){
	TNODE *y = t->root;
	while(y != NULL){
		if(t->comparator(getTNODEvalue(y),key) == 0)
			return getTNODEvalue(y);
		else if(t->comparator(getTNODEvalue(y),key) < 0)
			y = getTNODEright(y);
		else
			y = getTNODEleft(y);
	}	
	return NULL;
}
TNODE *locateBST(BST *t, void *key){
	if(t == NULL)
		return NULL;
	TNODE *y = t->root;
	while(y != NULL){
		if(t->comparator(getTNODEvalue(y),key) == 0)
			return y;
		else if(t->comparator(getTNODEvalue(y),key) < 0)
			y = getTNODEright(y);
		else
			y = getTNODEleft(y);
	}	
	return NULL;
}
int deleteBST(BST *t, void *key){
	TNODE *v = locateBST(t,key);
	v = swapToLeafBST(t,v);
	pruneLeafBST(t,v);				
	if(v == NULL)
		return -1;
	else{
		setBSTsize(t,sizeBST(t)-1);
		return 0;
	}
}
//fix swapper
TNODE *swapper(TNODE *a, TNODE *b){
	void *first = getTNODEvalue(a);
	void *second = getTNODEvalue(b);
	setTNODEvalue(a,second);
	setTNODEvalue(b,first);
	return b;
}
TNODE *swapToLeafBST(BST *t, TNODE *node){
	TNODE *next;
	if(getTNODEleft(node) == NULL && getTNODEright(node) == NULL)
		return node;
	next = getTNODEleft(node);
	if(next == NULL){
		next = getTNODEright(node);
		while(getTNODEleft(next) != NULL)
			next = getTNODEleft(next);
	}
	else{
		while(getTNODEright(next) != NULL)
			next = getTNODEright(next);
	}
	if(t->swapper != NULL)
		t->swapper(node,next);
	else
		swapper(node,next);
	return swapToLeafBST(t,next);
	
}
void pruneLeafBST(BST *t, TNODE *leaf){
	TNODE *temp = getTNODEparent(leaf);
	if(temp == leaf)
	{
		t->root = NULL;
		free(leaf);
		return;
	}
	if(getTNODEleft(temp) != NULL && t->comparator(getTNODEvalue(getTNODEleft(temp)),getTNODEvalue(leaf)) == 0){
		setTNODEleft(temp,NULL);	
	}
	else if(t->comparator(getTNODEvalue(getTNODEright(temp)),getTNODEvalue(leaf)) == 0){
		setTNODEright(temp,NULL);
	}
	setTNODEparent(leaf,NULL);
	free(leaf);
	return;
}
int sizeBST(BST *t){
	return t->size;
}
void inorder(TNODE *t,FILE *fp){
	if(t == NULL)
		return;
	if(getTNODEleft(t) != NULL){
		fprintf(fp,"[");
		inorder(getTNODEleft(t),fp);
		fprintf(fp,"] ");
	}
	displayTNODE(t,fp);
	if(getTNODEright(t) != NULL){
		fprintf(fp," [");
		inorder(getTNODEright(t),fp);
		fprintf(fp,"]");
	}		
}
void postorder(TNODE *t,FILE *fp){
	if(t == NULL)
		return;
	if(getTNODEleft(t) != NULL){
		fprintf(fp,"[");
		postorder(getTNODEleft(t),fp);
		fprintf(fp,"] ");
	}
	if(getTNODEright(t) != NULL){
		fprintf(fp,"[");
		postorder(getTNODEright(t),fp);
		fprintf(fp,"] ");
	}
	displayTNODE(t,fp);
}
void preorder(TNODE *t,FILE *fp){
	if(t == NULL)
		return;
	displayTNODE(t,fp);
	if(getTNODEleft(t) != NULL){
		fprintf(fp," [");
		preorder(getTNODEleft(t),fp);
		fprintf(fp,"]");
	}
	if(getTNODEright(t) != NULL){
		fprintf(fp," [");
		preorder(getTNODEright(t),fp);
		fprintf(fp,"]");
	}
}
void levelorder(TNODE *t, FILE *fp){
	int counter = 0;
	if(t == NULL){
		fprintf(fp,"%d:",counter);
		fprintf(fp,"\n");
		return;
	}
	fprintf(fp,"%d: ",counter);
	TNODE *x = NULL;
	QUEUE *queue = newQUEUE();
	enqueue(queue,t);
	enqueue(queue,NULL);
	while(sizeQUEUE(queue) != 0){
		x = dequeue(queue);	
		if(x == NULL && sizeQUEUE(queue) != 0){
			enqueue(queue,NULL);
			counter++;
			fprintf(fp,"\n");
			fprintf(fp,"%d: ",counter);
		}
		else if(sizeQUEUE(queue) != 0){
			if(getTNODEleft(x) == NULL && getTNODEright(x) == NULL)
				fprintf(fp,"=");	
			displayTNODE(x,fp);
			fprintf(fp,"(");
			if(getTNODEparent(x) != x){
				displayTNODE(getTNODEparent(x),fp);
				if(peekQUEUE(queue) != NULL){
					if(x == getTNODEleft(getTNODEparent(x)))
						fprintf(fp,")L ");
					else if(x == getTNODEright(getTNODEparent(x)))
						fprintf(fp,")R ");
				}
				else{
					if(x == getTNODEleft(getTNODEparent(x)))
						fprintf(fp,")L");
					else if(x == getTNODEright(getTNODEparent(x)))
						fprintf(fp,")R");
				}
			}
			else{
				displayTNODE(x,fp);	
				fprintf(fp,")");
				fprintf(fp,"X");
			}
			if(getTNODEleft(x) != NULL)
				enqueue(queue,getTNODEleft(x));	
			if(getTNODEright(x) != NULL)
				enqueue(queue,getTNODEright(x));
		}		
		else
			fprintf(fp,"\n");
	}		
	freeQUEUE(queue);
	return;
}
int minDepth(TNODE *root){
	if(root == NULL)
		return -1;
	else{
		int lDepth = minDepth(getTNODEleft(root));
		int rDepth = minDepth(getTNODEright(root));
		if(lDepth < rDepth)
			return (lDepth+1);
		else
			return (rDepth + 1);
	}
}
int maxDepth(TNODE *root){
	if(root == NULL)
		return -1;
	else{
		int leftDepth = maxDepth(getTNODEleft(root));
		int rightDepth = maxDepth(getTNODEright(root));
		if(leftDepth > rightDepth)
			return (leftDepth + 1);
		else
			return (rightDepth + 1);
	}
}
void numNodes(BST *t, TNODE *root){
	if(root == NULL)
		return;
	else
		t->numNodes++;
	numNodes(t,getTNODEleft(root));
	numNodes(t,getTNODEright(root));
}
void statisticsBST(BST *t, FILE *fp){
	numNodes(t,t->root);
	int mindepth = minDepth(t->root);
	int maxdepth = maxDepth(t->root);
	fprintf(fp,"Nodes: %d\n",t->numNodes);
	t->numNodes = 0;
	fprintf(fp,"Minimum depth: %d\n",mindepth);
	fprintf(fp,"Maximum depth: %d\n",maxdepth);	
}
void displayBST(BST *t, FILE *fp){
	if(t->debug == 0){
		levelorder(t->root,fp);
	}		
	if(t->debug == 1){
		fprintf(fp,"[");
		inorder(t->root,fp);
		fprintf(fp,"]");
	}
	if(t->debug == 2){
		fprintf(fp,"[");
		preorder(t->root,fp);
		fprintf(fp,"]");
	}
	if(t->debug == 3){
		fprintf(fp,"[");
		postorder(t->root,fp);
		fprintf(fp,"]");
	}
}
int debugBST(BST *t, int level){
	t->debug = level;
	return level;
}
void helper(BST *tree,TNODE *t){
	if(t == NULL)
		return;
	if(getTNODEleft(t) != NULL){
		helper(tree,getTNODEleft(t));
	}
	if(getTNODEright(t) != NULL){
		helper(tree,getTNODEright(t));
	}
	freeTNODE(t);
}	
void freeBST(BST *t){
	if(t == NULL)
		return;
	if(t->root != NULL)
		helper(t,t->root);
	free(t);
}
