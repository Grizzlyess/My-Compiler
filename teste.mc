// Questão UNO, da maratona de programação mineira

int n;      
int vez;    
int s;     
string c;  


vez = 1;
s = 1;     
c = "iniciar"; 

write "Digite o numero de jogadores:";
read n;

write "Jogo iniciado! Comandos:";
write "  - Digite uma carta (ex: A, 7, K, Q).";
write "  - Digite '?' para ver o jogador da vez.";
write "  - Digite '#' para terminar o jogo.";


while (c != "#") {
    
    write "Sua jogada:";
    read c;

    if (c == "?") {
        write "O jogador da vez e o numero: ";
        write vez;

    } else {
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
            if (s == 1) {
                // sentido horario 
                if (c == "A" || c == "7") {
                    vez = vez + 2; 
                } else {
                    vez = vez + 1; 
                }
                
                // Se o número do jogador passar do total, ele dá a volta.
                if (vez > n) {
                    vez = vez - n;
                }

            } else { // sentido anti-horario
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

