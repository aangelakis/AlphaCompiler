###################################################
#       Christos Zarkos csd4516@csd.uoc.gr        #
#     Theodoros Chalkidis csd4198@csd.uoc.gr      #
#     Αlexandros Angelakis csd4334@csd.uoc.gr     #
#            Phase_4_5 avm Makefile ~ hy340       #
###################################################

avm:
	gcc -Wall -g -lm avm.c avm_stack.c avm_main.c avm_table.c read_binary/*c exec_functions/*c  avm_libfuncs.c ../libs/symtable/symtablehash.c -lm -o avm.out

clean:
	rm -rf avm.out
