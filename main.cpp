#include <iostream>
#include "ast.h"

extern FILE* yyin;     
extern int yyparse();
extern ASTNode* root;

std::map<std::string, std::string> variables;
std::map<std::string, std::vector<std::string>> vector_variables;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " arquivo_entrada\n";
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        std::cerr << "Erro ao abrir arquivo " << argv[1] << "\n";
        return 1;
    }

    yyin = file;  // Direciona Flex para ler do arquivo

    if (yyparse() == 0 && root != nullptr) {
        root->execute();
        delete root;
    } else {
        std::cerr << "Erro na análise!\n";
    }

    fclose(file);
    return 0;
}
