#ifndef EMPRESTIMOS_H_INCLUDED
#define EMPRESTIMOS_H_INCLUDED
#endif // EMPRESTIMOS_H_INCLUDED

#include <stdio.h>
#include <windows.h>
#include <dos.h>
#include <string.h>
int codEmprestimo = 100;

//Estrutura para o cadastro de alunos
typedef struct emprestimos {
    int cod_livro;
    int cod_emprestimo;
    int matricula_aluno;
    char nome_livro[50];
    char nome_aluno[50];
    int dia_em;
    int mes_em;
    int ano_em;
    int diadev;
    int mesdev;
    int anodev;
} CAD_EMP;

typedef struct {
    int dia;
    int mes;
    int ano;
} DAT;

void p_data(char str[9], DAT *Alvo) {
    char _dia[3] = {
        str[3],
        str[4],
        0
    };
    char _mes[3] = {
        str[0],
        str[1],
        0
    };
    char _ano[3] = {
        str[6],
        str[7],
        0
    };
    Alvo->dia = atoi(_dia);
    Alvo->mes = atoi(_mes);
    Alvo->ano = atoi(_ano);
}

int contadorCodEm() {
    int aux = 0;
    FILE *arquivo;
    arquivo = fopen("emprestimos", "rb");
    CAD_EMP em;
    if(arquivo == NULL) {
        printf("\n\n  Problemas na abertura do arquivo!\n");
    } else
        while(fread(&em, sizeof(CAD_EMP), 1,arquivo) == 1) {
            if(&(em.cod_emprestimo) != NULL) {
                aux++;
            }
        }
    fclose(arquivo);
    return aux;
}

