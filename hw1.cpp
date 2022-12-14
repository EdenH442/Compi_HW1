#include <stdio.h>
#include "tokens.hpp"
#include <string>
#include <iostream>

using std::string;

//CHECK CHECK
void showToken(const char* tokenName)
{
    printf("%d %s %s\n", yylineno, tokenName, yytext);
}

void showComment()
{
    printf("%d %s %s\n", yylineno, "COMMENT", "//");
}

void printError()
{
    printf("Error %s\n", yytext);
    exit(0);
}

void Esc_Seq_Error()
{
    printf("Error undefined escape sequence %s\n", yytext);
}


int HexHandler(const std::string& str)
{
    bool not_valid = false;
    std::string err;
    for(int i = 0; i < str.length(); ++i)
    {
        if(!(std::isalnum(str[i]) || std::isalpha(str[i])))
        {
            not_valid= true;
            //hex is shorter than 2 characters
            if(str[i]=='\"')
            {
                printf("Error undefined escape sequence %s\n", ("x"+err).c_str());
                exit(0);
            }
        }
        else
        {
            err+=str[i];
        }
    }
    if(not_valid)
    {
        printf("Error undefined escape sequence %s\n", ("x"+str).c_str());
        exit(0);
    }
    int number;
    try
    {
        number = std::stoi(str, nullptr, 16);
    }
    catch(const std::invalid_argument& e)
    {
        printf("Error undefined escape sequence %s\n", ("x"+str).c_str());
        exit(0);
    }
    if (number>=0x00 && number<=0x7f)
    {
        return number;
    }
    else{
        printf("Error undefined escape sequence %s\n", ("x"+str).c_str());
        exit(0);
    }
}

std::string StringEscSeq(char escape_seq)
{
    switch (escape_seq)
    {
        case 'n':
            return "\n";
        case 'r':
            return "\r";
        case 't':
            return  "\t";
        case '\\':
            return  "\\";
        case '\"':
            return "\"";
        default:
            printf("Error undefined escape sequence %c\n", escape_seq);
            exit(0);
    }
}

void StringHandler()
{
    string res_str;
    for(int i=0 ; i < string(yytext).length() ; i++)
    {
        if(yytext[i]=='\"')
        {
            continue;
        }
        else if (yytext[i] == '\0')
        {
            std::cout << yylineno << " " << "STRING " << res_str << std::endl;
            return;
        }
        else if (yytext[i] != '\\')
        {
            res_str += yytext[i];
            continue;
        }
        else
        {
            char esc_seq = yytext[i+1];
            if(esc_seq =='x')
            {
                string yytext_str = (string)yytext;
                int hex_num =  HexHandler(yytext_str.substr(i+2, 2));
                if(hex_num == 0x0)
                {
                    std::cout << yylineno << " " << "STRING " << res_str << std::endl;
                    return;
                }
                res_str += (char)hex_num;
                i += 3;
            }
            else if (esc_seq == '0')
            {
                std::cout << yylineno << " " << "STRING " << res_str << std::endl;
                return;
            }
            else
            {
                res_str += StringEscSeq(esc_seq);
                i++;
            }

        }
    }
    std::cout << yylineno << " " << "STRING " << res_str << std::endl;
}



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
            case STRING:
                StringHandler();
                break;
            case UNCLOSED_STRING:
                printf("Error unclosed string\n");
                exit(0);
            case UNDEF_ESC_SEQ:
                Esc_Seq_Error();
                exit(0);
//            case HEX_SEQ_STRING:
//                break;
            case ERROR:
                printError();
                break;
            default:
                printf("Currently Not Supported");
                break;
        }
    }
    return 0;
}