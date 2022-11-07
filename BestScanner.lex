%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"

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
lparen			(\() /*Escape sequence to write the "(" regular exp.*/
rparen			(\))
lbrace			(\{)
rbrace			(\})
assign			(=)
relop			([<>]=?\==|!=)
binop			([\+\-\*\/])
comment			((\/\/)[^\x0A\x0D\x09]*)


%%
/* Rules Section */

/* Need to ignore Whitespaces:*/
{whitespace}				; /*the empty command*/

/*Reserved Words first:*/
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


%%
/* C Code Section */

