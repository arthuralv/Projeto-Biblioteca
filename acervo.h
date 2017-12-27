#ifndef ACERVO_H_INCLUDED
#define ACERVO_H_INCLUDED
#endif // ACERVO_H_INCLUDED
#include <stdio.h>
#include <windows.h>
#include <dos.h>
#include <string.h>

int cod_livro = 100;
//Estrutura para o cadastro de livros
typedef struct livro {
    int codigo;
    int quantidade;
    char nome_livro[50];
    char nome_autor[50];
    char area[50];
} CAD_LIVROS;

void procurarLivros();
void editarLivros();
void cadastrarLivros();
void excluirLivros();
int contadorCod();
void listarLivros();

void op_acervo () {
    int o = 0;
    struct livro li;
    do {
        menuAcervo();
        scanf("%d", &o);
        system("cls");
        switch(o) {
        case 1:
            cadastrarLivros();
            break;
        case 2:
            excluirLivros();
            break;
        case 3:
            editarLivros();
            break;
        case 4:
            listarLivros();
            break;
        case 5:
            return;
        default:
            system("cls");
            printf("\nOpcao invalida\n");
            system("pause");
            break;
        }
        fflush(stdin);
    } while(o != 5);
}

int contadorCod() {
    int aux = 0;
    FILE *arquivo;
    arquivo = fopen("cad_livros.txt", "rb");
    CAD_LIVROS li;
    if(arquivo == NULL) {
        system("cls");
        printf("\n\n  Problemas na abertura do arquivo!\n");
        system("pause");
    } else
        while(fread(&li, sizeof(CAD_LIVROS), 1,arquivo) == 1)
            if(&(li.codigo) != NULL)
                aux++;
    fclose(arquivo);
    return aux;
}

void cadastrarLivros() {
    system("cls");
    FILE* arquivo; //FILE (sempre maiuscula), variável do tipo file (arquivo é o nome do ponteiro), nesta linha está sendo criado o ponteiro
    CAD_LIVROS livros;
    arquivo = fopen ("cad_livros.txt", "ab");// "ab" acrescenta dados binários no fim do arquivo e se o arquivo não existir ele será criado e
    //e fopen é responsável fazer com que o ponteiro aponte para um arquivo no programa
    verificadorArquivo(arquivo);
    char op;
    int aux = 0;
    aux = contadorCod();
    system("cls");
    fflush(stdin);
    menuCIMA(strlen("Codigo do Livro: ") + 15);
    menuOPCAO("Codigo do livro: ", strlen("Codigo do livro: ") + 15);
    gotoXY(0, 2);
    menuBAIXO(strlen("Codigo do livro: ") + 15);
    gotoXY(22, 1);
    aux = aux + cod_livro;
    printf("%d\n\n", aux);
    livros.codigo = aux;
    system("pause");
    system("cls");
    fflush(stdin);
    menuCIMA(strlen("Area do Livro: ") + 30);
    menuOPCAO("Area do livro: ", strlen("Area do livro: ") + 30);
    gotoXY(0, 2);
    menuBAIXO(strlen("Area do livro: ") + 30);
    gotoXY(17, 1);
    scanf("%s", &livros.area);
    strupr(livros.area);
    system("cls");
    fflush(stdin);
    menuCIMA(strlen("Digite o Nome do livro: ") + 50);
    menuOPCAO("Digite o Nome do livro: ", strlen("Digite o Nome do livro: ") + 50);
    gotoXY(0, 2);
    menuBAIXO(strlen("Digite o Nome do livro: ") + 50);
    gotoXY(26, 1);
    gets(livros.nome_livro);
    strupr(livros.nome_livro); //Converte o conteúdo digitado em maiúsculo.
    fflush(stdin);
    system("cls");
    menuCIMA(strlen("Digite o Nome do Autor do livro: ") + 30);
    menuOPCAO("Digite o Nome do Autor do livro: ", strlen("Digite o Nome do Autor do livro: ") + 30);
    gotoXY(0, 2);
    menuBAIXO(strlen("Digite o Nome do Autor do livro: ") + 30);
    gotoXY(35, 1);
    gets(livros.nome_autor);
    strupr(livros.nome_autor);//Converte o conteúdo digitado em maiúsculo.
    system("cls");
    do {
        fflush(stdin);
        menuCIMA(strlen("Quantidade de Livros: ") + 10);
        menuOPCAO("Quantidade de Livros: ", strlen("Quantidade de Livros: ") + 10);
        gotoXY(0, 2);
        menuBAIXO(strlen("Quantidade de Livros: ") + 10);
        gotoXY(24, 1);
        scanf("%d", &livros.quantidade);
    } while(livros.quantidade <= 0);
    fwrite(&livros, sizeof(CAD_LIVROS), 1, arquivo); // o numero 1 representa a quantidade de elementos que desejo gravar na struct
    //SIZEOF passa para a função o tamanho em bytes da struct
    system("cls");
    gotoXY(0, 2);
    printf("\n\n  Livro gravado com sucesso!\n\n");
    gotoXY(22, 1);
    system("pause");
    fclose(arquivo); //Fecha o arquivo que foi aberto.
    system("cls");
}

