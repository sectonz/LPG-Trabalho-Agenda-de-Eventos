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
int compara_datas(struct data d, struct data p);
int converte_hora_min(struct horario h);
int busca_indice_data(struct evento *v, int nEventos, struct data d, struct horario h);
void remove_evento(struct evento *v, int *nEventos, int indice_rmv);
void salva_arquivo(struct evento *v, int nEventos, char *arquivo);
void carrega_arquivo(struct evento **v, int *nEventos, char *arquivo);

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

    carrega_arquivo(&v, &nEventos, "eventos.txt");

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
                limpaTela();
                struct data a;
                struct horario b;
                if(nEventos == 0){
                    printf("Nao ha eventos para serem removidos!\n\n");
                    pressEnter();
                }else{
                    if(leData_v2(&a)){
                        leHoraIni(&b);
                    }else{
                        break;
                    }
                    
                    int indice_rmv = busca_indice_data(v, nEventos, a, b);
                    if(indice_rmv != -1){
                        remove_evento(v, &nEventos, indice_rmv);
                        limpaTela();
                        printf("Evento removido com sucesso!\n\n");
                        pressEnter();
                    }else{
                        limpaTela();
                        printf("Nao ha um evento neste horario e nesta data!\n\n");
                        pressEnter();
                    }
                }
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
    
    salva_arquivo(v, nEventos, "eventos.txt");

    system("eventos.txt");

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

int compara_datas(struct data d, struct data p){
    if(d.dia == p.dia &&
       d.mes == p.mes &&
       d.ano == p.ano){
        return 1;
       }
    
    return 0;
}

int converte_hora_min(struct horario h){
    int minutos_totais = (h.hora * 60) + h.minuto;

    return minutos_totais;
}

int busca_indice_data(struct evento *v, int nEventos, struct data d, struct horario h){
    for(int i = 0; i < nEventos; i++){
        if(compara_datas(v[i].dataEvento, d) && converte_hora_min(v[i].horaInicio) == converte_hora_min(h)){
            return i;
        }
    }
    return -1; //como o indice 0 é valido para o primeiro evento no vetor, preciso de um numero especial
}

void remove_evento(struct evento *v, int *nEventos, int indice_rmv){ //*nEventos pois preferi que a funcao modifique diretamente a variavel, sem precisar usar variaveis auxiliares depois
    for (int i = indice_rmv; i < (*nEventos) - 1; i++) {
        v[i] = v[i + 1];
    }

    (*nEventos)--;
}

void salva_arquivo(struct evento *v, int nEventos, char *arquivo){

    FILE *f = fopen(arquivo, "wt");
    
    fprintf(f, "%i\n", nEventos);
    for(int i = 0; i < nEventos; i++){
        fprintf(f, "%i %i %i\n", v[i].dataEvento.dia, v[i].dataEvento.mes, v[i].dataEvento.ano);

        fprintf(f, "%i %i\n", v[i].horaInicio.hora, v[i].horaInicio.minuto);

        fprintf(f, "%i %i\n", v[i].horaFim.hora, v[i].horaFim.minuto);

        fprintf(f, "%s\n", v[i].descricao);

        fprintf(f, "%s\n", v[i].local);
    }
    
    fclose(f);
}

void carrega_arquivo(struct evento **v, int *nEventos, char *arquivo){
    limpaTela();
    printf("Abrindo arquivo...\n");
    FILE *f = fopen(arquivo, "rt");

    if(f == NULL) {
        printf("\nArquivo de cadastro nao encontrado!\n\n");
        pressEnter();
    }else{
        fscanf(f, "%i", nEventos); //a primeira linha do arquivo deve conter a quantidade de eventos
        *v = malloc(sizeof(struct evento)*(*nEventos));

        for(int i = 0; i < *nEventos; i++){
            fscanf(f, "%i %i %i",
                &(*v)[i].dataEvento.dia, &(*v)[i].dataEvento.mes, &(*v)[i].dataEvento.ano);
            
            fscanf(f, "%i %i",
                &(*v)[i].horaInicio.hora, &(*v)[i].horaInicio.minuto);

            fscanf(f, "%i %i",
                &(*v)[i].horaFim.hora, &(*v)[i].horaFim.minuto);

            fscanf(f, " %[^\n]", (*v)[i].descricao);

            fscanf(f, " %[^\n]", (*v)[i].local);
        }

        /*arquivo deve estar escrito na forma:
        quantidade de eventos no arquivo -> numero -> 1
        data do evento -> dia mes ano -> 01 01 2024
        hora de inicio -> hora minuto -> 16 30
        hora de fim -> hora minuto -> 17 30
        descricao -> string
        local -> string
        */

        fclose(f); 

        printf("\n%i eventos carregados do arquivo!\n\n", *nEventos);
        pressEnter();
    }
}
