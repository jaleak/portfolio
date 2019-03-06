#ifndef __STRING_INCLUDED__
#define __STRING_INCLUDED__

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <string.h>

typedef struct STRING STRING;

 extern STRING * newSTRING(char *x);
 extern char * getSTRING(STRING *v);
 extern char * setSTRING(STRING *v,char *x);
 extern void displaySTRING(void *v,FILE *fp);
 extern int compareSTRING(void *v,void *w);
 extern void freeSTRING(void *v);

#endif
