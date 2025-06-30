# MC ++
>A seguir está o passo a passo para conseguir utilizar a liguagem MC++. Este projeto foi apresentado a disciplina de Compiladores, ministrada pelo professor Diego Rocha, como requisito parcial para obtenção de nota. A linguagem está completa, feita a construção da linguagem léxica, sintática e semântica.

O interpretador foi desenvolvido utilizando as ferramentas Flex para a análise léxica e Bison para a análise sintática. O código-fonte  é analisado, traduzido para uma Árvore de Sintaxe Abstrata (AST).

![](logo.png)

## Tipos de Dados:

```sh
int: Números inteiros
```
```sh
float: Números de ponto flutuante
(são sempre formatados com duas casas decimais em operações aritméticas)
```
```sh
string: Texto, que é tratado como um vetor de caracteres,
permitindo acesso a caracteres individuais
```
```sh
vector<tipo>: Vetores de int, float ou string
```

## Operações:

```sh
Aritméticas: Adição (+), Subtração (-), Multiplicação (*),
Divisão (/) e Potência (^)
```
```sh
Lógicas: E (&&), Ou (||).
```
```sh
Relacionais: Igual a (==), Diferente de (!=), Menor que (<),
Menor ou igual a (<=), Maior que (>), Maior ou igual a (>=).
```
```sh
Comentários de linha: (//)
```
```sh
Comentários de bloco: (/* ... */)
```

## Estruturas de Controle:

```sh
Condicional: if (...) { ... } else { ... }
```
```sh
Repetição: while (...) { ... }
```

## Entrada e Saída:

```sh
read <variável>;: Lê um valor do teclado e armazena-o na variável.
```
```sh
write <expressão>;: Escreve o valor de uma expressão, variável ou texto na tela.
```

## Manipular vetores e strings:

```sh
Acesso a Elementos: minha_variavel[i]
```
```sh
Tamanho: minha_variavel.size()
```
```sh
Manipulação: minha_variavel.push(...) e minha_variavel.pop()
```


