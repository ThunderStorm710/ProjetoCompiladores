/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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

#line 162 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
