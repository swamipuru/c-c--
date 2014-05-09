#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
int strLen(char* str){
    int i=0;
    while(str[i])i++;
    return i;
}

char* getSubStr(char* str1, char* str2){
    int i=0;
    char *subStr = (char*)malloc(strLen(str1)*sizeof(char));
    char *sub = (char*)malloc(strLen(str1)*sizeof(char));
    int k=0;
    int j=0;
    int index;
    int tempIndex;
    while (str1[i]) {
        j=0;
        while (j<strLen(str2)) {
            k=0;
            while (j<strLen(str2) &&( str1[i] != str2[j])) {
                j++;
            }
            index = i;
            tempIndex = j;
            while (index<strLen(str1)&&j<strLen(str2) &&  (str1[index] == str2[tempIndex])) {
                subStr[k] = str1[index];
                k++;
                index++;
                tempIndex++;
            }
            subStr[k] = '\0';
            if (strLen(subStr) > strLen(sub)) {
                for (int p=0; p<strLen(subStr); p++) {
                    sub[p] = subStr[p];
                }
            }
            j++;
        }
        i++;
    }
    return sub;
}

int main() {
    char str1[MaxSize],str2[MaxSize];
    char *subStr = (char*)malloc(MaxSize*sizeof(char));
    printf("string1: ");
    fgets( str1,MaxSize,stdin);
    printf("string2: ");
    fgets( str2,MaxSize,stdin );
    subStr =getSubStr(str1,str2);
    printf("subString: %s\n",subStr);
    return 0;
}

