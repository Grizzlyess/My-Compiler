Compilador para a Linguagem MC
1. Descrição do Projeto
Este projeto consiste num interpretador para uma linguagem de programação simples, designada "MC" (com a extensão de ficheiro .mc). O interpretador foi desenvolvido utilizando as ferramentas Flex para a análise léxica e Bison para a análise sintática.

O código-fonte na linguagem MC é analisado, traduzido para uma Árvore de Sintaxe Abstrata (AST) em memória, e depois executado diretamente.

2. Funcionalidades da Linguagem
A linguagem MC suporta um conjunto robusto de funcionalidades, tornando-a capaz de resolver problemas de programação complexos.

Tipos de Dados:
int: Números inteiros.

float: Números de ponto flutuante (são sempre formatados com duas casas decimais em operações aritméticas).

string: Texto, que é tratado como um vetor de caracteres, permitindo acesso a caracteres individuais.

vector<tipo>: Vetores de int, float ou string.

Operações:
Aritméticas: Adição (+), Subtração (-), Multiplicação (*), Divisão (/) e Potência (^).

Lógicas: E (&&), Ou (||).

Relacionais: Igual a (==), Diferente de (!=), Menor que (<), Menor ou igual a (<=), Maior que (>), Maior ou igual a (>=).

Estruturas de Controlo:
Condicional: if (...) { ... } else { ... }

Repetição: while (...) { ... }

Entrada e Saída:
read <variável>;: Lê um valor do teclado e armazena-o na variável.

write <expressão>;: Escreve o valor de uma expressão, variável ou texto no ecrã.

Manipulação de Vetores e Strings:
Como as strings são tratadas como vetores, as seguintes operações funcionam para ambos:

Acesso a Elementos: minha_variavel[indice]

Tamanho: minha_variavel.size()

Manipulação: minha_variavel.push(...) e minha_variavel.pop()

Comentários:
Comentários de linha única são suportados com //.

3. Como Compilar e Executar
O projeto inclui um Makefile que automatiza todo o processo de compilação.

Pré-requisitos:
g++ (compilador C++)

flex

bison

Passos:
Compilar o Interpretador:
Abra um terminal na pasta do projeto e execute o comando:

make

Isto irá gerar um ficheiro executável chamado mc.

Executar um Programa:
Para executar um ficheiro de código escrito na linguagem MC (ex: problema.mc), use o seguinte comando:

./mc nome_do_ficheiro.mc

Limpar Ficheiros Gerados:
Para apagar o executável e todos os ficheiros intermédios gerados pelo processo de compilação, execute:

make clean

4. Estrutura dos Ficheiros
main.cpp: O ponto de entrada do programa. Orquestra o processo de análise e execução.

parser.y: Contém a gramática da linguagem MC para o Bison. É responsável pela análise sintática e pela construção da AST.

mc.l: Contém as regras de reconhecimento de tokens para o Flex. É responsável pela análise léxica.

ast.h: Define todas as classes que compõem a Árvore de Sintaxe Abstrata (AST). É o coração da estrutura de dados do interpretador.

Makefile: Automatiza a compilação do projeto.

Ficheiros .mc: Ficheiros de exemplo com código escrito na linguagem MC para testar as funcionalidades do interpretador.
