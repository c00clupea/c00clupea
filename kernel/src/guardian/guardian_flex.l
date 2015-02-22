%option noyywrap
%option always-interactive
%x STRING COMMENT

%{
#include "guardian.h"

#ifdef PRINT_FLEX
#define act(TOKEN) work_token(#TOKEN, yytext)
#define actc(TOKEN) work_token(TOKEN, yytext)



void work_token(char *tok, char *lex)
{
	if(*lex){
		fprintf(yyout,"%s:%s ",tok,lex);
	} else {
		fprintf(yyout,"%s:NaN ",tok);
	}
}
#else
#include "guardian_bison.h"
#define act(TOKEN) return TOKEN
#define actc(TOKEN) return TOKEN[0]
#endif

%}


ID [A-Za-z_][A-Za-z0-9_]*
NUM [0-9]+

%%
\n			++yylineno;/*just a linefeed*/
[ \t]+	/*simple whitespace, we do nothing*/
\"			yymore(); BEGIN(STRING);
<STRING>[^\"\n\\]*      yymore();
<STRING>\\              yymore();
<STRING>\\\"            yymore();
<STRING>\n  {
  BEGIN(INITIAL);
}
<STRING><<EOF>>          exit(-1);
<STRING>\" {         
  BEGIN(INITIAL);
yylval.string = malloc(strlen(yytext));
strncpy(yylval.string, yytext, strlen(yytext));
  act(STR);
}

"/*"                     BEGIN(COMMENT);  
<COMMENT>[^*\n]*
<COMMENT>[^*\n]*\n       ++yylineno;
<COMMENT>"*"+[^*/\n]*
<COMMENT>"*"+[^*/\n]*\n  ++yylineno;
<COMMENT>"*"+"/" {
		 BEGIN(INITIAL);
		 act(COMMENT);
		 }



[+\-*/=^|{}\[\]()<>:]	 actc(yytext);
"++" 			 act(PP);
"--" 			 act(MM);
">=" 			 act(GEQ);
"<=" 			 act(LEQ);
"==" 			 act(EQ);
"!="			 act(NEQ);
"||"			 act(OR);
"&&"			 act(AND);
"!"			 act(NOT);
">>"			 act(SR);
"<<"			 act(SL);

"if"			 act(IF);
"else"			 act(ELSE);
"let"			 act(LET);
"be"			 act(BE);			 
"..."			 act(STEP);
";"			 act(FIN);
"id"			 act(RETID);
"num"			 act(RETNUM);
"string"		 act(RETSTRING);
"exit"			 act(RETEXIT);
"void"			 act(RETVOID);

. 			actc(yytext);


{ID} {
yylval.string = malloc(strlen(yytext));
				strncpy(yylval.string, yytext, strlen(yytext));
act(ID);
}

{NUM} {
      yylval.integer = atoi(yytext);
      act(NUM);
}
%%
