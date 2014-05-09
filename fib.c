#include<stdio.h>

long fib(int n){
  long f[n+1];
  long i=0;
  f[0] = 1;
  f[1] = 1;
  i = 2;
  while(i <= n){
    f[i] = f[i-1]+f[i-2];
    i++;
  }
  return f[n];
}

int main(){
  long i=0;
  while(i<70){
    printf("f[%ld]: %ld\n",i,fib(i));
    i++;
  }
  return 0;
}
