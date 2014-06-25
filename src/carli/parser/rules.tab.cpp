#ifdef _MSC_VER
#pragma warning(push, 1)
#pragma warning(disable : 4003)
#pragma warning(disable : 4702)
#endif
/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         reteparse
#define yylex           retelex
#define yyerror         reteerror
#define yylval          retelval
#define yychar          retechar
#define yydebug         retedebug
#define yynerrs         retenerrs
#define yylloc          retelloc

/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 34 "rules.yyy"

#define YY_NO_UNISTD_H 1
#include <csignal>
#include <cstdio>
#include <sstream>
#include "rete_parser.h"

using namespace std;

static unordered_map<string, shared_ptr<tuple<double, double, bool>>> * Flags(const string &flag, const shared_ptr<tuple<double, double, bool>> &value, std::unordered_map<std::string, std::shared_ptr<std::tuple<double, double, bool>>> * flags = nullptr) {
  if(!flags)
    flags = new std::unordered_map<std::string, std::shared_ptr<std::tuple<double, double, bool>>>;
  (*flags)[flag] = value;
  return flags;
}

static array<string, 3> Variable(const string &s0, const string &s1, const string &s2) {
  array<string, 3> variable;
  variable[0] = s0;
  variable[1] = s1;
  variable[2] = s2;
  return variable;
}
static vector<array<string, 3>> Variables() {
  vector<array<string, 3>> rv;
  return rv;
}
static vector<array<string, 3>> Variables(const array<string, 3> &variable) {
  vector<array<string, 3>> rv;
  rv.push_back(variable);
  return rv;
}
static pair<Rete::Rete_Node_Ptr, vector<array<string, 3>>> *
Rete_Node_Ptr_and_Variables(const Rete::Rete_Node_Ptr &rete_node, const vector<array<string, 3>> &variables) {
  return new pair<Rete::Rete_Node_Ptr, vector<array<string, 3>>>(rete_node, variables);
}

static Rete::WME_Token_Index find_index(const std::vector<std::array<std::string, 3>> &variables, const std::string &variable) {
  for(size_t i = 0; i != variables.size(); ++i) {
    for(uint8_t ii = 0; ii != 3; ++ii) {
      if(variables[i][ii] == variable)
        return Rete::WME_Token_Index(i, ii);
    }
  }
  return Rete::WME_Token_Index(size_t(-1), uint8_t(-1));
}

static Rete::WME_Bindings join_bindings(const std::vector<std::array<std::string, 3>> &lhs,
                                        const std::vector<std::array<std::string, 3>> &rhs)
{
  Rete::WME_Bindings bindings;
  unordered_set<string> joined;
  for(size_t i = 0; i != lhs.size(); ++i) {
    for(uint8_t ii = 0; ii != 3; ++ii) {
      if(!lhs[i][ii].empty() && joined.find(lhs[i][ii]) == joined.end()) {
        for(size_t j = 0; j != rhs.size(); ++j) {
          for(uint8_t jj = 0; jj != 3; ++jj) {
            if(lhs[i][ii] == rhs[j][jj]) {
              bindings.insert(Rete::WME_Binding(Rete::WME_Token_Index(i, ii), Rete::WME_Token_Index(j, jj)));
              joined.insert(lhs[i][ii]);
              goto DONE_JOINING;
            }
          }
        }
      }
      DONE_JOINING:
        ;
    }
  }
  return bindings;
}

static Rete::Variable_Indices variables_to_indices(const vector<array<string, 3>> &variables) {
  Rete::Variable_Indices indices;
  for(size_t i = 0; i != variables.size(); ++i) {
    for(uint8_t ii = 0; ii != 3; ++ii) {
      if(!variables[i][ii].empty() && indices.find(variables[i][ii]) == indices.end())
        indices[variables[i][ii]] = Rete::WME_Token_Index(i, ii);
    }
  }
  return indices;
}


/* Line 371 of yacc.c  */
#line 161 "rules.tab.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "rules.tab.hh".  */
#ifndef YY_RETE_RULES_TAB_HH_INCLUDED
# define YY_RETE_RULES_TAB_HH_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int retedebug;
#endif
/* "%code requires" blocks.  */
/* Line 387 of yacc.c  */
#line 14 "rules.yyy"

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void *yyscan_t;
#endif


/* Line 387 of yacc.c  */
#line 201 "rules.tab.cpp"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     COMMAND_EXCISE = 258,
     COMMAND_EXCISE_ALL = 259,
     COMMAND_EXIT = 260,
     COMMAND_INSERT_WME = 261,
     COMMAND_REMOVE_WME = 262,
     COMMAND_SOURCE = 263,
     COMMAND_SP = 264,
     FLAG_FEATURE = 265,
     FLOAT = 266,
     INT = 267,
     NODE_TYPE = 268,
     STRING = 269,
     STRING_PART_C = 270,
     STRING_PART_S = 271,
     VARIABLE = 272,
     PREDICATE = 273
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 119 "rules.yyy"

  char cval;
  const char *csval;
  std::tuple<int64_t, std::string, Carli::Feature *> *flag_ptr;
  double fval;
  int64_t ival;
  std::string *sval;
  std::pair<Rete::Rete_Node_Ptr, std::vector<std::array<std::string, 3>>> *rete_node_ptr;
  std::tuple<std::pair<Rete::Rete_Node_Ptr, std::vector<std::array<std::string, 3>>>, std::string, std::tuple<int64_t, std::string, Carli::Feature *>> *rule_ptr;
  Rete::Symbol_Ptr_C *symbol_ptr;
  Rete::Rete_Predicate::Predicate predicate;


