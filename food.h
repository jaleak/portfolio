#ifndef __FOOD_INCLUDED__
#define __FOOD_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <string.h>

typedef struct FOOD FOOD;

extern FOOD * newFOOD(char *a,char *b,float c,float d,float e,float f,float g,char *h,float j,char *k);
extern char *getFOODNAME(FOOD *v);
extern char *getFOODCOMPANY(FOOD *v);
extern float getFOODCALORIES(FOOD *v);
extern float getFOODCARBS(FOOD *v);
extern float getFOODFAT(FOOD *v);
extern float getFOODPROTEIN(FOOD *v);
extern float getFOODAMOUNTINGRAMS(FOOD *v);
extern char *getFOODGRAMS(FOOD *v);
extern float getFOODAMOUNTPER(FOOD *v);
extern char *getFOODUNIT(FOOD *v);

extern char *setFOODNAME(FOOD *v,char *x);
extern char *setFOODCOMPANY(FOOD *v,char *x);
extern float setFOODCALORIES(FOOD *v,float x);
extern float setFOODCARBS(FOOD *v,float x);
extern float setFOODFAT(FOOD *v,float x);
extern float setFOODPROTEIN(FOOD *v,float x);
extern float setFOODAMOUNTINGRAMS(FOOD *v,float x);
extern char *setFOODGRAMS(FOOD *v,char *x);
extern float setFOODAMOUNTPER(FOOD *v,float x);
extern char *setFOODUNIT(FOOD *v,char *x);

extern void displayFOOD(void *v,FILE *fp);
extern int compareFOOD(void *v,void *w);
extern void freeFOOD(void *v);

#endif
