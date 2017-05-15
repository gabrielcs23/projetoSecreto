#ifndef ARVDIR_H_INCLUDED
#define ARVDIR_H_INCLUDED

// FALTOU O IMPRIME

//definição da estrutura de árvore de diretório
typedef struct coarv{
    struct coarv *pai, *filho, *irmao;
    int marcado; // 0 desmarcado, 1 marcado, 2 marcado e desmarcado
    int tipo; // -1 vertice, tipo 0 ou tipo 1
    int id; // nome do vertice caso seja vertice do grafo senao -1
    int f = 0;
    int mf = 0;
    int f_marcados = 0;
}TCA;

//definição dos métodos básicos de árvores
TCA *cria (int tipo,int id){
    TCA *a = (TCA*) malloc (sizeof(TCA));
    a->pai = NULL;
    a->filho = NULL;
    a->irmao = NULL;
    a->tipo = tipo;
    a->id = id;
    return a;
};

//inserção de subarvore "filho" em uma arvore "pai"
void inserir (TCA *afilho, TCA *apai){
    afilho->irmao = apai->filho;
    if(apai)
        apai->f++;
    afilho->pai = apai;
    apai->filho = afilho;
}

//liberar arvore da memoria
void liberar (TCA *a){
    TCA *p = a->filho;
    while(p){
        TCA *t = p->irmao;
        liberar(p);
        p = t;
    }
    free(a);
}
/*
//mover nó a para ser filho de nó b
void mover(TCA *a, TCA*b){
    if(a == a->pai->filho){
        a->pai->filho = a->irmao;
    } else {
        TCA *p = a->pai->filho;
        while(p->irmao != a) p = p->irmao;
        p->irmao = a->irmao;
    }
    a->pai = b;
    a->irmao = b->filho;
    b->filho = a;
    if(!a->arquivo){
        TDir *aux = (TDir*)b->info;
        aux->num_dir++;
    }
    else{
        TDir *aux = (TDir*)b->info;
        aux->num_arq++;
    }
}
*/
//remove um nó e seus filhos
void destruir (TCA *a){
    TCA *i;
    i = a->pai->filho;
    if(i == a) a->pai->filho = a->irmao;
    else{
        while (i->irmao != a) i = i->irmao;
        i->irmao = a->irmao;
    }
    liberar(a);
}

//busca e retorna o nó com o nome procurando-o na subárvore a
TCA* busca (TCA* a, char *c){
    if(!a) return NULL;
    if(a->id == id) return a;
    TCA *r, *p;
    for(p=a->filho;p;p=p->irmao){
        r = busca(p,c);
        if(r) return r;
    }
    return NULL;
}
/*
int f(TCA *a){
    TCA *f = a->filho;
    if(!f) return 0;
    int retorno = 1;
    while(f){
        f = f->irmao;
        retorno++;
    }
    return retorno;
}

int mf(TCA *a){
    TCA *f = a->filho;
    if(!f) return 0;
    int retorno = 0;
    while(f){
        if(f->marcado == 2)
            retorno++;
        f = f->irmao;
    }
    return retorno;
}
*/
TCA *marca_aux(TG *g, TCA *a, int x){
    if(!a) return NULL;
    if(a->id != -1){
        if(buscaAresta(g,a->id,x)){
            a->marcado = 1;
            if(a->pai)
                a->pai->f_marcados++;
        }
    }
    TCA *i;
    for(i=a->filho;i;i=i->irmao){
        i = marca_aux(g,i,x);
    }
    return NULL;
}

void marca_desmarca(TCA *T){
    TCA *u;
    for(u=T->filho;u;u->irmao){
        marca_desmarca(u);
        if((u->marcado == 1) && (u->f==u->mf)){
            u->marcado = 2;
            u->mf = 0;
            if(u->pai){
                u->pai->marcado = 1;
                u->pai->mf++;
                if(u->pai->pai)
                    u->pai->pai->f_marcados++;
            }
        }
    }
}

int vertice_marcado(TCA *T){
    if(T->marcado == 1)
        return 1;
    TCA *u;
    for(u=T->filho;u;u->irmao){
        if(vertice_marcado(u))
            return 1;
    }
    return 0;
}

void reset(TCA *T){
    if(T){
        T->marcado = 0;
        T->mf = 0;
        T->f_marcados = 0;
        TCA *v;
        for(v = T->filho;v;v->irmao){
            reset(v);
        }
    }
    else if(!T->pai){
        printf("Co-arvore nao possui nos\n");
        exit(1);
}

void marcar(TCA *T, TG *x){
    reset(T);
    marca_aux(x,T,x->id);
    marca_desmarca(T);
    if(T->f == 1 && vertice_marcado(T))
        T->marcado == 1;
}

void adicionar_vertice(TCA *t, int id){
    TCA *no = cria(-1,id);
    inserir(no,t);
}

int reconhece_cografos(TG *g){
    TCA *r = cria(1,-1);
    TG *v1 = g, *v2 = g->prox;
    if(buscaAresta(v1,v2){
        adicionar_vertice(r,v1->id);
        adicionar_vertice(r,v2->id);
    }
    else{
        TCA *n = cria(0,-1);
        inserir(n,r);
        TCA *v = cria(-1,v1->id);
        inserir(v,n);
        v = cria(-1,v2->id);
        inserir(v,n);
    }
    TCA *x;
    for(x = v2->prox;x;x = x->prox){
        marcar(r,x);
        if(ver_marca(r,2)){
            TCA *ins = cria(-1,x->id);
            inserir(ins,r);
            continue;
        }
        if(ver_marca(r,0){
            if(r->f == 1){
                TCA *ins = cria(-1, x->id);
                inserir(ins,r->filho);
            }
            else{
                TCA *novor = cria(1,-1);
                TCA *filhor = cria(0, -1);
                inserir(filhor, novor);
                TCA *ins = cria(-1, x->id);
                inserir(ins, filhor);
                inserir(r, filhor);
                r = &novor;
            }
            continue;
        }
        TCA *u = encontrar_no();
        //implementar encontrar_no e encontrar o vertice w
        if(u->tipo == 0){
            if(u->mf == 1){
                if(w->pai == u){
                    
                }
            }
        }    
    }    
}
// FALTOU O IMPRIME, ANIMAL

#endif // ARVDIR_H_INCLUDED
