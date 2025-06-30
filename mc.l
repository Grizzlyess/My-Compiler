%{
#include <bits/stdc++.h>
#include "mc.tab.h" 
using namespace std;

extern YYSTYPE yylval; 
%}

digit         [0-9]
letter        [a-zA-Z_]
id            {letter}({letter}|{digit})*
int_const     {digit}+
float_const   {digit}+"."{digit}+
string_const  \"([^\\\"]|\\.)*\"

%%

"//".* {}

"int"         { return INT; }
"float"       { return FLOAT; }
"string"      { return STRING; }
"vector"      { return VECTOR; }
"if"          { return IF; }
"else"        { return ELSE; }
"while"       { return WHILE; }
"read"        { return READ; }
"write"       { return WRITE; }
"push"        { return PUSH; }
"pop"         { return POP; }
"size"        { return SIZE; }

"&&"          { return AND; } 
"||"          { return OR; }  
"=="          { return EQ; }
"!="          { return NEQ; }
"<="          { return LEQ; } 
">="          { return GE; }  
"<"           { return LT; }
">"           { return GT; }
"="           { return ASSIGN; }

{float_const} { yylval.float_val = atof(yytext); return FLOAT_CONST; }
{int_const}   { yylval.int_val = atoi(yytext); return INT_CONST; }
{string_const} {
                std::string raw(yytext);
                yylval.str_val = new std::string(raw.substr(1, raw.length() - 2));
                return STRING_CONST;
              }
{id}          { yylval.id = new string(yytext); return ID; }

"{"           { return '{'; }
"}"           { return '}'; }
"("           { return '('; }
")"           { return ')'; }
"["           { return '['; } 
"]"           { return ']'; } 
";"           { return ';'; }
","           { return ','; } 
"."           { return '.'; }
"+"           { return '+'; }
"-"           { return '-'; }
"*"           { return '*'; }
"/"           { return '/'; }
"^"           { return POW; } 

[ \t\r\n]+    {}

.             { printf("Caractere nao reconhecido: %s\n", yytext); return '?'; }

%%

int yywrap() {
    return 1;
}
