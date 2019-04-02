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
	return p;
}
char *getFOODNAME(FOOD *v){
	return v->name;	
}
char *getFOODCOMPANY(FOOD *v){
	return v->company;
}
float getFOODCALORIES(FOOD *v){
	return v->calories;
}
float getFOODCARBS(FOOD *v){
	return v->carbs;
}
float getFOODFAT(FOOD *v){
	return v->fat;
}
float getFOODPROTEIN(FOOD *v){
	return v->protein;
}
float getFOODAMOUNTINGRAMS(FOOD *v){
	return v->amountInGrams;
}
char *getFOODGRAMS(FOOD *v){
	return v->grams;
}
float getFOODAMOUNTPER(FOOD *v){
	return v->amountPer;
}
char *getFOODUNIT(FOOD *v){
	return v->unit;
}
//changes name and returns old
char *setFOODNAME(FOOD *v,char *x){
	char *old = v->name;	
	v->name = x;
	return old;
}
char *setFOODCOMPANY(FOOD *v,char *x){
	char *old = v->company;
	v->company = x;
	return old;
}
float setFOODCALORIES(FOOD *v,float x){
	float old = v->calories;
	v->calories = x;
	return old;
}
float setFOODCARBS(FOOD *v,float x){
	float old = v->carbs;
	v->carbs = x;
	return old;
}
float setFOODFAT(FOOD *v,float x){
	float old = v->fat;
	v->fat = x;
	return old;
}
float setFOODPROTEIN(FOOD *v,float x){
	float old = v->protein;
	v->protein = x;
	return old;
}
float setFOODAMOUNTINGRAMS(FOOD *v,float x){
	float old = v->amountInGrams;
	v->amountInGrams = x;
	return old;
}
char *setFOODGRAMS(FOOD *v,char *x){
	char *old = v->grams;
	v->grams = x;
	return old;
}
float setFOODAMOUNTPER(FOOD *v,float x){
	float old = v->amountPer;
	v->amountPer = x;
	return old;
}
char *setFOODUNIT(FOOD *v,char *x){
	char *old = v->unit;
	v->unit = x;
	return old;
}

void displayFOOD(void *v,FILE *fp){
	fprintf(fp,"%s\n",getFOODNAME((FOOD *) v));
	fprintf(fp,"%s\n",getFOODCOMPANY((FOOD *) v));
	fprintf(fp,"Value per 100 g:\n");
	fprintf(fp,"%.2f Calories\n",getFOODCALORIES((FOOD *) v));	
	fprintf(fp,"%.2f Carbohydrates\n",getFOODCARBS((FOOD *) v));
	fprintf(fp,"%.2f Total lipid (fat)\n",getFOODFAT((FOOD *) v));
	fprintf(fp,"%.2f Protein\n",getFOODPROTEIN((FOOD *) v));
	fprintf(fp,"There are ");
	fprintf(fp,"%.2f ",getFOODAMOUNTINGRAMS((FOOD *) v));
	fprintf(fp,"%s ",getFOODGRAMS((FOOD *) v));
	fprintf(fp,"per %.1f ",getFOODAMOUNTPER((FOOD *) v));
	fprintf(fp,"%s\n",getFOODUNIT((FOOD *) v));
	fprintf(fp,"\n");
}
int compareFOOD(void *v,void *w){
	if(strcmp(getFOODNAME(v),getFOODNAME(w)) != 0){
		return strcmp(getFOODNAME(v),getFOODNAME(w));
	}
	if(strcmp(getFOODCOMPANY(v),getFOODCOMPANY(w)) != 0){
		return strcmp(getFOODNAME(v),getFOODNAME(w));
	}
	if((getFOODCALORIES(v) - getFOODCALORIES(w)) != 0){
		return (getFOODCALORIES(v) - getFOODCALORIES(w));
	}
	if((getFOODCARBS(v) - getFOODCARBS(w)) != 0){
		return (getFOODCARBS(v) - getFOODCARBS(w));
	}
	if((getFOODFAT(v) - getFOODFAT(w)) != 0){
		return (getFOODFAT(v) - getFOODFAT(w));
	}
	if((getFOODPROTEIN(v) - getFOODPROTEIN(w)) != 0){
		return (getFOODPROTEIN(v) - getFOODPROTEIN(w));
	}
	if((getFOODAMOUNTINGRAMS(v) - getFOODAMOUNTINGRAMS(w)) != 0){
		return (getFOODAMOUNTINGRAMS(v) - getFOODAMOUNTINGRAMS(w));
	}
	if(strcmp(getFOODGRAMS(v),getFOODGRAMS(w))!=0){
		return (strcmp(getFOODGRAMS(v),getFOODGRAMS(w)));
	}
	if((getFOODAMOUNTPER(v) - getFOODAMOUNTPER(w)) != 0){
		return (getFOODAMOUNTPER(v) - getFOODAMOUNTPER(w));
	}
	if(strcmp(getFOODUNIT(v),getFOODUNIT(w))!=0){
		return (strcmp(getFOODUNIT(v),getFOODUNIT(w)));
	}
	return 0;
}
void freeFOOD(void *v){
	free((FOOD *) v);
}
