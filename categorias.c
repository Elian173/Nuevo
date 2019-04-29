#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "categorias.h"
#include "validar.h"


int iniciarCategorias(eCategoria* lista, int TAM_CATEGORIAS){ // bien!
    int retorno = -1;
    int* cont = (int*) malloc(sizeof(int));
    if(TAM_CATEGORIAS > 0 && lista != NULL){
        retorno = 0;
        for(*cont = 0; *cont < TAM_CATEGORIAS; (*cont)++){
            (lista+(*cont))->isEmpty = 1;
        }
    }
    free(cont);
    return retorno;
}

void getCategoria(eCategoria* lista, int TAM_CATEGORIAS, int juegoIdCat, char* cadena){
    int* contador = (int*) malloc(sizeof(int));
    for(*contador = 0; *contador < TAM_CATEGORIAS; (*contador)++){
        if((lista+(*contador))->id == juegoIdCat){
            strcpy(cadena, (lista+(*contador))->descripcion);
        }
    }
    free(contador);
}

int menuSeleccionarCategoria(eCategoria* lista, int TAM_CATEGORIAS){
    int opcion, control;
    system("cls");
    printf("\n ****  Menu de Categorias  ****\n\n");
    mostrarListadoDeCategorias(lista, TAM_CATEGORIAS);
    control = getInt(&opcion, "\nSeleccione Categoria: ", "Error, ingrese una categoria de la lista: ", 1, 5, 3);
    if(control == 0){
        opcion = 0;
    }
    return opcion;
}

void mostrarListadoDeCategorias(eCategoria* lista, int TAM_CATEGORIAS){
    printf("   ****  Listado de Categorias  **** \n\n");
    printf("id   Descripcion\n\n");
    for(int contador=0; contador < TAM_CATEGORIAS; contador++){
        mostrarCategoria(lista+contador);
    }
    printf("\n");
}

void mostrarCategoria(eCategoria* categoria){
    printf("%2d %10s\n", categoria->id, categoria->descripcion);
}

void hardcodearCategorias(eCategoria* lista, int TAM_CATEGORIAS){
    eCategoria nuevaLista[]={
        { 1, "mesa"},
        { 2, "azar"},
        { 3, "estrategia"},
        { 4, "salon"},
        { 5, "magia"}
    };
    for(int contador=0; contador<TAM_CATEGORIAS; contador++){
        *(lista+contador) = *(nuevaLista+contador);
    }
}
