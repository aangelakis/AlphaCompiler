###################################################
#       Christos Zarkos csd4516@csd.uoc.gr        #
#     Theodoros Chalkidis csd4198@csd.uoc.gr      #
#     Αlexandros Angelakis csd4334@csd.uoc.gr     #
#                 Phase_2 ~ hy340                 #
###################################################

# Makefile for compiling and running our tests.

all: test_scopeList test_symtable test_zarkList test_total

test_scopeList:
	gcc scopelistTestMain.c ../libs/scopelist/scopelists.c  ../libs/zarkList/zarkList.c ../libs/SymTableEntry/SymTableEntry.c -o scopeList
	./scopeList

test_symtable:
	gcc symtableTestMain.c ../libs/scopelist/scopelists.c  ../libs/zarkList/zarkList.c ../libs/SymTableEntry/SymTableEntry.c ../libs/symtable/symtablehash.c -o symtable
	./symtable

test_zarkList:
	gcc zarkListTestMain.c ../libs/zarkList/zarkList.c -o zarkList
	./zarkList

test_stack:
	gcc stackTestMain.c ../libs/stack/stack.c -o stack
	./stack

test_total:
	gcc TotalTestMain.c ../libs/scopelist/scopelists.c  ../libs/zarkList/zarkList.c ../libs/SymTableEntry/SymTableEntry.c ../libs/symtable/symtablehash.c -o total
	./total

clean:
	rm -rf zarkList scopeList total symtable stack