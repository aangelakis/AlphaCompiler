/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

	
	#include "yacc_utilities.h"
	
	int yylex();

	extern int yylineno;
	extern char* yytext;
	int scope = 0;
	int flag_scope = 0 ; // 0 == block ; 1 == function
    /* TODO */
    //int blocks_active = 0;
    //int nested_start_block_line[1024];


#line 87 "parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_STRING = 4,                     /* STRING  */
  YYSYMBOL_INT = 5,                        /* INT  */
  YYSYMBOL_DOUBLE = 6,                     /* DOUBLE  */
  YYSYMBOL_LE = 7,                         /* "<="  */
  YYSYMBOL_LT = 8,                         /* "<"  */
  YYSYMBOL_NE = 9,                         /* "!="  */
  YYSYMBOL_GE = 10,                        /* ">="  */
  YYSYMBOL_GT = 11,                        /* ">"  */
  YYSYMBOL_EQ = 12,                        /* "=="  */
  YYSYMBOL_ASSIGN = 13,                    /* "="  */
  YYSYMBOL_PLUS = 14,                      /* "+"  */
  YYSYMBOL_MINUS = 15,                     /* "-"  */
  YYSYMBOL_PLUS_PLUS = 16,                 /* "++"  */
  YYSYMBOL_MINUS_MINUS = 17,               /* "--"  */
  YYSYMBOL_MULT = 18,                      /* "*"  */
  YYSYMBOL_DIV = 19,                       /* "/"  */
  YYSYMBOL_MOD = 20,                       /* "%"  */
  YYSYMBOL_IF = 21,                        /* "if"  */
  YYSYMBOL_ELSE = 22,                      /* "else"  */
  YYSYMBOL_WHILE = 23,                     /* "while"  */
  YYSYMBOL_FOR = 24,                       /* "for"  */
  YYSYMBOL_FUNCTION = 25,                  /* "function"  */
  YYSYMBOL_RETURN = 26,                    /* "return"  */
  YYSYMBOL_BREAK = 27,                     /* "break"  */
  YYSYMBOL_CONTINUE = 28,                  /* "continue"  */
  YYSYMBOL_AND = 29,                       /* "and"  */
  YYSYMBOL_NOT = 30,                       /* "not"  */
  YYSYMBOL_OR = 31,                        /* "or"  */
  YYSYMBOL_LOCAL = 32,                     /* "local"  */
  YYSYMBOL_TRUE = 33,                      /* "true"  */
  YYSYMBOL_FALSE = 34,                     /* "false"  */
  YYSYMBOL_NIL = 35,                       /* "nil"  */
  YYSYMBOL_LEFT_BRACKET = 36,              /* "["  */
  YYSYMBOL_RIGHT_BRACKET = 37,             /* "]"  */
  YYSYMBOL_LEFT_BRACE = 38,                /* "{"  */
  YYSYMBOL_RIGHT_BRACE = 39,               /* "}"  */
  YYSYMBOL_LEFT_PARENTHESIS = 40,          /* "("  */
  YYSYMBOL_RIGHT_PARENTHESIS = 41,         /* ")"  */
  YYSYMBOL_SEMICOLON = 42,                 /* ";"  */
  YYSYMBOL_COMMA = 43,                     /* ","  */
  YYSYMBOL_COLON = 44,                     /* ":"  */
  YYSYMBOL_DOUBLE_COLON = 45,              /* "::"  */
  YYSYMBOL_STOP = 46,                      /* "."  */
  YYSYMBOL_DOUBLE_STOP = 47,               /* ".."  */
  YYSYMBOL_UMINUS = 48,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_program = 50,                   /* program  */
  YYSYMBOL_liststmt = 51,                  /* liststmt  */
  YYSYMBOL_stmt = 52,                      /* stmt  */
  YYSYMBOL_expr = 53,                      /* expr  */
  YYSYMBOL_term = 54,                      /* term  */
  YYSYMBOL_assignexpr = 55,                /* assignexpr  */
  YYSYMBOL_primary = 56,                   /* primary  */
  YYSYMBOL_lvalue = 57,                    /* lvalue  */
  YYSYMBOL_member = 58,                    /* member  */
  YYSYMBOL_call = 59,                      /* call  */
  YYSYMBOL_callsuffix = 60,                /* callsuffix  */
  YYSYMBOL_normcall = 61,                  /* normcall  */
  YYSYMBOL_methodcall = 62,                /* methodcall  */
  YYSYMBOL_elist = 63,                     /* elist  */
  YYSYMBOL_objectdef = 64,                 /* objectdef  */
  YYSYMBOL_indexed = 65,                   /* indexed  */
  YYSYMBOL_indexedelem = 66,               /* indexedelem  */
  YYSYMBOL_block = 67,                     /* block  */
  YYSYMBOL_68_1 = 68,                      /* $@1  */
  YYSYMBOL_69_2 = 69,                      /* $@2  */
  YYSYMBOL_70_3 = 70,                      /* $@3  */
  YYSYMBOL_71_4 = 71,                      /* $@4  */
  YYSYMBOL_funcdef = 72,                   /* funcdef  */
  YYSYMBOL_73_5 = 73,                      /* $@5  */
  YYSYMBOL_74_6 = 74,                      /* $@6  */
  YYSYMBOL_const = 75,                     /* const  */
  YYSYMBOL_idlist = 76,                    /* idlist  */
  YYSYMBOL_ifstmt = 77,                    /* ifstmt  */
  YYSYMBOL_whilestmt = 78,                 /* whilestmt  */
  YYSYMBOL_forstmt = 79,                   /* forstmt  */
  YYSYMBOL_returnstmt = 80                 /* returnstmt  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  69
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   688

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  92
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  176

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   303


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   124,   124,   125,   128,   129,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   161,   162,   163,   164,   165,   166,   167,   168,   171,
     173,   174,   175,   176,   177,   180,   181,   182,   183,   186,
     187,   188,   189,   192,   193,   194,   197,   198,   201,   203,
     205,   206,   207,   210,   211,   214,   215,   218,   220,   220,
     220,   221,   221,   221,   224,   224,   225,   225,   228,   229,
     230,   231,   232,   233,   236,   237,   238,   241,   242,   245,
     247,   249,   250
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "STRING", "INT",
  "DOUBLE", "\"<=\"", "\"<\"", "\"!=\"", "\">=\"", "\">\"", "\"==\"",
  "\"=\"", "\"+\"", "\"-\"", "\"++\"", "\"--\"", "\"*\"", "\"/\"", "\"%\"",
  "\"if\"", "\"else\"", "\"while\"", "\"for\"", "\"function\"",
  "\"return\"", "\"break\"", "\"continue\"", "\"and\"", "\"not\"",
  "\"or\"", "\"local\"", "\"true\"", "\"false\"", "\"nil\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"(\"", "\")\"", "\";\"", "\",\"", "\":\"",
  "\"::\"", "\".\"", "\"..\"", "UMINUS", "$accept", "program", "liststmt",
  "stmt", "expr", "term", "assignexpr", "primary", "lvalue", "member",
  "call", "callsuffix", "normcall", "methodcall", "elist", "objectdef",
  "indexed", "indexedelem", "block", "$@1", "$@2", "$@3", "$@4", "funcdef",
  "$@5", "$@6", "const", "idlist", "ifstmt", "whilestmt", "forstmt",
  "returnstmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-140)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-72)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     190,  -140,  -140,  -140,  -140,   309,     1,     1,   -29,   -26,
      11,    44,    89,    19,    20,   309,    79,  -140,  -140,  -140,
     233,    47,   271,  -140,    85,   101,   190,  -140,   375,  -140,
    -140,  -140,   -11,  -140,   -24,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,    82,   -27,   -24,   -27,   309,   309,
     309,  -140,    68,  -140,   400,  -140,  -140,  -140,  -140,   309,
     613,   -16,    -9,  -140,   190,    70,   450,    75,  -140,  -140,
    -140,   309,   309,   309,   309,   309,   309,   309,   309,   309,
     309,   309,   309,   309,  -140,   309,  -140,  -140,   309,   309,
     115,   117,  -140,  -140,  -140,   309,   309,   123,    86,   475,
     500,   -19,    88,   127,  -140,   348,  -140,   309,  -140,    94,
     147,  -140,  -140,    96,    45,    45,   654,    45,    45,   654,
      95,    95,  -140,  -140,  -140,   668,   638,   613,   551,    -4,
    -140,    99,   582,    -3,  -140,    96,   190,   190,   309,   127,
    -140,     7,   309,   613,  -140,  -140,  -140,   309,  -140,  -140,
     309,  -140,  -140,   113,  -140,   425,    38,   102,   138,   525,
    -140,    46,    55,   190,   309,   102,  -140,  -140,  -140,  -140,
    -140,  -140,    56,  -140,   190,  -140
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    45,    80,    78,    79,     0,     0,     0,     0,     0,
       0,    76,     0,     0,     0,     0,     0,    82,    83,    81,
      60,    68,     0,    15,     0,     0,     2,     5,     0,    17,
      16,    38,    40,    48,    41,    42,    13,    14,    44,     7,
       8,     9,    10,    32,     0,    34,     0,    36,     0,     0,
      60,    74,     0,    92,     0,    11,    12,    33,    46,     0,
      62,     0,     0,    66,     0,     0,     0,     0,    47,     1,
       4,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,     0,    35,    37,     0,    60,
       0,     0,    54,    56,    57,     0,    60,     0,     0,     0,
       0,     0,     0,    84,    91,     0,    63,     0,    64,     0,
       0,    72,    31,    43,    25,    26,    28,    23,    24,    27,
      18,    19,    20,    21,    22,    29,    30,    39,     0,     0,
      49,     0,     0,     0,    51,     0,     0,     0,     0,    84,
      86,     0,     0,    61,    65,    69,    73,    60,    50,    58,
      60,    52,    53,    88,    89,     0,     0,     0,     0,     0,
      70,     0,     0,     0,    60,     0,    77,    85,    67,    55,
      59,    87,     0,    75,     0,    90
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -140,  -140,    80,   -25,    -5,  -140,  -140,  -140,    25,  -140,
      51,  -140,  -140,  -140,   -47,  -140,  -140,    34,  -139,  -140,
    -140,  -140,  -140,   -14,  -140,  -140,  -140,     8,  -140,  -140,
    -140,  -140
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    92,    93,    94,    61,    35,    62,    63,    36,    64,
     160,    65,   146,    37,   102,    52,    38,   141,    39,    40,
      41,    42
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,    70,    85,   101,     1,    86,    87,    54,    67,    88,
      57,    48,    95,    89,    49,    60,    96,    66,   166,    90,
      91,   106,    97,   138,   107,    88,   173,   107,   108,    89,
      98,    45,    47,    16,   109,    90,    91,   149,   152,   107,
     107,    44,   129,    99,   100,    60,    24,    51,   157,   133,
     158,    50,   -72,   -72,   105,   -72,   -72,    46,    46,    77,
      78,    55,    56,    79,    80,    81,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   165,
     127,   158,    58,   128,    60,    70,   -71,   169,    68,   107,
     132,    60,     1,     2,     3,     4,   170,   174,   107,   107,
     161,    69,   143,   162,     5,     6,     7,    11,   103,   111,
      78,   153,   154,    79,    80,    81,   113,   172,   130,    15,
     131,    16,    17,    18,    19,    20,   134,   135,   139,    22,
     140,    53,    59,   155,    24,   163,   147,   159,   171,   150,
      21,   167,    60,   144,   110,    60,     0,   156,     0,   175,
       1,     2,     3,     4,     0,     0,     0,     0,     0,    60,
       0,     0,     5,     6,     7,     0,     0,     0,     8,     0,
       9,    10,    11,    12,    13,    14,     0,    15,     0,    16,
      17,    18,    19,    20,     0,    21,   145,    22,     0,    23,
       0,     0,    24,     1,     2,     3,     4,     0,     0,     0,
       0,     0,     0,     0,     0,     5,     6,     7,     0,     0,
       0,     8,     0,     9,    10,    11,    12,    13,    14,     0,
      15,     0,    16,    17,    18,    19,    20,     0,    21,     0,
      22,     0,    23,     0,     0,    24,     1,     2,     3,     4,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    15,     0,    16,    17,    18,    19,    20,
       0,    59,     0,    22,     1,     2,     3,     4,    24,     0,
       0,     0,     0,     0,     0,     0,     5,     6,     7,     0,
       0,     0,     0,     0,     0,     0,    11,     0,     0,     0,
       0,    15,     0,    16,    17,    18,    19,    20,     0,     0,
       0,    22,     1,     2,     3,     4,    24,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    15,
       0,    16,    17,    18,    19,    20,     0,     0,     0,    22,
       0,     0,     0,     0,    24,    71,    72,    73,    74,    75,
      76,     0,    77,    78,     0,     0,    79,    80,    81,     0,
       0,     0,     0,     0,     0,     0,     0,    82,     0,    83,
       0,     0,    71,    72,    73,    74,    75,    76,     0,    77,
      78,     0,   142,    79,    80,    81,     0,     0,     0,     0,
       0,     0,     0,     0,    82,     0,    83,    71,    72,    73,
      74,    75,    76,     0,    77,    78,     0,    84,    79,    80,
      81,     0,     0,     0,     0,     0,     0,     0,     0,    82,
       0,    83,    71,    72,    73,    74,    75,    76,     0,    77,
      78,     0,   104,    79,    80,    81,     0,     0,     0,     0,
       0,     0,     0,     0,    82,     0,    83,    71,    72,    73,
      74,    75,    76,     0,    77,    78,     0,   164,    79,    80,
      81,     0,     0,     0,     0,     0,     0,     0,     0,    82,
       0,    83,    71,    72,    73,    74,    75,    76,     0,    77,
      78,   112,     0,    79,    80,    81,     0,     0,     0,     0,
       0,     0,     0,     0,    82,     0,    83,    71,    72,    73,
      74,    75,    76,     0,    77,    78,   136,     0,    79,    80,
      81,     0,     0,     0,     0,     0,     0,     0,     0,    82,
       0,    83,    71,    72,    73,    74,    75,    76,     0,    77,
      78,   137,     0,    79,    80,    81,     0,     0,     0,     0,
       0,     0,     0,     0,    82,     0,    83,     0,    71,    72,
      73,    74,    75,    76,   168,    77,    78,     0,     0,    79,
      80,    81,     0,     0,     0,     0,     0,     0,     0,     0,
      82,     0,    83,     0,     0,     0,     0,     0,   148,    71,
      72,    73,    74,    75,    76,     0,    77,    78,     0,     0,
      79,    80,    81,     0,     0,     0,     0,     0,     0,     0,
       0,    82,     0,    83,     0,     0,     0,     0,     0,   151,
      71,    72,    73,    74,    75,    76,     0,    77,    78,     0,
       0,    79,    80,    81,     0,     0,     0,     0,     0,     0,
       0,     0,    82,     0,    83,    71,    72,    73,    74,    75,
      76,     0,    77,    78,     0,     0,    79,    80,    81,     0,
       0,    71,    72,   -72,    74,    75,   -72,    82,    77,    78,
       0,     0,    79,    80,    81,    71,    72,    73,    74,    75,
      76,     0,    77,    78,     0,     0,    79,    80,    81
};

static const yytype_int16 yycheck[] =
{
       5,    26,    13,    50,     3,    16,    17,    12,    22,    36,
      15,    40,    36,    40,    40,    20,    40,    22,   157,    46,
      47,    37,    46,    42,    43,    36,   165,    43,    37,    40,
      44,     6,     7,    32,    43,    46,    47,    41,    41,    43,
      43,    40,    89,    48,    49,    50,    45,     3,    41,    96,
      43,    40,     7,     8,    59,    10,    11,     6,     7,    14,
      15,    42,    42,    18,    19,    20,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    41,
      85,    43,     3,    88,    89,   110,    39,    41,     3,    43,
      95,    96,     3,     4,     5,     6,    41,    41,    43,    43,
     147,     0,   107,   150,    15,    16,    17,    25,    40,    39,
      15,   136,   137,    18,    19,    20,    41,   164,     3,    30,
       3,    32,    33,    34,    35,    36,     3,    41,    40,    40,
       3,    42,    38,   138,    45,    22,    40,   142,   163,    40,
      38,     3,   147,   109,    64,   150,    -1,   139,    -1,   174,
       3,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,   164,
      -1,    -1,    15,    16,    17,    -1,    -1,    -1,    21,    -1,
      23,    24,    25,    26,    27,    28,    -1,    30,    -1,    32,
      33,    34,    35,    36,    -1,    38,    39,    40,    -1,    42,
      -1,    -1,    45,     3,     4,     5,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    15,    16,    17,    -1,    -1,
      -1,    21,    -1,    23,    24,    25,    26,    27,    28,    -1,
      30,    -1,    32,    33,    34,    35,    36,    -1,    38,    -1,
      40,    -1,    42,    -1,    -1,    45,     3,     4,     5,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    32,    33,    34,    35,    36,
      -1,    38,    -1,    40,     3,     4,     5,     6,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,
      -1,    30,    -1,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    40,     3,     4,     5,     6,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    32,    33,    34,    35,    36,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    45,     7,     8,     9,    10,    11,
      12,    -1,    14,    15,    -1,    -1,    18,    19,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,
      -1,    -1,     7,     8,     9,    10,    11,    12,    -1,    14,
      15,    -1,    44,    18,    19,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    31,     7,     8,     9,
      10,    11,    12,    -1,    14,    15,    -1,    42,    18,    19,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    31,     7,     8,     9,    10,    11,    12,    -1,    14,
      15,    -1,    42,    18,    19,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    31,     7,     8,     9,
      10,    11,    12,    -1,    14,    15,    -1,    42,    18,    19,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    31,     7,     8,     9,    10,    11,    12,    -1,    14,
      15,    41,    -1,    18,    19,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    31,     7,     8,     9,
      10,    11,    12,    -1,    14,    15,    41,    -1,    18,    19,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    31,     7,     8,     9,    10,    11,    12,    -1,    14,
      15,    41,    -1,    18,    19,    20,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    31,    -1,     7,     8,
       9,    10,    11,    12,    39,    14,    15,    -1,    -1,    18,
      19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    -1,    31,    -1,    -1,    -1,    -1,    -1,    37,     7,
       8,     9,    10,    11,    12,    -1,    14,    15,    -1,    -1,
      18,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    29,    -1,    31,    -1,    -1,    -1,    -1,    -1,    37,
       7,     8,     9,    10,    11,    12,    -1,    14,    15,    -1,
      -1,    18,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    -1,    31,     7,     8,     9,    10,    11,
      12,    -1,    14,    15,    -1,    -1,    18,    19,    20,    -1,
      -1,     7,     8,     9,    10,    11,    12,    29,    14,    15,
      -1,    -1,    18,    19,    20,     7,     8,     9,    10,    11,
      12,    -1,    14,    15,    -1,    -1,    18,    19,    20
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,    15,    16,    17,    21,    23,
      24,    25,    26,    27,    28,    30,    32,    33,    34,    35,
      36,    38,    40,    42,    45,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    64,    67,    72,    75,    77,
      78,    79,    80,    53,    40,    57,    59,    57,    40,    40,
      40,     3,    74,    42,    53,    42,    42,    53,     3,    38,
      53,    63,    65,    66,    68,    70,    53,    72,     3,     0,
      52,     7,     8,     9,    10,    11,    12,    14,    15,    18,
      19,    20,    29,    31,    42,    13,    16,    17,    36,    40,
      46,    47,    60,    61,    62,    36,    40,    46,    72,    53,
      53,    63,    73,    40,    42,    53,    37,    43,    37,    43,
      51,    39,    41,    41,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    63,
       3,     3,    53,    63,     3,    41,    41,    41,    42,    40,
       3,    76,    44,    53,    66,    39,    71,    40,    37,    41,
      40,    37,    41,    52,    52,    53,    76,    41,    43,    53,
      69,    63,    63,    22,    42,    41,    67,     3,    39,    41,
      41,    52,    63,    67,    41,    52
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    50,    51,    51,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    54,    54,    54,    54,    54,    54,    54,    54,    55,
      56,    56,    56,    56,    56,    57,    57,    57,    57,    58,
      58,    58,    58,    59,    59,    59,    60,    60,    61,    62,
      63,    63,    63,    64,    64,    65,    65,    66,    68,    69,
      67,    70,    71,    67,    73,    72,    74,    72,    75,    75,
      75,    75,    75,    75,    76,    76,    76,    77,    77,    78,
      79,    80,    80
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     2,     2,     2,     1,     3,
       1,     1,     1,     3,     1,     1,     2,     2,     1,     3,
       4,     3,     4,     4,     2,     6,     1,     1,     3,     5,
       0,     3,     1,     3,     3,     3,     1,     5,     0,     0,
       5,     0,     0,     4,     0,     7,     0,     6,     1,     1,
       1,     1,     1,     1,     0,     3,     1,     7,     5,     5,
       9,     3,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: liststmt  */
