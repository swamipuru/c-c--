#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main(){
  long f[50];
  long i=0;
  long fib[10000000000]={0};
  long n,k;
  f[0] = 1;
  fib[0] = 1;
  f[1] = 1;
  fib[1] = 1;
  i = 2;
  
  while(i < 30){
    f[i] = f[i-1]+f[i-2];
    n = f[i];
    fib[n] = 1;
    i++;
  }
  
  for(i=0;i<1000;i++){
   if(fib[i])
     printf("%ld: %ld\n",i,fib[i]);
  }
    
 return 0;
}

