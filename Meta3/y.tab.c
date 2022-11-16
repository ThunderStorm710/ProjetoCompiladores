/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "jucompiler.y"

/************Autores*************
* Pedro Ascensão   -   2020233012
* Leonardo Pina    -   2019234318
*********************************/
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "Tree.h"

    int yylex(void);
    void yyerror (const char *s);

    node *head = NULL;
    node *node1 = NULL;
    node *node2 = NULL;
    node *node3 = NULL;

#line 89 "y.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    COMMA = 258,
    MINUS = 259,
    RSHIFT = 260,
    LSHIFT = 261,
    LT = 262,
    LSQ = 263,
    LPAR = 264,
    LE = 265,
    LBRACE = 266,
    GT = 267,
    GE = 268,
    DIV = 269,
    STAR = 270,
    EQ = 271,
    ASSIGN = 272,
    AND = 273,
    SEMICOLON = 274,
    RSQ = 275,
    RPAR = 276,
    RBRACE = 277,
    PLUS = 278,
    OR = 279,
    NOT = 280,
    NE = 281,
    MOD = 282,
    XOR = 283,
    ARROW = 284,
    BOOL = 285,
    INT = 286,
    IF = 287,
    ELSE = 288,
    DOUBLE = 289,
    DOTLENGTH = 290,
    PRINT = 291,
    WHILE = 292,
    VOID = 293,
    STATIC = 294,
    RETURN = 295,
    PUBLIC = 296,
    PARSEINT = 297,
    CLASS = 298,
    BOOLLIT = 299,
    STRLIT = 300,
    ID = 301,
    INTLIT = 302,
    REALLIT = 303,
    RESERVED = 304,
    IFX = 305
  };
#endif
/* Tokens.  */
#define COMMA 258
#define MINUS 259
#define RSHIFT 260
#define LSHIFT 261
#define LT 262
#define LSQ 263
#define LPAR 264
#define LE 265
#define LBRACE 266
#define GT 267
#define GE 268
#define DIV 269
#define STAR 270
#define EQ 271
#define ASSIGN 272
#define AND 273
#define SEMICOLON 274
#define RSQ 275
#define RPAR 276
#define RBRACE 277
#define PLUS 278
#define OR 279
#define NOT 280
#define NE 281
#define MOD 282
#define XOR 283
#define ARROW 284
#define BOOL 285
#define INT 286
#define IF 287
#define ELSE 288
#define DOUBLE 289
#define DOTLENGTH 290
#define PRINT 291
#define WHILE 292
#define VOID 293
#define STATIC 294
#define RETURN 295
#define PUBLIC 296
#define PARSEINT 297
#define CLASS 298
#define BOOLLIT 299
#define STRLIT 300
#define ID 301
#define INTLIT 302
#define REALLIT 303
#define RESERVED 304
#define IFX 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "jucompiler.y"

    struct token* token;
    struct node* node;

#line 246 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   396

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  82
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  168

#define YYUNDEFTOK  2
#define YYMAXUTOK   305


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    49,    49,    55,    56,    57,    58,    62,    67,    74,
      77,    78,    87,    88,    89,    93,   100,   109,   116,   127,
     136,   147,   148,   158,   162,   163,   164,   168,   176,   177,
     185,   189,   194,   201,   207,   210,   214,   216,   218,   220,
     222,   226,   232,   235,   237,   243,   248,   255,   259,   260,
     264,   271,   278,   281,   283,   286,   289,   292,   295,   298,
     301,   304,   307,   310,   313,   316,   319,   322,   325,   328,
     331,   334,   337,   340,   343,   344,   345,   346,   349,   354,
     357,   360,   363
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "COMMA", "MINUS", "RSHIFT", "LSHIFT",
  "LT", "LSQ", "LPAR", "LE", "LBRACE", "GT", "GE", "DIV", "STAR", "EQ",
  "ASSIGN", "AND", "SEMICOLON", "RSQ", "RPAR", "RBRACE", "PLUS", "OR",
  "NOT", "NE", "MOD", "XOR", "ARROW", "BOOL", "INT", "IF", "ELSE",
  "DOUBLE", "DOTLENGTH", "PRINT", "WHILE", "VOID", "STATIC", "RETURN",
  "PUBLIC", "PARSEINT", "CLASS", "BOOLLIT", "STRLIT", "ID", "INTLIT",
  "REALLIT", "RESERVED", "IFX", "$accept", "Program", "ProgramRec",
  "MethodDecl", "FieldDecl", "FieldDeclRec", "Type", "MethodHeader",
  "FormalParams", "FormalParamsRec", "MethodBody", "MethodBodyRec",
  "VarDecl", "VarDeclRec", "Statement", "StatementRec", "MethodInvocation",
  "MethodInvocationRec", "Assignment", "ParseArgs", "Expr", "Expr2", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
# endif

