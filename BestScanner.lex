%{

/* Declarations section */
#include <stdio.h>
#include "tokens.hpp"

%}

%option yylineno
%option noyywrap
digit   		([0-9])
letter  		([a-zA-Z])
whitespace		([\t\n ])

%%
/* Rules Section */



%%
/* C Code Section */

