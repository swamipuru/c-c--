#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 1
#define NUMELEM 5

int main(int argc, char *argv[]){
 
 FILE *fs = NULL;
 FILE *fd = NULL;
 fd = fopen("final.c", "w");
 fs = fopen(argv[1], "r");
 char *line = NULL;
 char read;
 size_t len;
 int i=0;
 
 if(NULL == fd || NULL == fs){
  printf("\n fopen() Error!!!!\n");
  return 1;
 } 

 fprintf(fd,"#include<stdio.h>\n\n");
//write function to file 
 while(-1 != (read = getline(&line, &len,fs))){
  fprintf(fd,"%s",line);
 } 
 //add main function
 fprintf(fd,"\n\nint main() {\n");
 fprintf(fd," int x;\n");
 line = "printf(\"Enter value of x: \");\n";
 fprintf(fd," %s",line);
 line = "scanf(\"%d\",&x);\n";
 fprintf(fd," %s",line);
 line = "x =";
 fprintf(fd," %s",line);
 line =  argv[2];
// printf("function name: %s\n",argv[2]);
 fprintf(fd," %s",line);
 line = "(x);\n";
 fprintf(fd," %s",line);
 line = "printf(\" ";
 fprintf(fd," %s",line);
 line = argv[2];
 fprintf(fd," %s",line);
 line = ": %d\\n\",x);\n";
 fprintf(fd," %s",line);
 fprintf(fd," return 0;\n}"); 

// printf("written to file\n");

// printf("\n fwrite() successful, data written to text file\n");
 fclose(fd); 
 fclose(fs);
 
 return 0;
}
