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
        menuCIMA(strlen("Matricula do Aluno: ")+10);
        menuOPCAO("Matricula do Aluno: ", strlen("Matricula do Aluno: ")+10);
        gotoXY(0, 2);
        menuBAIXO(strlen("Matricula do Aluno: ")+10);
        gotoXY(22, 1);
        scanf("%d", &al.matricula);
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
        fwrite(&al, sizeof(CAD_ALUNOS), 1, arquivo); // o numero 1 representa a quantidade de elementos que desejo gravar na struct
        //SIZEOF passa para a função o tamanho em bytes da struct
        system("cls");
        menuCIMA(strlen("Registro gravado com sucesso!"));
        menuOPCAO("\nRegistro gravado com sucesso!\n", strlen("Registro gravado com sucesso!"));
        gotoXY(0, 2);
        menuBAIXO(strlen("Registro gravado com sucesso!"));
        gotoXY(22, 1);
        system("cls");
        menuCIMA(strlen("Deseja Continuar e Inserir um Novo Registro (S/N)?  "));
        menuOPCAO("Deseja Continuar e Inserir um Novo Registro (S/N)?  ", strlen("Deseja Continuar e Inserir um Novo Registro (S/N)? "));
        gotoXY(0, 2);
        menuBAIXO(strlen("Deseja Continuar e Inserir um Novo Registro (S/N)?  "));
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
            menuCIMA(strlen("Deseja Continuar e Inserir um Novo Registro (S/N)?  "));
            menuOPCAO("Deseja Continuar e Inserir um Novo Registro (S/N)?  ", strlen("Deseja Continuar e Inserir um Novo Registro (S/N)? "));
            gotoXY(0, 2);
            menuBAIXO(strlen("Deseja Continuar e Inserir um Novo Registro (S/N)?  "));
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

void listarAlunos() {

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
            alterar();
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
void alterar(){
    CAD_ALUNOS al;
    //variavel para contar a posição
    int i=0;
    //variavel para salvar o que o usuario digitar e comparar com os que está no arquivo
    char auxiliar[11];
    printf("\n---------------PROCURAR ALUNOS POR CPF-------------\n\n");
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo = fopen("cad_alunos.txt", "r+b");
    if(arquivo == NULL){
        printf("\n Impossivel Abrir o arquivo!\n");
        }
    else{
            fflush(stdin);
            printf("\nDigite o CPF que deseja procurar: ");
            gets(auxiliar);
            //lê todos os dados do arquivo até encontrar o final do arquivo (EOF)
            while(fread(&al, sizeof(CAD_ALUNOS), 1,arquivo)==1){
                 i++;
                 //comparar a cpf que o usuario digitou com os que ja estão no arquivo
                 if(strcmp(auxiliar, al.cpf) == 0){
                        printf("---------Dados Atuais---------\n");
                        printf("\nNome do Aluno: %s", al.nome);
                        printf("\nMatricula do Aluno: %d", al.matricula);
                        printf("\nCPF Atual: %s\n",al.cpf );
                        printf("\nDigite o Novo CPF: ");
                        fflush(stdin);
                        fgets(al.cpf, 11, stdin);
                        //O novo cpf que foi digitado vai receber um \0 para indicar o fim
                        al.cpf[strlen(al.cpf)-1]= '\0';
                        printf("\nDigite o Novo Nome: ");
                        fflush(stdin);
                        fgets(al.nome, 50, stdin);
                        //O novo nome que foi digitado vai receber um \0 para indicar o fim
                        al.nome[strlen(al.nome)-1] = '\0';
                        //vou para a posicao no arquivo que eu quero incluir os novos dados
                        fseek(arquivo,(i-1)*sizeof(CAD_ALUNOS),SEEK_SET);
                        //inscrevo os novos dados e verifico se foi feito com sucesso
                if(fwrite(&al,sizeof(CAD_ALUNOS),1,arquivo) != 1){
                            printf("\n Falha ao Alterar o registro!\n");
                            system("pause");
                }else{
                            printf("\n Registro alterado com sucesso!\n");
                        }
                        break;
                    }
                }
    }
    printf("\n\n***************Fim da Edição.***************\n\n");
	system("pause");
	system("cls");
	fclose(arquivo);
}
void excluir(){
    CAD_ALUNOS al;
    int i=0;
    char auxiliar[11];
    printf("\n---------------EXLUINDO ALUNOS -------------\n\n");
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo = fopen("cad_alunos.txt", "r+b");
    FILE *arq_auxiliar = fopen("auxiliar.txt", "w+b");
    if(arquivo == NULL || arq_auxiliar == NULL){
        printf("\n Impossivel Abrir o arquivo!\n");
        }
    else{
            fflush(stdin);
            printf("\nDigite o CPF que Deseja Excluir: ");
            gets(auxiliar);

            while(fread(&al, sizeof(CAD_ALUNOS), 1,arquivo)==1){
                 i++;
                 if(strcmp(auxiliar, al.cpf) == 0){
                        al.cpf[sizeof(al.cpf)-1] = '\0';
                        al.nome[sizeof(al.nome)-1] = '\0';
                        fseek(arquivo,(i-1)*sizeof(CAD_ALUNOS),SEEK_SET);
                 }else{
                    fwrite(&al,sizeof(CAD_ALUNOS),1,arq_auxiliar);
                 }
            }
    printf("\n\n---------------Registro Excluido com sucesso---------------n\n");
	system("pause");
	system("cls");
	fclose(arquivo);
	fclose(arq_auxiliar);
	remove("cad_alunos.txt");
    rename("auxiliar.txt", "cad_alunos.txt");
    }
}
//Função para verificar que opção vai ser usada no menu aluno
void op_alunos () {
    int o=0;
    struct alunos al;
    do{
    menuAluno();
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
            listarAlunos(al);
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
void verificadorArquivo(FILE *arquivo) {
    if(arquivo == NULL) {
        system("cls");
        printf("Ocorreu um erro no sistema. Por favor contate o fabricante! \n\n\n\n");
        printf("Saindo do programa...");
        Sleep(2000);
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
