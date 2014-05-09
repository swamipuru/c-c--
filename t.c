#include<stdio.h>
#include<stdlib.h>

union employee
{
 char name[15];
 int age;
 float salary;
};
const union employee e1;

int main()
{
 strcpy(e1.name, "K");
 printf("%s %d %0.2f", e1.name, e1.age, e1.salary);
 return 0;
}
