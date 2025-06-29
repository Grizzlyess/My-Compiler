// Jogo de Cartas - Exemplo para a Linguagem MC
// Este código simula um jogo de cartas simples onde o turno dos jogadores
// muda de acordo com a carta jogada.

// --- Declaração de Variáveis ---
int n;      // Armazena o número total de jogadores.
int vez;    // Indica qual jogador está na vez (começa com 1).
int s;      // Controla o sentido do jogo: 1 para horário, 0 para anti-horário.
string c;   // Armazena a carta ou comando lido do teclado.

// --- Inicialização do Jogo ---
vez = 1;
s = 1;      // O jogo começa no sentido horário.
c = "init"; // Valor inicial apenas para garantir que o loop comece.

write "Bem-vindo ao Jogo de Cartas!";
write "Digite o numero de jogadores:";
read n;

write "==================================================";
write "Jogo iniciado! Comandos:";
write "  - Digite uma carta (ex: A, 7, K, Q).";
write "  - Digite '?' para ver o jogador da vez.";
write "  - Digite '#' para terminar o jogo.";
write "==================================================";


// --- Loop Principal do Jogo ---
while (c != "#") {
    
    write "Sua jogada:";
    read c;

    if (c == "?") {
        // Se o comando for '?', apenas mostra o jogador da vez.
        write "O jogador da vez e o numero: ";
        write vez;

    } else {
        // Se for qualquer outra carta (e não o comando de saída '#'), processa a jogada.
        if (c != "#") {
            
            if (c == "Q") {
                // A carta 'Q' inverte o sentido do jogo.
                if (s == 1) {
                    s = 0; // Muda para anti-horário.
                    write "O sentido foi alterado para ANTI-HORARIO!";
                } else {
                    s = 1; // Muda para horário.
                    write "O sentido foi alterado para HORARIO!";
                }
            }

            // Verifica o sentido atual do jogo para calcular o próximo jogador.
            if (s == 1) {
                // --- Lógica para o sentido HORÁRIO ---
                if (c == "A" || c == "7") {
                    vez = vez + 2; // Pula um jogador.
                } else {
                    vez = vez + 1; // Passa para o próximo.
                }
                
                // Se o número do jogador passar do total, ele dá a volta.
                if (vez > n) {
                    vez = vez - n;
                }

            } else {
                // --- Lógica para o sentido ANTI-HORÁRIO ---
                if (c == "A" || c == "7") {
                    vez = vez - 2; // Volta um jogador.
                } else {
                    vez = vez - 1; // Passa para o anterior.
                }

                // Se o número do jogador ficar menor que 1, ele dá a volta.
                if (vez < 1) {
                    vez = vez + n;
                }
            }
        }
    }
}

write "Fim de jogo! Obrigado por jogar.";