#define YYPACT_NINF (-56)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -30,   -25,    22,    25,   -56,   -56,     4,    21,   -56,   -56,
       5,   -56,   -56,   -56,    45,   -56,   -56,   -56,    -4,    28,
      56,    59,    77,   -56,   -56,    50,    88,    24,   119,   -56,
      79,    42,    71,   -56,    75,    57,   -56,    92,   -56,   -56,
     -56,    98,   108,   112,   175,   115,    30,    80,   -56,   -56,
     113,   125,   126,   111,   -56,   -56,   -56,   -56,   -56,   141,
     193,   182,   193,   211,    81,   -56,   211,   211,   -56,     3,
     -56,   -56,   -56,   -56,   -56,   127,   256,    18,    68,   193,
     -56,   -56,   -56,   -56,   101,   131,   -56,   -56,   136,   137,
     145,   146,     0,   -56,   147,   148,   -56,   -56,   -56,   -56,
     211,   211,   211,   211,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   211,   149,   140,   150,   -56,
     -56,   -56,    27,   -56,   109,   153,   143,   155,   153,   -56,
     -56,    51,    14,    14,   369,   369,   369,   369,   -56,   -56,
     355,   306,    51,   281,   355,   -56,   331,   -56,   193,   -56,
      13,   129,   -56,   130,   159,   -56,   -56,   -56,   160,   193,
     -56,   -56,   -56,   153,   161,   -56,   -56,   -56
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     0,     0,     6,     2,
       0,     4,     5,     9,     0,    12,    13,    14,     0,     0,
       0,     0,    10,    24,     7,     0,     0,     0,     0,    16,
       0,     0,     0,    15,     0,     0,     8,     0,    43,    36,
      23,     0,     0,     0,     0,     0,     0,     0,    26,    25,
       0,     0,     0,     0,    21,    18,    17,    11,    42,     0,
       0,     0,     0,     0,     0,    34,     0,     0,    81,    77,
      79,    80,    75,    53,    76,     0,    54,     0,     0,     0,
      28,    37,    38,    39,     0,    19,    30,    44,     0,     0,
       0,     0,    77,    71,     0,     0,    73,    72,    78,    35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    45,
      48,    50,     0,    20,     0,     0,     0,     0,     0,    82,
      74,    56,    64,    63,    69,    68,    67,    66,    58,    57,
      65,    60,    55,    61,    70,    59,    62,    52,     0,    47,
       0,     0,    27,     0,    31,    41,    40,    33,     0,     0,
      46,    29,    22,     0,     0,    49,    32,    51
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -56,   -56,   -56,   -56,   -56,   -56,   -11,   -56,   162,   -56,
     -56,   -56,   -56,   -56,   -55,   -56,   -28,   -56,   -27,   -26,
     -54,   -52
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,    11,    12,    27,    31,    20,    32,    85,
      24,    28,    48,   122,    49,    59,    72,   150,    73,    74,
      75,    76
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      50,    51,    52,    19,    87,     7,    88,    90,    91,    78,
      95,    93,    78,     1,    96,    97,   159,    47,   100,   116,
      79,     3,     4,     8,   120,   121,     9,    35,   107,   108,
     151,    50,    51,    52,   160,    98,     5,   111,    98,    78,
      13,   114,    21,    36,    14,    10,   152,    79,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   117,   107,   108,    23,    25,   118,
     154,    29,    63,   157,    22,    15,    16,    64,   114,    17,
      15,    16,    94,    18,    17,    63,    26,    53,    54,   119,
      64,    66,    55,    67,   158,    30,    56,    50,    51,    52,
      50,    51,    52,    57,    66,   165,    67,    60,   166,    33,
      45,    58,    68,   153,    69,    70,    71,    61,    15,    16,
      37,    62,    17,    45,    77,    68,    80,    69,    70,    71,
      38,    84,    81,    30,   124,    50,    51,    52,    39,    15,
      16,    40,    37,    17,    82,    83,    99,   123,   148,    15,
      16,    41,    38,    17,    37,    42,    43,   125,   126,    44,
      39,    45,   155,    86,    38,    46,   127,   128,   129,   130,
     147,   149,    39,    41,   156,   161,   162,    42,    43,    63,
     164,    44,   167,    45,    64,    41,    63,    46,    34,    42,
      43,    64,   163,    44,    65,    45,     0,    63,    66,    46,
      67,     0,    64,     0,     0,    66,     0,    67,     0,     0,
       0,     0,     0,     0,     0,    63,    66,    45,    67,    68,
      64,    69,    70,    71,    45,     0,    68,    89,    69,    70,
      71,     0,     0,     0,    66,    45,    67,    68,     0,    69,
      70,    71,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    45,     0,    68,     0,    92,    70,    71,
     100,   101,   102,   103,     0,     0,   104,     0,   105,   106,
     107,   108,   109,     0,   110,     0,     0,     0,     0,   111,
     112,     0,   113,   114,   115,   100,   101,   102,   103,     0,
       0,   104,     0,   105,   106,   107,   108,   109,     0,   110,
       0,     0,     0,     0,   111,     0,     0,   113,   114,   115,
     100,   101,   102,   103,     0,     0,   104,     0,   105,   106,
     107,   108,   109,     0,     0,     0,     0,     0,     0,   111,
       0,     0,   113,   114,   115,   100,   101,   102,   103,     0,
       0,   104,     0,   105,   106,   107,   108,   109,     0,     0,
       0,     0,     0,     0,   111,     0,     0,   113,   114,   100,
     101,   102,   103,     0,     0,   104,     0,   105,   106,   107,
     108,     0,     0,   100,   101,   102,     0,     0,   111,     0,
       0,     0,   114,   107,   108,     0,     0,     0,     0,     0,
       0,     0,   111,     0,     0,     0,   114
};

