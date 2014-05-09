#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<termios.h>
void printUpper(int n, char ch){
 int i,j,k,l;
 for(i = n; i>0; i--){
  for(j=i;j>0;j--)
   printf("  ");
  for(k = 1;k<=(n-i+1);k++)
   printf("%c ",ch);
  for(l = k-2; l > 0; l--)
   printf("%c ",ch);
  printf("\n");
 }
}

void printLower(int n, char ch){
 int i,j,k,l,p;
 for(i=1; i<=n; i++){
  for(j=0;j<=i;j++)
   printf("  ");
  for(k=1;k<=(n-i+1);k++)
   printf("%c ",ch);
  for(l=k-2;l>0;l--)
   printf("%c ",ch);
  printf("\n");
 }
}

int main(){
 int n,k, t = 500000000;
 scanf("%d",&n);
 k=300;
 char ch = '*';
 while(1){
  system("clear");
  printUpper(n,ch);
  printLower(n-1,ch);
  usleep(100000);
  //wait(&t);
  //system("timeout /t 30"); 
  fflush(stdout);
  if(ch == '*')
   ch = '.';
  else
   ch = '*';
  if(kbhit()) break;
 }
 return 0;
}
