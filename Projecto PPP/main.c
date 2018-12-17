#include "projecto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define MAX 100

struct t_data{
    int dia;
    int mes;
    int ano;
};

struct t_tdo{
    t_tasks *tarefa;
    int id;
    int prior;
    char *desc;
    t_tdo *prox;
};

struct t_pessoas{
    char nome[MAX];
    char *contact;
    int id;
    t_doing *lista_tasks;
    t_pessoas *prox;
};

struct t_done{
    t_data data;
    t_pessoas *pessoa;
    t_done *prox;
    int id;
    int prior;
    char *desc;
};

struct t_doing{
     int id;
    int prior;
    char *desc;
    t_pessoas *pessoa;
    t_data data;
    t_doing *prox;
};

t_pessoas *cria_lista(void){
    t_pessoas *cabecalho=malloc(sizeof(t_pessoas));
    if (cabecalho ==NULL)
        return NULL;
    cabecalho->prox=NULL;
    return cabecalho;
}

t_tdo *cria_lista2(void){
    t_tdo *cabecalho=malloc(sizeof(t_tdo));
    if (cabecalho ==NULL)
        return NULL;
    cabecalho->prox=NULL;
    return cabecalho;
}

t_doing *cria_lista3(void){
    t_doing *cabecalho=malloc(sizeof(t_doing));
    if (cabecalho==NULL)
        return NULL;
    cabecalho->prox=NULL;
    return cabecalho;
}

t_done *cria_lista4(void){
    t_done *cabecalho=malloc(sizeof(t_done));
    if (cabecalho==NULL)
        return NULL;
    cabecalho->prox=NULL;
    return cabecalho;
}

t_pessoas *add_pessoa(t_pessoas *lista,char *nome,char *email,int id){
    t_pessoas *aux=lista;
    t_pessoas *pnova;
    pnova=malloc(sizeof(t_pessoas));
    if (pnova==NULL)
        return NULL;
    while(aux->prox!=NULL){
         aux=aux->prox;
    }
    strcpy(pnova->nome,nome);
    pnova->contact=strdup(email);
    pnova->id=id;
    aux->prox=pnova;
    pnova->prox=NULL;
    return lista;
}

t_done *finishing(t_doing *lista_todo,t_done *lista_doing,int id_t,t_pessoas *p,t_data dprazo)
{
        //ponteiros auxiliares
        t_doing *aux1=lista_todo;
        t_doing *aux1a=NULL;
        t_done *aux2=lista_doing;
        //Procurar a tarefa na lista to do
        while(aux1!=NULL)
        {
            if(aux1->prox->id==id_t)
            {
                aux1a=aux1->prox;
                aux1->prox=aux1a->prox;
                break;//So queremos que o aux1a aponte para a tarefa que queremos
            }
            aux1=aux1->prox;
        }
        //Agora vamos por no doing
        t_done *novo=malloc(sizeof(t_done));
        novo->pessoa=p;
        //novo->pessoa->id=p->id;
        novo->data.ano=dprazo.ano;
        novo->data.mes=dprazo.mes;
        novo->data.dia=dprazo.dia;
        novo->id=aux1a->id;
        novo->prior=aux1a->prior;
        novo->desc=strdup(aux1a->desc);
        novo->prox=NULL;
        if(lista_doing==NULL)
        {
            free(aux1a);
            return novo;
        }
        else
        {
            //percorrer lista pra por no fim
            for(aux2=lista_doing;aux2->prox!=NULL && aux2->prox->prior <aux2->prior;aux2=aux2->prox);
            aux2->prox=novo;
            free(aux1a);
            return lista_doing;
        }
}

t_tdo *inserir_todo(t_tdo *lista,char *desc,int id,int prior){
    t_tdo *to_tarefa= malloc(sizeof(t_tdo));
    //t_tdo *aux=lista;
    if(to_tarefa == NULL)
        return NULL;
    while(lista->prox!=NULL && lista->prox->prior > prior){
        lista=lista->prox;
    }
    to_tarefa->desc=strdup(desc);
    to_tarefa->id=id;
    to_tarefa->prior=prior;
    to_tarefa->prox=lista->prox;
    lista->prox=to_tarefa;
    return to_tarefa;
}

t_done *inserir_done(t_done *lista,char *desc,int id,int prior,t_pessoas *p, t_data conc){
    t_done *to_tarefa= malloc(sizeof(t_done));
    if(to_tarefa == NULL)
        return NULL;
    while(lista->prox!=NULL){
        lista=lista->prox;
    }
    to_tarefa->desc=strdup(desc);
    to_tarefa->id=id;
    to_tarefa->prior=prior;
    to_tarefa->pessoa=p;
    to_tarefa->data.ano=conc.ano;
    to_tarefa->data.mes=conc.mes;
    to_tarefa->data.dia=conc.dia;
    to_tarefa->prox=lista->prox;
    lista->prox=to_tarefa;
    return to_tarefa;
}