static const yytype_int16 yycheck[] =
{
      28,    28,    28,    14,    59,     1,    60,    61,    62,     9,
      64,    63,     9,    43,    66,    67,     3,    28,     4,     1,
      17,    46,     0,    19,    78,    79,    22,     3,    14,    15,
       3,    59,    59,    59,    21,    35,    11,    23,    35,     9,
      19,    27,    46,    19,    39,    41,    19,    17,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,    46,    14,    15,    11,     9,     1,
     125,    21,     4,   128,    46,    30,    31,     9,    27,    34,
      30,    31,     1,    38,    34,     4,     9,     8,    46,    21,
       9,    23,    21,    25,   148,    45,    21,   125,   125,   125,
     128,   128,   128,    46,    23,   159,    25,     9,   163,    21,
      42,    19,    44,   124,    46,    47,    48,     9,    30,    31,
       1,     9,    34,    42,     9,    44,    46,    46,    47,    48,
      11,    20,    19,    45,     3,   163,   163,   163,    19,    30,
      31,    22,     1,    34,    19,    19,    19,    46,     8,    30,
      31,    32,    11,    34,     1,    36,    37,    21,    21,    40,
      19,    42,    19,    22,    11,    46,    21,    21,    21,    21,
      21,    21,    19,    32,    19,    46,    46,    36,    37,     4,
      20,    40,    21,    42,     9,    32,     4,    46,    26,    36,
      37,     9,    33,    40,    19,    42,    -1,     4,    23,    46,
      25,    -1,     9,    -1,    -1,    23,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     4,    23,    42,    25,    44,
       9,    46,    47,    48,    42,    -1,    44,    45,    46,    47,
      48,    -1,    -1,    -1,    23,    42,    25,    44,    -1,    46,
      47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    42,    -1,    44,    -1,    46,    47,    48,
       4,     5,     6,     7,    -1,    -1,    10,    -1,    12,    13,
      14,    15,    16,    -1,    18,    -1,    -1,    -1,    -1,    23,
      24,    -1,    26,    27,    28,     4,     5,     6,     7,    -1,
      -1,    10,    -1,    12,    13,    14,    15,    16,    -1,    18,
      -1,    -1,    -1,    -1,    23,    -1,    -1,    26,    27,    28,
       4,     5,     6,     7,    -1,    -1,    10,    -1,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      -1,    -1,    26,    27,    28,     4,     5,     6,     7,    -1,
      -1,    10,    -1,    12,    13,    14,    15,    16,    -1,    -1,
      -1,    -1,    -1,    -1,    23,    -1,    -1,    26,    27,     4,
       5,     6,     7,    -1,    -1,    10,    -1,    12,    13,    14,
      15,    -1,    -1,     4,     5,     6,    -1,    -1,    23,    -1,
      -1,    -1,    27,    14,    15,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    27
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    43,    52,    46,     0,    11,    53,     1,    19,    22,
      41,    54,    55,    19,    39,    30,    31,    34,    38,    57,
      58,    46,    46,    11,    61,     9,     9,    56,    62,    21,
      45,    57,    59,    21,    59,     3,    19,     1,    11,    19,
      22,    32,    36,    37,    40,    42,    46,    57,    63,    65,
      67,    69,    70,     8,    46,    21,    21,    46,    19,    66,
       9,     9,     9,     4,     9,    19,    23,    25,    44,    46,
      47,    48,    67,    69,    70,    71,    72,     9,     9,    17,
      46,    19,    19,    19,    20,    60,    22,    65,    71,    45,
      71,    71,    46,    72,     1,    71,    72,    72,    35,    19,
       4,     5,     6,     7,    10,    12,    13,    14,    15,    16,
      18,    23,    24,    26,    27,    28,     1,    46,     1,    21,
      71,    71,    64,    46,     3,    21,    21,    21,    21,    21,
      21,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    21,     8,    21,
      68,     3,    19,    57,    65,    19,    19,    65,    71,     3,
      21,    46,    46,    33,    20,    71,    65,    21
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    53,    53,    54,    55,    55,
      56,    56,    57,    57,    57,    58,    58,    58,    58,    59,
      59,    60,    60,    61,    62,    62,    62,    63,    64,    64,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    66,    66,    67,    67,    67,    68,    68,
      69,    70,    70,    71,    71,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     5,     0,     2,     2,     2,     4,     6,     2,
       0,     3,     1,     1,     1,     4,     4,     5,     5,     3,
       4,     0,     4,     3,     0,     2,     2,     4,     0,     3,
       3,     5,     7,     5,     2,     3,     1,     2,     2,     2,
       5,     5,     2,     0,     2,     3,     5,     4,     0,     3,
       3,     7,     4,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     3,     1,     1,     1,     2,     1,
       1,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
  case 2:
#line 49 "jucompiler.y"
                                                                            {head = criaNode("Program", NULL, 0, 0);
                                                                            node1 = criaNode("Id", (yyvsp[-3].token)->valor, (yyvsp[-3].token)->linha, (yyvsp[-3].token)->coluna);
                                                                            addChild(head, node1);
                                                                            addBrother(node1, (yyvsp[-1].node));
                                                                            libertaToken((yyvsp[-3].token));}
#line 1585 "y.tab.c"
    break;

  case 3:
#line 55 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("NULL", NULL, 0, 0);}
#line 1591 "y.tab.c"
    break;

  case 4:
#line 56 "jucompiler.y"
                                                                            {(yyval.node) = (yyvsp[-1].node); addBrother((yyvsp[-1].node), (yyvsp[0].node));}
#line 1597 "y.tab.c"
    break;

  case 5:
#line 57 "jucompiler.y"
                                                                            {(yyval.node) = (yyvsp[-1].node); addBrother((yyvsp[-1].node), (yyvsp[0].node));}
#line 1603 "y.tab.c"
    break;

  case 6:
#line 58 "jucompiler.y"
                                                                            {(yyval.node) = (yyvsp[-1].node);}
#line 1609 "y.tab.c"
    break;

  case 7:
#line 62 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("MethodDecl", NULL, 0, 0);
                                                                            addChild((yyval.node), (yyvsp[-1].node));
                                                                            addBrother((yyvsp[-1].node), (yyvsp[0].node));}
