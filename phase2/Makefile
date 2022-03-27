all: bison flex gcc

conflicts: bison_conflict

bison_conflict:
	bison --defines -v  --output=parser.c parser.y

bison:
	bison --defines  --output=parser.c parser.y

flex:
	flex --outfile=scanner.c scanner.l

gcc:
	gcc scanner.c parser.c syntaxanal.c

clean:
	rm -rf a.out parser.c parser.h scanner.c scanner.h
