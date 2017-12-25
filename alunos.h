#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

int mat = 100;
//Estrutura para o cadastro de alunos
typedef struct alunos {
    int matricula;
    char nome[50];
    char cpf[11];
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
    while(fread(&al, sizeof(CAD_ALUNOS), 1,arquivo) == 1){
        aux++;
    }
    fclose(arquivo);
    return aux;
}

int verificarCpf(char cpf[11]){
    int i=0;
    FILE *arquivo;
    arquivo = fopen("cad_alunos.txt", "rb");
    verificadorArquivo(arquivo);
    CAD_ALUNOS al;

    while(fread(&al,sizeof(CAD_ALUNOS), 1, arquivo)==1){
        if(strcmp(cpf, al.cpf )==0){
            return 1;
        }
    }
}

void cadastrarAlunos() {
    system("cls");
    int aux = 0, x=0;
    char cpf[11];
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
        if(x == 1){
            printf("CPF Ja cadastrado\n");
            system("pause");
            return;
        }else{
            fwrite(&al, sizeof(CAD_ALUNOS), 1, arquivo);
        }
         // o numero 1 representa a quantidade de elementos que desejo gravar na struct
        //SIZEOF passa para a função o tamanho em bytes da struct
        system("cls");
        menuCIMA(strlen("Registro gravado com sucesso!"));
        menuOPCAO("\nRegistro gravado com sucesso!\n", strlen("Registro gravado com sucesso!"));
        gotoXY(0, 2);
        menuBAIXO(strlen("Registro gravado com sucesso!\n"));
        gotoXY(22, 1);
        system("pause");

    fclose(arquivo); //Fecha o arquivo que foi aberto.
    fclose(arq);
    system("cls");
}

void listarAlunos() {

    FILE *arquivo;
    arquivo = fopen("cad_alunos.txt", "rb");
    CAD_ALUNOS al;
    verificadorArquivo(arquivo);
    menuCIMA(29);
    menuOPCAO("     LISTAGEM DE ALUNOS", 29);
    menuBAIXO(29);
    while(fread(&al, sizeof(CAD_ALUNOS), 1,arquivo)==1) {
        printf("\nMatricula: %d\n", al.matricula);
        printf("\nNome: %s\n", al.nome);
        printf("\nCPF: %s\n\n", al.cpf);
        printf("---------------------------------------------\n");
    }

    menuCIMA(31);
    menuOPCAO("   FIM DA LISTAGEM DE ALUNOS", 31);
    menuBAIXO(31);
    system("pause");
    system("cls");
}

void editarAlunos() {
    int op = 0;
    do {
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
            printf("\nOpcao invalida\n");
            system("pause");
            break;
        }
    } while(op != 2);
}

void alterarAlunos() {
    CAD_ALUNOS al;
    //variavel para contar a posição
    int i=0;
    //variavel para salvar o que o usuario digitar e comparar com os que está no arquivo
    char auxiliar[11];
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo = fopen("cad_alunos.txt", "r+b");
    if(arquivo == NULL) {
        printf("\n Impossivel Abrir o arquivo!\n");
    }
    else {
        fflush(stdin);
        menuCIMA(30);
        menuOPCAO("Digite o CPF que deseja procurar: ", 30);
        menuBAIXO(30);
        gets(auxiliar);
        //lê todos os dados do arquivo até encontrar o final do arquivo (EOF)
        while(fread(&al, sizeof(CAD_ALUNOS), 1,arquivo)==1) {
            i++;
            //comparar a cpf que o usuario digitou com os que ja estão no arquivo
            if(strcmp(auxiliar, al.cpf) == 0) {
                menuCIMA(32);
                menuOPCAO("         Dados Atuais         ", 32);
                menuBAIXO(32);
                printf("\nNome do Aluno: %s", al.nome);
                printf("\nMatricula do Aluno: %d", al.matricula);
                printf("\nCPF Atual: %s\n",al.cpf );
                printf("\nDigite o Novo CPF: ");
                fflush(stdin);
                fgets(al.cpf, 11, stdin);
                //O novo cpf que foi digitado vai receber um \0 para indicar o fim
                al.cpf[strlen(al.cpf) - 1]= '\0';
                printf("\nDigite o Novo Nome: ");
                fflush(stdin);
                fgets(al.nome, 50, stdin);
                //O novo nome que foi digitado vai receber um \0 para indicar o fim
                al.nome[strlen(al.nome) - 1] = '\0';
                //vou para a posicao no arquivo que eu quero incluir os novos dados
                fseek(arquivo,(i-1)*sizeof(CAD_ALUNOS),SEEK_SET);
                //inscrevo os novos dados e verifico se foi feito com sucesso
                if(fwrite(&al,sizeof(CAD_ALUNOS),1,arquivo) != 1) {
                    system("cls");
                    printf("\n Falha ao Alterar o registro!\n");
                    system("pause");
                } else {
                    system("cls");
                    printf("\n Registro alterado com sucesso!\n");
                    system("pause");
                }
                break;
            }
        }
    }
    menuCIMA(32);
    menuOPCAO("         Fim da Edicao         ", 32);
    menuBAIXO(32);
    system("pause");
    system("cls");
    fclose(arquivo);
}

void excluirAlunos() {
    CAD_ALUNOS al;
    int i = 0;
    char auxiliar[11];
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo = fopen("cad_alunos.txt", "a+b");
    FILE *arq_auxiliar = fopen("auxiliar.txt", "w+b");
    if(arquivo == NULL || arq_auxiliar == NULL) {
        printf("\n Impossivel Abrir o arquivo!\n");
    }
    else {
        fflush(stdin);
        printf("\nDigite o CPF que deseja excluir: ");
        gets(auxiliar);

        while(fread(&al, sizeof(CAD_ALUNOS), 1, arquivo) == 1) {
            i++;
            if(strcmp(auxiliar, al.cpf) == 0) {
                al.cpf[strlen(al.cpf) - 1] = '\0';
                al.nome[strlen(al.nome) - 1] = '\0';
                fseek(arquivo,(i - 1) * sizeof(CAD_ALUNOS),SEEK_SET);
            } else {
                fwrite(&al,sizeof(CAD_ALUNOS), 1, arq_auxiliar);
            }
        }
        fclose(arquivo);
        fclose(arq_auxiliar);
        if(remove("cad_alunos.txt") == 0){
            rename("auxiliar.txt", "cad_alunos.txt");
            printf("\n\n--------------- Registro excluido com sucesso ---------------\n");
            system("pause");
        }else{
            printf("Nao foi Possivel Excluir o Cadastro!\n");
            printf("\n\n%s\n\n", strerror(errno));
            system("pause");
        }
        system("cls");
    }
}
//Função para verificar que opção vai ser usada no menu aluno

void verificadorArquivo(FILE *arquivo) {
    if(arquivo == NULL) {
        system("cls");
        printf("Ocorreu um erro no sistema. Por favor contate o fabricante! \n\n\n\n");
        printf("Saindo do programa...");
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
