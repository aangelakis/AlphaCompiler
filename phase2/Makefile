all: bison flex gcc

nogcc: bison flex

conflicts: bison_conflict

bison_conflict:
	bison --defines -v  --output=parser.c parser.y

bison:
	bison --defines  --output=parser.c parser.y

flex:
	flex --outfile=scanner.c scanner.l

gcc:
	gcc scanner.c parser.c syntaxanal.c libs/scopelist/scopelists.c libs/zarkList/zarkList.c libs/symtable/symtablehash.c libs/SymTableEntry/SymTableEntry.c

clean:
	rm -rf a.out parser.c parser.h scanner.c scanner.h lex_output.txt yacc_output.txt
