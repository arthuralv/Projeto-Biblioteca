#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

int mat = 100;
//Estrutura para o cadastro de alunos
typedef struct alunos {
    int matricula;
    char nome[50];
    char cpf[12];
} CAD_ALUNOS;

void verificadorArquivo(FILE* arquivo);
void alterarAlunos();
void cadastrarAlunos();
void listarAlunos();
void editarAlunos();
void excluirAlunos();

void op_alunos () {
    int o = 0;
    struct alunos al;
    do {
        menuAluno();
        scanf("%d", &o);
        system("cls");
        switch(o) {
        case 1:
            cadastrarAlunos();
            break;
        case 2:
            excluirAlunos();
            break;
        case 3:
            editarAlunos();
            break;
        case 4:
            listarAlunos(al);
            break;
        case 5:
            return;
        default:
            printf("Opção invalida\n");
            break;
        }
        fflush(stdin);
    } while(o != 5);
}

int contadorMat() {
    int aux = 0;
    FILE *arquivo;
    arquivo = fopen("cad_alunos.txt", "rb");
    CAD_ALUNOS al;
    verificadorArquivo(arquivo);
    while(fread(&al, sizeof(CAD_ALUNOS), 1, arquivo) == 1) {
        aux++;
    }
    fclose(arquivo);
    return aux;
}

int verificarCpf(char cpf[12]) {
    int i=0;
    FILE *arquivo;
    arquivo = fopen("cad_alunos.txt", "rb");
    verificadorArquivo(arquivo);
    CAD_ALUNOS al;
    while(fread(&al,sizeof(CAD_ALUNOS), 1, arquivo) == 1) {
        if(strcmp(cpf, al.cpf ) == 0) {
            fclose(arquivo);
            return 1;
        }
    }
    system("cls");
    fclose(arquivo);
}

void cadastrarAlunos() {
    system("cls");
    int aux = 0, x=0;
    char cpf[12];
    FILE *arquivo; //FILE (sempre maiuscula), variável do tipo file (arquivo é o nome do ponteiro), nesta linha está sendo criado o ponteiro
    FILE *arq;
    CAD_ALUNOS al;
    arquivo = fopen ("cad_alunos.txt", "ab");// "ab" acrescenta dados binários no fim do arquivo e se o arquivo não existir ele será criado e
    //e fopen é responsável fazer com que o ponteiro aponte para um arquivo no programa
    arq = fopen("cad_alunos.txt", "rb");
    verificadorArquivo(arq);
    verificadorArquivo(arquivo);
    char op;
    aux = contadorMat();
    system("cls");
    fflush(stdin);
    menuCIMA(strlen("Matricula do Aluno: ")+10);
    menuOPCAO("Matricula do Aluno: ", strlen("Matricula do Aluno: ")+10);
    gotoXY(0, 2);
    menuBAIXO(strlen("Matricula do Aluno: ")+10);
    gotoXY(22, 1);
    aux = aux + mat;
    printf("%d\n\n", aux);
    al.matricula = aux;
    system("pause");
    system("cls");
    fflush(stdin);
    menuCIMA(strlen("Digite o Nome do Aluno: ")+50);
    menuOPCAO("Digite o Nome do Aluno: ", strlen("Digite o Nome do Aluno: ")+50);
    gotoXY(0, 2);
    menuBAIXO(strlen("Digite o Nome do Aluno: ")+50);
    gotoXY(26, 1);
    gets(al.nome);
    strupr(al.nome); //Converte o conteúdo digitado em maiúsculo.
    fflush(stdin);
    system("cls");
    menuCIMA(strlen("Digite o CPF do Aluno: ")+15);
    menuOPCAO("Digite o CPF do Aluno: ", strlen("Digite o CPF do Aluno: ")+15);
    gotoXY(0, 2);
    menuBAIXO(strlen("Digite o CPF do Aluno: ")+15);
    gotoXY(25, 1);
    gets(al.cpf);
    strupr(al.cpf);//Converte o conteúdo digitado em maiúsculo.
    x = verificarCpf(al.cpf);
    if(x == 1) {
        system("cls");
        printf("\n\n  CPF ja cadastrado!\n\n");
        system("pause");
        fclose(arquivo); //Fecha o arquivo que foi aberto.
        fclose(arq);
        system("cls");
        return;
    } else {
        fwrite(&al, sizeof(CAD_ALUNOS), 1, arquivo);
    }
    // o numero 1 representa a quantidade de elementos que desejo gravar na struct
    //SIZEOF passa para a função o tamanho em bytes da struct
    system("cls");
    menuCIMA(strlen("Registro gravado com sucesso!"));
    menuOPCAO("Registro gravado com sucesso!", strlen("Registro gravado com sucesso!"));
    gotoXY(0, 2);
    menuBAIXO(strlen("Registro gravado com sucesso!"));
    gotoXY(2, 3);
    system("pause");
    fclose(arquivo); //Fecha o arquivo que foi aberto.
    fclose(arq);
    system("cls");
}

