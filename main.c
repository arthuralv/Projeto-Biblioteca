#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <windows.h>
#include "menu_principal.c"
#include "alunos.h"

main(){
    int i,j, op;

    printf("\n\n                                ...:::::  BIBLIOTECA CENTRAL DA UEPB ! :::::... \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("     Carregando Sistema...\n\n");
    for (i = 1; i <= 50; i++){
      printf ("  %d%%\r", i*2);
      for (j = 0; j < i; j++){
         if (j == 0)
           printf("     ");
           printf ("%c", 241);
           Sleep(2);
      }
   }
    system("cls");
    printf ("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n     Inicializando sistema...");
    Sleep(1000);//pausa para inicializar o sistema
    system("cls");
    do{
        op = menu_principal();
        system("cls");
        switch(op){
            case 1:
                op_alunos();break;
            case 2:
                printf("Cadastrar acervo\n\n");break;
            case 3:
                printf("Empréstimos\n\n");break;
            case 4:
                printf("\n\n\t\tObrigado por usar nosso sistema!\n\n");
                Sleep(1000);
                break;
            default:
                printf("\nOpção incorreta!\n");
                break;
        }

    }while(op != 4);

}



