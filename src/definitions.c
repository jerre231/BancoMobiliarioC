#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int players = 4; // TODO: criar uma função aqui depois que o menu principal for criado

int startingMoney = 200; //Dinheiro Inicial dos players, TODO: pode ser ajustado?

struct player{
        char nome;
        int money;
        int xy[2];
        int turno;
    };

struct player player1;
struct player player2;
struct player player3;
struct player player4;

void declarePlayers(){ // Função para definir as variáveis de cada jogador
    if(players >= 2) {
        player1.nome = "Nome1"; // TODO: Criar a inserção dos nomes
        player1.money = startingMoney;
        player1.xy[0] = 0, player1.xy[1] = 0;
        player1.turno = 0; // TODO: Definir turno aleatório dos players
        player2.nome = "Nome2"; // TODO: Criar a inserção dos nomes
        player2.money = startingMoney;
        player2.xy[0] = 0, player2.xy[1] = 0;
        player2.turno = 1; // TODO: Definir turno aleatório dos players
    }
    if(players >= 3) {
        player3.nome = "Nome3"; // TODO: Criar a inserção dos nomes
        player3.money = startingMoney;
        player3.xy[0] = 0, player3.xy[1] = 0;
        player3.turno = 2; // TODO: Definir turno aleatório dos players
    }
    if(players >= 4){
        player4.nome = "Nome4"; // TODO: Criar a inserção dos nomes
        player4.money = startingMoney;
        player4.xy[0] = 0, player4.xy[1] = 0;
        player4.turno = 3; // TODO: Definir turno aleatório dos players
    }
}