void listarAlunos() {
    int x = 0;
    FILE *arquivo;
    arquivo = fopen("cad_alunos.txt", "rb");
    CAD_ALUNOS al;
    menuCIMA(29);
    menuOPCAO("     LISTAGEM DE ALUNOS", 29);
    menuBAIXO(29);
    while(fread(&al, sizeof(CAD_ALUNOS), 1,arquivo)==1) {
        printf("\n Matricula: %d\n", al.matricula);
        printf("\n Nome: %s\n", al.nome);
        printf("\n CPF: %s\n\n", al.cpf);
        printf(" ---------------------------------------------\n");
        x++;
    }
    if(x == 0) {
        printf("\n\n  LISTA VAZIA!\n\n\n");
    }
    menuCIMA(31);
    menuOPCAO("   FIM DA LISTAGEM DE ALUNOS", 31);
    menuBAIXO(31);
    system("pause");
    system("cls");
    fclose(arquivo);
}

void editarAlunos() {
    int op = 0;
    do {
        system("cls");
        menuCIMA(29);
        menuOPCAO("     LISTAGEM DE ALUNOS", 29);
        menuOPCAO("", 29);
        menuOPCAO(" 1 - Procurar Por CPF ", 29);
        menuOPCAO("", 29);
        menuOPCAO(" 2 - Sair", 29);
        menuBAIXO(29);
        menuCIMA(10);
        menuOPCAO(" OPCAO: ", 10);
        menuBAIXO(10);
        gotoXY(10, 8);
        scanf("%d", &op);
        system("cls");
        switch(op) {
        case 1:
            alterarAlunos();
            break;
        case 2:
            break;
        default:
            printf("\n\n  Opcao invalida\n");
            system("pause");
            break;
        }
    } while(op != 2);
}

void alterarAlunos() {
    CAD_ALUNOS al;
    //variavel para contar a posição
    int i = 0;
    //variavel para salvar o que o usuario digitar e comparar com os que está no arquivo
    char auxiliar[12];
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo = fopen("cad_alunos.txt", "r+b");
    verificadorArquivo(arquivo);
    fflush(stdin);
    system("cls");
    menuCIMA(50);
    menuOPCAO("Digite o CPF que deseja editar: ", 50);
    menuBAIXO(50);
    gotoXY(35, 1);
    gets(auxiliar);
    //lê todos os dados do arquivo até encontrar o final do arquivo (EOF)
    while(fread(&al, sizeof(CAD_ALUNOS), 1,arquivo)==1) {
        //comparar a cpf que o usuario digitou com os que ja estão no arquivo
        if(strcmp(auxiliar, al.cpf) == 0) {
            printf("\n\n");
            menuCIMA(32);
            menuOPCAO("         Dados Atuais         ", 32);
            menuBAIXO(32);
            printf("\n Nome do Aluno: %s", al.nome);
            printf("\n Matricula do Aluno: %d", al.matricula);
            printf("\n CPF Atual: %s\n",al.cpf );
            printf("\n\n Digite o Novo CPF: ");
            fflush(stdin);
            fgets(al.cpf, 12, stdin);
            //O novo cpf que foi digitado vai receber um \0 para indicar o fim
            al.cpf[strlen(al.cpf) - 1]= '\0';
            printf("\n Digite o Novo Nome: ");
            fflush(stdin);
            fgets(al.nome, 50, stdin);
            strupr(al.nome);
            //O novo nome que foi digitado vai receber um \0 para indicar o fim
            al.nome[strlen(al.nome) - 1] = '\0';
            //vou para a posicao no arquivo que eu quero incluir os novos dados
            fseek(arquivo, i * sizeof(CAD_ALUNOS),SEEK_SET);
            //inscrevo os novos dados e verifico se foi feito com sucesso
            if(fwrite(&al,sizeof(CAD_ALUNOS), 1 , arquivo) != 1) {
                system("cls");
                printf("\n\n\n\n Falha ao Alterar o registro!\n");
                 system("cls");
                 fclose(arquivo);
                 return;
            } else {
                system("cls");
                printf("\n\n\n\n Registro alterado com sucesso!\n");
            }
            i++;
            break;
        }
    }
    if( i == 0 ){
        system("cls");
        printf("\n\n Nao ha registro com tal CPF!\n\n");

    }
    system("pause");
    system("cls");
    fclose(arquivo);
}

