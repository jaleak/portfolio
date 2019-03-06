#include <stdio.h>
#include "cda.h"
#include "queue.h"
#include <stdlib.h>
typedef struct queue{ 
	CDA *cda;
	int debugFlag;
	void(*displayMethod)(void *,FILE *);
	void(*freeMethod)(void *);
}QUEUE;

QUEUE *newQUEUE(void){
	QUEUE *newQueue = malloc(sizeof(QUEUE));
	newQueue->displayMethod = NULL;
	newQueue->freeMethod = NULL;
	newQueue->cda = newCDA();
	newQueue->debugFlag = 0;
	return newQueue;
}
void setQUEUEdisplay(QUEUE *items,void (*d)(void *v,FILE *f)){
	items->displayMethod = d;
	setCDAdisplay(items->cda,d);
	return;
}
void  setQUEUEfree(QUEUE *items,void (*f)(void *v)){
	items->freeMethod = f;
	setCDAfree(items->cda,f);
	return;
}
void  enqueue(QUEUE *items,void *value){
//	insertCDAfront(items->cda,value);
	insertCDAback(items->cda,value);
	return;
}
void *dequeue(QUEUE *items){
	return removeCDAfront(items->cda);
//	return removeCDAback(items->cda);
}
void *peekQUEUE(QUEUE *items){
	return getCDA(items->cda,0);
}
void  displayQUEUE(QUEUE *items,FILE *fp){
	if(items->debugFlag == 0){
		fprintf(fp,"<");
		for(int i = 0; i < sizeCDA(items->cda);i++){
			if(i > 0 && i != sizeCDA(items->cda))
				fprintf(fp,",");
			if(items->displayMethod == NULL)
				fprintf(fp,"@%p",getCDA(items->cda,i));
			else
				items->displayMethod(getCDA(items->cda,i),fp);	
		}
		fprintf(fp,">");
	}
	else if(items->debugFlag == 1){
		debugCDA(items->cda,0);
		displayCDA(items->cda,fp);	
	}
	else if(items->debugFlag == 2){
		debugCDA(items->cda,1);
		displayCDA(items->cda,fp);
	}
}
int   debugQUEUE(QUEUE *items,int level){
	int prev = items->debugFlag;
	items->debugFlag = level;
	return prev;
}
void  freeQUEUE(QUEUE *items){
	freeCDA(items->cda);
	free(items);
}
int   sizeQUEUE(QUEUE *items){
	return sizeCDA(items->cda);
}
