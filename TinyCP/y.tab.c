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
#line 1 "compiler.y"

#include <cstdlib>
#include <cstdio>
#include <string>
#include "tree.h"
#include "block.h"
#include "Praser.h"
using namespace std;

extern char *yytext;
extern int column;
extern FILE * yyin;
extern FILE * yyout;
gramTree *root;
extern int yylineno;

int yylex(void);
void yyerror(const char*); 

#line 91 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
    IDENTIFIER = 258,              /* IDENTIFIER  */
    CONSTANT = 259,                /* CONSTANT  */
    STRING_LITERAL = 260,          /* STRING_LITERAL  */
    SIZEOF = 261,                  /* SIZEOF  */
    CONSTANT_INT = 262,            /* CONSTANT_INT  */
    CONSTANT_DOUBLE = 263,         /* CONSTANT_DOUBLE  */
    PTR_OP = 264,                  /* PTR_OP  */
    INC_OP = 265,                  /* INC_OP  */
    DEC_OP = 266,                  /* DEC_OP  */
    LEFT_OP = 267,                 /* LEFT_OP  */
    RIGHT_OP = 268,                /* RIGHT_OP  */
    LE_OP = 269,                   /* LE_OP  */
    GE_OP = 270,                   /* GE_OP  */
    EQ_OP = 271,                   /* EQ_OP  */
    NE_OP = 272,                   /* NE_OP  */
    AND_OP = 273,                  /* AND_OP  */
    OR_OP = 274,                   /* OR_OP  */
    MUL_ASSIGN = 275,              /* MUL_ASSIGN  */
    DIV_ASSIGN = 276,              /* DIV_ASSIGN  */
    MOD_ASSIGN = 277,              /* MOD_ASSIGN  */
    ADD_ASSIGN = 278,              /* ADD_ASSIGN  */
    SUB_ASSIGN = 279,              /* SUB_ASSIGN  */
    LEFT_ASSIGN = 280,             /* LEFT_ASSIGN  */
    RIGHT_ASSIGN = 281,            /* RIGHT_ASSIGN  */
    AND_ASSIGN = 282,              /* AND_ASSIGN  */
    XOR_ASSIGN = 283,              /* XOR_ASSIGN  */
    OR_ASSIGN = 284,               /* OR_ASSIGN  */
    TYPE_NAME = 285,               /* TYPE_NAME  */
    CHAR = 286,                    /* CHAR  */
    INT = 287,                     /* INT  */
    DOUBLE = 288,                  /* DOUBLE  */
    VOID = 289,                    /* VOID  */
    BOOL = 290,                    /* BOOL  */
    CASE = 291,                    /* CASE  */
    IF = 292,                      /* IF  */
    ELSE = 293,                    /* ELSE  */
    SWITCH = 294,                  /* SWITCH  */
    WHILE = 295,                   /* WHILE  */
    DO = 296,                      /* DO  */
    FOR = 297,                     /* FOR  */
    GOTO = 298,                    /* GOTO  */
    CONTINUE = 299,                /* CONTINUE  */
    BREAK = 300,                   /* BREAK  */
    RETURN = 301,                  /* RETURN  */
    TRUE = 302,                    /* TRUE  */
    FALSE = 303,                   /* FALSE  */
    LOWER_THAN_ELSE = 304          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IDENTIFIER 258
#define CONSTANT 259
#define STRING_LITERAL 260
#define SIZEOF 261
#define CONSTANT_INT 262
#define CONSTANT_DOUBLE 263
#define PTR_OP 264
#define INC_OP 265
#define DEC_OP 266
#define LEFT_OP 267
#define RIGHT_OP 268
#define LE_OP 269
#define GE_OP 270
#define EQ_OP 271
#define NE_OP 272
#define AND_OP 273
#define OR_OP 274
#define MUL_ASSIGN 275
#define DIV_ASSIGN 276
#define MOD_ASSIGN 277
#define ADD_ASSIGN 278
#define SUB_ASSIGN 279
#define LEFT_ASSIGN 280
#define RIGHT_ASSIGN 281
#define AND_ASSIGN 282
#define XOR_ASSIGN 283
#define OR_ASSIGN 284
#define TYPE_NAME 285
#define CHAR 286
#define INT 287
#define DOUBLE 288
#define VOID 289
#define BOOL 290
#define CASE 291
#define IF 292
#define ELSE 293
#define SWITCH 294
#define WHILE 295
#define DO 296
#define FOR 297
#define GOTO 298
#define CONTINUE 299
#define BREAK 300
#define RETURN 301
#define TRUE 302
#define FALSE 303
#define LOWER_THAN_ELSE 304

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 21 "compiler.y"

	struct gramTree* gt;

