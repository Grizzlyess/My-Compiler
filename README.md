# MC ++
>A seguir está o passo a passo para conseguir utilizar a liguagem MC++. Este projeto foi apresentado a disciplina de Compiladores, ministrada pelo professor Diego Rocha, como requisito parcial para obtenção de nota. A linguagem está completa, feita a construção da linguagem léxica, sintática e semântica.

O interpretador foi desenvolvido utilizando as ferramentas Flex para a análise léxica e Bison para a análise sintática. O código-fonte  é analisado, traduzido para uma Árvore de Sintaxe Abstrata (AST).

![](logo.png)

## Tipos de Dados:

```sh
npm int: Números inteiros
```
```sh
npm float: Números de ponto flutuante (são sempre formatados com duas casas decimais em operações aritméticas)
```
```sh
npm string: Texto, que é tratado como um vetor de caracteres, permitindo acesso a caracteres individuais
```
```sh
npm vector<tipo>: Vetores de int, float ou string
```

## Operações:

```sh
npm Aritméticas: Adição (+), Subtração (-), Multiplicação (*), Divisão (/) e Potência (^)
```
```sh
npm Lógicas: E (&&), Ou (||).
```
```sh
npm Relacionais: Igual a (==), Diferente de (!=), Menor que (<), Menor ou igual a (<=), Maior que (>), Maior ou igual a (>=).
```
```sh
npm Comentários de linha: (//)
```

## Estruturas de Controle:

```sh
npm Condicional: if (...) { ... } else { ... }
```
```sh
npm Repetição: while (...) { ... }
```

## Entrada e Saída:

```sh
npm read <variável>;: Lê um valor do teclado e armazena-o na variável.
```
```sh
npm write <expressão>;: Escreve o valor de uma expressão, variável ou texto na tela.
```

## Manipular vetores e strings:

```sh
npm Acesso a Elementos: minha_variavel[i]
```
```sh
npm Tamanho: minha_variavel.size()
```
```sh
npm Manipulação: minha_variavel.push(...) e minha_variavel.pop()
```


