#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Verifica se o dispositivo é windows ou outro para poder limpar o terminal e fazer palsas
#ifdef _WIN32
#include <windows.h>
#define CLEAR_SCREEN "cls"
#define PAUSE(ms) Sleep(ms)
#else
#include <unistd.h>
#define CLEAR_SCREEN "clear"
#define PAUSE(ms) usleep(ms * 1000)
#endif

//Cores utilizadas
#define RESET_COLOR "\033[0m" //resetar cor
#define VERMELHO "\033[41m" //vermelho
#define AMARELO "\033[43m" //amarelo
#define AZUL "\033[44m" //azul
#define VERDE "\033[42;2m" //verde
#define ROSA "\033[48;5;206;2m" // Rosa
#define LARANJA "\033[48;5;202m" // Laranja
#define CIANO "\033[48;5;87m" //ciano
#define ROXO "\033[48;5;129m" // Roxo
#define PRETO "\033[40m" //preto

//Funcoes de menu
void introducao();
void exibirRegras();
void menuopcoes();
void opcoesdejogo();

//Funcoes do jogo
void gabaritoColoridas();
void gabaritoDaltonico();
void mostrarcartavirada();
void mostrarcartaviradaDalto();
void contagem();
void inicializarMatriz();

int main(int argc, char *argv[]){

    char opcao, modo;
    int pares[4][4], numeros[8] = {0};

    srand(time(NULL));
    
    while (1){
        
        system(CLEAR_SCREEN);
        introducao();
        PAUSE(500);
        
        if (argc < 2) {
        printf("Bem-vindo(a)!\n"); // Mensagem de boas-vindas genérica
        } else {
            printf("Bem-vindo(a) %s!\n", argv[1]); // Exibe o nome do usuário fornecido como argumento
        }
        
        menuopcoes();
        scanf(" %c", &opcao);
        
        switch (opcao) {
            case '1':
                while (1){
                    system(CLEAR_SCREEN);
                    opcoesdejogo();
                    scanf(" %c", &modo);
                    if (modo == '1' || modo == '2'){
                        break;
                    }
                    printf("Opcao invalida\n");
                    PAUSE(500);
                }
                for (int repetir = 0; repetir < 5; repetir++){
                    inicializarMatriz(pares);
                    //Sorteia numeros de 0 a 7 para uma matriz 4 x 4 e garante que haja dois de cada numero 
                    for (int num = 0; num < 8; num++) {
                        for (int count = 0; count < 2; count++) {
                            int l, c;
                            do {
                                l = rand() % 4;
                                c = rand() % 4;
                            } while (pares[l][c] != -1);

                            pares[l][c] = num;
                            numeros[num]++;
                        }
                    }
                    
                    system(CLEAR_SCREEN);

                    if (modo == '1'){
                        gabaritoColoridas(pares);
                    }
                    else if (modo == '2'){
                        gabaritoDaltonico(pares);
                    }
                    PAUSE(500);
                }
                contagem();

                system(CLEAR_SCREEN);

                int viradas[4][4] = {0}; // Matriz para controlar cartas viradas (0 para oculta, 1 para mostrada)
                int linha[2], coluna[2]; // Armazenar as posições das cartas selecionadas

                int acertos = 0; // Contador de acertos
                while (acertos < 8) {
                    system(CLEAR_SCREEN);
                    
                    // Mostrar estado atual das cartas
                    if (modo == '1'){
                        mostrarcartavirada(pares, viradas);
                    }
                    else if (modo == '2'){
                        mostrarcartaviradaDalto(pares, viradas);
                    }

                    printf("Escolha uma linha e uma coluna: ");
                    scanf("%d %d", &linha[0], &coluna[0]);

                    // Validar entrada do usuário para a primeira posição
                    while (linha[0] < 1 || linha[0] > 4 || coluna[0] < 1 || coluna[0] > 4 || viradas[linha[0] - 1][coluna[0] - 1] == 1) {
                        printf("Posicao invalida ou carta ja virada. Tente novamente.\n");
                        PAUSE(1000);

                        system(CLEAR_SCREEN);
                        if (modo == '1'){
                            mostrarcartavirada(pares, viradas);
                        }
                        else if (modo == '2'){
                            mostrarcartaviradaDalto(pares, viradas);
                        }

                        printf("Escolha uma linha e uma coluna: ");
                        scanf("%d %d", &linha[0], &coluna[0]);
                    }

                    viradas[linha[0] - 1][coluna[0] - 1] = 1; // Mostrar primeira carta selecionada

                    system(CLEAR_SCREEN);
                    if (modo == '1'){
                        mostrarcartavirada(pares, viradas);
                    }
                    else if (modo == '2'){
                        mostrarcartaviradaDalto(pares, viradas);
                    }

                    printf("Agora escolha outra posicao: ");
                    scanf("%d %d", &linha[1], &coluna[1]);

                    // Verificar se a segunda posição é inválida
                    while (linha[1] < 1 || linha[1] > 4 || coluna[1] < 1 || coluna[1] > 4 || viradas[linha[1] - 1][coluna[1] - 1] == 1) {
                        printf("Posicao invalida ou carta ja virada. Tente novamente.\n");
                        PAUSE(1000);

                        system(CLEAR_SCREEN);
                        if (modo == '1'){
                            mostrarcartavirada(pares, viradas);
                        }
                        else if (modo == '2'){
                            mostrarcartaviradaDalto(pares, viradas);
                        }

                        printf("Escolha outra posicao: ");
                        scanf("%d %d", &linha[1], &coluna[1]);
                    }

                    viradas[linha[1] - 1][coluna[1] - 1] = 1; // Mostrar segunda carta selecionada

                    system(CLEAR_SCREEN);
                    if (modo == '1'){
                        mostrarcartavirada(pares, viradas);
                    }
                    else if (modo == '2'){
                        mostrarcartaviradaDalto(pares, viradas);
                    }

                    // Verificar se as cartas são iguais
                    if (pares[linha[0] - 1][coluna[0] - 1] == pares[linha[1] - 1][coluna[1] - 1]) {
                        printf("Par correspondente encontrado!\n");
                        PAUSE(1000);
                        acertos++;
                    } else {
                        // Se não forem iguais, esconder as cartas após um breve intervalo
                        PAUSE(1000); // Aguarda 1 segundo (1.000.000 microssegundos)
                        viradas[linha[0] - 1][coluna[0] - 1] = 0;
                        viradas[linha[1] - 1][coluna[1] - 1] = 0;
                    }
                }

                printf("Parabens! Voce encontrou todos os pares.\n");
                return 0;
                
                
            case '2':
                system(CLEAR_SCREEN);
                exibirRegras();
                getchar();
                break;
            case '3':
                printf("Saindo do jogo. Ate a proxima!\n");
                PAUSE(1000);
                return 0;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                PAUSE(1000);
        }
    }

    return 0;

}