t_doing *move_to_do(t_tdo *lista_todo,t_doing *lista_doing,int id_t,t_pessoas *p,t_data dprazo)
{
        //ponteiros auxiliares
        t_tdo *aux1=lista_todo;
        t_tdo *aux1a=NULL;
        t_doing *aux2=lista_doing;
        //Procurar a tarefa na lista to do
        while(aux1!=NULL)
        {
            if(aux1->prox->id==id_t)
            {
                aux1a=aux1->prox;
                aux1->prox=aux1a->prox;
                break;//So queremos que o aux1a aponte para a tarefa que queremos
            }
            aux1=aux1->prox;
        }
        //Agora vamos por no doing
        t_doing *novo=malloc(sizeof(t_doing));
        novo->pessoa=p;
        //novo->pessoa->id=p->id;
        novo->data.ano=dprazo.ano;
        novo->data.mes=dprazo.mes;
        novo->data.dia=dprazo.dia;
        novo->id=aux1a->id;
        novo->prior=aux1a->prior;
        novo->desc=strdup(aux1a->desc);
        novo->prox=NULL;
        if(lista_doing==NULL)
        {
            free(aux1a);
            return novo;
        }
        else
        {
            //percorrer lista pra por no fim
            for(aux2=lista_doing;aux2->prox!=NULL;aux2=aux2->prox);
            aux2->prox=novo;
            free(aux1a);
            return lista_doing;
        }
}

t_tdo *move_doing(t_doing *lista_doing,t_tdo *lista_todo,int id_t)
{
        //ponteiros auxiliares
        t_doing *aux1=lista_doing;
        t_doing *aux1a=NULL;
        t_tdo *aux2=lista_todo;
        //Procurar a tarefa na lista to do
        while(aux1!=NULL)
        {
            if(aux1->prox->id==id_t)
            {
                aux1a=aux1->prox;
                aux1->prox=aux1a->prox;
                break;//So queremos que o aux1a aponte para a tarefa que queremos
            }
            aux1=aux1->prox;
        }
        //Agora vamos por no doing
        t_tdo *novo=malloc(sizeof(t_tdo));
        novo->id=aux1a->id;
        novo->prior=aux1a->prior;
        novo->desc=strdup(aux1a->desc);
        aux1a->pessoa=NULL;
        novo->prox=NULL;

        if(lista_todo==NULL)
        {
            free(aux1a);
            return novo;
        }
        else
        {
            //percorrer lista pra por no fim
            for(aux2=lista_todo;aux2->prox!=NULL;aux2=aux2->prox);
            aux2->prox=novo;
            free(aux1a);
            return lista_todo;
        }
}

t_tdo *move_done(t_done *lista_done,t_tdo *lista_todo,int id_t)
{
        //ponteiros auxiliares
        t_done*aux1=lista_done;
        t_done *aux1a=NULL;
        t_tdo *aux2=lista_todo;
        //Procurar a tarefa na lista to do
        while(aux1!=NULL)
        {
            if(aux1->prox->id==id_t)
            {
                aux1a=aux1->prox;
                aux1->prox=aux1a->prox;
                break;//So queremos que o aux1a aponte para a tarefa que queremos
            }
            aux1=aux1->prox;
        }
        //Agora vamos por no doing
        t_tdo *novo=malloc(sizeof(t_tdo));
        novo->id=aux1a->id;
        novo->prior=aux1a->prior;
        novo->desc=strdup(aux1a->desc);
        aux1a->pessoa=NULL;
        novo->prox=NULL;

        if(lista_todo==NULL)
        {
            free(aux1a);
            return novo;
        }
        else
        {
            //percorrer lista pra por no fim
            for(aux2=lista_todo;aux2->prox!=NULL;aux2=aux2->prox);
            aux2->prox=novo;
            free(aux1a);
            return lista_todo;
        }
}

t_doing *inserir_doing(t_doing *lista,char *desc,int id,int prior,t_pessoas *p,t_data data){
    t_doing *to_tarefa= malloc(sizeof(t_doing));
    t_doing *aux=lista;
    if(to_tarefa == NULL)
        return NULL;
    while(aux->prox!=NULL){
        aux=aux->prox;
    }
    to_tarefa->desc=strdup(desc);
    to_tarefa->id=id;
    to_tarefa->prior=prior;
    to_tarefa->data.ano=data.ano;
    to_tarefa->data.mes=data.mes;
    to_tarefa->data.dia=data.dia;
    to_tarefa->pessoa=p;
    aux->prox=to_tarefa;
    to_tarefa->prox=NULL;
    return lista;
}

int comparadatas(t_data *data1,t_data *data2){
    if (data1->ano < data2->ano)
        return -1;
    if (data1->ano > data2->ano)
        return 1;
    if(data1->mes < data2->mes)
        return -1;
    if(data2-> mes > data2->mes)
        return 1;
    if(data1->dia < data2->dia)
        return -1;
    if(data1->dia > data2->dia)
        return 1;
    return 0;
}

