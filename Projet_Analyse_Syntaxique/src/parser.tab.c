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
#line 1 "src/parser.y"
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "tree.h"

void yyerror(const char *s);

Node* root;
extern char *yytext;
extern int lineno;
extern int line;
extern char * word;
int yylex(void);
void yyerror(const char *s);

// Ajout aux feuilles de l'arbre leur valeur
char *strdup(const char *s) {
    size_t len = strlen(s);
    char *dup = malloc(len + 1);
    if (dup != NULL) {
        strcpy(dup, s);
    }
    return dup;
}

#line 99 "./src/parser.tab.c"

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
  YYSYMBOL_VOID = 3,                       /* VOID  */
  YYSYMBOL_IF = 4,                         /* IF  */
  YYSYMBOL_ELSE = 5,                       /* ELSE  */
  YYSYMBOL_WHILE = 6,                      /* WHILE  */
  YYSYMBOL_RETURN = 7,                     /* RETURN  */
  YYSYMBOL_OR = 8,                         /* OR  */
  YYSYMBOL_AND = 9,                        /* AND  */
  YYSYMBOL_STATIC = 10,                    /* STATIC  */
  YYSYMBOL_NUM = 11,                       /* NUM  */
  YYSYMBOL_EQ = 12,                        /* EQ  */
  YYSYMBOL_ADDSUB = 13,                    /* ADDSUB  */
  YYSYMBOL_DIVSTAR = 14,                   /* DIVSTAR  */
  YYSYMBOL_TYPE = 15,                      /* TYPE  */
  YYSYMBOL_ORDER = 16,                     /* ORDER  */
  YYSYMBOL_IDENT = 17,                     /* IDENT  */
  YYSYMBOL_CHARACTER = 18,                 /* CHARACTER  */
  YYSYMBOL_19_ = 19,                       /* ';'  */
  YYSYMBOL_20_ = 20,                       /* ','  */
  YYSYMBOL_21_ = 21,                       /* '('  */
  YYSYMBOL_22_ = 22,                       /* ')'  */
  YYSYMBOL_23_ = 23,                       /* '{'  */
  YYSYMBOL_24_ = 24,                       /* '}'  */
  YYSYMBOL_25_ = 25,                       /* '='  */
  YYSYMBOL_26_ = 26,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 27,                  /* $accept  */
  YYSYMBOL_Prog = 28,                      /* Prog  */
  YYSYMBOL_DeclVars = 29,                  /* DeclVars  */
  YYSYMBOL_Declarateurs = 30,              /* Declarateurs  */
  YYSYMBOL_DeclFoncts = 31,                /* DeclFoncts  */
  YYSYMBOL_DeclFonct = 32,                 /* DeclFonct  */
  YYSYMBOL_EnTeteFonct = 33,               /* EnTeteFonct  */
  YYSYMBOL_Parametres = 34,                /* Parametres  */
  YYSYMBOL_ListTypVar = 35,                /* ListTypVar  */
  YYSYMBOL_Corps = 36,                     /* Corps  */
  YYSYMBOL_DeclVarsLocale = 37,            /* DeclVarsLocale  */
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
#define YYLAST   122

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  27
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  54
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  112

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   273


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
       2,     2,     2,    26,     2,     2,     2,     2,     2,     2,
      21,    22,     2,     2,    20,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    19,
       2,    25,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    23,     2,    24,     2,     2,     2,     2,
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
      15,    16,    17,    18
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    45,    45,    56,    64,    65,    69,    75,    81,    85,
      89,    95,   105,   115,   116,   120,   128,   138,   153,   160,
     168,   172,   173,   177,   182,   189,   202,   210,   218,   220,
     222,   224,   228,   233,   237,   242,   246,   252,   256,   263,
     267,   274,   278,   284,   288,   294,   300,   301,   306,   308,
     310,   317,   318,   322,   323
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
  "\"end of file\"", "error", "\"invalid token\"", "VOID", "IF", "ELSE",
  "WHILE", "RETURN", "OR", "AND", "STATIC", "NUM", "EQ", "ADDSUB",
  "DIVSTAR", "TYPE", "ORDER", "IDENT", "CHARACTER", "';'", "','", "'('",
  "')'", "'{'", "'}'", "'='", "'!'", "$accept", "Prog", "DeclVars",
  "Declarateurs", "DeclFoncts", "DeclFonct", "EnTeteFonct", "Parametres",
  "ListTypVar", "Corps", "DeclVarsLocale", "SuiteInstr", "Instr", "Exp",
  "TB", "FB", "M", "E", "T", "F", "Arguments", "ListExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-82)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -82,    23,    59,   -82,    -2,    30,    13,    49,   -82,    47,
      51,    62,    56,    17,    69,   -82,   -82,   -82,    60,   -82,
      61,    60,   -82,    70,    56,    58,   -82,    71,    67,    72,
     -82,    68,   -82,    76,    62,     1,   -82,   -82,    78,   -82,
      62,    63,    73,    74,    29,    46,   -82,   -82,   -82,   -82,
      79,    65,   -82,    40,    40,   -82,    40,    77,   -82,   -82,
      40,    40,    -6,    88,    66,    83,    87,    89,   -82,    40,
      40,    15,   -82,   -82,    -5,     6,   -82,    40,    27,   -82,
      40,   -82,    40,    40,    40,    40,    40,    93,    80,    84,
      57,   -82,    37,    37,    85,   -82,    88,    66,    83,    87,
      89,   -82,    86,    40,   -82,   101,   -82,   -82,   -82,    93,
      37,   -82
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       5,     0,     0,     1,     0,     0,     0,     2,     9,     0,
       0,     0,     7,     0,     0,     8,    20,    10,     0,     7,
       0,     0,     3,     0,     0,    22,    13,     0,     0,    14,
       4,     0,     6,     0,     0,     0,    16,    12,     0,    11,
       0,     0,     0,     0,     0,     0,    31,    22,    17,    21,
       0,     0,    19,     0,     0,    47,     0,    48,    49,    29,
       0,     0,     0,    33,    35,    37,    39,    41,    43,    52,
       0,     0,    15,    18,     0,     0,    44,    52,     0,    45,
       0,    28,     0,     0,     0,     0,     0,    54,     0,    51,
       0,    30,     0,     0,     0,    46,    32,    34,    36,    38,
      40,    42,     0,     0,    23,    24,    26,    50,    27,    53,
       0,    25
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -82,   -82,   -82,    -7,   -82,   102,   -82,    90,   -82,   -82,
     -82,    75,   -81,   -44,    28,    31,    32,    26,    33,   -55,
      35,   -82
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    13,     7,     8,     9,    28,    29,    17,
      25,    35,    49,    87,    63,    64,    65,    66,    67,    68,
      88,    89
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      62,    76,    80,    80,    20,    42,    79,    43,    44,    74,
      75,   105,   106,    81,    80,    10,    78,    92,    45,    42,
      46,    43,    44,     3,    47,    48,    90,    41,    93,   111,
      12,   101,    45,    51,    46,    80,    22,    23,    47,    91,
      55,    42,    56,    43,    44,    11,    57,    58,    59,    95,
      60,    55,     4,    56,    45,    61,    46,    57,    58,   109,
      47,    60,     4,    26,    14,    80,    61,    69,    33,     5,
      16,    70,    18,    34,     6,    27,   104,    21,    83,    19,
      30,    23,    52,    23,    73,    23,    24,    32,    36,    37,
      39,    40,    38,    50,    53,    54,    72,    82,    77,    84,
      85,    80,   102,    86,   103,   108,   110,   107,    96,    15,
      99,    31,    94,    97,     0,    98,     0,     0,   100,     0,
       0,     0,    71
};