#line 124 "parser.y"
                    {   Manage_program_liststmt();      }
#line 1376 "parser.c"
    break;

  case 3: /* program: %empty  */
#line 125 "parser.y"
                    {   Manage_program_empty();         }
#line 1382 "parser.c"
    break;

  case 4: /* liststmt: liststmt stmt  */
#line 128 "parser.y"
                        {  Manage_liststmt_liststmtStmt();      }
#line 1388 "parser.c"
    break;

  case 5: /* liststmt: stmt  */
#line 129 "parser.y"
                        {   Manage_liststmt_stmt();             }
#line 1394 "parser.c"
    break;

  case 6: /* stmt: expr ";"  */
#line 132 "parser.y"
                    {   Manage_stmt_expr();         }
#line 1400 "parser.c"
    break;

  case 7: /* stmt: ifstmt  */
#line 133 "parser.y"
                    {   Manage_stmt_ifstmt();       }
#line 1406 "parser.c"
    break;

  case 8: /* stmt: whilestmt  */
#line 134 "parser.y"
                    {   Manage_stmt_whilestmt();    }
#line 1412 "parser.c"
    break;

  case 9: /* stmt: forstmt  */
#line 135 "parser.y"
                    {   Manage_stmt_forstmt();      }
#line 1418 "parser.c"
    break;

  case 10: /* stmt: returnstmt  */
