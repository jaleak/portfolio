#include "cda.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct cda{
void **data;
int totalSize, numItems, debugFlag, startIndex, endIndex;
void(*displayMethod)(void *,FILE *);
void(*freeMethod)(void *);
}CDA;

int correctIndex(CDA *items, int index){
	int returnIndex = (index + items->totalSize)%items->totalSize;
	return returnIndex;
}
void doubleSizeCDA(CDA *items){
	int newTotalSize = 0;
	newTotalSize = items->totalSize * 2;
	void **newArray = NULL;
	newArray = (void **)malloc(sizeof(void*) * newTotalSize);
	for(int j = 0; j < newTotalSize; j++){
//		newArray[j] = (void*)malloc(sizeof(void*));
		newArray[j] = NULL;
	}
	for(int i = 0; i < items->numItems; i++){
		newArray[i] = getCDA(items,i);	
	}
//	for(int j = 0; j < items->numItems; j++){
//		if(items->freeMethod != NULL)
		//	items->freeMethod(getCDA(items,j));
//	}
	free(items->data);
	items->startIndex = 0;
	items->endIndex = items->numItems - 1;
	items->data = newArray;
	items->totalSize = newTotalSize;
}
void halfSizeCDA(CDA *items){
	int newTotalSize = 0;
	newTotalSize = items->totalSize / 2;
	void **newCDA = NULL;
	newCDA = (void **)malloc(sizeof(void*) * newTotalSize);
	for(int j = 0; j < newTotalSize; j++){
		//newCDA[j] = (void*)malloc(sizeof(void*));
		newCDA[j] = NULL;
	}
	for(int i = 0;i < items->numItems; i++){
		newCDA[i] = getCDA(items,i);
	}
//	for(int j = 0; j < items->numItems; j++){
	//	if(items->freeMethod != NULL)
	//		items->freeMethod(items->data[j]);
//	}
	free(items->data);
	items->startIndex = 0;
	items->endIndex = items->numItems - 1;
	items->data = newCDA;
	items->totalSize = newTotalSize;
}
CDA *newCDA(void){
	CDA *newCDA;
	newCDA = (CDA *)malloc(sizeof(CDA));
	assert(newCDA != 0);
	newCDA->totalSize = 1;
	newCDA->numItems = 0;
	newCDA->debugFlag = 0;
	newCDA->startIndex = 0;
	newCDA->endIndex = 0;
	newCDA->displayMethod = NULL;
	newCDA->freeMethod = NULL;
	newCDA->data = (void **)malloc(sizeof(void*) * newCDA->totalSize);
	for(int i = 0; i < newCDA->totalSize; i++)
		newCDA->data[i] = NULL;
	assert(newCDA->data != 0);
	return newCDA;
}
void setCDAdisplay(CDA *items, void (*display)(void *v,FILE *f)){
	items->displayMethod = display;
}
void setCDAfree(CDA *items, void (*free)(void *)){
	items->freeMethod = free;
}
void insertCDA(CDA *items,int index,void *value){
	int realIndex = 0;
	void *temp, *prevVal;
	assert(index > -1 && index <= items->totalSize);
	if(index == items->totalSize || items->numItems == items->totalSize)
		doubleSizeCDA(items);
	if(index == items->numItems){
		items->endIndex = correctIndex(items, items->endIndex + 1);
		items->data[items->endIndex] = value;	
	}
	else if(index == 0){
		items->startIndex = correctIndex(items, items->startIndex - 1);
		items->data[items->startIndex] = value;
	}
	else if(index >= items->numItems / 2){
		realIndex = correctIndex(items, index + items->startIndex);
		prevVal = items->data[realIndex];
		items->data[realIndex] = value;
		for(int i = index+1;i <= items->numItems;i++){
			realIndex = correctIndex(items,i + items->startIndex);
			temp = items->data[realIndex];
			items->data[realIndex] = prevVal;
			prevVal = temp;
		}
	
/*		prevVal = getCDA(items,index);		
		setCDA(items,index,value);
		for(int i = index+1;i<=items->numItems;i++){
			temp = setCDA(items,i,prevVal);
			prevVal = temp;
		}
*/
		items->endIndex = correctIndex(items, items->endIndex + 1);
	}
	else if(index < items->numItems / 2){
		realIndex = correctIndex(items, index + items->startIndex - 1);
		prevVal = items->data[realIndex];
		items->data[realIndex] = value;
		for(int i = index-2; i >= -1; i--){
			//if(i == -1){
			//	insertCDAfront(items,prevVal);	
			//	items->startIndex = correctIndex(items,items->startIndex - 1);
			//}
			//else{
			realIndex = correctIndex(items,i + items->startIndex);
			temp = items->data[realIndex];
			items->data[realIndex] = prevVal;
			prevVal = temp;
			//}
		}
		items->startIndex = correctIndex(items,items->startIndex - 1);
	
	/*	prevVal = setCDA(items,index,value);
		for(int i = index-1;i>=-1;i--){
			if(items->data[(correctIndex(items,i))] == NULL){
				items->data[i] = (void *)malloc(sizeof(void *));
			}
			temp = setCDA(items,i,prevVal);
			prevVal = temp;
			displayCDA(items,stdout);
		}
		items->startIndex = correctIndex(items,items->startIndex - 1);
	*/	
	}
	items->numItems++;
}
void *removeCDA(CDA *items,int index){
	assert(items->numItems > 0);
	void* removedVal;
	void* temp;
	if(index == items->numItems){
		removedVal = items->data[items->endIndex]; 
		items->endIndex = correctIndex(items, items->endIndex - 1);
	}
	else if(index == 0){
		removedVal = items->data[items->startIndex];
		items->startIndex = correctIndex(items, items->startIndex + 1);
	}
	else if(index >= items->numItems / 2){	
		removedVal = getCDA(items,index);
		temp = getCDA(items,index+1);
		setCDA(items,index,temp);
		for(int i = index+1;i < items->numItems; i++){
			temp = getCDA(items,i+1); 
			setCDA(items,i,temp);
		}
		items->endIndex = correctIndex(items, items->endIndex - 1);	
	}
	else if(index <= items->numItems / 2){
		removedVal = getCDA(items,index);
		temp = getCDA(items,index-1);
		setCDA(items,index,temp);
		for(int i = index - 1;i > 0; i--){
			temp = getCDA(items,i-1);
			setCDA(items,i,temp);
		}
		items->startIndex = correctIndex(items, items->startIndex + 1);
	}
	items->numItems--;
	while((double)((double)items->numItems/(double)items->totalSize) < 0.25 && items->totalSize > 1)
		halfSizeCDA(items);	
	return removedVal;
}
void unionCDA(CDA *recipient,CDA *donor){
	if(donor->numItems == 0)
		return;
	for(int i = 0;i < donor->numItems; i++){
		insertCDAback(recipient,removeCDA(donor,0));
	}		
}
void *getCDA(CDA *items,int index){
	assert(index >= 0 && index < items->totalSize);
	int realIndex = correctIndex(items,index + items->startIndex);
	return items->data[realIndex];
}
void *setCDA(CDA *items,int index,void *value){
	int realIndex = 0;
	void *temp = NULL;
	if(index == items->numItems){
		insertCDAback(items,value);
	}
	else if(index == -1){
		insertCDAfront(items,value);
	}
	else if(index > items->numItems || index < 0)
		return temp;
	else{
		realIndex = correctIndex(items, index + items->startIndex);
		temp = items->data[realIndex]; 
		items->data[realIndex] = value;
	}
	return temp;
}
int  sizeCDA(CDA *items){
	return items->numItems;
}
void displayCDA(CDA *items,FILE *fp){
	fprintf(fp,"(");
	if(items->debugFlag == 0){
		for(int i = 0; i < items->numItems; i++){
			if(i != items->numItems && i > 0)
				fprintf(fp,",");
			if(items->displayMethod == NULL)
				fprintf(fp,"@%p",getCDA(items,i));
			else{
			//	printf("%d",i);
				items->displayMethod(getCDA(items,i),fp);
			}
		}
	}
	else{
		for(int j = 0; j < items->numItems; j++){
			if(j != items->numItems && j > 0)
				fprintf(fp,",");
			if(items->displayMethod == NULL)
				fprintf(fp,"@%p",getCDA(items,j));
			else
				items->displayMethod(getCDA(items,j),fp);
		}
			if(items->numItems !=0)
				fprintf(fp,",");
			fprintf(fp,"(");
			fprintf(fp,"%d",items->totalSize - items->numItems);
			fprintf(fp,")");
	}
	fprintf(fp,")");
	return;
}
int  debugCDA(CDA *items,int level){
	int prevDebug = 0;
	prevDebug = items->debugFlag;
	items->debugFlag = level;
	return prevDebug; 
}
void freeCDA(CDA *items){
	for(int i = 0;i < items->numItems;i++){
		if(items->freeMethod != NULL)
			items->freeMethod(getCDA(items,i));
	}
	free(items->data);
	free(items);
}
