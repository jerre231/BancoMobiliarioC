#include "definitions.c"

enum{HOUSE_STD, HOUSE_CMP, GO_TO_JAIL, FREE_DAY, SORTE_OU_REVES};
struct house {
    int ID;
    int type;
    int rentWithHouses[4]; //Alugueis de 1 casa até 4 casas
    int rentWithHotel; //Aluguel do local com hotel
    char name[30];
    int buildCost; //Custo do hotel ou casa
    unsigned int isOwnedBySomeone:1;
    unsigned int isOwnable:1;
    unsigned int isSetCompleted:1;
    int setColour; //Cor associada com o Set
    int ownerID;
    int housesBuilt;
    int hotelBuilt;
    int cost;
    int rent;
};
struct house houses[40], *currentHouse; // TODO: preparar essa lista quando o mapa estiver pronto
void declareHouses(struct house houses[]){
    for(int i=0;i<housesCount;i++){
        houses[i].ID = i;
        houses[i].type = 0; // TODO: adicionar grupos de casa
        // TODO: houses[i].colourGroup = (X, X, X)
        houses[i].isOwnedBySomeone = FALSE;
        houses[i].ownerID = houses[i].hotelBuilt = houses[i].housesBuilt = 0;
        houses[i].rent = 0;
    }
} 

