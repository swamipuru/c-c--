#include<stdio.h>

int totalSwaps=0;

void print(int ar[], int l, int r){
 for(int i=l;i<=r;i++)
  printf("%d ",ar[i]);
 printf("\n");
}

void swap(int ar[], int i,int j){
 int temp = ar[i];
 ar[i] = ar[j];
 ar[j] = temp;
}
void bubble(int ar[], int size){
 for(int i=0;i<size-1;i++){
  for(int j=size-1;j>i;j--){
   if(ar[j] < ar[j-1])
    swap(ar,j,j-1);
    totalSwaps++;
  }
 }
}

int main(){
 int ar[] = {5,8,1,3,7,9,2},size=7,n,i=0;
 printf("Enter size of array: ");
 scanf("%d",&size);
 n=size;
 printf("Enter elements: ");
 while(n-->0) scanf("%d",&ar[i++]);
 bubble(ar, size);
 print(ar,0,size-1);
 printf("total number of swaps: %d\n",totalSwaps);
 return 0;
}