#line 136 "parser.y"
                    {   Manage_stmt_returnstmt();   }
#line 1424 "parser.c"
    break;

  case 11: /* stmt: "break" ";"  */
#line 137 "parser.y"
                    {   Manage_stmt_break();        }
#line 1430 "parser.c"
    break;

  case 12: /* stmt: "continue" ";"  */
#line 138 "parser.y"
                    {   Manage_stmt_continue();     }
#line 1436 "parser.c"
    break;

  case 13: /* stmt: block  */
#line 139 "parser.y"
                    {   Manage_stmt_block();        }
#line 1442 "parser.c"
    break;

  case 14: /* stmt: funcdef  */
#line 140 "parser.y"
                    {   Manage_stmt_funcdef();      }
#line 1448 "parser.c"
    break;

  case 15: /* stmt: ";"  */
#line 141 "parser.y"
                    {   Manage_stmt_semicolon();    }
#line 1454 "parser.c"
    break;

  case 16: /* expr: assignexpr  */
#line 144 "parser.y"
                          {     Manage_expr_assignexpr();       }
#line 1460 "parser.c"
    break;

  case 17: /* expr: term  */
#line 145 "parser.y"
                          {     Manage_expr_term();             }
#line 1466 "parser.c"
    break;

  case 18: /* expr: expr "+" expr  */
