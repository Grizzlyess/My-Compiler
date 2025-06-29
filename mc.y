%code requires {
    #include "ast.h"
}

%{
#include <bits/stdc++.h>
#include "ast.h"

using namespace std;

ASTNode* root;
int yylex();
void yyerror(const char* s) { cerr << "Erro de sintaxe: " << s << endl; }
%}

%union {
    int int_val;
    float float_val;
    std::string* str_val;
    ASTNode* node;
    ASTExpr* expr;
    std::string* id;
    std::vector<ASTExpr*>* expr_list_ptr;
}


// Precedência
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%left OR
%left AND
%left EQ NEQ
%left LT GT LEQ GE // Modificado de LE para LEQ para consistência com o mc.l
%left '+' '-'
%left '*' '/'
%right UMINUS

// Tokens
%token <int_val> INT_CONST
%token <float_val> FLOAT_CONST
%token <str_val> STRING_CONST
%token <id> ID
%token VECTOR

%token INT FLOAT STRING IF ELSE WHILE READ WRITE AND OR EQ NEQ LEQ LE GE LT GT ASSIGN

// Definições de tipo para não-terminais
%type <expr> expr
%type <node> program stmt stmt_list
%type <id> type                          
%type <expr_list_ptr> expr_list     
    

%%

program:
    stmt_list { root = $1; }
;

stmt_list:
    stmt stmt_list { $$ = new ASTSequence($1, $2); }
    | /* vazio */ { $$ = nullptr; }
;

stmt:
    INT ID ';' { $$ = new ASTDeclaration("int", *$2); delete $2; }
  | FLOAT ID ';' { $$ = new ASTDeclaration("float", *$2); delete $2; }
  | STRING ID ';' { $$ = new ASTDeclaration("string", *$2); delete $2; }
  | VECTOR LT type GT ID ';' {
        $$ = new ASTVectorDeclaration(*$3, *$5);
        delete $3; delete $5;
    }
  | VECTOR LT type GT ID ASSIGN expr ';' {
        ASTVectorInit* init = dynamic_cast<ASTVectorInit*>($7);
        if (!init) {
            yyerror("declaracao de vetor so pode ser inicializada com uma lista [...]");
            YYABORT;
        }
        $$ = new ASTVectorDeclaration(*$3, *$5, init);
        delete $3; delete $5;
    }
  | ID ASSIGN expr ';' { $$ = new ASTAssignment(*$1, $3); delete $1; }
  | WRITE expr ';' { $$ = new ASTWrite($2); }
  | READ ID ';' { $$ = new ASTRead(*$2); delete $2; }
  | IF '(' expr ')' stmt %prec LOWER_THAN_ELSE { $$ = new ASTIf($3, $5, nullptr); }
  | IF '(' expr ')' stmt ELSE stmt { $$ = new ASTIf($3, $5, $7); }
  | WHILE '(' expr ')' stmt { $$ = new ASTWhile($3, $5); }
  | '{' stmt_list '}' { $$ = $2; }
;

// Regra para capturar o nome de um tipo (usado em 'vector<tipo>')
type:
    INT { $$ = new std::string("int"); }
  | FLOAT { $$ = new std::string("float"); }
  | STRING { $$ = new std::string("string"); }
;

// Regras para construir uma lista de expressões dentro de [...]
expr_list:
    expr {
        $$ = new std::vector<ASTExpr*>();
        $$->push_back($1);
    }
  | expr_list ',' expr {
        $1->push_back($3);
        $$ = $1;
    }
;

expr:
    INT_CONST { $$ = new ASTInt($1); }
  | FLOAT_CONST { $$ = new ASTFloat($1); }
  | STRING_CONST { $$ = new ASTString(*$1); delete $1; }
  | ID { $$ = new ASTVariable(*$1); delete $1; }
  | '[' expr_list ']' { $$ = new ASTVectorInit($2); }
  | '[' ']'           { $$ = new ASTVectorInit(nullptr); }
  | ID '[' expr ']'   { $$ = new ASTVectorAccess(*$1, $3); delete $1; }
  | expr '+' expr { $$ = new ASTBinary("+", $1, $3); }
  | expr '-' expr { $$ = new ASTBinary("-", $1, $3); }
  | expr '*' expr { $$ = new ASTBinary("*", $1, $3); }
  | expr '/' expr { $$ = new ASTBinary("/", $1, $3); }
  | expr EQ expr { $$ = new ASTBinary("==", $1, $3); }
  | expr NEQ expr { $$ = new ASTBinary("!=", $1, $3); }
  | expr LT expr { $$ = new ASTBinary("<", $1, $3); }
  | expr GT expr { $$ = new ASTBinary(">", $1, $3); }
  | expr LEQ expr { $$ = new ASTBinary("<=", $1, $3); } // Corrigido de LE para LEQ
  | expr GE expr { $$ = new ASTBinary(">=", $1, $3); }
  | expr AND expr { $$ = new ASTBinary("&&", $1, $3); }
  | expr OR expr { $$ = new ASTBinary("||", $1, $3); }
  | '-' expr %prec UMINUS { $$ = new ASTUnary("-", $2); }
  | '(' expr ')' { $$ = $2; }
;

%%