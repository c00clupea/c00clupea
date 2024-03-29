/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2009, 2010 Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUM = 258,
     ID = 259,
     STR = 260,
     PP = 261,
     MM = 262,
     GEQ = 263,
     LEQ = 264,
     EQ = 265,
     NEQ = 266,
     OR = 267,
     AND = 268,
     NOT = 269,
     SR = 270,
     SL = 271,
     IF = 272,
     ELSE = 273,
     STEP = 274,
     LET = 275,
     BE = 276,
     FIN = 277,
     RETID = 278,
     RETNUM = 279,
     RETSTRING = 280,
     RETEXIT = 281,
     RETVOID = 282
   };
#endif
/* Tokens.  */
#define NUM 258
#define ID 259
#define STR 260
#define PP 261
#define MM 262
#define GEQ 263
#define LEQ 264
#define EQ 265
#define NEQ 266
#define OR 267
#define AND 268
#define NOT 269
#define SR 270
#define SL 271
#define IF 272
#define ELSE 273
#define STEP 274
#define LET 275
#define BE 276
#define FIN 277
#define RETID 278
#define RETNUM 279
#define RETSTRING 280
#define RETEXIT 281
#define RETVOID 282




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1685 of yacc.c  */
#line 21 "guardian_bison.y"

char *string;
int integer;



/* Line 1685 of yacc.c  */
#line 112 "guardian_bison.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


