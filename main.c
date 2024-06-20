//TRABALHO: AGENDA DE EVENTOS
//1) CADASTRAR UM NOVO EVENTO NA AGENDA(MANTER ORDENADO POR DATA E HORA)
//2) MOSTRAR TODOS OS EVENTOS DA AGENDA
//3) DADA UMA DATA, MOSTRAR TODOS OS EVENTOS QUE ACONTECEM NESTA DATA
//4) DADA UMA DESCRICAO, MOSTRAR TODOS OS EVENTOS QUE POSSUEM ESTA DESCRICAO
//5) REMOVER EVENTO
//6) SAIR(DESALOCA O VETOR DE EVENTOS E FINALIZA O PROGRAMA)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Evento *v= NULL;
{
    struct data{
        int dia;
        int mes;
        int ano;
    }
    struct horaInicio{
        int hora;
        int minuto;
    }
    struct horaFim{
        int hora;
        int minuto;
    }
    char descricao[100];
    char local[100];
};

void limpaTela();
void pressEnter();

int main(int *argc,char *argv[]){

    int opcao = -1;
    limpaTela();
    printf("\n\tBem vindo a sua agenda de eventos!\n\n");
    printf("\nPressione qualquer tecla para continuar...\n");
    getchar();
    limpaTela();

    while(opcao != 6){
        printf("Escolha uma opcao:\n");
        printf("1) Cadastrar um novo evento\n");
        printf("2) Mostrar todos os eventos\n");
        printf("3) Mostrar eventos de uma data\n");
        printf("4) Mostrar eventos de uma descricao\n");
        printf("5) Remover evento\n");
        printf("6) Sair\n");
        scanf("%d",&opcao);

        switch(opcao){
            case 1:
                printf("Cadastrar um novo evento\n");
                break;
            case 2:
                printf("Mostrar todos os eventos\n");
                break;
            case 3:
                printf("Mostrar eventos pela data\n");
                break;
            case 4:
                printf("Mostrar eventos pela descricao\n");
                break;
            case 5:
                printf("Remover evento\n");
                break;
            case 6:
                limpaTela();
                printf("Ate mais! :D\n");
                return 0;
            default:
                limpaTela();
                printf("Opcao invalida\n");
                pressEnter();
                break;
        }
    }    

    return 0;
}

void limpaTela(){
    printf("\033[H\033[J"); 
}

void pressEnter(){
    printf("Aperte enter para continuar...\n");
    getchar();
    getchar();
    limpaTela();
}