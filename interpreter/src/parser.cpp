/* A Bison parser, made by GNU Bison 3.7.3.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1





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
  YYSYMBOL_routine = 3,                    /* routine  */
  YYSYMBOL_test = 4,                       /* test  */
  YYSYMBOL_loop = 5,                       /* loop  */
  YYSYMBOL_delay = 6,                      /* delay  */
  YYSYMBOL_read_pin = 7,                   /* read_pin  */
  YYSYMBOL_set_pin = 8,                    /* set_pin  */
  YYSYMBOL_perrint = 9,                    /* perrint  */
  YYSYMBOL_perrintln = 10,                 /* perrintln  */
  YYSYMBOL_expect = 11,                    /* expect  */
  YYSYMBOL_exit_tok = 12,                  /* exit_tok  */
  YYSYMBOL_prompt = 13,                    /* prompt  */
  YYSYMBOL_read_msg = 14,                  /* read_msg  */
  YYSYMBOL_send_msg = 15,                  /* send_msg  */
  YYSYMBOL_call = 16,                      /* call  */
  YYSYMBOL_forever = 17,                   /* forever  */
  YYSYMBOL_dout = 18,                      /* dout  */
  YYSYMBOL_din = 19,                       /* din  */
  YYSYMBOL_aout = 20,                      /* aout  */
  YYSYMBOL_ain = 21,                       /* ain  */
  YYSYMBOL_22_ = 22,                       /* ';'  */
  YYSYMBOL_23_ = 23,                       /* '('  */
  YYSYMBOL_24_ = 24,                       /* ')'  */
  YYSYMBOL_25_ = 25,                       /* '{'  */
  YYSYMBOL_26_ = 26,                       /* '}'  */
  YYSYMBOL_27_ = 27,                       /* '|'  */
  YYSYMBOL_serialRx = 28,                  /* serialRx  */
  YYSYMBOL_serialTx = 29,                  /* serialTx  */
  YYSYMBOL_assert = 30,                    /* assert  */
  YYSYMBOL_If = 31,                        /* If  */
  YYSYMBOL_Else = 32,                      /* Else  */
  YYSYMBOL_length = 33,                    /* length  */
  YYSYMBOL_stringLiteral = 34,             /* stringLiteral  */
  YYSYMBOL_identifier = 35,                /* identifier  */
  YYSYMBOL_can_msg = 36,                   /* can_msg  */
  YYSYMBOL_add = 37,                       /* add  */
  YYSYMBOL_mult = 38,                      /* mult  */
  YYSYMBOL_comparison = 39,                /* comparison  */
  YYSYMBOL_andToken = 40,                  /* andToken  */
  YYSYMBOL_orToken = 41,                   /* orToken  */
  YYSYMBOL_NE = 42,                        /* NE  */
  YYSYMBOL_EQ = 43,                        /* EQ  */
  YYSYMBOL_integerLiteral = 44,            /* integerLiteral  */
  YYSYMBOL_hexLiteral = 45,                /* hexLiteral  */
  YYSYMBOL_dstate = 46,                    /* dstate  */
  YYSYMBOL_plusplus = 47,                  /* plusplus  */
  YYSYMBOL_minusminus = 48,                /* minusminus  */
  YYSYMBOL_49_ = 49,                       /* '['  */
  YYSYMBOL_50_ = 50,                       /* ']'  */
  YYSYMBOL_51_ = 51,                       /* '='  */
  YYSYMBOL_52_ = 52,                       /* '.'  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_goal = 54,                      /* goal  */
  YYSYMBOL_testScript = 55,                /* testScript  */
  YYSYMBOL_VarList = 56,                   /* VarList  */
  YYSYMBOL_RoutineList = 57,               /* RoutineList  */
  YYSYMBOL_Routine = 58,                   /* Routine  */
  YYSYMBOL_TestList = 59,                  /* TestList  */
  YYSYMBOL_Test = 60,                      /* Test  */
  YYSYMBOL_StatementList = 61,             /* StatementList  */
  YYSYMBOL_ExpectCall = 62,                /* ExpectCall  */
  YYSYMBOL_PromptCall = 63,                /* PromptCall  */
  YYSYMBOL_PrintCall = 64,                 /* PrintCall  */
  YYSYMBOL_Index = 65,                     /* Index  */
  YYSYMBOL_CanManip = 66,                  /* CanManip  */
  YYSYMBOL_Exp = 67,                       /* Exp  */
  YYSYMBOL_VariableAssign = 68,            /* VariableAssign  */
  YYSYMBOL_SendMsgCall = 69,               /* SendMsgCall  */
  YYSYMBOL_ReadMsgCall = 70,               /* ReadMsgCall  */
  YYSYMBOL_ReadPinCall = 71,               /* ReadPinCall  */
  YYSYMBOL_SetAnalogTail = 72,             /* SetAnalogTail  */
  YYSYMBOL_SetPinCall = 73,                /* SetPinCall  */
  YYSYMBOL_DelayCall = 74,                 /* DelayCall  */
  YYSYMBOL_LoopCall = 75,                  /* LoopCall  */
  YYSYMBOL_Statement = 76                  /* Statement  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;


/* Second part of user prologue.  */
#line 43 "src/parser.y"

  #include <string>
  #include <iostream>
  #include <cstdio>

  #include "symbol-table.h"
  #include "object.h"
  #include "ast.h"

  extern FILE *yyin;
  extern int yylineno;  

  int yylex(void);
  void yyerror(const char * err);

  Node * root;
  std::string infilename;
  int errors = 0;
  int perform_math_op(Node * lhs, Node * rhs, std::string * op);
  std::string stringifyNode(Node * node);