int veri_cpf(int cod) {
    FILE *arquivo;
    arquivo = fopen("cad_alunos.txt", "rb");
    verificadorArquivo(arquivo);
    CAD_ALUNOS al;
    while(fread(&al, sizeof(CAD_ALUNOS), 1, arquivo) == 1) {
        if(cod == al.matricula) {
            fclose(arquivo);
            return 1;
        }
    }
    fclose(arquivo);
    return 0;
}
void cadastrarEmprestimos() {
    system("cls");
    char dataatual[9];
    // pega a data atual
    _strdate( dataatual);
    DAT atual;
    p_data(dataatual, &atual);
    int ano = atual.ano;
    int dia = atual.dia;
    int mes = atual.mes;
    int cod = 0, aux = 0, x = 0, i = 0;
    FILE *arquivo;
    FILE *livro;
    FILE *aluno; //FILE (sempre maiuscula), variável do tipo file (arquivo é o nome do ponteiro), nesta linha está sendo criado o ponteiro
    CAD_EMP em;
    CAD_LIVROS li;
    CAD_ALUNOS al;
    arquivo = fopen ("emprestimos", "a+b");// "ab" acrescenta dados binários no fim do arquivo e se o arquivo não existir ele será criado e
    livro = fopen("cad_livros.txt", "r+b");
    aluno = fopen("cad_alunos.txt", "rb");
    verificadorArquivo(arquivo);
    if(livro == NULL){
        printf("\n\n  Nao ha livro para devolver!\n");
        system("pause");
        system("cls");
        fclose(arquivo);
        fclose(livro);
        return;
    }
    if(aluno == NULL){
        printf("\n\n  Nao ha aluno cadastrado!\n");
        system("pause");
        system("cls");
        fclose(arquivo);
        fclose(livro);
        fclose(aluno);
        return;
    }
    menuCIMA(29);
    menuOPCAO(" REALIZANDO EMPRESTIMO", 29);
    menuBAIXO(29);
    char op;
    printf("\n\n Digite o codigo do livro que deseja realizar o emprestimo: ");
    scanf("%d", &cod);
    while(fread(&li, sizeof(CAD_LIVROS), 1, livro)==1) {
        if(cod == li.codigo) {
            li.quantidade = li.quantidade - 1;
            if(li.quantidade < 0) {
                system("cls");
                printf("\n\n  Sem livro para emprestimo.\n");
                system("pause");
                fclose(arquivo);
                fclose(livro);
                fclose(aluno);
                return;
            } else {
                fseek(livro,(aux)*sizeof(CAD_LIVROS),SEEK_SET);
                fwrite(&li,sizeof(CAD_LIVROS), 1,livro);
            }
            break;
        }
        aux++;
    }
    system("cls");
    printf("\n\n Digite a Matricula do Aluno que deseja realizar o emprestimo: ");
    scanf("%d", &cod);
    //continuar a fazer a busca para saber se os alunos tem o mesmo CPF
    x = veri_cpf(cod);
    if(x == 1) {
        system("cls");
        printf("\n\n  Matricula nao existe!\n");
        system("pause");
        system("cls");
        fclose(arquivo);
        fclose(livro);
        fclose(aluno);
        return;
    } else {
        while(fread(&al, sizeof(CAD_ALUNOS), 1, aluno)==1) {
            x = al.matricula;
            if(cod == al.matricula) {
                em.matricula_aluno = al.matricula;
                strcpy(em.nome_aluno, al.nome);
                break;
            }
        }
        //Verificando se o aluno ja tem mais de 2 emprestimos
        while(fread(&em, sizeof(CAD_EMP), 1, arquivo) == 1) {
            if(cod == em.matricula_aluno) {
                i++;
            }
        }
        if(i >= 2) {
            system("cls");
            printf("\n\n Nao foi possivel realizar o Emprestimo do aluno, devido a quantidade maxima de Emprestimos.\n");
            system("pause");
            system("cls");
            fclose(arquivo);
            fclose(livro);
            fclose(aluno);
            return;
        } else {
            aux = contadorCodEm();
            system("cls");
            menuCIMA(30);
            menuOPCAO("     DADOS DO EMPRESTIMO", 30);
            menuBAIXO(30);
            printf("\n Codigo do Emprestimo: %d\n", codEmprestimo);
            codEmprestimo = codEmprestimo + aux;
            printf("\n Codigo do Livro: %d\n", li.codigo);
            printf("\n Nome do Livro: %s\n", strupr(li.nome_livro));
            printf("\n Matricula do Aluno: %d\n", em.matricula_aluno);
            printf("\n Nome do Aluno: %s\n", strupr(em.nome_aluno));
            printf("\n Data do Emprestimo: %d/%d/%d\n\n", dia, mes, ano);
            em.dia_em = dia;
            em.mes_em = mes;
            em.ano_em = ano;
            menuCIMA(41);
            dia = dia + 10;
            if(dia > 30) {
                dia = dia % 30;
                mes = mes + 1;
                if(mes > 12) {
                    mes = 1;
                    ano = ano + 1;
                }
            }
            printf(" %c Data da Devolucao do Emprestimo: %d/%d/%d %c\n", 186, dia, mes, ano, 186);
            menuBAIXO(41);
            menuCIMA(40);
            menuOPCAO("    Emprestimo Salvo com Sucesso!", 40);
            menuBAIXO(40);
            em.cod_livro = li.codigo;
            strcpy(em.nome_livro, li.nome_livro);
            //em.matricula_aluno = al.matricula;
            //strcpy(em.nome_aluno, al.nome);
            em.diadev = dia;
            em.mesdev = mes;
            em.anodev = ano;
            em.cod_emprestimo = codEmprestimo;
            fwrite(&em, sizeof(CAD_EMP), 1, arquivo);
        }
    }
    fclose(arquivo); //Fecha o arquivo que foi aberto.
    fclose(livro);
    fclose(aluno);
    system("pause");
    system("cls");
    return;
}

void listartodos() {
    int x = 0;
    FILE *arquivo;
    arquivo = fopen("emprestimos", "rb");
    CAD_EMP em;
    menuCIMA(27);
    menuOPCAO("  LISTAGEM DE EMPRESTIMOS", 27);
    menuBAIXO(27);
    while(fread(&em, sizeof(CAD_EMP), 1,arquivo)==1) {
        printf("\n Codigo do Emprestimo: %d\n", em.cod_emprestimo);
        printf("\n Matricula do Aluno: %d\n", em.matricula_aluno);
        printf("\n Nome do Aluno: %s\n", em.nome_aluno);
        printf("\n Codigo do Livro: %d\n", em.cod_livro);
        printf("\n Nome do Livro: %s\n", em.nome_livro);
        printf("\n Data do Emprestimo do Livro: %d/%d/%d\n", em.dia_em, em.mes_em, em.ano_em);
        printf("\n Data da Devolucao do Livro: %d/%d/%d\n\n", em.diadev, em.mesdev, em.anodev);
        printf("---------------------------------------------\n\n");
        x++;
    }
    if(x == 0) {
        printf("\n\n  LISTA VAZIA!\n\n\n");
    }
    menuCIMA(32);
    menuOPCAO(" FIM DA LISTAGEM DE EMPRESTIMOS", 32);
    menuBAIXO(32);
    system("pause");
    system("cls");
    fclose(arquivo);
    return;
}

