###################################################
#       Christos Zarkos csd4516@csd.uoc.gr        #
#     Theodoros Chalkidis csd4198@csd.uoc.gr      #
#     Αlexandros Angelakis csd4334@csd.uoc.gr     #
#              Phase_4 Makefile ~ hy340           #
###################################################

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
	gcc scanner.c parser.c syntaxanal.c instruction.c libs/scopelist/scopelists.c libs/zarkList/zarkList.c libs/symtable/symtablehash.c libs/SymTableEntry/SymTableEntry.c quads.c expression.c libs/Vektor/Vektor.c libs/stack/stack.c

avm:
	gcc avm/avm.c avm/avm_stack.c avm/avm_main.c avm/read_binary/read_binary.c avm/exec_functions/arithm_exec.c avm/exec_functions/assign_exec.c avm/exec_functions/exec.c avm/exec_functions/func_exec.c avm/exec_functions/relat_exec.c avm/exec_functions/table_exec.c


clean:
	rm -rf a.out parser.c parser.h scanner.c scanner.h lex_output.txt yacc_output.txt quads_output.txt instructions_output.txt out.out binary.abc

