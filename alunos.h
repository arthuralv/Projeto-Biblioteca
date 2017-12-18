#include <stdio.h>
#include <windows.h>
#include <dos.h>

int mat = 100;
//Estrutura para o cadastro de alunos
typedef struct alunos {
    int matricula;
    char nome[50];
    char cpf[11];
}CAD_ALUNOS;
//Função para gravar registro de funcionários.
void cadastrar(){
	limpartela();
	FILE* arquivo; //FILE (sempre maiuscula), variável do tipo file (arquivo é o nome do ponteiro), nesta linha está sendo criado o ponteiro
	CAD_ALUNOS al;
	arquivo = fopen ("cad_alunos.txt", "ab"); // "ab" acrescenta dados binários no fim do arquivo e se o arquivo não existir ele será criado e
	                                     //e fopen é responsável fazer com que o ponteiro aponte para um arquivo no programa

	if (arquivo == NULL){
		printf("\nProblemas na abertura do arquivo!\n");
	}
	else{
		do{
            limpartela();
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
		}
		while(getche() == 's');
		fclose(arquivo); //Fecha o arquivo que foi aberto.
		}
    }
void cad_alunos(struct alunos al){
    int cont=0;
    printf("\n---------------CADASTRO DE ALUNOS-------------\n\n");
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo;
    //Abrindo o arquivo criado e dando o nome cad_alunos para o arquivo
    //O "a+" é  para abrir salvar no final, e ler os dados do arquivo
    arquivo = fopen("cad_alunos.txt", "a+b");
    //verificando se o arquivo foi aberto com exito
    if(arquivo == NULL){
        printf("Impossivel Abrir Aquivo!");
    }
    else{

        mat++;
        printf("Sua matricula: %d\n", mat);
        fprintf(arquivo, "%d ", mat); //escrevendo a matricula no arquivo
        printf("Digite o Nome do Aluno: ");
        fflush(stdin);
        gets(al.nome);
        fprintf(arquivo, "%s ", al.nome); //escrevendo o nome no arquivo
        printf("Digite o CPF do Aluno: ");
        fflush(stdin);
        gets(al.cpf);
        fprintf(arquivo, "%s ", al.cpf); //escrevendo o nome no arquivo
        limpartela();
        printf("ALUNO CADASTRADO COM SUCESSO!");
    }
    fclose(arquivo);
}
void listaralunos(){
    char aux[255];
    CAD_ALUNOS al;
    printf("\n---------------LISTAGEM DE ALUNOS-------------\n\n");
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo;
    //Abrindo o arquivo criado e dando o nome cad_alunos para o arquivo
    //O "a+" é  para abrir salvar no final, e ler os dados do arquivo
    arquivo = fopen("cad_alunos.txt", "rb");
    //verificando se o arquivo foi aberto com exito
    if(arquivo == NULL){
        printf("Impossivel Abrir Aquivo!");
    }
    else{
            while(fread(&al, sizeof(CAD_ALUNOS), 1,arquivo)==1){
                printf("\nMatricula: %d\n", al.matricula);
                printf("\nNome: %s", al.nome);
                printf("\nCPF: %s", al.cpf);
                printf("\n-----------------------------------------------------------\n");
                system("pause");
                }
    }
    printf("\n\n***************Fim do relatório.***************\n\n");
	system("pause");
	limpartela();
}
//Função para verificar que opção vai ser usada no menu aluno
void op_alunos () {
    int o=0;
    struct alunos al;
    do{
                printf("\n---------------ALUNOS-------------\n\n");
                printf("-\t 1 Cadastrar Aluno\t\t\t-\n");
                printf("-\t 2 Remover Aluno\t\t\t-\n");
                printf("-\t 3 Editar Aluno\t\t\t-\n");
                printf("-\t 4 Listar Alunos Cadastrados\t\t\t-\n");
                printf("-\t 5 Ir para menu anterior\t\t\t-\n\n");
                scanf("%d", &o);
        switch(o){
            case 1:
                limpartela();
                cadastrar();
                Sleep(1000);
            case 2:
                limpartela();
                Sleep(1000);
                break;
            case 3:
                limpartela();
                Sleep(1000);
                break;
            case 4:
                limpartela();
                listaralunos(al);
                Sleep(1000);
                break;
            case 5:
                limpartela();
                Sleep(1000);
                menu_principal();
            default:
                printf("Opção invalida\n");break;
        }
        fflush(stdin);
    }
    while(o >= 5);
}