#line 146 "parser.y"
                          {     Manage_expr_exprOPexpr("+");    }
#line 1472 "parser.c"
    break;

  case 19: /* expr: expr "-" expr  */
#line 147 "parser.y"
                          {     Manage_expr_exprOPexpr("-");    }
#line 1478 "parser.c"
    break;

  case 20: /* expr: expr "*" expr  */
#line 148 "parser.y"
                          {     Manage_expr_exprOPexpr("*");    }
#line 1484 "parser.c"
    break;

  case 21: /* expr: expr "/" expr  */
#line 149 "parser.y"
                          {     Manage_expr_exprOPexpr("/");    }
#line 1490 "parser.c"
    break;

  case 22: /* expr: expr "%" expr  */
#line 150 "parser.y"
                          {     Manage_expr_exprOPexpr("%");    }
#line 1496 "parser.c"
    break;

  case 23: /* expr: expr ">=" expr  */
#line 151 "parser.y"
                          {     Manage_expr_exprOPexpr(">=");   }
#line 1502 "parser.c"
    break;

  case 24: /* expr: expr ">" expr  */
#line 152 "parser.y"
                          {     Manage_expr_exprOPexpr(">");    }
#line 1508 "parser.c"
    break;

  case 25: /* expr: expr "<=" expr  */