void editarLivros() {
    int op = 0;
    menuCIMA(42);
    menuOPCAO("         PROCURAR LIVROS PARA EDITAR", 42);
    menuBAIXO(42);
    do {
        printf("\n 1 - Procurar Por Codigo do livro ");
        printf("\n 2 - Sair");
        printf("\n Opcao: ");
        scanf("%d", &op);
        setbuf(stdin, NULL);
        system("cls");
        switch(op) {
        case 1:
            procurarLivros();
            break;
        case 2:
            return;
            break;
        default:
            system("cls");
            printf("\n\n  Opcao invalida\n");
            system("pause");
            break;
        }
    } while(op != 2);
}

void listarLivros() {
    int x = 0;
    FILE *arquivo;
    arquivo = fopen("cad_livros.txt", "rb");
    CAD_LIVROS livros;
    menuCIMA(29);
    menuOPCAO("     LISTAGEM DE LIVROS", 29);
    menuBAIXO(29);
    while(fread(&livros, sizeof(CAD_LIVROS), 1,arquivo)==1) {
        printf("\n Codigo do Livro: %d\n", livros.codigo);
        printf("\n Nome do Livro: %s\n", livros.nome_livro);
        printf("\n Nome do Autor do Livro: %s\n", livros.nome_autor);
        printf("\n Area que o Livro se encaixa: %s\n", livros.area);
        printf("\n Quantidade de Livros no Acervo: %d\n", livros.quantidade);
        printf("\n ---------------------------------------------\n");
        x++;
    }
    if(x == 0) {
        printf("\n\n  LISTA VAZIA!\n\n\n");
    }
    menuCIMA(31);
    menuOPCAO("   FIM DA LISTAGEM DE LIVROS", 31);
    menuBAIXO(31);
    system("pause");
    system("cls");
    fclose(arquivo);
}

void procurarLivros() {
    CAD_LIVROS livros;
    //variavel para contar a posição
    int i=0, op=0;
    //variavel para salvar o que o usuario digitar e comparar com os que está no arquivo
    int auxiliar;
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo = fopen("cad_livros.txt", "r+b");
    if(arquivo == NULL) {
        printf("\n Impossivel Abrir o arquivo!\n");
    } else {
        fflush(stdin);
        menuCIMA(57);
        menuOPCAO("Digite o Codigo do Livro que Deseja Procurar: ", 57);
        menuBAIXO(57);
        gotoXY(48, 1);
        scanf("%d", &auxiliar);
        system("cls");
        //lê todos os dados do arquivo até encontrar o final do arquivo (EOF)
        while(fread(&livros, sizeof(CAD_LIVROS), 1,arquivo)==1) {
            i++;
            //comparar a cpf que o usuario digitou com os que ja estão no arquivo
            if(auxiliar == livros.codigo) {
                menuCIMA(32);
                menuOPCAO("         DADOS ATUAIS         ", 32);
                menuBAIXO(32);
                printf("\n Codigo do livro: %d", livros.codigo);
                printf("\n Nome do livro: %s", livros.nome_livro);
                printf("\n Nome do Autor do Livro: %s", livros.nome_autor );
                printf("\n Area de Conhecimento do Livro: %s", livros.area );
                printf("\n Quantidade de Livros: %d\n\n", livros.quantidade);
                menuCIMA(32);
                menuOPCAO("O que voce deseja alterar ?", 32);
                menuBAIXO(32);
                printf("\n 1 - Nome do Livro");
                printf("\n 2 - Nome do Autor do Livro");
                printf("\n 3 - Area de Conhecimento do Livro");
                printf("\n 4 - Quantidade de Livros");
                printf("\n 5 - Sair\n");
                menuCIMA(10);
                menuOPCAO(" OPCAO: ", 10);
                menuBAIXO(10);
                gotoXY(10, 20);
                scanf("%d", &op);
                system("cls");
                switch(op) {
                case 1:
                    fflush(stdin);
                    menuCIMA(strlen("Digite o Novo Nome do Livro: ") + 30);
                    menuOPCAO("Digite o Novo Nome do Livro: ", strlen("Digite o Novo Nome do Livro: ") + 30);
                    gotoXY(0, 2);
                    menuBAIXO(strlen("Digite o Novo Nome do Livro: ") + 30);
                    gotoXY(strlen("Digite o Novo Nome do Livro:   "), 1);
                    fgets(livros.nome_livro, 50, stdin);
                    //O novo campo que foi digitado vai receber um \0 para indicar o fim
                    livros.nome_livro[strlen(livros.nome_livro) - 1]= '\0';
                    strupr(livros.nome_livro);
                    break;
                case 2:
                    fflush(stdin);
                    menuCIMA(strlen("Digite o Novo Nome do Autor do Livro: ") + 30);
                    menuOPCAO("Digite o Novo Nome do Autor do Livro: ", strlen("Digite o Novo Nome do Autor do Livro: ") + 30);
                    gotoXY(0, 2);
                    menuBAIXO(strlen("Digite o Novo Nome do Autor do Livro: ") + 30);
                    gotoXY(strlen("Digite o Novo Nome do Autor do Livro:   "), 1);
                    fgets(livros.nome_autor, 50, stdin);
                    //O novo campo que foi digitado vai receber um \0 para indicar o fim
                    livros.nome_autor[strlen(livros.nome_autor) - 1]= '\0';
                    strupr(livros.nome_autor);
                    break;
                case 3:
                    fflush(stdin);
                    menuCIMA(strlen("Digite a Nova Area de Conhecimento do Livro: ") + 30);
                    menuOPCAO("Digite a Nova Area de Conhecimento do Livro: ", strlen("Digite a Nova Area de Conhecimento do Livro: ") + 30);
                    gotoXY(0, 2);
                    menuBAIXO(strlen("Digite a Nova Area de Conhecimento do Livro: ") + 30);
                    gotoXY(strlen("Digite a Nova Area de Conhecimento do Livro:   "), 1);
                    fgets(livros.nome_livro, 50, stdin);
                    //O novo campo que foi digitado vai receber um \0 para indicar o fim
                    livros.area[strlen(livros.area) - 1]= '\0';
                    strupr(livros.area);

                    break;
                case 4:
                    fflush(stdin);
                    menuCIMA(strlen("Digite a Nova Quantidade de Livros: ") + 20);
                    menuOPCAO("Digite a Nova Quantidade de Livros: ", strlen("Digite a Nova Quantidade de Livros: ") + 20);
                    gotoXY(0, 2);
                    menuBAIXO(strlen("Digite a Nova Quantidade de Livros: ") + 20);
                    gotoXY(strlen("Digite a Nova Quantidade de Livros:   "), 1);
                    scanf("%d", &livros.quantidade);
                    break;
                case 5:
                    break;
                default:
                    printf("Opcao Incorreta!\n");
                }
                fseek(arquivo,(i-1)*sizeof(CAD_LIVROS),SEEK_SET);
                if(fwrite(&livros,sizeof(CAD_LIVROS), 1, arquivo) != 1) {
                    printf("\n Falha ao Alterar o registro!\n");
                    system("pause");
                } else {
                    printf("\n Registro alterado com sucesso!\n");
                }
                break;
            }
        }
    }
    menuCIMA(32);
    menuOPCAO("         FIM DA EDICAO         ", 32);
    menuBAIXO(32);
    system("pause");
    system("cls");
    fclose(arquivo);
}

