#include<stdio.h>
#include<stdlib.h>

void print(int ar[], int size){
  for(int i=0; i<size; i++)
    printf("%d ",ar[i]);
  printf("\n");
}

void merge(int arr[], int l, int m, int r){
  int i,j,k;
  int n1 = m - l+1;
  int n2 = r-m;
  int L[n1], R[n2];
  //copy
  for(i=0;i<n1;i++)
    L[i] = arr[l+i];
  for(j=0;  j<=n2; j++)
    R[j] = arr[m+1+j];

  //merge
  i=0;j=0;k=l;
  while(i  < n1 && j < n2){
    if(L[i] <= R[j]){
      arr[k]= L[i];
      i++;
    }else{
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  //copy remaining elements
  while(i < n1){
    arr[k] = L[i];
    i++;
    k++;
  }
  while(j < n2){
    arr[k] = R[j];
    j++;
    k++;
  }
}

void mergeSort(int arr[], int l, int r){
  if(l < r){
    int m = (l +r)/2;
    mergeSort(arr, l,m);
    mergeSort(arr, m+1, r);
    merge(arr, l,m,r);
  }
}

void printIndex(int ar[], int value, int k, int size){
  static int i=0;
  int j=0;
  for(i=0; i<size; i++){
    //printf(" %d ",ar[i]);
    if(ar[i] == value && j < k){
      printf("%d ",i);
      j++;
    }
  }
}

int main(){
  int size = 6;
  int k = 3,i,j,ans=0;
  int ar[] = {5,8,1,3,7,9,2};
  int *br = (int*)malloc(sizeof(ar));
  for(i=0; i<size; i++)
    br[i] = ar[i];
  for(i=0;i<size;i++)
    br[i] = ar[i];
  print(ar,size);
  mergeSort(ar,0,size-1);
  print(ar,size);
  print(br,size);
  for(i=0; i<size; i++){
    if(ar[i] == ar[i+k-1]){
      ans++;
      printIndex(br, ar[i],k, size);
      i = i+k-1;
      //for(j=0;j<k;j++)
	//printf("%d ",i+j);
    }
  }
  if(ans < 2)
    printf("No\n");
 else
    printf("Yes\n"); 
  return 0;
}
