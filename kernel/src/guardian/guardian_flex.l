%{
#include "guardian.h"


#define act(TOKEN) work_token(#TOKEN, yytext)
#define actc(TOKEN) work_token(TOKEN, yytext)

void work_token(char *tok, char *lex)
{
	if(*lex){
		fprintf(yyout,"%s:%s",tok,lex);
	} else {
		fprintf(yyout,"%s:NaN",tok);
	}
}

%}

%option noyywrap
%option always-interactive
%x STRING

%%
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
  act(STR);
}

"/*"                     BEGIN(COMMENT);  
<COMMENT>[^*\n]*
<COMMENT>[^*\n]*\n       
<COMMENT>"*"+[^*/\n]*
<COMMENT>"*"+[^*/\n]*\n  
<COMMENT>"*"+"/"{BEGIN(INITIAL);act(COMMENT);}



[ \t]+	/*simple whitespace, we do nothing*/
"++" 	act(PP);
"--" 	act(MM);
">=" 	act(GEQ);
"<=" 	act(LEQ);
"==" 	act(EQ);
"!="	act(NEQ);
"||"	act(OR);
"&&"	act(AND);
"!"	act(NOT);
">>"	act(SR);
"<<"	act(SL);
"{"	act(LBBRACE);
"}"	act(RBBRACE);
"["	act(LNBRACE);
"]"	act(RNBRACE);
"("	act(LBRACE);
")"	act(RBRACE);

[A-Za-z_][A-Za-z0-9_]*	act(ID);
[0-9]+			act(NUM);


%%