/* Line 387 of yacc.c  */
#line 248 "rules.tab.cpp"
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


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int reteparse (void *YYPARSE_PARAM);
#else
int reteparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int reteparse (yyscan_t yyscanner, Carli::Agent &agent, const std::string &filename, const std::string &source_path);
#else
int reteparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_RETE_RULES_TAB_HH_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 288 "rules.tab.cpp"
/* Unqualified %code blocks.  */
/* Line 391 of yacc.c  */
#line 21 "rules.yyy"

#include "lex.rete.hh"

static volatile sig_atomic_t g_rete_exit = false;

static void reteerror(const YYLTYPE * const /*yylloc*/, yyscan_t const yyscanner, Rete::Rete_Agent &/*agent*/, const std::string &filename, const std::string &/*source_path*/, const char *msg) {
  if(filename.empty())
    cout << "rete-parse error: " << msg << endl;
  else
    cout << "rete-parse error " << filename << '(' << reteget_lineno(yyscanner) << "): " << msg << endl;
}


/* Line 391 of yacc.c  */
#line 306 "rules.tab.cpp"

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

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
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

# define YYCOPY_NEEDED 1

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

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   109

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  28
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  44
/* YYNRULES -- Number of states.  */
#define YYNSTATES  93

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   273

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      19,    21,     2,    24,     2,    25,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    26,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    20,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    22,    27,    23,     2,     2,     2,     2,
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
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    12,    14,    22,    30,
      33,    36,    41,    47,    54,    61,    65,    67,    70,    73,
      77,    81,    84,    91,    98,   100,   104,   106,   108,   115,
     122,   129,   136,   138,   140,   143,   145,   147,   149,   151,
     153,   157,   160,   163,   165
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      29,     0,    -1,    -1,    29,    30,    -1,     3,    14,    -1,
       4,    -1,     5,    -1,     6,    19,    38,    20,    38,    38,
      21,    -1,     7,    19,    38,    20,    38,    38,    21,    -1,
       8,    41,    -1,     9,    31,    -1,    22,    14,    33,    23,
      -1,    22,    14,    32,    33,    23,    -1,    10,    12,    13,
      12,    11,    11,    -1,    10,    12,    13,    12,    12,    12,
      -1,    10,    12,    13,    -1,    34,    -1,    24,    34,    -1,
      25,    34,    -1,    33,    24,    36,    -1,    33,    25,    36,
      -1,    34,    36,    -1,    34,    19,    17,    18,    40,    21,
      -1,    34,    19,    17,    18,    17,    21,    -1,    36,    -1,
      22,    33,    23,    -1,    37,    -1,    35,    -1,    19,    17,
      20,    40,    40,    21,    -1,    19,    17,    20,    40,    17,
      21,    -1,    19,    17,    20,    17,    40,    21,    -1,    19,
      17,    20,    17,    17,    21,    -1,    40,    -1,    39,    -1,
      26,    14,    -1,    11,    -1,    12,    -1,    41,    -1,    14,
      -1,    42,    -1,    27,    43,    27,    -1,    43,    15,    -1,
      43,    16,    -1,    15,    -1,    16,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   156,   156,   157,   160,   162,   163,   165,   170,   175,
     187,   271,   274,   281,   283,   285,   289,   290,   291,   292,
     295,   300,   305,   314,   324,   327,   330,   331,   334,   335,
     336,   337,   340,   341,   344,   347,   348,   349,   352,   353,
     356,   359,   360,   361,   362
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "COMMAND_EXCISE", "COMMAND_EXCISE_ALL",
  "COMMAND_EXIT", "COMMAND_INSERT_WME", "COMMAND_REMOVE_WME",
  "COMMAND_SOURCE", "COMMAND_SP", "FLAG_FEATURE", "FLOAT", "INT",
  "NODE_TYPE", "STRING", "STRING_PART_C", "STRING_PART_S", "VARIABLE",
  "PREDICATE", "'('", "'^'", "')'", "'{'", "'}'", "'+'", "'-'", "'@'",
  "'|'", "$accept", "commands", "command", "rule", "flag",
  "final_conditions", "conditions", "condition_group", "condition_type",
  "condition", "symbol", "identifier", "symbol_constant",
  "string_or_literal", "literal", "literal_parts", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,    40,
      94,    41,   123,   125,    43,    45,    64,   124
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    28,    29,    29,    30,    30,    30,    30,    30,    30,
      30,    31,    31,    32,    32,    32,    33,    33,    33,    33,
      33,    34,    34,    34,    34,    35,    36,    36,    37,    37,
      37,    37,    38,    38,    39,    40,    40,    40,    41,    41,
      42,    43,    43,    43,    43
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     7,     7,     2,
       2,     4,     5,     6,     6,     3,     1,     2,     2,     3,
       3,     2,     6,     6,     1,     3,     1,     1,     6,     6,
       6,     6,     1,     1,     2,     1,     1,     1,     1,     1,
       3,     2,     2,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     5,     6,     0,     0,     0,     0,
       3,     4,     0,     0,    38,     0,     9,    39,     0,    10,
      35,    36,     0,     0,    33,    32,    37,     0,    43,    44,
       0,     0,    34,     0,     0,    41,    42,    40,     0,     0,
       0,     0,     0,     0,     0,    16,    27,    24,    26,     0,
       0,     0,     0,     0,    17,    18,     0,    11,     0,     0,
       0,    21,     0,     0,    15,     0,    25,    12,    19,    20,
       0,     7,     8,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    13,    14,    31,    30,    29,
      28,    23,    22
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    10,    19,    43,    44,    45,    46,    47,    48,
      23,    24,    25,    26,    17,    30
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -41
static const yytype_int8 yypact[] =
{
     -41,    66,   -41,    17,   -41,   -41,   -16,    15,    11,    18,
     -41,   -41,   -10,   -10,   -41,    33,   -41,   -41,    31,   -41,
     -41,   -41,    42,    39,   -41,   -41,   -41,    58,   -41,   -41,
      35,    36,   -41,   -10,   -10,   -41,   -41,   -41,    65,    72,
      57,    -9,    -9,    57,    60,    13,   -41,   -41,   -41,   -10,
     -10,    81,    76,    63,    13,    13,    67,   -41,    -9,    -9,
      80,   -41,    59,    77,    87,    -5,   -41,   -41,   -41,   -41,
      75,   -41,   -41,    41,    12,    16,    30,    89,    90,    82,
      83,    84,    85,    86,    88,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -41,   -41,   -41,   -41,   -41,   -32,    26,   -41,   -40,   -41,
     -13,   -41,   -11,    93,   -41,   -41
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      27,    20,    21,    12,    14,    61,    20,    21,    53,    14,
      39,    56,    74,    40,    61,    61,    22,    15,    68,    69,
      49,    50,    15,    20,    21,    14,    14,    20,    21,    79,
      14,    11,    60,    81,    13,    40,    62,    63,    15,    15,
      18,    20,    21,    15,    14,    31,    38,    83,    28,    29,
      35,    36,    77,    78,    75,    39,    32,    15,    40,    33,
      41,    42,    37,    80,    82,    84,     2,    54,    55,     3,
       4,     5,     6,     7,     8,     9,    39,    51,    34,    40,
      71,    41,    42,    57,    58,    59,    66,    58,    59,    52,
      67,    58,    59,    76,    64,    65,    65,    70,    72,    73,
      85,    16,    86,    87,    88,    89,    90,    91,     0,    92
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-41)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      13,    11,    12,    19,    14,    45,    11,    12,    40,    14,
      19,    43,    17,    22,    54,    55,    26,    27,    58,    59,
      33,    34,    27,    11,    12,    14,    14,    11,    12,    17,
      14,    14,    19,    17,    19,    22,    49,    50,    27,    27,
      22,    11,    12,    27,    14,    14,    10,    17,    15,    16,
      15,    16,    11,    12,    65,    19,    14,    27,    22,    20,
      24,    25,    27,    74,    75,    76,     0,    41,    42,     3,
       4,     5,     6,     7,     8,     9,    19,    12,    20,    22,
      21,    24,    25,    23,    24,    25,    23,    24,    25,    17,
      23,    24,    25,    18,    13,    20,    20,    17,    21,    12,
      11,     8,    12,    21,    21,    21,    21,    21,    -1,    21
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    29,     0,     3,     4,     5,     6,     7,     8,     9,
      30,    14,    19,    19,    14,    27,    41,    42,    22,    31,
      11,    12,    26,    38,    39,    40,    41,    38,    15,    16,
      43,    14,    14,    20,    20,    15,    16,    27,    10,    19,
      22,    24,    25,    32,    33,    34,    35,    36,    37,    38,
      38,    12,    17,    33,    34,    34,    33,    23,    24,    25,
      19,    36,    38,    38,    13,    20,    23,    23,    36,    36,
      17,    21,    21,    12,    17,    40,    18,    11,    12,    17,
      40,    17,    40,    17,    40,    11,    12,    21,    21,    21,
      21,    21,    21
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (&yylloc, yyscanner, agent, filename, source_path, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
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
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

__attribute__((__unused__))
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
#else
static unsigned
yy_location_print_ (yyo, yylocp)
    FILE *yyo;
    YYLTYPE const * const yylocp;
#endif
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += fprintf (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += fprintf (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += fprintf (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += fprintf (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += fprintf (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc, yyscanner)
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
		  Type, Value, Location, yyscanner, agent, filename, source_path); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t yyscanner, Carli::Agent &agent, const std::string &filename, const std::string &source_path)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, yyscanner, agent, filename, source_path)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    yyscan_t yyscanner;
    Carli::Agent &agent;
    const std::string &filename;
    const std::string &source_path;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (yyscanner);
  YYUSE (agent);
  YYUSE (filename);
  YYUSE (source_path);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t yyscanner, Carli::Agent &agent, const std::string &filename, const std::string &source_path)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, yyscanner, agent, filename, source_path)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    yyscan_t yyscanner;
    Carli::Agent &agent;
    const std::string &filename;
    const std::string &source_path;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, yyscanner, agent, filename, source_path);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, yyscan_t yyscanner, Carli::Agent &agent, const std::string &filename, const std::string &source_path)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, yyscanner, agent, filename, source_path)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    yyscan_t yyscanner;
    Carli::Agent &agent;
    const std::string &filename;
    const std::string &source_path;
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
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , yyscanner, agent, filename, source_path);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, yyscanner, agent, filename, source_path); \
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, yyscan_t yyscanner, Carli::Agent &agent, const std::string &filename, const std::string &source_path)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, yyscanner, agent, filename, source_path)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    yyscan_t yyscanner;
    Carli::Agent &agent;
    const std::string &filename;
    const std::string &source_path;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (yyscanner);
  YYUSE (agent);
  YYUSE (filename);
  YYUSE (source_path);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