#line 153 "parser.y"
                          {     Manage_expr_exprOPexpr("<=");   }
#line 1514 "parser.c"
    break;

  case 26: /* expr: expr "<" expr  */
#line 154 "parser.y"
                          {     Manage_expr_exprOPexpr("<");    }
#line 1520 "parser.c"
    break;

  case 27: /* expr: expr "==" expr  */
#line 155 "parser.y"
                          {     Manage_expr_exprOPexpr("==");   }
#line 1526 "parser.c"
    break;

  case 28: /* expr: expr "!=" expr  */
#line 156 "parser.y"
                          {     Manage_expr_exprOPexpr("!=");   }
#line 1532 "parser.c"
    break;

  case 29: /* expr: expr "and" expr  */
#line 157 "parser.y"
                          {     Manage_expr_exprOPexpr("and");  }
#line 1538 "parser.c"
    break;

  case 30: /* expr: expr "or" expr  */
#line 158 "parser.y"
                          {     Manage_expr_exprOPexpr("or");   }
#line 1544 "parser.c"
    break;

  case 31: /* term: "(" expr ")"  */
#line 161 "parser.y"
                                {   Manage_term_expr();                 }
#line 1550 "parser.c"
    break;

  case 32: /* term: "-" expr  */
#line 162 "parser.y"
                                {   Manage_term_uminusExpr();           }