void excluirAlunos() {
    CAD_ALUNOS al;
    int i = 0, j = 0;
    char auxiliar[12];
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo = fopen("cad_alunos.txt", "a+b");
    FILE *arq_auxiliar = fopen("auxiliar.txt", "w+b");
    if(arquivo == NULL || arq_auxiliar == NULL) {
        printf("\n Impossivel Abrir o arquivo!\n");
    } else {
        fflush(stdin);
        menuCIMA(50);
        menuOPCAO("Digite o CPF que deseja excluir: ", 50);
        menuBAIXO(50);
        gotoXY(35, 1);
        gets(auxiliar);
        while(fread(&al, sizeof(CAD_ALUNOS), 1, arquivo) == 1) {
            i++;
            if(strcmp(auxiliar, al.cpf) == 0) {
                al.cpf[strlen(al.cpf) - 1] = '\0';
                al.nome[strlen(al.nome) - 1] = '\0';
                fseek(arquivo,(i - 1) * sizeof(CAD_ALUNOS),SEEK_SET);
                j++;
            } else {
                fwrite(&al,sizeof(CAD_ALUNOS), 1, arq_auxiliar);
            }
        }
        fclose(arquivo);
        fclose(arq_auxiliar);
        system("cls");
        if(j > 0) {
            printf("\n\n  Registro encontrado!\n\n");
            system("pause");
        } else {

            printf("\n\n  Nao ha registro com esse CPF!\n\n");
            system("pause");
            system("cls");
            fclose(arquivo);
            fclose(arq_auxiliar);
            return;
        }
        system("cls");
        if(remove("cad_alunos.txt") == 0) {
            rename("auxiliar.txt", "cad_alunos.txt");
            putchar('\n');
            menuCIMA(40);
            menuOPCAO("    Registro excluido com Sucesso", 40);
            menuBAIXO(40);
            system("pause");
        } else {
            printf("\n\n  Nao foi Possivel Excluir o Cadastro!\n");
            printf("\n\n%s\n\n", strerror(errno));
            system("pause");
        }
        system("cls");
    }
    fclose(arquivo);
    fclose(arq_auxiliar);
}
//Função para verificar que opção vai ser usada no menu aluno

void verificadorArquivo(FILE *arquivo) {
    if(arquivo == NULL) {
        system("cls");
        printf("\n\n  Saindo do programa...");
        Sleep(100);
        exit(1);
    }
}

int menuAluno() {
    int o;
    menuCIMA(40);
    printf(" %c                 ALUNOS                 %c\n", 186, 186);
    menuOPCAO("", 40);
    menuOPCAO(" 1 - Cadastrar Aluno", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 2 - Remover Aluno", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 3 - Editar Aluno", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 4 - Listar Alunos Cadastrados", 40);
    menuOPCAO("", 40);
    menuOPCAO(" 5 - Ir para menu anterior", 40);
    menuOPCAO("", 40);
    menuBAIXO(40);
    menuCIMA(10);
    menuOPCAO(" OPCAO: ", 10);
    menuBAIXO(10);
    gotoXY(10, 15);

}