//Funcao da contagem regressiva partindo de 5
void contagem(){
    for (int count = 5; count >= 1; count--) {
        printf("%d", count); // Mostra o número
        fflush(stdout); // Garante que a saída seja exibida imediatamente

        PAUSE(500); // Aguarda meio segundo (500 milissegundos)

        printf("\r "); // Retorna ao início da linha e sobrescreve o número com um espaço
        fflush(stdout); // Garante que a saída seja exibida imediatamente

        PAUSE(500); // Aguarda meio segundo (500 milissegundos) antes de mostrar o próximo número
    }
}

//Funcao que mostra o gabarito das cartas no modo padrao
void gabaritoColoridas(int pares[4][4]){
    int linhaDefault = 0;
    //Exibe os numeros da matriz sorteada atribuindo uma carta a cada numero
    for (int i = 0; i < 8; i++){
        if (i == 0 || i == 2 || i == 4 || i == 6){
            printf("#################     #################     #################     #################\n");
        } else {

            for (int k = 0; k < 6; k++){
                for (int w = 0; w < 4; w++){
                    switch (pares[linhaDefault][w]){
                        case 0:
                            printf("#"AZUL"               "RESET_COLOR"#     ");
                            break;
                        case 1:
                            printf("#"VERMELHO"               "RESET_COLOR"#     ");
                            break;
                        case 2:
                            printf("#"AMARELO"               "RESET_COLOR"#     ");
                            break;
                        case 3:
                            printf("#"VERDE"               "RESET_COLOR"#     ");
                            break;
                        case 4:
                            printf("#"ROSA"               "RESET_COLOR"#     ");
                            break;
                        case 5:
                            printf("#"LARANJA"               "RESET_COLOR"#     ");
                            break;
                        case 6:
                            printf("#"CIANO"               "RESET_COLOR"#     ");
                            break;
                        case 7:
                            printf("#"ROXO"               "RESET_COLOR"#     ");
                    }
                }
                
                printf("\n");
            }
            linhaDefault++;
            printf("#################     #################     #################     #################\n\n");
        }
    }
}