#line 203 "src/parser.cpp"


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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYLAST   418

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  167

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


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
      23,    24,     2,     2,     2,     2,    52,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    22,
       2,    51,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    49,     2,    50,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    25,    27,    26,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    69,    69,    73,   110,   113,   120,   124,   133,   143,
     147,   151,   161,   164,   171,   175,   182,   191,   195,   202,
     212,   217,   225,   228,   268,   296,   303,   310,   316,   322,
     328,   332,   336,   340,   344,   349,   371,   377,   382,   388,
     399,   408,   421,   427,   437,   443,   449,   455,   464,   474,
     485,   495,   508,   511,   518,   529,   536,   541,   548,   553,
     558,   569,   572,   576,   579,   582,   585,   588,   591,   594,
     597,   600,   603,   607,   610,   613,   617,   633
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "routine", "test",
  "loop", "delay", "read_pin", "set_pin", "perrint", "perrintln", "expect",
  "exit_tok", "prompt", "read_msg", "send_msg", "call", "forever", "dout",
  "din", "aout", "ain", "';'", "'('", "')'", "'{'", "'}'", "'|'",
  "serialRx", "serialTx", "assert", "If", "Else", "length",
  "stringLiteral", "identifier", "can_msg", "add", "mult", "comparison",
  "andToken", "orToken", "NE", "EQ", "integerLiteral", "hexLiteral",
  "dstate", "plusplus", "minusminus", "'['", "']'", "'='", "'.'",
  "$accept", "goal", "testScript", "VarList", "RoutineList", "Routine",
  "TestList", "Test", "StatementList", "ExpectCall", "PromptCall",
  "PrintCall", "Index", "CanManip", "Exp", "VariableAssign", "SendMsgCall",
  "ReadMsgCall", "ReadPinCall", "SetAnalogTail", "SetPinCall", "DelayCall",
  "LoopCall", "Statement", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,    59,    40,    41,   123,   125,   124,   277,   278,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   293,   294,   295,   296,   297,    91,
      93,    61,    46
};
#endif

#define YYPACT_NINF (-57)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -57,    40,   -57,     6,   -57,    -7,    50,   -57,    42,    42,
      23,    10,    32,   -57,    53,    42,   -57,   -43,   -57,    42,
     -57,   -57,   -57,   320,   298,    12,    42,    75,    41,   -57,
     341,    34,   -57,    67,    42,    42,    42,    42,    42,    42,
      42,   -57,   -57,    42,   305,   -57,    78,   -57,   -57,    67,
     -57,    33,    43,    43,    43,    43,   312,   -57,    83,   -57,
     -57,    88,     2,    42,    29,    65,    42,    42,    42,   -18,
      42,   -30,   -25,    81,   -57,    94,    42,    42,    98,     0,
     100,   101,   102,   349,   -57,   104,   119,   120,   121,   122,
     -57,   -57,   124,   -57,   123,   368,   375,   -27,   -23,   -22,
     -21,   375,   375,   375,   -57,   127,   375,   -57,   -57,    42,
      42,   129,   -57,   334,   375,    42,   112,    10,   -57,   -57,
     -57,   134,   135,   -57,   -57,   -57,   -57,   -57,   -57,   -57,
     -57,   -57,   -57,   -57,   -57,   116,   117,   -11,    -1,   -57,
     -57,   375,   375,   -57,   -57,   361,    12,   -57,   -57,   165,
     206,   -57,   -57,   -57,   -57,   -57,   -57,   139,   -57,   -57,
     -57,   247,   114,   140,   -57,   288,   -57
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     7,     1,     0,    10,     5,     0,     0,
       0,     0,     0,     6,     3,     0,    31,    30,    34,     0,
      32,    33,    22,     0,     0,     0,     0,     0,     0,     9,
       0,     0,    20,    35,     0,     0,     0,     0,     0,     0,
       0,    19,    37,     0,     0,    12,     0,    36,    21,    23,
      24,    27,    28,    29,    25,    26,     0,    38,     0,    12,
      39,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     8,     0,     0,     0,     0,    30,
       0,     0,     0,     0,    61,     0,     0,     0,     0,     0,
      63,    13,     0,    58,     0,     0,    55,     0,     0,     0,
       0,    17,    18,    14,    74,     0,    16,    43,    42,     0,
       0,     0,    73,     0,    15,     0,     0,    20,    66,    71,
      67,     0,     0,    68,    69,    65,    64,    70,    11,    12,
      12,    47,    46,    45,    44,     0,     0,     0,     0,    52,
      75,    41,    40,    62,    72,     0,    21,    76,    77,     0,
       0,    54,    53,    49,    50,    48,    51,     0,    57,    56,
      12,     0,    59,     0,    12,     0,    60
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -56,   -57,
     -57,   -57,   -15,   -57,    -8,   164,   -57,   -57,   -57,   -57,
     -57,   -57,   -57,   -57
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     3,     6,    13,    14,    29,    58,    80,
      81,    82,    11,    22,    83,    84,    85,    86,    87,   139,
      88,    89,    90,    91
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      23,    24,    32,    92,   104,   107,     8,    30,   131,    31,
     109,    33,   133,   135,   137,   108,   105,   132,    44,    94,
     110,   134,   136,   138,   153,    15,    49,    50,    51,    52,
      53,    54,    55,   154,   155,    56,    16,    17,    18,    19,
       4,     5,     8,   156,     9,    10,    20,    21,    97,     8,
      98,     9,   116,    12,    95,    96,    25,    28,   101,   102,
     103,    26,   106,    43,   117,    15,    27,    48,   113,   114,
      34,    35,    -1,   149,   150,    46,    16,    17,    18,    19,
      34,    35,    36,    99,    61,   100,    20,    21,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      45,   141,   142,    59,   161,    35,    15,   145,   165,    74,
      93,    75,    76,    77,    78,   111,   112,    16,    79,    18,
      19,   115,   118,   119,   120,    61,   123,    20,    21,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,   124,   125,   126,   127,   146,   163,    15,   129,   140,
     128,   143,    75,    76,    77,    78,   147,   148,    16,    79,
      18,    19,   151,   152,   160,   164,    61,     7,    20,    21,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,     0,     0,     0,     0,     0,     0,    15,     0,
       0,   158,     0,    75,    76,    77,    78,     0,     0,    16,
      79,    18,    19,     0,     0,     0,     0,    61,     0,    20,
      21,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,     0,     0,     0,     0,     0,     0,    15,
       0,     0,   159,     0,    75,    76,    77,    78,     0,     0,
      16,    79,    18,    19,     0,     0,     0,     0,    61,     0,
      20,    21,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,     0,     0,     0,     0,     0,     0,
      15,     0,     0,   162,     0,    75,    76,    77,    78,     0,
       0,    16,    79,    18,    19,     0,     0,     0,     0,    61,
       0,    20,    21,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,     0,     0,     0,     0,     0,
       0,    15,     0,     0,   166,     0,    75,    76,    77,    78,
      42,     0,    16,    79,    18,    19,     0,    57,     0,     0,
       0,     0,    20,    21,    60,    34,    35,    36,    37,    38,
      39,    40,    34,    35,    36,    37,    38,    39,    40,    34,
      35,    36,    37,    38,    39,    40,   144,    34,    35,    36,
      37,    38,    39,    40,     0,    47,     0,     0,     0,     0,
      41,    34,    35,    36,    37,    38,    39,    40,    34,    35,
      36,    37,    38,    39,    40,   157,    34,    35,    36,    37,
      38,    39,    40,   130,     0,     0,   121,   122,    34,    35,
      36,    37,    38,    39,    40,    34,    35,    36,    37,    38,
      39,    40,    34,    35,    36,    37,    38,    39,    40
};

