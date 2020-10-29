#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 Program to implement a simple banking application
 **********************************************************
 * Author      Dept.          Date         Notes
 **********************************************************
 * Xinyi Zhu   Comp.Science   Mar 06 2020  Initial version.
 * Xinyi Zhu   Comp.Science   Mar 07 2020  Added error handling.
 * Xinyi Zhu   Comp.Science   Mar 30 2020  Final version.

*/


//open an account
void create(char* num, char* name, FILE* file) {
	char tmp[100];
	char* p;
	int flag=0;
	
	//search for the account number
	while(fgets(tmp,100,file)) {
                p = strstr(tmp,num);
                if (p)  flag=1;
        }
		
	if(flag==1) {
		fprintf(stderr, "Error, account number %s already exists\n", num);
		exit(50);
	} else {
		fprintf(file,"AC,%s,%s\n",num,name);
	}
}

void deposit(char* num, char* date, char* amount, FILE* file) {
	char tmp[100];
	char* p;
	int flag=0;
	
	//search for the account number
	while(fgets(tmp,100,file)) {
                p = strstr(tmp,num);
                if (p)  flag=1;
        }
		
	if(flag==0) {
		fprintf(stderr, "Error, account number %s does not exists\n", num);
		exit(50);
	} else {
		fprintf(file,"TX,%s,%s,%s\n",num,date,amount);  //write to file
	}
}


//helper function
//calculate the balance for a specific account
double balance(char* num, FILE* file) {
    char line[1000];
    file = fopen("bankdata.csv", "r");            
    double bal = 0.00;

    while (fgets(line, 1000, file))
    {
        char *token = strtok(line, ",");   //first token
        if (strcmp(token, "TX") == 0)
        {
            char *acctnum = strtok(NULL, ",");   //next token
            if (strcmp(acctnum, num) == 0)  //check if the account number matches
            {
                char *date = strtok(NULL, ",");    
                char *amount = strtok(NULL, ",");  
                double am = atof(amount);   
                bal += am;
                //printf("%s: %s: %9.2f %9.2f\n", acctnum, date, am, bal); 
            }
        }   
    }
    fclose(file);
    return bal;
}

void withdraw(char* num, char* date, char* amount, FILE* file) {
	char tmp[100];
	char* p;
	int flag=0;
	
	//search for the account number
	while(fgets(tmp,100,file)) {
        p = strstr(tmp,num);
        if (p)  flag=1;
        }
	
	if(flag==0) {
        fprintf(stderr, "Error, account number %s does not exists\n", num);
        exit(50);
        } 
	
	float bal = balance(num, file);  //get balance
	if(bal < atof(amount)) {
		fprintf(stderr, "Error, account number %s has only %.2f\n", num, bal);
		exit(60);
	}
		
	else {
		fprintf(file,"TX,%s,%s,-%s\n",num,date,amount);
	}
	
}

int main(int argc, char* argv[]) {
	//throw usage errors when the user passes invalid arguments
	if (argc == 1){
		fprintf(stderr, "Error, incorrect usage!\n-a ACCTNUM NAME\n-d ACCTNUM DATE AMOUNT\n-w ACCTNUM DATE AMOUNT\n");
		exit (1);
	}

	if ((strcmp(argv[1],"-a")==0) && (argc!=4)){
		fprintf(stderr, "Error, incorrect usage!\n-a ACCTNUM NAME\n");
		exit (1);
	}

	if ((strcmp(argv[1],"-d")==0 || strcmp(argv[1],"-w")==0) && (argc!=5)){
		fprintf(stderr, "Error, incorrect usage!\n%s ACCTNUM DATE AMOUNT\n", argv[1]);
		exit (1);
	}

	//check if the file exits in the current directory
	FILE *bank=fopen("bankdata.csv","r+");
	if (bank==NULL){
		fprintf(stderr, "Error, unable to locate the data file bankdata.csv\n");
		exit (100);
    }
	
	if (strcmp(argv[1],"-a")==0) create(argv[2], argv[3], bank);   //open account
	if (strcmp(argv[1],"-d")==0) deposit(argv[2], argv[3], argv[4], bank);  //deposit
	if (strcmp(argv[1],"-w")==0) withdraw(argv[2], argv[3], argv[4], bank);  //withdraw
	
	return 0;
		
}