#line 1617 "y.tab.c"
    break;

  case 8:
#line 67 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("FieldDecl", NULL, 0, 0);
                                                                            addChild((yyval.node), (yyvsp[-3].node));
                                                                            node1 = criaNode("Id", (yyvsp[-2].token)->valor, (yyvsp[-2].token)->linha, (yyvsp[-2].token)->coluna);
                                                                            addBrother((yyvsp[-3].node), node1);
                                                                            joinType((yyvsp[-3].node), (yyvsp[-1].node));
                                                                            addBrother((yyval.node), (yyvsp[-1].node));
                                                                            libertaToken((yyvsp[-2].token));}
#line 1629 "y.tab.c"
    break;

  case 9:
#line 74 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Error", NULL, 0, 0);}
#line 1635 "y.tab.c"
    break;

  case 10:
#line 77 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("NULL", NULL, 0, 0);}
#line 1641 "y.tab.c"
    break;

  case 11:
#line 78 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("FieldDecl", NULL, 0, 0);
                                                                            addBrother((yyvsp[-2].node), (yyval.node));
                                                                            node1 = criaNode("Id", (yyvsp[0].token)->valor, (yyvsp[0].token)->linha, (yyvsp[0].token)->coluna);
                                                                            addChild((yyval.node), node1);
                                                                            (yyval.node) = (yyvsp[-2].node); 
                                                                            libertaToken((yyvsp[0].token));}
#line 1652 "y.tab.c"
    break;

  case 12:
#line 87 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Bool", NULL, 0, 0);}
#line 1658 "y.tab.c"
    break;

  case 13:
#line 88 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Int", NULL, 0, 0);}
#line 1664 "y.tab.c"
    break;

  case 14:
#line 89 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Double", NULL, 0, 0);}
#line 1670 "y.tab.c"
    break;

  case 15:
#line 93 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("MethodHeader", NULL, 0, 0);
                                                                            addChild((yyval.node), (yyvsp[-3].node));
                                                                            node1 = criaNode("Id", (yyvsp[-2].token)->valor, (yyvsp[-2].token)->linha, (yyvsp[-2].token)->coluna);
                                                                            addBrother((yyvsp[-3].node), node1);
                                                                            addBrother(node1, criaNode("MethodParams", NULL, 0, 0));
                                                                            libertaToken((yyvsp[-2].token));}
#line 1681 "y.tab.c"
    break;

  case 16:
#line 100 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("MethodHeader", NULL, 0, 0);
                                                                            node1 = criaNode("Void", NULL, (yyvsp[-3].token)->linha, (yyvsp[-3].token)->coluna);
                                                                            addChild((yyval.node), node1);
                                                                            node2 = criaNode("Id", (yyvsp[-2].token)->valor, (yyvsp[-2].token)->linha, (yyvsp[-2].token)->coluna);
                                                                            addBrother(node1, node2);
                                                                            addBrother(node2, criaNode("MethodParams", NULL, 0, 0));
                                                                            libertaToken((yyvsp[-3].token));
                                                                            libertaToken((yyvsp[-2].token));}
#line 1694 "y.tab.c"
    break;

  case 17:
