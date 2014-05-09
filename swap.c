#include <stdio.h>
#if !defined(__APPLE__)
#include <malloc.h>
#endif
#include <stdlib.h>

void swap(int* a, int* b){
  printf("%lu %lu\n",sizeof(a),sizeof(*a));
  int* temp = malloc(sizeof(a));
  *temp = *a;
  *a = *b;
  printf("%d %d %d....\n",*temp,*a,*b);
  *b = *temp;
  printf("%d %d %d----\n",*temp,*a,*b);
}

void swap(double* a, double* b){
  double* temp = malloc(sizeof(a));
  *temp = *a;
  *a = *b;
  *b = *temp;
}

int main(){
  int a = 110, b = 1;
  printf("%d %d\n",a,b);
  swap(&a,&b);
  printf("%d %d\n",a,b);
  return 0;
}