static const yytype_int16 yycheck[] =
{
       8,     9,    17,    59,    22,    35,    49,    15,    35,    52,
      35,    19,    35,    35,    35,    45,    34,    44,    26,    17,
      45,    44,    44,    44,    35,    23,    34,    35,    36,    37,
      38,    39,    40,    44,    35,    43,    34,    35,    36,    37,
       0,    35,    49,    44,    51,    52,    44,    45,    19,    49,
      21,    51,    52,     3,    62,    63,    33,     4,    66,    67,
      68,    51,    70,    51,    79,    23,    34,    33,    76,    77,
      37,    38,    39,   129,   130,    34,    34,    35,    36,    37,
      37,    38,    39,    18,     1,    20,    44,    45,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      25,   109,   110,    25,   160,    38,    23,   115,   164,    26,
      22,    28,    29,    30,    31,    34,    22,    34,    35,    36,
      37,    23,    22,    22,    22,     1,    22,    44,    45,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    22,    22,    22,    22,    33,    32,    23,    25,    22,
      26,    22,    28,    29,    30,    31,    22,    22,    34,    35,
      36,    37,    46,    46,    25,    25,     1,     3,    44,    45,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    23,    -1,
      -1,    26,    -1,    28,    29,    30,    31,    -1,    -1,    34,
      35,    36,    37,    -1,    -1,    -1,    -1,     1,    -1,    44,
      45,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,    23,
      -1,    -1,    26,    -1,    28,    29,    30,    31,    -1,    -1,
      34,    35,    36,    37,    -1,    -1,    -1,    -1,     1,    -1,
      44,    45,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    26,    -1,    28,    29,    30,    31,    -1,
      -1,    34,    35,    36,    37,    -1,    -1,    -1,    -1,     1,
      -1,    44,    45,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,
      -1,    23,    -1,    -1,    26,    -1,    28,    29,    30,    31,
      22,    -1,    34,    35,    36,    37,    -1,    22,    -1,    -1,
      -1,    -1,    44,    45,    22,    37,    38,    39,    40,    41,
      42,    43,    37,    38,    39,    40,    41,    42,    43,    37,
      38,    39,    40,    41,    42,    43,    22,    37,    38,    39,
      40,    41,    42,    43,    -1,    24,    -1,    -1,    -1,    -1,
      50,    37,    38,    39,    40,    41,    42,    43,    37,    38,
      39,    40,    41,    42,    43,    24,    37,    38,    39,    40,
      41,    42,    43,    25,    -1,    -1,    47,    48,    37,    38,
      39,    40,    41,    42,    43,    37,    38,    39,    40,    41,
      42,    43,    37,    38,    39,    40,    41,    42,    43
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    54,    55,    56,     0,    35,    57,    68,    49,    51,
      52,    65,     3,    58,    59,    23,    34,    35,    36,    37,
      44,    45,    66,    67,    67,    33,    51,    34,     4,    60,
      67,    52,    65,    67,    37,    38,    39,    40,    41,    42,
      43,    50,    22,    51,    67,    25,    34,    24,    33,    67,
      67,    67,    67,    67,    67,    67,    67,    22,    61,    25,
      22,     1,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    26,    28,    29,    30,    31,    35,
      62,    63,    64,    67,    68,    69,    70,    71,    73,    74,
      75,    76,    61,    22,    17,    67,    67,    19,    21,    18,
      20,    67,    67,    67,    22,    34,    67,    35,    45,    35,
      45,    34,    22,    67,    67,    23,    52,    65,    22,    22,
      22,    47,    48,    22,    22,    22,    22,    22,    26,    25,
      25,    35,    44,    35,    44,    35,    44,    35,    44,    72,
      22,    67,    67,    22,    22,    67,    33,    22,    22,    61,
      61,    46,    46,    35,    44,    35,    44,    24,    26,    26,
      25,    61,    26,    32,    25,    61,    26
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    56,    56,    57,    57,    58,    59,
      59,    60,    61,    61,    62,    62,    63,    64,    64,    65,
      66,    66,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    68,    68,    68,
      69,    69,    70,    70,    71,    71,    71,    71,    72,    72,
      72,    72,    73,    73,    73,    74,    75,    75,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     0,     2,     2,     0,     5,     2,
       0,     5,     0,     2,     2,     2,     2,     2,     2,     3,
       2,     3,     1,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     2,     3,     4,     5,     6,
       3,     3,     2,     2,     3,     3,     3,     3,     2,     2,
       2,     2,     3,     4,     4,     2,     5,     5,     2,     7,
      11,     1,     3,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     2,     2,     3,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
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
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3: /* testScript: VarList RoutineList TestList  */
#line 73 "src/parser.y"
                                {
      (yyval.node) = new Node("Script", 0);
      if (!(yyvsp[-2].node)->children.empty())
      {
        (yyval.node)->addChild((yyvsp[-2].node));
      }
      else
      {
        delete (yyvsp[-2].node);
      }

      if (!(yyvsp[-1].node)->children.empty())
      {
        (yyval.node)->addChild((yyvsp[-1].node));
      }
      else
      {
        delete (yyvsp[-1].node);
      }

      if (!(yyvsp[0].node)->children.empty())
      {
        (yyval.node)->addChild((yyvsp[0].node));
      }
      else
      {
        delete (yyvsp[0].node);
      }

      root = (yyval.node);
      if (errors == 0)
        (yyval.node)->print();
  }
#line 1715 "src/parser.cpp"
    break;

  case 4: /* VarList: %empty  */
#line 110 "src/parser.y"
         {
      (yyval.node) = new Node(vardecl_list_node, yylineno);
  }
#line 1723 "src/parser.cpp"
    break;

  case 5: /* VarList: VarList VariableAssign  */
#line 113 "src/parser.y"
                           {
      (yyval.node) = (yyvsp[-1].node);
      (yyval.node)->addChild((yyvsp[0].node));
  }
#line 1732 "src/parser.cpp"
    break;

  case 6: /* RoutineList: RoutineList Routine  */
#line 120 "src/parser.y"
                      {
      (yyval.node) = (yyvsp[-1].node);
      (yyval.node)->addChild((yyvsp[0].node));
  }
#line 1741 "src/parser.cpp"
    break;

  case 7: /* RoutineList: %empty  */
#line 124 "src/parser.y"
           {
      (yyval.node) = new Node(routine_list_node, yylineno);
    }
#line 1749 "src/parser.cpp"
    break;

  case 8: /* Routine: routine stringLiteral '{' StatementList '}'  */
#line 133 "src/parser.y"
                                              {
    int lineno = (yylsp[-4]).first_line - (yyvsp[-1].node)->line_no;
    (yyval.node) = new Node(routine_node, lineno);
    (yyval.node)->setString((yyvsp[-3].str));
    (yyval.node)->addChild((yyvsp[-1].node));
  }
#line 1760 "src/parser.cpp"
    break;

  case 9: /* TestList: TestList Test  */
#line 143 "src/parser.y"
                { 
    (yyval.node) = (yyvsp[-1].node);
    (yyval.node)->addChild((yyvsp[0].node));
  }
#line 1769 "src/parser.cpp"
    break;

  case 10: /* TestList: %empty  */
#line 147 "src/parser.y"
           { (yyval.node) = new Node(test_list_node, yylineno); }
#line 1775 "src/parser.cpp"
    break;

  case 11: /* Test: test stringLiteral '{' StatementList '}'  */
#line 151 "src/parser.y"
                                           {
    int lineno = (yylsp[-4]).first_line - (yyvsp[-1].node)->line_no;
    (yyval.node) = new Node(test_node, lineno);
    (yyval.node)->setString((yyvsp[-3].str));
    (yyval.node)->addChild((yyvsp[-1].node));
  }
#line 1786 "src/parser.cpp"
    break;

  case 12: /* StatementList: %empty  */
#line 161 "src/parser.y"
           {
      (yyval.node) = new Node(statement_list, yylineno);
  }
#line 1794 "src/parser.cpp"
    break;

  case 13: /* StatementList: StatementList Statement  */
#line 164 "src/parser.y"
                            {
      (yyval.node) = (yyvsp[-1].node);
      (yyval.node)->addChild((yyvsp[0].node));
  }
#line 1803 "src/parser.cpp"
    break;

  case 14: /* ExpectCall: expect Exp  */
#line 171 "src/parser.y"
             {
      (yyval.node) = new Node(expect_node, (yylsp[-1]).first_line);
      (yyval.node)->addChild((yyvsp[0].node));
  }
#line 1812 "src/parser.cpp"
    break;

  case 15: /* ExpectCall: assert Exp  */
#line 175 "src/parser.y"
               {
      (yyval.node) = new Node(assert_node, (yylsp[-1]).first_line);
      (yyval.node)->addChild((yyvsp[0].node));
  }
#line 1821 "src/parser.cpp"
    break;

  case 16: /* PromptCall: prompt Exp  */
#line 182 "src/parser.y"
             {
    (yyval.node) = new Node(prompt_node, (yylsp[-1]).first_line);
    (yyval.node)->addChild((yyvsp[0].node));
  }
#line 1830 "src/parser.cpp"
    break;

  case 17: /* PrintCall: perrint Exp  */
#line 191 "src/parser.y"
              {
      (yyval.node) = new Node(print, (yylsp[-1]).first_line);
      (yyval.node)->addChild((yyvsp[0].node));
  }
#line 1839 "src/parser.cpp"
    break;

  case 18: /* PrintCall: perrintln Exp  */
#line 195 "src/parser.y"
                  {
      (yyval.node) = new Node(println, (yylsp[-1]).first_line);
      (yyval.node)->addChild((yyvsp[0].node));
  }
#line 1848 "src/parser.cpp"
    break;

  case 19: /* Index: '[' Exp ']'  */
#line 202 "src/parser.y"
              {
    (yyval.node) = new Node(index_node, (yylsp[-1]).first_line);
    (yyval.node)->addChild((yyvsp[-1].node));
    (yyval.node)->setString("[]");
  }
#line 1858 "src/parser.cpp"
    break;

  case 20: /* CanManip: identifier Index  */
#line 212 "src/parser.y"
                   {
    (yyval.node) = new Node(identifier_node, (yylsp[-1]).first_line);
    (yyval.node)->setString((yyvsp[-1].str));
    (yyval.node)->addChild((yyvsp[0].node));
  }
#line 1868 "src/parser.cpp"
    break;

  case 21: /* CanManip: identifier '.' length  */
#line 217 "src/parser.y"
                         {
    (yyval.node) = new Node(identifier_node, (yylsp[-2]).first_line);
    (yyval.node)->setString((yyvsp[-2].str));
    (yyval.node)->addChild(new Node(length_node, (yylsp[-2]).first_line));
  }
#line 1878 "src/parser.cpp"
    break;

  case 22: /* Exp: CanManip  */
#line 225 "src/parser.y"
            {
      (yyval.node) = (yyvsp[0].node);
  }
#line 1886 "src/parser.cpp"
    break;

  case 23: /* Exp: Exp add Exp  */
#line 228 "src/parser.y"
                 {
      if ((yyvsp[-2].node)->isLiteral() && (yyvsp[0].node)->isLiteral())
      {
        node_type_t lhst = (yyvsp[-2].node)->node_type; 
        node_type_t rhst = (yyvsp[0].node)->node_type; 
        if ((lhst == integerLiteral_node || lhst == hexLiteral_node) 
            && (rhst == integerLiteral_node || rhst == hexLiteral_node))
        {
          perform_math_op((yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].str));
        }
        else if ((yyvsp[-2].node)->node_type == stringLiteral_node 
                 || (yyvsp[0].node)->node_type == stringLiteral_node)
        {
          // TODO string concatenation
          Node * str = new Node(stringLiteral_node, (yyvsp[-2].node)->line_no);
          std::cout << "node 1: " << stringifyNode((yyvsp[-2].node)) << " | node 2: " << stringifyNode((yyvsp[0].node)) << "\n";
          std::string val = stringifyNode((yyvsp[-2].node)) + stringifyNode((yyvsp[0].node));
          str->setString(val);
          delete (yyvsp[-2].node);
          delete (yyvsp[-1].str);
          delete (yyvsp[0].node);
          (yyval.node) = str;
        }
        else 
        {
          (yyval.node) = new Node(binary_math_node, (yylsp[-2]).first_line);
          (yyval.node)->setString((yyvsp[-1].str));
          (yyval.node)->addChild((yyvsp[-2].node));
          (yyval.node)->addChild((yyvsp[0].node));
        }
      }
  
      else 
      {
        (yyval.node) = new Node(binary_math_node, (yylsp[-2]).first_line);
        (yyval.node)->setString((yyvsp[-1].str));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
      }
  }
