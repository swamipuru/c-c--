#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int bool;
#define true 1
#define false 0

// function declaration
int isExist(char*,char);
bool isDigitExist(int, int);
void print(int[],int);
void solve(char*, char*, char*);
int assignFirst(char*,int[],int,int*);
int assignSecond(char*, char*,int[],int[],int,int*);
void check(char*,char*,char*,int[],int[]);
int numberOfDigits(int num);
bool differentDigits(int,int);
int getDigit(int,int);
int totalNumberOfMatchingCharacter(char*);
int arrayToNumber(int [],int);
int totalNumberOfMatchingNumbers(int);
bool containsDigit(int,int);
void applyPermutations(char*,char*,char*,int[],int[]);
void swap(int[],int,int);

//main
int main(){
  char *str1="SUMR";
  char *str2="SCHL";
  char *res ="COOL";
  solve(str1,str2,res);
}

void solve(char* str1, char *str2, char *str){
  int len1 = strlen(str1);
  int len2 = strlen(str2);
  int len3 = strlen(str);
  int sol1[len1],sol2[len2],sol3[len3+1];
  int r=0,temp=-1,l=1,per,num1,num2;
  printf("%s + %s = %s\n",str1,str2,str);
  printf("%d %d %d\n",len1,len2,len3);
  if(len1 == len2){
      l=0;
      while(l<1){
    /*assigning numbers to 1st string*/
//          r = l;
    r=assignFirst(str1,sol1,len1,&r);
    /*assigning numbers to 2nd string*/
    r=assignSecond(str1,str2,sol1,sol2,len2,&r);
//          printf("sol1: %d sol2: %d\n",arrayToNumber(sol1,len1),arrayToNumber(sol2,len2));
    /*check for solution*/
      check(str1,str2,str,sol1,sol2);
//      printf("matching charcters: %d\n",totalNumberOfMatchingCharacter(str1,str2));
          applyPermutations(str1, str2, str,sol1,sol2);
          l++;
      }
  }
//  num2 = arrayToNumber(sol2,len2);
//  printf("totalNumberOfMatchingNumbers: %d\n",totalNumberOfMatchingNumbers(num2));
//  applyPermutations(str1, str2, str,sol1,sol2);
}

void print(int ar[], int size){
  for(int i=0;i<size;i++)
    fprintf(stdout,"%d ",ar[i]);
  fprintf(stdout,"\n");
}

