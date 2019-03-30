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
#include "food.h"
void helpMessage(){
	printf("Please input one of the following commands:\n");
	printf("Help \t \t \t \t \t displays help message\n");
	printf("Create \"name of log\" \t \t \t creates new log with desired name\n");
	printf("Display \"name of log\" \t \t \t displays the entire log\n");
	printf("Search \"search\" \"name of log\" \t \t searches for food by name/company\n");
	printf("Add \"name\" \"name of log\" \t \t adds food by name into log\n");
	printf("Delete \"name\" \"name of log\" \t \t deletes food by name in log\n");
	printf("Quit \t \t \t \t \t quits the program\n");
	printf("Exit \t \t \t \t \t quits the program\n");
}
void foodHelper(RBT *t,char *fileName){
	printf("Creating Red Black Tree of Data File, may take some time... \n");
	FILE *fp = NULL;
	fp = fopen(fileName,"r");
	char ch = '0';
	int i = 0;
	char *input = calloc(256,sizeof(char));
	int counter = 0;
	char *name = NULL;
	char *company = NULL;
	float calories = 0;
	float carbs = 0;
	float fat = 0;
	float protein = 0;
	float amtInGs = 0;
	char *grams = NULL;
	float amtPer = 0;
	char *unit = NULL;	
	FOOD *x = NULL;
	while(!feof(fp)){
		ch = fgetc(fp);	
	//	printf("%c",ch);
		if(ch != '~' && ch != '\n'){
			input[i] = ch;
			i++;
		}
		else{
			input[i] = '\0';
		//	printf("%s\n",input);
			i=0;
			if(counter == 0){
				counter++;
				x = newFOOD("","",0,0,0,0,0,"",0,"");
			}
			else if(counter == 1){
				counter++;
				name = calloc(strlen(input)+1,sizeof(char));
				strcpy(name,input);
				setFOODNAME(x,name);
			}
			else if(counter == 2){
				counter++; 
				company = calloc(strlen(input)+1,sizeof(char));
				strcpy(company,input);
				setFOODCOMPANY(x,company); 
			}
			else if(counter == 3){
				counter++;
				calories = atof(input);
				setFOODCALORIES(x,calories); 
			}
			else if(counter == 4){
				counter++;
				carbs = atof(input);
				setFOODCARBS(x,carbs);
			}
			else if(counter == 5){ 
				counter++;
				fat = atof(input);
				setFOODFAT(x,fat);
			}
			else if(counter == 6){
				counter++;
				protein = atof(input);
				setFOODPROTEIN(x,protein);
			}
			else if(counter == 7){
				counter++;
				amtInGs = atof(input);
				setFOODAMOUNTINGRAMS(x,amtInGs);
			}
			else if(counter == 8){ 
				counter++;
				grams = calloc(strlen(input)+1,sizeof(char));
				strcpy(grams,input);
				setFOODGRAMS(x,grams);
			}
			else if(counter == 9){ 
				counter++;
				amtPer = atof(input);
				setFOODAMOUNTPER(x,amtPer);
			}
			else if(counter == 10){
				counter = 0;
				unit = calloc(strlen(input)+1,sizeof(char));
				strcpy(unit,input);
				setFOODUNIT(x,unit);
			//	displayFOOD(x,stdout);
				insertRBT(t,x);
			}
		}
	}
	free(input);
	fclose(fp);	
}
void freeRBThelper(void *v){
	char *name = getFOODNAME((FOOD *)v);
	char *company = getFOODCOMPANY((FOOD *)v);
	char *grams = getFOODGRAMS((FOOD *)v);
	char *unit = getFOODUNIT((FOOD *)v);
	freeFOOD((FOOD *)v);
	if(name!=NULL)
		free(name);
	if(company!=NULL)
		free(company);
	if(grams!=NULL)
		free(grams);
	if(unit != NULL)
		free(unit);
	return;
}
int main(int argc, char **argv){
	if(argc == 1){
		printf("No arguments given, please enter a data file as an argument. EXITING PROGRAM");
		return 1;
	}
	char *dataFile = NULL;
	dataFile = argv[1];
	if(dataFile == NULL){
		printf("No data file. EXITING PROGRAM\n");
		return 1;
	}
	RBT *data = newRBT(compareFOOD);
	setRBTdisplay(data,displayFOOD);
	setRBTfree(data,freeRBThelper);
	foodHelper(data,dataFile);
	//rbt created at this point
	int i = 0;
	char *command = calloc(256,sizeof(char));
	helpMessage();
	while(strcmp(command,"exit") != 0 && strcmp(command,"quit") != 0){
		printf("Enter a command:\n");
		scanf("%s",command);
		for(i=0;(unsigned)i < strlen(command);i++){
			command[i] = tolower(command[i]);
		}
		if(strcmp(command,"help")==0){
			helpMessage();
		}
		else if(strcmp(command,"create") == 0){
			scanf("%s",command);
			if(strcmp(command,"") == 0){
				printf("please enter an argument\n");	
			}
		}
		else if(strcmp(command,"display") == 0){
				
		}
		else if(strcmp(command,"search") == 0){

		}
		else if(strcmp(command,"add") == 0){

		}
		else if(strcmp(command,"delete") == 0){

		}
		else if(strcmp(command,"exit") == 0 || strcmp(command,"quit") == 0){
			//im dumb
		}
		else{
			printf("Please enter a valid command. If you need help, type \"help\" or \"exit\" to exit the program\n");
		}	
	}
	free(command);
	freeRBT(data);
	return 0;
}