#line 1931 "src/parser.cpp"
    break;

  case 24: /* Exp: Exp mult Exp  */
#line 268 "src/parser.y"
                 {
      if ((yyvsp[-2].node)->isLiteral() && (yyvsp[0].node)->isLiteral())
      {
        node_type_t lhst = (yyvsp[-2].node)->node_type; 
        node_type_t rhst = (yyvsp[0].node)->node_type; 
        if ((lhst == integerLiteral_node || lhst == hexLiteral_node) 
            && (rhst == integerLiteral_node || rhst == hexLiteral_node))
        {
          perform_math_op((yyvsp[-2].node), (yyvsp[0].node), (yyvsp[-1].str));
        }
         else 
        {
          (yyval.node) = new Node(binary_math_node, (yylsp[-2]).first_line);
          (yyval.node)->setString((yyvsp[-1].str));
          (yyval.node)->addChild((yyvsp[-2].node));
          delete (yyvsp[-1].str);
          (yyval.node)->addChild((yyvsp[0].node));
        }
      }
      else
      {
        (yyval.node) = new Node(binary_math_node, (yylsp[-2]).first_line);
        (yyval.node)->setString((yyvsp[-1].str));
        (yyval.node)->addChild((yyvsp[-2].node));
        (yyval.node)->addChild((yyvsp[0].node));
      }

  }
