#include<stdio.h>
#include<ctype.h>
#include<string.h>

int main(int argc, char* argv[]){
  int c;
  if(strncmp(argv[1], "tolower", NULL)) c = 0;
  else if(argv[1] == "toupper") c = 1;
  switch(c){
  case 0:
    printf("tolower");
    break;

  case 1:
    printf("toupper");
    break;
  }
  return 0;
}