//Funcao que mostra o gabarito das cartas no modo para daltonicos
void gabaritoDaltonico(int pares[4][4]){
    int linhaDefault = 0;
    //Exibe os numeros da matriz sorteada atribuindo uma carta a cada numero
    for (int i = 0; i < 8; i++){
        if (i == 0 || i == 2 || i == 4 || i == 6){
            printf("#################     #################     #################     #################\n");
        } else {

            for (int k = 0; k < 6; k++){
                for (int w = 0; w < 4; w++){
                    switch (pares[linhaDefault][w]){
                        case 0:
                            printf("#""_______________""#     ");
                            break;
                        case 1:
                            printf("#"" | | | | | | | ""#     ");
                            break;
                        case 2:
                            printf("#"" < < < < < < < ""#     ");
                            break;
                        case 3:
                            printf("#"" > > > > > > > ""#     ");
                            break;
                        case 4:
                            printf("#""...............""#     ");
                            break;
                        case 5:
                            printf("#"" o o o o o o o ""#     ");
                            break;
                        case 6:
                            printf("#""xxxxxxxxxxxxxxx""#     ");
                            break;
                        case 7:
                            printf("#"" v v v v v v v ""#     ");
                    }
                }
                
                printf("\n");
            }
            linhaDefault++;
            printf("#################     #################     #################     #################\n\n");
        }
    }
}

//Funcao para exibir as cartas no modo padrao
void mostrarcartavirada(int pares[4][4], int viradas[4][4]) {
    int linhaDefault;
    for (int i = 0; i < 8; i++) {
        if (i == 0 || i == 2 || i == 4 || i == 6) {
            printf("#################     #################     #################     #################\n");
        } else {
            if (i == 1){
                linhaDefault = 0;
            } else if (i == 3){
                linhaDefault = 1;
            } else if (i == 5){
                linhaDefault = 2;
            } else if (i == 7){
                linhaDefault = 3;
            }
            for (int k = 0; k < 6; k++) {
                for (int w = 0; w < 4; w++) {
                    if (viradas[linhaDefault][w] == 1) {
                        switch (pares[linhaDefault][w]) {
                            case 0:
                            printf("#"AZUL"               "RESET_COLOR"#     ");
                            break;
                        case 1:
                            printf("#"VERMELHO"               "RESET_COLOR"#     ");
                            break;
                        case 2:
                            printf("#"AMARELO"               "RESET_COLOR"#     ");
                            break;
                        case 3:
                            printf("#"VERDE"               "RESET_COLOR"#     ");
                            break;
                        case 4:
                            printf("#"ROSA"               "RESET_COLOR"#     ");
                            break;
                        case 5:
                            printf("#"LARANJA"               "RESET_COLOR"#     ");
                            break;
                        case 6:
                            printf("#"CIANO"               "RESET_COLOR"#     ");
                            break;
                        case 7:
                            printf("#"ROXO"               "RESET_COLOR"#     ");
                            break;
                        }
                    } else {
                        printf("#" PRETO "               " RESET_COLOR "#     ");
                    }
                }
                printf("\n");
            }
            printf("#################     #################     #################     #################\n\n");
        }
    }
}

