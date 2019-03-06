#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "scanner.h"
#include "rbt.h"
#include "gst.h"
#include "tnode.h"
#include "string.h"

char *cleaner(char *TBC){
	if(TBC==NULL)
		return NULL;
	else if(strcmp(TBC,"")==0){
		free(TBC);
		return "";
	}
	assert(TBC!=0);
	char *cleaned = calloc(256,sizeof(char));
	int i = 0;
	int j = 0;
	int z = 0;
	char ch = TBC[0];
	while(isalnum(ch) == 0 && i < (int)strlen(TBC)){
		i++;
		ch = TBC[i];
	}
	while(ch != '\0'){
		if(ch >= 'a' && ch <= 'z'){
			cleaned[j] = ch;
			i++;
			j++;
			z = 0;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			cleaned[j] = (ch + 32);
			i++;
			j++;
			z = 0;
		}
		else if(ch == ' ' && z == 0){
			cleaned[j] = ch;
			i++;
			j++;
			z = 1;
		}
		else
			i++;
		ch = TBC[i];
	}
	if(cleaned == NULL){
		free(TBC);
		return NULL;
	}
	cleaned[j+1] = '\0';
	i = 0;
	char temp = '\0';
/*
	int exists = 0;
	while(i < (int)strlen(cleaned)){
		if((cleaned[i]) >= 'a' && cleaned[i] <= 'z'){
			exists = 1;
		}	
		i++;
	}
	i=0;
	if(exists == 0){
		free(TBC);
		cleaned = "";
		cleaned[0] = '\0';
		return cleaned;
	} */
	int q = 0;
	while(isspace(cleaned[0]) && q < (int)strlen(cleaned)){
		while(i < (int)strlen(cleaned) - 1){
			temp = cleaned[i];
			cleaned[i] = cleaned[i+1];
			cleaned[i+1] = temp;
			i++;
		}
		 q++;
	}
	i = strlen(cleaned)-1;
	if(i < 0){
		free(TBC);
		return cleaned;
	}
	ch=cleaned[i];
	while(isspace(ch) && i >= 0){
		cleaned[i]='\0';
		i--;
		if(i != -1)
			ch=cleaned[i];
	}
	free(TBC);
	return cleaned;
}

void RBTHelper(char *corpus, char *commands, RBT *t){
	FILE *fp = NULL;
	fp = fopen(corpus, "r");
	char *ch = "1";
	char c = ' ';
	STRING *string = NULL;
	int z = 0;
	while(!feof(fp)){
		if(stringPending(fp) == 1){
			ch = readString(fp);
		}
		else{
			ch = readToken(fp);
		}
		ch = cleaner(ch);
		if(ch!= NULL && strlen(ch) > 0){
			string = newSTRING(ch);
			insertRBT(t,string);
		}
		else if(ch != NULL)
				free(ch);
	}
	fclose(fp);
	ch = "1";
	fp = fopen(commands, "r");
	c = readChar(fp);
	while(!feof(fp)){
		if(c == 'd' || c == 'i' || c == 'f'){
			if(stringPending(fp) == 1){
				ch = readString(fp);
			}
			else
				ch = readToken(fp);
			ch = cleaner(ch);
			if(c == 'i'){
				if(strlen(ch) > 0){
					string = newSTRING(ch);
					insertRBT(t,string);
				}
				else
					free(ch);
			}
			if(c == 'd'){
				if(strlen(ch) > 0){
					string = newSTRING(ch);
					if(string != NULL){	
						z = deleteRBT(t,string);
					}
					else{
						z = -1;
					}
					if(z == -1){
						printf("Value ");
						printf("%s",ch);
						printf(" not found.\n");
					}
					if(string != NULL)
						freeSTRING(string);
					free(ch);
				}
				else
					free(ch);
			}
			if(c == 'f'){
				if(strlen(ch) > 0){
					string = newSTRING(ch);
					freqRBT(t,string);
					freeSTRING(string);
					free(ch);
				}
				else
					free(ch);
			}
		}
		if(c == 's')
			displayRBT(t,stdout);
		if(c == 'r')
			statisticsRBT(t,stdout);
		c = getc(fp);
	}
	fclose(fp);
	return;
}

