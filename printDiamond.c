#include<stdio.h>

void printUpper(int n){
 int i,j,k,l;
 for(i = n; i>0; i--){
  for(j=i;j>0;j--)
   printf("  ");
  for(k = 1;k<=(n-i+1);k++)
   printf("%d ",k);
  for(l = k-2; l > 0; l--)
   printf("%d ",l);
  printf("\n");
 }
}

void printLower(int n){
 int i,j,k,l,p;
 for(i=1; i<=n; i++){
  for(j=0;j<=i;j++)
   printf("  ");
  for(k=1;k<=(n-i+1);k++)
   printf("%d ",k);
  for(l=k-2;l>0;l--)
   printf("%d ",l);
  printf("\n");
 }
}

int main(){
 int n;
 scanf("%d",&n);
 printUpper(n);
 printLower(n-1);
}
