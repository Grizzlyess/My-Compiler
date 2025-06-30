
int k;
string s;
string word;
int tam;
int finished; 


word = "tamocompetindo";
finished = 0;

write "Digite o valor maximo de erros:";
read k;
write "Digite a string a ser testada:";
read s;

tam = s.size();


if (tam < 14) {
    write "NAO";
    finished = 1;
}


if (finished == 0) {
    if (tam == 14) {
        int erros;
        erros = 0;
        int i;
        i = 0;
        while (i < tam) {
            if (s[i] != word[i]) {
                erros = erros + 1;
            }
            i = i + 1;
        }

        if (erros <= k) {
            write "SIM";
        } else {
            write "NAO";
        }
        finished = 1; 
    }
}


if (finished == 0) {
    int l;      
    int r;      
    int menor;  
    l = 0;
    r = 13;
    menor = 15; 

    // Loop da janela deslizante
    while (r < tam) {
        int j;      
        int erros;  
        int i;      
        j = 0;
        erros = 0;
        i = l;

        
        while (i <= r) {
            if (s[i] != word[j]) {
                erros = erros + 1;
            }
            j = j + 1;
            i = i + 1;
        }

        if (erros < menor) {
            menor = erros;
        }

        // Desliza a janela para a direita
        l = l + 1;
        r = r + 1;
    }

    // Verifica o resultado final
    if (menor <= k) {
        write "SIM";
    } else {
        write "NAO";
    }
}
