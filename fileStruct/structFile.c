#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct customer {
   char name[30];
   double  availBal;
}customer;

typedef struct transaction{
  char sender[30];
  char receiver[30];
  double transferAmount;
  static int totalInvestments;
}transaction;

char *mygetline(char *line, int size)
{
   if ( fgets(line, size, stdin) )
   {
      char *newline = strchr(line, '\n'); /* check for trailing '\n' */
      if ( newline )
      {
         *newline =  '\0'; /* overwrite the '\n' with a terminating null */
      }
   }
   return line;
}


int mygeti(double *result)
{
   char buff [ 13 ]; /* signed 32-bit value, extra room for '\n' and '\0' */
   return fgets(buff, sizeof buff, stdin) && sscanf(buff, "%lf", result) == 1;
}

void record_write(const char *filename)
{
   FILE *file = fopen(filename, "ab"); /* append to the file in binary mode */
   if ( file != NULL )
   {
      customer data;
      /*
       * Read a string from the user. Put it into the structure.
       */
      printf("Enter name: ");
      fflush(stdout);
      mygetline(data.name, sizeof data.name);
      /*
       * Read a string from the user. Put it into the structure.
       */
      do
      {
         printf("Enter Avail bal: ");
         fflush(stdout);
      } while ( !mygeti(&data.availBal) );
      /*
       * Write the data to the file.
       */
      fwrite(&data, sizeof data, 1, file);
      fclose(file);
   }
}




void record_readall(const char *filename)
{
   FILE *file = fopen(filename, "rb"); /* read from the file in binary mode */
   if ( file != NULL )
   {
      customer data;
      while ( fread(&data, sizeof data, 1, file) == 1 ) /* read all records */
      {
         printf("%s : %f\n", data.name, data.availBal); /* print each */
      }
      fclose(file);
   }
}



int main()
{
   static const char inputFile[] = "output.dat";
   char line[10];
   /*
    * Loop as long as the user wants to add records.
    */
   while (1 )
   {
      char line[10];
      fputs("Add record (Y/N)? ", stdout);
      fflush(stdout);
      mygetline(line, sizeof line);
      if ( tolower(*line) == 'n' )
      {
         break;
      }
      record_write(inputFile);
   }
   /*
    * Show all records in the file.
    */
   record_readall(inputFile);
   
   printf("transactions:");


   return 0;
}
