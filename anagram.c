#include<stdio.h>
#include<stdlib.h>

int strlen(char *str){
  int i=0;
  while(str[i++]);
  return i;
}

char* getString(char *s, int index, int jump){
  int i=0,j=0;
  int temp;
  char *permute = (char*)malloc(strlen(s));
  for(i=0;i<strlen(s);i++){
    temp = (i+index + jump)%strlen(s);
    if(s[temp]){
      permute[j++] = s[temp];
    }
  }
  permute[j]='\0';
  return permute;
}

void getAllStrings(char *s,char *mat[],int jump){
  int i=0;
  for(i=0;i<strlen(s);i++){
    mat[i] = getString(s,i,jump);
  }
}

void createAnagram(char *s){
  int len = strlen(s)-1,i=0,j=0;
  char *anaMat[len];
  printf("i: %d\n",i);
  int totalStrings = 0;
  for(i=0;i<len;i++){
    printf("i: %d\n",i);
    getAllStrings(s,anaMat,i);
    printf("First strings are: \n");
    for(j=0;j<len;j++){
      totalStrings++;
      printf("%s\n",anaMat[j]);
    }
    //printf("i: %d\n",i);
    //printf("anammat[0]: %s\n ",anaMat[i]);
    s = anaMat[i];
  }
  printf("\ntotal strings: %d\n",totalStrings);
}



int main(int argc, char **argv){
  char *s = "creative";
  printf("%s len is %d\n",s,strlen(s));
  createAnagram(s);
  return 0;
}
