//Reconhecer comentários
/*Reconhecer comentários;*/

//1. Declaração de todos os tipos de variáveis
int idade;
float saldo;
string nome;
vector<string> compras;

write "Por favor, digite o seu nome:";
read nome;
write "Digite a sua idade:";
read idade;

print "Ola, ";
write nome;
print "Voce tem ";
print idade;
write " anos.";
<3;
// 2. Operações Aritméticas 


saldo = 100.50;
int bonus;
bonus = idade * 2 + (5^2); 

write "Seu bonus calculado e: ";
write bonus;

saldo = saldo + bonus;
write "Seu novo saldo e: ";
write saldo;

write "Testando o inverter o sinal: 10 para -10";
int negativo;
negativo = 10;
write negativo;
write -negativo;
<3;

// 3. Controle e Lógica

if (idade >= 18 && saldo > 100.00) {
    write "Voce e maior de idade e tem um bom saldo!";
} else {
    write "Voce ou e menor de idade ou o seu saldo nao e superior a 100.00.";
}
<3;
// Testando o operador NOT (!)
if (!(idade < 18)) {
    write "(Usando NOT) Confirmado: Voce nao e menor de idade.";
}
<3;
// 4. Vetores e Loops

compras.push("arroz");
compras.push("feijao");
compras.push("batata");

write "Sua lista de compras inicial:";
write compras;
write "Tamanho da lista:";
write compras.size();

compras.pop(); // Remove "batata"
write "Lista de compras apos o pop():";
write compras;

write "Iterando sobre a lista de compras:";
int i;
i = 0;
while (i < compras.size()) {
    write "Item: ";
    write compras[i];
    i = i + 1;
}

// 5. Strings como Vetores 


print "O seu nome, ";
print nome;
print ", tem ";
print nome.size();
write " caracteres.";

print "O primeiro caractere do seu nome e: ";
write nome[0];
<3;
write "Seu nome soletrado ao contrario:";
i = nome.size() - 1;
while (i >= 0) {
    print nome[i];
    i = i - 1;
}

write "--------------";
write "XOXO, MCBS";