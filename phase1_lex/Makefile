# Phase1 was tested on 'portokali'.
all: flex compile

flex:
	flex --outfile=scanner.c scanner.l

compile:
	gcc lexanal.c scanner.c

test:
	./a.out test.txt > out.out

clean:
	rm a.out scanner.c scanner.h