#line 1964 "src/parser.cpp"
    break;

  case 25: /* Exp: Exp NE Exp  */
#line 296 "src/parser.y"
               {

      (yyval.node) = new Node(comparison_node, (yylsp[-2]).first_line);
      (yyval.node)->setString((yyvsp[-1].str));
      (yyval.node)->addChild((yyvsp[-2].node));
      (yyval.node)->addChild((yyvsp[0].node));
  }
#line 1976 "src/parser.cpp"
    break;

  case 26: /* Exp: Exp EQ Exp  */
#line 303 "src/parser.y"
               {

      (yyval.node) = new Node(comparison_node, (yylsp[-2]).first_line);
      (yyval.node)->setString((yyvsp[-1].str));
      (yyval.node)->addChild((yyvsp[-2].node));
      (yyval.node)->addChild((yyvsp[0].node));
  }
#line 1988 "src/parser.cpp"
    break;

  case 27: /* Exp: Exp comparison Exp  */
#line 310 "src/parser.y"
                       {
      (yyval.node) = new Node(comparison_node, (yylsp[-2]).first_line);
      (yyval.node)->setString((yyvsp[-1].str));
      (yyval.node)->addChild((yyvsp[-2].node));
      (yyval.node)->addChild((yyvsp[0].node));
  }
#line 1999 "src/parser.cpp"
    break;

  case 28: /* Exp: Exp andToken Exp  */
#line 316 "src/parser.y"
                     {
      (yyval.node) = new Node(and_node, (yylsp[-2]).first_line);
      (yyval.node)->setString((yyvsp[-1].str));
      (yyval.node)->addChild((yyvsp[-2].node));
      (yyval.node)->addChild((yyvsp[0].node));
  }
#line 2010 "src/parser.cpp"
    break;

  case 29: /* Exp: Exp orToken Exp  */
#line 322 "src/parser.y"
                    {
      (yyval.node) = new Node(or_node, (yylsp[-2]).first_line);
      (yyval.node)->setString((yyvsp[-1].str));
      (yyval.node)->addChild((yyvsp[-2].node));
      (yyval.node)->addChild((yyvsp[0].node));
  }
#line 2021 "src/parser.cpp"
    break;

  case 30: /* Exp: identifier  */
#line 328 "src/parser.y"
               {
    (yyval.node) = new Node(identifier_node, (yylsp[0]).first_line);
    (yyval.node)->setString((yyvsp[0].str));
  }
#line 2030 "src/parser.cpp"
    break;

  case 31: /* Exp: stringLiteral  */
#line 332 "src/parser.y"
                  {
    (yyval.node) = new Node(stringLiteral_node, (yylsp[0]).first_line);
    (yyval.node)->setString((yyvsp[0].str));
  }
#line 2039 "src/parser.cpp"
    break;

  case 32: /* Exp: integerLiteral  */
#line 336 "src/parser.y"
                   {
    (yyval.node) = new Node(integerLiteral_node, (yylsp[0]).first_line);
    (yyval.node)->setInt((yyvsp[0].i));
  }
#line 2048 "src/parser.cpp"
    break;

  case 33: /* Exp: hexLiteral  */