#line 246 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_CONSTANT = 4,                   /* CONSTANT  */
  YYSYMBOL_STRING_LITERAL = 5,             /* STRING_LITERAL  */
  YYSYMBOL_SIZEOF = 6,                     /* SIZEOF  */
  YYSYMBOL_CONSTANT_INT = 7,               /* CONSTANT_INT  */
  YYSYMBOL_CONSTANT_DOUBLE = 8,            /* CONSTANT_DOUBLE  */
  YYSYMBOL_PTR_OP = 9,                     /* PTR_OP  */
  YYSYMBOL_INC_OP = 10,                    /* INC_OP  */
  YYSYMBOL_DEC_OP = 11,                    /* DEC_OP  */
  YYSYMBOL_LEFT_OP = 12,                   /* LEFT_OP  */
  YYSYMBOL_RIGHT_OP = 13,                  /* RIGHT_OP  */
  YYSYMBOL_LE_OP = 14,                     /* LE_OP  */
  YYSYMBOL_GE_OP = 15,                     /* GE_OP  */
  YYSYMBOL_EQ_OP = 16,                     /* EQ_OP  */
  YYSYMBOL_NE_OP = 17,                     /* NE_OP  */
  YYSYMBOL_AND_OP = 18,                    /* AND_OP  */
  YYSYMBOL_OR_OP = 19,                     /* OR_OP  */
  YYSYMBOL_MUL_ASSIGN = 20,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 21,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 22,                /* MOD_ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 23,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 24,                /* SUB_ASSIGN  */
  YYSYMBOL_LEFT_ASSIGN = 25,               /* LEFT_ASSIGN  */
  YYSYMBOL_RIGHT_ASSIGN = 26,              /* RIGHT_ASSIGN  */
  YYSYMBOL_AND_ASSIGN = 27,                /* AND_ASSIGN  */
  YYSYMBOL_XOR_ASSIGN = 28,                /* XOR_ASSIGN  */
  YYSYMBOL_OR_ASSIGN = 29,                 /* OR_ASSIGN  */
  YYSYMBOL_TYPE_NAME = 30,                 /* TYPE_NAME  */
  YYSYMBOL_CHAR = 31,                      /* CHAR  */
  YYSYMBOL_INT = 32,                       /* INT  */
  YYSYMBOL_DOUBLE = 33,                    /* DOUBLE  */
  YYSYMBOL_VOID = 34,                      /* VOID  */
  YYSYMBOL_BOOL = 35,                      /* BOOL  */
  YYSYMBOL_CASE = 36,                      /* CASE  */
  YYSYMBOL_IF = 37,                        /* IF  */
  YYSYMBOL_ELSE = 38,                      /* ELSE  */
  YYSYMBOL_SWITCH = 39,                    /* SWITCH  */
  YYSYMBOL_WHILE = 40,                     /* WHILE  */
  YYSYMBOL_DO = 41,                        /* DO  */
  YYSYMBOL_FOR = 42,                       /* FOR  */
  YYSYMBOL_GOTO = 43,                      /* GOTO  */
  YYSYMBOL_CONTINUE = 44,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 45,                     /* BREAK  */
  YYSYMBOL_RETURN = 46,                    /* RETURN  */
  YYSYMBOL_TRUE = 47,                      /* TRUE  */
  YYSYMBOL_FALSE = 48,                     /* FALSE  */
  YYSYMBOL_49_ = 49,                       /* ';'  */
  YYSYMBOL_50_ = 50,                       /* ','  */
  YYSYMBOL_51_ = 51,                       /* ':'  */
  YYSYMBOL_52_ = 52,                       /* '='  */
  YYSYMBOL_53_ = 53,                       /* '['  */
  YYSYMBOL_54_ = 54,                       /* ']'  */
  YYSYMBOL_55_ = 55,                       /* '.'  */
  YYSYMBOL_56_ = 56,                       /* '&'  */
  YYSYMBOL_57_ = 57,                       /* '!'  */
  YYSYMBOL_58_ = 58,                       /* '~'  */
  YYSYMBOL_59_ = 59,                       /* '-'  */
  YYSYMBOL_60_ = 60,                       /* '+'  */
  YYSYMBOL_61_ = 61,                       /* '*'  */
  YYSYMBOL_62_ = 62,                       /* '/'  */
  YYSYMBOL_63_ = 63,                       /* '%'  */
  YYSYMBOL_64_ = 64,                       /* '<'  */
  YYSYMBOL_65_ = 65,                       /* '>'  */
  YYSYMBOL_66_ = 66,                       /* '^'  */
  YYSYMBOL_67_ = 67,                       /* '|'  */
  YYSYMBOL_68_ = 68,                       /* '?'  */
  YYSYMBOL_69_ = 69,                       /* '{'  */
  YYSYMBOL_70_ = 70,                       /* '}'  */
  YYSYMBOL_71_ = 71,                       /* '('  */
  YYSYMBOL_72_ = 72,                       /* ')'  */
  YYSYMBOL_LOWER_THAN_ELSE = 73,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 74,                  /* $accept  */
  YYSYMBOL_Program = 75,                   /* Program  */
  YYSYMBOL_primary_expression = 76,        /* primary_expression  */
  YYSYMBOL_postfix_expression = 77,        /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 78,  /* argument_expression_list  */
  YYSYMBOL_unary_expression = 79,          /* unary_expression  */
  YYSYMBOL_unary_operator = 80,            /* unary_operator  */
  YYSYMBOL_multiplicative_expression = 81, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 82,       /* additive_expression  */
  YYSYMBOL_shift_expression = 83,          /* shift_expression  */
  YYSYMBOL_relational_expression = 84,     /* relational_expression  */
  YYSYMBOL_equality_expression = 85,       /* equality_expression  */
  YYSYMBOL_and_expression = 86,            /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 87,   /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 88,   /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 89,    /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 90,     /* logical_or_expression  */
  YYSYMBOL_assignment_expression = 91,     /* assignment_expression  */
  YYSYMBOL_assignment_operator = 92,       /* assignment_operator  */
  YYSYMBOL_expression = 93,                /* expression  */
  YYSYMBOL_declaration = 94,               /* declaration  */
  YYSYMBOL_init_declarator_list = 95,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 96,           /* init_declarator  */
  YYSYMBOL_type_specifier = 97,            /* type_specifier  */
  YYSYMBOL_declarator = 98,                /* declarator  */
  YYSYMBOL_parameter_list = 99,            /* parameter_list  */
  YYSYMBOL_parameter_declaration = 100,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 101,          /* identifier_list  */
  YYSYMBOL_abstract_declarator = 102,      /* abstract_declarator  */
  YYSYMBOL_initializer = 103,              /* initializer  */
  YYSYMBOL_initializer_list = 104,         /* initializer_list  */
  YYSYMBOL_designation = 105,              /* designation  */
  YYSYMBOL_designator_list = 106,          /* designator_list  */
  YYSYMBOL_designator = 107,               /* designator  */
  YYSYMBOL_statement = 108,                /* statement  */
  YYSYMBOL_labeled_statement = 109,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 110,       /* compound_statement  */
  YYSYMBOL_block_item_list = 111,          /* block_item_list  */
  YYSYMBOL_block_item = 112,               /* block_item  */
  YYSYMBOL_expression_statement = 113,     /* expression_statement  */
  YYSYMBOL_selection_statement = 114,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 115,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 116,           /* jump_statement  */
  YYSYMBOL_translation_unit = 117,         /* translation_unit  */
  YYSYMBOL_external_declaration = 118,     /* external_declaration  */
  YYSYMBOL_function_definition = 119,      /* function_definition  */
  YYSYMBOL_declaration_list = 120          /* declaration_list  */
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
typedef yytype_int16 yy_state_t;

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
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   717

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  154
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  269

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   304


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
       2,     2,     2,    57,     2,     2,     2,    63,    56,     2,
      71,    72,    61,    60,    50,    59,    55,    62,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    51,    49,
      64,    52,    65,    68,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    53,     2,    54,    66,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    69,    67,    70,    58,     2,     2,     2,
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
      45,    46,    47,    48,    73
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    61,    61,    68,    72,    78,    83,    90,    95,   102,
     105,   109,   113,   117,   121,   128,   131,   138,   142,   146,
     150,   157,   160,   163,   166,   173,   176,   179,   182,   189,
     192,   195,   202,   205,   209,   217,   220,   223,   226,   230,
     238,   241,   245,   252,   255,   262,   265,   272,   275,   282,
     285,   293,   296,   304,   308,   315,   318,   322,   326,   330,
     334,   338,   342,   346,   350,   354,   362,   366,   374,   377,
     384,   387,   393,   396,   404,   407,   410,   413,   416,   424,
     428,   432,   437,   441,   445,   449,   453,   462,   465,   471,
     474,   477,   483,   486,   492,   495,   498,   501,   504,   507,
     510,   513,   516,   519,   522,   529,   532,   536,   543,   546,
     549,   552,   558,   564,   567,   573,   576,   583,   586,   589,
     592,   595,   598,   605,   608,   615,   618,   624,   627,   633,
     636,   642,   645,   652,   655,   658,   665,   668,   671,   674,
     677,   680,   687,   690,   693,   696,   699,   705,   708,   714,
     719,   727,   730,   736,   739
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
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "CONSTANT", "STRING_LITERAL", "SIZEOF", "CONSTANT_INT",
  "CONSTANT_DOUBLE", "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP", "RIGHT_OP",
  "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "MUL_ASSIGN",
  "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "LEFT_ASSIGN",
  "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "TYPE_NAME",
  "CHAR", "INT", "DOUBLE", "VOID", "BOOL", "CASE", "IF", "ELSE", "SWITCH",
  "WHILE", "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN", "TRUE",
  "FALSE", "';'", "','", "':'", "'='", "'['", "']'", "'.'", "'&'", "'!'",
  "'~'", "'-'", "'+'", "'*'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'",
  "'?'", "'{'", "'}'", "'('", "')'", "LOWER_THAN_ELSE", "$accept",
  "Program", "primary_expression", "postfix_expression",
  "argument_expression_list", "unary_expression", "unary_operator",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "assignment_expression", "assignment_operator", "expression",
  "declaration", "init_declarator_list", "init_declarator",
  "type_specifier", "declarator", "parameter_list",
  "parameter_declaration", "identifier_list", "abstract_declarator",
  "initializer", "initializer_list", "designation", "designator_list",
  "designator", "statement", "labeled_statement", "compound_statement",
  "block_item_list", "block_item", "expression_statement",
  "selection_statement", "iteration_statement", "jump_statement",
  "translation_unit", "external_declaration", "function_definition",
  "declaration_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-144)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     183,  -144,  -144,  -144,  -144,  -144,    15,  -144,     4,   183,
    -144,  -144,  -144,  -144,  -144,     5,   133,  -144,   434,  -144,
      20,  -144,     5,   575,   486,   244,    94,  -144,     4,  -144,
     112,  -144,  -144,    97,  -144,  -144,  -144,   646,   646,  -144,
    -144,  -144,  -144,  -144,  -144,   470,   646,  -144,    33,   243,
     646,   127,   126,   195,    23,   205,   -34,   -38,   -36,    16,
      26,  -144,  -144,  -144,    11,    14,     3,   646,    27,    53,
      66,   374,    68,   177,   124,   143,   315,  -144,  -144,  -144,
     207,  -144,  -144,  -144,  -144,   309,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,    46,   -31,  -144,   -30,  -144,  -144,  -144,
    -144,   646,   199,  -144,   -23,   575,   122,  -144,   -15,  -144,
    -144,   646,    22,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,   646,  -144,   646,   646,   646,   646,
     646,   646,   646,   646,   646,   646,   646,   646,   646,   646,
     646,   646,   646,   646,  -144,  -144,   374,  -144,    -5,   646,
     646,   646,   171,   393,   197,  -144,  -144,  -144,   247,  -144,
     646,  -144,  -144,   545,    81,   105,   116,   183,  -144,   216,
    -144,    -6,  -144,   451,  -144,  -144,  -144,  -144,  -144,    10,
    -144,   -11,  -144,  -144,  -144,  -144,  -144,   127,   127,   126,
     126,   195,   195,   195,   195,    23,    23,   205,   -34,   -38,
     -36,    16,  -144,   374,   -10,     2,    28,   152,   640,   640,
    -144,  -144,  -144,  -144,   194,   204,  -144,    51,    50,   560,
     128,  -144,  -144,  -144,  -144,  -144,   575,  -144,   646,  -144,
    -144,   374,   374,   374,   646,    48,   202,  -144,  -144,  -144,
    -144,  -144,   228,   240,  -144,    82,  -144,  -144,   215,  -144,
    -144,    83,   374,   106,   374,   107,  -144,  -144,  -144,   374,
     251,  -144,   374,  -144,   374,  -144,  -144,  -144,  -144
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    75,    76,    77,    74,    78,     0,   150,     0,     2,
     147,   149,     1,    79,    68,     0,     0,    70,    72,   148,
       0,    69,     0,     0,     0,     0,     0,   153,     0,   152,
       0,    80,    71,    72,     3,     6,     7,     0,     0,     4,
       5,    24,    23,    22,    21,     0,     0,     9,    17,    25,
       0,    29,    32,    35,    40,    43,    45,    47,    49,    51,
      53,   105,    73,    83,     0,     0,     3,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   131,   125,    66,
       0,   129,   130,   117,   118,     0,   127,   119,   120,   121,
     122,    92,    86,    91,     0,    87,     0,   154,   151,    18,
      19,     0,     0,   108,     0,     0,     0,   113,     0,    13,
      14,     0,     0,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    55,     0,    20,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    82,    81,     0,    25,     0,     0,
       0,     0,     0,     0,     0,   143,   144,   145,     0,   132,
       0,   126,   128,     0,     0,    89,    90,     0,    84,     0,
      85,     0,   116,     0,   106,   109,   112,   114,     8,     0,
      11,     0,    15,    54,    26,    27,    28,    31,    30,    33,
      34,    38,    39,    36,    37,    41,    42,    44,    46,    48,
      50,    52,   123,     0,     0,     0,     0,     0,     0,     0,
     142,   146,    67,    95,     0,     0,   101,     0,     0,     0,
       0,    88,    93,   115,   107,   110,     0,    10,     0,    12,
     124,     0,     0,     0,     0,     0,     0,    99,    96,   102,
      94,    97,     0,     0,   103,     0,   111,    16,   133,   135,
     136,     0,     0,     0,     0,     0,   100,    98,   104,     0,
       0,   140,     0,   138,     0,   134,   137,   141,   139
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -144,  -144,  -144,  -144,  -144,    98,  -144,   169,   174,   109,
     170,   172,   181,   168,   182,   167,   -51,   -22,  -144,   -40,
     -13,  -144,   305,     0,    -4,  -143,   161,  -144,   165,   -42,
    -144,   157,  -144,   225,   -61,  -144,   100,  -144,   248,  -142,
    -144,  -144,  -144,  -144,   323,  -144,  -144
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     6,    47,    48,   181,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    79,   124,    80,
       7,    16,    17,    28,    20,    94,    95,    96,   166,    62,
     104,   105,   106,   107,    82,    83,    84,    85,    86,    87,
      88,    89,    90,     9,    10,    11,    30
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       8,    61,    65,   103,    18,    27,   108,    13,    13,     8,
     152,   209,    81,   143,   143,    12,   148,    97,    33,   167,
     169,   217,   139,    61,    33,    34,    93,   173,   140,    35,
      36,   141,    37,    38,   142,   160,   158,   133,   134,   228,
     160,   168,   170,   109,   110,   143,   203,   174,   223,    13,
     171,    34,   160,    14,   146,    35,    36,   178,    37,    38,
     160,   229,   231,   175,   227,   144,   235,   236,   145,    39,
      40,   179,    81,    24,   232,    15,    15,   245,   160,    41,
      42,    43,    44,    61,    13,   202,   111,   135,   136,   165,
     182,    26,    31,    46,   180,    39,    40,    91,   149,   163,
     233,   167,   183,   219,   112,    41,    42,    43,    44,   204,
     205,   206,     1,     2,     3,     4,     5,   164,    29,    46,
     252,   220,   240,   239,   150,     1,     2,     3,     4,     5,
      98,   225,   167,   160,   163,    99,   100,   151,   212,   153,
     208,   215,   230,     1,     2,     3,     4,     5,   125,    23,
      24,    61,   164,   216,   258,   260,   160,   160,    24,     1,
       2,     3,     4,     5,    93,   147,    92,    93,    26,   219,
     248,   249,   250,   155,   176,   101,    26,   102,   262,   264,
     154,    25,    21,    22,   246,   129,   130,   220,   126,   127,
     128,   261,   156,   263,   251,   253,   255,   243,   265,   147,
     244,   267,   172,   268,    61,    34,   247,   131,   132,    35,
      36,   207,    37,    38,     1,     2,     3,     4,     5,   222,
      93,   137,   138,   234,   184,   185,   186,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   191,   192,   193,   194,   210,    66,   237,    39,
      40,    35,    36,   259,    37,    38,   159,   160,   238,    41,
      42,    43,    44,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,    46,   254,     1,     2,     3,     4,     5,
      67,    68,   256,    69,    70,    71,    72,    73,    74,    75,
      76,    39,    40,    77,   257,   123,   211,   160,   187,   188,
     266,    41,    42,    43,    44,   189,   190,   195,   196,   199,
     201,   197,    66,    25,    78,    46,    35,    36,    34,    37,
      38,   198,    35,    36,   200,    37,    38,    32,   221,   218,
     226,   177,    19,   162,     0,     0,     0,     0,     0,     0,
       1,     2,     3,     4,     5,    67,    68,     0,    69,    70,
      71,    72,    73,    74,    75,    76,    39,    40,    77,     0,
       0,     0,    39,    40,   157,     0,    41,    42,    43,    44,
       0,     0,    41,    42,    43,    44,     0,    66,    25,   161,
      46,    35,    36,     0,    37,    38,    46,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,     0,     0,     0,
      35,    36,     0,    37,    38,     0,     0,     0,     0,     0,
      67,    68,     0,    69,    70,    71,    72,    73,    74,    75,
      76,    39,    40,    77,     1,     2,     3,     4,     5,     0,
       0,    41,    42,    43,    44,     0,     0,     0,     0,     0,
      39,    40,    77,    25,     0,    46,     0,     0,     0,     0,
      41,    42,    43,    44,    34,     0,     0,     0,    35,    36,
       0,    37,    38,     0,    46,     1,     2,     3,     4,     5,
       0,     0,     0,    34,     0,     0,     0,    35,    36,     0,
      37,    38,     0,     0,     0,     0,    23,    24,     0,    34,
       0,     0,     0,    35,    36,     0,    37,    38,    39,    40,
       0,     0,     0,    25,   101,    26,   102,     0,    41,    42,
      43,    44,     0,     0,     0,     0,     0,    39,    40,     0,
      45,   224,    46,   101,     0,   102,     0,    41,    42,    43,
      44,     0,     0,    39,    40,     0,     0,     0,     0,    45,
      63,    46,     0,    41,    42,    43,    44,    64,    34,     0,
       0,     0,    35,    36,     0,    37,    38,    46,     0,     0,
       0,     0,     0,    34,     0,     0,     0,    35,    36,     0,
      37,    38,     0,     0,     0,     0,     0,     0,    34,     0,
       0,     0,    35,    36,     0,    37,    38,     0,     0,     0,
       0,     0,    39,    40,     0,     0,     0,     0,     0,   213,
       0,     0,    41,    42,    43,    44,   214,    39,    40,     0,
       0,     0,     0,     0,   241,     0,    46,    41,    42,    43,
      44,   242,    39,    40,     0,     0,     0,     0,     0,     0,
       0,    46,    41,    42,    43,    44,     0,     0,     0,     0,
       0,     0,     0,    34,    45,     0,    46,    35,    36,    34,
      37,    38,     0,    35,    36,     0,    37,    38,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    39,    40,    77,
       0,     0,     0,    39,    40,     0,     0,    41,    42,    43,
      44,     0,     0,    41,    42,    43,    44,     0,     0,     0,
       0,    46,     0,     0,     0,     0,     0,    46
};

