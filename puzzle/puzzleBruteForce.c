#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int bool;
#define true 1
#define false 0
#define MAXSIZE 900000

// function declaration
int isExist(char*,char);
bool isDigitExist(int, int);
void print(int[],int);
void solve(char*, char*, char*);
void assignString(char*,int[]);
bool assign(int[],int,int[],int*,int);
bool allNine(int[],int);
int arrayToNumber(int [],int);
void check(char*,char*,char*, int[], int[]);
void numberToArray(int[],int);
int numberOfDigits(int);
void validate(char*,char*,char*,int[],int[]);
bool checkStringAssignment(char*,int[]);
bool checkFinalString(char*,int[]);
int getDigit(int,int);
int totalNumberOfMatchingCharacter(char*);
int totalNumberOfMatchingNumbers(int);

//main
static int totalRes;
static int totalValues;
int main(){
    char *str1=(char*)malloc(10*sizeof(char));
    char *str2=(char*)malloc(10*sizeof(char));
    char *res =(char*)malloc(10*sizeof(char));
    printf("String 1: ");
    scanf("%s",str1);
    printf("String 2: ");
    scanf("%s",str2);
    printf("String 3: ");
    scanf("%s",res);

    totalRes = 0;
    solve(str1,str2,res);
    printf("\ntotalRes: %d\n",totalRes);
  return 0;
}

void solve(char* str1, char *str2, char *str){
  int len1 = strlen(str1);
  int len2 = strlen(str2);
  int len3 = strlen(str);
  int sol1[MAXSIZE],sol2[MAXSIZE],sol3[len3+1];
  int r=0,temp=-1,l=1,per,num1,num2;
  printf("%s + %s = %s\n",str1,str2,str);
  if(len1 == len2){
    /*assigning numbers to 1st string*/
    assignString(str1,sol1);
    /*assigning numbers to 2nd string*/
    assignString(str2,sol2);
    /*Check for solution*/
    check(str1, str2, str, sol1, sol2);
  }else{
      printf("\nboth strings are of different length.\n\n");
      exit(1);
  }
}

void assignString(char *str,int sol[]){
    int i=0,j=0,k=0,l=0,temp,index;
    int len = strlen(str);
    int sol1[len], tempIndex;
    int flag;
    for (i=1; i<2; i++) {
        sol1[0]=i;
        for(j=i;j<len;j++){
            sol1[j]=0;
        }
        for (index=len-1; index>0; index--) {
            flag = assign(sol1,index,sol,&l,len);
            temp = sol[l-1];
            tempIndex=strlen(str);
            while(tempIndex>0){
                while (temp%10 == 9){
                    tempIndex--;
                    temp = temp/10;
                }
                if(tempIndex == 0){
                    return;
                }
                numberToArray(sol1, sol[l-1]);
                sol1[tempIndex] = 0;
                sol1[tempIndex-1] = sol1[tempIndex-1]+1;
                flag = assign(sol1,tempIndex,sol,&l,len);
                if (flag) {
//                    printf("\nl:%d\n",l);
//                    print(sol,l);
                    totalValues = l;
                    return;
                }
            }
        }
    }
}

bool assign(int num[],int index,int sol[],int *l,int len){
    int temp=0,k=0,i;
    for (i=0; i<10; i++) {
        num[index] = i;
        sol[(*l)++] = arrayToNumber(num,len);
        if(allNine(num,len)){
            return true;
        }
    }
    return false;
}

bool allNine(int ar[],int len){
    int i;
    for (i=0; i<len; i++) {
        if(ar[i] != 9)
            return false;
    }
    return true;
}

void print(int ar[], int size){
    int i;
    for(i=0;i<size;i++){
        fprintf(stdout,"%d ",ar[i]);
        if(i!=0 && (i+1)%10==0)
            fprintf(stdout,"\n");
    }
    fprintf(stdout,"\n");
}

int isExist(char *str, char ch){
    int i=0,index=-1;
    while(str[i]){
        if(str[i] == ch)
            return i;
        i++;
    }
    return index;
}

bool isDigitExist(int num, int digit){
    while(num){
        if(num%10 == digit)
            return true;
        num = num/10;
    }
    return false;
}

int arrayToNumber(int ar[],int size){
    int num=0,i=0;
    while(size != i)
        num = num*10+ar[i++];
    return num;
}


void numberToArray(int ar[], int num){
    int i=0;
    int digits = numberOfDigits(num);
    while(num){
        ar[digits-i-1] = num%10;
        num = num/10;
        i++;
    }
}

