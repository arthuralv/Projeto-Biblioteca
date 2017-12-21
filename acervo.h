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
}CAD_LIVROS;


void cadastrar_livro(){
    system("cls");
    FILE* arquivo; //FILE (sempre maiuscula), variável do tipo file (arquivo é o nome do ponteiro), nesta linha está sendo criado o ponteiro
    CAD_LIVROS livros;
    arquivo = fopen ("cad_livros.txt", "ab");// "ab" acrescenta dados binários no fim do arquivo e se o arquivo não existir ele será criado e
    //e fopen é responsável fazer com que o ponteiro aponte para um arquivo no programa
    verificadorArquivo(arquivo);
    char op;

    do {
        cod_livro++;
        system("cls");
        fflush(stdin);
        menuCIMA(strlen("Codigo do Livro: ")+10);
        menuOPCAO("Codigo do livro: ", strlen("Codigo do livro: ")+10);
        gotoXY(0, 2);
        menuBAIXO(strlen("Codigo do livro: ")+10);
        gotoXY(22, 1);
        printf("%d\n\n", cod_livro);
        livros.codigo = cod_livro;
        system("pause");
        system("cls");
        fflush(stdin);
        menuCIMA(strlen("Area do Livro: ")+10);
        menuOPCAO("Area do livro: ", strlen("Area do livro: ")+10);
        gotoXY(0, 2);
        menuBAIXO(strlen("Area do livro: ")+10);
        gotoXY(22, 1);
        scanf("%s", &livros.area);
        strupr(livros.area);
        system("cls");
        fflush(stdin);
        menuCIMA(strlen("Digite o Nome do livro: ")+50);
        menuOPCAO("Digite o Nome do livro: ", strlen("Digite o Nome do livro: ")+50);
        gotoXY(0, 2);
        menuBAIXO(strlen("Digite o Nome do livro: ")+50);
        gotoXY(26, 1);
        gets(livros.nome_livro);
        strupr(livros.nome_livro); //Converte o conteúdo digitado em maiúsculo.
        fflush(stdin);
        system("cls");
        menuCIMA(strlen("Digite o Nome do Autor do livro: ")+15);
        menuOPCAO("Digite o Nome do Autor do livro: ", strlen("Digite o Nome do Autor do livro: ")+15);
        gotoXY(0, 2);
        menuBAIXO(strlen("Digite o Nome do Autor do livro: ")+15);
        gotoXY(25, 1);
        gets(livros.nome_autor);
        strupr(livros.nome_autor);//Converte o conteúdo digitado em maiúsculo.
        system("cls");
        fflush(stdin);
        menuCIMA(strlen("Quantidade de Livros: ")+10);
        menuOPCAO("Quantidade de Livros: ", strlen("Quantidade de Livros: ")+10);
        gotoXY(0, 2);
        menuBAIXO(strlen("Quantidade de Livros: ")+10);
        gotoXY(22, 1);
        scanf("%d", &livros.quantidade);
        fwrite(&livros, sizeof(CAD_LIVROS), 1, arquivo); // o numero 1 representa a quantidade de elementos que desejo gravar na struct
        //SIZEOF passa para a função o tamanho em bytes da struct
        system("cls");
        menuCIMA(strlen("Livro gravado com sucesso!"));
        menuOPCAO("\nLivro gravado com sucesso!\n", strlen("Livro gravado com sucesso!"));
        gotoXY(0, 2);
        menuBAIXO(strlen("Livro gravado com sucesso!"));
        gotoXY(22, 1);
        system("cls");
        menuCIMA(strlen("Deseja Continuar e Inserir um Novo Livro (S/N)?  "));
        menuOPCAO("Deseja Continuar e Inserir um Novo Livro (S/N)?  ", strlen("Deseja Continuar e Inserir um Novo Livro (S/N)? "));
        gotoXY(0, 2);
        menuBAIXO(strlen("Deseja Continuar e Inserir um Novo Livro (S/N)?  "));
        menuCIMA(10);
        menuOPCAO(" OPCAO: ", 10);
        menuBAIXO(10);
        gotoXY(10, 4);
        setbuf(stdin, NULL);
        op = getchar();
        op = toupper(op);
        system("cls");
        while(op != 'S' && op != 'N') {
            system("cls");
            menuCIMA(strlen("Opcao invalida, digite novamente!"));
            menuOPCAO("Opcao invalida, digite novamente!", strlen("Opcao invalida, digite novamente!"));
            gotoXY(0, 2);
            menuBAIXO(strlen("Opcao invalida, digite novamente!"));
            gotoXY(22, 1);
            printf("\n\n");
            system("pause");
            system("cls");
            menuCIMA(strlen("Deseja Continuar e Inserir um Novo Livro (S/N)?  "));
            menuOPCAO("Deseja Continuar e Inserir um Novo Livro (S/N)?  ", strlen("Deseja Continuar e Inserir um Novo Livro (S/N)? "));
            gotoXY(0, 2);
            menuBAIXO(strlen("Deseja Continuar e Inserir um Novo Livro (S/N)?  "));
            menuCIMA(10);
            menuOPCAO(" OPCAO: ", 10);
            menuBAIXO(10);
            gotoXY(10, 4);
            setbuf(stdin, NULL);
            op = getchar();
            op = toupper(op);
            system("cls");
        }
    } while(op == 'S');

    fclose(arquivo); //Fecha o arquivo que foi aberto.
    system("cls");
}
void editar_livro(){
    int op=0;

    printf("---------PROCURAR ALUNO PARA EDITAR-----------");
    do{
        printf("\n1 - Procurar Por Nome do livro ");
        printf("\n2 - Sair");
        printf("\nOpcao: ");
        scanf("%d", &op);
        system("cls");
        switch(op){
            case 1:
                procurar_livro();
                break;
            case 2:
                printf("Saindo...\n");
                Sleep(1000);
                break;
            default:
                printf("\nOpcao invalida\n");
                break;
        }
    }while(op != 2);
}
void listarlivros() {

    FILE *arquivo;
    arquivo = fopen("cad_livros.txt", "rb");
    CAD_LIVROS livros;
    verificadorArquivo(arquivo);
    printf("\n---------------LISTAGEM DE LIVROS-------------\n\n");
    while(fread(&livros, sizeof(CAD_LIVROS), 1,arquivo)==1) {
        printf("\nCodigo do Livro: %d\n", livros.codigo);
        printf("\nNome do Livro: %s\n", livros.nome_livro);
        printf("\nNome do Autor do Livro: %s\n", livros.nome_autor);
        printf("\nArea que o Livro se encaixa: %s\n", livros.area);
        printf("\nQuantidade de Livros no Acervo: %d\n\n\n\n", livros.quantidade);
        system("pause");

    }

    printf("\n--------------- FIM DA LISTAGEM DE LIVROS-------------\n\n");
    system("pause");
    system("cls");
}
void procurar_livro(){
    CAD_LIVROS livros;
    //variavel para contar a posição
    int i=0, op=0;
    //variavel para salvar o que o usuario digitar e comparar com os que está no arquivo
    char auxiliar[11];
    printf("\n---------------PROCURAR LIVROS POR NOME-------------\n\n");
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo = fopen("cad_livros.txt", "r+b");
    if(arquivo == NULL){
        printf("\n Impossivel Abrir o arquivo!\n");
        }
    else{
            fflush(stdin);
            printf("\nDigite o Nome do Livro que deseja procurar: ");
            gets(auxiliar);
            strupr(auxiliar);
            system("cls");
            //lê todos os dados do arquivo até encontrar o final do arquivo (EOF)
            while(fread(&livros, sizeof(CAD_LIVROS), 1,arquivo)==1){
                 i++;
                 //comparar a cpf que o usuario digitou com os que ja estão no arquivo
                 if(strcmp(auxiliar, livros.nome_livro) == 0){
                        printf("---------Dados Atuais---------\n");
                        printf("\nCodigo do livro: %d", livros.codigo);
                        printf("\nNome do livro: %s", livros.nome_livro);
                        printf("\nNome do Autor do Livro: %s",livros.nome_autor );
                        printf("\nArea de Conhecimento do Livro: %s",livros.area );
                        printf("\nQuantidade de Livros: %d\n\n", livros.quantidade);

                            printf("O QUE VOCE DESEJA ALTERAR ?\n");
                            printf("\n1 - Nome do Livro");
                            printf("\n2 - Nome do Autor do Livro");
                            printf("\n3 - Area de Conhecimento do Livro");
                            printf("\n4 - Quantidade de Livros");
                            printf("\n5 - Sair\n");
                            printf("Escolha uma opcao: ");
                            scanf("%d", &op);
                            system("cls");
                            switch(op){
                                case 1:
                                    fflush(stdin);
                                    printf("\nDigite o Novo Nome do Livro: ");
                                    fgets(livros.nome_livro, 50, stdin);
                                   //O novo campo que foi digitado vai receber um \0 para indicar o fim
                                    livros.nome_livro[strlen(livros.nome_livro)-1]= '\0';
                                    strupr(livros.nome_livro);
                                    break;
                                case 2:
                                    fflush(stdin);
                                    printf("\nDigite o Novo Nome do Autor do Livro: ");
                                    fgets(livros.nome_autor, 50, stdin);
                                    //O novo campo que foi digitado vai receber um \0 para indicar o fim
                                    livros.nome_autor[strlen(livros.nome_autor)-1]= '\0';
                                    strupr(livros.nome_autor);
                                    break;
                                case 3:
                                    fflush(stdin);
                                    printf("\nDigite a Nova Area de Conhecimento do Livro: ");
                                    fgets(livros.nome_livro, 50, stdin);
                                    //O novo campo que foi digitado vai receber um \0 para indicar o fim
                                    livros.area[strlen(livros.area)-1]= '\0';
                                    strupr(livros.area);

                                    break;
                                case 4:
                                    fflush(stdin);
                                    printf("\nDigite a Nova Quantidade de Livros: ");
                                    scanf("%d", &livros.quantidade);
                                    break;
                                case 5:
                                    printf("Saindo...\n");
                                    Sleep(1000);
                                    break;
                                default:
                                    printf("Opcao Incorreta!\n");
                            }
                        fseek(arquivo,(i-1)*sizeof(CAD_LIVROS),SEEK_SET);
                    if(fwrite(&livros,sizeof(CAD_LIVROS),1,arquivo) != 1){
                                printf("\n Falha ao Alterar o registro!\n");
                                system("pause");
                    }else{
                                printf("\n Registro alterado com sucesso!\n");
                            }
                            break;
                        }
                    }
    }
    printf("\n\n---------Fim da Edição---------n\n");
	system("pause");
	system("cls");
	fclose(arquivo);
}
void editar_livros () {
    int op=0;

    printf("---------PROCURAR LIVRO PARA EDITAR-----------");
    do {
        printf("\n1 - Procurar Por NOME ");
        printf("\n2 - Sair");
        printf("\nOpcao: ");
        scanf("%d", &op);
        system("cls");
        switch(op) {
        case 1:
            procurar_livro();
            break;
        case 2:
            printf("Saindo...\n");
            Sleep(1000);
            break;
        default:
            printf("\nOpcao invalida\n");
            break;
        }
    } while(op != 2);
}
void excluir_livro(){
    CAD_LIVROS li;
    int i=0;
    char auxiliar[11];
    printf("\n---------------EXLUINDO LIVROS-------------\n\n");
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo = fopen("cad_livros.txt", "r+b");
    FILE *arq_auxiliar = fopen("auxiliar.txt", "w+b");
    if(arquivo == NULL || arq_auxiliar == NULL){
        printf("\n Impossivel Abrir o arquivo!\n");
        }
    else{
            fflush(stdin);
            printf("\nDigite o Nome do Livro que Deseja Excluir: ");
            gets(auxiliar);

            while(fread(&li, sizeof(CAD_LIVROS), 1,arquivo)==1){
                 i++;
                 if(strcmp(auxiliar, li.nome_livro) == 0){
                        li.nome_livro[sizeof(li.nome_livro)-1] = '\0';
                        li.nome_autor[sizeof(li.nome_autor)-1] = '\0';
                        li.area[sizeof(li.area)-1] = '\0';
                        li.quantidade = 0;
                        fseek(arquivo,(i-1)*sizeof(CAD_LIVROS),SEEK_SET);
                 }else{
                    fwrite(&li,sizeof(CAD_LIVROS),1,arq_auxiliar);
                 }
            }
    printf("\n\n---------------Livro Excluido com sucesso---------------n\n");
	system("pause");
	system("cls");
	fclose(arquivo);
	fclose(arq_auxiliar);
	remove("cad_livros.txt");
    rename("auxiliar.txt", "cad_livros.txt");
    }
}

//Função para verificar que opção vai ser usada no menu livro
void op_acervo () {
    int o=0;
    struct livro li;
    do{
    menuAcervo();
    scanf("%d", &o);
        system("cls");
        switch(o) {
        case 1:
            cadastrar_livro();
            Sleep(1000);
            break;
        case 2:
            excluir_livro();
            Sleep(1000);
            break;
        case 3:
            editar_livro();
            Sleep(1000);
            break;
        case 4:
            listarlivros(li);
            Sleep(1000);
            break;
        case 5:
            Sleep(1000);
            return;
        default:
            printf("Opção invalida\n");
            break;
        }
        fflush(stdin);
    }while(o != 5);
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

