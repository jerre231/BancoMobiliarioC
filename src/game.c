#include "houses.c" //cachorro

bool running = true; //o while do jogo começa rodando por enquanto

int turnos = 0;
    //quantidade de turnos total, turno atual de qual jogador

int rollDice(){
    int dice = (arc4random()%6)+1;
    return dice;
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

void position(int x, int y) //função para definir a posição de algum print no terminal, deve ser escrito: position("coordenada de x", "coordenada de y");
{                           //[gotoXY!]
    COORD c;                //precisa do #include <windows.h>
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
    
int clearScreen(){
    system("clear || cls");
}
int printTable(){
    clearScreen();
    printf("\n");
    printf("\n                ST.CH  ELCT  STATES VRGNIA PNSLVA  ST.JA   COM    TEN    NY    FREE         ");
    printf("\n                 AVE   COMP    AVE    AVE   RAIL    AVE   CHEST   AVE   AVE    PARK         ");
    printf("\n        ____________________________________________________________________________        ");
    printf("\n VISIT |      |      |      |      |      |      |      |      |      |      |      |       ");
    printf("\n  JAIL |      |      |      |      |      |      |      |      |      |      |      |       ");
    printf("\n       |______|______|______|______|______|______|______|______|______|______|______|       ");
    printf("\n CNNCT |      |                                                              |      | KNTCY ");
    printf("\n  AVE  |      |                                                              |      |  AVE  ");
    printf("\n       |______|                                                              |______|       ");
    printf("\n VERMNT|      |                                                              |      |       ");
    printf("\n  AVE  |      |                                                              |      |CHANCE ");
    printf("\n       |______|                                                              |______|       ");
    printf("\n       |      |                                                              |      |  IND  ");
    printf("\n CHANCE|      |                                                              |      |  AVE  ");
    printf("\n       |______|                                                              |______|       ");
    printf("\n ORNTL |      |                                                              |      |  ILL  ");
    printf("\n  AVE  |      |                                                              |      |  AVE  ");
    printf("\n       |______|                                                              |______|       ");
    printf("\n  READ |      |                                                              |      | B&O.  ");
    printf("\n  RAIL |      |                                                              |      | RAIL  ");
    printf("\n       |______|                                                              |______|       ");
    printf("\n       |      |                                                              |      |ATLNTC ");
    printf("\n  TAX  |      |                                                              |      |  AVE  ");
    printf("\n       |______|                                                              |______|       ");
    printf("\n BALTIC|      |                                                              |      | VNTNR ");
    printf("\n  AVE  |      |                                                              |      |  AVE  ");
    printf("\n       |______|                                                              |______|       ");
    printf("\n  COM  |      |                                                              |      | WATER ");
    printf("\n CHEST |      |                                                              |      | WORKS ");
    printf("\n       |______|                                                              |______|       ");
    printf("\n MEDTRN|      |                                                              |      | MRVN  ");
    printf("\n  AVE  |      |                                                              |      | GRDNS ");
    printf("\n       |______|______________________________________________________________|______|       ");
    printf("\n       |      |      |      |      |      |      |      |      |      |      |      | GO TO ");
    printf("\n START |      |      |      |      |      |      |      |      |      |      |      |  JAIL ");
    printf("\n       |______|______|______|______|______|______|______|______|______|______|______|       ");
    printf("\n                BRDWK LUXURY  PARK  CHANCE  SHORT PNSLVA   COM    NC    PCFC                ");
    printf("\n                       TAX    PLACE         LINE    AVE   CHEST   AVE   AVE                 ");
}

int main(){
    
// TODO: Menu Principal aqui <--

declarePlayers(players, playerCount, Nomes);

declareHouses(houses);

int turnoPlayer = 0; // TODO: Configurar essa variável com o sistema de turnos

while(running){ //while do jogo em si
    // TODO: adicionar if, caso o jogador esteja na prisão
    currentPlayer = &players[turnoPlayer];
    if(!(currentPlayer->prisao == 1)){
        unsigned int rollIsOver:1 = 0;
        int housesToWalk = 0;
        while(!rollIsOver){
            int roll1 = rollDice();
            int roll2 = rollDice();
            printf("%s rolou %d e %d para andar!\n", currentPlayer->nome, roll1, roll2);
            housesToWalk += (roll1 + roll2);
            if(roll1 == roll2){https://github.com/MaquinaDeCoxinha/BancoMobiliarioC
            } else {
                printf("%s rolou números iguais para andar, rola de novo!", currentPlayer->nome);
            }
        }
        currentPlayer->pos += housesToWalk;
        if(currentPlayer->pos >= 40){
            currentPlayer->pos -= 40;
        }
    }
    currentHouse = &houses[currentPlayer->pos];
    int opcao; // variável auxiliar em que será armazenada a opcao do jogador
    switch (currentHouse->type) {
        case HOUSE_STD:
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