int compara_semana(int ano1,int dia1,int mes1,char *nome_p,t_doing *tasks){
    int num,data1,result,result1;
    t_doing *aux=tasks->prox;
    num=(ano1*100+mes1)*100+dia1;
    while(aux!=NULL){
            result1=strcmp(aux->pessoa->nome,nome_p);
            if(result1==0){
                data1=(aux->data.ano*100+aux->data.mes)*100+aux->data.dia;
                result=data1-num;
                if(result==0){
                    printf("Datas identicas, %s ja possui uma tarefa com o mesmo prazo!\n",aux->pessoa->nome);
                    return -1;
                }
                printf("tudo");
                if(result<=-7){
                        printf("oi");
                    aux=aux->prox;
                printf("bum");
                   while(aux!=NULL){
                        printf("again!");
                        result1=strcmp(aux->pessoa->nome,nome_p);
                        if(result1==0){
                        data1=(aux->data.ano*100+aux->data.mes)*100+aux->data.dia;
                        result=data1-num;
                        if(result>=7)
                            return 1;

                        if(result <7 && result >1)
                            printf("Permitido apenas uma tarefa por semana!\n");
                            return -1;

                        aux=aux->prox;
                         if(aux==NULL)
                            return 1;
                        }
                        if(result1!=0){
                            return 1;
                        }
                    }
                    return 1;
                }
                   if(result>-7 && result<0){
                        printf("Permitido apenas uma tarefa por semana!\n");
                        return -1;
                   }
                   if(result>0 && result<7){
                        printf("Permitido apenas uma tarefa por semana!\n");
                        return -1;
                   }
                   if(result>=7)
                        return 1;
                }
        aux=aux->prox;
    }
return 0;
}

void imprime_t_done(t_done *tarefas){
    t_done *aux=tarefas;
    while(aux!=NULL){
        printf("Nome da pessoa que terminou a tarefa: %s\n",aux->pessoa->nome);
        printf("Descricao textual: %s\n",aux->desc);
        printf("id da tarefa: %d\n",aux->id);
        printf("Prioridade da tarefa: %d\n",aux->prior);
        printf("Data de conclusao: %d/%d/%d\n\n",aux->data.dia,aux->data.mes,aux->data.ano);
        aux=aux->prox;
    }

}

void imprimepessoas(t_pessoas *pessoas){
    t_pessoas *aux=pessoas->prox;
    while (aux!=NULL){
        printf("nome da pessoa: %s\n",aux->nome);
        printf("id da pessoa: %d\n",aux->id);
        printf("email da pessoa: %s\n\n",aux->contact);
        aux=aux->prox;
    }
}
void imprime_tudo(t_pessoas *p, t_doing *lista,t_tdo *lista1, t_done *lista3){
	t_pessoas *aux=p->prox;
	t_doing *aux1=lista->prox;
	t_done *aux2=lista3->prox;
	t_tdo *aux3=lista1->prox;
	printf("PESSOAS\n");
	while (aux!=NULL){
        printf("nome da pessoa: %s\n",aux->nome);
        printf("id da pessoa: %d\n",aux->id);
        printf("email da pessoa: %s\n\n",aux->contact);
        aux=aux->prox;
    }
    printf("TO DO\n");
	 while(aux3!=NULL){
        printf("Descricao textual: %s\n",aux3->desc);
        printf("id da tarefa: %d\n",aux3->id);
        printf("Prioridade da tarefa: %d\n\n",aux3->prior);
        aux3=aux3->prox;
    }
    char nome[MAX];
    printf("DOING \n");
    while(aux1!=NULL){
        printf("Nome da pessoa a efetuar a tarefa: %s\n",aux1->pessoa->nome);
        printf("ID da pessoa a efetuar a tarefa: %d\n",aux1->pessoa->id);
        strcpy(nome,aux1->pessoa->nome);
        printf("Descricao textual: %s\n",aux1->desc);
        printf("id da tarefa: %d\n",aux1->id);
        printf("prioridade da tarefa: %d\n",aux1->prior);
        printf("data de validade: %d/%d/%d \n\n",aux1->data.dia,aux1->data.mes,aux1->data.ano);
        aux1=aux1->prox;
        while(aux1!=NULL){
                if(strcmp(nome,aux1->pessoa->nome)==0){
                    printf("Descricao textual: %s\n",aux1->desc);
                    printf("id da tarefa: %d\n",aux1->id);
                    printf("prioridade da tarefa: %d\n",aux1->prior);
                    printf("data de validade: %d/%d/%d \n\n",aux1->data.dia,aux1->data.mes,aux1->data.ano);
                }
                if(strcmp(nome,aux1->pessoa->nome)!=0){
                    break;
                }
                aux1=aux1->prox;
        }
    }
    printf("DONE \n");
	while(aux2!=NULL){
        printf("Nome da pessoa que terminou a tarefa: %s\n",aux2->pessoa->nome);
        printf("Descricao textual: %s\n",aux2->desc);
        printf("id da tarefa: %d\n",aux2->id);
        printf("Prioridade da tarefa: %d\n",aux2->prior);
        printf("Data de conclusao: %d/%d/%d\n\n",aux2->data.dia,aux2->data.mes,aux2->data.ano);
        aux2=aux2->prox;
    }
}


