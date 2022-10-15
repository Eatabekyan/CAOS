#include <stdio.h>
#include <stdint.h>
int main() {
  unsigned char symbol[1000];
  uint64_t massive=0;
  uint64_t res=0;
  uint64_t t = 1;
  scanf("%s",&symbol[0]);
  int j = 0;
  while(symbol[j] != '\0'){
    if(symbol[j] >= '0' && symbol[j] <= '9'){
      massive = massive|(t<<(symbol[j]-'0'));
    } else if(symbol[j] >= 'A' && symbol[j] <= 'Z'){
      massive = massive|(t<<(symbol[j]-'A'+ 10));
    } else if(symbol[j] >= 'a' && symbol[j] <= 'z'){
      massive = massive|(t<<(symbol[j]-'a'+ 36));
    } else if(symbol[j] == '&') {
      res &= massive;
      massive=0;
    } else if(symbol[j] == '|') {
      res |= massive;
      massive=0;
    } else if(symbol[j] == '^') {
      res ^= massive;
      massive=0;
    } else if(symbol[j] == '~'){
      res = (~res);
    } 
    j++;
  }
  for(int i = 0 ; i < 62 ; i++){
    if (res & 1) {
      if(i < 10){
        printf("%d",i);
      } else if(i>=10 && i < 36){
        printf("%c", i+'A'-10);
      } else {
        printf("%c", i+'a'- 36);
      }
    }
    res >>= 1;
  }
  printf("\n");
  return 0;
}