static const yytype_int16 yycheck[] =
{
       0,    23,    24,    45,     8,    18,    46,     3,     3,     9,
      71,   153,    25,    19,    19,     0,    67,    30,    22,    50,
      50,   164,    56,    45,    28,     3,    26,    50,    66,     7,
       8,    67,    10,    11,    18,    50,    76,    14,    15,    50,
      50,    72,    72,    10,    11,    19,    51,    70,    54,     3,
     101,     3,    50,    49,    51,     7,     8,    72,    10,    11,
      50,    72,    72,   105,    54,    54,   208,   209,    54,    47,
      48,   111,    85,    53,    72,    71,    71,   220,    50,    57,
      58,    59,    60,   105,     3,   146,    53,    64,    65,    93,
     112,    71,    72,    71,    72,    47,    48,     3,    71,    53,
      72,    50,   124,    53,    71,    57,    58,    59,    60,   149,
     150,   151,    31,    32,    33,    34,    35,    71,    18,    71,
      72,    71,    72,    72,    71,    31,    32,    33,    34,    35,
      30,   173,    50,    50,    53,    37,    38,    71,   160,    71,
     153,   163,   203,    31,    32,    33,    34,    35,    50,    52,
      53,   173,    71,    72,    72,    72,    50,    50,    53,    31,
      32,    33,    34,    35,   164,    67,    72,   167,    71,    53,
     231,   232,   233,    49,    52,    53,    71,    55,    72,    72,
       3,    69,    49,    50,   226,    59,    60,    71,    61,    62,
      63,   252,    49,   254,   234,   235,   236,   219,   259,   101,
      72,   262,     3,   264,   226,     3,   228,    12,    13,     7,
       8,    40,    10,    11,    31,    32,    33,    34,    35,     3,
     220,    16,    17,    71,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   133,   134,   135,   136,    49,     3,    54,    47,
      48,     7,     8,    38,    10,    11,    49,    50,    54,    57,
      58,    59,    60,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    71,    72,    31,    32,    33,    34,    35,
      36,    37,    54,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    54,    52,    49,    50,   129,   130,
      49,    57,    58,    59,    60,   131,   132,   137,   138,   141,
     143,   139,     3,    69,    70,    71,     7,     8,     3,    10,
      11,   140,     7,     8,   142,    10,    11,    22,   167,   164,
     173,   106,     9,    85,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    32,    33,    34,    35,    36,    37,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    -1,
      -1,    -1,    47,    48,    49,    -1,    57,    58,    59,    60,
      -1,    -1,    57,    58,    59,    60,    -1,     3,    69,    70,
      71,     7,     8,    -1,    10,    11,    71,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,
       7,     8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,
      36,    37,    -1,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    31,    32,    33,    34,    35,    -1,
      -1,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    -1,
      47,    48,    49,    69,    -1,    71,    -1,    -1,    -1,    -1,
      57,    58,    59,    60,     3,    -1,    -1,    -1,     7,     8,
      -1,    10,    11,    -1,    71,    31,    32,    33,    34,    35,
      -1,    -1,    -1,     3,    -1,    -1,    -1,     7,     8,    -1,
      10,    11,    -1,    -1,    -1,    -1,    52,    53,    -1,     3,
      -1,    -1,    -1,     7,     8,    -1,    10,    11,    47,    48,
      -1,    -1,    -1,    69,    53,    71,    55,    -1,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,
      69,    70,    71,    53,    -1,    55,    -1,    57,    58,    59,
      60,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    69,
      54,    71,    -1,    57,    58,    59,    60,    61,     3,    -1,
      -1,    -1,     7,     8,    -1,    10,    11,    71,    -1,    -1,
      -1,    -1,    -1,     3,    -1,    -1,    -1,     7,     8,    -1,
      10,    11,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,
      -1,    -1,     7,     8,    -1,    10,    11,    -1,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    -1,    57,    58,    59,    60,    61,    47,    48,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    71,    57,    58,    59,
      60,    61,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,    69,    -1,    71,     7,     8,     3,
      10,    11,    -1,     7,     8,    -1,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,
      -1,    -1,    -1,    47,    48,    -1,    -1,    57,    58,    59,
      60,    -1,    -1,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    71,    -1,    -1,    -1,    -1,    -1,    71
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    31,    32,    33,    34,    35,    75,    94,    97,   117,
     118,   119,     0,     3,    49,    71,    95,    96,    98,   118,
      98,    49,    50,    52,    53,    69,    71,    94,    97,   110,
     120,    72,    96,    98,     3,     7,     8,    10,    11,    47,
      48,    57,    58,    59,    60,    69,    71,    76,    77,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,   103,    54,    61,    91,     3,    36,    37,    39,
      40,    41,    42,    43,    44,    45,    46,    49,    70,    91,
      93,    94,   108,   109,   110,   111,   112,   113,   114,   115,
     116,     3,    72,    97,    99,   100,   101,    94,   110,    79,
      79,    53,    55,   103,   104,   105,   106,   107,    93,    10,
      11,    53,    71,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    52,    92,    79,    61,    62,    63,    59,
      60,    12,    13,    14,    15,    64,    65,    16,    17,    56,
      66,    67,    18,    19,    54,    54,    51,    79,    90,    71,
      71,    71,   108,    71,     3,    49,    49,    49,    93,    49,
      50,    70,   112,    53,    71,    98,   102,    50,    72,    50,
      72,    90,     3,    50,    70,   103,    52,   107,    72,    93,
      72,    78,    91,    91,    79,    79,    79,    81,    81,    82,
      82,    83,    83,    83,    83,    84,    84,    85,    86,    87,
      88,    89,   108,    51,    93,    93,    93,    40,    94,   113,
      49,    49,    91,    54,    61,    91,    72,    99,   102,    53,
      71,   100,     3,    54,    70,   103,   105,    54,    50,    72,
     108,    72,    72,    72,    71,   113,   113,    54,    54,    72,
      72,    54,    61,    91,    72,    99,   103,    91,   108,   108,
     108,    93,    72,    93,    72,    93,    54,    54,    72,    38,
      72,   108,    72,   108,    72,   108,    49,   108,   108
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    74,    75,    76,    76,    76,    76,    76,    76,    77,
      77,    77,    77,    77,    77,    78,    78,    79,    79,    79,
      79,    80,    80,    80,    80,    81,    81,    81,    81,    82,
      82,    82,    83,    83,    83,    84,    84,    84,    84,    84,
      85,    85,    85,    86,    86,    87,    87,    88,    88,    89,
      89,    90,    90,    91,    91,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    93,    93,    94,    94,
      95,    95,    96,    96,    97,    97,    97,    97,    97,    98,
      98,    98,    98,    98,    98,    98,    98,    99,    99,   100,
     100,   100,   101,   101,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   103,   103,   103,   104,   104,
     104,   104,   105,   106,   106,   107,   107,   108,   108,   108,
     108,   108,   108,   109,   109,   110,   110,   111,   111,   112,
     112,   113,   113,   114,   114,   114,   115,   115,   115,   115,
     115,   115,   116,   116,   116,   116,   116,   117,   117,   118,
     118,   119,   119,   120,   120
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     3,     1,
       4,     3,     4,     2,     2,     1,     3,     1,     2,     2,
       2,     1,     1,     1,     1,     1,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     2,     3,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     4,     4,     3,     4,     4,     3,     1,     3,     2,
       2,     1,     1,     3,     3,     2,     3,     3,     4,     3,
       4,     2,     3,     3,     4,     1,     3,     4,     1,     2,
       3,     4,     2,     1,     2,     3,     2,     1,     1,     1,
       1,     1,     1,     3,     4,     2,     3,     1,     2,     1,
       1,     1,     2,     5,     7,     5,     5,     7,     6,     7,
       6,     7,     3,     2,     2,     2,     3,     1,     2,     1,
       1,     4,     3,     1,     2
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
  case 2: /* Program: translation_unit  */
#line 61 "compiler.y"
                         {
		root = create_tree("Program",1,(yyvsp[0].gt));
	}
#line 1636 "y.tab.c"
    break;

  case 3: /* primary_expression: IDENTIFIER  */
#line 68 "compiler.y"
                   {
		(yyval.gt) = create_tree("primary_expression",1,(yyvsp[0].gt));
	}
#line 1644 "y.tab.c"
    break;

  case 4: /* primary_expression: TRUE  */
#line 72 "compiler.y"
             {
		(yyval.gt) = create_tree("primary_expression",1,(yyvsp[0].gt));
		// $$->type = "bool";
		// $$->int_value = $1->int_value;
	}
#line 1654 "y.tab.c"
    break;

  case 5: /* primary_expression: FALSE  */
#line 78 "compiler.y"
              {
		(yyval.gt) = create_tree("primary_expression",1,(yyvsp[0].gt));
		// $$->type = "bool";
		// $$->int_value = $1->int_value;
	}
#line 1664 "y.tab.c"
    break;

  case 6: /* primary_expression: CONSTANT_INT  */
#line 83 "compiler.y"
                       {
		//printf("%d",$1->int_value);
		(yyval.gt) = create_tree("primary_expression",1,(yyvsp[0].gt));
		// $$->type = "int";
		// $$->int_value = $1->int_value;
		
	}
#line 1676 "y.tab.c"
    break;

  case 7: /* primary_expression: CONSTANT_DOUBLE  */
#line 90 "compiler.y"
                          {
		(yyval.gt) = create_tree("primary_expression",1,(yyvsp[0].gt));
		// $$->type = "double";
		// $$->double_value = $1->double_value;
	}
#line 1686 "y.tab.c"
    break;

  case 8: /* primary_expression: '(' expression ')'  */
#line 95 "compiler.y"
                            {
		(yyval.gt) = create_tree("primary_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1694 "y.tab.c"
    break;

  case 9: /* postfix_expression: primary_expression  */
#line 102 "compiler.y"
                          {
		(yyval.gt) = create_tree("postfix_expression",1,(yyvsp[0].gt));
	}
#line 1702 "y.tab.c"
    break;

  case 10: /* postfix_expression: postfix_expression '[' expression ']'  */
#line 105 "compiler.y"
                                                     {
		(yyval.gt) = create_tree("postfix_expression",4,(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
		//数组调用
	}
#line 1711 "y.tab.c"
    break;

  case 11: /* postfix_expression: postfix_expression '(' ')'  */
#line 109 "compiler.y"
                                          {
		(yyval.gt) = create_tree("postfix_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
		//函数调用
	}
#line 1720 "y.tab.c"
    break;

  case 12: /* postfix_expression: postfix_expression '(' argument_expression_list ')'  */
#line 113 "compiler.y"
                                                                   {
		(yyval.gt) = create_tree("postfix_expression",4,(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
		//函数调用
	}
#line 1729 "y.tab.c"
    break;

  case 13: /* postfix_expression: postfix_expression INC_OP  */
#line 117 "compiler.y"
                                         {
		//++
		(yyval.gt) = create_tree("postfix_expression",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1738 "y.tab.c"
    break;

  case 14: /* postfix_expression: postfix_expression DEC_OP  */
#line 121 "compiler.y"
                                         {
		//--
		(yyval.gt) = create_tree("postfix_expression",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1747 "y.tab.c"
    break;

  case 15: /* argument_expression_list: assignment_expression  */
#line 128 "compiler.y"
                             {
		(yyval.gt) = create_tree("argument_expression_list",1,(yyvsp[0].gt));
	}
#line 1755 "y.tab.c"
    break;

  case 16: /* argument_expression_list: argument_expression_list ',' assignment_expression  */
#line 131 "compiler.y"
                                                                   {
		(yyval.gt) = create_tree("argument_expression_list",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1763 "y.tab.c"
    break;

  case 17: /* unary_expression: postfix_expression  */
#line 138 "compiler.y"
                          {
		//printf("postfix");
		(yyval.gt) = create_tree("unary_expression",1,(yyvsp[0].gt));
	}
#line 1772 "y.tab.c"
    break;

  case 18: /* unary_expression: INC_OP unary_expression  */
#line 142 "compiler.y"
                                       {
		//++
		(yyval.gt) = create_tree("unary_expression",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1781 "y.tab.c"
    break;

  case 19: /* unary_expression: DEC_OP unary_expression  */
#line 146 "compiler.y"
                                       {
		//--
		(yyval.gt) = create_tree("unary_expression",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1790 "y.tab.c"
    break;

  case 20: /* unary_expression: unary_operator unary_expression  */
#line 150 "compiler.y"
                                               {
		(yyval.gt) = create_tree("unary_expression",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1798 "y.tab.c"
    break;

  case 21: /* unary_operator: '+'  */
#line 157 "compiler.y"
            {
		(yyval.gt) = create_tree("unary_operator",1,(yyvsp[0].gt));
	}
#line 1806 "y.tab.c"
    break;

  case 22: /* unary_operator: '-'  */
#line 160 "compiler.y"
              {
		(yyval.gt) = create_tree("unary_operator",1,(yyvsp[0].gt));
	}
#line 1814 "y.tab.c"
    break;

  case 23: /* unary_operator: '~'  */
#line 163 "compiler.y"
              {
		(yyval.gt) = create_tree("unary_operator",1,(yyvsp[0].gt));
	}
#line 1822 "y.tab.c"
    break;

  case 24: /* unary_operator: '!'  */
#line 166 "compiler.y"
              {
		(yyval.gt) = create_tree("unary_operator",1,(yyvsp[0].gt));
	}
#line 1830 "y.tab.c"
    break;

  case 25: /* multiplicative_expression: unary_expression  */
#line 173 "compiler.y"
                         {
		(yyval.gt) = create_tree("multiplicative_expression",1,(yyvsp[0].gt));
	}
#line 1838 "y.tab.c"
    break;

  case 26: /* multiplicative_expression: multiplicative_expression '*' unary_expression  */
#line 176 "compiler.y"
                                                         {
		(yyval.gt) = create_tree("multiplicative_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1846 "y.tab.c"
    break;

  case 27: /* multiplicative_expression: multiplicative_expression '/' unary_expression  */
#line 179 "compiler.y"
                                                         {
		(yyval.gt) = create_tree("multiplicative_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1854 "y.tab.c"
    break;

  case 28: /* multiplicative_expression: multiplicative_expression '%' unary_expression  */
#line 182 "compiler.y"
                                                         {
		(yyval.gt) = create_tree("multiplicative_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1862 "y.tab.c"
    break;

  case 29: /* additive_expression: multiplicative_expression  */
#line 189 "compiler.y"
                                   {
		(yyval.gt) = create_tree("additive_expression",1,(yyvsp[0].gt));
	}
#line 1870 "y.tab.c"
    break;

  case 30: /* additive_expression: additive_expression '+' multiplicative_expression  */
#line 192 "compiler.y"
                                                            {
		(yyval.gt) = create_tree("additive_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1878 "y.tab.c"
    break;

  case 31: /* additive_expression: additive_expression '-' multiplicative_expression  */
#line 195 "compiler.y"
                                                            {
		(yyval.gt) = create_tree("additive_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1886 "y.tab.c"
    break;

  case 32: /* shift_expression: additive_expression  */
#line 202 "compiler.y"
                            {
		(yyval.gt) = create_tree("shift_expression",1,(yyvsp[0].gt));
	}
#line 1894 "y.tab.c"
    break;

  case 33: /* shift_expression: shift_expression LEFT_OP additive_expression  */
#line 205 "compiler.y"
                                                       {
		//<<
		(yyval.gt) = create_tree("shift_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1903 "y.tab.c"
    break;

  case 34: /* shift_expression: shift_expression RIGHT_OP additive_expression  */
#line 209 "compiler.y"
                                                        {
		//<<
		(yyval.gt) = create_tree("shift_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1912 "y.tab.c"
    break;

  case 35: /* relational_expression: shift_expression  */
#line 217 "compiler.y"
                         {
		(yyval.gt) = create_tree("relational_expression",1,(yyvsp[0].gt));
	}
#line 1920 "y.tab.c"
    break;

  case 36: /* relational_expression: relational_expression '<' shift_expression  */
#line 220 "compiler.y"
                                                     {
		(yyval.gt) = create_tree("relational_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1928 "y.tab.c"
    break;

  case 37: /* relational_expression: relational_expression '>' shift_expression  */
#line 223 "compiler.y"
                                                     {
		(yyval.gt) = create_tree("relational_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1936 "y.tab.c"
    break;

  case 38: /* relational_expression: relational_expression LE_OP shift_expression  */
#line 226 "compiler.y"
                                                       {
		// <= 
		(yyval.gt) = create_tree("relational_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1945 "y.tab.c"
    break;

  case 39: /* relational_expression: relational_expression GE_OP shift_expression  */
#line 230 "compiler.y"
                                                       {
		// >=
		(yyval.gt) = create_tree("relational_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1954 "y.tab.c"
    break;

  case 40: /* equality_expression: relational_expression  */
#line 238 "compiler.y"
                              {
		(yyval.gt) = create_tree("equality_expression",1,(yyvsp[0].gt));
	}
#line 1962 "y.tab.c"
    break;

  case 41: /* equality_expression: equality_expression EQ_OP relational_expression  */
#line 241 "compiler.y"
                                                          {
		// ==
		(yyval.gt) = create_tree("equality_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1971 "y.tab.c"
    break;

  case 42: /* equality_expression: equality_expression NE_OP relational_expression  */
#line 245 "compiler.y"
                                                          {
		// !=
		(yyval.gt) = create_tree("equality_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1980 "y.tab.c"
    break;

  case 43: /* and_expression: equality_expression  */
#line 252 "compiler.y"
                            {
		(yyval.gt) = create_tree("and_expression",1,(yyvsp[0].gt));
	}
#line 1988 "y.tab.c"
    break;

  case 44: /* and_expression: and_expression '&' equality_expression  */
#line 255 "compiler.y"
                                                 {
		(yyval.gt) = create_tree("and_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 1996 "y.tab.c"
    break;

  case 45: /* exclusive_or_expression: and_expression  */
#line 262 "compiler.y"
                       {
		(yyval.gt) = create_tree("exclusive_or_expression",1,(yyvsp[0].gt));
	}
#line 2004 "y.tab.c"
    break;

  case 46: /* exclusive_or_expression: exclusive_or_expression '^' and_expression  */
#line 265 "compiler.y"
                                                     {
		(yyval.gt) = create_tree("exclusive_or_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2012 "y.tab.c"
    break;

  case 47: /* inclusive_or_expression: exclusive_or_expression  */
#line 272 "compiler.y"
                                {
		(yyval.gt) = create_tree("inclusive_or_expression",1,(yyvsp[0].gt));
	}
#line 2020 "y.tab.c"
    break;

  case 48: /* inclusive_or_expression: inclusive_or_expression '|' exclusive_or_expression  */
#line 275 "compiler.y"
                                                              {
		(yyval.gt) = create_tree("inclusive_or_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2028 "y.tab.c"
    break;

  case 49: /* logical_and_expression: inclusive_or_expression  */
#line 282 "compiler.y"
                                {
		(yyval.gt) = create_tree("logical_and_expression",1,(yyvsp[0].gt));
	}
#line 2036 "y.tab.c"
    break;

  case 50: /* logical_and_expression: logical_and_expression AND_OP inclusive_or_expression  */
#line 285 "compiler.y"
                                                                {
		//&&
		(yyval.gt) = create_tree("logical_and_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2045 "y.tab.c"
    break;

  case 51: /* logical_or_expression: logical_and_expression  */
#line 293 "compiler.y"
                               {
		(yyval.gt) = create_tree("logical_or_expression",1,(yyvsp[0].gt));
	}
#line 2053 "y.tab.c"
    break;

  case 52: /* logical_or_expression: logical_or_expression OR_OP logical_and_expression  */
#line 296 "compiler.y"
                                                             {
		//||
		(yyval.gt) = create_tree("logical_or_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2062 "y.tab.c"
    break;

  case 53: /* assignment_expression: logical_or_expression  */
#line 304 "compiler.y"
                              {
		//条件表达式
		(yyval.gt) = create_tree("assignment_expression",1,(yyvsp[0].gt));
	}
#line 2071 "y.tab.c"
    break;

  case 54: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 308 "compiler.y"
                                                                     {
		(yyval.gt) = create_tree("assignment_expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2079 "y.tab.c"
    break;

  case 55: /* assignment_operator: '='  */
#line 315 "compiler.y"
            {
		(yyval.gt) = create_tree("assignment_operator",1,(yyvsp[0].gt));
	}
#line 2087 "y.tab.c"
    break;

  case 56: /* assignment_operator: MUL_ASSIGN  */
#line 318 "compiler.y"
                     {
		//*=
		(yyval.gt) = create_tree("assignment_operator",1,(yyvsp[0].gt));
	}
#line 2096 "y.tab.c"
    break;

  case 57: /* assignment_operator: DIV_ASSIGN  */
#line 322 "compiler.y"
                     {
		// /=
		(yyval.gt) = create_tree("assignment_operator",1,(yyvsp[0].gt));
	}
#line 2105 "y.tab.c"
    break;

  case 58: /* assignment_operator: MOD_ASSIGN  */
#line 326 "compiler.y"
                     {
		// %=
		(yyval.gt) = create_tree("assignment_operator",1,(yyvsp[0].gt));
	}
#line 2114 "y.tab.c"
    break;

  case 59: /* assignment_operator: ADD_ASSIGN  */
#line 330 "compiler.y"
                     {
		// += 
		(yyval.gt) = create_tree("assignment_operator",1,(yyvsp[0].gt));
	}
#line 2123 "y.tab.c"
    break;

  case 60: /* assignment_operator: SUB_ASSIGN  */
#line 334 "compiler.y"
                     {
		// -=
		(yyval.gt) = create_tree("assignment_operator",1,(yyvsp[0].gt));
	}
#line 2132 "y.tab.c"
    break;

  case 61: /* assignment_operator: LEFT_ASSIGN  */
#line 338 "compiler.y"
                      {
		// <<=
		(yyval.gt) = create_tree("assignment_operator",1,(yyvsp[0].gt));
	}
#line 2141 "y.tab.c"
    break;

  case 62: /* assignment_operator: RIGHT_ASSIGN  */
#line 342 "compiler.y"
                       {
		// >>=
		(yyval.gt) = create_tree("assignment_operator",1,(yyvsp[0].gt));
	}
#line 2150 "y.tab.c"
    break;

  case 63: /* assignment_operator: AND_ASSIGN  */
#line 346 "compiler.y"
                     {
		// &=
		(yyval.gt) = create_tree("assignment_operator",1,(yyvsp[0].gt));
	}
#line 2159 "y.tab.c"
    break;

  case 64: /* assignment_operator: XOR_ASSIGN  */
#line 350 "compiler.y"
                     {
		// ^=
		(yyval.gt) = create_tree("assignment_operator",1,(yyvsp[0].gt));
	}
#line 2168 "y.tab.c"
    break;

  case 65: /* assignment_operator: OR_ASSIGN  */
#line 354 "compiler.y"
                    {
		// |=
		(yyval.gt) = create_tree("assignment_operator",1,(yyvsp[0].gt));
	}
#line 2177 "y.tab.c"
    break;

  case 66: /* expression: assignment_expression  */
#line 362 "compiler.y"
                              {
		//赋值表达式
		(yyval.gt) = create_tree("expression",1,(yyvsp[0].gt));
	}
#line 2186 "y.tab.c"
    break;

  case 67: /* expression: expression ',' assignment_expression  */
#line 366 "compiler.y"
                                               {
		//逗号表达式
		(yyval.gt) = create_tree("expression",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2195 "y.tab.c"
    break;

  case 68: /* declaration: type_specifier ';'  */
#line 374 "compiler.y"
                           {
		(yyval.gt) = create_tree("declaration",2,(yyvsp[-1].gt),(yyvsp[0].gt)); //?
	}
#line 2203 "y.tab.c"
    break;

  case 69: /* declaration: type_specifier init_declarator_list ';'  */
#line 377 "compiler.y"
                                                  {
		(yyval.gt) = create_tree("declaration",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2211 "y.tab.c"
    break;

  case 70: /* init_declarator_list: init_declarator  */
#line 384 "compiler.y"
                        {
		(yyval.gt) = create_tree("init_declarator_list",1,(yyvsp[0].gt));
	}
#line 2219 "y.tab.c"
    break;

  case 71: /* init_declarator_list: init_declarator_list ',' init_declarator  */
#line 387 "compiler.y"
                                                   {
		(yyval.gt) = create_tree("init_declarator_list",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2227 "y.tab.c"
    break;

  case 72: /* init_declarator: declarator  */
#line 393 "compiler.y"
                   {
		(yyval.gt) = create_tree("init_declarator",1,(yyvsp[0].gt));
	}
#line 2235 "y.tab.c"
    break;

  case 73: /* init_declarator: declarator '=' initializer  */
#line 396 "compiler.y"
                                     {
		(yyval.gt) = create_tree("init_declarator",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2243 "y.tab.c"
    break;

  case 74: /* type_specifier: VOID  */
#line 404 "compiler.y"
             {
		(yyval.gt) = create_tree("type_specifier",1,(yyvsp[0].gt));
	}
#line 2251 "y.tab.c"
    break;

  case 75: /* type_specifier: CHAR  */
#line 407 "compiler.y"
               {
		(yyval.gt) = create_tree("type_specifier",1,(yyvsp[0].gt));
	}
#line 2259 "y.tab.c"
    break;

  case 76: /* type_specifier: INT  */
#line 410 "compiler.y"
              {
		(yyval.gt) = create_tree("type_specifier",1,(yyvsp[0].gt));
	}
#line 2267 "y.tab.c"
    break;

  case 77: /* type_specifier: DOUBLE  */
#line 413 "compiler.y"
                 {
		(yyval.gt) = create_tree("type_specifier",1,(yyvsp[0].gt));	
	}
#line 2275 "y.tab.c"
    break;

  case 78: /* type_specifier: BOOL  */
#line 416 "compiler.y"
               {
		(yyval.gt) = create_tree("type_specifier",1,(yyvsp[0].gt));
	}
#line 2283 "y.tab.c"
    break;

  case 79: /* declarator: IDENTIFIER  */
#line 424 "compiler.y"
                   {
		//变量
		(yyval.gt) = create_tree("declarator",1,(yyvsp[0].gt));
	}
#line 2292 "y.tab.c"
    break;

  case 80: /* declarator: '(' declarator ')'  */
#line 428 "compiler.y"
                             {
		//.....
		(yyval.gt) = create_tree("declarator",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2301 "y.tab.c"
    break;

  case 81: /* declarator: declarator '[' assignment_expression ']'  */
#line 432 "compiler.y"
                                                   {
		//数组
		//printf("assignment_expression");
		(yyval.gt) = create_tree("declarator",4,(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2311 "y.tab.c"
    break;

  case 82: /* declarator: declarator '[' '*' ']'  */
#line 437 "compiler.y"
                                 {
		//....
		(yyval.gt) = create_tree("declarator",4,(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2320 "y.tab.c"
    break;

  case 83: /* declarator: declarator '[' ']'  */
#line 441 "compiler.y"
                             {
		//数组
		(yyval.gt) = create_tree("declarator",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2329 "y.tab.c"
    break;

  case 84: /* declarator: declarator '(' parameter_list ')'  */
#line 445 "compiler.y"
                                            {
		//函数
		(yyval.gt) = create_tree("declarator",4,(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2338 "y.tab.c"
    break;

  case 85: /* declarator: declarator '(' identifier_list ')'  */
#line 449 "compiler.y"
                                             {
		//函数
		(yyval.gt) = create_tree("declarator",4,(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2347 "y.tab.c"
    break;

  case 86: /* declarator: declarator '(' ')'  */
#line 453 "compiler.y"
                             {
		//函数
		(yyval.gt) = create_tree("declarator",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2356 "y.tab.c"
    break;

  case 87: /* parameter_list: parameter_declaration  */
#line 462 "compiler.y"
                              {
		(yyval.gt) = create_tree("parameter_list",1,(yyvsp[0].gt));
	}
#line 2364 "y.tab.c"
    break;

  case 88: /* parameter_list: parameter_list ',' parameter_declaration  */
#line 465 "compiler.y"
                                                   {
		(yyval.gt) = create_tree("parameter_list",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2372 "y.tab.c"
    break;

  case 89: /* parameter_declaration: type_specifier declarator  */
#line 471 "compiler.y"
                                  {
		(yyval.gt) = create_tree("parameter_declaration",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2380 "y.tab.c"
    break;

  case 90: /* parameter_declaration: type_specifier abstract_declarator  */
#line 474 "compiler.y"
                                             {
		(yyval.gt) = create_tree("parameter_declaration",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2388 "y.tab.c"
    break;

  case 91: /* parameter_declaration: type_specifier  */
#line 477 "compiler.y"
                         {
		(yyval.gt) = create_tree("parameter_declaration",1,(yyvsp[0].gt));
	}
#line 2396 "y.tab.c"
    break;

  case 92: /* identifier_list: IDENTIFIER  */
#line 483 "compiler.y"
                   {
		(yyval.gt) = create_tree("identifier_list",1,(yyvsp[0].gt));
	}
#line 2404 "y.tab.c"
    break;

  case 93: /* identifier_list: identifier_list ',' IDENTIFIER  */
#line 486 "compiler.y"
                                         {
		(yyval.gt) = create_tree("identifier_list",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2412 "y.tab.c"
    break;

  case 94: /* abstract_declarator: '(' abstract_declarator ')'  */
#line 492 "compiler.y"
                                    {
		(yyval.gt) = create_tree("abstract_declarator",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2420 "y.tab.c"
    break;

  case 95: /* abstract_declarator: '[' ']'  */
#line 495 "compiler.y"
                  {
		(yyval.gt) = create_tree("abstract_declarator",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2428 "y.tab.c"
    break;

  case 96: /* abstract_declarator: '[' assignment_expression ']'  */
#line 498 "compiler.y"
                                        {
		(yyval.gt) = create_tree("abstract_declarator",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2436 "y.tab.c"
    break;

  case 97: /* abstract_declarator: abstract_declarator '[' ']'  */
#line 501 "compiler.y"
                                      {
		(yyval.gt) = create_tree("abstract_declarator",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2444 "y.tab.c"
    break;

  case 98: /* abstract_declarator: abstract_declarator '[' assignment_expression ']'  */
#line 504 "compiler.y"
                                                            {
		(yyval.gt) = create_tree("abstract_declarator",4,(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2452 "y.tab.c"
    break;

  case 99: /* abstract_declarator: '[' '*' ']'  */
#line 507 "compiler.y"
                      {
		(yyval.gt) = create_tree("abstract_declarator",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2460 "y.tab.c"
    break;

  case 100: /* abstract_declarator: abstract_declarator '[' '*' ']'  */
#line 510 "compiler.y"
                                          {
		(yyval.gt) = create_tree("abstract_declarator",4,(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2468 "y.tab.c"
    break;

  case 101: /* abstract_declarator: '(' ')'  */
#line 513 "compiler.y"
                  {
		(yyval.gt) = create_tree("abstract_declarator",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2476 "y.tab.c"
    break;

  case 102: /* abstract_declarator: '(' parameter_list ')'  */
#line 516 "compiler.y"
                                 {
		(yyval.gt) = create_tree("abstract_declarator",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2484 "y.tab.c"
    break;

  case 103: /* abstract_declarator: abstract_declarator '(' ')'  */
#line 519 "compiler.y"
                                      {
		(yyval.gt) = create_tree("abstract_declarator",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2492 "y.tab.c"
    break;

  case 104: /* abstract_declarator: abstract_declarator '(' parameter_list ')'  */
#line 522 "compiler.y"
                                                     {
		(yyval.gt) = create_tree("abstract_declarator",4,(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2500 "y.tab.c"
    break;

  case 105: /* initializer: assignment_expression  */
#line 529 "compiler.y"
                              {
		(yyval.gt) = create_tree("initializer",1,(yyvsp[0].gt));
	}
#line 2508 "y.tab.c"
    break;

  case 106: /* initializer: '{' initializer_list '}'  */
#line 532 "compiler.y"
                                   {
		//列表初始化 {1,1,1}
		(yyval.gt) = create_tree("initializer",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2517 "y.tab.c"
    break;

  case 107: /* initializer: '{' initializer_list ',' '}'  */
#line 536 "compiler.y"
                                       {
		//列表初始化 {1,1,1,}
		(yyval.gt) = create_tree("initializer",4,(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2526 "y.tab.c"
    break;

  case 108: /* initializer_list: initializer  */
#line 543 "compiler.y"
                    {
		(yyval.gt) = create_tree("initializer_list",1,(yyvsp[0].gt));
	}
#line 2534 "y.tab.c"
    break;

  case 109: /* initializer_list: designation initializer  */
#line 546 "compiler.y"
                                  {
		(yyval.gt) = create_tree("initializer_list",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2542 "y.tab.c"
    break;

  case 110: /* initializer_list: initializer_list ',' initializer  */
#line 549 "compiler.y"
                                           {
		(yyval.gt) = create_tree("initializer_list",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2550 "y.tab.c"
    break;

  case 111: /* initializer_list: initializer_list ',' designation initializer  */
#line 552 "compiler.y"
                                                       {
		(yyval.gt) = create_tree("initializer_list",3,(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt));
	}
#line 2558 "y.tab.c"
    break;

  case 112: /* designation: designator_list '='  */
#line 558 "compiler.y"
                            {
		(yyval.gt) = create_tree("designation",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2566 "y.tab.c"
    break;

  case 113: /* designator_list: designator  */
#line 564 "compiler.y"
                   {
		(yyval.gt) = create_tree("designator_list",1,(yyvsp[0].gt));
	}
#line 2574 "y.tab.c"
    break;

  case 114: /* designator_list: designator_list designator  */
#line 567 "compiler.y"
                                     {
		(yyval.gt) = create_tree("designator_list",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2582 "y.tab.c"
    break;

  case 115: /* designator: '[' logical_or_expression ']'  */
#line 573 "compiler.y"
                                      {
		(yyval.gt) = create_tree("designator",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2590 "y.tab.c"
    break;

  case 116: /* designator: '.' IDENTIFIER  */
#line 576 "compiler.y"
                         {
		(yyval.gt) = create_tree("designator",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2598 "y.tab.c"
    break;

  case 117: /* statement: labeled_statement  */
#line 583 "compiler.y"
                          {
		(yyval.gt) = create_tree("statement",1,(yyvsp[0].gt));
	}
#line 2606 "y.tab.c"
    break;

  case 118: /* statement: compound_statement  */
#line 586 "compiler.y"
                             {
		(yyval.gt) = create_tree("statement",1,(yyvsp[0].gt));
	}
#line 2614 "y.tab.c"
    break;

  case 119: /* statement: expression_statement  */
#line 589 "compiler.y"
                              {
		(yyval.gt) = create_tree("statement",1,(yyvsp[0].gt));
	}
#line 2622 "y.tab.c"
    break;

  case 120: /* statement: selection_statement  */
#line 592 "compiler.y"
                              {
		(yyval.gt) = create_tree("statement",1,(yyvsp[0].gt));
	}
#line 2630 "y.tab.c"
    break;

  case 121: /* statement: iteration_statement  */
#line 595 "compiler.y"
                              {
		(yyval.gt) = create_tree("statement",1,(yyvsp[0].gt));
	}
#line 2638 "y.tab.c"
    break;

  case 122: /* statement: jump_statement  */
#line 598 "compiler.y"
                         {
		(yyval.gt) = create_tree("statement",1,(yyvsp[0].gt));
	}
#line 2646 "y.tab.c"
    break;

  case 123: /* labeled_statement: IDENTIFIER ':' statement  */
#line 605 "compiler.y"
                                 {
		(yyval.gt) = create_tree("labeled_statement",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2654 "y.tab.c"
    break;

  case 124: /* labeled_statement: CASE logical_or_expression ':' statement  */
#line 608 "compiler.y"
                                                   {
		(yyval.gt) = create_tree("labeled_statement",4,(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2662 "y.tab.c"
    break;

  case 125: /* compound_statement: '{' '}'  */
#line 615 "compiler.y"
                {
		(yyval.gt) = create_tree("compound_statement",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2670 "y.tab.c"
    break;

  case 126: /* compound_statement: '{' block_item_list '}'  */
#line 618 "compiler.y"
                                  {
		(yyval.gt) = create_tree("compound_statement",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2678 "y.tab.c"
    break;

  case 127: /* block_item_list: block_item  */
#line 624 "compiler.y"
                   {
		(yyval.gt) = create_tree("block_item_list",1,(yyvsp[0].gt));
	}
#line 2686 "y.tab.c"
    break;

  case 128: /* block_item_list: block_item_list block_item  */
#line 627 "compiler.y"
                                     {
		(yyval.gt) = create_tree("block_item_list",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2694 "y.tab.c"
    break;

  case 129: /* block_item: declaration  */
#line 633 "compiler.y"
                    {
		(yyval.gt) = create_tree("block_item",1,(yyvsp[0].gt));
	}
#line 2702 "y.tab.c"
    break;

  case 130: /* block_item: statement  */
#line 636 "compiler.y"
                    {
		(yyval.gt) = create_tree("block_item",1,(yyvsp[0].gt));
	}
#line 2710 "y.tab.c"
    break;

  case 131: /* expression_statement: ';'  */
#line 642 "compiler.y"
            {
		(yyval.gt) = create_tree("expression_statement",1,(yyvsp[0].gt));
	}
#line 2718 "y.tab.c"
    break;

  case 132: /* expression_statement: expression ';'  */
#line 645 "compiler.y"
                         {
		(yyval.gt) = create_tree("expression_statement",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2726 "y.tab.c"
    break;

  case 133: /* selection_statement: IF '(' expression ')' statement  */
#line 652 "compiler.y"
                                                              {
		(yyval.gt) = create_tree("selection_statement",5,(yyvsp[-4].gt),(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2734 "y.tab.c"
    break;

  case 134: /* selection_statement: IF '(' expression ')' statement ELSE statement  */
#line 655 "compiler.y"
                                                     {
		(yyval.gt) = create_tree("selection_statement",7,(yyvsp[-6].gt),(yyvsp[-5].gt),(yyvsp[-4].gt),(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2742 "y.tab.c"
    break;

  case 135: /* selection_statement: SWITCH '(' expression ')' statement  */
#line 658 "compiler.y"
                                          {
		(yyval.gt) = create_tree("selection_statement",5,(yyvsp[-4].gt),(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2750 "y.tab.c"
    break;

  case 136: /* iteration_statement: WHILE '(' expression ')' statement  */
#line 665 "compiler.y"
                                           {
		(yyval.gt) = create_tree("iteration_statement",5,(yyvsp[-4].gt),(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2758 "y.tab.c"
    break;

  case 137: /* iteration_statement: DO statement WHILE '(' expression ')' ';'  */
#line 668 "compiler.y"
                                                    {
		(yyval.gt) = create_tree("iteration_statement",7,(yyvsp[-6].gt),(yyvsp[-5].gt),(yyvsp[-4].gt),(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2766 "y.tab.c"
    break;

  case 138: /* iteration_statement: FOR '(' expression_statement expression_statement ')' statement  */
#line 671 "compiler.y"
                                                                          {
		(yyval.gt) = create_tree("iteration_statement",6,(yyvsp[-5].gt),(yyvsp[-4].gt),(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2774 "y.tab.c"
    break;

  case 139: /* iteration_statement: FOR '(' expression_statement expression_statement expression ')' statement  */
#line 674 "compiler.y"
                                                                                     {
		(yyval.gt) = create_tree("iteration_statement",7,(yyvsp[-6].gt),(yyvsp[-5].gt),(yyvsp[-4].gt),(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2782 "y.tab.c"
    break;

  case 140: /* iteration_statement: FOR '(' declaration expression_statement ')' statement  */
#line 677 "compiler.y"
                                                                 {
		(yyval.gt) = create_tree("iteration_statement",6,(yyvsp[-5].gt),(yyvsp[-4].gt),(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2790 "y.tab.c"
    break;

  case 141: /* iteration_statement: FOR '(' declaration expression_statement expression ')' statement  */
#line 680 "compiler.y"
                                                                            {
		(yyval.gt) = create_tree("iteration_statement",7,(yyvsp[-6].gt),(yyvsp[-5].gt),(yyvsp[-4].gt),(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2798 "y.tab.c"
    break;

  case 142: /* jump_statement: GOTO IDENTIFIER ';'  */
#line 687 "compiler.y"
                            {
		(yyval.gt) = create_tree("jump_statement",2,(yyvsp[-2].gt),(yyvsp[-1].gt));
	}
#line 2806 "y.tab.c"
    break;

  case 143: /* jump_statement: CONTINUE ';'  */
#line 690 "compiler.y"
                       {
		(yyval.gt) = create_tree("jump_statement",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2814 "y.tab.c"
    break;

  case 144: /* jump_statement: BREAK ';'  */
#line 693 "compiler.y"
                    {
		(yyval.gt) = create_tree("jump_statement",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2822 "y.tab.c"
    break;

  case 145: /* jump_statement: RETURN ';'  */
#line 696 "compiler.y"
                     {
		(yyval.gt) = create_tree("jump_statement",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2830 "y.tab.c"
    break;

  case 146: /* jump_statement: RETURN expression ';'  */
#line 699 "compiler.y"
                                {
		(yyval.gt) = create_tree("jump_statement",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2838 "y.tab.c"
    break;

  case 147: /* translation_unit: external_declaration  */
#line 705 "compiler.y"
                             {
		(yyval.gt) = create_tree("translation_unit",1,(yyvsp[0].gt));
	}
#line 2846 "y.tab.c"
    break;

  case 148: /* translation_unit: translation_unit external_declaration  */
#line 708 "compiler.y"
                                                {
		(yyval.gt) = create_tree("translation_unit",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2854 "y.tab.c"
    break;

  case 149: /* external_declaration: function_definition  */
#line 714 "compiler.y"
                            {
		(yyval.gt) = create_tree("external_declaration",1,(yyvsp[0].gt));
		//函数定义
		//printf("function_definition");
	}
#line 2864 "y.tab.c"
    break;

  case 150: /* external_declaration: declaration  */
#line 719 "compiler.y"
                      {
		(yyval.gt) = create_tree("external_declaration",1,(yyvsp[0].gt));
		//变量声明
		//printf("declaration");
	}
#line 2874 "y.tab.c"
    break;

  case 151: /* function_definition: type_specifier declarator declaration_list compound_statement  */
#line 727 "compiler.y"
                                                                      {
		(yyval.gt) = create_tree("function_definition",4,(yyvsp[-3].gt),(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2882 "y.tab.c"
    break;

  case 152: /* function_definition: type_specifier declarator compound_statement  */
#line 730 "compiler.y"
                                                       {
		(yyval.gt) = create_tree("function_definition",3,(yyvsp[-2].gt),(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2890 "y.tab.c"
    break;

  case 153: /* declaration_list: declaration  */
#line 736 "compiler.y"
                    {
		(yyval.gt) = create_tree("declaration_list",1,(yyvsp[0].gt));
	}
#line 2898 "y.tab.c"
    break;

  case 154: /* declaration_list: declaration_list declaration  */
#line 739 "compiler.y"
                                       {
		(yyval.gt) = create_tree("declaration_list",2,(yyvsp[-1].gt),(yyvsp[0].gt));
	}
#line 2906 "y.tab.c"
    break;


#line 2910 "y.tab.c"

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

#line 744 "compiler.y"



void yyerror(char const *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}


int main(int argc,char* argv[]) {

	yyin = fopen(argv[1],"r");
	
	//freopen("output/output.txt","w", stdout);
	yyparse();
	printf("\n");
	eval(root,0);	//输出语法分析树

	Praser praser(root);

	freeGramTree(root);

	fclose(yyin);
	return 0;
}
