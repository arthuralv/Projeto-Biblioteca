#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <windows.h>
#include "menu_principal.c"
#include "alunos.h"
#include "acervo.h"
#include "emprestimos.h"

main() {
    int i, j, op;
    menuCIMA(116);
    printf("                                    ...:::::  BIBLIOTECA CENTRAL DA UEPB  :::::...");
    gotoXY(0, 28);
    menuBAIXO(55);
    gotoXY(0, 24);
    menuCIMA(23);
    menuOPCAO(" Carregando Sistema...", 23);
    menuBAIXO(23);
    for (i = 1; i <= 50; i++) {
        printf ("  %d%%\r", i*2);
        for (j = 0; j < i; j++) {
            if (j == 0)
                printf("  ");
            printf ("%c", 177);
            Sleep(2);
        }
    }
    gotoXY(26, 26);
    system("cls");
    do {
        op = menu_principal();
        system("cls");
        setbuf(stdin, NULL);
        switch(op) {
        case 1:
            op_alunos();
            break;
        case 2:
            op_acervo();
            break;
        case 3:
            op_emprestimos();
            break;
        case 4:
            menuCIMA(24);
            menuOPCAO(" Finalizando Sistema...", 24);
            menuBAIXO(24);
            system("pause");
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
