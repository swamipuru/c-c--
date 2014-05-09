#include<stdio.h>
#include<stdlib.h>

crash(){
  char a[0];
  free(a);
}

int main(int argc,char **argv){
crash();
return 0;
}