static const yytype_int8 yycheck[] =
{
      44,    56,     8,     8,    11,     4,    61,     6,     7,    53,
      54,    92,    93,    19,     8,    17,    60,    22,    17,     4,
      19,     6,     7,     0,    23,    24,    70,    34,    22,   110,
      17,    86,    17,    40,    19,     8,    19,    20,    23,    24,
      11,     4,    13,     6,     7,    15,    17,    18,    19,    22,
      21,    11,     3,    13,    17,    26,    19,    17,    18,   103,
      23,    21,     3,     3,    15,     8,    26,    21,    10,    10,
      23,    25,    21,    15,    15,    15,    19,    21,    12,    17,
      19,    20,    19,    20,    19,    20,    17,    17,    17,    22,
      22,    15,    20,    15,    21,    21,    17,     9,    21,    16,
      13,     8,    22,    14,    20,    19,     5,    22,    80,     7,
      84,    21,    77,    82,    -1,    83,    -1,    -1,    85,    -1,
      -1,    -1,    47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    28,    29,     0,     3,    10,    15,    31,    32,    33,
      17,    15,    17,    30,    15,    32,    23,    36,    21,    17,
      30,    21,    19,    20,    17,    37,     3,    15,    34,    35,
      19,    34,    17,    10,    15,    38,    17,    22,    20,    22,
      15,    30,     4,     6,     7,    17,    19,    23,    24,    39,
      15,    30,    19,    21,    21,    11,    13,    17,    18,    19,
      21,    26,    40,    41,    42,    43,    44,    45,    46,    21,
      25,    38,    17,    19,    40,    40,    46,    21,    40,    46,
       8,    19,     9,    12,    16,    13,    14,    40,    47,    48,
      40,    24,    22,    22,    47,    22,    41,    42,    43,    44,
      45,    46,    22,    20,    19,    39,    39,    22,    19,    40,
       5,    39
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    27,    28,    29,    29,    29,    30,    30,    31,    31,
      32,    33,    33,    34,    34,    35,    35,    36,    37,    37,
      37,    38,    38,    39,    39,    39,    39,    39,    39,    39,
      39,    39,    40,    40,    41,    41,    42,    42,    43,    43,
      44,    44,    45,    45,    46,    46,    46,    46,    46,    46,
      46,    47,    47,    48,    48
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     4,     5,     0,     3,     1,     2,     1,
       2,     5,     5,     1,     1,     4,     2,     4,     5,     4,
       0,     2,     0,     4,     5,     7,     5,     5,     3,     2,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     2,     2,     3,     1,     1,     1,
       4,     1,     0,     3,     1
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
#line 46 "src/parser.y"
    { (yyval.node) = makeNode(Prog); 
    if((yyvsp[-1].node)->firstChild == NULL){
         addChild((yyval.node), NULL);
    } else {
        addChild((yyval.node), (yyvsp[-1].node));
    }
    addChild((yyval.node), (yyvsp[0].node)); root = (yyval.node);}
#line 1209 "./src/parser.tab.c"
    break;

  case 3: /* DeclVars: DeclVars TYPE Declarateurs ';'  */
#line 57 "src/parser.y"
       { 
       (yyval.node) = (yyvsp[-3].node);
       // Vesion père unique, plusieurs fils
       Node* nodeType1 = makeNode(type);
       nodeType1->word = strdup((yyvsp[-2].word));
       addChild((yyval.node), nodeType1); addChild(nodeType1, (yyvsp[-1].node)); }
#line 1220 "./src/parser.tab.c"
    break;

  case 4: /* DeclVars: DeclVars STATIC TYPE Declarateurs ';'  */
#line 64 "src/parser.y"
                                             {yyerror("Variable globale statique"); return 1;}
#line 1226 "./src/parser.tab.c"
    break;

  case 5: /* DeclVars: %empty  */
#line 65 "src/parser.y"
       { (yyval.node) = makeNode(DeclVars); }
#line 1232 "./src/parser.tab.c"
    break;

  case 6: /* Declarateurs: Declarateurs ',' IDENT  */
#line 70 "src/parser.y"
       { (yyval.node) = (yyvsp[-2].node);
       Node* nodeIdent = makeNode(ident);
       nodeIdent->word = strdup((yyvsp[0].word)); // Autre variable liée à la première
       addSibling((yyval.node), nodeIdent); }
#line 1241 "./src/parser.tab.c"
    break;

  case 7: /* Declarateurs: IDENT  */
#line 76 "src/parser.y"
      { (yyval.node) = makeNode(ident);
       (yyval.node)->word = strdup((yyvsp[0].word)); }
#line 1248 "./src/parser.tab.c"
    break;

  case 8: /* DeclFoncts: DeclFoncts DeclFonct  */
#line 82 "src/parser.y"
       { (yyval.node) = (yyvsp[-1].node); 
       addSibling((yyval.node), (yyvsp[0].node));
       }
#line 1256 "./src/parser.tab.c"
    break;

  case 9: /* DeclFoncts: DeclFonct  */
#line 85 "src/parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1262 "./src/parser.tab.c"
    break;

  case 10: /* DeclFonct: EnTeteFonct Corps  */
#line 89 "src/parser.y"
                         { (yyval.node) = makeNode(DeclFonct); addChild((yyval.node), (yyvsp[-1].node)); addSibling((yyvsp[-1].node), (yyvsp[0].node));
		
       }
#line 1270 "./src/parser.tab.c"
    break;

  case 11: /* EnTeteFonct: TYPE IDENT '(' Parametres ')'  */
#line 96 "src/parser.y"
       { (yyval.node) = makeNode(EnTeteFonct); 
       Node* nodeType = makeNode(type);
       nodeType->word = strdup((yyvsp[-4].word));
       addChild((yyval.node), nodeType); 
       Node* nodeIdent = makeNode(ident);
       nodeIdent->word = strdup((yyvsp[-3].word));
       addChild((yyval.node), nodeIdent); 
       addSibling((yyval.node), (yyvsp[-1].node)); }
#line 1283 "./src/parser.tab.c"
    break;

  case 12: /* EnTeteFonct: VOID IDENT '(' Parametres ')'  */
#line 106 "src/parser.y"
       { 
       (yyval.node) = makeNode(Void); 
       Node* nodeIdent = makeNode(ident);
       nodeIdent->word = strdup((yyvsp[-3].word));
       addChild((yyval.node),nodeIdent); 
       addSibling((yyval.node), (yyvsp[-1].node)); }
#line 1294 "./src/parser.tab.c"
    break;

  case 13: /* Parametres: VOID  */
#line 115 "src/parser.y"
            {(yyval.node) = makeNode(Void); }
#line 1300 "./src/parser.tab.c"
    break;

  case 14: /* Parametres: ListTypVar  */
#line 116 "src/parser.y"
                  { (yyval.node) = makeNode(ListTypVar); addChild((yyval.node), (yyvsp[0].node)); }
#line 1306 "./src/parser.tab.c"
    break;

  case 15: /* ListTypVar: ListTypVar ',' TYPE IDENT  */
#line 121 "src/parser.y"
       { (yyval.node) = (yyvsp[-3].node);
       Node* nodeType = makeNode(type);
       nodeType->word = strdup((yyvsp[-1].word)); 
       Node* nodeIdent = makeNode(ident);
       nodeIdent->word = strdup((yyvsp[0].word));
       addSibling((yyval.node), nodeType);   addSibling(nodeType, nodeIdent); }
#line 1317 "./src/parser.tab.c"
    break;

  case 16: /* ListTypVar: TYPE IDENT  */
#line 128 "src/parser.y"
                  { 
       Node* nodeType = makeNode(type);
       nodeType->word = strdup((yyvsp[-1].word));
       (yyval.node) = nodeType;
       Node* nodeIdent = makeNode(ident);
       nodeIdent->word = strdup((yyvsp[0].word));
       addSibling(nodeType, nodeIdent);}
#line 1329 "./src/parser.tab.c"
    break;

  case 17: /* Corps: '{' DeclVarsLocale SuiteInstr '}'  */
#line 138 "src/parser.y"
                                      { (yyval.node) = makeNode(Corps); 
    if ((yyvsp[-2].node)->firstChild == NULL){
        addChild((yyval.node), NULL);
    } else {
         addChild((yyval.node), (yyvsp[-2].node));
    }
    if ((yyvsp[-1].node)->firstChild == NULL){
     addChild((yyval.node), NULL);
    } else {
        addChild((yyval.node), (yyvsp[-1].node));
    }
    }
#line 1346 "./src/parser.tab.c"
    break;

  case 18: /* DeclVarsLocale: DeclVarsLocale STATIC TYPE Declarateurs ';'  */
#line 153 "src/parser.y"
                                                    { (yyval.node) = (yyvsp[-4].node);
        Node* elem = makeNode(Static);
        Node* nodeType = makeNode(type);
        nodeType->word = strdup((yyvsp[-2].word));
        addChild(elem,nodeType);
        addChild((yyval.node),elem);
        addChild(nodeType,(yyvsp[-1].node));}
#line 1358 "./src/parser.tab.c"
    break;

  case 19: /* DeclVarsLocale: DeclVarsLocale TYPE Declarateurs ';'  */
#line 160 "src/parser.y"
                                             { 
        (yyval.node) = (yyvsp[-3].node);
        Node* elem = makeNode(NonStatic); 
        Node* nodeType = makeNode(type);
        nodeType->word = strdup((yyvsp[-2].word));
        addChild(elem,nodeType);
        addChild((yyval.node), elem); 
        addChild(nodeType, (yyvsp[-1].node)); }
#line 1371 "./src/parser.tab.c"
    break;

  case 20: /* DeclVarsLocale: %empty  */
#line 168 "src/parser.y"
        {(yyval.node) = makeNode(DeclVarsLocale);}
#line 1377 "./src/parser.tab.c"
    break;

  case 21: /* SuiteInstr: SuiteInstr Instr  */
#line 172 "src/parser.y"
                        { (yyval.node) = (yyvsp[-1].node); addChild((yyval.node), (yyvsp[0].node)); }
#line 1383 "./src/parser.tab.c"
    break;

  case 22: /* SuiteInstr: %empty  */
#line 173 "src/parser.y"
      { (yyval.node) = makeNode(Instr); }
#line 1389 "./src/parser.tab.c"
    break;

  case 23: /* Instr: IDENT '=' Exp ';'  */
#line 177 "src/parser.y"
                         {  
       (yyval.node) = makeNode(ident);
       (yyval.node)->word = strdup((yyvsp[-3].word));
       addChild((yyval.node), (yyvsp[-1].node)); }
#line 1398 "./src/parser.tab.c"
    break;

  case 24: /* Instr: IF '(' Exp ')' Instr  */
#line 182 "src/parser.y"
                                     { (yyval.node) = makeNode(If);
        Node* exp = makeNode (Exp);
        addChild(exp, (yyvsp[-2].node));
		addChild((yyval.node), exp);
		addChild((yyval.node), (yyvsp[0].node)); 
        }
#line 1409 "./src/parser.tab.c"
    break;

  case 25: /* Instr: IF '(' Exp ')' Instr ELSE Instr  */
#line 189 "src/parser.y"
                                                  { 
       (yyval.node) = makeNode(If);
       Node* exp = makeNode (Exp);
       Node* nodeElse = makeNode(Else);
       addChild(exp,(yyvsp[-4].node));
       addChild((yyval.node),exp);
       addChild((yyval.node),(yyvsp[-2].node));
       addChild(nodeElse,(yyvsp[0].node));
       addSibling((yyval.node),nodeElse); 
       }
#line 1424 "./src/parser.tab.c"
    break;

  case 26: /* Instr: WHILE '(' Exp ')' Instr  */
#line 202 "src/parser.y"
                               { 
        (yyval.node) = makeNode(While);
        Node* exp = makeNode (Exp);
        addChild(exp,(yyvsp[-2].node));
        addChild((yyval.node),exp);
        addChild((yyval.node),(yyvsp[0].node));
    }
#line 1436 "./src/parser.tab.c"
    break;

  case 27: /* Instr: IDENT '(' Arguments ')' ';'  */
#line 210 "src/parser.y"
                                   { 
       Node* nodeIdent = makeNode(ident);
       nodeIdent->word = strdup((yyvsp[-4].word));
       (yyval.node) = nodeIdent;
       addChild((yyval.node), (yyvsp[-2].node));
    }
#line 1447 "./src/parser.tab.c"
    break;

  case 28: /* Instr: RETURN Exp ';'  */
#line 218 "src/parser.y"
                      {  (yyval.node) = makeNode(Return); addChild((yyval.node), (yyvsp[-1].node)); }
#line 1453 "./src/parser.tab.c"
    break;

  case 29: /* Instr: RETURN ';'  */
#line 220 "src/parser.y"
                  { (yyval.node) = makeNode(Return); }
#line 1459 "./src/parser.tab.c"
    break;

  case 30: /* Instr: '{' SuiteInstr '}'  */
#line 222 "src/parser.y"
                          { (yyval.node) = (yyvsp[-1].node); }
#line 1465 "./src/parser.tab.c"
    break;

  case 31: /* Instr: ';'  */
#line 224 "src/parser.y"
           { (yyval.node) = makeNode(Instr); }
#line 1471 "./src/parser.tab.c"
    break;

  case 32: /* Exp: Exp OR TB  */
#line 228 "src/parser.y"
              { Node* NodeOr = makeNode(Or);
        addChild(NodeOr,(yyvsp[-2].node));
        addChild(NodeOr,(yyvsp[0].node));
        (yyval.node) = NodeOr;
    }
#line 1481 "./src/parser.tab.c"
    break;

  case 33: /* Exp: TB  */
#line 233 "src/parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 1487 "./src/parser.tab.c"
    break;

  case 34: /* TB: TB AND FB  */
#line 237 "src/parser.y"
              { Node* NodeAnd = makeNode(And);
        addChild(NodeAnd,(yyvsp[-2].node));
        addChild(NodeAnd,(yyvsp[0].node));
        (yyval.node) = NodeAnd;
    }
#line 1497 "./src/parser.tab.c"
    break;

  case 35: /* TB: FB  */
#line 242 "src/parser.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 1503 "./src/parser.tab.c"
    break;

  case 36: /* FB: FB EQ M  */
#line 246 "src/parser.y"
            { Node * nodeEq = makeNode(Eq);
        nodeEq->word = strdup((yyvsp[-1].word));
        addChild(nodeEq,(yyvsp[-2].node));
        addChild(nodeEq,(yyvsp[0].node));
        (yyval.node) = nodeEq;
    }
#line 1514 "./src/parser.tab.c"
    break;

  case 37: /* FB: M  */
#line 252 "src/parser.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 1520 "./src/parser.tab.c"
    break;

  case 38: /* M: M ORDER E  */
#line 256 "src/parser.y"
              { 
        Node* nodeOrder = makeNode(Order);
        nodeOrder->word = strdup((yyvsp[-1].word));
        addChild(nodeOrder,(yyvsp[-2].node)); 
        addChild(nodeOrder, (yyvsp[0].node));
        (yyval.node) = nodeOrder; 
    }
#line 1532 "./src/parser.tab.c"
    break;

  case 39: /* M: E  */
#line 263 "src/parser.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 1538 "./src/parser.tab.c"
    break;

  case 40: /* E: E ADDSUB T  */
#line 267 "src/parser.y"
               {
        Node* operator = makeNode(Addsub);
        operator->word = strdup((yyvsp[-1].word));
        addChild(operator,(yyvsp[-2].node)); 
        addChild(operator, (yyvsp[0].node));
        (yyval.node) = operator; 
    }
#line 1550 "./src/parser.tab.c"
    break;

  case 41: /* E: T  */
#line 274 "src/parser.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 1556 "./src/parser.tab.c"
    break;

  case 42: /* T: T DIVSTAR F  */
#line 278 "src/parser.y"
                { Node* operator = makeNode(divstar);
        operator->word = strdup((yyvsp[-1].word));
        addChild(operator,(yyvsp[-2].node)); 
        addChild(operator, (yyvsp[0].node));
        (yyval.node) = operator; 
    }
#line 1567 "./src/parser.tab.c"
    break;

  case 43: /* T: F  */
#line 284 "src/parser.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 1573 "./src/parser.tab.c"
    break;

  case 44: /* F: ADDSUB F  */
#line 288 "src/parser.y"
             { 
        Node* operator = makeNode(Addsub);
        operator->word = strdup((yyvsp[-1].word));
        addChild(operator,(yyvsp[0].node)); 
        (yyval.node) = operator; 
        }
#line 1584 "./src/parser.tab.c"
    break;

  case 45: /* F: '!' F  */
#line 294 "src/parser.y"
             {Node* notNode = makeNode(Not);
           notNode->word = strdup("!"); 
           addChild(notNode,(yyvsp[0].node));
           (yyval.node) = notNode;
           }
#line 1594 "./src/parser.tab.c"
    break;

  case 46: /* F: '(' Exp ')'  */
#line 300 "src/parser.y"
                   { (yyval.node) = (yyvsp[-1].node); }
#line 1600 "./src/parser.tab.c"
    break;

  case 47: /* F: NUM  */
#line 301 "src/parser.y"
           { 
        (yyval.node) = makeNode(Num); 
        (yyval.node)->value = (yyvsp[0].num); 
        
    }
#line 1610 "./src/parser.tab.c"
    break;

  case 48: /* F: IDENT  */
#line 306 "src/parser.y"
             { (yyval.node) = makeNode(ident);
               (yyval.node)->word = strdup((yyvsp[0].word)); }
#line 1617 "./src/parser.tab.c"
    break;

  case 49: /* F: CHARACTER  */
#line 308 "src/parser.y"
                 {(yyval.node) = makeNode(Character);
       (yyval.node)->word = strdup((yyvsp[0].word));}
#line 1624 "./src/parser.tab.c"
    break;

  case 50: /* F: IDENT '(' Arguments ')'  */
#line 310 "src/parser.y"
                               {(yyval.node) = makeNode(ident);
       (yyval.node)->word = strdup((yyvsp[-3].word));
       //Node nodeArg = makeNode(Arguments);
       addChild((yyval.node),(yyvsp[-1].node));}
#line 1633 "./src/parser.tab.c"
    break;

  case 51: /* Arguments: ListExp  */
#line 317 "src/parser.y"
            { (yyval.node) = makeNode(Arguments); addChild((yyval.node),(yyvsp[0].node));}
#line 1639 "./src/parser.tab.c"
    break;

  case 52: /* Arguments: %empty  */
#line 318 "src/parser.y"
      { (yyval.node) = makeNode(Void); }
#line 1645 "./src/parser.tab.c"
    break;

  case 53: /* ListExp: ListExp ',' Exp  */
#line 322 "src/parser.y"
                    { (yyval.node) = (yyvsp[-2].node); addSibling((yyval.node), (yyvsp[0].node)); }
#line 1651 "./src/parser.tab.c"
    break;

  case 54: /* ListExp: Exp  */
#line 323 "src/parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1657 "./src/parser.tab.c"
    break;


#line 1661 "./src/parser.tab.c"

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

#line 326 "src/parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Erreur syntaxique à la ligne %d  (position %d : '%s')\n", lineno, line, yytext ? yytext : "inconnu");
    if (word) {
        fprintf(stderr, "%s\n", word);

        for(int i =0; i< line - 2;i++){
            fprintf(stderr, " ");
        }
        fprintf(stderr, "-^\n");
    }
}


