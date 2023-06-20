#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

enum colours  {RESET,INCREASED_INTENSITY,BLACK=30,RED,GREEN,YELLOW,BLUE,PURPLE,CYAN,WHITE,\
               RED_BG=41,GREEN_BG,YELLOW_BG,BLUE_BG,PURPLE_BG,CYAN_BG,WHITE_BG,\
               LIGHTBLACK_BG=100,LIGHTRED_BG,LIGHTGREEN_BG,LIGHTYELLOW_BG,LIGHTBLUE_BG,LIGHTPURPLE_BG,LIGHTCYAN_BG,PUREWHITE_BG};

enum falseoutrue {FALSE, TRUE};

char Nomes[][20] = {"Nome1","Nome2","Nome3","Nome4"};// TODO: Leitura de nomes, nomes exemplo temporarios

int playerCount = 4; // TODO: criar uma função aqui depois que o menu principal for criado

int housesCount = 40;

int startingMoney = 200; //Dinheiro Inicial dos players, TODO: pode ser ajustado?

struct player{ //Definindo a as variáveis de cada jogador
        int ID;
        char nome[20];
        int money;
        int netWorth; //money + valor de suas propriedades
        int pos;
        int turno;
        unsigned int prisao:1;
        int turnosPrisao;
        int colour;
    };
struct player players[4], *currentPlayer;

void declarePlayers(struct player player[], int playerCount, char (*Nomes)[20]){
for(int i=0;i<playerCount;i++){
    strcpy(player[i].nome,Nomes[i]);
    //player[i].nome = Nomes[i];
    player[i].ID = i;
    player[i].money = player[i].netWorth = startingMoney;
    player[i].pos = 0;
    player[i].turno = i; //TODO: Definir turno aleatório dos players
    player[i].prisao = FALSE;
    player[i].turnosPrisao = 0;
    switch(i) {
    case 0:
        player[i].colour = BLUE;
        break;
    case 1:
        player[i].colour = RED;
        break;
    case 2:
        player[i].colour = GREEN;
        break;
    case 3:
        player[i].colour = YELLOW;
        break;
    case 4:
        player[i].colour = PURPLE;
        break;
    case 5:
        player[i].colour = CYAN;
        break;
    }
}
}

//ANSI ESCAPE CODE FUNÇOES:

void changeTextColour(int colour) {
    printf("\x1b[%dm", colour);
}
void restoreConsole() {
    printf("\x1b[%dm", RESET);
}
void changeCursorTo(int X, int Y){
    printf("\x1b[{%d};{%d}f", X, Y);
}
void moveCursorUp(int X) {
    printf("\x1b[%dA",X);
}
void moveCursorDown(int X) {
    printf("\x1b[%dB",X);
}
void moveCursorRight(int X) {
    printf("\x1b[%dC",X);
}
void moveCursorLeft(int X) {
    printf("\x1b[%dD",X);
}
/* int getCursorPosition() {
    printf("\x1b[s");
} */
void writeSomethingSomewhereAndReturn(int X, int Y) {
    printf("\x1b 7");
    moveCursorUp(Y);
    moveCursorRight(X);
    printf("o");
    printf("\x1b 8");
}

void movePlayer(struct player *currentPlayer,int OldLocationID,int NewLocationID)
{
    int mapXY[40][2]={{ 9,36},{ 9,33},{ 9,30},{ 9,27},{ 9,24},{ 9,21},{ 9,18},{ 9,15},{ 9,12},{ 9, 9},\
                    { 9, 6},{16, 6},{23, 6},{30, 6},{37, 6},{44, 6},{51, 6},{58, 6},{65, 6},{72, 6},\
                    {79, 6},{79, 9},{79,12},{79,15},{79,18},{79,21},{79,24},{79,27},{79,30},{79,33},\
                    {79,36},{72,36},{65,36},{58,36},{51,36},{44,36},{37,36},{30,36},{23,36},{16,36}};
    int playerID = currentPlayer->ID;
    move(mapXY[OldLocationID][0]+(playerID)%4,mapXY[OldLocationID][1]+(playerID)/4);
    printf(" ");
    changeTextColour(currentPlayer->colour);
    move(mapXY[NewLocationID][0]+(playerID)%4,mapXY[NewLocationID][1]+(playerID)/4);
    printf("o");
    changeTextColour(RESET);
}

void order(int *vetor, size_t tamanho) //função para ordenar vetores de forma crescente: order("nome do vetor", "tamanho do vetor");
{
    for (int i = 0; i < tamanho - 1; ++i) {
        for (int j = i + 1; j < tamanho; ++j) {
            if (vetor[i] > vetor[j]) {
                int temp = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temp;
            }
        }
    }
}