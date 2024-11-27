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

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

// Déclaration explicite de yyin
extern FILE *yyin;

void yyerror(const char *s);

Node* root;
extern char *yytext;
extern int lineno;
extern int yylineno;
int yylex(void);

#line 88 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NOT = 3,                        /* NOT  */
  YYSYMBOL_TYPE = 4,                       /* TYPE  */
  YYSYMBOL_IDENT = 5,                      /* IDENT  */
  YYSYMBOL_VOID = 6,                       /* VOID  */
  YYSYMBOL_IF = 7,                         /* IF  */
  YYSYMBOL_ELSE = 8,                       /* ELSE  */
  YYSYMBOL_WHILE = 9,                      /* WHILE  */
  YYSYMBOL_RETURN = 10,                    /* RETURN  */
  YYSYMBOL_OR = 11,                        /* OR  */
  YYSYMBOL_AND = 12,                       /* AND  */
  YYSYMBOL_EQ = 13,                        /* EQ  */
  YYSYMBOL_ORDER = 14,                     /* ORDER  */
  YYSYMBOL_ADDSUB = 15,                    /* ADDSUB  */
  YYSYMBOL_DIVSTAR = 16,                   /* DIVSTAR  */
  YYSYMBOL_NUM = 17,                       /* NUM  */
  YYSYMBOL_CHARACTER = 18,                 /* CHARACTER  */
  YYSYMBOL_STATIC = 19,                    /* STATIC  */
  YYSYMBOL_20_ = 20,                       /* ';'  */
  YYSYMBOL_21_ = 21,                       /* ','  */
  YYSYMBOL_22_ = 22,                       /* '='  */
  YYSYMBOL_23_ = 23,                       /* '('  */
  YYSYMBOL_24_ = 24,                       /* ')'  */
  YYSYMBOL_25_ = 25,                       /* '{'  */
  YYSYMBOL_26_ = 26,                       /* '}'  */
  YYSYMBOL_27_ = 27,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 28,                  /* $accept  */
  YYSYMBOL_Prog = 29,                      /* Prog  */
  YYSYMBOL_DeclVars = 30,                  /* DeclVars  */
  YYSYMBOL_Declarateurs = 31,              /* Declarateurs  */
  YYSYMBOL_DeclFoncts = 32,                /* DeclFoncts  */
  YYSYMBOL_DeclFonct = 33,                 /* DeclFonct  */
  YYSYMBOL_EnTeteFonct = 34,               /* EnTeteFonct  */
  YYSYMBOL_Parametres = 35,                /* Parametres  */
  YYSYMBOL_ListTypVar = 36,                /* ListTypVar  */
  YYSYMBOL_Corps = 37,                     /* Corps  */
  YYSYMBOL_SuiteInstr = 38,                /* SuiteInstr  */
  YYSYMBOL_Instr = 39,                     /* Instr  */
  YYSYMBOL_Exp = 40,                       /* Exp  */
  YYSYMBOL_TB = 41,                        /* TB  */
  YYSYMBOL_FB = 42,                        /* FB  */
  YYSYMBOL_M = 43,                         /* M  */
  YYSYMBOL_E = 44,                         /* E  */
  YYSYMBOL_T = 45,                         /* T  */
  YYSYMBOL_F = 46,                         /* F  */
  YYSYMBOL_Arguments = 47,                 /* Arguments  */
  YYSYMBOL_ListExp = 48                    /* ListExp  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   106

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  28
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  21
/* YYNRULES -- Number of rules.  */
#define YYNRULES  51
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  101

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   274


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
       2,     2,     2,    27,     2,     2,     2,     2,     2,     2,
      23,    24,     2,     2,    21,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    20,
       2,    22,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,     2,    26,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    32,    32,    36,    37,    41,    42,    43,    44,    48,
      49,    53,    57,    58,    62,    63,    64,    68,    69,    73,
      77,    78,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    94,    95,    99,   100,   104,   105,   109,   110,   114,
     115,   119,   120,   124,   125,   126,   127,   128,   132,   133,
     137,   138
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
  "\"end of file\"", "error", "\"invalid token\"", "NOT", "TYPE", "IDENT",
  "VOID", "IF", "ELSE", "WHILE", "RETURN", "OR", "AND", "EQ", "ORDER",
  "ADDSUB", "DIVSTAR", "NUM", "CHARACTER", "STATIC", "';'", "','", "'='",
  "'('", "')'", "'{'", "'}'", "'!'", "$accept", "Prog", "DeclVars",
  "Declarateurs", "DeclFoncts", "DeclFonct", "EnTeteFonct", "Parametres",
  "ListTypVar", "Corps", "SuiteInstr", "Instr", "Exp", "TB", "FB", "M",
  "E", "T", "F", "Arguments", "ListExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-76)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -76,     9,    40,   -76,     8,    20,    56,   -76,     4,    42,
      47,    17,    49,   -76,   -76,   -76,    52,    57,   -76,    69,
      57,    24,    71,   -76,   -76,    72,   -76,    54,    55,   -76,
      58,    74,    23,   -76,   -76,    76,   -76,    59,    50,    60,
      61,    -1,   -76,   -76,   -76,   -76,    80,     0,     0,     0,
       0,   -76,     0,   -76,   -76,     0,     0,    25,    75,    73,
      77,    78,    79,   -76,    32,   -76,    39,    81,    64,    68,
      -4,     7,   -76,    10,   -76,     0,   -76,     0,     0,     0,
       0,     0,   -76,   -76,    70,     0,    46,    46,   -76,    75,
      73,    77,    78,    79,   -76,   -76,    81,    86,   -76,    46,
     -76
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,     2,    10,     0,     8,
       0,     0,     0,     9,     4,    11,     0,    16,     3,     0,
      16,     0,    21,     7,     6,     0,    14,     0,    15,     5,
       0,     0,     0,    18,    12,     0,    13,     8,     0,     0,
       0,     0,    30,    21,    19,    20,     0,     0,    49,     0,
       0,    47,     0,    46,    28,     0,     0,     0,    32,    34,
      36,    38,    40,    42,     0,    17,     0,    51,     0,    48,
       0,     0,    43,     0,    44,     0,    27,     0,     0,     0,
       0,     0,    29,    22,     0,     0,     0,     0,    45,    31,
      33,    35,    37,    39,    41,    26,    50,    23,    25,     0,
      24
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -76,   -76,    82,   -76,   -76,    91,   -76,    83,   -76,   -76,
      62,   -75,   -47,    26,    21,    22,    27,    19,   -46,   -76,
     -76
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    10,     6,     7,     8,    27,    28,    15,
      32,    45,    57,    58,    59,    60,    61,    62,    63,    68,
      69
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      66,    67,    70,    71,    51,    51,    72,    75,    73,     3,
      74,    97,    98,     9,    52,    52,    53,    53,    75,    54,
      86,    75,    55,    55,   100,    11,    56,    56,    38,    14,
      39,    87,    40,    41,    88,    94,    75,    38,    96,    39,
      20,    40,    41,    42,     4,    76,     5,    17,    43,    44,
      75,    38,    42,    39,    21,    40,    41,    43,    82,    83,
      12,    25,     5,    26,    16,    17,    42,    18,    19,    23,
      24,    43,    47,    48,    29,    31,    35,    33,    34,    37,
      46,    16,    36,    49,    50,    65,    78,    77,    84,    85,
      95,    79,    75,    80,    99,    81,    22,    13,    90,    93,
      91,    89,     0,    30,     0,    64,    92
};