void imprime_todo(t_tdo *lista_tarefas){
    t_tdo *aux=lista_tarefas->prox;
    while(aux!=NULL){
        printf("Descricao textual: %s\n",aux->desc);
        printf("id da tarefa: %d\n",aux->id);
        printf("Prioridade da tarefa: %d\n\n",aux->prior);
        aux=aux->prox;
    }
}

void imprime_tarefa_pessoas(t_doing *lista_tarefas){
    t_doing *aux=lista_tarefas->prox;
    char nome[MAX];
    while(aux!=NULL){
        printf("Nome da pessoa a efetuar a tarefa: %s\n",aux->pessoa->nome);
        printf("ID da pessoa a efetuar a tarefa: %d\n",aux->pessoa->id);
        strcpy(nome,aux->pessoa->nome);
        printf("Descricao textual: %s\n",aux->desc);
        printf("id da tarefa: %d\n",aux->id);
        printf("prioridade da tarefa: %d\n",aux->prior);
        printf("data de validade: %d/%d/%d \n\n",aux->data.dia,aux->data.mes,aux->data.ano);
        aux=aux->prox;
        while(aux!=NULL){
                if(strcmp(nome,aux->pessoa->nome)==0){
                    printf("Descricao textual: %s\n",aux->desc);
                    printf("id da tarefa: %d\n",aux->id);
                    printf("prioridade da tarefa: %d\n",aux->prior);
                    printf("data de validade: %d/%d/%d \n\n",aux->data.dia,aux->data.mes,aux->data.ano);
                }
                if(strcmp(nome,aux->pessoa->nome)!=0){
                    break;
                }
                aux=aux->prox;
        }
    }
}

void sort_doing(t_doing *lista){
    int result;
    int troca;
    t_doing *aux=lista->prox;
    do{
    lista=aux;
    troca=0;
    while(lista->prox!=NULL){
            result=strcmp(lista->pessoa->nome,lista->prox->pessoa->nome);
            if(result>0){
                char *nome=lista->pessoa->nome;
                strcpy(lista->pessoa->nome,lista->prox->pessoa->nome);
                strcpy(lista->prox->pessoa->nome,nome);
                troca++;
            }
            lista=lista->prox;
    }
    }while(troca>0);
}

void update_done(t_done *lista){
    FILE *file;
    t_done *aux=lista->prox;
    file=fopen("tarefas_done.txt","w");
    while(aux!=NULL){
        fprintf(file,"%s,",aux->pessoa->nome);
        fprintf(file,"%s,",aux->desc);
        fprintf(file,"%d,",aux->id);
        fprintf(file,"%d,",aux->prior);
        fprintf(file,"%02d/%02d/%02d\n",aux->data.dia,aux->data.mes,aux->data.ano);
        aux=aux->prox;
    }
}

void update_doing1(t_doing *lista){
    FILE *file;
    t_doing *aux=lista->prox;
    file=fopen("tarefas_doing.txt","w");
    if(file==NULL)
        exit(1);
    while(aux!=NULL){
        fprintf(file,"%s,",aux->pessoa->nome);
        fprintf(file,"%s,",aux->desc);
        fprintf(file,"%d,",aux->id);
        fprintf(file,"%d,",aux->prior);
        fprintf(file,"%02d/%02d/%02d\n",aux->data.dia,aux->data.mes,aux->data.ano);
        aux=aux->prox;
    }
}

void update_td(t_tdo *lista){
    FILE *file;
    t_tdo *aux=lista->prox;
    file=fopen("tarefas_to_do.txt","w");
    while(aux!=NULL){
        fprintf(file,"%s,",aux->desc);
        fprintf(file,"%d,",aux->prior);
        fprintf(file,"%d\n",aux->id);
        aux=aux->prox;
    }
}

void updateall(t_done *lista3,t_doing *lista,t_tdo *lista2,t_pessoas *pessoas){
    FILE *file;
    t_doing *aux=lista->prox;
    t_tdo *aux1=lista2->prox;
    t_done *aux2=lista3;
    t_pessoas *aux4=pessoas->prox;
    file=fopen("Tudo.txt","w");
    if(file==NULL)
        exit(1);
    fprintf(file,"DOING\n");
    while(aux->prox!=NULL){
        fprintf(file,"nome pessoa: %s \n",aux->pessoa->nome);
        fprintf(file,"Descricao Textual: %s\n",aux->desc);
        fprintf(file,"id da tarefa: %d\n",aux->id);
        fprintf(file,"Prazo para efetuar a tarefa: %d/%d/%d\n",aux->data.dia,aux->data.mes,aux->data.ano);
        aux=aux->prox;
    }
    fprintf(file,"TO DO\n");
    while(aux1->prox!=NULL){
        fprintf(file,"Descricao Textual: %s",aux1->desc);
        fprintf(file,"id da tarefa: %d\n",aux1->id);
        fprintf(file,"Prioridade da tarefa: %d\n\n",aux1->prior);
        aux1=aux1->prox;
    }
    fprintf(file,"Lista de Pessoas\n");
    while(aux4->prox!=NULL){
        fprintf(file,"nome da pessoa: %s\n",aux4->nome);
        fprintf(file,"id da pessoa: %d\n",aux4->id);
        fprintf(file,"email da pessoa: %s\n\n",aux4->contact);
        aux4=aux4->prox;
    }
    fprintf(file,"DONE\n");
    while(aux2!=NULL){
        fprintf(file,"nome pessoa: %s \n",aux2->pessoa->nome);
        fprintf(file,"Descricao Textual: %s\n",aux2->desc);
        fprintf(file,"id da tarefa: %d\n",aux->id);
        fprintf(file,"Data de conclusao da tarefa: %d/%d/%d\n",aux2->data.dia,aux2->data.mes,aux2->data.ano);
        aux2=aux2->prox;
    }
}

