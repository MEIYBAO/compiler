
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "src/parser.y"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include "ast.hpp"

using namespace mc;

#ifndef YYLTYPE
typedef struct YYLTYPE {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
} YYLTYPE;
#define YYLTYPE_IS_DECLARED 1
#endif

extern int yylex(void);
extern int yylineno;
extern int yycolumn;
void yyerror(const char* msg);

Node* g_root = nullptr;

static SourcePos loc(const YYLTYPE& l) {
    return {l.first_line, l.first_column};
}


/* Line 189 of yacc.c  */
#line 105 "src/parser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

/* "%code requires" blocks.  */

/* Line 209 of yacc.c  */
#line 34 "src/parser.y"

  #include "ast.hpp"



/* Line 209 of yacc.c  */
#line 135 "src/parser.cpp"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     INTCONST = 259,
     KW_INT = 260,
     KW_IF = 261,
     KW_ELSE = 262,
     KW_WHILE = 263,
     KW_FOR = 264,
     KW_PRINTF = 265,
     KW_SCANF = 266,
     KW_RETURN = 267,
     PLUS = 268,
     MINUS = 269,
     MUL = 270,
     DIV = 271,
     MOD = 272,
     POW = 273,
     ASSIGN = 274,
     EQ = 275,
     NE = 276,
     GE = 277,
     LE = 278,
     GT = 279,
     LT = 280,
     AND = 281,
     OR = 282,
     NOT = 283,
     SEMI = 284,
     COMMA = 285,
     LPAREN = 286,
     RPAREN = 287,
     LBRACE = 288,
     RBRACE = 289,
     UMINUS = 290
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 38 "src/parser.y"

    int ival;
    char* sval;
    mc::Node* node;