#line 1556 "parser.c"
    break;

  case 33: /* term: "not" expr  */
#line 163 "parser.y"
                                {   Manage_term_notExpr();              }
#line 1562 "parser.c"
    break;

  case 34: /* term: "++" lvalue  */
#line 164 "parser.y"
                                {   Manage_term_pluspluslvalue((yyvsp[0].symEntr));       }
#line 1568 "parser.c"
    break;

  case 35: /* term: lvalue "++"  */
#line 165 "parser.y"
                                {   Manage_term_lvalueplusplus((yyvsp[-1].symEntr));       }
#line 1574 "parser.c"
    break;

  case 36: /* term: "--" lvalue  */
#line 166 "parser.y"
                                {   Manage_term_minusminuslvalue((yyvsp[0].symEntr));     }
#line 1580 "parser.c"
    break;

  case 37: /* term: lvalue "--"  */
#line 167 "parser.y"
                                {   Manage_term_lvalueminusminus((yyvsp[-1].symEntr));     }
#line 1586 "parser.c"
    break;

  case 38: /* term: primary  */
#line 168 "parser.y"
                                {   Manage_term_primary();              }
#line 1592 "parser.c"
    break;

  case 39: /* assignexpr: lvalue "=" expr  */
#line 171 "parser.y"
                                {   Manage_assignexpr((yyvsp[-2].symEntr));  }
#line 1598 "parser.c"
    break;

  case 40: /* primary: lvalue  */
#line 173 "parser.y"
                            {   Manage_primary_lvalue();      }
#line 1604 "parser.c"
    break;

  case 41: /* primary: call  */