void AlterarPesssoa(t_doing *lista,t_pessoas *p,int id_t){
    t_doing *aux=lista;
    while(aux!=NULL){
        if(id_t==aux->id){
            aux->pessoa=p;
            break;
        }
    aux=aux->prox;
    }
}

int VerificarMaxTarefa(int MAXTAREFA,t_doing *lista,char *p){
    t_doing *aux=lista->prox;
    int c=0;
    while(aux!=NULL){
        int compare=strcmp(aux->pessoa->nome,p);
        if(compare==0){
            c++;
        }
        aux=aux->prox;
    }
    if(c>MAXTAREFA){
        return -1;
    }
    if(c<MAXTAREFA){
        return 1;
    }
    return 0;
}

/*Menu teste*/
int main(){
    int MAXTAREFA=0;
    t_pessoas *pessoas=cria_lista();
    t_tdo *tarefa=cria_lista2();
    t_doing *tarefas=cria_lista3();
    t_done *tarefas_f=cria_lista4();

//adicionar pesssoas
    char num[512];
    FILE *file;
    file = fopen("pessoas.txt", "r");
    char nome[MAX];
    char contacto[MAX];
    char id__[MAX];
    int id_;
    while(fgets(num, sizeof(num), file)!=NULL){
        strcpy(nome,strtok(num,","));
        strcpy(contacto,strtok(NULL,","));
        strcpy(id__,strtok(NULL,"/"));
        sscanf(id__,"%d",&id_);
        add_pessoa(pessoas,nome,contacto,id_);
    }
    fclose(file);

    //adicionar na lista doing
    char rands[512];
        //FILE *file;
        file = fopen("tarefas_doing.txt","r");
        t_pessoas *aux=pessoas;
        t_pessoas *aux1=NULL;
        char dia1[MAX];
        char mes1[MAX];
        char ano1[MAX];
        char desc1[MAX];
        char prior_[MAX];
        char id_dd[MAX];
        char nome1[MAX];
        int prior_d,id_d,dia,mes,ano;

        while(fgets(rands,sizeof(rands),file)!=NULL){
                strcpy(nome1,strtok(rands,","));
                strcpy(desc1,strtok(NULL,","));
                strcpy(id_dd,strtok(NULL,","));
                strcpy(prior_,strtok(NULL,","));
                strcpy(dia1,strtok(NULL,"/"));
                strcpy(mes1,strtok(NULL,"/"));
                strcpy(ano1,strtok(NULL,"/"));
                sscanf(id_dd,"%d",&id_d);
                sscanf(prior_,"%d",&prior_d);
                sscanf(mes1,"%d",&mes);
                sscanf(dia1,"%d",&dia);
                sscanf(ano1,"%d",&ano);
                t_data prazo={dia,mes,ano};
                while(aux!=NULL){
                    if(strcmp(nome1,aux->nome)==0){
                            aux1=aux;
                            aux->prox=aux1->prox;
                            break;
                    }
                    aux=aux->prox;
                }
                inserir_doing(tarefas,desc1,id_d,prior_d,aux1,prazo);
                aux=pessoas;
                aux1=NULL;
            }
        fclose(file);

    //adicionar na lista to do
        char tab[512];
        //FILE *file;
        file = fopen("tarefas_to_do.txt","r");
        char desc[MAX];
        char prior1[MAX];
        char id1[MAX];
        int prior;
        int id;
        while(fgets(tab,sizeof(tab),file)!=NULL){
                strcpy(desc,strtok(tab,","));
                strcpy(prior1,strtok(NULL,","));
                strcpy(id1,strtok(NULL,"/"));
                sscanf(id1,"%d",&id);
                sscanf(prior1,"%d",&prior);
                inserir_todo(tarefa,desc,id,prior);
                }
        fclose(file);
    char done[512];
        //FILE *file;
        file = fopen("tarefas_done.txt","r");
        t_pessoas *aux_c=pessoas;
        t_pessoas *aux1_c=NULL;
        char dia_c[MAX];
        char mes_c[MAX];
        char ano_c[MAX];
        char desc_c[MAX];
        char prior_c[MAX];
        char id_c[MAX];
        char nome_c[MAX];
        int prior_dc,id_dc,diac,mesc,anoc;

        while(fgets(done,sizeof(done),file)!=NULL){
                strcpy(nome_c,strtok(rands,","));
                strcpy(desc_c,strtok(NULL,","));
                strcpy(id_c,strtok(NULL,","));
                strcpy(prior_c,strtok(NULL,","));
                strcpy(dia_c,strtok(NULL,"/"));
                strcpy(mes_c,strtok(NULL,"/"));
                strcpy(ano_c,strtok(NULL,"/"));
                sscanf(id_c,"%d",&id_dc);
                sscanf(prior_c,"%d",&prior_dc);
                sscanf(mes_c,"%d",&mesc);
                sscanf(dia_c,"%d",&diac);
                sscanf(ano_c,"%d",&anoc);
                t_data prazo_c={diac,mesc,anoc};
                while(aux_c!=NULL){
                    if(strcmp(nome_c,aux_c->nome)==0){
                            aux1_c=aux_c;
                            aux_c->prox=aux1_c->prox;
                            break;
                    }
                    aux_c=aux_c->prox;
                }
                inserir_done(tarefas_f,desc_c,id_dc,prior_dc,aux1,prazo_c);
                aux_c=pessoas;
                aux1_c=NULL;
            }
        fclose(file);

    int options;
    int option1;
    while(options!=3){
        system("cls");
        printf("1.Visualizar Quadro \n");
        printf("2.Editar \n");
        printf("3.Sair \n");
        scanf("%d",&options);
        if(options>3||options<1){
            printf("insira uma opcao valida! ");
            scanf("%d",&options);
        }
        switch (options){
            case 1:
               imprime_tudo(pessoas,tarefas,tarefa,tarefas_f);
                break;
            case 2:
                system("cls");
                printf("1.Pessoas \n");
                printf("2.Tarefas \n");
                printf("3. Voltar \n");
                scanf("%d",&option1);
                if(option1==3){
                    break;
                }
                if(option1==1){
                     system("cls");
                    printf("1.Listar Pessoas \n");
                    scanf("%d",&option1);
                    if(option1==1){
                        imprimepessoas(pessoas);
                        printf("\n1.Listar tarefas atribuidas \n");
                        scanf("%d",&option1);
                        if(option1!=1){
                            break;
                        }
                        if(option1==1){
                             system("cls");
                             sort_doing(tarefas);
                            imprime_tarefa_pessoas(tarefas);
                            getchar();
                            getchar();
                            if(tarefas->prox==NULL){
                                printf("Nao existem pessoas com tarefas atribuidas");
                                getchar();
                                getchar();
                                break;
                            }
                            break;
                        }
                    }
                }
                if(option1==2){
                        int option3;
                        system("cls");
                        printf("1.Atribuir Tarefa \n");
                        printf("2.Listar Tarefas \n");
                        printf("3.Mover Tarefa \n");
                        printf("4.Adicionar Tarefa nova\n");
                        printf("5.Terminar Tarefa\n");
                        printf("6.Alterar responsavel por tarefa em Doing\n");
                        scanf("%d",&option3);
                        getchar();
                        if(option3==6){
                                int id_t;
                                char name[MAX];
                                t_doing *aux=tarefas->prox;
                                t_pessoas *aux1=pessoas;
                                t_pessoas *aux_t=NULL;
                                if(tarefas->prox==NULL){
                                    printf("Lista Doing nao contem tarefas!");
                                    getchar();
                                    break;
                                }
                                do{
                                imprime_tarefa_pessoas(tarefas);
                                printf("Introduza o id da tarefa que deseja alterar o seu responsavel: ");
                                scanf("%d",&id_t);
                                system("cls");
                                getchar();
                                imprimepessoas(pessoas);
                                printf("introduza o nome do novo responsavel pela tarefa: ");
                                fgets(name,MAX,stdin);
                                strtok(name,"\n");
                                while(aux1!=NULL){
                                    if(strcmp(name,aux1->prox->nome)==0){
                                        aux_t=aux1->prox;
                                        break;
                                    }
                                    aux1=aux1->prox;
                                }
                                while(aux!=NULL){
                                    if(strcmp(name,aux->pessoa->nome)==0){
                                        break;
                                    }
                                    aux=aux->prox;
                                }
                                }while(VerificarMaxTarefa(MAXTAREFA,tarefas,name)==-1 && compara_semana(aux->data.ano,aux->data.dia,aux->data.mes,name,tarefas)==-1);
                                AlterarPesssoa(aux,aux_t,id_t);
                                sort_doing(tarefas);
                                imprime_tarefa_pessoas(tarefas);
                                update_doing1(tarefas);
                                printf("Tarefa alterada com sucesso!");
                                getchar();
                        }

                        if(option3==5){
                             int dia,mes,ano,id_t;
                             char name[MAX];
                            t_pessoas *aux=pessoas;
                            t_doing *aux1=tarefas->prox;

                            system("cls");
                            if(tarefas->prox==NULL){
                                printf("Nao existem tarefas na lista Doing!");
                                getchar();
                                break;
                            }
                            sort_doing(tarefas);
                            imprime_tarefa_pessoas(tarefas);
                            printf("insira o nome da pessoa que tenha terminado a tarefa: ");
                            fgets(name,MAX,stdin);
                            strtok(name,"\n");
                            int ver=strcmp(name,aux1->pessoa->nome);
                            while(ver!=0){
                                if(ver==0){
                                     break;
                                }
                                aux1=aux1->prox;
                                if(aux1==NULL){
                                    printf("insira um nome que esteja na lista Doing! ");
                                    fgets(name,MAX,stdin);
                                    aux1=tarefas->prox;
                                }
                            }
                            system("cls");
                            printf("Introduza a data de conclusao da tarefa\n");
                            printf("Dia: ");
                            scanf("%d",&dia);
                            while(dia<1 || dia>31){
                                    printf("Insira um dia valido \n");
                                    scanf("%d",&dia);
                            }
                            printf("Mes: ");
                            scanf("%d",&mes);
                            while(mes<1 || mes>12){
                                printf("Insira um mes valido \n");
                                scanf("%d",&mes);
                            }
                            printf("Ano: ");
                            scanf("%d",&ano);
                            system("cls");
                            t_data dconc={dia,mes,ano};
                            sort_doing(tarefas);
                            imprime_tarefa_pessoas(tarefas);
                            printf("\n introduza o id da tarefa que %s terminou: ",name);
                            scanf("%d",&id_t);
                            while(id_t!= aux1->id){
                                if(id_t==aux1->id){
                                    break;
                                }
                                aux1=aux1->prox;
                                if(aux1==NULL){
                                    printf("insira um id valido! ");
                                    scanf("%d",&id_t);
                                    aux1=tarefas;
                                }
                            }
                            finishing(tarefas,tarefas_f,id_t,aux,dconc);
                            update_done(tarefas_f);
                            printf("Tarefa terminada com sucesso!");
                        }
                        if (option3==4){
                            char desc[MAX];
                            int id_t,prior;
                            t_tdo *aux=tarefa;
                            printf("Insira uma descricao textual para a tarefa: ");
                            fgets(desc,MAX,stdin);

                            printf("Insira o id da tarefa que deseja adicionar: ");
                            scanf("%d",&id_t);
                            if(aux!=NULL){
                                while(id_t!=aux->id){
                                    if(id_t==aux->id){
                                        printf("Tarefa com o mesmo ID ja existe, por favor insira outro ID");
                                        scanf("%d",&id_t);
                                        aux=tarefa;
                                    }
                                    aux=aux->prox;
                                    if(aux==NULL){
                                        break;
                                    }
                                }
                            }
                            printf("Insira a prioridade da tarefa que deseja adicionar(Note que a prioridade deve estar entre 1 a 10): ");
                            scanf("%d",&prior);
                            if(prior<1 || prior >10){
                                printf("Insira uma prioridade valida! ");
                                scanf("%d",&prior);
                            }
                            inserir_todo(tarefa,desc,id_t,prior);
                            printf("Tarefa adicionada com sucesso!");
                            update_td(tarefa);
                            getchar();
                            getchar();
                        }
                        if(option3==1){
                            int dia,mes,ano,id_t,id_p,c=0;
                            t_pessoas *aux=pessoas;
                            t_tdo *aux1=tarefa;
                            t_doing *aux2=tarefas->prox;
                            int compare;
                            char nome[MAX];
                            if(MAXTAREFA==0){
                            printf("Numero maximo de tarefas que deseja atribuir por pessoa ?");
                            scanf("%d",&MAXTAREFA);
                            }
                            if(tarefa->prox==NULL){
                                printf("Lista To Do nao contem tarefas!");
                                getchar();
                                getchar();
                                break;
                            }
                            system("cls");
                            imprimepessoas(pessoas);
                            printf("insira o id da pessoa que deseja que realize a tarefa: ");
                            scanf("%d",&id_p);
                            while(aux!=NULL){
                                if(id_p==aux->id){
                                      strcpy(nome,aux->nome);
                                      while(aux2!=NULL){
                                            compare=strcmp(aux2->pessoa->nome,nome);
                                            if(compare==0){
                                                c++;
                                            }
                                        aux2=aux2->prox;
                                    }
                                      break;
                                }
                                aux=aux->prox;
                                if(aux==NULL){
                                    printf("insira um id valido! ");
                                    scanf("%d",&id_p);
                                    aux=pessoas;
                                }
                            }
                            if(c>MAXTAREFA){
                                printf("Numero maximo de tarefas excedido para %s!",nome);
                                getchar();
                                getchar();
                                break;
                            }
                            system("cls");
                            do{
                            printf("Introduza o prazo para a tarefa\n");
                            printf("Dia: ");
                            scanf("%d",&dia);
                            while(dia<1 || dia>31){
                                    printf("Insira um dia valido \n");
                                    scanf("%d",&dia);
                            }
                            printf("Mes: ");
                            scanf("%d",&mes);
                            while(mes<1 || mes>12){
                                printf("Insira um mes valido \n");
                                scanf("%d",&mes);
                            }
                            printf("Ano: ");
                            scanf("%d",&ano);
                            while(ano<1900){
                                printf("Insira um ano valido \n");
                                scanf("%d",&ano);
                            }
                            }while(compara_semana(ano,dia,mes,nome,tarefas)==-1);
                            system("cls");
                            t_data dprazo={dia,mes,ano};
                            imprime_todo(tarefa);
                            printf("\n introduza o id da tarefa que %d pretende realizar: ",id_p);
                            scanf("%d",&id_t);
                            while(id_t!= aux1->id){
                                if(id_t==aux1->id){
                                    break;
                                }
                                aux1=aux1->prox;
                                if(aux1==NULL){
                                    printf("insira um id valido! ");
                                    scanf("%d",&id_t);
                                    aux1=tarefa;
                                }
                            }
                            move_to_do(tarefa,tarefas,id_t,aux,dprazo);
                            sort_doing(tarefas);
                            imprime_tarefa_pessoas(tarefas);
                            update_doing1(tarefas);
                            //update_doing(tarefas);
                            update_td(tarefa);
                            printf("Atribuicao bem sucedida!");
                            getchar();
                            getchar();
                            break;
                        }

                    if(option3 ==2){
                        system("cls");
                        printf("1.Tarefas que encontram-se no quadro 'To Do'\n");
                        printf("2.Tarefas que encontram-se no quadro 'Doing'\n");
                        printf("3.Tarefas que encontram-se no quadro 'Done'\n");
                        scanf("%d",&option1);
                        if(option1==1){
                                if(tarefa->prox==NULL){
                                        printf("Lista To Do nao contem tarefas!");
                                        getchar();
                                        getchar();
                                        break;
                                }
                                imprime_todo(tarefa);
                                getchar();
                                getchar();
                                break;
                        }
                        if(option1==2){
                                if(tarefas->prox==NULL){
                                         printf("Lista Doing nao contem tarefas!");
                                         getchar();
                                         getchar();
                                         break;
                                }
                                sort_doing(tarefas);
                                imprime_tarefa_pessoas(tarefas);
                                getchar();
                                getchar();
                                break;
                        }
                        if(option1==3){
                                if(tarefas_f->prox==NULL){
                                    printf("Lista Done nao contem tarefas!");
                                    getchar();
                                    getchar();
                                }
                            imprime_t_done(tarefas_f);
                            getchar();
                            getchar();
                            break;
                        }
                    }
                    if(option3 ==3){
                        system("cls");
                        printf("1.De Doing para To Do \n");
                        printf("2. De Done para Done\n");
                        scanf("%d",&option1);
                        if(option1==1){
                                system("cls");
                                int id_t1;
                                t_doing *aux=tarefas;
                                if(tarefas->prox==NULL){
                                    printf("Quadro Doing nao contem tarefas");
                                    getchar();
                                    break;
                                }
                                sort_doing(tarefas);
                                imprime_tarefa_pessoas(tarefas);
                                printf("\n introduza o id da tarefa que pretende mover: ");
                                scanf("%d",&id_t1);
                                while(aux!=NULL){
                                    if(id_t1==aux->id){
                                        break;
                                    }
                                    aux=aux->prox;
                                    if(aux==NULL){
                                        printf("insira um ID valido! ");
                                        scanf("%d",&id_t1);
                                        aux=tarefas;
                                    }
                                }
                                sort_doing(tarefas);
                                move_doing(tarefas,tarefa,id_t1);
                                printf("Transferencia bem sucedida!");
                                getchar();
                                getchar();
                        }
                        if(option1==2){
                            system("cls");
                                int id_t;
                                t_done *aux=tarefas_f;
                                if(tarefas_f->prox==NULL){
                                    printf("Quadro Done nao contem tarefas");
                                    getchar();
                                    break;
                                }
                                imprime_t_done(tarefas_f);
                                printf("\n introduza o id da tarefa que pretende mover: ");
                                scanf("%d",&id_t);
                                 while(aux!=NULL){
                                    if(id_t==aux->id){
                                        break;
                                    }
                                    aux=aux->prox;
                                    if(aux==NULL){
                                        printf("insira um ID valido! ");
                                        scanf("%d",&id_t);
                                        aux=tarefas_f;
                                    }
                                }
                                move_done(tarefas_f,tarefa,id_t);
                                printf("Transferencia bem sucedida!");
                                getchar();
                                getchar();
                        }
                }
                }
                break;
            case 3:
                printf("Deseja guardar antes de sair? S ou N: ");
                char opt;
                scanf("%s",&opt);
                opt=toupper(opt);
                if(opt=='S'){
                    updateall(tarefas_f,tarefas,tarefa,pessoas);
                    printf("As alteracoes foram guardadas!");
                }
                else
                    exit(0);
                break;
        }
}
    return 0;
}


