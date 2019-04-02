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
	printf("Stats \"name of log\" \t \t \t displays stats about the log red black tree\n");
	printf("Display \"name of log\" \t \t \t displays the entire log\n");
	printf("Search \"search\" \"name of log\" \t \t searches for food by name/company\n");
	printf("Add \"name\" \"name of log\" \t \t adds food by name into log\n");
	printf("Delete \"name\" \"name of log\" \t \t deletes food by name in log\n");
	printf("Quit \t \t \t \t \t quits the program\n");
	printf("Exit \t \t \t \t \t quits the program\n");
}

FOOD *search(RBT *tree,char *foodSearch){
	if(tree == NULL)
		return NULL;
	TNODE *y = getRBTroot(tree);
	while(y!= NULL){
		FOOD *x = unwrapRBT(y);
		if(strcmp(getFOODNAME(x),foodSearch) == 0)
			return x;
		else if(strcmp(getFOODNAME(x),foodSearch) < 0)
			y = getTNODEright(y);
		else
			y = getTNODEleft(y);
	}
	return NULL;
}
void saveDisplayHelper(void *v,FILE *fp){
	fprintf(fp,"0~");
	fprintf(fp,"%s~",getFOODNAME((FOOD *) v));
	fprintf(fp,"%s~",getFOODCOMPANY((FOOD *) v));
	fprintf(fp,"%.2f~",getFOODCALORIES((FOOD *) v));
	fprintf(fp,"%.2f~",getFOODCARBS((FOOD *) v));
	fprintf(fp,"%.2f~",getFOODFAT((FOOD *) v));
	fprintf(fp,"%.2f~",getFOODPROTEIN((FOOD *) v));
	fprintf(fp,"%.2f~",getFOODAMOUNTINGRAMS((FOOD *) v));
	fprintf(fp,"%s~",getFOODGRAMS((FOOD *) v));
	fprintf(fp,"%.2f~",getFOODAMOUNTPER((FOOD *) v));
	fprintf(fp,"%s\n",getFOODUNIT((FOOD *) v));
}
void copyFood(FOOD *dest, FOOD *y){
	setFOODNAME(dest,getFOODNAME(y));
	setFOODCOMPANY(dest,getFOODCOMPANY(y));
	setFOODCALORIES(dest,getFOODCALORIES(y));
	setFOODCARBS(dest,getFOODCALORIES(y));
	setFOODFAT(dest,getFOODFAT(y));
	setFOODPROTEIN(dest,getFOODFAT(y));
	setFOODAMOUNTINGRAMS(dest,getFOODAMOUNTINGRAMS(y));
	setFOODGRAMS(dest,getFOODGRAMS(y));
	setFOODAMOUNTPER(dest,getFOODAMOUNTPER(y));
	setFOODUNIT(dest,getFOODUNIT(y));
}

void saveRBTfile(char *nameOfLog, RBT *tree){
	//change display to "saveDisplayHelper"
	setRBTdisplay(tree,saveDisplayHelper);
//	displayRBT(tree,stdout);
	//open file for writing
	FILE *fp = NULL;
	if(strlen(nameOfLog) == 0 || nameOfLog == NULL){
		return;
	}
	//print into file
	fp = fopen(nameOfLog,"w");
	displayRBT(tree,fp);
	fclose(fp);	
	//close file
//	setRBTdisplay(tree,displayFOOD);
	//change display back to original value
	return;
}