void listar_por_Alunos() {
    int aux;
    int x = 0;
    FILE *arquivo;
    arquivo = fopen("emprestimos", "rb");
    CAD_EMP em;
    menuCIMA(36);
    menuOPCAO(" LISTAGEM DE EMPRESTIMOS POR ALUNO", 36);
    menuBAIXO(36);
    printf("\n\n Digite a Matricula do Aluno: ");
    scanf("%d", &aux);
    while(fread(&em, sizeof(CAD_EMP), 1,arquivo)==1) {
        if(aux == em.matricula_aluno) {
            printf("\n Matricula do Aluno: %d\n", em.matricula_aluno);
            printf("\n Nome do Aluno: %s\n", em.nome_aluno);
            printf("\n Codigo do Livro: %d\n", em.cod_livro);
            printf("\n Nome do Livro: %s\n", em.nome_livro);
            printf("\n Data do Emprestimo do Livro: %d/%d/%d\n", em.dia_em, em.mes_em, em.ano_em);
            printf("\n Data da Devolucao do Livro: %d/%d/%d\n\n", em.diadev, em.mesdev, em.anodev);
            printf("---------------------------------------------\n\n");
            x++;
        }
    }
    if(x == 0) {
        printf("\n\n  LISTA VAZIA!\n\n\n");
    }
    menuCIMA(32);
    menuOPCAO(" FIM DA LISTAGEM DE EMPRESTIMOS", 32);
    menuBAIXO(32);
    system("pause");
    system("cls");
    fclose(arquivo);
    return;
}

void listar_por_livros() {
    int aux;
    int x = 0;
    FILE *arquivo;
    arquivo = fopen("emprestimos", "rb");
    CAD_EMP em;
    menuCIMA(36);
    menuOPCAO(" LISTAGEM DE EMPRESTIMOS POR LIVRO", 36);
    menuBAIXO(36);
    printf("\n\n Digite o Codigo do Livro: ");
    scanf("%d", &aux);
    while(fread(&em, sizeof(CAD_EMP), 1,arquivo) == 1) {
        if(aux == em.cod_livro) {
            printf("\n Matricula do Aluno: %d\n", em.matricula_aluno);
            printf("\n Nome do Aluno: %s\n", em.nome_aluno);
            printf("\n Codigo do Livro: %d\n", em.cod_livro);
            printf("\n Nome do Livro: %s\n", em.nome_livro);
            printf("\n Data do Emprestimo do Livro: %d/%d/%d\n", em.dia_em, em.mes_em, em.ano_em);
            printf("\n Data da Devolucao do Livro: %d/%d/%d\n\n", em.diadev, em.mesdev, em.anodev);
            printf("---------------------------------------------\n\n");
            x++;
        }
    }
    if(x == 0) {
        printf("\n\n  LISTA VAZIA!\n\n\n");
    }
    menuCIMA(32);
    menuOPCAO(" FIM DA LISTAGEM DE EMPRESTIMOS", 32);
    menuBAIXO(32);
    system("pause");
    system("cls");
    fclose(arquivo);
    return;
}
void devolucao() {
    int aux=0,j =0,i=0;
    char auxlivro[50];
    FILE *arquivo;
    FILE *livro;
    CAD_EMP em;
    CAD_LIVROS li;
    arquivo = fopen("emprestimos", "rb");
    livro = fopen("cad_livros.txt", "r+b");
    verificadorArquivo(arquivo);
    if(livro == NULL){
        printf("\n\n  Nao ha livro para devolver!");
        system("pause");
        system("cls");
        fclose(arquivo);
        fclose(livro);
        return;
    }
    menuCIMA(60);
    menuOPCAO("  Qual Codigo do Emprestimo que Deseja fazer a Devolucao:", 60);
    menuBAIXO(60);
    gotoXY(60, 1);
    scanf("%d", &aux);
    while(fread(&em, sizeof(CAD_EMP), 1, arquivo)==1) {
        if(aux == em.cod_emprestimo) {
            j = em.cod_livro;
            break;
        }
    }
    system("cls");
    while(fread(&li, sizeof(CAD_LIVROS), 1, livro) == 1) {
        i++;
        if(em.cod_livro == li.codigo) {
            li.quantidade = li.quantidade + 1;
            fseek(livro,(i-1)*sizeof(CAD_LIVROS),SEEK_SET);
            if(fwrite(&li, sizeof(CAD_LIVROS), 1, livro) != 1) {
                menuCIMA(27);
                menuOPCAO("  Falha ao fazer devolucao!", 27);
                menuBAIXO(27);
                system("pause");
                printf("\n\n%s\n\n", strerror(errno));
            } else {
                menuCIMA(20);
                menuOPCAO("  Devolucao feita com Sucesso!", 20);
                menuBAIXO(20);
                system("pause");
            }
            break;
        }
    }
    system("cls");
    fclose(arquivo);
    fclose(livro);
    return;
}