int isExist(char *str, char ch){
  int i=0,index=-1;
  while(str[i]){
    if(str[i] == ch)
      index=i;
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

int assignFirst(char *str1,int sol1[],int len1,int* r){
    int l=0,temp=-1;
    bool flag = false;
    if(*r == 0){
        sol1[l++]=1;
        flag = true;
    }
    while(l < len1){
        temp = isExist(str1, str1[l]);
        if(temp != -1 && temp == l){
            sol1[l]=*r;
            (*r)++;
        }
        else{
            sol1[l] = sol1[temp];
        }
//        printf("l: %d temp: %d sol[%d]: %d r: %d\n",l,temp,l,sol1[l],*r);
        if(flag){
            (*r)++;
            flag = false;
        }
        if(*r > 9){
            *r = 0;
        }
        l++;
    }
//    print(sol1,len1);
    return *r;
}

int  assignSecond(char *str1, char *str2,int sol1[],int sol2[],int len2,int* r){
    int l=0,temp=-1;
    //r = *digit;
    while(l<len2){
        temp=isExist(str1,str2[l]);
        if (temp != -1) {
            if(l!=0){
                sol2[l] = sol1[temp];
            }else if(l==0){
                if (sol1[temp]!=0) {
                    sol2[l] = sol1[temp];
                }
                else{
                    *r = assignFirst(str1,sol1,strlen(str1),r);
                    *r = assignSecond(str1, str2, sol1, sol2, len2, r);
                }
            }
        }
        else{
            temp = isExist(str2,str2[l]);
            if(temp != -1 && temp == l){
                if(*r > 9){
                    *r=0;
                    if(l == 0){
                        sol2[l++]=1;
                    }
                }
                sol2[l]=(*r);
                (*r)++;
            }
            else{
                sol2[l]=sol2[temp];
            }
        }
        l++;
    }
    return *r;
}

void check(char* str1,char* str2,char* str,int sol1[],int sol2[]){
    int num1=0,num2=0,res,sol[strlen(str)];
    int i=0,index1=-1,index2=-1,index=-1;
    bool flag = false;
    for(i=0;i<strlen(str1);i++){
        num1 = num1*10+sol1[i];
    }
    for(i=0;i<strlen(str2);i++){
        num2 = num2*10+sol2[i];
    }
    res = num1+num2;
//    print(sol1,strlen(str1));
//    print(sol2,strlen(str2));
    printf("%d + %d = %d\n",num1,num2,res);
//    printf("number of digits: %d\n",numberOfDigits(res));
//    printf("%s totalNumberOfMatchingCharacter:  %d, totalNumberOfMatchingNumbers: %d\n",str,totalNumberOfMatchingCharacter(str), totalNumberOfMatchingNumbers(res));
    if((numberOfDigits(res) == strlen(str)) && (totalNumberOfMatchingCharacter(str) == totalNumberOfMatchingNumbers(res))){
//            printf("%d + %d = %d\n",num1,num2,res);
        flag = true;
        for(i=0;i<strlen(str);i++){
//            printf(" %c ",str[i]);
            index1 = isExist(str1,str[i]);
            index2 = isExist(str2,str[i]);
            index = isExist(str, str[i]);
//            printf("index1: %d index2: %d index: %d\n",index1,index2,index);
                if(index1 != -1){
//                    printf("%d, %d\n",sol1[index1],getDigit(res,i));
                    if (sol1[index1] != getDigit(res,i)) {
                        flag=false;
                    }
                }
                if(index2 != -1){
//                  printf("%d, %d\n",sol2[index2],getDigit(res,i));
                    if (sol2[index2] != getDigit(res,i)) {
                        flag = false;
                    }
                }
                if ((index != i) && (index >=0)){
//                  printf("ch: %c index: %d sol: %d %d\n",str[i],index,getDigit(res,index),getDigit(res,i));
                    if(getDigit(res,index) != getDigit(res,i))
                        flag = false;
                }
            if(isDigitExist(num1, getDigit(res,i)) == true){
                if (str[i] != str1[index1]) {
                    flag = false;
                }
            }
            if(isDigitExist(num2, getDigit(res,i)) == true){
                if (str[i] != str2[index2]) {
                    flag = false;
                }
            }
        }
        if (flag) {
            printf("<<<<<<<<<<<<<solution: %d + %d = %d>>>>>>>>>>>>>>>>>>>\n",num1,num2,res);
        }
    }
//    printf("flag: %d\n",flag);
    
}

int numberOfDigits(int num){
    int i=0;
    while(num){
        num = num/10;
        i++;
    }
    return i;
}

int getDigit(int num,int index){
    index=numberOfDigits(num)-index-1;
    while (index-->0) {
        num=num/10;
    }
    return num%10;
}

int totalNumberOfMatchingCharacter(char* str1){
    int i=0,res=0,j=0;
//    printf("%s %s\n",str1,str2);
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

int arrayToNumber(int ar[],int size){
    int num=0,i=0;
    while(size != i)
        num = num*10+ar[i++];
    return num;
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
//    printf("res: %d\n",res);
    return res;
}

bool containsDigit(int num, int digit){
    while(num){
        if(num%10 == digit)
            return true;
        num = num/10;
    }
    return false;
}

void applyPermutations(char* str1, char* str2, char* str, int sol1[],int sol2[]){
    int i,j,k,l;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int tempArray2[len2];
    int tempArray1[len1];
    for (i=0; i<len2; i++) {
        tempArray2[i] = sol2[i];
    }
    for (i=0; i<len1; i++) {
        tempArray1[i] = sol1[i];
    }

    for (i=len2-1; i>=0; i--) {
        if (isExist(str1, str2[i]) == -1) {
            for(j=0;j<len2;j++){
                if (isExist(str1, str2[j]) == -1) {
                    if(sol2[i]!=0 && sol2[j] !=0){
                        if(sol2[i] != sol2[j]){
                            if((sol1[i] != sol2[i]) && (sol1[j] != sol2[j])){
                                swap(sol2,i,j);
                                check(str1,str2,str,sol1,sol2);
                            }
                        }
                    }
                }
            }
        }
        for (k=0; k<len2; k++) {
            sol2[k] = tempArray2[k];
        }
    }
//    }
    
    printf("\n");
    
//    for (k=0; k<len1; k++) {
        for (i=len1-1; i>=0; i--) {
            if (isExist(str2, str1[i]) == -1) {
                for(j=0;j<len1;j++){
                    if (isExist(str2, str1[j]) == -1) {
                    if((sol1[i]==0 || sol1[j] ==0) && !(i == 0 || j == 0)){
                        if(sol1[i] != sol1[j]){
                            if((sol1[i] != sol2[i]) && (sol1[j] != sol2[j])){
//                                printf("SOL1: before swap: %d + %d\n",arrayToNumber(sol1, len1), arrayToNumber(sol2,len2));
                                swap(sol1,i,j);
//                                printf("SOL1 after swap: %d + %d\n",arrayToNumber(sol1, len1), arrayToNumber(sol2,len2));
                                check(str1,str2,str,sol1,sol2);
                            }
                        }
                    }
                    }
                }
            }
            for (k=0; k<len1; k++) {
                sol1[k] = tempArray1[k];
            }
        }
    //}
}

//void permute(char* str1, char* str2, char *str, int sol1[], int sol2[], int check){
    
//}

void swap(int ar[], int i,int j){
    int temp = ar[i];
    ar[i] = ar[j];
    ar[j] = temp;
}