#line 109 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("MethodHeader", NULL, 0, 0);
                                                                            addChild((yyval.node), (yyvsp[-4].node));
                                                                            node1 = criaNode("Id", (yyvsp[-3].token)->valor, (yyvsp[-3].token)->linha, (yyvsp[-3].token)->coluna);
                                                                            addBrother((yyvsp[-4].node), node1);
                                                                            addBrother(node1, (yyvsp[-1].node));
                                                                            libertaToken((yyvsp[-3].token));}
#line 1705 "y.tab.c"
    break;

  case 18:
#line 116 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("MethodHeader", NULL, 0, 0);
                                                                            node1 = criaNode("Void", NULL, (yyvsp[-4].token)->linha, (yyvsp[-4].token)->coluna);
                                                                            addChild((yyval.node), node1);
                                                                            node2 = criaNode("Id", (yyvsp[-3].token)->valor, (yyvsp[-3].token)->linha, (yyvsp[-3].token)->coluna);
                                                                            addBrother(node1, node2);
                                                                            addBrother(node2, (yyvsp[-1].node));
                                                                            libertaToken((yyvsp[-4].token));
                                                                            libertaToken((yyvsp[-3].token));}
#line 1718 "y.tab.c"
    break;

  case 19:
#line 127 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("MethodParams", NULL, 0, 0);
                                                                            node1 = criaNode("ParamDecl", NULL, 0, 0);
                                                                            addChild((yyval.node), node1);
                                                                            node2 = criaNode("Id", (yyvsp[-1].token)->valor, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addBrother((yyvsp[-2].node), node2);
                                                                            addChild(node1, (yyvsp[-2].node));
                                                                            addBrother(node1, (yyvsp[0].node));
                                                                            libertaToken((yyvsp[-1].token));}
#line 1731 "y.tab.c"
    break;

  case 20:
#line 136 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("MethodParams", NULL, 0, 0);
                                                                            node1 = criaNode("ParamDecl", NULL, 0, 0);
                                                                            addChild((yyval.node), node1);
                                                                            node2 = criaNode("StringArray", NULL, (yyvsp[-3].token)->linha, (yyvsp[-3].token)->coluna);
                                                                            addChild(node1, node2);
                                                                            node3 = criaNode("Id", (yyvsp[0].token)->valor, (yyvsp[0].token)->linha, (yyvsp[0].token)->coluna);
                                                                            addBrother(node2, node3);
                                                                            libertaToken((yyvsp[-3].token));
                                                                            libertaToken((yyvsp[0].token));}
#line 1745 "y.tab.c"
    break;

  case 21:
#line 147 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("NULL", NULL, 0, 0);}
#line 1751 "y.tab.c"
    break;

  case 22:
#line 148 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("ParamDecl", NULL, 0, 0);
                                                                            node1 = criaNode("Id", (yyvsp[0].token)->valor, (yyvsp[0].token)->linha, (yyvsp[0].token)->coluna);
                                                                            addChild((yyval.node), (yyvsp[-1].node));
                                                                            addBrother((yyvsp[-1].node), node1);
                                                                            addBrother((yyvsp[-3].node), (yyval.node));
                                                                            (yyval.node) = (yyvsp[-3].node);
                                                                            libertaToken((yyvsp[0].token));}
#line 1763 "y.tab.c"
    break;

  case 23:
#line 158 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("MethodBody", NULL, 0, 0);
                                                                            addChild((yyval.node), (yyvsp[-1].node));}
#line 1770 "y.tab.c"
    break;

  case 24:
#line 162 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("NULL", NULL, 0, 0);}
#line 1776 "y.tab.c"
    break;

  case 25:
#line 163 "jucompiler.y"
                                                                            {(yyval.node) = (yyvsp[-1].node); addBrother((yyvsp[-1].node), (yyvsp[0].node));}
#line 1782 "y.tab.c"
    break;

  case 26:
#line 164 "jucompiler.y"
                                                                            {(yyval.node) = (yyvsp[-1].node); addBrother((yyvsp[-1].node), (yyvsp[0].node));}
#line 1788 "y.tab.c"
    break;

  case 27:
#line 168 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("VarDecl", NULL, 0, 0);
                                                                            addChild((yyval.node), (yyvsp[-3].node));
                                                                            node1 = criaNode("Id", (yyvsp[-2].token)->valor, (yyvsp[-2].token)->linha, (yyvsp[-2].token)->coluna);
                                                                            addBrother((yyvsp[-3].node), node1);
                                                                            joinType((yyvsp[-3].node), (yyvsp[-1].node));
                                                                            addBrother((yyval.node), (yyvsp[-1].node));
                                                                            libertaToken((yyvsp[-2].token));}
#line 1800 "y.tab.c"
    break;

  case 28:
#line 176 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("NULL", NULL, 0, 0);}
#line 1806 "y.tab.c"
    break;

  case 29:
#line 177 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("VarDecl", NULL, 0, 0);
                                                                            node1 = criaNode("Id", (yyvsp[0].token)->valor, (yyvsp[0].token)->linha, (yyvsp[0].token)->coluna);
                                                                            addChild((yyval.node), node1);
                                                                            addBrother((yyvsp[-2].node), (yyval.node));
                                                                            (yyval.node) = (yyvsp[-2].node);
                                                                            libertaToken((yyvsp[0].token));}
#line 1817 "y.tab.c"
    break;

  case 30:
#line 185 "jucompiler.y"
                                                                            {if(countBlock((yyvsp[-1].node))>2){(yyval.node) = criaNode("Block", NULL, 0, 0); addChild((yyval.node), (yyvsp[-1].node));}
                                                                            else if(countBlock((yyvsp[-1].node))==0){(yyval.node) = NULL; astreeClean((yyvsp[-1].node));}
                                                                            else{(yyval.node) = (yyvsp[-1].node);}}
#line 1825 "y.tab.c"
    break;

  case 31:
#line 189 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("If",NULL, (yyvsp[-4].token)->linha, (yyvsp[-4].token)->coluna); 
                                                                            if((yyvsp[0].node) == NULL){node1=criaNode("Block",NULL, 0, 0); addBrother((yyvsp[-2].node), node1);}
                                                                            else{addBrother((yyvsp[-2].node),(yyvsp[0].node));} addBrother((yyvsp[-2].node), criaNode("Block",NULL, 0, 0)); addChild((yyval.node),(yyvsp[-2].node));
                                                                            libertaToken((yyvsp[-4].token));}
#line 1834 "y.tab.c"
    break;

  case 32:
#line 194 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("If", NULL, (yyvsp[-6].token)->linha, (yyvsp[-6].token)->coluna); 
                                                                            if((yyvsp[-2].node) == NULL){node1=criaNode("Block", NULL, 0, 0); addBrother((yyvsp[-4].node), node1);}
                                                                            else{addBrother((yyvsp[-4].node), (yyvsp[-2].node));}
                                                                            if((yyvsp[0].node) == NULL){node1 = criaNode("Block", NULL, 0, 0); addBrother((yyvsp[-4].node), node1);}
                                                                            else{addBrother((yyvsp[-4].node), (yyvsp[0].node));} addChild((yyval.node),(yyvsp[-4].node));
                                                                            libertaToken((yyvsp[-6].token));}
#line 1845 "y.tab.c"
    break;

  case 33:
#line 201 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("While",NULL, (yyvsp[-4].token)->linha, (yyvsp[-4].token)->coluna);
                                                                            if((yyvsp[0].node) == NULL){node1=criaNode("Block",NULL, 0, 0); addBrother((yyvsp[-2].node), node1);}
                                                                            else{addBrother((yyvsp[-2].node),(yyvsp[0].node));}
                                                                            addChild((yyval.node),(yyvsp[-2].node));
                                                                            libertaToken((yyvsp[-4].token));}
#line 1855 "y.tab.c"
    break;

  case 34:
#line 207 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Return", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            libertaToken((yyvsp[-1].token));}
#line 1862 "y.tab.c"
    break;

  case 35:
#line 210 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Return", NULL, (yyvsp[-2].token)->linha, (yyvsp[-2].token)->coluna);
                                                                            addChild((yyval.node), (yyvsp[-1].node));
                                                                            libertaToken((yyvsp[-2].token));}
#line 1870 "y.tab.c"
    break;

  case 36:
#line 214 "jucompiler.y"
                                                                            {(yyval.node) = NULL;}
#line 1876 "y.tab.c"
    break;

  case 37:
#line 216 "jucompiler.y"
                                                                            {(yyval.node) = (yyvsp[-1].node);}
#line 1882 "y.tab.c"
    break;

  case 38:
#line 218 "jucompiler.y"
                                                                            {(yyval.node) = (yyvsp[-1].node);}
#line 1888 "y.tab.c"
    break;

  case 39:
#line 220 "jucompiler.y"
                                                                            {(yyval.node) = (yyvsp[-1].node);}
#line 1894 "y.tab.c"
    break;

  case 40:
#line 222 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Print", NULL, (yyvsp[-4].token)->linha, (yyvsp[-4].token)->coluna);
                                                                            addChild((yyval.node), (yyvsp[-2].node));
                                                                            libertaToken((yyvsp[-4].token));}
#line 1902 "y.tab.c"
    break;

  case 41:
#line 226 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Print", NULL, (yyvsp[-4].token)->linha, (yyvsp[-4].token)->coluna);
                                                                            node1 = criaNode("StrLit", (yyvsp[-2].token)->valor, (yyvsp[-2].token)->linha, (yyvsp[-2].token)->coluna);
                                                                            addChild((yyval.node), node1);
                                                                            libertaToken((yyvsp[-4].token));
                                                                            libertaToken((yyvsp[-2].token));}
#line 1912 "y.tab.c"
    break;

  case 42:
#line 232 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Error", NULL, 0, 0);}
#line 1918 "y.tab.c"
    break;

  case 43:
#line 235 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("NULL", NULL, 0, 0);}
#line 1924 "y.tab.c"
    break;

  case 44:
#line 237 "jucompiler.y"
                                                                            {addBrother((yyvsp[-1].node), (yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node);}
#line 1930 "y.tab.c"
    break;

  case 45:
#line 243 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Call", NULL, (yyvsp[-2].token)->linha, (yyvsp[-2].token)->coluna);
                                                                            node1 = criaNode("Id", (yyvsp[-2].token)->valor, (yyvsp[-2].token)->linha, (yyvsp[-2].token)->coluna);
                                                                            addChild((yyval.node), node1);
                                                                            libertaToken((yyvsp[-2].token));}
#line 1939 "y.tab.c"
    break;

  case 46:
#line 248 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Call", NULL, (yyvsp[-4].token)->linha, (yyvsp[-4].token)->coluna);
                                                                            node1 = criaNode("Id", (yyvsp[-4].token)->valor, (yyvsp[-4].token)->linha, (yyvsp[-4].token)->coluna);
                                                                            addChild((yyval.node), node1);
                                                                            addBrother(node1, (yyvsp[-2].node));
                                                                            addBrother(node1, (yyvsp[-1].node));
                                                                            libertaToken((yyvsp[-4].token));}
#line 1950 "y.tab.c"
    break;

  case 47:
#line 255 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Error", NULL, 0, 0); 
                                                                            libertaToken((yyvsp[-3].token));}
#line 1957 "y.tab.c"
    break;

  case 48:
#line 259 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("NULL", NULL, 0, 0);}
#line 1963 "y.tab.c"
    break;

  case 49:
#line 260 "jucompiler.y"
                                                                            {(yyval.node) = (yyvsp[-2].node); addBrother((yyvsp[-2].node), (yyvsp[0].node));}
#line 1969 "y.tab.c"
    break;

  case 50:
#line 264 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Assign", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            node1 = criaNode("Id", (yyvsp[-2].token)->valor, (yyvsp[-2].token)->linha, (yyvsp[-2].token)->coluna);
                                                                            addChild((yyval.node), node1);
                                                                            addBrother(node1, (yyvsp[0].node));
                                                                            libertaToken((yyvsp[-1].token));
                                                                            libertaToken((yyvsp[-2].token));}
#line 1980 "y.tab.c"
    break;

  case 51:
#line 271 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("ParseArgs", NULL, (yyvsp[-6].token)->linha, (yyvsp[-6].token)->coluna);
                                                                            node1 = criaNode("Id", (yyvsp[-4].token)->valor, (yyvsp[-4].token)->linha, (yyvsp[-4].token)->coluna);
                                                                            addChild((yyval.node), node1);
                                                                            addBrother(node1, (yyvsp[-2].node));
                                                                            libertaToken((yyvsp[-6].token));
                                                                            libertaToken((yyvsp[-4].token));}
#line 1991 "y.tab.c"
    break;

  case 52:
#line 278 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Error", NULL, 0, 0);}
#line 1997 "y.tab.c"
    break;

  case 53:
#line 281 "jucompiler.y"
                                                                            {(yyval.node) = (yyvsp[0].node);}
#line 2003 "y.tab.c"
    break;

  case 54:
#line 283 "jucompiler.y"
                                                                            {(yyval.node) = (yyvsp[0].node);}
#line 2009 "y.tab.c"
    break;

  case 55:
#line 286 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Add", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node),(yyvsp[-2].node)); addBrother((yyvsp[-2].node),(yyvsp[0].node)); libertaToken((yyvsp[-1].token));}
#line 2016 "y.tab.c"
    break;

  case 56:
#line 289 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Sub", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node),(yyvsp[-2].node)); addBrother((yyvsp[-2].node),(yyvsp[0].node)); libertaToken((yyvsp[-1].token));}
#line 2023 "y.tab.c"
    break;

  case 57:
#line 292 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Mul", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node),(yyvsp[-2].node)); addBrother((yyvsp[-2].node),(yyvsp[0].node)); libertaToken((yyvsp[-1].token));}
#line 2030 "y.tab.c"
    break;

  case 58:
#line 295 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Div", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node),(yyvsp[-2].node)); addBrother((yyvsp[-2].node),(yyvsp[0].node)); libertaToken((yyvsp[-1].token));}
#line 2037 "y.tab.c"
    break;

  case 59:
#line 298 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Mod", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node),(yyvsp[-2].node)); addBrother((yyvsp[-2].node),(yyvsp[0].node)); libertaToken((yyvsp[-1].token));}
#line 2044 "y.tab.c"
    break;

  case 60:
#line 301 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("And", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node),(yyvsp[-2].node)); addBrother((yyvsp[-2].node),(yyvsp[0].node)); libertaToken((yyvsp[-1].token));}
#line 2051 "y.tab.c"
    break;

  case 61:
#line 304 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Or", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node),(yyvsp[-2].node)); addBrother((yyvsp[-2].node),(yyvsp[0].node)); libertaToken((yyvsp[-1].token));}
#line 2058 "y.tab.c"
    break;

  case 62:
