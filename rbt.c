#include "tnode.h"
#include "rbt.h"
#include "gst.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct rbt{
	void (*free)(void *);
	void(*display)(void *, FILE *);
	int(*comparator)(void *,void *);
	GST *tree;
}RBT;

typedef struct rbtval{
	void(*display)(void *,FILE *);
	int(*comparator)(void *,void *);
	void(*free)(void *);
	void *value;
	char color;
}RBTVALUE;

void swapperRBT(TNODE *a, TNODE *b){
	RBTVALUE *va = getTNODEvalue(a);
	RBTVALUE *vb = getTNODEvalue(b);
	setTNODEvalue(a,vb);
	setTNODEvalue(b,va);
	RBTVALUE *x = unwrapGST(a);
	RBTVALUE *y = unwrapGST(b);
	char color = x->color;
	x->color = y->color;
	y->color = color;
}
char getColorRBT(RBTVALUE *val){
	if(val == NULL)
		return 'B';
	else
		return val->color;
}
void *getValueRBT(RBTVALUE *val){
	return val->value;
}
static void valueDisplayRBT(void *value, FILE *fp){	
	RBTVALUE *val = ((RBTVALUE*)value);
	val->display(getValueRBT(val),fp);
	if(getColorRBT(val) == 'R'){
		fprintf(fp,"*");
	}			
}
static int valueComparatorRBT(void *x,void *y){
	RBTVALUE *valX = ((RBTVALUE *)x);
	RBTVALUE *valY = ((RBTVALUE *)y);
//	valX->display(getValueRBT(valX),stdout);
//	valY->display(getValueRBT(valY),stdout);
	return valX->comparator(getValueRBT(valX),getValueRBT(valY));
}
void freeRBTV(void *value){
	RBTVALUE *val = ((RBTVALUE *)value);
	if(val->value != NULL){
		if(val->free != NULL)
			val->free(val->value);
		else
			free(val->value);
	}
	free(val);
}
RBT *newRBT(int (*c)(void *,void *)){
	RBT *newrbt = (RBT *)malloc(sizeof(RBT));
	newrbt->comparator = c;
	newrbt->tree = newGST(valueComparatorRBT);
	setGSTdisplay(newrbt->tree,valueDisplayRBT);
	setGSTswapper(newrbt->tree,swapperRBT);
	setGSTfree(newrbt->tree,freeRBTV);
	newrbt->free = NULL;
	newrbt->display = NULL;
	return newrbt;	
}

RBTVALUE *newRBTVALUE(void(*display)(void *,FILE *),int (*comparator)(void *, void *),void (*free)(void *), void *value){
	RBTVALUE *node = malloc(sizeof(RBTVALUE));
	node->free = free;
	node->value = value;
	node->display = display;
	node->comparator = comparator;
	node->color = 'R';
	return node;
}

void setRBTdisplay(RBT *t,void (*d)(void *,FILE *)){
	t->display = d;
}
void setColorRBT(RBTVALUE *val, char replacement){
	val->color = replacement;
}

void setRBTswapper(RBT *t,void (*s)(TNODE *,TNODE *)){
	setGSTswapper(t->tree,s);
}

