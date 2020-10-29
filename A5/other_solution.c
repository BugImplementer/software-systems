#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//macros for different options
#define ADDACC "-a"
#define WITHDRAW "-w"
#define DEPOSIT "-d"
#define FILENAME "bankdata.csv"


//structure for a bank account
typedef struct account{
    char accnum[20];
    char name[50];
    double bal;
    struct account* next; //contains pointer for next account
}Account;


//find account
//this function returns pointer to the structure of an account with given account number
Account* findAccount(Account* root , char *accnum){
    Account *temp = root;
    while(temp != NULL){
        if(strcmp(temp->accnum , accnum) == 0)
            return temp;
        //check next account
        temp = temp->next;
    }
    //else not found return null
    return NULL;
}

//function to add a node to the account list
Account* addNode(Account* root , Account* node){
    if(root == NULL){
        return node;
    }
    else{
        root->next = addNode(root->next , node);
        return root;
    }
}

Account* createAccount(Account* root, char* ac_num , char* acc_name){
    Account* acc = malloc(sizeof(Account)); //new acc
    strcpy(acc->accnum , ac_num);
    strcpy(acc->name , acc_name);
    acc->bal = 0;
    acc->next = NULL;
    return addNode(root , acc); //add new acc to root
}

void updateBalance(Account* root , char* ac_num , char* amount){
    Account* acc = findAccount(root , ac_num);
    if(acc == NULL){
        fprintf(stderr, "Error ! Corrupted data file\n");
        exit(1); //data file corrupted
    }
    //update balance
    double am = strtod(amount, NULL);
    acc->bal += am;
    if(acc->bal < 0){
        fprintf(stderr, "Error ! Corrupted data file\n");
        exit(1); //data file corrupted
    }
}

Account* readData(FILE* fp){
    //function to read data from file
    //first getting first two characters
    Account* root = NULL;
    char buffer[200]; //buffer
    while(fgets(buffer, 200 , fp)){
        //remove last new line
        if(buffer[strlen(buffer) - 1] == '\n'){
            buffer[strlen(buffer) - 1] = '\0';
        }
        //now split with respect to comma
        char* type = strtok(buffer , ",");
        char* ac_num;
        char* ac_name;
        char* amount;
        char* date;
        //
        if(type != NULL){
            if(strcmp(type , "AC") == 0){
                //get acc number and name
                ac_num = strtok(NULL , ",");
                ac_name = strtok(NULL , ",");
                if(!ac_num || !ac_name){
                    fprintf(stderr, "Error ! Corrupted data file\n");
                    exit(1); //data file corrupted
                }
                root = createAccount(root , ac_num , ac_name);
            }
            else if(strcmp(type , "TX") == 0){
                //get acc number, date and amount
                ac_num = strtok(NULL , ",");
                date = strtok(NULL , ",");
                amount = strtok(NULL , ",");
                if(!ac_num || !date || !amount){
                    fprintf(stderr, "Error ! Corrupted data file\n");
                    exit(1); //data file corrupted
                }
                //update balace
                updateBalance(root , ac_num , amount);
            }
            else{
                //corrupted data file
                fprintf(stderr, "Error ! Corrupted data file\n");
                exit(1);
            }

        }
    }
    return root;
}

void addAccount(FILE* fp, Account* root , char* num , char* name){
    if(findAccount(root, num) != NULL){
        //account exists
        fprintf(stderr, "Error, account number %s already exists\n", num);
        exit(50);
    }
    //else add account
    fprintf(fp , "AC,%s,%s\n",num, name);
}

void deposit(FILE* fp, Account* root , char* num , char* date , char* amount){
    if(findAccount(root , num ) == NULL){
        //account not found
        fprintf(stderr , "Error, account number %s does not exists\n", num);
        exit(50);
    }
    fprintf(fp , "TX,%s,%s,%s\n",num, date , amount);
}

void withdraw(FILE* fp, Account* root , char* num , char* date , char* amount){
    Account* acc;
    if((acc = findAccount(root , num )) == NULL){
        //account not found
        fprintf(stderr , "Error, account number %s does not exists\n", num);
        exit(50);
    }
    double am = strtod(amount , NULL);
    if(am > acc->bal){
        fprintf(stderr , "Error, account number %s has only %.2lf\n", num , acc->bal);
        exit(60);
    }
    fprintf(fp , "TX,%s,%s,-%s\n",num, date , amount);
}

int main(int argc , char* argv[]){
    //first check that the number of arguments is atleast 2
    int use; //depicts the function to perform
    if(argc < 2){
        //throw error
        fprintf(stderr, "Error, incorrect usage! \n-a ACCTNUM NAME\n-d ACCTNUM DATE AMOUNT\n-w ACCTNUM DATE AMOUNT\n");
        //exit code
        exit(1);
    }
    //now check individual errors
    if(strcmp(argv[1], ADDACC) == 0){
        //add command
        //number of commands should be less that 4
        if(argc < 4){
            fprintf(stderr , "Error, incorrect usage! -a ACCTNUM NAME\n");
            exit(1);
        }
        use = 1;
    }
    else if(strcmp(argv[1], DEPOSIT) == 0){
        //add command
        //number of commands should be less that 5
        if(argc < 5){
            fprintf(stderr , "Error, incorrect usage! -d ACCTNUM DATE AMOUNT\n");
            exit(1);
        }
        use = 2;
    }
    else if(strcmp(argv[1], WITHDRAW) == 0){
        //add command
        //number of commands should be less that 5
        if(argc < 5){
            fprintf(stderr , "Error, incorrect usage! -w ACCTNUM DATE AMOUNT\n");
            exit(1);
        }
        use = 3;
    }
    else{
        //invalid option
        fprintf(stderr, "Error, incorrect usage! \n-a ACCTNUM NAME\n-d ACCTNUM DATE AMOUNT\n-w ACCTNUM DATE AMOUNT\n");
        //exit code
        exit(1);
    }

    //now try to open file
    FILE* fp = fopen(FILENAME , "r");
    if(fp == NULL){
        //file does not exit
        fprintf(stderr , "Error, unable to locate the data file bankdata.csv\n");
        exit(100);
    }

    //read data
    Account* root = readData(fp);
    //close file
    fclose(fp);
    //open file for appending
    fp = fopen(FILENAME , "a");

//to the screen
    switch(use){
        case 1:
            addAccount(fp , root , argv[2], argv[3]);
            break;
        case 2:
            //deposit
            deposit(fp , root , argv[2], argv[3], argv[4]);
            break;
        case 3:
            withdraw(fp , root , argv[2], argv[3], argv[4]);
            break;
    }
    fclose(fp);
    return 0;
}