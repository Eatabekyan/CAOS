#include <stdio.h>
#include <string.h>
#include <unistd.h>

char* GetPyExpr(char* py_expr){
  fgets(py_expr, 4096, stdin);    
  return py_expr;
}

int main()
{   char py_expr[4096];
    char code[4096];
    snprintf(code, 4096, "print(%s)", GetPyExpr(py_expr));
    execlp("python3", "python3", "-c", code, NULL);
    return 0;
}
