#include <bits/stdc++.h>
#include "ast.h"

// ✅ Aqui você DEFINE a variável global
std::map<std::string, std::string> variables;

extern int yyparse();
extern ASTNode* root;  // AST gerada pelo parser

int main() {
    if (yyparse() == 0 && root != nullptr) {
        root->execute();  // Executa o programa gerado
        delete root;
    } else {
        std::cerr << "Erro na análise!" << std::endl;
    }
    return 0;
}
