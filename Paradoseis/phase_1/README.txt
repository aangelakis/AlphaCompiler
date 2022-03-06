***************************************************
*       Christos Zarkos csd4516@csd.uoc.gr        *
*     Theodoros Chalkidis csd4198@csd.uoc.gr      *
*     Αlexandros Angelakis csd4334@csd.uoc.gr     *
*                 Phase_1 ~ hy340                 *
***************************************************

How to compile and run:
For the lex:
    make
    make test (or ./a.out name_of_test_file)

P.S.
    make test runs a test file named "test.txt" and it redirects its output to a out.out file.

For the bonus:
    gcc byhand.c
    ./a.out name_of_test_file

-Lexical Analysis is implemented using Flex program, following the rules of Alpha Programming Language.
-Everyting is working as intented, based on the FAQ section, for both lex and bonus.
-Bonus is implemented using the state transition table technique, in order to create our own lexical analyzer.
-Phase_1 was tested on 'portokali' for both lex and bonus.