void check(char* str1, char* str2, char *str, int sol1[], int sol2[]){
    int ar1[strlen(str1)], ar2[strlen(str2)];
    int i,j,k,p;
    bool flag = true;
    int tempIndex = -1;
    
    for (i=0; i<totalValues; i++) {
        numberToArray(ar1,sol1[i]);
        if(checkStringAssignment(str1, ar1)){
            for (j=0; j<totalValues; j++) {
                numberToArray(ar2,sol2[j]);
                if(checkStringAssignment(str2, ar2)){
                    flag = true;
                    //cross validation
                    for (k=0; k<strlen(str1); k++) {
                        tempIndex = isExist(str1, str2[k]);
                        if (tempIndex != -1) {
                            if(ar1[tempIndex]!= ar2[k]){
                                flag = false;
                            }
                        }else{
                            for (p=0; p<strlen(str1); p++) {
                                if(ar1[p] == ar2[k]){
                                    flag = false;
                                }
                            }
                        }
                    }
                    if (flag) {
                        //check for resulting string
//                        printf("validating\n");
                        validate(str1, str2, str, ar1, ar2);
                    }
                }
            }
        }
    }
}



int numberOfDigits(int num){
    int i=0;
    while(num){
        num = num/10;
        i++;
    }
    return i;
}

bool checkStringAssignment(char *str, int ar[]){
    bool flag = true;
    int i;
    for (i=0; i<strlen(str); i++) {
        if(isExist(str,str[i]) != i){
            if(ar[i] != ar[isExist(str,str[i])]){
                flag = false;
            }
        }else{
            for(int k=0;k<i;k++){
                if(ar[i] == ar[k]){
                    flag = false;
                }
            }
        }
    }
    return flag;
}


void validate(char *str1, char *str2, char *str,int ar1[],int ar2[]){
    
    int num1 = arrayToNumber(ar1, strlen(str1));
    int num2 = arrayToNumber(ar2, strlen(str2));
    int res = num1 + num2;
    int ar[strlen(str)];
    int index1, index2;
    int p;
//    printf("%d + %d = %d\n",num1,num2,res);
    if(numberOfDigits(res) == strlen(str)){
    numberToArray(ar, res);
        if(checkFinalString(str, ar)){
            for(int i=0;i<strlen(str);i++){
                index1 = isExist(str1,str[i]);
                index2 = isExist(str2,str[i]);
//        printf("str1: %s str2: %s ch: %c\n",str1, str2, str[i]);
//        printf("index1: %d index2: %d index: %d\n",index1, index2, index);
                if (index1!=-1) {
                    if (ar1[index1] != ar[i]) {
                        return;
                    }
                }
                else{
                    for (p=0; p<strlen(str1); p++) {
                        if (ar1[p] == ar[i]) {
                            return;
                        }
                    }
                }
                if (index2!=-1) {
                    if (ar2[index1] != ar[i]) {
                        return;
                    }
                }
                else{
                    for (p=0; p<strlen(str2); p++) {
                        if (ar2[p] == ar[i]) {
                            return;
                        }
                    }
                }
            }
            totalRes++;
            printf("%d + %d = %d \t",num1,num2, res);
            if (totalRes%2==0) {
                printf("\n");
            }
        }
    }
}


bool checkFinalString(char *str,int ar[]){
    bool flag = true;
    int index=-1, i;
    if (totalNumberOfMatchingCharacter(str) == totalNumberOfMatchingNumbers(arrayToNumber(ar, strlen(str))) ) {
        flag = true;
        for (i=0; i<strlen(str); i++) {
            index = isExist(str, str[i]);
            if (index != i) {
                if (ar[i] != ar[index]) {
                    flag = false;
                }
            }
        }
        
    }
    else{
        flag = false;
    }
    return flag;
}


int totalNumberOfMatchingCharacter(char* str1){
    int i=0,res=0,j=0;
    while(str1[i]){
        j=0;
        while (str1[j]) {
            if (str1[i]==str1[j] && i!=j) {
                res++;
            }
            j++;
        }
        i++;
    }
    return res;
}


int totalNumberOfMatchingNumbers(int num){
    int len = numberOfDigits(num);
    int i=0,j=0,res=0;
    while(i<len){
        j=0;
        while (j<len) {
            if(getDigit(num,i) == getDigit(num,j) && i!=j){
                res++;
            }
            j++;
        }
        i++;
    }
    return res;
}


int getDigit(int num,int index){
    index=numberOfDigits(num)-index-1;
    while (index-->0) {
        num=num/10;
    }
    return num%10;
}
