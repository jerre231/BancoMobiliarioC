#include <stdio.h>
#include <stdlib.h>
void gotoxy(int x,int y) {     printf("%c[%d;%df",0x1B,y,x); }
print("\n");
print(".. ..\n");
print(".. ..\n");
gotoxy(2,3);