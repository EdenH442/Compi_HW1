%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"
#include <string.h>
%}

/* Definitions Section */
%option yylineno
%option noyywrap
digit   		([0-9])
letter  		([a-zA-Z])
no_zero_digit 	([1-9])

whitespace		([\t\n\x20\r])
sc				([;])
comma			(,)
lparen			(\() 
rparen			(\))
lbrace			(\{)
rbrace			(\})
assign			(=)
relop			([<>]=?\==|!=)
binop			([\+\-\*\/])
comment			((\/\/)[^\x0A\x0D\x09]*)

%x STRING_STATE
%x ESCAPE_SEQ
%x STRING_HEX

%%

{whitespace}				; /*the empty command*/

void							return VOID;
int								return INT;
byte							return BYTE;
b								return B;
bool							return BOOL;
and								return AND;
or								return OR;
not								return NOT;
true							return TRUE;
false							return FALSE;
return							return RETURN;
if								return IF;
else							return ELSE;
while							return WHILE;
break							return BREAK;
continue						return CONTINUE;
{sc}							return SC;
{comma}							return COMMA;
{lparen}						return LPAREN;
{rparen}						return RPAREN;
{lbrace}						return LBRACE;
{rbrace}						return RBRACE;
{assign}						return ASSIGN;
{relop}							return RELOP;
{binop}							return BINOP;
{comment}						return COMMENT;
{letter}+({letter}|{digit})*	return ID;
({no_zero_digit}+{digit}*)|0	return NUM;

\"										BEGIN(STRING_STATE);
<STRING_STATE>[\n\r]					{BEGIN(INITIAL); return UNCLOSED_STRING;}
<STRING_STATE><<EOF>>					{BEGIN(INITIAL); return UNCLOSED_STRING;}

<STRING_STATE>\\						BEGIN(ESCAPE_SEQ);
<ESCAPE_SEQ>(\x)						BEGIN(STRING_HEX); 
<ESCAPE_SEQ>(\\|\"|\n|\r|\t|\0)			BEGIN(STRING_STATE); 

<ESCAPE_SEQ>.							return UNDEF_ESC_SEQ;

<STRING_HEX>([0-7][0-9a-fA-F])			{BEGIN(STRING_STATE); return HEX_SEQ_STRING;}
<STRING_HEX>(.\")						return UNDEF_ESC_SEQ;
<STRING_HEX>.							return UNDEF_ESC_SEQ;

<STRING_STATE>([^\\\"\n\r]|\\.)*\"		{ BEGIN(INITIAL); return STRING;}
<STRING_STATE,ESCAPE_SEQ>.				return ERROR;


.								return INVALID_INPUT;


%%
/* C Code Section */

