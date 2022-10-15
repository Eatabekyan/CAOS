  .text
  .global solve
solve:
  mov    w4, #0      
LoopBegin:          
  cmp    w4, #255    
  bge    LoopEnd
  ////////////////////////    
  mov    w5, #1
  mov    w13, w3
  ////////////////////////
  mul    w5 , w5, w4
  mov    w12, w2
  mul    w12, w12, w5
  add    w12, w12, w13
  ////////////////////////
  mul    w5 , w5, w4
  mov    w11, w1
  mul    w11, w11, w5
  add    w11, w11, w12
  ////////////////////////
  mul    w5 , w5, w4
  mov    w10, w0
  mul    w10, w10, w5
  add    w10, w10, w11
  ///////////////////////
  cmp    w10, #0
  beq    LoopEnd
  add    w4, w4, #1  
  b      LoopBegin  
LoopEnd:
  mov  w0, w4
  ret
  