void foodHelper(RBT *t,char *fileName){
//	printf("Creating Red Black Tree of Data File, may take some time... \n");
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
	debugRBT(data,4);
	printf("Creating Red-Black Tree of data file. May take some time...\n");
	foodHelper(data,dataFile);
	//data rbt created at this point
	int i = 0;
	char *command = calloc(256,sizeof(char));
	char *nameInput = calloc(256,sizeof(char));
	char *name = calloc(256,sizeof(char));
	int commandNums = 0;
	helpMessage();
	char *logTemp = calloc(256,sizeof(char));
	char *currentLog = calloc(256,sizeof(char));
	//char *dataLog =  "data.log";
	//dataLog = dataFile;
	RBT *currentRBT = newRBT(compareFOOD);
	setRBTdisplay(currentRBT,saveDisplayHelper);
	setRBTfree(currentRBT,freeRBThelper);
	debugRBT(currentRBT,4);
	FILE *fp = NULL;
	while(strcmp(command,"exit") != 0 && strcmp(command,"quit") != 0){
		printf("Enter a command:\n");
		scanf("%s",command);
		for(i=0;(unsigned)i < strlen(command);i++){
			command[i] = tolower(command[i]);
		}
		//display Help Message
		//DONE
		if(strcmp(command,"help")==0){
			helpMessage();
		}
		//create "name of log"
		//done
		else if(strcmp(command,"create") == 0){
			scanf("%s",logTemp);
			saveRBTfile(currentLog,currentRBT);
			strcpy(currentLog,logTemp);
			freeRBT(currentRBT);
			currentRBT = newRBT(compareFOOD);
			setRBTdisplay(currentRBT,saveDisplayHelper);
			setRBTfree(currentRBT,freeFOOD);
			debugRBT(currentRBT,4);
			fp = fopen(currentLog,"w");
			foodHelper(currentRBT,currentLog);
			fclose(fp);
		}
		//display "name of log"
		//should be done
		else if(strcmp(command,"display") == 0){
			scanf("%s",logTemp);
			saveRBTfile(currentLog,currentRBT);
			strcpy(currentLog,logTemp);
			freeRBT(currentRBT);
			currentRBT = newRBT(compareFOOD);
			setRBTdisplay(currentRBT,saveDisplayHelper);
			setRBTfree(currentRBT,freeFOOD);
			debugRBT(currentRBT,4);
			foodHelper(currentRBT,currentLog);
			displayRBT(currentRBT,stdout);
		/*	if(strcmp(logTemp,dataLog) == 0){
				displayRBT(data,stdout);	
			}
			else{
				saveRBTfile(currentLog,currentRBT);
				strcpy(currentLog,logTemp);
				freeRBT(currentRBT);
				currentRBT = newRBT(
				foodHelper(currentRBT,currentLog);
				displayRBT(currentRBT,stdout);
			}
		}*/
		}
		//search "search" "name of log"
		//can be done
		else if(strcmp(command,"search") == 0){
			char *name = readString(stdin);	
			FOOD *returnFood = NULL;
			scanf("%s",logTemp);
			saveRBTfile(currentLog,currentRBT);
			strcpy(currentLog,logTemp);
			freeRBT(currentRBT);
			currentRBT = newRBT(compareFOOD);
			setRBTdisplay(currentRBT,saveDisplayHelper);
			setRBTfree(currentRBT,freeFOOD);
			debugRBT(currentRBT,4);
			foodHelper(currentRBT,currentLog);
			returnFood = search(data,name);
			displayFOOD(returnFood,stdout);
		}
		//add "name" "name of log"
		else if(strcmp(command,"add") == 0){
			FOOD *addFood = NULL;
			FOOD *newFood = NULL;
			char *name = readString(stdin);
			scanf("%s",logTemp);
			saveRBTfile(currentLog,currentRBT);
			strcpy(currentLog,logTemp);
			freeRBT(currentRBT);
			currentRBT = newRBT(compareFOOD);
			setRBTdisplay(currentRBT,saveDisplayHelper);
			setRBTfree(currentRBT,freeFOOD);
			debugRBT(currentRBT,4);
			foodHelper(currentRBT,currentLog);
			addFood = search(data,name);
			newFood = newFOOD("","",0,0,0,0,0,"",0,"");
			copyFood(newFood,addFood);
			insertRBT(currentRBT,newFood);
		}
		//delete "name" "name of log"
		else if(strcmp(command,"delete") == 0){
			FOOD *delFood = NULL;
			FOOD *newFood = NULL;
			char *name = readString(stdin);
			scanf("%s",logTemp);
			saveRBTfile(currentLog,currentRBT);
			strcpy(currentLog,logTemp);
			freeRBT(currentRBT);
			currentRBT = newRBT(compareFOOD);
			setRBTdisplay(currentRBT,saveDisplayHelper);
			setRBTfree(currentRBT,freeFOOD);
			debugRBT(currentRBT,4);
			foodHelper(currentRBT,currentLog);
			delFood = search(data,name);
			newFood = newFOOD("","",0,0,0,0,0,"",0,"");
			copyFood(newFood,delFood);
			deleteRBT(currentRBT,newFood); 
			//call delete function(foodName,nameOfLog,dataLog)
		}
		//stats "name of log"
		//DONE
		else if(strcmp(command,"stats") == 0){
			scanf("%s",logTemp);
			saveRBTfile(currentLog,currentRBT);
			strcpy(currentLog,logTemp);
			freeRBT(currentRBT);
			currentRBT = newRBT(compareFOOD);
			setRBTdisplay(currentRBT,saveDisplayHelper);
			setRBTfree(currentRBT,freeFOOD);
			debugRBT(currentRBT,4);
			foodHelper(currentRBT,currentLog);
			statisticsRBT(currentRBT,stdout);
	//		statisticsRBT(command,stdout);
		}
		//DONE
		else if(strcmp(command,"exit") == 0 || strcmp(command,"quit") == 0){
			
		}
		else{
			if(commandNums == 0){
				printf("Please enter a valid command. If you need help, type \"help\" or \"exit\" to exit the program\n");
			}
			commandNums = 0;
		}	
	/*	saveRBTfile(currentLog,currentRBT);
		while(getRBTroot(currentRBT) != NULL){
			deleteRBT(currentRBT,unwrapRBT(getRBTroot(currentRBT)));
		}
		foodHelper(currentRBT,currentLog);
	*/
	}
	freeRBT(currentRBT);
	if(nameInput != NULL)
		free(nameInput);
	if(logTemp != NULL)
		free(logTemp);
	if(command != NULL)
		free(command);
	if(data != NULL)
		freeRBT(data);
	free(currentLog);
	free(name);
//	saveRBTfile(currentLog,currentRBT);
//	strcpy(currentLog,logTemp);
//	freeRBT(currentRBT);
//	free(command);
//	if(logTemp != NULL){
//		free(logTemp);
//	}
//	if(nameInput != NULL){
//		free(nameInput);
//	}
//	foodHelper(currentRBT,currentLog);
//	free(currentLog);
//	freeRBT(data);
	return 0;
}