#line 340 "src/parser.y"
               {
    (yyval.node) = new Node(hexLiteral_node, (yylsp[0]).first_line);
    (yyval.node)->setInt((yyvsp[0].i));
  }
#line 2057 "src/parser.cpp"
    break;

  case 34: /* Exp: can_msg  */
#line 344 "src/parser.y"
            {
    (yyval.node) = new Node(can_msg_node, (yylsp[0]).first_line);
    (yyval.node)->setCanMsg((yyvsp[0].str));
  }
#line 2066 "src/parser.cpp"
    break;

  case 35: /* Exp: add Exp  */
#line 349 "src/parser.y"
            {
      node_type_t type = (yyvsp[0].node)->node_type;

      if ((yyvsp[0].node)->isLiteral() && (type == integerLiteral_node 
                                || type == hexLiteral_node))
      {
        if (*(yyvsp[-1].str) == "+")
        {
          (yyvsp[0].node)->setInt(+(yyvsp[0].node)->data.intval);
        }
        else if (*(yyvsp[-1].str) == "-")
        {
          (yyvsp[0].node)->setInt(-(yyvsp[0].node)->data.intval);
        }
      }
      else
      {
        (yyval.node) = new Node(binary_math_node, (yylsp[-1]).first_line);
        (yyval.node)->setString((yyvsp[-1].str));
        (yyval.node)->addChild((yyvsp[0].node));
      }
  }
#line 2093 "src/parser.cpp"
    break;

  case 36: /* Exp: '(' Exp ')'  */
#line 371 "src/parser.y"
                {
    (yyval.node) = (yyvsp[-1].node);
  }
#line 2101 "src/parser.cpp"
    break;

  case 37: /* VariableAssign: identifier '=' Exp ';'  */
#line 377 "src/parser.y"
                        {
      (yyval.node) = new Node(vardecl_node, (yylsp[-3]).first_line);
      (yyval.node)->setString((yyvsp[-3].str));
      (yyval.node)->addChild((yyvsp[-1].node));
  }
#line 2111 "src/parser.cpp"
    break;

  case 38: /* VariableAssign: identifier Index '=' Exp ';'  */
#line 382 "src/parser.y"
                                 {
      (yyval.node) = new Node(vardecl_node, (yylsp[-4]).first_line);
      (yyval.node)->setString((yyvsp[-4].str));
      (yyval.node)->addChild((yyvsp[-1].node));
      (yyval.node)->addChild((yyvsp[-3].node));
  }
#line 2122 "src/parser.cpp"
    break;

  case 39: /* VariableAssign: identifier '.' length '=' Exp ';'  */
#line 388 "src/parser.y"
                                      {
      (yyval.node) = new Node(vardecl_node, (yylsp[-5]).first_line);
      Node * l = new Node(length_node, (yylsp[-5]).first_line);
      l->setString("length");
      (yyval.node)->setString((yyvsp[-5].str));
      (yyval.node)->addChild((yyvsp[-1].node));
      (yyval.node)->addChild(l);
  }
#line 2135 "src/parser.cpp"
    break;

  case 40: /* SendMsgCall: send_msg hexLiteral Exp  */
#line 399 "src/parser.y"
                          {
      (yyval.node) = new Node(send_msg_node, (yylsp[-2]).first_line);
      Node * id = new Node(hexLiteral_node, (yylsp[-2]).first_line);

      id->setInt((yyvsp[-1].i));

      (yyval.node)->addChild(id);
      (yyval.node)->addChild((yyvsp[0].node));
  }
#line 2149 "src/parser.cpp"
    break;

  case 41: /* SendMsgCall: send_msg identifier Exp  */
#line 408 "src/parser.y"
                            {
      (yyval.node) = new Node(send_msg_node, (yylsp[-2]).first_line);
      Node * var = new Node (identifier_node, (yylsp[-2]).first_line);
      var->setString((yyvsp[-1].str));

      (yyval.node)->addChild(var);
      (yyval.node)->addChild((yyvsp[0].node));
  }
#line 2162 "src/parser.cpp"
    break;

  case 42: /* ReadMsgCall: read_msg hexLiteral  */
#line 421 "src/parser.y"
                       {
      (yyval.node) = new Node(read_msg_node, (yylsp[-1]).first_line);
      Node * id = new Node(hexLiteral_node, (yylsp[-1]).first_line);
      id->setInt((yyvsp[0].i));
      (yyval.node)->addChild(id);
  }
#line 2173 "src/parser.cpp"
    break;

  case 43: /* ReadMsgCall: read_msg identifier  */
#line 427 "src/parser.y"
                        {
      (yyval.node) = new Node(read_msg_node, (yylsp[-1]).first_line);
      Node * var = new Node(identifier_node, (yylsp[-1]).first_line);
      var->setString((yyvsp[0].str));
      (yyval.node)->addChild(var);
  }
#line 2184 "src/parser.cpp"
    break;

  case 44: /* ReadPinCall: read_pin ain integerLiteral  */
#line 437 "src/parser.y"
                              {
      (yyval.node) = new Node(analog_read, (yylsp[-2]).first_line);
      Node * pin = new Node(integerLiteral_node, (yylsp[-2]).first_line);
      pin->setInt((yyvsp[0].i));
      (yyval.node)->addChild(pin);
  }
#line 2195 "src/parser.cpp"
    break;

  case 45: /* ReadPinCall: read_pin ain identifier  */
#line 443 "src/parser.y"
                            {
      (yyval.node) = new Node(analog_read, (yylsp[-2]).first_line);
      Node * var = new Node(identifier_node, (yylsp[-2]).first_line);
      var->setString((yyvsp[0].str));
      (yyval.node)->addChild(var);
  }
#line 2206 "src/parser.cpp"
    break;

  case 46: /* ReadPinCall: read_pin din integerLiteral  */
#line 449 "src/parser.y"
                                {
      (yyval.node) = new Node(digital_read, (yylsp[-2]).first_line);
      Node * pin = new Node(integerLiteral_node, (yylsp[-2]).first_line);
      pin->setInt((yyvsp[0].i));
      (yyval.node)->addChild(pin);
  }
