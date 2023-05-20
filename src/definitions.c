#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

//srand = (time(NULL));

char Nomes[4][20] = {"Nome1", "Nome2", "Nome3", "Nome4"}; // TODO: Leitura de nomes, nomes exemplo temporarios
int playerCount = 4; // TODO: criar uma função aqui depois que o menu principal for criado

int startingMoney = 200; //Dinheiro Inicial dos players, TODO: pode ser ajustado?

struct player{ //Definindo a as variáveis de cada jogador
        int ID;
        char nome;
        int money;
        int xy[2];
        int turno;
        bool prisao;
        int turnosPrisao;
    };
struct player players[4], *currentPlayer;
/* CODIGO ANTIGO:
struct player player1;
struct player player2;
struct player player3;
struct player player4;

void declarePlayers(){ // Função para definir as variáveis de cada jogador
    if(playerCount >= 2) {
        player1.nome = "Nome1"; // TODO: Criar a inserção dos nomes
        player1.money = startingMoney;
        player1.xy[0] = 0, player1.xy[1] = 0;
        player1.turno = 0; // TODO: Definir turno aleatório dos players
        player2.nome = "Nome2"; // TODO: Criar a inserção dos nomes
        player2.money = startingMoney;
        player2.xy[0] = 0, player2.xy[1] = 0;
        player2.turno = 1; // TODO: Definir turno aleatório dos players
    }
    if(playerCount >= 3) {
        player3.nome = "Nome3"; // TODO: Criar a inserção dos nomes
        player3.money = startingMoney;
        player3.xy[0] = 0, player3.xy[1] = 0;
        player3.turno = 2; // TODO: Definir turno aleatório dos players
    }
    if(playerCount >= 4){
        player4.nome = "Nome4"; // TODO: Criar a inserção dos nomes
        player4.money = startingMoney;
        player4.xy[0] = 0, player4.xy[1] = 0;
        player4.turno = 3; // TODO: Definir turno aleatório dos players
    }
}
*/
void declarePlayers(struct player player[], int playerCount, char (*Nomes)[20]){
for(int i=0;i<playerCount;i++){
    strcpy(player[i].nome,Nomes[i]);
    player[i].ID = i;
    player[i].money = startingMoney;
    player[i].xy[0] = player[i].xy[1] = 0;
    player[i].turno = i; //TODO: Definir turno aleatório dos players
    player[i].prisao = false;
    player[i].turnosPrisao = 0;
}

}