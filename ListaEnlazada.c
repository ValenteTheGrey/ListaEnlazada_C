//
// Created by Martin Valente on 30/04/2026.
//

#include "ListaEnlazada.h"

void reinsertar_nodo(tLista* pl, tLista* men);

void crearLista(tLista* pl)
{
    *pl = NULL;
}

int ponerPrimeroLista(tLista* pl, const void* pd, size_t tam)
{
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue)
        return LISTA_LLENA;

    nue->info = malloc(tam);
    if(!nue->info) {
        free(nue);
        return LISTA_LLENA;
    }

    nue->tamInfo = tam;
    memcpy(nue->info, pd, tam);
    nue->sig = *pl;

    *pl = nue;

    return TODO_OK;
}

int sacarPrimeroLista(tLista* pl, void* pd, size_t tam)
{
    tNodo* elim = *pl;
    if(!*pl)
    {
        return LISTA_VACIA;
    }

    memcpy(pd, elim->info, MINIMO(elim->tamInfo, tam));
    *pl = elim->sig;

    free(elim->info);
    free(elim);

    return TODO_OK;

}



int ponerUltimoLista(tLista* pl, const void* pd, size_t tam)
{
    tNodo* nue;

    while(*pl)
    {
        pl = &(*pl)->sig;
    }

    nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue)
        return LISTA_LLENA;

    nue->info = malloc(tam);
    if(!nue->info){
        free(nue);
        return LISTA_LLENA;
    }

    nue->tamInfo = tam;
    memcpy(nue->info, pd, tam);
    nue->sig = *pl;  // esto es NULL al salir del while

    *pl = nue;      //ahora apunta al nuevo nodo, pl contiene &(*pl)->sig del penultimo

    return TODO_OK;
}

/*
tLista*       tLista        tNodo
pl ---------> p ----------> [[info] [tamInfo] [sig]]

tLista*  pl = tNodo ** pl
&(*pl)->sig = &((*pl)->sig) por precedencia
&(*pl)->sig es la dirección de (*pl)->sig

Al pasar &lista a una función como parámetro *pl le estamos copiando la dirección de lista.
Recordar que los parámetros siempre se pasan por valor, se copian.
Modificamos lista al desreferenciar y modificar a donde apunta la dirección.

 */

int ponerPosLista(tLista* pl, const void* pd, size_t tam, unsigned pos)
{
    tNodo* nue;

    //La primera posicion es 0 con este criterio
    while(*pl && pos)
    {
        pl = &(*pl)->sig;
        pos--;
    }

    if(pos)
        return POSICION_INVALIDA;

    nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue)
        return LISTA_LLENA;

    nue->info = malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return LISTA_LLENA;
    }

    nue->tamInfo = tam;
    memcpy(nue->info, pd, tam);
    nue->sig = *pl;

    *pl = nue;

    return TODO_OK;

}

int ponerOrdenLista(tLista* pl, const void* pd, size_t tam, int (*cmp)(const void*, const void*))
{
    tNodo* nue;
    int rc;

    while(*pl && (rc= cmp(pd, (*pl)->info)) > 0 )
        pl = &(*pl)->sig;

    if(*pl && !rc)
        return DUPLICADO;

    nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue)
        return LISTA_LLENA;

    nue->info = malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return LISTA_LLENA;
    }

    nue->tamInfo = tam;
    memcpy(nue->info, pd, tam);
    nue->sig = *pl;

    *pl = nue;

    return TODO_OK;

}

int sacarElemLista(tLista* pl, void* pd, size_t tam, int (*cmp)(const void*, const void*))
{
    tNodo* elim;

    while(*pl && cmp(pd, (*pl)->info) != 0)
        pl = &(*pl)->sig;

    if(!*pl)
        return NO_EXISTE;

    elim = *pl;
    memcpy(pd, elim->info, MINIMO(tam, elim->tamInfo));

    *pl = elim->sig;
    free(elim->info);
    free(elim);

    return TODO_OK;

}

int sacarElemOrdLista(tLista* pl, void* pd, size_t tam, int (*cmp)(const void*, const void*))
{
    tNodo* elim;
    int rc;

    while(*pl && (rc=cmp(pd, (*pl)->info)) > 0)
        pl = &(*pl)->sig;

    if(!*pl || rc)
        return NO_EXISTE;

    elim = *pl;
    memcpy(pd, elim->info, MINIMO(tam, elim->tamInfo));

    *pl = elim->sig;
    free(elim->info);
    free(elim);

    return TODO_OK;
}



void recorrerLista(tLista* pl, void (*accion)(void*, void*), void* param)
{
    while(*pl)
    {
        accion((*pl)->info, param);
        pl =&(*pl)->sig;
    }
}


void ordenarSelLista(tLista* pl, int (*cmp)(const void*, const void*))
{


    while(*pl)
    {
        tLista* men = buscarMenorLista(pl, cmp);
        if(pl != men)
            //reinsertar_nodo(pl,men)

        pl = &(*pl)->sig;
    }




}

void reinsertar_nodo(tLista* pl, tLista* men)
{
    tNodo* aux = *men;
    *men = aux->sig;

    aux->sig = *pl;
    *pl = aux;
}

tLista* buscarMenorLista(tLista* pl, int (*cmp)(const void*, const void*))
{
    tLista* men = pl;     //no puedo manejarlo como puntero a tNodo pq pierdo la referencia del anterior

    if(*pl)                   //tNodo*
        pl = &(*pl)->sig;     //pl es tNodo** entonces *pl es tNodo* y (*pl)-> es **pl o sea tNodo
                              //tNodo sig es un puntero a otro nodo, es decir es un tNodo*
    while(*pl)
    {
        if(cmp((*men)->info, (*pl)->info) > 0)
            men = pl;

        pl= &(*pl)->sig;
    }

    return men;

}

/*

void* reduce(tLista* pl, void (*accion)(const void*, void*, void*), void* params, void* result)
{

    return result;
}



void filter(tLista* pl, int (*verif)(const void*, const void*), const void* param)    verif V o F
{
    while(*pl)
    {
        if(!verif(*pl->info, param)
        {
            tNodo* elim = *pl;
            *pl = elim->sig;
            free(elim->sig);
            free(elim);
        }else{
            pl = &(*pl)->sig;
        }
    }
}






*/
