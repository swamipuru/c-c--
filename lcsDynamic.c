#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100

int strLen(char* str){
    int i=0;
    while(str[i])i++;
    return i;
}

void reverseString(char* str){
    for (int i=0; i<strLen(str)/2;i++) {
        char ch = str[strLen(str)-i-1];
        str[strLen(str)-i-1] = str[i];
        str[i] = ch;
    }
}

void LCS(char* x, char* y, int m, int n){
    int kValue = 2;
    int matrix[m][n];
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            matrix[i][j]=0;
        }

    }
    int indexX,indexY,max=0;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            if (x[i] == y[j]) {
                if (i==0 || j==0) {
                    matrix[i][j] = 1;
                }else{
                    matrix[i][j] = matrix[i-1][j-1]+1;
                }
                if (max < matrix[i][j]) {
                    max = matrix[i][j];
                    indexX = i;
                    indexY = j;
                }
            }
        }
    }
    
    char *sub = (char*)malloc(max*sizeof(char));
    int i;
    for (i=0; i<max; i++) {
        sub[max-i-1] = x[indexX--];
        indexY--;
    }
    sub[max] = '\0';
    printf("lcs: %s\n",sub);
}

void findLCS(char* str1, char* str2){
    int m = strLen(str1);
    int n = strLen(str2);
    LCS(str1, str2, m,n);
    
}

int main() {
    char str1[MaxSize],str2[MaxSize];
    printf("string1: ");
    fgets(str1, MaxSize, stdin);
    printf("string2: ");
    fgets(str2, MaxSize, stdin);

    findLCS(str1,str2);
    return 0;
}
