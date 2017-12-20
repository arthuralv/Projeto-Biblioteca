#include <stdio.h>
#define C 40

void menuCIMA();
void menuBAIXO();
void menuOPCAO();

int menu_principal (){
    int o;
    menuCIMA();
    printf("\n %c                  MENU                  %c\n", 186, 186);
    printf(" %c                                        %c\n", 186, 186);
    printf(" %c 1 - Aluno\t\t\t          %c\n", 186, 186, 186);
    printf(" %c                                        %c\n", 186, 186);
    printf(" %c 2 - Acervo\t\t\t          %c\n", 186, 186, 186);
    printf(" %c                                        %c\n", 186, 186);
    printf(" %c 3 - Emprestimo\t\t          %c\n", 186, 186, 186);
    printf(" %c                                        %c\n", 186, 186);
    printf(" %c 4 - Sair\t\t\t          %c\n", 186);
    printf(" %c                                        %c\n", 186, 186);
    printf(" %c Opcao: \t\t\t          %c", 186, 186);
    menuBAIXO();
    scanf("%d", &o);
    return o;
}

void menuCIMA(){
    int i;
    printf("\n %c", 201);
    for (i = 0 ; i < C ; i++){
        printf("%c", 205);
    }
    printf("%c", 187);
}

void menuBAIXO(){
    int i;
    printf("\n %c", 200);
    for ( i = 0 ; i < C ; i++){
        printf("%c", 205);
    }
    printf("%c", 188);
}

void menuOPCAO(char opcao[]){
    int  cont = 0, i;
    printf("%c", 188);
    while (opcao[i] != '\0'){
        cont++;
    }
    printf("");
}


