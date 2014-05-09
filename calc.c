#include<stdio.h>
#include<stdlib.h>

int calc_sum(int x,int y){
 return x+y;
}

int calc_subtract(int x, int y){
 return x-y;
}

int calc_multiplies(int x, int y){
 return x*y;
}

int calc_divides(int x, int y){
 if(y != 0)
  return x/y;
 else
  fprintf(stderr, "Math error: Division by zero!");
}

int main(int argc, char *argv[]){
 int x=6,y=2;
 //scanf("%d %d",&x,&y);
 printf("x: %d, y: %d\n",x,y);
 printf(" + sum: %d\n",calc_sum(x,y));
 printf(" + subtract: %d\n",calc_subtract(x,y));
 printf(" + multiplies: %d\n",calc_multiplies(x,y));
 printf(" + divides: %d\n",calc_divides(x,y));
 return 0;
}