void GSTHelper(char *corpus, char *commands, GST *t){
	FILE *fp = NULL;
	fp = fopen(corpus, "r");
	char *ch = "1";
	char c = ' ';
	STRING *string = NULL;
	int z = 0;
	while(!feof(fp)){
		if(stringPending(fp) == 1){
			ch = readString(fp);
		}
		else{
			ch = readToken(fp);
		}
		ch = cleaner(ch);
		if(ch!= NULL && strlen(ch) > 0){
			string = newSTRING(ch);
			insertGST(t,string);
		}
		else{
			if(ch != NULL)
				free(ch);
		}
	}
	fclose(fp);
	ch = "1";
	fp = fopen(commands, "r");
	c = readChar(fp);
	while(!feof(fp)){
		if(c == 'd' || c == 'i' || c == 'f'){
			if(stringPending(fp) == 1){
				ch = readString(fp);
			}
			else
				ch = readToken(fp);
			ch = cleaner(ch);
			if(c == 'i'){
				if(strlen(ch) > 0){
					string = newSTRING(ch);
					insertGST(t,string);
				}
				else
					free(ch);
			}
			if(c == 'd'){
				if(strlen(ch) > 0){
					string = newSTRING(ch);
					if(string != NULL){
						z = deleteGST(t,string);
					}
					else{
						z = -1;
					}
					if(z == -1){
						printf("Value ");
						printf("%s",ch);
						printf(" not found.\n");
					}
					if(string != NULL)
						freeSTRING(string);
					free(ch);
				}
				else
					free(ch);
			}
			if(c == 'f'){
				if(strlen(ch) > 0){
					string = newSTRING(ch);
					freqGST(t,string);
					freeSTRING(string);
					free(ch);
				}
				else
					free(ch);
			}
		}
		if(c == 's')
			displayGST(t,stdout);
		if(c == 'r')
			statisticsGST(t,stdout);
		c = getc(fp);
	}
	fclose(fp);
	return;
}
void freeRBThelper(void *v){
	char *test = getSTRING((STRING *)v);
	freeSTRING((STRING *)v);
	free(test);
	return;
}
void freeGSThelper(void *v){
	char *test = getSTRING((STRING *)v);
	freeSTRING((STRING *)v);
	free(test);
	return;
}

int main(int argc, char **argv){
	if(argc == 1){
		printf("No arguments given, EXITING PROGRAM");
		return 0;
	}
	char treeChoice = 'r';
	char *corpus = NULL;
	char *commands = NULL;
	RBT *tree = NULL;
	GST *t = NULL;
	if(argv[1][0] == '-' && argv[1][1] == 'g'){
		treeChoice = 'g';
	}
	else if(argv[1][0] == '-' && argv[1][1] == 'r'){
		treeChoice = 'r';
	}
	else if(argv[1][0] == '-' && argv[1][1] == 'v'){
		printf("Written by Alex Leak\n");
		return -1;
	}
	else
		treeChoice = 'r';
	if(argv[1][0] != '-'){
	corpus = argv[1];
	commands = argv[2];
	}
	else{
		corpus = argv[2];
		commands = argv[3];
	}

	if(corpus!=NULL && commands!=NULL){
		if(treeChoice == 'g'){
			t = newGST(compareSTRING);
			setGSTdisplay(t,displaySTRING);
			setGSTfree(t,freeGSThelper);
			GSTHelper(corpus, commands, t);
			freeGST(t);
		}
		else{
			tree = newRBT(compareSTRING);
			setRBTdisplay(tree,displaySTRING);
			setRBTfree(tree,freeRBThelper);
			RBTHelper(corpus, commands, tree);
			freeRBT(tree);
		}
	}
	else{
		printf("EMPTY\n");
	}
	return 0;
}