/* Line 214 of yacc.c  */
#line 195 "src/parser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 220 "src/parser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   160

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  54
/* YYNRULES -- Number of states.  */
#define YYNSTATES  113

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      35
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    13,    14,    17,    20,    23,
      26,    30,    32,    34,    36,    38,    40,    44,    47,    49,
      53,    55,    59,    63,    68,    73,    79,    87,    93,   103,
     104,   106,   107,   109,   113,   117,   120,   124,   126,   128,
     132,   136,   140,   144,   148,   152,   156,   160,   164,   168,
     172,   176,   179,   183,   185
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      37,     0,    -1,    39,    -1,    38,    -1,     5,     3,    31,
      32,    41,    -1,    -1,    39,    40,    -1,    42,    29,    -1,
      45,    29,    -1,    46,    29,    -1,    12,    54,    29,    -1,
      47,    -1,    48,    -1,    49,    -1,    41,    -1,    29,    -1,
      33,    39,    34,    -1,     5,    43,    -1,    44,    -1,    43,
      30,    44,    -1,     3,    -1,     3,    19,    54,    -1,     3,
      19,    54,    -1,    10,    31,    54,    32,    -1,    11,    31,
       3,    32,    -1,     6,    31,    52,    32,    40,    -1,     6,
      31,    52,    32,    40,     7,    40,    -1,     8,    31,    52,
      32,    40,    -1,     9,    31,    51,    29,    50,    29,    51,
      32,    40,    -1,    -1,    52,    -1,    -1,    45,    -1,    52,
      27,    52,    -1,    52,    26,    52,    -1,    28,    52,    -1,
      31,    52,    32,    -1,    53,    -1,    54,    -1,    54,    25,
      54,    -1,    54,    23,    54,    -1,    54,    24,    54,    -1,
      54,    22,    54,    -1,    54,    20,    54,    -1,    54,    21,
      54,    -1,    54,    13,    54,    -1,    54,    14,    54,    -1,
      54,    15,    54,    -1,    54,    16,    54,    -1,    54,    17,
      54,    -1,    54,    18,    54,    -1,    14,    54,    -1,    31,
      54,    32,    -1,     3,    -1,     4,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    68,    68,    74,    83,    92,    93,   102,   103,   104,
     105,   109,   110,   111,   112,   113,   117,   125,   133,   134,
     143,   149,   164,   175,   180,   189,   195,   205,   214,   225,
     226,   230,   231,   235,   236,   237,   238,   239,   240,   244,
     245,   246,   247,   248,   249,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   266
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INTCONST", "KW_INT", "KW_IF",
  "KW_ELSE", "KW_WHILE", "KW_FOR", "KW_PRINTF", "KW_SCANF", "KW_RETURN",
  "PLUS", "MINUS", "MUL", "DIV", "MOD", "POW", "ASSIGN", "EQ", "NE", "GE",
  "LE", "GT", "LT", "AND", "OR", "NOT", "SEMI", "COMMA", "LPAREN",
  "RPAREN", "LBRACE", "RBRACE", "UMINUS", "$accept", "program", "func_def",
  "stmt_list", "stmt", "block", "decl", "init_list", "init_item", "assign",
  "io_stmt", "if_stmt", "while_stmt", "for_stmt", "opt_expr", "opt_assign",
  "bool_expr", "rel_expr", "expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    37,    38,    39,    39,    40,    40,    40,
      40,    40,    40,    40,    40,    40,    41,    42,    43,    43,
      44,    44,    45,    46,    46,    47,    47,    48,    49,    50,
      50,    51,    51,    52,    52,    52,    52,    52,    52,    53,
      53,    53,    53,    53,    53,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     5,     0,     2,     2,     2,     2,
       3,     1,     1,     1,     1,     1,     3,     2,     1,     3,
       1,     3,     3,     4,     4,     5,     7,     5,     9,     0,
       1,     0,     1,     3,     3,     2,     3,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     0,     0,     3,     2,     0,     1,     0,     0,     0,
       0,     0,     0,     0,     0,    15,     5,     6,    14,     0,
       0,     0,    11,    12,    13,     0,     0,    20,    17,    18,
       0,     0,    31,     0,     0,    53,    54,     0,     0,     0,
       0,     7,     8,     9,     0,    22,     0,     0,     0,     0,
       0,    37,    38,     0,    32,     0,     0,     0,    51,     0,
       0,     0,     0,     0,     0,     0,    10,    16,     4,    21,
      19,    35,     0,    38,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    29,    23,    24,    52,    45,    46,
      47,    48,    49,    50,    36,    34,    33,    25,    43,    44,
      42,    40,    41,    39,    27,     0,    30,     0,    31,    26,
       0,     0,    28
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     4,    17,    18,    19,    28,    29,    20,
      21,    22,    23,    24,   105,    55,    50,    51,    52
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -73
static const yytype_int16 yypact[] =
{
       0,     6,    21,   -73,    79,   -19,   -73,    -5,    19,    -2,
      -1,     1,     7,    11,    12,   -73,   -73,   -73,   -73,    -6,
       8,    15,   -73,   -73,   -73,    13,    12,    43,    31,   -73,
       3,     3,    70,    12,    80,   -73,   -73,    12,    12,    42,
      69,   -73,   -73,   -73,    37,   140,    12,    19,     3,     3,
     -24,   -73,   126,    14,   -73,    57,   113,    60,   -73,   120,
      12,    12,    12,    12,    12,    12,   -73,   -73,   -73,   140,
     -73,   -73,    67,   100,     3,     3,    79,    12,    12,    12,
      12,    12,    12,    79,     3,   -73,   -73,   -73,    89,    89,
      77,    77,    77,    77,   -73,   -73,    71,    93,   140,   140,
     140,   140,   140,   140,   -73,    72,    -8,    79,    70,   -73,
      64,    79,   -73
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -73,   -73,   -73,    94,   -72,    65,   -73,   -73,   112,   -32,
     -73,   -73,   -73,   -73,   -73,    52,   -21,   -73,   -13
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      54,    39,    74,    75,    97,     1,    35,    36,    76,     5,
      53,   104,    25,    45,    26,    35,    36,    37,    74,    75,
      56,     6,    27,    41,    58,    59,    37,    71,    72,    30,
      31,    48,    32,    69,    49,   109,    73,    42,    33,   112,
      74,    75,    34,    38,    43,    44,    83,    88,    89,    90,
      91,    92,    93,    95,    96,    60,    61,    62,    63,    64,
      65,    47,    46,   106,    98,    99,   100,   101,   102,   103,
      16,    66,     7,     7,     8,     9,    54,    10,    11,    12,
      13,    14,     7,    57,     8,     9,    84,    10,    11,    12,
      13,    14,    86,    74,    75,    65,   111,    74,    15,    94,
     107,   108,    16,    67,    62,    63,    64,    65,    15,    68,
      40,     0,    16,    60,    61,    62,    63,    64,    65,     0,
      77,    78,    79,    80,    81,    82,    60,    61,    62,    63,
      64,    65,    87,    60,    61,    62,    63,    64,    65,    60,
      61,    62,    63,    64,    65,    85,    77,    78,    79,    80,
      81,    82,    87,    60,    61,    62,    63,    64,    65,    70,
     110
};

