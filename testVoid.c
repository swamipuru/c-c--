#include<stdio.h>

int main(void){
  static int i=500;
  if(--i){
    printf("%d ",i);
    main(10);
  }
  return 0;
}