/*----------.
| yyparse.  |
`----------*/

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
yyparse (yyscan_t yyscanner, Carli::Agent &agent, const std::string &filename, const std::string &source_path)
#else
int
yyparse (yyscanner, agent, filename, source_path)
    yyscan_t yyscanner;
    Carli::Agent &agent;
    const std::string &filename;
    const std::string &source_path;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;


#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
static YYSTYPE yyval_default;
# define YY_INITIAL_VALUE(Value) = Value
#endif
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc = yyloc_default;


    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
  if (yypact_value_is_default (yyn))
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
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
        case 3:
/* Line 1787 of yacc.c  */
#line 157 "rules.yyy"
    { /*cerr << "Read in rule on line " << reteget_lineno(yyscanner) << endl;*/ }
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 160 "rules.yyy"
    { agent.excise_rule(*(yyvsp[(2) - (2)].sval), true);
                          delete (yyvsp[(2) - (2)].sval); }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 162 "rules.yyy"
    { agent.excise_all(); }
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 163 "rules.yyy"
    { g_rete_exit = true;
                   YYACCEPT; }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 165 "rules.yyy"
    { const auto wme = make_shared<Rete::WME>(*(yyvsp[(3) - (7)].symbol_ptr), *(yyvsp[(5) - (7)].symbol_ptr), *(yyvsp[(6) - (7)].symbol_ptr));
                                                          agent.insert_wme(wme);
                                                          delete (yyvsp[(3) - (7)].symbol_ptr);
                                                          delete (yyvsp[(5) - (7)].symbol_ptr);
                                                          delete (yyvsp[(6) - (7)].symbol_ptr); }
    break;

  case 8:
