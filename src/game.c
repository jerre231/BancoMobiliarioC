#include "player.c"

bool running = true; //o while do jogo começa rodando por enquanto

int turnos = 0;
    //quantidade de turnos total, turno atual de qual jogador

int maingame() //loop do jogo
{    
    declarePlayers(players);    //iniciando variáveis
    declareHouses(houses);

    printTable();   //printando o tabuleiro, que fica fixo

    for(int i=0; i<playerCount; i++)    //colocando os players na casa do início
    {
        currentPlayer = &players[i];
        movePlayer(currentPlayer, 0, 0);
    }

    int playerInic = 0;

    SAIRGAME:
    while(running){ //while do jogo em si
        fflush(stdin);
        ClearRightScreen(0);

        if(turnos >= playerCount){
            turnos = 0; }
        if(playerInic >= playerCount){
            playerInic = 0; }

        currentPlayer = &players[playerInic];
        
        if(currentPlayer->turno != turnos){
            playerInic++;
            goto SAIRGAME;  }
        if(currentPlayer->faliu == 1){
            turnos++;
            goto SAIRGAME;  }

        printPlayerInfo(currentPlayer);

        int housesToWalk;

        if(!(currentPlayer->prisao == 1))
        {
            int rollIsOver = 0;
            int oldLocation;
            housesToWalk = 0;

            while(!rollIsOver)
            {
                ClearRightScreen(4);
                int roll1 = rollDice();
                int roll2 = rollDice();
                move(95,5); printf("%s rolou %d e %d para andar!\n", currentPlayer->nome, roll1, roll2);
                housesToWalk += (roll1 + roll2);
                if(roll1 != roll2){rollIsOver = 1;} 
                else
                {
                    move(95,6); printf("%s rolou numeros iguais para andar, rola de novo!\n", currentPlayer->nome);
                    move(95,7); printf("Pressione qualquer botao para continuar... \n");
                    fflush(stdin);
                    move(95,8); getchar();
                }
            }

            oldLocation = currentPlayer->pos;
            currentPlayer->pos += housesToWalk;

            if(currentPlayer->pos >= 40){currentPlayer->pos -= 40;}

            movePlayer(currentPlayer, oldLocation, currentPlayer->pos);
        }
        currentHouse = &houses[currentPlayer->pos];
        switch (currentHouse->type)
        {
            case HOUSE_STD:
            move(95,6); printf("Voce caiu na casa %s, ", currentHouse->name);
            if(currentHouse->isOwnedBySomeone)
            {
                move(95,7); printf("ela e possuída por %s.\n", players[currentHouse->ownerID].nome);
                move(95,8); printf("Voce deve pagar %d$ ao proprietario.\n", currentHouse->rent);
                // TODO: adicionar o sistema de pagar aluguel
                if(currentPlayer->netWorth < currentHouse->rent) { // Falencia!
                    move(95,9); printf("O jogador %s nao tem como pagar o aluguel!.", currentPlayer->nome);
                    move(95,10); playerLosed(currentPlayer);
                    break; // TODO: TESTAR!!!!!!!!!!!!!!!!!!!!!!!!!!!
                } 
                else if(currentPlayer->money < currentHouse->rent) {
                    while(!(currentPlayer->money >= currentHouse->rent)){    // TODO: TESTAR!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        move(95,9); printf("Voce precisa vender algumas coisas para conseguir pagar o aluguel");
                        move(95,10); printf("Vamos abrir o menu de compra e venda para voce.");
                        move(95,11); printf("Aperte qualquer botao para continuar");
                        fflush(stdin);
                        move(95,12); getchar();
                        if((BuyAndSellHousesMenu(currentPlayer, houses))!= EXIT_SUCCESS) {
                            ClearRightScreen(0);
                            move(95,0); printf("error in BuyAndSellHousesMenu"); }
                        printPlayerInfo(currentPlayer);
                    }
                }
                currentPlayer->money -= currentHouse->rent;
            } 
            else 
            {
                move(95,7); printf("ela nao e possuida por ninguem.\n");
                move(95,8); printf("%s deseja comprar essa propriedade por %i?\n", currentPlayer->nome, currentHouse->cost);
                move(95,9); printf("1 - SIM"); move(95,10); printf("2 - NAO"); move(95,11); printf("3 - COMPRAR E VENDER CASAS");
                move(95,12); fflush(stdin); char opcao = getchar();
                switch (opcao) {
                case '1':
                    currentPlayer->money -= currentHouse->cost;
                    currentHouse->isOwnedBySomeone = TRUE;
                    currentHouse->ownerID = currentPlayer->ID;
                    addPropertieToPlayer(currentPlayer, houses, currentHouse->ID);
                    ClearRightScreen(4);
                    move(95,5); printf("Voce adquiriu a casa %s!.", currentHouse->name); // TODO: adicionar sistema de não poder pagar
                    move(95,6); printf("Pressione qualquer botao para continuar... \n");
                    fflush(stdin);
                    move(95,7); getchar();
                    break;
                case '2':
                    break;
                case '3':
                    if((BuyAndSellHousesMenu(currentPlayer, houses))!= EXIT_SUCCESS) {
                            ClearRightScreen(0);
                            move(95,0); printf("error in BuyAndSellHousesMenu"); }
                        printPlayerInfo(currentPlayer);
                    break;
                };
            }
            break;

            case HOUSE_CMP:
            move(95,6); printf("Você caiu na casa %s, ", currentHouse->name);
            if(currentHouse->isOwnedBySomeone)
            {
                move(95,7); printf("ela e possuída por %s.\n", players[currentHouse->ownerID].nome);
                move(95,8); printf("Você deve pagar %d$ ao proprietario.\n", housesToWalk*(currentHouse->rent));
                // TODO: adicionar o sistema de pagar aluguel
                if(currentPlayer->netWorth < housesToWalk*(currentHouse->rent)) { // Falencia!
                    move(95,9); printf("O jogador %s nao tem como pagar o aluguel!.", currentPlayer->nome);
                    move(95,10); playerLosed(currentPlayer);
                    break; // TODO: TESTAR!!!!!!!!!!!!!!!!!!!!!!!!!!!
                } 
                else if(currentPlayer->money < housesToWalk*(currentHouse->rent)) {
                    while(!(currentPlayer->money >= housesToWalk*(currentHouse->rent))){    // TODO: TESTAR!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        move(95,9); printf("Voce precisa vender algumas coisas para conseguir pagar o aluguel");
                        move(95,10); printf("Vamos abrir o menu de compra e venda para voce.");
                        move(95,11); printf("Aperte qualquer botao para continuar");
                        fflush(stdin);
                        move(95,12); getchar();
                        if((BuyAndSellHousesMenu(currentPlayer, houses))!= EXIT_SUCCESS) {
                            ClearRightScreen(0);
                            move(95,0); printf("error in BuyAndSellHousesMenu"); }
                        printPlayerInfo(currentPlayer);
                    }
                }
                currentPlayer->money -= housesToWalk*(currentHouse->rent);
            } 
            else 
            {
                move(95,7); printf("ela não é possuída por ninguém.\n");
                move(95,8); printf("%s deseja comprar essa propriedade por %i?\n", currentPlayer->nome, currentHouse->cost);
                move(95,9); printf("1 - SIM"); move(95,10); printf("2 - NAO"); move(95,11); printf("3 - COMPRAR E VENDER CASAS");
                move(95,12); fflush(stdin); char opcao = getchar();
                switch (opcao) {
                case '1':
                    currentPlayer->money -= currentHouse->cost;
                    currentHouse->isOwnedBySomeone = TRUE;
                    currentHouse->ownerID = currentPlayer->ID;
                    addPropertieToPlayer(currentPlayer, houses, currentHouse->ID);
                    ClearRightScreen(4);
                    move(95,5); printf("Voce adquiriu a casa %s!.", currentHouse->name); // TODO: adicionar sistema de não poder pagar
                    move(95,6); printf("Pressione qualquer botao para continuar... \n");
                    fflush(stdin);
                    move(95,7); getchar();
                    break;
                case '2':
                    break;
                case '3':
                    if((BuyAndSellHousesMenu(currentPlayer, houses))!= EXIT_SUCCESS) {
                            ClearRightScreen(0);
                            move(95,0); printf("error in BuyAndSellHousesMenu"); }
                        printPlayerInfo(currentPlayer);
                    break;
                };
            }

            case GO_TO_JAIL:
            move(95,5); printf("Opa! Você está preso!");
            currentPlayer->prisao = TRUE;
            currentPlayer->turnosPrisao = 3;
            // TODO: adicionar sistema de prisao
            break;

            case FREE_DAY:
            move(95,5); printf("Você recebeu um dia de folga! Fique um turno sem jogar.");
            break;

            case SORTE_OU_REVES:
            move(95,5); printf("Você vai retirar uma carta aleatória!");
            // TODO: adicionar sistema de carta sorte ou reves
            break;
            
        }

        while(TRUE) {   //Turno do player atual
            ClearRightScreen(0);
            printPlayerInfo;
            changeTextColour(currentPlayer->colour);
            move(95,3); printf("%s ", currentPlayer->nome);
            changeTextColour(RESET); printf("o que deseja fazer?");
            move(95,4); printf("1 - COMPRAR E VENDER CASAS"); move(95,5); printf("2 - PASSAR TURNO"); move(95,6); printf("3 - DESISTIR");
            move(95,8); fflush(stdin); char opcao = getchar();
            switch (opcao){
                case '1':
                    if((BuyAndSellHousesMenu(currentPlayer, houses))!= EXIT_SUCCESS) {
                            ClearRightScreen(0);
                            move(95,0); printf("error in BuyAndSellHousesMenu"); }
                    break;
                case '2':
                    goto turnoacabou;
                    break;
                case '3':
                    move(95,9); printf("Voce tem certeza disso? nao sera possivel voltar... (1 = SIM)");
                    fflush(stdin);
                    move(95,10); char opcao2 = getchar();
                    if(opcao2 == '1') {
                        ClearRightScreen(0);
                        playerLosed(currentPlayer);
                        goto turnoacabou;
                    } else {
                        move(95,11); printf("Tudo bem entao, nada sera feito.");
                    }
                    break;
                default:
                    move(95,9); printf("Opcao invalida, por favor tente novamente.");
                    break;
            };

            move(95,16); printf("Pressione qualquer botao para continuar... \n");
            fflush(stdin);
            move(95,17); getchar();
        }

        turnoacabou:
        move(95,15); printf("Seu turno acabou!");
        move(95,16); printf("Pressione qualquer botao para continuar... \n");
        fflush(stdin);
        move(95,17); getchar();
        turnos++;
    }
    return EXIT_SUCCESS;
}