//Funcao para exibir as cartas no modo para daltonicos
void mostrarcartaviradaDalto(int pares[4][4], int viradas[4][4]) {
    int linhaDefault;
    for (int i = 0; i < 8; i++) {
        if (i == 0 || i == 2 || i == 4 || i == 6) {
            printf("#################     #################     #################     #################\n");
        } else {
            if (i == 1){
                linhaDefault = 0;
            } else if (i == 3){
                linhaDefault = 1;
            } else if (i == 5){
                linhaDefault = 2;
            } else if (i == 7){
                linhaDefault = 3;
            }
            for (int k = 0; k < 6; k++) {
                for (int w = 0; w < 4; w++) {
                    if (viradas[linhaDefault][w] == 1) {
                        switch (pares[linhaDefault][w]) {
                            case 0:
                                printf("#""_______________""#     ");
                                break;
                            case 1:
                                printf("#"" | | | | | | | ""#     ");
                                break;
                            case 2:
                                printf("#"" < < < < < < < ""#     ");
                                break;
                            case 3:
                                printf("#"" > > > > > > > ""#     ");
                                break;
                            case 4:
                                printf("#""...............""#     ");
                                break;
                            case 5:
                                printf("#"" o o o o o o o ""#     ");
                                break;
                            case 6:
                                printf("#""xxxxxxxxxxxxxxx""#     ");
                                break;
                            case 7:
                                printf("#"" v v v v v v v ""#     ");
                            break;
                        }
                    } else {
                        printf("#""               ""#     ");
                    }
                }
                printf("\n");
            }
            printf("#################     #################     #################     #################\n\n");
        }
    }
}

void inicializarMatriz(int matriz[4][4]) {
    int i, j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            matriz[i][j] = -1; // Inicializando a matriz com um valor inválido
        }
    }
}

void exibirRegras(){
    printf("Regras do Jogo da Memoria:\n");
    printf("1. Memorize a posicao das cartas.\n");
    printf("2. Encontre os pares correspondentes.\n");
    printf("3. Ganhe o jogo encontrando todos os pares.\n");
    printf("\nPressione 'Enter' para voltar...\n");

    getchar(); // Aguarda até que o usuário pressione Enter
}

void menuopcoes(){

    printf("\nMenu:\n");
    printf("1. Iniciar Jogo\n");
    printf("2. Exibir Regras\n");
    printf("3. Sair\n");
    printf("Escolha uma opcao: ");

}

void opcoesdejogo(){
    printf("\nModo de jogo:\n");
    printf("1. Padrao\n");
    printf("2. Modo para Daltonicos\n");
    printf("Escolha uma opcao: ");
}

void introducao(){

    printf("                              __________________ \n");
    printf("                              | ______________  |\n");
    printf("                              | |             | |\n");
    printf("                              | |             | |\n");
    printf("                              | |             | |\n");
    printf("                              | |_____________| |\n");
    printf("                              |_________________|\n");
    printf("                                  _[_______]_    \n");
    printf("                             ____[___________]____\n");
    printf("                             |         [_____] []|\n");
    printf("                             |         [_____] []|\n");
    printf("                             L___________________J\n");
    printf("                             _____________________\n");
    printf("                             |###################|\n");
    
    printf("                        +-+-+-+-+ +-+-+ +-+-+-+-+-+-+-+\n");
    printf("                        |J|o|g|o| |d|a| |m|e|m|o|r|i|a|\n");
    printf("                        +-+-+-+-+ +-+-+ +-+-+-+-+-+-+-+\n");

}