/* Line 1787 of yacc.c  */
#line 170 "rules.yyy"
    { const auto wme = make_shared<Rete::WME>(*(yyvsp[(3) - (7)].symbol_ptr), *(yyvsp[(5) - (7)].symbol_ptr), *(yyvsp[(6) - (7)].symbol_ptr));
                                                          agent.remove_wme(wme);
                                                          delete (yyvsp[(3) - (7)].symbol_ptr);
                                                          delete (yyvsp[(5) - (7)].symbol_ptr);
                                                          delete (yyvsp[(6) - (7)].symbol_ptr); }
    break;

  case 9:
/* Line 1787 of yacc.c  */
#line 175 "rules.yyy"
    { const int rv = rete_parse_file(agent, *(yyvsp[(2) - (2)].sval), source_path);
                                       if(rv) {
                                         ostringstream oss;
                                         oss << "Error sourcing '" << *(yyvsp[(2) - (2)].sval) << "'.";
                                         reteerror(&yylloc, yyscanner, agent, filename, source_path, oss.str().c_str());
                                         delete (yyvsp[(2) - (2)].sval);
                                         YYABORT;
                                       }
                                       delete (yyvsp[(2) - (2)].sval);
                                       if(g_rete_exit) {
                                         YYACCEPT;
                                       } }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 187 "rules.yyy"
    { const auto &parent = get<0>(*(yyvsp[(2) - (2)].rule_ptr)).first;
                      const auto &variable_names = get<0>(*(yyvsp[(2) - (2)].rule_ptr)).second;
                      const string &name = get<1>(*(yyvsp[(2) - (2)].rule_ptr));
                      const int64_t &q_value_depth = get<0>(get<2>(*(yyvsp[(2) - (2)].rule_ptr)));
                      const string &node_type = get<1>(get<2>(*(yyvsp[(2) - (2)].rule_ptr)));
                      const auto &feature = get<2>(get<2>(*(yyvsp[(2) - (2)].rule_ptr)));
                      const auto variable_indices = variables_to_indices(variable_names);

                      agent.get_agenda().lock();
                      const auto existing = agent.unname_rule(name, true);
                      if(existing) {
                        parent->suppress_destruction(true);
                        existing->destroy(agent);
                      }

                      Rete::Rete_Action_Ptr new_action;
                      if(!feature) {
                        /// Root/General RL action
                        const auto root_action = agent.make_standard_action(parent, name, true);
                        const auto root_action_data = std::make_shared<Carli::Node_Unsplit>(agent, root_action, 1, nullptr);
                        root_action->data = root_action_data;
                      }
                      else {
                        feature->axis = variable_indices.find((*variable_names.rbegin())[0])->second;

                        if(const auto feature_e = dynamic_cast<Carli::Feature_Enumerated<Carli::Feature> *>(feature)) {
                          /// TODO: Handle variable-to-variable relations
                          if(const auto predicate = dynamic_cast<Rete::Rete_Predicate *>(parent.get())) {
                            const auto rhs = predicate->get_rhs().get();
                            const auto symbol_i = dynamic_cast<const Rete::Symbol_Constant_Int *>(rhs);
                            assert(symbol_i);
                            feature_e->value = symbol_i->value;
                          }
                          else if(dynamic_cast<Rete::Rete_Existential_Join *>(parent.get()))
                            feature_e->value = true;
                          else if(dynamic_cast<Rete::Rete_Negation_Join *>(parent.get()))
                            feature_e->value = false;
                          else
                            abort();
                        }
                        else if(const auto feature_r = dynamic_cast<Carli::Feature_Ranged<Carli::Feature> *>(feature)) {
                          const auto &predicate = dynamic_cast<Rete::Rete_Predicate &>(*parent);
                          feature_r->upper = predicate.get_predicate() == Rete::Rete_Predicate::GTE;
                        }
                        else
                          abort();

                        if(node_type == "split") {
                          const auto filter = dynamic_cast<Rete::Rete_Filter *>(parent->parent_right().get());
                          bool terminal = true;
                          if(filter) {
                            const auto &wme = filter->get_wme();
                            terminal = !dynamic_cast<const Rete::Symbol_Variable *>(wme.symbols[0].get()) ||
                                       wme.symbols[0] != wme.symbols[1] || wme.symbols[0] != wme.symbols[2];
                          }

                          const auto new_q_value = new Carli::Q_Value(0.0, Carli::Q_Value::Type::SPLIT, q_value_depth, feature);
                          new_action = agent.make_standard_action(parent, name, true, variable_indices);
                          auto new_action_data = std::make_shared<Carli::Node_Split>(agent, new_action, new_q_value, terminal);
                          new_action->data = new_action_data;
                        }
                        else if(node_type == "unsplit") {
                          Carli::Fringe_Values node_unsplit_fringe; ///< TODO
                          new_action = agent.make_standard_action(parent, name, true, variable_indices);
                          auto new_action_data = std::make_shared<Carli::Node_Unsplit>(agent, new_action, q_value_depth, feature);
                          new_action->data = new_action_data;
                          new_action_data->fringe_values.swap(node_unsplit_fringe);
                        }
                        else {
                          assert(node_type == "fringe");
                          Carli::Node_Unsplit_Ptr node_unsplit_ptr; ///< TODO
                          new_action = agent.make_standard_action(parent, name, true, variable_indices);
                          auto new_action_data = std::make_shared<Carli::Node_Fringe>(agent, new_action, q_value_depth, feature);
                          new_action->data = new_action_data;
                          node_unsplit_ptr->fringe_values[feature].values.push_back(new_action_data);
                        }
                      }

                      parent->suppress_destruction(false);
                      agent.get_agenda().unlock();
                      agent.get_agenda().run();
                      delete (yyvsp[(2) - (2)].rule_ptr); }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 271 "rules.yyy"
    { (yyval.rule_ptr) = new tuple<std::pair<Rete::Rete_Node_Ptr, std::vector<std::array<std::string, 3>>>, std::string, tuple<int64_t, string, Carli::Feature *>>(*(yyvsp[(3) - (4)].rete_node_ptr), *(yyvsp[(2) - (4)].sval), tuple<int64_t, string, Carli::Feature *>());
                                    delete (yyvsp[(2) - (4)].sval);
                                    delete (yyvsp[(3) - (4)].rete_node_ptr); }
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 274 "rules.yyy"
    { (yyval.rule_ptr) = new tuple<std::pair<Rete::Rete_Node_Ptr, std::vector<std::array<std::string, 3>>>, std::string, tuple<int64_t, string, Carli::Feature *>>(*(yyvsp[(4) - (5)].rete_node_ptr), *(yyvsp[(2) - (5)].sval), *(yyvsp[(3) - (5)].flag_ptr));
                                           delete (yyvsp[(2) - (5)].sval);
                                           delete (yyvsp[(3) - (5)].flag_ptr);
                                           delete (yyvsp[(4) - (5)].rete_node_ptr); }
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 281 "rules.yyy"
    { (yyval.flag_ptr) = new tuple<int64_t, string, Carli::Feature *>((yyvsp[(2) - (6)].ival), *(yyvsp[(3) - (6)].sval), new Carli::Feature_Ranged<Carli::Feature>(Rete::WME_Token_Index() /*FIXUP later*/, (yyvsp[(5) - (6)].fval), (yyvsp[(6) - (6)].fval), (yyvsp[(4) - (6)].ival), false /*FIXUP later*/, false));
                                               delete (yyvsp[(3) - (6)].sval); }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 283 "rules.yyy"
    { (yyval.flag_ptr) = new tuple<int64_t, string, Carli::Feature *>((yyvsp[(2) - (6)].ival), *(yyvsp[(3) - (6)].sval), new Carli::Feature_Ranged<Carli::Feature>(Rete::WME_Token_Index() /*FIXUP later*/, (yyvsp[(5) - (6)].ival), (yyvsp[(6) - (6)].ival), (yyvsp[(4) - (6)].ival), false /*FIXUP later*/, true));
                                             delete (yyvsp[(3) - (6)].sval); }
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 285 "rules.yyy"
    { (yyval.flag_ptr) = new tuple<int64_t, string, Carli::Feature *>((yyvsp[(2) - (3)].ival), *(yyvsp[(3) - (3)].sval), new Carli::Feature_Enumerated<Carli::Feature>(Rete::WME_Token_Index() /*FIXUP later*/, 0 /*FIXUP later*/));
                                 delete (yyvsp[(3) - (3)].sval); }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 289 "rules.yyy"
    { (yyval.rete_node_ptr) = (yyvsp[(1) - (1)].rete_node_ptr); }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 290 "rules.yyy"
    { (yyval.rete_node_ptr) = Rete_Node_Ptr_and_Variables(Rete::Rete_Node_Ptr(agent.make_existential((yyvsp[(2) - (2)].rete_node_ptr)->first)), Variables()); delete (yyvsp[(2) - (2)].rete_node_ptr); }
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 291 "rules.yyy"
    { (yyval.rete_node_ptr) = Rete_Node_Ptr_and_Variables(Rete::Rete_Node_Ptr(agent.make_negation((yyvsp[(2) - (2)].rete_node_ptr)->first)), Variables()); delete (yyvsp[(2) - (2)].rete_node_ptr); }
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 292 "rules.yyy"
    { (yyval.rete_node_ptr) = Rete_Node_Ptr_and_Variables(Rete::Rete_Node_Ptr(agent.make_existential_join(join_bindings((yyvsp[(1) - (3)].rete_node_ptr)->second, (yyvsp[(3) - (3)].rete_node_ptr)->second), (yyvsp[(1) - (3)].rete_node_ptr)->first, (yyvsp[(3) - (3)].rete_node_ptr)->first)), (yyvsp[(1) - (3)].rete_node_ptr)->second);
                                          delete (yyvsp[(1) - (3)].rete_node_ptr);
                                          delete (yyvsp[(3) - (3)].rete_node_ptr); }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 295 "rules.yyy"
    { (yyval.rete_node_ptr) = Rete_Node_Ptr_and_Variables(Rete::Rete_Node_Ptr(agent.make_negation_join(join_bindings((yyvsp[(1) - (3)].rete_node_ptr)->second, (yyvsp[(3) - (3)].rete_node_ptr)->second), (yyvsp[(1) - (3)].rete_node_ptr)->first, (yyvsp[(3) - (3)].rete_node_ptr)->first)), (yyvsp[(1) - (3)].rete_node_ptr)->second);
                                          delete (yyvsp[(1) - (3)].rete_node_ptr);
                                          delete (yyvsp[(3) - (3)].rete_node_ptr); }
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 300 "rules.yyy"
    { vector<array<string, 3>> variables((yyvsp[(1) - (2)].rete_node_ptr)->second);
                              variables.insert(variables.end(), (yyvsp[(2) - (2)].rete_node_ptr)->second.begin(), (yyvsp[(2) - (2)].rete_node_ptr)->second.end());
                              (yyval.rete_node_ptr) = Rete_Node_Ptr_and_Variables(Rete::Rete_Node_Ptr(agent.make_join(join_bindings((yyvsp[(1) - (2)].rete_node_ptr)->second, (yyvsp[(2) - (2)].rete_node_ptr)->second), (yyvsp[(1) - (2)].rete_node_ptr)->first, (yyvsp[(2) - (2)].rete_node_ptr)->first)), variables);
                              delete (yyvsp[(1) - (2)].rete_node_ptr);
                              delete (yyvsp[(2) - (2)].rete_node_ptr); }
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 305 "rules.yyy"
    { const auto lhs_index = find_index((yyvsp[(1) - (6)].rete_node_ptr)->second, *(yyvsp[(3) - (6)].sval));
                                                            if(lhs_index.second > 2) {
                                                              reteerror(&yylloc, yyscanner, agent, filename, source_path, "Unbound variable tested by predicate.");
                                                              YYABORT;
                                                            }
                                                            (yyval.rete_node_ptr) = Rete_Node_Ptr_and_Variables(Rete::Rete_Node_Ptr(agent.make_predicate_vc((yyvsp[(4) - (6)].predicate), lhs_index, *(yyvsp[(5) - (6)].symbol_ptr), (yyvsp[(1) - (6)].rete_node_ptr)->first)), (yyvsp[(1) - (6)].rete_node_ptr)->second);
                                                            delete (yyvsp[(1) - (6)].rete_node_ptr);
                                                            delete (yyvsp[(3) - (6)].sval);
                                                            delete (yyvsp[(5) - (6)].symbol_ptr); }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 314 "rules.yyy"
    { const auto lhs_index = find_index((yyvsp[(1) - (6)].rete_node_ptr)->second, *(yyvsp[(3) - (6)].sval));
                                                     const auto rhs_index = find_index((yyvsp[(1) - (6)].rete_node_ptr)->second, *(yyvsp[(5) - (6)].sval));
                                                     if(lhs_index.second > 2 || rhs_index.second > 2) {
                                                       reteerror(&yylloc, yyscanner, agent, filename, source_path, "Unbound variable tested by predicate.");
                                                       YYABORT;
                                                     }
                                                     (yyval.rete_node_ptr) = Rete_Node_Ptr_and_Variables(Rete::Rete_Node_Ptr(agent.make_predicate_vv((yyvsp[(4) - (6)].predicate), lhs_index, rhs_index, (yyvsp[(1) - (6)].rete_node_ptr)->first)), (yyvsp[(1) - (6)].rete_node_ptr)->second);
                                                     delete (yyvsp[(1) - (6)].rete_node_ptr);
                                                     delete (yyvsp[(3) - (6)].sval);
                                                     delete (yyvsp[(5) - (6)].sval); }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 324 "rules.yyy"
    { (yyval.rete_node_ptr) = (yyvsp[(1) - (1)].rete_node_ptr); }
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 327 "rules.yyy"
    { (yyval.rete_node_ptr) = (yyvsp[(2) - (3)].rete_node_ptr); }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 330 "rules.yyy"
    { (yyval.rete_node_ptr) = (yyvsp[(1) - (1)].rete_node_ptr); }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 331 "rules.yyy"
    { (yyval.rete_node_ptr) = (yyvsp[(1) - (1)].rete_node_ptr); }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 334 "rules.yyy"
    { (yyval.rete_node_ptr) = Rete_Node_Ptr_and_Variables(Rete::Rete_Node_Ptr(agent.make_filter(Rete::WME(make_shared<Rete::Symbol_Variable>(Rete::Symbol_Variable::First), *(yyvsp[(4) - (6)].symbol_ptr), *(yyvsp[(5) - (6)].symbol_ptr)))), Variables(Variable(*(yyvsp[(2) - (6)].sval), "", ""))); delete (yyvsp[(2) - (6)].sval); delete (yyvsp[(4) - (6)].symbol_ptr); delete (yyvsp[(5) - (6)].symbol_ptr); }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 335 "rules.yyy"
    { (yyval.rete_node_ptr) = Rete_Node_Ptr_and_Variables(Rete::Rete_Node_Ptr(agent.make_filter(Rete::WME(make_shared<Rete::Symbol_Variable>(Rete::Symbol_Variable::First), *(yyvsp[(4) - (6)].symbol_ptr), make_shared<Rete::Symbol_Variable>(*(yyvsp[(2) - (6)].sval) == *(yyvsp[(5) - (6)].sval) ? Rete::Symbol_Variable::First : Rete::Symbol_Variable::Third)))), Variables(Variable(*(yyvsp[(2) - (6)].sval), "", *(yyvsp[(5) - (6)].sval)))); delete (yyvsp[(2) - (6)].sval); delete (yyvsp[(4) - (6)].symbol_ptr); delete (yyvsp[(5) - (6)].sval); }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 336 "rules.yyy"
    { (yyval.rete_node_ptr) = Rete_Node_Ptr_and_Variables(Rete::Rete_Node_Ptr(agent.make_filter(Rete::WME(make_shared<Rete::Symbol_Variable>(Rete::Symbol_Variable::First), make_shared<Rete::Symbol_Variable>(*(yyvsp[(2) - (6)].sval) == *(yyvsp[(4) - (6)].sval) ? Rete::Symbol_Variable::First : Rete::Symbol_Variable::Second), *(yyvsp[(5) - (6)].symbol_ptr)))), Variables(Variable(*(yyvsp[(2) - (6)].sval), *(yyvsp[(4) - (6)].sval), ""))); delete (yyvsp[(2) - (6)].sval); delete (yyvsp[(4) - (6)].sval); delete (yyvsp[(5) - (6)].symbol_ptr); }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 337 "rules.yyy"
    { (yyval.rete_node_ptr) = Rete_Node_Ptr_and_Variables(Rete::Rete_Node_Ptr(agent.make_filter(Rete::WME(make_shared<Rete::Symbol_Variable>(Rete::Symbol_Variable::First), make_shared<Rete::Symbol_Variable>(*(yyvsp[(2) - (6)].sval) == *(yyvsp[(4) - (6)].sval) ? Rete::Symbol_Variable::First : Rete::Symbol_Variable::Second), make_shared<Rete::Symbol_Variable>(*(yyvsp[(2) - (6)].sval) == *(yyvsp[(5) - (6)].sval) ? Rete::Symbol_Variable::First : *(yyvsp[(4) - (6)].sval) == *(yyvsp[(5) - (6)].sval) ? Rete::Symbol_Variable::Second : Rete::Symbol_Variable::Third)))), Variables(Variable(*(yyvsp[(2) - (6)].sval), *(yyvsp[(4) - (6)].sval), *(yyvsp[(5) - (6)].sval)))); delete (yyvsp[(2) - (6)].sval); delete (yyvsp[(4) - (6)].sval); delete (yyvsp[(5) - (6)].sval); }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 340 "rules.yyy"
    { (yyval.symbol_ptr) = (yyvsp[(1) - (1)].symbol_ptr); }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 341 "rules.yyy"
    { (yyval.symbol_ptr) = (yyvsp[(1) - (1)].symbol_ptr); }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 344 "rules.yyy"
    { (yyval.symbol_ptr) = new Rete::Symbol_Ptr_C(make_shared<Rete::Symbol_Identifier>(*(yyvsp[(2) - (2)].sval))); delete (yyvsp[(2) - (2)].sval); }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 347 "rules.yyy"
    { (yyval.symbol_ptr) = new Rete::Symbol_Ptr_C(make_shared<Rete::Symbol_Constant_Float>((yyvsp[(1) - (1)].fval))); }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 348 "rules.yyy"
    { (yyval.symbol_ptr) = new Rete::Symbol_Ptr_C(make_shared<Rete::Symbol_Constant_Int>((yyvsp[(1) - (1)].ival))); }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 349 "rules.yyy"
    { (yyval.symbol_ptr) = new Rete::Symbol_Ptr_C(make_shared<Rete::Symbol_Constant_String>(*(yyvsp[(1) - (1)].sval))); delete (yyvsp[(1) - (1)].sval); }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 352 "rules.yyy"
    { (yyval.sval) = (yyvsp[(1) - (1)].sval); }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 353 "rules.yyy"
    { (yyval.sval) = (yyvsp[(1) - (1)].sval); }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 356 "rules.yyy"
    { (yyval.sval) = (yyvsp[(2) - (3)].sval); }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 359 "rules.yyy"
    { (yyval.sval) = (yyvsp[(1) - (2)].sval); *(yyval.sval) += (yyvsp[(2) - (2)].cval); }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 360 "rules.yyy"
    { (yyval.sval) = (yyvsp[(1) - (2)].sval); *(yyval.sval) += *(yyvsp[(2) - (2)].sval); delete (yyvsp[(2) - (2)].sval); }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 361 "rules.yyy"
    { (yyval.sval) = new string; *(yyval.sval) += (yyvsp[(1) - (1)].cval); }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 362 "rules.yyy"
    { (yyval.sval) = (yyvsp[(1) - (1)].sval); }
    break;


