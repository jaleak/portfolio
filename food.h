#ifndef __FOOD_INCLUDED__
#define __FOOD_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <string.h>

typedef struct FOOD FOOD;

extern FOOD * newFOOD(char *x);
extern char *getFOOD(FOOD *v);
extern char *setFOOD(FOOD *v,char *x);
extern void displayFOOD(void *v,FILE *fp);
extern int compareFOOD(void *v,void *w);
extern void freeFOOD(void *v):

#endif
