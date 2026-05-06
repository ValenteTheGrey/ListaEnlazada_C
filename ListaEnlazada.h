//
// Created by Martin Valente on 30/04/2026.
//

#ifndef LISTAENLAZADA_LISTAENLAZADA_H
#define LISTAENLAZADA_LISTAENLAZADA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TODO_OK 0
#define LISTA_LLENA 1
#define LISTA_VACIA 2
#define POSICION_INVALIDA 3
#define DUPLICADO 4
#define NO_EXISTE 5

#define MINIMO(a,b)     ((a) < (b) ? (a) : (b))

typedef struct sNodo
{
    void* info;
    size_t tamInfo;
    struct sNodo * sig;
}tNodo;

typedef tNodo* tLista;

void crearLista(tLista* pl);
int ponerPrimeroLista(tLista* pl, const void* d, size_t tam);
int sacarPrimeroLista(tLista* pl, void* d, size_t tam);
int ponerUltimoLista(tLista* pl, const void* pd, size_t tam);
int ponerPosLista(tLista* pl, const void* pd, size_t tam, unsigned pos);
int ponerOrdenLista(tLista* pl, const void* pd, size_t tam, int (*cmp)(const void*, const void*));
int sacarElemLista(tLista* pl, void* pd, size_t tam, int (*cmp)(const void*, const void*));
int sacarElemOrdLista(tLista* pl, void* pd, size_t tam, int (*cmp)(const void*, const void*));

void recorrerLista(tLista* pl, void (*accion)(void*, void*), void* param);
void ordenarSelLista(tLista* pl, int (*cmp)(const void*, const void*));
tLista* buscarMenorLista(tLista* pl, int (*cmp)(const void*, const void*));


/*
map: recorre la lista y para cada elemento realiza una accion
filter: recibe una condicion y decide si el elemento se tiene que quedar o no en la lista
reduce: reduce todo a un solo resultado, ejemplo suma de todo, resta de todo luego de recorrer todos los valores
sort: Ordenar


//Hacer
//void buscarElemento



*/

#endif //LISTAENLAZADA_LISTAENLAZADA_H