/* Line 1787 of yacc.c  */
#line 2110 "rules.tab.cpp"
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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, yyscanner, agent, filename, source_path, YY_("syntax error"));
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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
        yyerror (&yylloc, yyscanner, agent, filename, source_path, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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
		      yytoken, &yylval, &yylloc, yyscanner, agent, filename, source_path);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, yyscanner, agent, filename, source_path);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, yyscanner, agent, filename, source_path, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, yyscanner, agent, filename, source_path);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, yyscanner, agent, filename, source_path);
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


/* Line 2050 of yacc.c  */
#line 365 "rules.yyy"


bool rete_get_exit() {
  return g_rete_exit;
}

int rete_parse_file(Carli::Agent &agent, const string &filename, const std::string &source_path) {
  if(filename.empty())
    return -1;

  string source_path_full = source_path;
  string filename_part = filename;
  string filename_full;
  const size_t filename_slash_pos = filename.find_last_of("/\\");
  if(filename_slash_pos != string::npos) {
    if(filename[0] == '/' || filename[0] == '\\')
      source_path_full.clear();
    source_path_full += filename.substr(0, filename_slash_pos + 1);
    filename_part = filename.substr(filename_slash_pos + 1);
  }
  filename_full = source_path_full + filename_part;

  //cerr << "Sourcing '" << filename_part << "' from '" << source_path_full << '\'' << endl;

  FILE * file = fopen(filename_full.c_str(), "r");
  if(!file)
    return -1;

  yyscan_t yyscanner;
  if(retelex_init(&yyscanner)) {
    fclose(file);
    return -1;
  }

  int rv = 0;

  reterestart(file, yyscanner);
  reteset_lineno(1, yyscanner);

  // retelex();
  do {
    rv = reteparse(yyscanner, agent, filename_full, source_path_full);
    if(rv)
      break;
  } while (!feof(reteget_in(yyscanner)));

  retelex_destroy(yyscanner);
  fclose(file);
  return rv;
}

int rete_parse_string(Carli::Agent &agent, const string &str, int &line_number) {
  int rv = 0;

  yyscan_t yyscanner;
  if(retelex_init(&yyscanner))
    return -1;

  YY_BUFFER_STATE buf = rete_scan_string(str.c_str(), yyscanner);
  reteset_lineno(line_number, yyscanner);

  // retelex();
  rv = reteparse(yyscanner, agent, "", "");

  line_number = reteget_lineno(yyscanner) + 1;

  rete_delete_buffer(buf, yyscanner);
  retelex_destroy(yyscanner);
  return rv;
}

void rete_set_exit() {
  g_rete_exit = true;
}
#ifdef _MSC_VER
#pragma warning(pop)
#endif
