/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    STRING = 259,                  /* STRING  */
    INT = 260,                     /* INT  */
    DOUBLE = 261,                  /* DOUBLE  */
    LE = 262,                      /* "<="  */
    LT = 263,                      /* "<"  */
    NE = 264,                      /* "!="  */
    GE = 265,                      /* ">="  */
    GT = 266,                      /* ">"  */
    EQ = 267,                      /* "=="  */
    ASSIGN = 268,                  /* "="  */
    PLUS = 269,                    /* "+"  */
    MINUS = 270,                   /* "-"  */
    PLUS_PLUS = 271,               /* "++"  */
    MINUS_MINUS = 272,             /* "--"  */
    MULT = 273,                    /* "*"  */
    DIV = 274,                     /* "/"  */
    MOD = 275,                     /* "%"  */
    IF = 276,                      /* "if"  */
    ELSE = 277,                    /* "else"  */
    WHILE = 278,                   /* "while"  */
    FOR = 279,                     /* "for"  */
    FUNCTION = 280,                /* "function"  */
    RETURN = 281,                  /* "return"  */
    BREAK = 282,                   /* "break"  */
    CONTINUE = 283,                /* "continue"  */
    AND = 284,                     /* "and"  */
    NOT = 285,                     /* "not"  */
    OR = 286,                      /* "or"  */
    LOCAL = 287,                   /* "local"  */
    TRUE = 288,                    /* "true"  */
    FALSE = 289,                   /* "false"  */
    NIL = 290,                     /* "nil"  */
    LEFT_BRACKET = 291,            /* "["  */
    RIGHT_BRACKET = 292,           /* "]"  */
    LEFT_BRACE = 293,              /* "{"  */
    RIGHT_BRACE = 294,             /* "}"  */
    LEFT_PARENTHESIS = 295,        /* "("  */
    RIGHT_PARENTHESIS = 296,       /* ")"  */
    SEMICOLON = 297,               /* ";"  */
    COMMA = 298,                   /* ","  */
    COLON = 299,                   /* ":"  */
    DOUBLE_COLON = 300,            /* "::"  */
    STOP = 301,                    /* "."  */
    DOUBLE_STOP = 302,             /* ".."  */
    UMINUS = 303                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "parser.y"

    char*   strVal;
    int     intVal;
	double  realVal;
	SymTableEntry* symEntr;
	idList* args;

#line 120 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_H_INCLUDED  */
