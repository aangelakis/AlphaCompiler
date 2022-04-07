***************************************************
*       Christos Zarkos csd4516@csd.uoc.gr        *
*     Theodoros Chalkidis csd4198@csd.uoc.gr      *
*     Αlexandros Angelakis csd4334@csd.uoc.gr     *
*                 Phase_2 ~ hy340                 *
***************************************************

How to compile and run:
    make;
    ./a.out name_of_test_file;

How to compile and run our tests in folder "/testMains":
    make all; -> For compiling and running all the tests one by one.
    make test_total; -> For compiling and running the TotalTestMain.c test file.
    make test_scopeList; -> For compiling and running the scopelistTestMain.c test file.
    make test_symtable; -> For compiling and running the symtableTestMain.c test file.
    make test_zarkList; -> For compiling and running the zarkListTestMain.c test file.

-Syntax Analysis is implemented using YACC/Bison program in C, following the grammar of Alpha Programming Language.
-There are no conflicts in our grammar, except of the ifelse conflict.
-The scope rules are working as intended, based on the FAQ and the Labs.
-Some logical error checkings are also implemented (to our knowledge this is not something asked to be implemented in this phase, but we tried to do some anyway).
-In the folder "testMains" there are some test programs we created to test our data structures. They show their functionality and usage very well.

-Phase_2 was tested on 'portokali'.