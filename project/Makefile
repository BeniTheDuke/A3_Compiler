all: lexyacc-code/calc3i.exe

lexyacc-code/y.tab.c lexyacc-code/y.tab.h: lexyacc-code/calc3.y
	bison -y -d lexyacc-code/calc3.y

lexyacc-code/lex.yy.c: lexyacc-code/calc3.l
	flex lexyacc-code/calc3.l

lexyacc-code/lex.yy.o lexyacc-code/y.tab.o: lexyacc-code/lex.yy.c lexyacc-code/y.tab.c
	gcc -c lexyacc-code/y.tab.c lexyacc-code/lex.yy.c

lexyacc-code/calc3i.exe: lexyacc-code/y.tab.o lexyacc-code/lex.yy.o lexyacc-code/calc3i.c
	gcc lexyacc-code/y.tab.o lexyacc-code/lex.yy.o lexyacc-code/calc3i.c -o lexyacc-code/calc3i.exe


clean: 
	rm lexyacc-code/y.tab.c lexyacc-code/y.tab.h lexyacc-code/lex.yy.c lexyacc-code/lex.yy.o lexyacc-code/y.tab.o
