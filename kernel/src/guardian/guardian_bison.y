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
%token RETID
%token RETNUM
%token RETSTRING
%token RETEXIT
%token RETVOID




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

definition:	LET returnal ID BE ID FIN {		
		writefmt("def(id): %s<-%s\n",$3,$5);
}
		|LET returnal ID BE NUM FIN {
		writefmt("def(int): %s<-%d\n",$3,$5);
}
		|LET returnal ID BE STR FIN {
		writefmt("def(string): %s<-%s\n",$3,$5);
}
		|LET returnal ID param BE '{' innerdef '}' FIN {
		writefmt("(func)%s",$3);
}

returnal :	'('RETID')'	{
	 	write("return ID\n");
}
		|'('RETSTRING')'	{
	 	write("return String\n");
}		|'('RETNUM')'	{
	 	write("return NUM\n");
}
		|'('RETEXIT')'	{
	 	write("return EXIT\n");
}

innerdef :	'\n'
	 	|ID	{writefmt("idef -> %s\n",$1);}

param :		emptyparam
      		|singleparam
      		|singleparam singleparam

emptyparam :	'('')'		{write("param void\n");}		

singleparam :	'('RETID')'ID		{writefmt("param id -> %s\n",$4);}
	    	|'('RETNUM')'ID		{writefmt("param num -> %s\n",$4);}
		|'('RETSTRING')'ID	{writefmt("param string -> %s\n",$4);}

funccall :	ID funcparam

funcparam : 	'('fparam')'
	  	|'('')'
		|'('fparam sparam')'
		
fparam :		ID
		|NUM
		|STR

sparam	:	','fparam
		|sparam sparam
;
