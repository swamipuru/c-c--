#include<stdio.h>
#include <stdlib.h>

int main(){

  void *a = 5;
  void *b = 'c';
  int i=0,j;
  i += printf("%d %c",a,b);
  // i += printf("%d"); 
  printf("%d",i);
  for(j=0;j<=i;j++)
    printf("\b");
  //    printf("\n%d",scanf("%d %d",&i,&j));
  // printf("  %d\n",j);
  printf("----");
  //printf("******  %d",printf("12345678 %d",j));
  // _Exit(1);
  printf("%d",printf("\n\b")); 
  return 0;
}
