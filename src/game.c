
#include "board.c"

bool running = true; //o while do jogo começa rodando por enquanto

int turnos = 0;
    //quantidade de turnos total, turno atual de qual jogador

int rollDice(){
    int dice = (rand()%6)+1;
    return dice;
}

/*void position(int x, int y) //função para definir a posição de algum print no terminal, deve ser escrito: position("coordenada de x", "coordenada de y");
{                           //[gotoXY!]
    COORD c;                //precisa do #include <windows.h>
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}*/

// int main
int main(){
srand((unsigned)time(NULL));
// TODO: Menu Principal aqui <--

declarePlayers(players, playerCount, Nomes);

declareHouses(houses);

printTable();

for(int i=0; i<playerCount; i++){
    currentPlayer = &players[i];
    movePlayer(currentPlayer, 0, 0);
}

int turnoPlayer = 0; // TODO: Configurar essa variável com o sistema de turnos

while(running){ //while do jogo em si
    // TODO: adicionar if, caso o jogador esteja na prisão
    currentPlayer = &players[turnoPlayer];
    if(!(currentPlayer->prisao == 1)){
        int rollIsOver = 0;
        int housesToWalk = 0;
        int oldLocation;
        while(!rollIsOver){
            int roll1 = rollDice();
            int roll2 = rollDice();
            move(1,40);
            printf("%s rolou %d e %d para andar!\n", currentPlayer->nome, roll1, roll2);
            housesToWalk += (roll1 + roll2);
            if(roll1 != roll2){
                rollIsOver = 1;
            } else {
                printf("%s rolou números iguais para andar, rola de novo!\n", currentPlayer->nome);
            }
        }
        oldLocation = currentPlayer->pos;
        currentPlayer->pos += housesToWalk;
        if(currentPlayer->pos >= 40){
            currentPlayer->pos -= 40;
        }
        movePlayer(currentPlayer, oldLocation, currentPlayer->pos);
    }
    currentHouse = &houses[currentPlayer->pos]; // variável auxiliar em que será armazenada a opcao do jogador
    int opcao; 
    switch (currentHouse->type) {
        case HOUSE_STD:
        printf("Você caiu na casa %s, ", currentHouse->name);
        if(currentHouse->isOwnedBySomeone){
            printf("ela é possuída por %s.\n", players[currentHouse->ownerID].nome);
            printf("Você deve pagar %d$ ao proprietário.\n", currentHouse->rent);
            // TODO: adicionar o sistema de pagar aluguel
        } else {
            printf("ela não é possuída por ninguém.\n%s deseja comprar essa propriedade por %i?\n", currentPlayer->nome, currentHouse->cost);
            printf("1 - SIM\n2 - NAO\n");
            sleep(5);
            scanf("%d", &opcao);
            if(opcao == '1'){
                currentPlayer->money -= currentHouse->cost;
                currentHouse->isOwnedBySomeone = TRUE;
                currentHouse->ownerID = currentPlayer->ID;
                printf("Você adquiriu a casa %s!.", currentHouse->name); // TODO: adicionar sistema de não poder pagar
            }
        }
        break;

        case HOUSE_CMP:
        printf("Você caiu na casa %s, ", currentHouse->name);
        if(currentHouse->isOwnedBySomeone){
            printf("ela é possuída por %s.\n", players[currentHouse->ownerID].nome);
            printf("Você deve pagar %d$ ao proprietário.\n", currentHouse->rent);
            // TODO: adicionar o sistema de pagar aluguel
        } else {
            printf("ela não é possuída por ninguém.\n%s deseja comprar essa propriedade por %i?\n", currentPlayer->nome, currentHouse->cost);
            printf("1 - SIM\n2 - NAO");
            scanf("%d", &opcao);
            if(opcao == '1'){
                currentPlayer->money -= currentHouse->cost;
                currentHouse->isOwnedBySomeone = TRUE;
                currentHouse->ownerID = currentPlayer->ID;
                printf("Você adquiriu a casa %s!.", currentHouse->name); // TODO: adicionar sistema de não poder pagar
            }
        }

        break;

        case GO_TO_JAIL:
        printf("Opa! Você está preso!");
        currentPlayer->prisao = TRUE;
        currentPlayer->turnosPrisao = 3;
        // TODO: adicionar sistema de prisao
        break;

        case FREE_DAY:
        printf("Você recebeu um dia de folga! Fique um turno sem jogar.");
        break;

        case SORTE_OU_REVES:
        printf("Você vai retirar uma carta aleatória!");
        // TODO: adicionar sistema de carta sorte ou reves
        break;
    }
}
return 0;
}
