#include<stdio.h>

int getMax(int a, int b);
int main(){
 int x = 3, y =4,max;
 max = getMax(x,y){
  if(x > y)
   return x;
  else
   return y;
 }
 printf("max is :%d\n",max);
 return 0;
}
