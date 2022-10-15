//#define __STDC_FORMAT_MACROS
//#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

extern void sum(uint64_t first, uint64_t second, uint64_t *res, int *CF);
extern void mul(uint64_t first, uint64_t second, uint64_t *res, int *CF);

extern void sum(uint64_t first, uint64_t second, uint64_t* res, int* CF) {
    uint64_t carry = 0;
    uint64_t size = sizeof(uint64_t);
    for (uint64_t i = 0; i < size; i++) {
        carry = first & second;
        first = first ^ second;
        second = (carry << 1);
    }
    *res = first;
    if (carry == 0) {
        *CF = 0;
    } else {
        *CF = 1;
    }
}

extern void mul(uint64_t first, uint64_t second, uint64_t *res, int *CF) {
  uint64_t curr = 0;
  while(second != 0) {
    second--;
    sum(curr,first,res,CF);
    curr = *res;
  }
  *res = curr;
  //printf("%"PRIu64"\n", curr);
}

/*int main() {
  uint64_t res = 0 , CF = 0;
  mul(10,0,&res,&CF);
  return 0;
}*/