void cancelar() {
    CAD_EMP em;
    int i = 0;
    int auxiliar;
    //Criando um arquivo, com um ponteiro do tipo FILE
    FILE *arquivo = fopen("emprestimos", "a+b");
    FILE *arq_auxiliar = fopen("auxiliar", "w+b");
    if(arquivo == NULL || arq_auxiliar == NULL) {
        printf("\n\n Impossivel abrir o arquivo!\n");
    } else {
        fflush(stdin);
        printf("\n\n  Digite o Codigo do Emprestimo que deseja Cancelar: ");
        scanf("%d", &auxiliar);
        while(fread(&em, sizeof(CAD_EMP), 1, arquivo) == 1) {
            i++;
            if(auxiliar == em.cod_emprestimo) {
                fseek(arquivo,(i - 1) * sizeof(CAD_EMP),SEEK_SET);
            } else {
                fwrite(&em,sizeof(CAD_EMP), 1, arq_auxiliar);
            }
        }
        fclose(arquivo);
        fclose(arq_auxiliar);
        if(remove("emprestimos") == 0) {
            rename("auxiliar", "emprestimos");
            menuCIMA(40);
            menuOPCAO("Emprestimo Cancelado com Sucesso", 40);
            menuBAIXO(40);
            system("pause");
        } else {
            printf("Nao foi possivel Cancelar o Emprestimo!\n");
            printf("\n\n%s\n\n", strerror(errno));
            system("pause");
        }
        system("cls");
    }
    fclose(arquivo);
    fclose(arq_auxiliar);
    return;
}

void listar_emprestimos() {
    int op = 0;
    do {
        menuCIMA(33);
        menuOPCAO("     LISTAGEM DE EMPRESTIMOS", 33);
        menuOPCAO("", 33);
        menuOPCAO(" 1 - Listar Todos Emprestimos", 33);
        menuOPCAO("", 33);
        menuOPCAO(" 2 - Listar Por Livro Especifico", 33);
        menuOPCAO("", 33);
        menuOPCAO(" 3 - Listar Por Aluno Especifico", 33);
        menuOPCAO("", 33);
        menuOPCAO(" 4 - Sair", 33);
        menuOPCAO("", 33);
        menuBAIXO(33);
        menuCIMA(10);
        menuOPCAO(" OPCAO:", 10);
        menuBAIXO(10);
        gotoXY(10, 13);
        setbuf(stdin, NULL);
        scanf("%d", &op);
        system("cls");
        switch(op) {
        case 1:
            listartodos();
            break;
        case 2:
            listar_por_livros();
            break;
        case 3:
            listar_por_Alunos();
            break;
        case 4:
            return;
            break;
        default:
            printf("\n\n  Opcao invalida\n");
            system("pause");
            break;
        }
    } while(op != 4);
    return;
}

//Função para verificar que opção vai ser usada no menu aluno

void op_emprestimos () {
    int o = 0;
    struct emprestimos em;
    do {
        menuCIMA(32);
        menuOPCAO("           EMPRESTIMOS", 32);
        menuOPCAO("", 32);
        menuOPCAO(" 1 - Novo Emprestimo", 32);
        menuOPCAO("", 32);
        menuOPCAO(" 2 - Confirma Devolucao", 32);
        menuOPCAO("", 32);
        menuOPCAO(" 3 - Cancelar Emprestimo", 32);
        menuOPCAO("", 32);
        menuOPCAO(" 4 - Listar Emprestimos", 32);
        menuOPCAO("", 32);
        menuOPCAO(" 5 - Ir para menu anterior", 32);
        menuOPCAO("", 32);
        menuBAIXO(32);
        menuCIMA(10);
        menuOPCAO(" OPCAO: ", 10);
        menuBAIXO(10);
        gotoXY(10, 15);
        scanf("%d", &o);
        system("cls");
        switch(o) {
        case 1:
            cadastrarEmprestimos();
            break;
        case 2:
            devolucao();
            break;
        case 3:
            cancelar();
            break;
        case 4:
            listar_emprestimos();
            break;
        case 5:
            return;
            break;
        default:
            printf("\n\n  Opcao invalida\n");
            system("pause");
            break;
        }
    } while(o != 5);
}
