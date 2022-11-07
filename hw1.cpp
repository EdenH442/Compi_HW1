#include <stdio.h>
#include "tokens.hpp"

void showToken(const char* tokenName)
{
    printf("%d %s %s\n", yylineno, tokenName, yytext);
}

void showComment()
{
    printf("%d %s %s\n", yylineno, "COMMENT", "//");
};

int main()
{
	int token;
	while ((token = yylex()))
    {
	  switch(token)
      {
          case VOID:
              showToken("VOID");
              break;
          case INT:
              showToken("INT");
              break;
          case BYTE:
              showToken("BYTE");
              break;
          case B:
              showToken("B");
              break;
          case BOOL:
              showToken("BOOL");
              break;
          case AND:
              showToken("AND");
              break;
          case OR:
              showToken("OR");
              break;
          case NOT:
              showToken("NOT");
              break;
          case TRUE:
              showToken("TRUE");
              break;
          case FALSE:
              showToken("FALSE");
              break;
          case RETURN:
              showToken("RETURN");
              break;
          case IF:
              showToken("IF");
              break;
          case ELSE:
              showToken("ELSE");
              break;
          case WHILE:
              showToken("WHILE");
              break;
          case BREAK:
              showToken("BREAK");
              break;
          case CONTINUE:
              showToken("CONTINUE");
              break;
          case SC:
              showToken("SC");
              break;
          case COMMA:
              showToken("COMMA");
              break;
          case LPAREN:
              showToken("LPAREN");
              break;
          case RPAREN:
              showToken("RPAREN");
              break;
          case LBRACE:
              showToken("LBRACE");
              break;
          case RBRACE:
              showToken("RBRACE");
              break;
          case ASSIGN:
              showToken("ASSIGN");
              break;
          case RELOP:
              showToken("RELOP");
              break;
          case BINOP:
              showToken("BINOP");
              break;
          case COMMENT:
              showComment();
              break;
          case ID:
              showToken("ID");
              break;
          case NUM:
              showToken("NUM");
              break;
          case INVALID_INPUT:
              printf("Error %c\n", yytext[0]);
              exit(0);
              
          default:
              printf("Currently Not Supported");
              break;
      }
	}
	return 0;
}
