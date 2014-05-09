#include<stdio.h>
#define MAX 1000
int totalSwaps = 0;

void print(int ar[], int l, int r){
  for(int i=l; i<= r; i++){
    printf("%d ",ar[i]);
  }
  printf("\n");
}

void swap(int ar[], int i, int j){
  int temp = ar[i];
  ar[i] = ar[j];
  ar[j] = temp;
}

int partition(int ar[], int l, int r){
  int pivot = ar[r];
  int i=l-1, j;
  for(j = l; j<r;j++){
    if(ar[j] <= pivot){
      i = i+1;
      swap(ar,i,j);
      totalSwaps++;
    }
  }
  swap(ar,i+1,r);
  return i+1;
}

void quick(int ar[], int l, int r){
  if(l < r){
    int pos = partition(ar, l, r);
    quick(ar, l, pos-1);
    quick(ar, pos+1, r);
  }
}

int main(){
  int size,ar[MAX]={0},i=0,n;
  scanf("%d",&size);
  n = size;
  while(n-->0)
    scanf("%d",&ar[i++]);
  quick(ar, 0,size-1);
  printf("Sorted array: ");
  print(ar,0,size-1);
  printf("total number of swaps: %d\n",totalSwaps);
 return 0;
}
