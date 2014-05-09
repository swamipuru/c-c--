#include<stdio.h>
#define MAX 10000

int numberOfShifts=0;

void print(int ar[], int size){
 for(int i=0; i<size; i++)
  printf("%d ",ar[i]);
 printf("\n");
}

void insertion(int ar[], int size){
 for(int j=1;j<size;++j){
  int key = ar[j];
  int i = j-1;
  while(i >= 0 && ar[i] > key){
   ar[i+1] = ar[i];
   numberOfShifts++; 
   i--;
  }
  ar[i+1] = key;
 }
}

int main(){
 int size,ar[MAX]={0},i=0,n;
 scanf("%d",&size);
 n = size;
 while(n-- > 0)
  scanf("%d",&ar[i++]);
 insertion(ar, size);
 print(ar,size);
 printf("Total number of shits: %d\n",numberOfShifts);
 return 0;
}
