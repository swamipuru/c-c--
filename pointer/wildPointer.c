/*
* A pointer in C which has not been initialized is known as wild poiter.
*/

#include<stdio.h>

int main(){
 int *ptr;
 printf("%d\n",ptr);
 printf("%d\n",*ptr);

 return 0;
}
