SHELL := /bin/bash
M := ""$$(cat ./compile.conf)""
run: solution.o
	@./program.exe
	@chmod +x program.exe
solution.o:
	@./generate.sh
	@gcc -g solution.c -o program.exe

clean:
	@rm -f program.exe
	@rm -f solution.c