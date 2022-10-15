#include <stdio.h>
#include <stdint.h>
#include <math.h>
typedef enum {
    PlusZero      = 0x00,
    MinusZero     = 0x01,
    PlusInf       = 0xF0,
    MinusInf      = 0xF1,
    PlusRegular   = 0x10,
    MinusRegular  = 0x11,
    PlusDenormal  = 0x20,
    MinusDenormal = 0x21,
    SignalingNaN  = 0x30,
    QuietNaN      = 0x31
} float_class_t;

extern float_class_t classify(double *value_ptr);
extern float_class_t classify(double *value_ptr) {
  struct MES {
          uint64_t   mant : 52;
          uint64_t   exp : 11;
          uint64_t   s : 1;
        };
  void* value_ptr_as_void = value_ptr;
  struct MES* value_MES = value_ptr_as_void;
  if(value_MES->mant == 0 && value_MES->exp == 0 && value_MES->s == 0){
    return PlusZero;
  }
  if(value_MES->mant == 0 && value_MES->exp == 0 && value_MES->s == 1){
    return MinusZero;
  }
  if(value_MES->mant == 0 && value_MES->exp == 2047 && value_MES->s == 0){
    return PlusInf;
  }
  if(value_MES->mant == 0 && value_MES->exp == 2047 && value_MES->s == 1){
    return MinusInf;
  }
  if(value_MES->exp == 0 && value_MES->s == 0){
    return PlusDenormal;
  }
  if(value_MES->exp == 0 && value_MES->s == 1){
    return MinusDenormal;
  }
  if(value_MES->mant>>51 == 1 && value_MES->exp == 2047 && value_MES->s == 0){
    return QuietNaN;
  }
  if(value_MES->mant>>51 != 1 && value_MES->exp == 2047 && value_MES->s == 0){
    return SignalingNaN;
  }
  if(value_MES->s == 0){
    return PlusRegular;
  }
  return MinusRegular;
};

