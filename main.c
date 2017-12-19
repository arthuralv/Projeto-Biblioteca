#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <windows.h>
#include <locale.h>
#include "menu_principal.c"
#include "alunos.h"


main(){
    setlocale(LC_ALL, "");
    int i,j, op=0;
    printf("\n\n     ...:::::  VOCÊ VAI CONHECER O NOSSO SISTEMA DE GESTÃO DE BIBLIOTECAS ! :::::... \n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("     Carregando Sistema...\n\n");
    for (i = 1; i <= 50; i++){
      printf ("  %d%%\r", i*2);
      for (j = 0; j < i; j++){
         if (j == 0)
           printf("     ");
           printf ("%c", 177);
           Sleep(2);
      }
   }
    system("cls");
    printf ("\n\n\n\tInicializando sistema...");
    Sleep(1000);//pausa para inicializar o sistema
    system("cls");
    do{
        menu_principal();
        scanf("%d", &op);
        system("cls");
        switch(op){
            case 1:
                op_alunos();break;
            case 2:
                printf("Cadastrar acervo\n\n");break;
            case 3:
                printf("Emprestimos\n\n");break;
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



