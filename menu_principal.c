#include <stdio.h>
#include <windows.h>
#include <conio.h> //Caso esta biblioteca não pegue em sua máquina, deve-se importar manualmente

void menuCIMA(int tamanho);
void menuBAIXO(int tamanho);
void menuOPCAO(char opcao[], int tamanho);
void gotoXY(int x, int y);

int menu_principal() {
    int o;
    menuCIMA(40);
    printf(" %c                  MENU                  %c\n", 186, 186);
    menuOPCAO("", 40);
    menuOPCAO(" 1 - Menu Alunos", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 2 - Menu Acervo", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 3 - Menu Emprestimo", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 4 - Sair", 40);
    menuOPCAO("", 40);
    menuBAIXO(40);
    menuCIMA(10);
    menuOPCAO(" OPCAO: ", 10);
    menuBAIXO(10);
    gotoXY(10, 13);
    scanf("%d", &o);
    return o;
}

void menuCIMA(int tamanho) {
    int i;
    printf(" %c", 201);
    for (i = 0 ; i < tamanho ; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 187);
}

void menuOPCAO(char opcao[], int tamanho) {
    int  cont = 0, i = 0;
    printf(" %c", 186);
    while (opcao[i] != '\0') {
        i++;
        cont++;
    }
    printf("%s", opcao);
    while (cont < tamanho) {
        printf("%c", 32);
        cont++;
    }
    printf("%c\n", 186);
}

void menuBAIXO(int tamanho) {
    int i;
    printf(" %c", 200);
    for ( i = 0 ; i < tamanho ; i++) {
        printf("%c", 205);
    }
    printf("%c\n", 188);
}

void gotoXY(int x,int y){
    COORD coordenadas = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordenadas);
}