#line 307 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Xor", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node),(yyvsp[-2].node)); addBrother((yyvsp[-2].node),(yyvsp[0].node)); libertaToken((yyvsp[-1].token));}
#line 2065 "y.tab.c"
    break;

  case 63:
#line 310 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Lshift", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node),(yyvsp[-2].node)); addBrother((yyvsp[-2].node),(yyvsp[0].node)); libertaToken((yyvsp[-1].token));}
#line 2072 "y.tab.c"
    break;

  case 64:
#line 313 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Rshift", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node),(yyvsp[-2].node)); addBrother((yyvsp[-2].node),(yyvsp[0].node)); libertaToken((yyvsp[-1].token));}
#line 2079 "y.tab.c"
    break;

  case 65:
#line 316 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Eq", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node),(yyvsp[-2].node)); addBrother((yyvsp[-2].node),(yyvsp[0].node)); libertaToken((yyvsp[-1].token));}
#line 2086 "y.tab.c"
    break;

  case 66:
#line 319 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Ge", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node),(yyvsp[-2].node)); addBrother((yyvsp[-2].node),(yyvsp[0].node)); libertaToken((yyvsp[-1].token));}
#line 2093 "y.tab.c"
    break;

  case 67:
#line 322 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Gt", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node),(yyvsp[-2].node)); addBrother((yyvsp[-2].node),(yyvsp[0].node)); libertaToken((yyvsp[-1].token));}
#line 2100 "y.tab.c"
    break;

  case 68:
#line 325 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Le", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node),(yyvsp[-2].node)); addBrother((yyvsp[-2].node),(yyvsp[0].node)); libertaToken((yyvsp[-1].token));}
#line 2107 "y.tab.c"
    break;

  case 69:
#line 328 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Lt", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node),(yyvsp[-2].node)); addBrother((yyvsp[-2].node),(yyvsp[0].node)); libertaToken((yyvsp[-1].token));}
#line 2114 "y.tab.c"
    break;

  case 70:
#line 331 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Ne", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node),(yyvsp[-2].node)); addBrother((yyvsp[-2].node),(yyvsp[0].node)); libertaToken((yyvsp[-1].token));}
#line 2121 "y.tab.c"
    break;

  case 71:
#line 334 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Minus", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node),(yyvsp[0].node)); libertaToken((yyvsp[-1].token));}
#line 2128 "y.tab.c"
    break;

  case 72:
#line 337 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Not", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node),(yyvsp[0].node)); libertaToken((yyvsp[-1].token));}
#line 2135 "y.tab.c"
    break;

  case 73:
#line 340 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Plus", NULL, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node),(yyvsp[0].node)); libertaToken((yyvsp[-1].token));}
#line 2142 "y.tab.c"
    break;

  case 74:
#line 343 "jucompiler.y"
                                                                            {(yyval.node) = (yyvsp[-1].node);}
#line 2148 "y.tab.c"
    break;

  case 75:
#line 344 "jucompiler.y"
                                                                            {(yyval.node) = (yyvsp[0].node);}
#line 2154 "y.tab.c"
    break;

  case 76:
#line 345 "jucompiler.y"
                                                                            {(yyval.node) = (yyvsp[0].node);}
#line 2160 "y.tab.c"
    break;

  case 77:
#line 346 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Id", (yyvsp[0].token)->valor, (yyvsp[0].token)->linha, (yyvsp[0].token)->coluna);
                                                                            libertaToken((yyvsp[0].token));}
#line 2167 "y.tab.c"
    break;

  case 78:
#line 349 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Length", NULL, (yyvsp[0].token)->linha, (yyvsp[0].token)->coluna);
                                                                            node1 = criaNode("Id", (yyvsp[-1].token)->valor, (yyvsp[-1].token)->linha, (yyvsp[-1].token)->coluna);
                                                                            addChild((yyval.node), node1);
                                                                            libertaToken((yyvsp[0].token)); libertaToken((yyvsp[-1].token));}
#line 2176 "y.tab.c"
    break;

  case 79:
#line 354 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("DecLit", (yyvsp[0].token)->valor, (yyvsp[0].token)->linha, (yyvsp[0].token)->coluna);
                                                                            libertaToken((yyvsp[0].token));}
#line 2183 "y.tab.c"
    break;

  case 80:
#line 357 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("RealLit", (yyvsp[0].token)->valor, (yyvsp[0].token)->linha, (yyvsp[0].token)->coluna);
                                                                            libertaToken((yyvsp[0].token));}
#line 2190 "y.tab.c"
    break;

  case 81:
#line 360 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("BoolLit", (yyvsp[0].token)->valor, (yyvsp[0].token)->linha, (yyvsp[0].token)->coluna); 
                                                                            libertaToken((yyvsp[0].token));}
#line 2197 "y.tab.c"
    break;

  case 82:
#line 363 "jucompiler.y"
                                                                            {(yyval.node) = criaNode("Error", NULL, 0, 0);}
#line 2203 "y.tab.c"
    break;


#line 2207 "y.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
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
  return yyresult;
}
#line 365 "jucompiler.y"
