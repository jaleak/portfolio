#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <string.h>
#include "food.h"

struct FOOD{
	char *name;
	char *company;
	float calories;
	float carbs;
	float fat;
	float protein;
	
	float amountInGrams;
	char *grams;
	float amountPer;
	char *unit;	
};

FOOD * newFOOD(char *newName,char *newComp,float newCal,float newCarbs,float newFat,float newPro, float newAmountinG, char *newGrams, float newAmountPer, char *newUnit){
	FOOD *p = malloc(sizeof(FOOD));
	assert(p  != 0);
	p->name = newName;
	p->company = newComp;
	p->calories = newCal;
	p->carbs = newCarbs;
	p->fat = newFat;
	p->protein = newPro;
	p->amountInGrams = newAmountinG;
	p->grams = newGrams;
	p->amountPer = newAmountPer;
	p->unit = newUnit;
}
char *getFOODNAME(FOOD *v){
	return v->name;	
}
char *setFOOD(FOOD *v,char *x);
void displayFOOD(void *v,FILE *fp);
int compareFOOD(void *v,void *w);
void freeFOOD(void *v):

#endif
