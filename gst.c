#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gst.h"
#include "bst.h"

typedef struct gst{
	BST *tree;
	int debug;
	int duplicates;
	void (*free)(void *);	
	void (*display)(void *, FILE *);
	int (*comparator)(void *,void *);
}GST;
typedef struct gtval{
	void *value;
	int frequency;
	void (*display)(void *,FILE *);
	void (*free)(void *);
	int (*comparator)(void *,void *);		
}GTVALUE;

void *getValue(GTVALUE *val){
	return val->value;
}

int getFreq(GTVALUE *val){
	return val->frequency;
}

void valueDisplay(void *value, FILE *fp){
	GTVALUE *val = ((GTVALUE *)value);
	val->display(getValue(val),fp);
	if(getFreq(val) > 1){
		fprintf(fp,"<%d>",getFreq(val));
	}
}
static int valueComparator(void *x,void *y){
	GTVALUE *valX = ((GTVALUE *)x);
	GTVALUE *valY = ((GTVALUE *)y);
	return valX->comparator(getValue(valX),getValue(valY));
}
void freeGSTV(void *value){
	GTVALUE *val = ((GTVALUE *)value);
	if(val->value != NULL){
		if(val->free != NULL)
			val->free(val->value);
		else
			free(val->value);
	}
	free(val);
}
GST *newGST(int (*c)(void *,void *)){
	GST *newGST;
	newGST = (GST *)malloc(sizeof(GST));
	newGST->comparator = c;
	newGST->tree = newBST(valueComparator);	
	setBSTdisplay(newGST->tree,valueDisplay);
	setBSTfree(newGST->tree,freeGSTV);
	newGST->debug = 0;
	newGST->free = NULL;
	newGST->duplicates = 0;
	return newGST;
}
static GTVALUE *newGTVALUE(void (*display)(void *,FILE *),int (*comparator)(void *,void *),void (*free)(void *), void *value){
	GTVALUE *node = malloc(sizeof(GTVALUE));
	node->free = free;
	node->value = value;
	node->frequency = 1;
	node->display = display;
	node->comparator = comparator;
	return node;
}
void increment(GTVALUE *val){
	val->frequency++;
}
void decrement(GTVALUE *val){
	val->frequency--;
}
void setGSTdisplay(GST *t,void (*d)(void *,FILE *)){
	t->display = d;
}
void setGSTswapper(GST *t,void (*s)(TNODE *,TNODE *)){
	setBSTswapper(t->tree,s);
}
void setGSTfree(GST *t,void (*f)(void *)){
	t->free = f;
}
TNODE *getGSTroot(GST *t){
	return getBSTroot(t->tree);	
}
void setGSTroot(GST *t,TNODE *replacement){
	setBSTroot(t->tree,replacement);
}
void setGSTsize(GST *t,int s){
	setBSTsize(t->tree,s);
}
TNODE *insertGST(GST *t,void *value){
	TNODE *temp;
	GTVALUE *node = newGTVALUE(t->display,t->comparator,t->free,value);
	temp = locateBST(t->tree,node);
	GTVALUE *temp2;
	if(temp != NULL){	
		temp2 = getTNODEvalue(temp);
		increment(temp2);
		if(t->free != NULL)
			t->free(value);
		free(node);
		return temp;
	}
	else{
		temp = insertBST(t->tree,node);
		return temp;
	}
	return temp;
}
void  *findGST(GST *t,void *key){
	TNODE *temp;
	GTVALUE *node = newGTVALUE(t->display, t->comparator,t->free,key);
	temp = locateBST(t->tree,node);
	if(temp){
		free(node);
		return unwrapGST(temp);
	}
	else{
		free(node);
		return NULL;
	}
}
//fix
TNODE *locateGST(GST *t,void *key){	
	TNODE *temp;
	GTVALUE *node = newGTVALUE(t->display,t->comparator,t->free,key);
	temp = locateBST(t->tree,node);
	if(temp){
		free(node);
		return temp;
	}
	else{
		free(node);
		return NULL;
	}
}
int deleteGST(GST *t,void *key){
	TNODE *temp;
	GTVALUE *node = newGTVALUE(t->display,t->comparator,t->free,key);
	temp = locateBST(t->tree,node);
	free(node);
	GTVALUE *temp2;
	if(temp != NULL){
		temp2 = getTNODEvalue(temp);
		if(getFreq(temp2) == 1){
			deleteBST(t->tree,temp2);
			if(t->free != NULL)
				temp2->free(temp2->value);
			free(temp2);
			return 0;
		}
		else{
			decrement((GTVALUE *)getTNODEvalue(temp));
			return getFreq(getTNODEvalue(temp));
		}
	}
	else
		return -1;
}
TNODE *swapToLeafGST(GST *t,TNODE *node){
	return swapToLeafBST(t->tree,node);
}
void pruneLeafGST(GST *t,TNODE *leaf){
	pruneLeafBST(t->tree,leaf);
}
int sizeGST(GST *t){
	return sizeBST(t->tree);
}
void statisticsGST(GST *t,FILE *fp){
	fprintf(fp,"Duplicates: %d\n",duplicatesGST(t));
	statisticsBST(t->tree,fp);	
}
void displayGST(GST *t,FILE *fp){
	displayBST(t->tree,fp);
}
int debugGST(GST *t,int level){
	return debugBST(t->tree,level);
}
void freeGST(GST *t){
	freeBST(t->tree);
	free(t);	
}

/* extensions of BST */
void *unwrapGST(TNODE *n){
	if(n != NULL){
		GTVALUE *val = getTNODEvalue(n);
		return val->value;
	}
	else
		return NULL;
}
int freqGST(GST *g,void *key){
	int frequency = 0;
	TNODE *temp;
	GTVALUE *node = newGTVALUE(g->display,g->comparator,g->free,key);
	temp = locateBST(g->tree,node);
	free(node);
	GTVALUE *temp2;
	if(temp!= NULL){
		temp2 = getTNODEvalue(temp); 
		frequency = getFreq(temp2);	
		return frequency;
	}
	else{
		return 0;
	}
}
void duplicatesHelper(GST *t,TNODE *n){
	if(n == NULL){
		return;
	}
	else if(getFreq(getTNODEvalue(n)) > 1)
		t->duplicates += getFreq(getTNODEvalue(n)) - 1;
	duplicatesHelper(t,getTNODEleft(n));
	duplicatesHelper(t,getTNODEright(n));
}
int duplicatesGST(GST *g){
	duplicatesHelper(g,getGSTroot(g));
	int duplicates = 0;
	duplicates = g->duplicates;
	g->duplicates = 0;
	return duplicates;
}