#line 2217 "src/parser.cpp"
    break;

  case 47: /* ReadPinCall: read_pin din identifier  */
#line 455 "src/parser.y"
                            {
      (yyval.node) = new Node(digital_read, (yylsp[-2]).first_line);
      Node * var = new Node(identifier_node, (yylsp[-2]).first_line);
      var->setString((yyvsp[0].str));

      (yyval.node)->addChild(var);
  }
#line 2229 "src/parser.cpp"
    break;

  case 48: /* SetAnalogTail: integerLiteral identifier  */
#line 464 "src/parser.y"
                            { 
      (yyval.node) = new Node(analog_write, (yylsp[-1]).first_line);
      Node * pin = new Node(integerLiteral_node, (yylsp[-1]).first_line);
      Node * var = new Node(identifier_node, (yylsp[-1]).first_line);
      var->setString((yyvsp[0].str));
      pin->setInt((yyvsp[-1].i));

      (yyval.node)->addChild(pin);
      (yyval.node)->addChild(var);
  }
#line 2244 "src/parser.cpp"
    break;

  case 49: /* SetAnalogTail: identifier identifier  */
#line 474 "src/parser.y"
                           {
      (yyval.node) = new Node(analog_write, (yylsp[-1]).first_line);
      Node * var = new Node(identifier_node, (yylsp[-1]).first_line);
      Node * var1 = new Node(identifier_node, (yylsp[-1]).first_line);
      
      var->setString((yyvsp[-1].str));
      var->setString((yyvsp[0].str));

      (yyval.node)->addChild(var);
      (yyval.node)->addChild(var1);
  }
#line 2260 "src/parser.cpp"
    break;

  case 50: /* SetAnalogTail: identifier integerLiteral  */
#line 485 "src/parser.y"
                              {
      (yyval.node) = new Node(analog_write, (yylsp[-1]).first_line);
      Node * value = new Node(integerLiteral_node, (yylsp[-1]).first_line);
      Node * var = new Node(identifier_node, (yylsp[-1]).first_line);
      var->setString((yyvsp[-1].str));
      value->setInt((yyvsp[0].i));

      (yyval.node)->addChild(var);
      (yyval.node)->addChild(value);
  }
#line 2275 "src/parser.cpp"
    break;

  case 51: /* SetAnalogTail: integerLiteral integerLiteral  */
#line 495 "src/parser.y"
                                  {
      (yyval.node) = new Node(analog_write, (yylsp[-1]).first_line);
      Node * pin = new Node(integerLiteral_node, (yylsp[-1]).first_line);
      Node * value = new Node(integerLiteral_node, (yylsp[-1]).first_line);
      pin->setInt((yyvsp[-1].i));
      value->setInt((yyvsp[0].i));

      (yyval.node)->addChild(pin);
      (yyval.node)->addChild(value);
  }
#line 2290 "src/parser.cpp"
    break;

  case 52: /* SetPinCall: set_pin aout SetAnalogTail  */
#line 508 "src/parser.y"
                             {
      (yyval.node) = (yyvsp[0].node);
 }
#line 2298 "src/parser.cpp"
    break;

  case 53: /* SetPinCall: set_pin dout integerLiteral dstate  */
#line 511 "src/parser.y"
                                       {
      (yyval.node) = new Node(digital_write, (yylsp[-3]).first_line);
      Node * pin = new Node(integerLiteral_node, (yylsp[-3]).first_line);
      pin->setInt((yyvsp[-1].i));
      (yyval.node)->setInt((yyvsp[0].i));
      (yyval.node)->addChild(pin);
  }
#line 2310 "src/parser.cpp"
    break;

  case 54: /* SetPinCall: set_pin dout identifier dstate  */
#line 518 "src/parser.y"
                                   {
      (yyval.node) = new Node(digital_write, (yylsp[-3]).first_line);
      Node * var = new Node(identifier_node, (yylsp[-3]).first_line);
      var->setString((yyvsp[-1].str));
      (yyval.node)->setInt((yyvsp[0].i));
      (yyval.node)->addChild(var);
  }
#line 2322 "src/parser.cpp"
    break;

  case 55: /* DelayCall: delay Exp  */
#line 529 "src/parser.y"
            {
      (yyval.node) = new Node(delay_node, (yylsp[-1]).first_line);
      (yyval.node)->addChild((yyvsp[0].node));
  }
#line 2331 "src/parser.cpp"
    break;

  case 56: /* LoopCall: loop Exp '{' StatementList '}'  */
#line 536 "src/parser.y"
                                 {
      (yyval.node) = new Node(loop_node, (yylsp[-4]).first_line);
      (yyval.node)->addChild((yyvsp[-3].node));
      (yyval.node)->addChild((yyvsp[-1].node));
  }
#line 2341 "src/parser.cpp"
    break;

  case 57: /* LoopCall: loop forever '{' StatementList '}'  */
#line 541 "src/parser.y"
                                       {
      (yyval.node) = new Node(loop_node, (yylsp[-4]).first_line);
      Node * times = new Node(forever_node, (yylsp[-4]).first_line);
      (yyval.node)->addChild(times);
      (yyval.node)->addChild((yyvsp[-1].node));
  }
#line 2352 "src/parser.cpp"
    break;

  case 58: /* Statement: error ';'  */
#line 548 "src/parser.y"
                     {
    errors++;
    yyerrok;
    yyclearin;
  }
#line 2362 "src/parser.cpp"
    break;

  case 59: /* Statement: If '(' Exp ')' '{' StatementList '}'  */
#line 553 "src/parser.y"
                                         {
      (yyval.node) = new Node(if_node, (yylsp[-6]).first_line);
      (yyval.node)->addChild((yyvsp[-4].node));
      (yyval.node)->addChild((yyvsp[-1].node));
  }
#line 2372 "src/parser.cpp"
    break;

  case 60: /* Statement: If '(' Exp ')' '{' StatementList '}' Else '{' StatementList '}'  */