static const yytype_int8 yycheck[] =
{
      47,    48,    49,    50,     5,     5,    52,    11,    55,     0,
      56,    86,    87,     5,    15,    15,    17,    17,    11,    20,
      24,    11,    23,    23,    99,     5,    27,    27,     5,    25,
       7,    24,     9,    10,    24,    81,    11,     5,    85,     7,
      23,     9,    10,    20,     4,    20,     6,    23,    25,    26,
      11,     5,    20,     7,     5,     9,    10,    25,    26,    20,
       4,     4,     6,     6,    22,    23,    20,    20,    21,    17,
      18,    25,    22,    23,     5,     4,    21,     5,    24,     5,
       4,    22,    24,    23,    23,     5,    13,    12,    24,    21,
      20,    14,    11,    15,     8,    16,    14,     6,    77,    80,
      78,    75,    -1,    20,    -1,    43,    79
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    29,    30,     0,     4,     6,    32,    33,    34,     5,
      31,     5,     4,    33,    25,    37,    22,    23,    20,    21,
      23,     5,    30,    17,    18,     4,     6,    35,    36,     5,
      35,     4,    38,     5,    24,    21,    24,     5,     5,     7,
       9,    10,    20,    25,    26,    39,     4,    22,    23,    23,
      23,     5,    15,    17,    20,    23,    27,    40,    41,    42,
      43,    44,    45,    46,    38,     5,    40,    40,    47,    48,
      40,    40,    46,    40,    46,    11,    20,    12,    13,    14,
      15,    16,    26,    20,    24,    21,    24,    24,    24,    41,
      42,    43,    44,    45,    46,    20,    40,    39,    39,     8,
      39
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    28,    29,    30,    30,    31,    31,    31,    31,    32,
      32,    33,    34,    34,    35,    35,    35,    36,    36,    37,
      38,    38,    39,    39,    39,    39,    39,    39,    39,    39,
      39,    40,    40,    41,    41,    42,    42,    43,    43,    44,
      44,    45,    45,    46,    46,    46,    46,    46,    47,    47,
      48,    48
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     4,     0,     3,     3,     3,     1,     2,
       1,     2,     5,     5,     1,     1,     0,     4,     2,     4,
       2,     0,     4,     5,     7,     5,     5,     3,     2,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     2,     2,     3,     1,     1,     1,     0,
       3,     1
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
  case 2: /* Prog: DeclVars DeclFoncts  */
#line 32 "parser.y"
                           { (yyval.node) = makeNode(Prog); addChild((yyval.node), (yyvsp[-1].node)); addChild((yyval.node), (yyvsp[0].node)); root = (yyval.node);}
#line 1185 "parser.tab.c"
    break;

  case 3: /* DeclVars: DeclVars TYPE Declarateurs ';'  */
#line 36 "parser.y"
                                      { (yyval.node) = makeNode(DeclVars); addChild((yyval.node), (yyvsp[-3].node)); addChild((yyval.node), makeNode(type)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 1191 "parser.tab.c"
    break;

  case 4: /* DeclVars: %empty  */
#line 37 "parser.y"
       { (yyval.node) = makeNode(DeclVars); }
#line 1197 "parser.tab.c"
    break;

  case 5: /* Declarateurs: Declarateurs ',' IDENT  */
#line 41 "parser.y"
                              { (yyval.node) = (yyvsp[-2].node); addSibling((yyval.node), makeNode(ident)); }
#line 1203 "parser.tab.c"
    break;

  case 6: /* Declarateurs: IDENT '=' CHARACTER  */
#line 42 "parser.y"
                           { (yyval.node) = makeNode(Declarateurs); addChild((yyval.node), makeNode(ident)); addChild((yyval.node), makeNode(Character)); }
#line 1209 "parser.tab.c"
    break;

  case 7: /* Declarateurs: IDENT '=' NUM  */
#line 43 "parser.y"
                           { (yyval.node) = makeNode(Declarateurs); addChild((yyval.node), makeNode(ident)); addChild((yyval.node), makeNode(Num)); }
#line 1215 "parser.tab.c"
    break;

  case 8: /* Declarateurs: IDENT  */
#line 44 "parser.y"
                           { (yyval.node) = makeNode(Declarateurs); addChild((yyval.node), makeNode(ident)); }
#line 1221 "parser.tab.c"
    break;

  case 9: /* DeclFoncts: DeclFoncts DeclFonct  */
#line 48 "parser.y"
                            { (yyval.node) = (yyvsp[-1].node); addSibling((yyval.node), (yyvsp[0].node)); }
#line 1227 "parser.tab.c"
    break;

  case 10: /* DeclFoncts: DeclFonct  */
#line 49 "parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1233 "parser.tab.c"
    break;

  case 11: /* DeclFonct: EnTeteFonct Corps  */
#line 53 "parser.y"
                         { (yyval.node) = makeNode(DeclFonct); addChild((yyval.node), (yyvsp[-1].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1239 "parser.tab.c"
    break;

  case 12: /* EnTeteFonct: TYPE IDENT '(' Parametres ')'  */
#line 57 "parser.y"
                                     { (yyval.node) = makeNode(EnTeteFonct); addChild((yyval.node), makeNode(type)); addChild((yyval.node), makeNode(ident)); addChild((yyval.node), makeNode(Parametres)); }
#line 1245 "parser.tab.c"
    break;

  case 13: /* EnTeteFonct: VOID IDENT '(' Parametres ')'  */
#line 58 "parser.y"
                                     { (yyval.node) = makeNode(EnTeteFonct); addChild((yyval.node), makeNode(Void)); addChild((yyval.node), makeNode(ident)); addChild((yyval.node), makeNode(Parametres)); }
#line 1251 "parser.tab.c"
    break;

  case 14: /* Parametres: VOID  */
#line 62 "parser.y"
            { (yyval.node) = makeNode(Parametres); addChild((yyval.node), makeNode(VOID)); }
#line 1257 "parser.tab.c"
    break;

  case 15: /* Parametres: ListTypVar  */
#line 63 "parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1263 "parser.tab.c"
    break;

  case 16: /* Parametres: %empty  */
#line 64 "parser.y"
       {(yyval.node) = NULL;}
#line 1269 "parser.tab.c"
    break;

  case 17: /* ListTypVar: ListTypVar ',' TYPE IDENT  */
#line 68 "parser.y"
                                 { (yyval.node) = (yyvsp[-3].node); addSibling((yyval.node), makeNode(TYPE)); addSibling((yyval.node), makeNode(IDENT)); }
#line 1275 "parser.tab.c"
    break;

  case 18: /* ListTypVar: TYPE IDENT  */
#line 69 "parser.y"
                  { (yyval.node) = makeNode(ListTypVar); addChild((yyval.node), makeNode(TYPE)); addChild((yyval.node), makeNode(IDENT)); }
#line 1281 "parser.tab.c"
    break;

  case 19: /* Corps: '{' DeclVars SuiteInstr '}'  */
#line 73 "parser.y"
                                { (yyval.node) = makeNode(Corps); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 1287 "parser.tab.c"
    break;

  case 20: /* SuiteInstr: SuiteInstr Instr  */
#line 77 "parser.y"
                        { (yyval.node) = (yyvsp[-1].node); addSibling((yyval.node), (yyvsp[0].node)); }
#line 1293 "parser.tab.c"
    break;

  case 21: /* SuiteInstr: %empty  */
#line 78 "parser.y"
                 { (yyval.node) = makeNode(SuiteInstr); }
#line 1299 "parser.tab.c"
    break;

  case 22: /* Instr: IDENT '=' Exp ';'  */
#line 82 "parser.y"
                         { (yyval.node) = makeNode(Instr); addChild((yyval.node), makeNode(IDENT)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 1305 "parser.tab.c"
    break;

  case 23: /* Instr: IF '(' Exp ')' Instr  */
#line 83 "parser.y"
                            { (yyval.node) = makeNode(Instr); addChild((yyval.node), makeNode(IF)); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1311 "parser.tab.c"
    break;

  case 24: /* Instr: IF '(' Exp ')' Instr ELSE Instr  */
#line 84 "parser.y"
                                       { (yyval.node) = makeNode(Instr); addChild((yyval.node), makeNode(IF)); addChild((yyval.node), (yyvsp[-4].node)); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), makeNode(ELSE)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1317 "parser.tab.c"
    break;

  case 25: /* Instr: WHILE '(' Exp ')' Instr  */
#line 85 "parser.y"
                               { (yyval.node) = makeNode(Instr); addChild((yyval.node), makeNode(WHILE)); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1323 "parser.tab.c"
    break;

  case 26: /* Instr: IDENT '(' Arguments ')' ';'  */
#line 86 "parser.y"
                                   { (yyval.node) = makeNode(Instr); addChild((yyval.node), makeNode(IDENT)); addChild((yyval.node), (yyvsp[-2].node)); }
#line 1329 "parser.tab.c"
    break;

  case 27: /* Instr: RETURN Exp ';'  */
#line 87 "parser.y"
                      { (yyval.node) = makeNode(Instr); addChild((yyval.node), makeNode(Return)); addChild((yyval.node), (yyvsp[-1].node)); }
#line 1335 "parser.tab.c"
    break;

  case 28: /* Instr: RETURN ';'  */
#line 88 "parser.y"
                  { (yyval.node) = makeNode(Instr); addChild((yyval.node), makeNode(Return)); }
#line 1341 "parser.tab.c"
    break;

  case 29: /* Instr: '{' SuiteInstr '}'  */
#line 89 "parser.y"
                          { (yyval.node) = (yyvsp[-1].node); }
#line 1347 "parser.tab.c"
    break;

  case 30: /* Instr: ';'  */
#line 90 "parser.y"
           { (yyval.node) = makeNode(Instr); }
#line 1353 "parser.tab.c"
    break;

  case 31: /* Exp: Exp OR TB  */
#line 94 "parser.y"
              { (yyval.node) = makeNode(Exp); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), makeNode(OR)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1359 "parser.tab.c"
    break;

  case 32: /* Exp: TB  */
#line 95 "parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 1365 "parser.tab.c"
    break;

  case 33: /* TB: TB AND FB  */
#line 99 "parser.y"
              { (yyval.node) = makeNode(TB); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), makeNode(AND)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1371 "parser.tab.c"
    break;

  case 34: /* TB: FB  */
#line 100 "parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 1377 "parser.tab.c"
    break;

  case 35: /* FB: FB EQ M  */
#line 104 "parser.y"
            { (yyval.node) = makeNode(FB); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), makeNode(EQ)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1383 "parser.tab.c"
    break;

  case 36: /* FB: M  */
#line 105 "parser.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 1389 "parser.tab.c"
    break;

  case 37: /* M: M ORDER E  */
#line 109 "parser.y"
              { (yyval.node) = makeNode(M); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), makeNode(ORDER)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1395 "parser.tab.c"
    break;

  case 38: /* M: E  */
#line 110 "parser.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 1401 "parser.tab.c"
    break;

  case 39: /* E: E ADDSUB T  */
#line 114 "parser.y"
               { (yyval.node) = makeNode(E); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), makeNode(ADDSUB)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1407 "parser.tab.c"
    break;

  case 40: /* E: T  */
#line 115 "parser.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 1413 "parser.tab.c"
    break;

  case 41: /* T: T DIVSTAR F  */
#line 119 "parser.y"
                { (yyval.node) = makeNode(T); addChild((yyval.node), (yyvsp[-2].node)); addChild((yyval.node), makeNode(DIVSTAR)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1419 "parser.tab.c"
    break;

  case 42: /* T: F  */
#line 120 "parser.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 1425 "parser.tab.c"
    break;

  case 43: /* F: ADDSUB F  */
#line 124 "parser.y"
             { (yyval.node) = makeNode(F); addChild((yyval.node), makeNode(ADDSUB)); addChild((yyval.node), (yyvsp[0].node)); }
#line 1431 "parser.tab.c"
    break;

  case 44: /* F: '!' F  */
#line 125 "parser.y"
             { (yyval.node) = makeNode(F); addChild((yyval.node), makeNode('!')); addChild((yyval.node), (yyvsp[0].node)); }
#line 1437 "parser.tab.c"
    break;

  case 45: /* F: '(' Exp ')'  */
#line 126 "parser.y"
                   { (yyval.node) = (yyvsp[-1].node); }
#line 1443 "parser.tab.c"
    break;

  case 46: /* F: NUM  */
#line 127 "parser.y"
           { (yyval.node) = makeNode(F); addChild((yyval.node), makeNode(Num)); }
#line 1449 "parser.tab.c"
    break;

  case 47: /* F: IDENT  */
#line 128 "parser.y"
             { (yyval.node) = makeNode(F); addChild((yyval.node), makeNode(ident)); }
#line 1455 "parser.tab.c"
    break;

  case 48: /* Arguments: ListExp  */
#line 132 "parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1461 "parser.tab.c"
    break;

  case 49: /* Arguments: %empty  */
#line 133 "parser.y"
                 { (yyval.node) = makeNode(Arguments); }
#line 1467 "parser.tab.c"
    break;

  case 50: /* ListExp: ListExp ',' Exp  */
#line 137 "parser.y"
                    { (yyval.node) = (yyvsp[-2].node); addSibling((yyval.node), (yyvsp[0].node)); }
#line 1473 "parser.tab.c"
    break;

  case 51: /* ListExp: Exp  */
#line 138 "parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1479 "parser.tab.c"
    break;


#line 1483 "parser.tab.c"

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

#line 141 "parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Erreur de syntaxe à la ligne %d : %s", yylineno, s);
    // Afficher le caractère qui a provoqué l'erreur
    if (yytext[0] != '\0') {
        fprintf(stderr, " - Caractère : '%s'\n", yytext);
    } else {
        fprintf(stderr, "\n");
    }
}

int main(int argc, char **argv) {
    yyparse();
    printTree(root);
    return 0;
}
