/*
*If any pointer is pointing the memory address of any variable but after some 
* time variable has been deleted from that memory location while pointer is 
*still pointing such memory location.
*/


#include<stdio.h>
int *call();

int main(){
 int *ptr;
 ptr = call();

 fflush(stdin);
 printf("%d\n",*ptr);
 return 0;
}

int* call(){
 int x = 25;
 ++x;
return &x;
}
