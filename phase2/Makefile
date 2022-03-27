all: bison flex gcc

bison:
	bison --defines  --output=parser.c parser.y

flex:
	flex --outfile=scanner.c scanner.l

gcc:
	gcc scanner.c parser.c syntaxanal.c

clean:
	rm -rf a.out parser.c parser.h scanner.c scanner.h