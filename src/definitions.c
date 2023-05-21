#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

char Nomes[][20] = {"Nome1","Nome2","Nome3","Nome4"};// TODO: Leitura de nomes, nomes exemplo temporarios

int playerCount = 4; // TODO: criar uma função aqui depois que o menu principal for criado

int startingMoney = 200; //Dinheiro Inicial dos players, TODO: pode ser ajustado?

struct player{ //Definindo a as variáveis de cada jogador
        int ID;
        char nome[20];
        int money;
        //int xy[2];
        int pos;
        int turno;
        bool prisao;
        int turnosPrisao;
    };
struct player players[4], *currentPlayer;

void declarePlayers(struct player player[], int playerCount, char (*Nomes)[20]){
for(int i=0;i<playerCount;i++){
    strcpy(player[i].nome,Nomes[i]);
    //player[i].nome = Nomes[i];
    player[i].ID = i;
    player[i].money = startingMoney;
    //player[i].xy[0] = player[i].xy[1] = 0;
    player[i].pos = 0;
    player[i].turno = i; //TODO: Definir turno aleatório dos players
    player[i].prisao = false;
    player[i].turnosPrisao = 0;
}

}