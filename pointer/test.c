#include<stdio.h>

int main(){
 int i=10;
 int *ptr = &i;
 ptr++;
 printf("%p\n",ptr);
 printf("%Fp\n",ptr);
 return 0;
}
