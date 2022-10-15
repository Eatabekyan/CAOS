#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int sum = 0;
int isint(const char* str);
void addline(char* line);
int isint(const char* str){
  if(*str=='\0')
    return 1;
  if(!isdigit(*str)){
    return 0;
  }
  return isint(str+1);
}
void addline(char* line){
  int flag = 0; 
  
  if(line[0]!='#'){
      while(line[0] != '=') {
        line++;
      }
      line++;
      if(isint(line)==1){
        int v = atoi(line);
        sum += v;
      } else {
        printf("%s\n", line);
      }
    }

}
int main(int argc, char* argv[])
{
  
  char* line;