static const yytype_int8 yycheck[] =
{
      32,    14,    26,    27,    76,     5,     3,     4,    32,     3,
      31,    83,    31,    26,    19,     3,     4,    14,    26,    27,
      33,     0,     3,    29,    37,    38,    14,    48,    49,    31,
      31,    28,    31,    46,    31,   107,    49,    29,    31,   111,
      26,    27,    31,    31,    29,    32,    32,    60,    61,    62,
      63,    64,    65,    74,    75,    13,    14,    15,    16,    17,
      18,    30,    19,    84,    77,    78,    79,    80,    81,    82,
      33,    29,     3,     3,     5,     6,   108,     8,     9,    10,
      11,    12,     3,     3,     5,     6,    29,     8,     9,    10,
      11,    12,    32,    26,    27,    18,    32,    26,    29,    32,
       7,    29,    33,    34,    15,    16,    17,    18,    29,    44,
      16,    -1,    33,    13,    14,    15,    16,    17,    18,    -1,
      20,    21,    22,    23,    24,    25,    13,    14,    15,    16,
      17,    18,    32,    13,    14,    15,    16,    17,    18,    13,
      14,    15,    16,    17,    18,    32,    20,    21,    22,    23,
      24,    25,    32,    13,    14,    15,    16,    17,    18,    47,
     108
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,    37,    38,    39,     3,     0,     3,     5,     6,
       8,     9,    10,    11,    12,    29,    33,    40,    41,    42,
      45,    46,    47,    48,    49,    31,    19,     3,    43,    44,
      31,    31,    31,    31,    31,     3,     4,    14,    31,    54,
      39,    29,    29,    29,    32,    54,    19,    30,    28,    31,
      52,    53,    54,    52,    45,    51,    54,     3,    54,    54,
      13,    14,    15,    16,    17,    18,    29,    34,    41,    54,
      44,    52,    52,    54,    26,    27,    32,    20,    21,    22,
      23,    24,    25,    32,    29,    32,    32,    32,    54,    54,
      54,    54,    54,    54,    32,    52,    52,    40,    54,    54,
      54,    54,    54,    54,    40,    50,    52,     7,    29,    40,
      51,    32,    40
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 69 "src/parser.y"
    {
      g_root = makeNode(NodeKind::Program, loc((yylsp[(1) - (1)])));
      if ((yyvsp[(1) - (1)].node)) g_root->children.push_back((yyvsp[(1) - (1)].node));
      (yyval.node) = g_root;
    ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 75 "src/parser.y"
    {
      g_root = makeNode(NodeKind::Program, loc((yylsp[(1) - (1)])));
      g_root->children.push_back((yyvsp[(1) - (1)].node));
      (yyval.node) = g_root;
    ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 84 "src/parser.y"
    {
      (yyval.node) = makeNode(NodeKind::Function, loc((yylsp[(1) - (5)])), (yyvsp[(2) - (5)].sval));
      (yyval.node)->children.push_back((yyvsp[(5) - (5)].node));
      free((yyvsp[(2) - (5)].sval));
    ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 92 "src/parser.y"
    { (yyval.node) = nullptr; ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 94 "src/parser.y"
    {
      if ((yyvsp[(1) - (2)].node) == nullptr) (yyval.node) = makeNode(NodeKind::StmtList, loc((yylsp[(2) - (2)])));
      else (yyval.node) = (yyvsp[(1) - (2)].node);
      if ((yyvsp[(2) - (2)].node)) (yyval.node)->children.push_back((yyvsp[(2) - (2)].node));
    ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 102 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 103 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 104 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 105 "src/parser.y"
    {
      (yyval.node) = makeNode(NodeKind::Return, loc((yylsp[(1) - (3)])));
      (yyval.node)->children.push_back((yyvsp[(2) - (3)].node));
    ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 109 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 110 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 111 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 112 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 113 "src/parser.y"
    { (yyval.node) = makeNode(NodeKind::Empty, loc((yylsp[(1) - (1)]))); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 118 "src/parser.y"
    {
      (yyval.node) = makeNode(NodeKind::Block, loc((yylsp[(1) - (3)])));
      if ((yyvsp[(2) - (3)].node)) (yyval.node)->children.push_back((yyvsp[(2) - (3)].node));
    ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 126 "src/parser.y"
    {
      (yyval.node) = makeNode(NodeKind::Decl, loc((yylsp[(1) - (2)])));
      if ((yyvsp[(2) - (2)].node)) (yyval.node)->children.push_back((yyvsp[(2) - (2)].node));
    ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 133 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 135 "src/parser.y"
    {
      (yyval.node) = (yyvsp[(1) - (3)].node);
      for (auto* ch : (yyvsp[(3) - (3)].node)->children) (yyval.node)->children.push_back(ch);
      delete (yyvsp[(3) - (3)].node);
    ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 144 "src/parser.y"
    {
      (yyval.node) = makeNode(NodeKind::VarList, loc((yylsp[(1) - (1)])));
      (yyval.node)->children.push_back(makeNode(NodeKind::Var, loc((yylsp[(1) - (1)])), (yyvsp[(1) - (1)].sval)));
      free((yyvsp[(1) - (1)].sval));
    ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 150 "src/parser.y"
    {
      (yyval.node) = makeNode(NodeKind::VarList, loc((yylsp[(1) - (3)])));
      mc::Node* v = makeNode(NodeKind::Var, loc((yylsp[(1) - (3)])), (yyvsp[(1) - (3)].sval));
      (yyval.node)->children.push_back(v);
      mc::Node* a = makeNode(NodeKind::Assign, loc((yylsp[(2) - (3)])));
      a->children.push_back(makeNode(NodeKind::Var, loc((yylsp[(1) - (3)])), (yyvsp[(1) - (3)].sval)));
      a->children.push_back((yyvsp[(3) - (3)].node));
      (yyval.node)->children.push_back(a);
      free((yyvsp[(1) - (3)].sval));
    ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 165 "src/parser.y"
    {
      Node* lhs = makeNode(NodeKind::Var, loc((yylsp[(1) - (3)])), (yyvsp[(1) - (3)].sval));
      (yyval.node) = makeNode(NodeKind::Assign, loc((yylsp[(2) - (3)])));
      (yyval.node)->children.push_back(lhs);
      (yyval.node)->children.push_back((yyvsp[(3) - (3)].node));
      free((yyvsp[(1) - (3)].sval));
    ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 176 "src/parser.y"
    {
      (yyval.node) = makeNode(NodeKind::Print, loc((yylsp[(1) - (4)])));
      (yyval.node)->children.push_back((yyvsp[(3) - (4)].node));
    ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 181 "src/parser.y"
    {
      (yyval.node) = makeNode(NodeKind::Scan, loc((yylsp[(1) - (4)])));
      (yyval.node)->children.push_back(makeNode(NodeKind::Var, loc((yylsp[(3) - (4)])), (yyvsp[(3) - (4)].sval)));
      free((yyvsp[(3) - (4)].sval));
    ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 190 "src/parser.y"
    {
      (yyval.node) = makeNode(NodeKind::If, loc((yylsp[(1) - (5)])));
      (yyval.node)->children.push_back((yyvsp[(3) - (5)].node));
      (yyval.node)->children.push_back((yyvsp[(5) - (5)].node));
    ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 196 "src/parser.y"
    {
      (yyval.node) = makeNode(NodeKind::If, loc((yylsp[(1) - (7)])));
      (yyval.node)->children.push_back((yyvsp[(3) - (7)].node));
      (yyval.node)->children.push_back((yyvsp[(5) - (7)].node));
      (yyval.node)->children.push_back((yyvsp[(7) - (7)].node));
    ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 206 "src/parser.y"
    {
      (yyval.node) = makeNode(NodeKind::While, loc((yylsp[(1) - (5)])));
      (yyval.node)->children.push_back((yyvsp[(3) - (5)].node));
      (yyval.node)->children.push_back((yyvsp[(5) - (5)].node));
    ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 215 "src/parser.y"
    {
      (yyval.node) = makeNode(NodeKind::For, loc((yylsp[(1) - (9)])));
      (yyval.node)->children.push_back((yyvsp[(3) - (9)].node) ? (yyvsp[(3) - (9)].node) : makeNode(NodeKind::Empty, loc((yylsp[(1) - (9)]))));
      (yyval.node)->children.push_back((yyvsp[(5) - (9)].node));
      (yyval.node)->children.push_back((yyvsp[(7) - (9)].node) ? (yyvsp[(7) - (9)].node) : makeNode(NodeKind::Empty, loc((yylsp[(1) - (9)]))));
      (yyval.node)->children.push_back((yyvsp[(9) - (9)].node));
    ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 225 "src/parser.y"
    { (yyval.node) = nullptr; ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 226 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 230 "src/parser.y"
    { (yyval.node) = nullptr; ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 231 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 235 "src/parser.y"
    { (yyval.node) = makeBinary("||", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), loc((yylsp[(2) - (3)]))); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 236 "src/parser.y"
    { (yyval.node) = makeBinary("&&", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), loc((yylsp[(2) - (3)]))); ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 237 "src/parser.y"
    { (yyval.node) = makeUnary("!", (yyvsp[(2) - (2)].node), loc((yylsp[(1) - (2)]))); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 238 "src/parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 239 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 240 "src/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 244 "src/parser.y"
    { (yyval.node) = makeBinary("<",  (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), loc((yylsp[(2) - (3)]))); ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 245 "src/parser.y"
    { (yyval.node) = makeBinary("<=", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), loc((yylsp[(2) - (3)]))); ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 246 "src/parser.y"
    { (yyval.node) = makeBinary(">",  (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), loc((yylsp[(2) - (3)]))); ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 247 "src/parser.y"
    { (yyval.node) = makeBinary(">=", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), loc((yylsp[(2) - (3)]))); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 248 "src/parser.y"
    { (yyval.node) = makeBinary("==", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), loc((yylsp[(2) - (3)]))); ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 249 "src/parser.y"
    { (yyval.node) = makeBinary("!=", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), loc((yylsp[(2) - (3)]))); ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 253 "src/parser.y"
    { (yyval.node) = makeBinary("+", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), loc((yylsp[(2) - (3)]))); ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 254 "src/parser.y"
    { (yyval.node) = makeBinary("-", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), loc((yylsp[(2) - (3)]))); ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 255 "src/parser.y"
    { (yyval.node) = makeBinary("*", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), loc((yylsp[(2) - (3)]))); ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 256 "src/parser.y"
    { (yyval.node) = makeBinary("/", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), loc((yylsp[(2) - (3)]))); ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 257 "src/parser.y"
    { (yyval.node) = makeBinary("%", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), loc((yylsp[(2) - (3)]))); ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 258 "src/parser.y"
    { (yyval.node) = makeBinary("^", (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node), loc((yylsp[(2) - (3)]))); ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 259 "src/parser.y"
    { (yyval.node) = makeUnary("NEG", (yyvsp[(2) - (2)].node), loc((yylsp[(1) - (2)]))); ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 260 "src/parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 262 "src/parser.y"
    {
      (yyval.node) = makeNode(NodeKind::Var, loc((yylsp[(1) - (1)])), (yyvsp[(1) - (1)].sval));
      free((yyvsp[(1) - (1)].sval));
    ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 267 "src/parser.y"
    {
      (yyval.node) = makeNode(NodeKind::IntLiteral, loc((yylsp[(1) - (1)])), std::to_string((yyvsp[(1) - (1)].ival)));
    ;}
    break;



/* Line 1455 of yacc.c  */
#line 2002 "src/parser.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

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
		      yytoken, &yylval, &yylloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 272 "src/parser.y"


void yyerror(const char* s) {
    fprintf(stderr, "Parse Error: %s at line %d, col %d\n", s, yylloc.first_line, yylloc.first_column);
}

