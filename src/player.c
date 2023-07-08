#include "board.c"

void printPlayerInfo(struct player *currentPlayer)
{
    ClearRightScreen(0); 
    move(95,3); printf("JOGADOR: ");
    changeTextColour(currentPlayer->colour);
    printf("%s ",currentPlayer->nome);
    changeTextColour(RESET);
    printf("DINHEIRO EM MAOS: $%d VALOR EM BENS: $%d", currentPlayer->money, currentPlayer->netWorth);
}

int BuyAndSellHousesMenu(struct player *currentPlayer, struct house* houses)   // Lembrar de sempre chamar a funcao printPlayerInfo() depois de executar essa funcao, pois ela vai apagar oq foi printado antes
{
    int *propertiesPlayer = (currentPlayer->properties);
    ClearRightScreen(0);
    move(95,3); printf("JOGADOR: ");
    changeTextColour(currentPlayer->colour);
    printf("%s ",currentPlayer->nome);
    changeTextColour(RESET);
    printf("DINHEIRO EM MAOS: $%d VALOR EM BENS: $%d", currentPlayer->money, currentPlayer->netWorth);
    move(95,5); printf("BENS DO JOGADOR: ");
    int startlineLIST = 6;
    for(int i = 0; i < currentPlayer->numberofProperties; i++)
    {
        move(95,startlineLIST+i); printf("%d- %s (%d casas e um aluguel atual de $%d)", propertiesPlayer[i], houses[propertiesPlayer[i]].name, houses[propertiesPlayer[i]].housesBuilt, houses[propertiesPlayer[i]].rent);
    }
    buyorsell: move(95,25); printf("Deseja comprar ou vender algo?");
    move(95,26); printf("1- COMPRAR CASAS");
    move(95,27); printf("2- VENDER PROPRIEDADES/CASAS");
    move(95,28); printf("3- VOLTAR");
    choicebuyorsell: move(95,29); fflush(stdin); char opcao = getchar();
    switch (opcao) {
        case '1':
            move(95,30); printf("Escolha qual propriedade voce deseja administrar.");
            choicewheretobuy: move(95,31); fflush(stdin); int opcaoProp = (int)getchar();
            if( (currentPlayer->properties[opcaoProp] > 40) || (currentPlayer->properties[opcaoProp]) < 0 || (currentPlayer->properties[opcaoProp]) == 0) {
                move(95,32); printf("Opcao invalida, por favor tente novamente.");
                move(95,33); printf("Pressione qualquer botao para continuar.");
                fflush(stdin);
                move(95,34); getchar();
                ClearRightScreen(31);
                goto choicewheretobuy;
            }
            move(95, 32); printf("O preco para comprar uma casa nessa propriedade e $%d", houses[propertiesPlayer[(int)opcao]].buildCost);
            move(95, 33); printf("O alugel ao comprar uma casa nessa propriedade e $%d", houses[propertiesPlayer[(int)opcao]].rentWithHouses);
            move(95, 34); printf("Deseja comprar uma casa aqui?");
            move(95, 35); printf("1- SIM");
            move(95, 36); printf("2- VOLTAR");
            choicewannabuyhouse: move(95, 37); fflush(stdin); char opcao2 = getchar();
            switch (opcao2) {
                case '1':
                    if(!((currentPlayer->money -= houses[propertiesPlayer[(int)opcao]].buildCost) < 0)) {
                        move(95,38); printf("Casa comprada com sucesso!");
                        move(95,39); printf("O menu de compras agora sera atualizado.");
                        move(95,40); printf("Pressione qualquer botao para continuar.");
                        fflush(stdin);
                        move(95,41); getchar();
                        ClearRightScreen(0);
                        return EXIT_SUCCESS;
                    } else {
                        move(95,38); printf("Voce nao tem dinheiro suficiente!");
                        move(95,39); printf("Voce ira voltar para a parte anterior");
                        move(95,40); printf("Pressione qualquer botao para continuar.");
                        fflush(stdin);
                        move(95,41); getchar();
                        ClearRightScreen(29);
                        goto choicebuyorsell;
                    }
                    break;
                case '2':
                    ClearRightScreen(29);
                    goto choicebuyorsell;
                    break;
                default:
                    move(95,38); printf("Opcao invalida, por favor tente novamente.");
                    move(95,39); printf("Pressione qualquer botao para continuar.");
                    fflush(stdin);
                    move(95,40); getchar();
                    ClearRightScreen(37);
                    goto choicewannabuyhouse;
                    break;
            };

            break;

        case '2':
            move(95,30); printf("Escolha qual propriedade voce deseja administrar. Aperte 0 para voltar");
            choicewheretosell: move(95,31); int opcaoProp2 = getchar();
            opcaoProp2 = opcaoProp2 - '0';
            if(opcaoProp2 == 0) {
                ClearRightScreen(29);
                goto choicebuyorsell;
            }
            if( (currentPlayer->properties[opcaoProp2] > 40) || (currentPlayer->properties[opcaoProp2]) < 0) {
                move(95,32); printf("Opcao invalida, por favor tente novamente.");
                move(95,33); printf("Pressione qualquer botao para continuar.");
                move(95,34); getchar();
                ClearRightScreen(31);
                goto choicewheretosell;
            }
            if(houses[currentPlayer->properties[opcaoProp2]].housesBuilt <= 0) {
                move(95,32); printf("Voce nao tem nenhuma casa aqui! Por favor tente novamente");
                move(95,33); printf("Pressione qualquer botao para continuar.");
                move(95,34); getchar();
                ClearRightScreen(31);
                goto choicewheretosell;
            }
            move(95, 32); printf("Voce ganhara $%.0f ao vender uma casa dessa propriedade", (houses[currentPlayer->properties[opcaoProp2]].buildCost)/2);
            move(95, 33); printf("Deseja vender uma casa aqui?");
            move(95, 34); printf("1- SIM");
            move(95, 35); printf("2- VOLTAR");
            choicewannasellhouse: move(95, 36); char opcao3 = getchar();
            switch (opcao3) {
                case '1':
                    move(95,37); printf("Casa vendida com sucesso!");
                    move(95,38); printf("O menu de compras agora sera atualizado.");
                    move(95,39); printf("Pressione qualquer botao para continuar.");
                    move(95,40); getchar();
                    ClearRightScreen(0);
                    return EXIT_SUCCESS;
                    break;
                case '2':
                    ClearRightScreen(29);
                    goto choicebuyorsell;
                    break;
                default:
                    move(95,37); printf("Opcao invalida, por favor tente novamente.");
                    move(95,38); printf("Pressione qualquer botao para continuar.");
                    move(95,39); getchar();
                    ClearRightScreen(36);
                    goto choicewannasellhouse;
                    break;
            };
            break;

        case '3':
            return EXIT_SUCCESS;
            break;
        default:
            move(95,30); printf("Opcao invalida, por favor tente novamente.");
            move(95,31); printf("Pressione qualquer botao para continuar.");
            fflush(stdin);
            move(95,32); getchar();
            ClearRightScreen(25);
            goto buyorsell;
            break;
    };
    return EXIT_FAILURE;
}

void addPropertieToPlayer(struct player *currentPlayer, struct house houses[], int propertieID) 
{
    currentPlayer->properties[currentPlayer->numberofProperties] = houses[propertieID].ID;
    currentPlayer->numberofProperties += 1;
}

int delPropertieToPlayer(struct player *currentPlayer, struct house houses[], int propertieID) 
{
    for(int i=0; i < 40; i++)
    {
        if (currentPlayer->properties[i] == propertieID)
        {
        currentPlayer->properties[i] = NULL;
        currentPlayer->numberofProperties -= 1;
        return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

void playerLosed(struct player *currentPlayer) 
{
    move(95, 0); printf("O jogador %s foi a falencia!", currentPlayer->nome);
    movePlayer(currentPlayer, currentPlayer->pos, 666);
    currentPlayer->faliu = TRUE;
    // TODO: Devolver propriedades do jogador ao banco (?)
}