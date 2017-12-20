#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <windows.h>
#include "menu_principal.c"
#include "alunos.h"

//#include <locale.h>

void apresentacao();

main() {
    apresentacao();
    int o = menu_principal();
    do {
        system("cls");
        switch(o) {
        case 1:
            op_alunos();
            break;
        case 2:
            printf("Cadastrar acervo\n\n");
            break;
        case 3:
            printf("Emprestimos\n\n");
            break;
        case 4:
            printf("\n\n\t\tObrigado por usar nosso sistema!\n\n");
            Sleep(1000);
            exit(0);
        default:
            printf("\nOpcao incorreta!\n");
            system("pause");
            system("cls");
            do {
                o = menu_principal();
                system("cls");
            } while(o < 1 && o > 4);
            break;
        }
    } while (o != 4);

}


void apresentacao() {
    int i, j, op = 0;
    menuCIMA(116);
    printf("                                ...:::::  BIBLIOTECA CENTRAL DA UEPB ! :::::...");
    while( i < 25) {
        printf("\n");
        i++;
    }
    gotoXY(0, 28);
    menuBAIXO(116);
    gotoXY(1, 25);
    printf("   Carregando Sistema...\n\n");
    for (i = 1; i <= 50; i++) {
        printf ("  %d%%\r", i*2);
        for (j = 0; j < i; j++) {
            if (j == 0)
                printf("    ");
            printf ("%c", 241);
            Sleep(2);
        }
    }
    system("cls");
}
