#include "definitions.c"
/* void gotoxy(int x,int y) { 

        printf("%c[%d;%df",0x1B,y,x); 
    } */
int main(){
    printf("\x1b[%dm O", BLUE);
    printf(" \n");
    printf("..    ..\n");
    printf("..    ..\n");
    changeTextColour(RED);
    printf("..    ..\n");
    restoreConsole();
    printf("..    ..\n");
    printf("..    ..\n");
    //changeCursorTo(3,3);
    //moveCursorUp(3);
    //moveCursorRight(3);
    writeSomethingSomewhereAndReturn(3,2);
    printf("o");
    int i;
    scanf("%d", &i);
}