#include <stdio.h>
#include <windows.h>
#include <dos.h>
#include <string.h>

int mat = 100;
//Estrutura para o cadastro de alunos
typedef struct alunos {
    int matricula;
    char nome[50];
    char cpf[11];
} CAD_ALUNOS;
//Função para gravar registro de funcionários.

void verificadorArquivo(FILE* arquivo);

void cadastrar() {
    system("cls");
    FILE* arquivo; //FILE (sempre maiuscula), variável do tipo file (arquivo é o nome do ponteiro), nesta linha está sendo criado o ponteiro
    CAD_ALUNOS al;
    arquivo = fopen ("cad_alunos.txt", "ab");// "ab" acrescenta dados binários no fim do arquivo e se o arquivo não existir ele será criado e
    //e fopen é responsável fazer com que o ponteiro aponte para um arquivo no programa
    verificadorArquivo(arquivo);
    char op;

    do {
        system("cls");
        fflush(stdin);
        printf("\nMatricula do Aluno: \n");
        scanf("%d", &al.matricula);
        fflush(stdin);
        printf("\nDigite o Nome do Aluno: \n");
        gets(al.nome);
        strupr(al.nome); //Converte o conteúdo digitado em maiúsculo.
        fflush(stdin);
        printf("\nDigite o CPF do Aluno: \n");
        gets(al.cpf);
        strupr(al.cpf);//Converte o conteúdo digitado em maiúsculo.
        fwrite(&al, sizeof(CAD_ALUNOS), 1, arquivo); // o numero 1 representa a quantidade de elementos que desejo gravar na struct
        //SIZEOF passa para a função o tamanho em bytes da struct
        printf("\n\nRegistro gravado com sucesso!\n\n");
        printf("\nDeseja Continuar e Inserir um Novo Registro (S/N)?\n");
        setbuf(stdin, NULL);
        op = getchar();
        op = toupper(op);
        system("cls");
        if(op != 'S' && op != 'N') {
            do {
                printf("Opção inválida. Digite novamente!\n");
                printf("\nDeseja Continuar e Inserir um Novo Registro (S/N)?\n");
                printf("Opção: ");
                setbuf(stdin, NULL);
                op = getchar();
                op = toupper(op);
                system("cls");
            } while(op != 'S' && op != 'N');
        }
    }while(op == 'S');
    fclose(arquivo); //Fecha o arquivo que foi aberto.
    system("cls");
}
void listaralunos() {

    FILE *arquivo;
    arquivo = fopen("cad_alunos.txt", "rb");
    CAD_ALUNOS al;
    verificadorArquivo(arquivo);
    printf("\n---------------LISTAGEM DE ALUNOS-------------\n\n");
    while(fread(&al, sizeof(CAD_ALUNOS), 1,arquivo)==1) {
        printf("\nMatricula: %d\n", al.matricula);
        printf("\nNome: %s\n", al.nome);
        printf("\nCPF: %s\n\n", al.cpf);
        system("pause");

    }

    printf("\n--------------- FIM DA LISTAGEM DE ALUNOS-------------\n\n");
    system("pause");
    system("cls");
}
void editar () {
    int op=0;

    printf("---------PROCURAR ALUNO PARA EDITAR-----------");
    do {
        printf("\n1 - Procurar Por CPF ");
        printf("\n2 - Sair");
        printf("\nOpcao: ");
        scanf("%d", &op);
        system("cls");
        switch(op) {
        case 1:
            pnome();
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
pnome() {
    CAD_ALUNOS al;
    char aux[255];
    printf("\n---------------PROCURAR ALUNOS POR NOME-------------\n\n");
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo;
    //Abrindo o arquivo criado e dando o nome cad_alunos para o arquivo
    //O "a+" é  para abrir salvar no final, e ler os dados do arquivo
    arquivo = fopen("cad_alunos.txt", "rb");
    //verificando se o arquivo foi aberto com exito
    if(arquivo == NULL) {
        printf("Impossivel Abrir Aquivo!");
    }
    else {
        fflush(stdin);
        printf("\nDigite o nome que deseja procurar: ");
        gets(aux);

        while(fread(&al, sizeof(CAD_ALUNOS), 1,arquivo) == 1) {
            if(strstr(aux, al.nome)) {
                printf("editar nome: ");
            }
        }
    }
    printf("\n\n***************Fim da Edição.***************\n\n");
    system("pause");
    system("cls");
}

//Função para verificar que opção vai ser usada no menu aluno
void op_alunos () {
    int o=0;
    struct alunos al;
    do {
        printf("\n---------------ALUNOS-------------\n\n");
        printf("-\t 1 Cadastrar Aluno\t\t\t-\n");
        printf("-\t 2 Remover Aluno\t\t\t-\n");
        printf("-\t 3 Editar Aluno\t\t\t-\n");
        printf("-\t 4 Listar Alunos Cadastrados\t\t\t-\n");
        printf("-\t 5 Ir para menu anterior\t\t\t-\n\n");
        scanf("%d", &o);
        system("cls");
        switch(o) {
        case 1:
            cadastrar();
            Sleep(1000);
        case 2:
            break;
        case 3:
            editar();
            Sleep(1000);
            break;
        case 4:
            listaralunos(al);
            Sleep(1000);
            break;
        case 5:
            Sleep(1000);
            menu_principal();
        default:
            printf("Opção invalida\n");
            break;
        }
        fflush(stdin);
    }
    while(o >= 5);
}
void verificadorArquivo(FILE *arquivo) {
    if(arquivo == NULL) {
        system("cls");
        printf("Ocorreu um erro no sistema. Por favor contate o fabricante! \n\n\n\n");
        printf("Saindo do programa...");
        Sleep(2000);
        exit(1);
    }
}
