#include <stdio.h> 
int main() { 
char symbol; 
int asciinum = 0, othernum = 0; 
while ((symbol = getchar()) != EOF) { 
  if (symbol >= 0 && symbol <= 127) { 
    asciinum++;   
  } 
  else { 
    othernum++; 
  } 
} 
 
printf("%d %d", asciinum, othernum / 2); 
return 0; 
}