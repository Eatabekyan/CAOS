
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

void CreateFile(){
  char expression[4096];
  int i = 0;
  fgets(expression, sizeof(expression), stdin);
  FILE* open_cfile = fopen("out.c", "w");
  const char* code = "#include <stdio.h>\nint main(){printf(\"%%d\\n\",(%s));}";
  fprintf(open_cfile, code , expression);
  fclose(open_cfile);
}
void CompileAndRun(){
  int status = fork();
  if (0 == status) {
      execlp("gcc", "gcc", "out.c", NULL);
  } else {
      wait(&status);
      execlp("./a.out", "./a.out", NULL);
  }
}

int main()
{
  CreateFile();
  CompileAndRun();
}