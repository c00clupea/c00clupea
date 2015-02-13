%{
#include <stdio.h>
#define YYERROR_VERBOSE
#define write(msg) printf(msg)

#define writefmt(msg,...) printf(msg,__VA_ARGS__)

void yyerror(char *s) {
  fprintf(stderr, "%s\n", s);
}
int yylex(void);

int sym[26];




%}

//%define api.value.type union
%union {
char *string;
int integer;
}

%token <integer> NUM 'n'
%token <string> ID STR


%token '+'
%token '-'
%token '*'
%token '/'
%token '='
%token '^'
%token '{'
%token '}'
%token '['
%token ']'
%token '('
%token ')'
%token '|'
%token '<'
%token '>'
%token ':'
%token PP
%token MM
%token GEQ
%token LEQ
%token EQ
%token NEQ
%token OR
%token AND
%token NOT
%token SR
%token SL
%token IF
%token ELSE
%token STEP
%token LET
%token BE
%token FIN




%right '='
%left OR
%left AND
%left EQ NEQ
%left GEQ LEQ '<' '>'
%left '+' '-' '*' '/'
%right PP MM NOT

 


%%

program: /*can be empty*/
	 | program line
;

line:	'\n'	
	| definition			
;

definition:	LET ID BE ID FIN {		
		writefmt("def(id): %s<-%s\n",$2,$4);
}
		|LET ID BE NUM FIN {
		writefmt("def(int): %s<-%d\n",$2,$4);
}
		|LET ID BE STR FIN {
		writefmt("def(string): %s<-%s\n",$2,$4);
}
;
