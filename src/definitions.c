#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

enum colours  {RESET,INCREASED_INTENSITY,BLACK=30,RED,GREEN,YELLOW,BLUE,PURPLE,CYAN,WHITE,\
               RED_BG=41,GREEN_BG,YELLOW_BG,BLUE_BG,PURPLE_BG,CYAN_BG,WHITE_BG,\
               LIGHTBLACK_BG=100,LIGHTRED_BG,LIGHTGREEN_BG,LIGHTYELLOW_BG,LIGHTBLUE_BG,LIGHTPURPLE_BG,LIGHTCYAN_BG,PUREWHITE_BG};

enum boolean {FALSE, TRUE};

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
}

}