void setRBTfree(RBT *t,void (*f)(void *)){
//	setGSTfree(t->tree,f);
	t->free = f;
}
TNODE *getRBTroot(RBT *t){
	return getGSTroot(t->tree);
}
void   setRBTroot(RBT *t,TNODE *replacement){
	setGSTroot(t->tree,replacement);
}
void   setRBTsize(RBT *t,int s){
	setGSTsize(t->tree,s);
}
void leftRotate(RBT *t,TNODE *z){
	TNODE *y = getTNODEright(z);
	setTNODEright(z,getTNODEleft(y));
	if(getTNODEleft(y) != NULL){
		setTNODEparent(getTNODEleft(y),z);
	}
	setTNODEparent(y,getTNODEparent(z));
	if(getRBTroot(t) == z){
		setRBTroot(t,y);
		if(getTNODEleft(z) != NULL){
			setTNODEparent(getTNODEleft(z),z);
		}
		if(getTNODEright(z) != NULL)
			setTNODEparent(getTNODEright(z),z);
	}
	else if(z == getTNODEleft(getTNODEparent(z)))
		setTNODEleft(getTNODEparent(z),y);
	else
		setTNODEright(getTNODEparent(z),y);
	setTNODEleft(y,z);
	setTNODEparent(z,y);
}
void rightRotate(RBT *t,TNODE *z){
	TNODE *left = getTNODEleft(z);
	setTNODEleft(z,getTNODEright(left));
	if(getTNODEleft(z) != NULL)
		setTNODEparent(getTNODEleft(z),z);
	setTNODEparent(left,getTNODEparent(z));
	if(getRBTroot(t) == z){
		setRBTroot(t,left);
		if(getTNODEleft(z)!= NULL)
			setTNODEparent(getTNODEleft(z),z);
		if(getTNODEright(z)!= NULL)
			setTNODEparent(getTNODEright(z),z);
	}
	else if(z == getTNODEleft(getTNODEparent(z))){
		setTNODEleft(getTNODEparent(z),left);
	}
	else{
		setTNODEright(getTNODEparent(z),left);
	}
	setTNODEright(left,z);
	setTNODEparent(z,left);	
}
void rbtFixUp(RBT *t,TNODE *x){
	if(x == NULL)
		return;
	TNODE *z = x;
	TNODE *parent = NULL;
	TNODE *grandParent = NULL;
	TNODE *uncle = NULL;
	char tempColor = 'B';
	while(z != getRBTroot(t) && getColorRBT(unwrapGST(z)) != 'B' && getColorRBT(unwrapGST(getTNODEparent(z))) == 'R'){
			parent = getTNODEparent(z);
			grandParent = getTNODEparent(getTNODEparent(z));
			if(parent == getTNODEleft(grandParent)){
				uncle = getTNODEright(grandParent);
				if(uncle != NULL && getColorRBT(unwrapGST(uncle)) == 'R'){
					setColorRBT(unwrapGST(grandParent),'R');
					setColorRBT(unwrapGST(parent),'B');
					setColorRBT(unwrapGST(uncle),'B');
					z = grandParent;
				}
				else{
					if(z == getTNODEright(parent)){
						leftRotate(t,parent);
						z = parent;
						parent = getTNODEparent(z);
					}
					rightRotate(t,grandParent);
					tempColor = getColorRBT(unwrapGST(parent));
					setColorRBT(unwrapGST(parent),getColorRBT(unwrapGST(grandParent)));
					setColorRBT(unwrapGST(grandParent),tempColor);	
					z = parent;
				}
			}	
			else{
				uncle = getTNODEleft(grandParent);	
				if(uncle != NULL && getColorRBT(unwrapGST(uncle)) == 'R'){
					setColorRBT(unwrapGST(grandParent),'R');
					setColorRBT(unwrapGST(parent),'B');
					setColorRBT(unwrapGST(uncle),'B');
					z = grandParent;
				}
				else{
					if(z == getTNODEleft(parent)){
						rightRotate(t,parent);
						z = parent;
						parent = getTNODEparent(z);
					}
					leftRotate(t,grandParent);
					tempColor = getColorRBT(unwrapGST(parent));
					setColorRBT(unwrapGST(parent),getColorRBT(unwrapGST(grandParent)));
					setColorRBT(unwrapGST(grandParent),tempColor);	
					z = parent;
				}
			}
		}
		setColorRBT(unwrapGST(getRBTroot(t)),'B');
}
TNODE *insertRBT(RBT *t,void *value){
	RBTVALUE *temp = newRBTVALUE(t->display,t->comparator,t->free,value);
	TNODE *returnNode;
	returnNode = insertGST(t->tree,temp);
	rbtFixUp(t,returnNode);	
	return returnNode;
}
void  *findRBT(RBT *t,void *key){
	TNODE *temp;
	RBTVALUE *node = newRBTVALUE(t->display,t->comparator,t->free,key);
	temp = locateGST(t->tree,node);
	if(temp){
		free(node);
		return unwrapRBT(temp);
	}
	else{
		free(node);
		return NULL;
	}
}
TNODE *locateRBT(RBT *t,void *key){
	TNODE *temp;
	RBTVALUE *node = newRBTVALUE(t->display,t->comparator,t->free,key);
	temp = locateGST(t->tree,node);
	if(temp){
		free(node);
		return temp;
	}
	else{
		free(node);
		return NULL;
	}
}
void rbDeleteFixup(RBT *t,TNODE *x){
	TNODE *w;
	while(x != getRBTroot(t) && getColorRBT(unwrapGST(x)) == 'B'){
		if(x == getTNODEleft(getTNODEparent(x))){
			w = getTNODEright(getTNODEparent(x));		
			if(getColorRBT(unwrapGST(w)) == 'R'){
				setColorRBT(unwrapGST(w),'B');
				setColorRBT(unwrapGST(getTNODEparent(x)),'R');
				leftRotate(t,getTNODEparent(x));
				w = getTNODEright(getTNODEparent(x));
			}
			if(getColorRBT(unwrapGST(getTNODEleft(w))) == 'B' && getColorRBT(unwrapGST(getTNODEright(w))) == 'B'){
				setColorRBT(unwrapGST(w),'R');
				x = getTNODEparent(x);
			}
			else{
				if(getColorRBT(unwrapGST(getTNODEright(w))) == 'B'){
					setColorRBT(unwrapGST(getTNODEleft(w)),'B');
					setColorRBT(unwrapGST(w),'R');
					rightRotate(t,w);
					w = getTNODEright(getTNODEparent(x));
				}
				setColorRBT(unwrapGST(w),getColorRBT(unwrapGST(getTNODEparent(x))));
				setColorRBT(unwrapGST(getTNODEparent(x)),'B');
				setColorRBT(unwrapGST(getTNODEright(w)),'B');
				leftRotate(t,getTNODEparent(x));
				x = getRBTroot(t);
			}
		}
		else{
			w = getTNODEleft(getTNODEparent(x));		
			if(getColorRBT(unwrapGST(w)) == 'R'){
				setColorRBT(unwrapGST(w),'B');
				setColorRBT(unwrapGST(getTNODEparent(x)),'R');
				rightRotate(t,getTNODEparent(x));
				w = getTNODEleft(getTNODEparent(x));
			}
			if(getColorRBT(unwrapGST(getTNODEright(w))) == 'B' && getColorRBT(unwrapGST(getTNODEleft(w))) == 'B'){
				setColorRBT(unwrapGST(w),'R');
				x = getTNODEparent(x);
			}
			else{
				if(getColorRBT(unwrapGST(getTNODEleft(w))) == 'B'){
					setColorRBT(unwrapGST(getTNODEright(w)),'B');
					setColorRBT(unwrapGST(w),'R');
					leftRotate(t,w);
					w = getTNODEleft(getTNODEparent(x));
				}
				setColorRBT(unwrapGST(w),getColorRBT(unwrapGST(getTNODEparent(x))));
				setColorRBT(unwrapGST(getTNODEparent(x)),'B');
				setColorRBT(unwrapGST(getTNODEleft(w)),'B');
				rightRotate(t,getTNODEparent(x));
				x = getRBTroot(t);
			}
		}
	}
	setColorRBT(unwrapGST(x),'B');
}
TNODE *treeMaximum(TNODE *x){
	while(getTNODEright(x) != NULL)
		x = getTNODEright(x);
	return x;
}
TNODE *treeMinimum(TNODE *x){
	while(getTNODEleft(x) != NULL)
		x = getTNODEleft(x);
	return x;
}
void rbTransplant(RBT *t,TNODE *u,TNODE *v){
	if(getRBTroot(t) == u)
		setRBTroot(t,v);
	else if(u == getTNODEleft(getTNODEparent(u)))
		setTNODEleft(getTNODEparent(u),v);
	else
		setTNODEright(getTNODEparent(u),v);
	if(v != NULL)
		setTNODEparent(v,getTNODEparent(u));
}
int deleteRBT(RBT *t,void *key){
	if(key == NULL)
		return -1;
	TNODE *z;
	int returnVal;
	RBTVALUE *temp = newRBTVALUE(t->display,t->comparator,t->free,key);
	TNODE *y = locateGST(t->tree,temp);			
	z = y;
	free(temp);
	if(y == NULL){
		return -1;
	}
	RBTVALUE *temp2 = newRBTVALUE(t->display,t->comparator,t->free,key);
	if(freqGST(t->tree,temp2) > 1){
		returnVal = deleteGST(t->tree,temp2);
		free(temp2);
		return returnVal;
	}
	free(temp2);
	z = swapToLeafRBT(t,z);
	rbDeleteFixup(t,z);
	RBTVALUE *test2 = unwrapGST(z);
	void *test = getTNODEvalue(z);
	pruneLeafRBT(t,z);
//	deleteGST(t->tree,
	if(t->free != NULL){
		t->free(test2->value);
	}
	free(test2);
	free(test);
	setRBTsize(t,sizeRBT(t)-1);
	return 0;
/*
	TNODE *x = NULL;
	char yOriginalColor = getColorRBT(unwrapGST(y));
	if(getTNODEleft(z) == NULL){
		x = getTNODEright(z);
		rbTransplant(t,z,getTNODEright(z));
	}
	else if(getTNODEright(z) == NULL){
		x = getTNODEleft(z);
		rbTransplant(t,z,getTNODEleft(z));
	}
	else{
		y = treeMinimum(getTNODEright(z));
		yOriginalColor = getColorRBT(unwrapGST(y));
		x = getTNODEright(y);
		if(getTNODEparent(y) == z){
			if(x != NULL){
				setTNODEparent(x,y);
			}
		}
		else{
			rbTransplant(t,y,getTNODEright(y));
			setTNODEright(y,getTNODEright(z));
			if(getTNODEright(z) != NULL)
				setTNODEparent(getTNODEright(z),y);
		}
		rbTransplant(t,z,y);
		setTNODEleft(y,getTNODEleft(z));
		if(getTNODEleft(y) != NULL)
			setTNODEparent(getTNODEleft(y),y);
		setColorRBT(unwrapGST(y),getColorRBT(unwrapGST(z)));
	}
	if(yOriginalColor == 'B' && x != NULL){
		rbDeleteFixup(t,x);	
	}
	RBTVALUE *test2 = unwrapGST(z);
	if(t->free != NULL){
		t->free(test2->value);
	}
	void *test = getTNODEvalue(z);
	free(z);
	free(test2);
	free(test);
	setRBTsize(t,sizeRBT(t)-1);
	return 0;*/
}
TNODE *swapToLeafRBT(RBT *t,TNODE *node){
	return swapToLeafGST(t->tree,node);
}
void pruneLeafRBT(RBT *t,TNODE *leaf){
	pruneLeafGST(t->tree,leaf);
}
int sizeRBT(RBT *t){
	return sizeGST(t->tree);
}
void statisticsRBT(RBT *t,FILE *fp){
	statisticsGST(t->tree,fp);	
}
void displayRBT(RBT *t,FILE *fp){
//	setGSTdisplay(t->tree,t->display);
	displayGST(t->tree,fp);
}
int debugRBT(RBT *t,int level){
	return debugGST(t->tree,level);	
}
void freeRBT(RBT *t){
//	helperRBT(t,getRBTroot(t));
	freeGST(t->tree);
	free(t);
}
void *unwrapRBT(TNODE *n){
	RBTVALUE *val = unwrapGST(n);
	return val->value;
}
int freqRBT(RBT *g,void *key){
	TNODE *temp;
	int freq = 0;
	RBTVALUE *node = newRBTVALUE(g->display,g->comparator,g->free,key);
	temp = locateGST(g->tree,node);
	if(temp){
		freq = freqGST(g->tree,node);
		free(node);
		return freq;
	}
	else{
		free(node);
		return 0;
	}
}
int duplicatesRBT(RBT *g){
	return duplicatesGST(g->tree);
}
