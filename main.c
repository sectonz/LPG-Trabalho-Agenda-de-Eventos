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


struct data{
	int dia, mes, ano;
};

struct horario{
    int hora, minuto;
};

struct evento{
	struct data dataEvento;
    struct horario horaInicio;
    struct horario horaFim;
    char descricao[100];
    char local[100];
};

void limpaTela();
void pressEnter();
void mostraEvento(struct evento *x,int n);
int leHoraIni(struct horario *p);
int leHoraFim(struct horario *p);
int leData(struct data *p);
int leData_v2(struct data *p);
int leEvento(struct evento *p);
int verifica_choque(struct evento novo, struct evento *eventos, int numEventos);
void selection_sort(struct evento v[], int qtd_eventos);
long long int id(struct evento p);

int main(int argc,char *argv[]){

    struct evento *v = NULL; //cria struct de eventos vazio
    struct evento x;

    int nEventos = 0; //numero de eventos atual...
    int opcao = -1,idx=0;
    
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
        scanf(" %d",&opcao);

        switch(opcao){
            
            case 1:
                if(leEvento( &x) && verifica_choque(x,v,nEventos)){
                    nEventos++;
                    v = realloc(v,sizeof(struct evento) * nEventos);
                    v[nEventos-1] = x;
                    selection_sort(v,nEventos);
                    printf("\nCadastro realizado com sucesso!\n");
                    pressEnter();
                }
                else{
                    printf("\nErro na entrada... Cadastro nao realizado.\n");
                    pressEnter();
                }
                break;
            
            case 2:
                if(nEventos == 0){
                    limpaTela();
                    printf("Nao ha eventos cadastrados!\n\n");
                    pressEnter();
                }
                else{
                    limpaTela();
                    printf("Lista de Eventos:\n\n");
                    mostraEvento(v,nEventos);
                    printf("\n");
                    pressEnter();
                }
                break;
            
            case 3:
                if(nEventos == 0){
                    limpaTela();
                    printf("Nao ha eventos cadastrados!\n\n");
                    pressEnter();
                }
                else{
                    limpaTela();
                    struct data y;
                    int achou = 0;
                    if(leData_v2(&y)){
                        limpaTela();
                        printf("Eventos do dia %.2d/%.2d/%d:\n\n",y.dia,y.mes,y.ano);
                        for(int i = 0;i<nEventos;i++){
                            if(v[i].dataEvento.dia == y.dia && v[i].dataEvento.mes == y.mes && v[i].dataEvento.ano == y.ano){
                                mostraEvento(&v[i],1);
                                achou = 1;
                            }
                        }
                        if(!achou){
                            limpaTela();
                            printf("Evento nao foi encontrado!\n\n");
                            pressEnter();
                            break;
                        }
                        printf("\n");
                        pressEnter();
                    }
                    else{
                        printf("\nErro na entrada... busca nao realizada.\n");
                        pressEnter();

                    }
                }
                // idx = buscaEvento(struct evento *v)
                break;
            
            case 4:
                if(nEventos == 0){
                    limpaTela();
                    printf("Nao ha eventos cadastrados!\n\n");
                    pressEnter();
                }
                else{
                    limpaTela();
                    int achou = 0;
                    char descricao[100];
                    printf("Digite a descricao do evento: ");
                    scanf(" %[^\n]", descricao);
                    limpaTela();
                    printf("Eventos com a descricao '%s':\n\n", descricao);
                    for(int i = 0;i<nEventos;i++){
                        if(strcasecmp(v[i].descricao,descricao) == 0){
                            mostraEvento(&v[i],1);
                            achou = 1;
                        }
                    }
                    if(!achou){
                        limpaTela();
                        printf("Evento nao foi encontrado!\n\n");
                        pressEnter();
                        break;
                    }
                    printf("\n");
                    pressEnter();
                }
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
    
    free(v);
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



void mostraEvento(struct evento *x,int n){

    // Evento x em Local y no dia das z ate as p
    for(int i = 0;i<n;i++){    
        printf("%s em %s no dia %.2d/%.2d/%d das %.2d:%.2d as %.2d:%.2d;\n",x[i].descricao,x[i].local,
            x[i].dataEvento.dia,x[i].dataEvento.mes,x[i].dataEvento.ano,
            x[i].horaInicio.hora,x[i].horaInicio.minuto,x[i].horaFim.hora,x[i].horaFim.minuto );
    }

}

int leData(struct data *p){
    printf("Digite o dia: ");
    scanf(" %d", &p->dia);
    if(p->dia < 1 || (*p).dia > 31){
        printf("Dia invalido!\n");
        return 0; //erro
    }
    
    printf("Digite o mes: ");
    scanf(" %d", &p->mes);
    if(p->mes < 1 || p->mes >12){
        printf("Mes invalido!\n");
        return 0;
    }
    printf("Digite o ano: ");
    scanf(" %d", &p->ano);

    return 1;
}

int leData_v2(struct data *p){
    // 10/12/2000
    char entrada[11];
    int dia,mes,ano;

    printf("Digite a data do evento no formato (dd/mm/aaaa): ");
    scanf("%10s", entrada);
    
    if (sscanf(entrada, "%d/%d/%d", &dia, &mes,&ano) != 3) {
        limpaTela();
        printf("Formato invalido. Use o formato dia/mes/ano.\n");
        return 0; 
    }
    if(dia < 1 || dia > 31){
        limpaTela();
        printf("Dia invalido!\n");
        return 0; //erro
    }
    if(mes < 1 || mes >12){
        limpaTela();
        printf("Mes invalido!\n");
        return 0;
    }
    if(ano < 2024 || ano > 2100){
        limpaTela();
        printf("Ano invalido!\n");
        return 0;
    }

    p->dia = dia;
    p->mes = mes;
    p->ano = ano;
    return 1;
}



int leHoraIni(struct horario *p){
    char entrada[6]; 
    int horas, minutos;

    printf("Digite o horário de inicio do evento no formato (hh:mm): ");
    scanf("%5s", entrada); //le até 5 caracteres (hh:mm)

    //passo a string com o horario pra sscanf e ela separa em hora e min, retornando o num de variaveis preenchidas
    if (sscanf(entrada, "%d:%d", &horas, &minutos) != 2) {
        limpaTela();
        printf("Formato invalido. Use o formato hora:minutos.\n");
        return 0; 
    }

    if (horas<0 || horas>23 || minutos<0 || minutos>59){
        printf("\nHorario invalido. Insira valores dentro dos limites.\n");
        return 0; 
    }
    p->hora = horas;
    p->minuto = minutos;
    return 1;
}


int leHoraFim(struct horario *p){
    char entrada[6]; 
    int horas, minutos;

    printf("Digite o horário de fim do evento no formato (hh:mm): ");
    scanf("%5s", entrada); //le até 5 caracteres (hh:mm)

    //passo a string com o horario pra sscanf e ela separa em hora e min, retornando o num de variaveis preenchidas
    if (sscanf(entrada, "%d:%d", &horas, &minutos) != 2) {
        printf("\nFormato invalido. Use o formato hora:minutos.\n");
        return 0; 
    }

    if (horas<0 || horas>23 || minutos<0 || minutos>59){
        printf("\nHorario invalido. Insira valores dentro dos limites.\n");
        return 0; 
    }
    p->hora = horas;
    p->minuto = minutos;
    return 1;
}

int leEvento(struct evento *p) {
    limpaTela();
    printf("Digite a descricao do evento: ");
    scanf(" %[^\n]", p->descricao);
    printf("Local de realizacao: ");
    scanf(" %[^\n]", p->local);
    // printf("Digite a data do evento:\n");
    int minutosDoFim = 0, minutosDoIni = 0;
    if (leData_v2(&p->dataEvento) && leHoraIni(&p->horaInicio) && leHoraFim(&p->horaFim)) {
        minutosDoIni = (p->horaInicio.hora)*60+(p->horaInicio.minuto);
        minutosDoFim = (p->horaFim.hora)*60+(p->horaFim.minuto);
        if(minutosDoFim>minutosDoIni){
            return 1;
        }
    }
    return 0;
}

int sobrepoe(struct evento a, struct evento b) {
    // Verifique se os intervalos de tempo se sobrepõem
    if (a.dataEvento.ano == b.dataEvento.ano &&
        a.dataEvento.mes == b.dataEvento.mes &&
        a.dataEvento.dia == b.dataEvento.dia) {
        // Mesmo dia, verifique os horários
        if (a.horaFim.hora < b.horaInicio.hora || a.horaInicio.hora > b.horaFim.hora) {
            return 0; // Não há sobreposição
        }
        // Verifique os minutos
        if (a.horaFim.hora == b.horaInicio.hora && a.horaFim.minuto <= b.horaInicio.minuto) {
            return 0; // Não há sobreposição
        }
        if (a.horaInicio.hora == b.horaFim.hora && a.horaInicio.minuto >= b.horaFim.minuto) {
            return 0; // Não há sobreposição
        }
        return 1; // Há sobreposição
    }
    return 0; // Datas diferentes, sem sobreposição
}


int verifica_choque(struct evento x, struct evento *p, int numEventos) {
    for (int i = 0; i < numEventos; i++) {
        if (sobrepoe(x, p[i])) {
            limpaTela();
            printf("O novo evento se sobrepoe a outro evento existente.\n");
            // pressEnter();
            return 0; // Sobreposição detectada
        }
    }
    return 1; // Sem sobreposição
}


void selection_sort(struct evento v[], int qtd_eventos){
    int i;
    for( i = 0 ; i < qtd_eventos-1 ; i++ ){
        int j, i_menor = i;
        for( j = i+1 ; j < qtd_eventos ; j++ ){
            if(id(v[j]) < id(v[i_menor]))
                i_menor = j;
        }
        struct evento aux = v[i];
        v[i] = v[i_menor];
        v[i_menor] = aux;
    }
}

long long int id(struct evento p){
    long long int id;
    id = p.dataEvento.ano * 10e8;
    id += p.dataEvento.mes * 10e6;
    id += p.dataEvento.dia * 10e4;
    id += (p.horaInicio.hora * 60) + p.horaInicio.minuto;

    return id;
}

// int busca_remocao(struct evento v, int nventos, struct data d, struct horario h){
//     int i;
//     for(i = 0; i < qtd_eventos; i++){
//         if(comp_data(v[i].data_evento, d) && conv_horario(v[i].inicio) == conv_horario(h)){
//             return i;
//         }
//     }
//     return -1;
// }

// void remove_evento(struct eventov, int qtd_eventos, int index){
//     int i;
//     for(i = index+1; i <qtd_eventos; i++){
//         v[i-1] = v[i];
//     }

//     (qtd_eventos)--;
//     v = realloc(v, sizeof(struct evento) (*qtd_eventos));
// }

//                 if(qtd_eventos == 0){
//                     printf("Nao existem eventos cadastrados!\n");
//                 }else{
//                     struct data remove_data;
//                     struct horario remove_horario;
//                     printf("Digite a data do evento que deseja remover: \n");
//                     if(le_data(&remove_data)){

//                         printf("\nDigite o horario inicial do evento que deseja remover: \n");
//                         if(le_horario(&remove_horario)){

//                             int index = busca_remocao(v, qtd_eventos, remove_data, remove_horario);

//                             if(index != -1){
//                                 remove_evento(v, &qtd_eventos, index);
//                                 limpa_tela();
//                                 printf("Evento removido!\n");
//                             }else{
//                                 limpa_tela();
//                                 printf("Evento nao encontrado!\n");
//                             }
//                         }
//                     }
//                 }

//                 funcaoEnter();
//             break;


// int compararEventos(struct evento *a, struct evento *b) {
//     if (a->dataEvento.ano != b->dataEvento.ano) {
//         return a->dataEvento.ano - b->dataEvento.ano;
//     }
//     if (a->dataEvento.mes != b->dataEvento.mes) {
//         return a->dataEvento.mes - b->dataEvento.mes;
//     }
//     if (a->dataEvento.dia != b->dataEvento.dia) {
//         return a->dataEvento.dia - b->dataEvento.dia;
//     }
//     if (a->horaInicio.hora != b->horaInicio.hora) {
//         return a->horaInicio.hora - b->horaInicio.hora;
//     }
//     return a->horaInicio.minuto - b->horaInicio.minuto;
// }



//CHAMAR ESSA FUNCAO NO FINAL DA MAIN ANTES DE DAR O FREE E ENCERRAR O PROGRAMA
// void salva_arquivo( struct pessoa *v, int n, char *nome_arquivo ){
// 	FILE *f = fopen( nome_arquivo, "wt" );
// 	fprintf( f, "%d\n", n);	
// 	int i;
// 	for( i = 0 ; i < n ; i++ ){
// 		fprintf( f, "%s\n", v[i].nome );
// 		fprintf( f, "%d %d %d\n",
// 				v[i].nascimento.dia, v[i].nascimento.mes, v[i].nascimento.ano);
// 	}
// 	fclose( f ); // Fecha o arquivo.
// }

// void carrega_arquivo( struct pessoa **pv, int *pn, char *nome_arquivo ){
// 	FILE *f = fopen( nome_arquivo, "rt" );
// 	if( f == NULL ){
// 		printf("Arquivo de cadastro nao encontrado!\n");
// 		return;
// 	}
// 	fscanf( f, "%d", pn);
	
// 	*pv = malloc( sizeof(struct pessoa) * *pn);
	
// 	int i;
// 	for( i = 0 ; i < *pn ; i++ ){
// 		fscanf( f, " %[^\n]", (*pv)[i].nome );
// 		fscanf( f, "%d %d %d",
// 				(*pv)[i].nascimento.dia, (*pv)[i].nascimento.mes, (*pv)[i].nascimento.ano);
// 	}
// 	fclose( f ); // Fecha o arquivo.	
	
// }

    // R- > READ, W -> WRITE, T-> TEXT, B -> BINARY
    //fopen("nome do arquivo","modo de abertura")