#line 558 "src/parser.y"
                                                                    {
      (yyval.node) = new Node(if_node, (yylsp[-10]).first_line);
      (yyval.node)->addChild((yyvsp[-8].node));
      (yyval.node)->addChild((yyvsp[-5].node));

      Node * elsenode = new Node(else_node, (yylsp[-10]).first_line);
      elsenode->addChild((yyvsp[-1].node));

      (yyval.node)->addChild(elsenode);

  }
#line 2388 "src/parser.cpp"
    break;

  case 61: /* Statement: VariableAssign  */
#line 569 "src/parser.y"
                  {
      (yyval.node) = (yyvsp[0].node);
  }
#line 2396 "src/parser.cpp"
    break;

  case 62: /* Statement: call stringLiteral ';'  */
#line 572 "src/parser.y"
                           {
      (yyval.node) = new Node(call_node, (yylsp[-2]).first_line);
      (yyval.node)->setString((yyvsp[-1].str));
  }
#line 2405 "src/parser.cpp"
    break;

  case 63: /* Statement: LoopCall  */
#line 576 "src/parser.y"
             {
      (yyval.node) = (yyvsp[0].node);
  }
#line 2413 "src/parser.cpp"
    break;

  case 64: /* Statement: SetPinCall ';'  */
#line 579 "src/parser.y"
                   {
      (yyval.node) = (yyvsp[-1].node);
  }
#line 2421 "src/parser.cpp"
    break;

  case 65: /* Statement: ReadPinCall ';'  */
#line 582 "src/parser.y"
                    {
      (yyval.node) = (yyvsp[-1].node);
  }
#line 2429 "src/parser.cpp"
    break;

  case 66: /* Statement: ExpectCall ';'  */
#line 585 "src/parser.y"
                   {
      (yyval.node) = (yyvsp[-1].node);
  }
#line 2437 "src/parser.cpp"
    break;

  case 67: /* Statement: PrintCall ';'  */
#line 588 "src/parser.y"
                  {
      (yyval.node) = (yyvsp[-1].node);
  }
#line 2445 "src/parser.cpp"
    break;

  case 68: /* Statement: SendMsgCall ';'  */
#line 591 "src/parser.y"
                    {
      (yyval.node) = (yyvsp[-1].node);
  }
#line 2453 "src/parser.cpp"
    break;

  case 69: /* Statement: ReadMsgCall ';'  */
#line 594 "src/parser.y"
                    {
      (yyval.node) = (yyvsp[-1].node);
  }
#line 2461 "src/parser.cpp"
    break;

  case 70: /* Statement: DelayCall ';'  */
#line 597 "src/parser.y"
                  {
      (yyval.node) = (yyvsp[-1].node);
  }
#line 2469 "src/parser.cpp"
    break;

  case 71: /* Statement: PromptCall ';'  */
#line 600 "src/parser.y"
                   {
      (yyval.node) = (yyvsp[-1].node);
  }
#line 2477 "src/parser.cpp"
    break;

  case 72: /* Statement: serialTx Exp ';'  */
#line 603 "src/parser.y"
                     {
      (yyval.node) = new Node(serial_tx, (yylsp[-2]).first_line);
      (yyval.node)->addChild((yyvsp[-1].node));
  }
#line 2486 "src/parser.cpp"
    break;

  case 73: /* Statement: serialRx ';'  */
#line 607 "src/parser.y"
                 {
      (yyval.node) = new Node(serial_rx, (yylsp[-1]).first_line);
  }
#line 2494 "src/parser.cpp"
    break;

  case 74: /* Statement: exit_tok ';'  */
#line 610 "src/parser.y"
                 {
      (yyval.node) = new Node(exit_node, (yylsp[-1]).first_line);
  }
#line 2502 "src/parser.cpp"
    break;

  case 75: /* Statement: exit_tok stringLiteral ';'  */
#line 613 "src/parser.y"
                               {
      (yyval.node) = new Node(exit_node, (yylsp[-2]).first_line);
      (yyval.node)->setString((yyvsp[-1].str));
  }
#line 2511 "src/parser.cpp"
    break;

  case 76: /* Statement: Exp plusplus ';'  */
#line 617 "src/parser.y"
                    {
      node_type_t type = (yyvsp[-2].node)->node_type;

      if ((yyvsp[-2].node)->isLiteral() && (type == integerLiteral_node 
                              || type == hexLiteral_node))
      {
        (yyvsp[-2].node)->data.intval++;
      }
      else
      {
        (yyval.node) = new Node(unary_math_node, (yylsp[-2]).first_line);
        (yyval.node)->setString("++");
        (yyval.node)->addChild((yyvsp[-2].node));
      }

  }
#line 2532 "src/parser.cpp"
    break;

  case 77: /* Statement: Exp minusminus ';'  */
#line 633 "src/parser.y"
                      {
      node_type_t type = (yyvsp[-2].node)->node_type;

      if ((yyvsp[-2].node)->isLiteral() && (type == integerLiteral_node 
                              || type == hexLiteral_node))
      {
        (yyvsp[-2].node)->data.intval--;
      }
      else
      {
        (yyval.node) = new Node(unary_math_node, (yylsp[-2]).first_line);
        (yyval.node)->setString("--");
        (yyval.node)->addChild((yyvsp[-2].node));
      }
  }
#line 2552 "src/parser.cpp"
    break;


#line 2556 "src/parser.cpp"

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
  *++yylsp = yyloc;

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          goto yyexhaustedlab;
      }
    }

  yyerror_range[1] = yylloc;
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 650 "src/parser.y"



void yyerror(const char * err)
{
  printf("\n%s on line %d", err, yylloc.first_line);
}



int perform_math_op(Node * lhs, Node * rhs, std::string * op)
{
  std::string oper = *op;
  int lhs_val = lhs->data.intval;
  int rhs_val = rhs->data.intval;

  if (oper == "+")
  {
    lhs->setInt(lhs_val + rhs_val);
  } 
  else if (oper == "-")
  {
    lhs->setInt(lhs_val - rhs_val);
  } 
  else if (oper == "*")
  {
    lhs->setInt(lhs_val * rhs_val);
  } 
  else if (oper == "/")
  {
    lhs->setInt(lhs_val / rhs_val);
  }
  delete rhs;
  delete op;
  return lhs->data.intval;
}


