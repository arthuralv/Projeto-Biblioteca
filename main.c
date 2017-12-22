#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <windows.h>
#include "menu_principal.c"
#include "alunos.h"
#include "acervo.h"

main() {
    int i,j, op;
    menuCIMA(116);
    printf("                                ...:::::  BIBLIOTECA CENTRAL DA UEPB ! :::::... ");
    gotoXY(0, 25);
    menuCIMA(21);
    menuOPCAO("Carregando Sistema...", 21);
    menuBAIXO(21);
    for (i = 1; i <= 50; i++) {
        printf ("  %d%%\r", i*2);
        for (j = 0; j < i; j++) {
            if (j == 0)
                printf(" ");
            printf ("%c", 177);
            Sleep(2);
        }
    }
    system("cls");
    gotoXY(26, 27);
    system("cls");
    do {
        op = menu_principal();
        system("cls");
        switch(op) {
        case 1:
            op_alunos();
            break;
        case 2:
            op_acervo();
            break;
        case 3:
            printf("Emprestimos\n\n");
            break;
        case 4:
            printf("\n\n\t\tObrigado por usar nosso sistema!\n\n");
            Sleep(1000);
            exit(0);
        default:
            system("cls");
            printf("\n\n Opcao incorreta!\n\n");
            system("pause");
            system("cls");
            break;
        }
    } while(op != 4);
}