// int main
int main(){
    clearScreen();
    printf("\n                                              888b     d888  .d88888b.  888b    888  .d88888b.  8888888b.   .d88888b.  888    Y88b   d88P           "); 
    printf("\n                                              8888b   d8888 d88P\" \"Y88b 8888b   888 d88P\" \"Y88b 888   Y88b d88P\" \"Y88b 888     Y88b d88P      ");       
    printf("\n                                              88888b.d88888 888     888 88888b  888 888     888 888    888 888     888 888      Y88o88P             "); 
    printf("\n                                              888Y88888P888 888     888 888Y88b 888 888     888 888   d88P 888     888 888       Y888P              "); 
    printf("\n                                              888 Y888P 888 888     888 888 Y88b888 888     888 8888888P\"  888     888 888        888              ");  
    printf("\n                                              888  Y8P  888 888     888 888  Y88888 888     888 888        888     888 888        888               "); 
    printf("\n                                              888   \"   888 Y88b. .d88P 888   Y8888 Y88b. .d88P 888        Y88b. .d88P 888        888              ");  
    printf("\n                                              888       888  \"Y88888P\"  888    Y888  \"Y88888P\"  888         \"Y88888P\"  88888888   888         ");       
    printf("\n\n\n\n\n");
    srand((unsigned)time(NULL));
    //checkWindowSize(172, 40);     // TODO: RESOLVER ISSO AQUI DE ALGUM JEITO
    printf("1- Novo Jogo \n");
    choice_mainmenu:
    fflush(stdin);
    char choice = getchar();
    if (choice == '1') 
    {
        if(maingame()!= EXIT_SUCCESS)
        {
            printf("Error in maingame");
        }
    }
    else
    {
        printf("Opcao invalida! Por favor tente novamente.\n");
        goto choice_mainmenu; 
    }
}