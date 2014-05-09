/*
* void pointer is known as Generic Pointer.
* Generic pointer can point to any type of data.
*1. We cannot dereference generic pointer.
*2. We can find the size of generic pointer using sizeof operator.
*3. Generic pointer can hold any type of pointers like char pointer, struct
*    pointer, array of pointer etc. without any typecasting.
*4. Any type of pointer can hold generic pointer without any typecasting.
*5. Generic pointers are used when we want to return such pointer which is 
*     applicable to all types of pointers.
*/

#include<stdio.h>
#include<stdlib.h>

int main(){
 void *ptr;
 char c = 'A';
 int i =4;
 void *p;
 char *q = &c;
 int *r = &i;
/* error:
 printf("%d\n",*ptr);
*/
 printf("size %d\n",sizeof(ptr));
 
 p = q;
 printf("%c\n",*(char*)p);

 p = r;
 printf("%d\n",*(int*)p); 

 return 0;
}