void excluirLivros() {
    CAD_LIVROS li;
    int i = 0;
    char auxiliar[12];
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo = fopen("cad_livros.txt", "r+b");
    FILE *arq_auxiliar = fopen("auxiliar.txt", "w+b");
    if(arquivo == NULL || arq_auxiliar == NULL) {
        printf("\n\n  Impossivel Abrir o arquivo!\n");
    } else {
        fflush(stdin);
        menuCIMA(60);
        menuOPCAO("Digite o Nome do Livro que Deseja Excluir:    ", 60);
        menuBAIXO(60);
        gotoXY(47, 1);
        gets(auxiliar);
        strupr(auxiliar);
        while(fread(&li, sizeof(CAD_LIVROS), 1,arquivo)==1) {
            i++;
            if(strcmp(auxiliar, li.nome_livro) == 0) {
                fseek(arquivo,(i-1) * sizeof(CAD_LIVROS), SEEK_SET);
            } else {
                fwrite( &li, sizeof(CAD_LIVROS), 1, arq_auxiliar);
            }
        }
        if(remove("cad_livros.txt")==0) {
            menuCIMA(60);
            menuOPCAO("         Livro excluido com Sucesso", 60);
            menuBAIXO(60);
        } else {
            menuCIMA(60);
            menuOPCAO("         Nao foi possivel excluir o Livro         ", 60);
            menuBAIXO(60);
            printf("\n\n%s\n\n", strerror(errno));
        }
        rename("auxiliar.txt", "cad_livros.txt");
        system("pause");
        system("cls");
        fclose(arquivo);
        fclose(arq_auxiliar);
    }
    system("pause");
    system("cls");
    fclose(arquivo);
    fclose(arq_auxiliar);
}

int menuAcervo() {
    menuCIMA(40);
    printf(" %c                 LIVROS                 %c\n", 186, 186);
    menuOPCAO("", 40);
    menuOPCAO(" 1 - Cadastrar livro", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 2 - Remover livro", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 3 - Editar livro", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 4 - Listar livros Cadastrados", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 5 - Ir para menu anterior", 40);
    menuOPCAO("", 40);
    menuBAIXO(40);
    menuCIMA(10);
    menuOPCAO(" OPCAO: ", 10);
    menuBAIXO(10);
    gotoXY(10, 15);
}