#line 174 "parser.y"
                            {   Manage_primary_call();        }
#line 1610 "parser.c"
    break;

  case 42: /* primary: objectdef  */
#line 175 "parser.y"
                            {   Manage_primary_objectdef();   }
#line 1616 "parser.c"
    break;

  case 43: /* primary: "(" funcdef ")"  */
#line 176 "parser.y"
                            {   Manage_primary_funcdef();     }
#line 1622 "parser.c"
    break;

  case 44: /* primary: const  */
#line 177 "parser.y"
                            {   Manage_primary_const();       }
#line 1628 "parser.c"
    break;

  case 45: /* lvalue: ID  */
#line 180 "parser.y"
                              { Manage_lvalue_id(&((yyval.symEntr)), (yyvsp[0].strVal), scope, yylineno);         }
#line 1634 "parser.c"
    break;

  case 46: /* lvalue: "local" ID  */
#line 181 "parser.y"
                              { Manage_lvalue_localID(&((yyval.symEntr)), (yyvsp[0].strVal), scope, yylineno);    }
#line 1640 "parser.c"
    break;

  case 47: /* lvalue: "::" ID  */
#line 182 "parser.y"
                              { Manage_lvalue_globalID(&((yyval.symEntr)), (yyvsp[0].strVal));                    }
#line 1646 "parser.c"
    break;

  case 48: /* lvalue: member  */
#line 183 "parser.y"
                              { Manage_lvalue_member();                            }
#line 1652 "parser.c"
    break;

  case 49: /* member: lvalue "." ID  */
#line 186 "parser.y"
                                {   Manage_member_lvalueID();   }
#line 1658 "parser.c"
    break;

  case 50: /* member: lvalue "[" expr "]"  */
#line 187 "parser.y"
                                {   Manage_member_lvalueExpr(); }
#line 1664 "parser.c"
    break;

  case 51: /* member: call "." ID  */
#line 188 "parser.y"
                                {   Manage_member_callID();     }
#line 1670 "parser.c"
    break;

  case 52: /* member: call "[" expr "]"  */
#line 189 "parser.y"
                                {   Manage_member_callExpr();   }
#line 1676 "parser.c"
    break;

  case 53: /* call: call "(" elist ")"  */
#line 192 "parser.y"
                                         {  Manage_call_callElist();        }
#line 1682 "parser.c"
    break;

  case 54: /* call: lvalue callsuffix  */
#line 193 "parser.y"
                                         {  Manage_call_lvalueCallsuffix((yyvsp[-1].symEntr)); }
#line 1688 "parser.c"
    break;

  case 55: /* call: "(" funcdef ")" "(" elist ")"  */
#line 194 "parser.y"
                                         {  Manage_call_funcdefElist();     }
#line 1694 "parser.c"
    break;

  case 56: /* callsuffix: normcall  */
#line 197 "parser.y"
                          { Manage_callsuffix_normcall();     }
#line 1700 "parser.c"
    break;

  case 57: /* callsuffix: methodcall  */
#line 198 "parser.y"
                          { Manage_callsuffix_methodcall();   }
#line 1706 "parser.c"
    break;

  case 58: /* normcall: "(" elist ")"  */
#line 201 "parser.y"
                            {   Manage_normcall();    }
#line 1712 "parser.c"
    break;

  case 59: /* methodcall: ".." ID "(" elist ")"  */
#line 203 "parser.y"
                                            {   Manage_methodcall();  }
#line 1718 "parser.c"
    break;

  case 60: /* elist: %empty  */
#line 205 "parser.y"
                          {     Manage_elist_empty();           }
#line 1724 "parser.c"
    break;

  case 61: /* elist: elist "," expr  */
#line 206 "parser.y"
                          {     Manage_elist_elistExpr();       }
#line 1730 "parser.c"
    break;

  case 62: /* elist: expr  */
#line 207 "parser.y"
                          {     Manage_elist_expr();            }
#line 1736 "parser.c"
    break;

  case 63: /* objectdef: "[" elist "]"  */
#line 210 "parser.y"
                              {     Manage_objectdef_elist();   }
#line 1742 "parser.c"
    break;

  case 64: /* objectdef: "[" indexed "]"  */
#line 211 "parser.y"
                              {     Manage_objectdef_indexed(); }
#line 1748 "parser.c"
    break;

  case 65: /* indexed: indexed "," indexedelem  */
#line 214 "parser.y"
                                    {   Manage_indexed_indexedIndexedelem(); }
#line 1754 "parser.c"
    break;

  case 66: /* indexed: indexedelem  */
#line 215 "parser.y"
                                    {   Manage_indexed_indexedelem();        }
#line 1760 "parser.c"
    break;

  case 67: /* indexedelem: "{" expr ":" expr "}"  */
