#include "definitions.c"
/*
o primeiro digito é a casa, o segundo é o identificador
0 - propriedade padrão
1 - propriedade compania
2 - casa go to jail
3 - casa free park ou visita de prisao
4 - sorte ou reves
*/
int HOUSE_STD = 0; HOUSE_CMP = 1; GO_TO_JAIL = 2; FREE_DAY = 3; SORTE_OU_REVES = 4;
struct house {
    int ID;
    int group;
    bool isOwnedBySomeone;
    int owner;
};
struct house houses[40]; // TODO: preparar essa lista quando o mapa estiver pronto
void declareHouses(struct house houses[]){
    for(int i=0;i<housesCount;i++){
        houses[i].ID = i;
        houses[i].group = 0; // TODO: adicionar grupos de casa
        // TODO: houses[i].colourGroup = (X, X, X)
        houses[i].isOwnedBySomeone = false;
        houses[i].owner = NULL;
    }
} 