#line 218 "parser.y"
                                    {   Manage_indexedelem(); }
#line 1766 "parser.c"
    break;

  case 68: /* $@1: %empty  */
#line 220 "parser.y"
           {ScopeUp(0);}
#line 1772 "parser.c"
    break;

  case 69: /* $@2: %empty  */
#line 220 "parser.y"
                                      {ScopeDown(0);}
#line 1778 "parser.c"
    break;

  case 70: /* block: "{" $@1 liststmt "}" $@2  */
#line 220 "parser.y"
                                                      {   Manage_block_liststmt();    }
#line 1784 "parser.c"
    break;

  case 71: /* $@3: %empty  */
#line 221 "parser.y"
               {ScopeUp(0);}
#line 1790 "parser.c"
    break;

  case 72: /* $@4: %empty  */
#line 221 "parser.y"
                                 {ScopeDown(0);}
#line 1796 "parser.c"
    break;

  case 73: /* block: "{" $@3 "}" $@4  */
#line 221 "parser.y"
                                                       {  Manage_block_emptyblock();   }
#line 1802 "parser.c"
    break;

  case 74: /* $@5: %empty  */
#line 224 "parser.y"
                     {ScopeUp(1);}
#line 1808 "parser.c"
    break;

  case 75: /* funcdef: "function" ID $@5 "(" idlist ")" block  */
#line 224 "parser.y"
                                                      {  Manage_funcdef_functionId((yyvsp[-5].strVal),(yyvsp[-2].args)); }
#line 1814 "parser.c"
    break;

  case 76: /* $@6: %empty  */
#line 225 "parser.y"
                  {ScopeUp(1);}
#line 1820 "parser.c"
    break;

  case 77: /* funcdef: "function" $@6 "(" idlist ")" block  */
#line 225 "parser.y"
                                                     {   Manage_funcdef_function((yyvsp[-2].args));   }
#line 1826 "parser.c"
    break;

  case 78: /* const: INT  */
#line 228 "parser.y"
                  { Manage_const_number();    }
#line 1832 "parser.c"
    break;

  case 79: /* const: DOUBLE  */
#line 229 "parser.y"
                  { Manage_const_number();    }
#line 1838 "parser.c"
    break;

  case 80: /* const: STRING  */
#line 230 "parser.y"
                  { Manage_const_string();    }
#line 1844 "parser.c"
    break;

  case 81: /* const: "nil"  */
#line 231 "parser.y"
                  { Manage_const_nil();       }
#line 1850 "parser.c"
    break;

  case 82: /* const: "true"  */
#line 232 "parser.y"
                  { Manage_const_true();      }
#line 1856 "parser.c"
    break;

  case 83: /* const: "false"  */
#line 233 "parser.y"
                  { Manage_const_false();     }
#line 1862 "parser.c"
    break;

  case 84: /* idlist: %empty  */
#line 236 "parser.y"
                        {   Manage_idlist_empty(&((yyval.args)));      }
#line 1868 "parser.c"
    break;

  case 85: /* idlist: idlist "," ID  */
#line 237 "parser.y"
                        {   Manage_idlist_idlistId(&((yyval.args)),(yyvsp[-2].args),(yyvsp[0].strVal));   }
#line 1874 "parser.c"
    break;

  case 86: /* idlist: ID  */
#line 238 "parser.y"
                        {   Manage_idlist_id(&((yyval.args)),(yyvsp[0].strVal));         }
#line 1880 "parser.c"
    break;

  case 87: /* ifstmt: "if" "(" expr ")" stmt "else" stmt  */
#line 241 "parser.y"
                                       {   Manage_ifstmt_ifelse();  }
#line 1886 "parser.c"
    break;

  case 88: /* ifstmt: "if" "(" expr ")" stmt  */
#line 242 "parser.y"
                                       {    Manage_ifstmt_if();     }
#line 1892 "parser.c"
    break;

  case 89: /* whilestmt: "while" "(" expr ")" stmt  */
#line 245 "parser.y"
                                        {    Manage_whilestmt();  }
#line 1898 "parser.c"
    break;

  case 90: /* forstmt: "for" "(" elist ";" expr ";" elist ")" stmt  */
#line 247 "parser.y"
                                                    {   Manage_forstmt();  }
#line 1904 "parser.c"
    break;

  case 91: /* returnstmt: "return" expr ";"  */
#line 249 "parser.y"
                            {   Manage_returnstmt_returnexpr(); }
#line 1910 "parser.c"
    break;

  case 92: /* returnstmt: "return" ";"  */
#line 250 "parser.y"
                            {   Manage_returnstmt_return();     }
#line 1916 "parser.c"
    break;


#line 1920 "parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 253 "parser.y"


