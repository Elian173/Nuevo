#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "juegos.h"
#include "categorias.h"
#include "validar.h"

#define OCUPADO 0
#define VACIO 1

int iniciarJuegos(eJuego* lista, int TAM_JUEGOS){ // bien!
    int retorno = -1;
    int* contador = (int*) malloc(sizeof(int));
    if(TAM_JUEGOS > 0 && lista != NULL){
        retorno = 0;
        for(*contador=0; *contador < TAM_JUEGOS; (*contador)++){
            (lista+(*contador))->isEmpty = VACIO;
        }
    }
    free(contador);
    return retorno;
}

int buscarJuego(eJuego* lista, int TAM_JUEGOS, int codigo){
    int indice = -1;
    int* contador = (int*) malloc(sizeof(int));
    if(TAM_JUEGOS > 0 && lista != NULL){
        indice = -2;
        for(*contador=0; *contador < TAM_JUEGOS; (*contador)++){
            if((lista+(*contador))->codigo == codigo && (lista+(*contador))->isEmpty == OCUPADO){
                indice = *contador;
                break;
            }
        }
    }
    free(contador);
    return indice;
}

int buscarLibreJuegos(eJuego* lista, int TAM_JUEGOS){
    int indice = -1;
    int* contador = (int*) malloc(sizeof(int));
    if(TAM_JUEGOS > 0 && lista != NULL){
        indice = -2;
        for(*contador=0; *contador < TAM_JUEGOS; (*contador)++){
            if((lista+(*contador))->isEmpty == OCUPADO){
                indice = *contador;
                break;
            }
        }
    }
    free(contador);
    return indice;
}

int comprobarRegistroJuegos(eJuego* lista, int TAM_JUEGOS){
    int bandera = -1;
    int* contador = (int*) malloc(sizeof(int));
    if(TAM_JUEGOS > 0 && lista != NULL){
        for(*contador=0; *contador < TAM_JUEGOS; (*contador)++){
            if((lista+(*contador))->isEmpty == OCUPADO){
                bandera = *contador;
                break;
            }
        }
    }
    free(contador);
    return bandera;
}

void mostrarJuego(eJuego* juego, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS){
    char* descCategoria = (char*) malloc(sizeof(char)*20);
    char* descMarca = (char*) malloc(sizeof(char)*20);
    getCategoria(categorias, TAM_CATEGORIAS, juego->idCategoria, descCategoria);
    getMarca(marcas, TAM_MARCAS, juego->idMarca, descMarca);
    printf("%5d %14s   %10s  %7.2f   %10s\n", juego->codigo, juego->descripcion, descMarca, juego->importe, descCategoria);
    free(descCategoria);
    free(descMarca);
}

void mostrarListadoDeJuegos(eJuego* lista, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS){
    int* contador = (int*) malloc(sizeof(int));
    printf("   ****  Listado de Juegos  **** \n\n");
    printf("Codigo   Descripcion    Marca   Importe    Categoria\n\n");
    for(*contador=0; *contador < TAM_JUEGOS; (*contador)++){
        mostrarJuego((lista+(*contador)), categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
    }
    printf("\n");
    free(contador);
}

int menuSeleccionarJuego(eJuego* lista, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS){
    int opcion;
    int* control = (int*) malloc(sizeof(int));
    if(lista != NULL && categorias != NULL){
        system("cls");
        mostrarListadoDeJuegos(lista, TAM_JUEGOS, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
        *control = getInt(&opcion, "\nSeleccione Juego: ", "Error, ingrese un juego de la lista: ", 1, 10, 3);
        if(*control == 0){
            opcion = 0;
        }
    }
    free(control);
    return opcion;
}

int ingresarJuego(eJuego* lista, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS){
    int* indice = (int*) malloc(sizeof(int));
    int* opcionCat = (int*) malloc(sizeof(int));
    int* opcionMarca = (int*) malloc(sizeof(int));
    int control;
    eJuego* nuevoJuego = (eJuego*) malloc(sizeof(eJuego));

    *indice = buscarLibreJuegos(lista, TAM_JUEGOS);
    system("cls");
    printf("*** Alta Juegos ***\n\n");
    if(*indice == -1){
        control = -1;
    }else{
        nuevoJuego->codigo = *indice + 1;
        control = getString(nuevoJuego->descripcion, "Ingrese descripcion: ", "Error, ingrese solo letras respetando el rango (3 - 20): ", 3, 20, 3);
        if(control == 0){
            printf("\nSe agotaron las chances y no se pudo ingresar la descripcion.\n\n");
        }else{
            control = getFloat(&nuevoJuego->importe, "Ingrese importe: ", "Error, ingrese solo numeros respetando el rango (100.00 - 500.00): ", 100.00, 500.00, 3);
            if(control == 0){
                printf("\nSe agotaron las chances y no se pudo ingresar el importe.\n\n");
            }else{
                *opcionCat = menuSeleccionarCategoria(categorias, TAM_CATEGORIAS);
                *opcionMarca = menuSeleccionarMarca(marcas, TAM_MARCAS);
                if(control == 0){
                    printf("\nSe agotaron las chances y no se pudo ingresar la categoria.\n\n");
                }else{
                    nuevoJuego->idCategoria = *opcionCat;
                    nuevoJuego->idMarca = *opcionMarca;
                    nuevoJuego->isEmpty = OCUPADO;
                    *(lista+(*indice)) = *nuevoJuego;
                }
            }
        }
    }
    free(indice);
    free(opcionCat);
    free(opcionMarca);
    free(nuevoJuego);
    return control;
}

int modificarJuego(eJuego* lista, int TAM_JUEGOS, int *codigo, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS){
    int* indice = (int*) malloc(sizeof(int));
    int* control = (int*) malloc(sizeof(int));
    int bandera;
    char* seguir = (char*) malloc(sizeof(char));

    system("cls");
    printf("  *** Modificar juego ***\n\n");
    *control = getInt(codigo, "Ingrese codigo de juego: ", "Error, ingrese solo numeros respetando el rango (1 - 10): ", 1, 10, 3);
    if(*control != 1){
        bandera = 0;
        printf("\nNo se obtuvo el codigo de juego.");
    }else{
        *indice = buscarJuego(lista, TAM_JUEGOS, *codigo);
        if(*indice == -1){
            bandera = -1;
        }else{
            printf("Codigo   Descripcion   Marca   Importe    Categoria\n\n");
            mostrarJuego((lista+(*indice)), categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);// d
            printf("\nDesea modificar algun campo? s/n: ");
            fflush(stdin);
            scanf("%c", seguir);
            *control = validarRespuesta(seguir);
            while(*control != 1){
                printf("Error, solo debe ingresar 's' o 'n', reingrese: ");
                fflush(stdin);
                scanf("%c", seguir);
            }
            if(*seguir == 'n' || *seguir == 'N'){
                bandera = 0;
            }else{
                bandera = menuModificarJuego(lista, *indice, TAM_JUEGOS);
            }
        }
    }
    free(indice);
    free(control);
    free(seguir);
    return bandera;
}

int menuModificarJuego(eJuego* lista, int indice, int TAM_JUEGOS){ // bien!
    int* opcion = (int*) malloc(sizeof(int));
    int control;
    int* nuevaIdCat = (int*) malloc(sizeof(int));
    int* nuevaIdMarca = (int*) malloc(sizeof(int));
    char* nuevaDesc = (char*) malloc(sizeof(char)*20);
    float* nuevoImporte = (float*) malloc(sizeof(float));

    system("cls");
    printf("\nSeleccione el campo que desea modificar: \n\n");
    printf(" 1- Descripcion\n");
    printf(" 2- Importe\n");
    printf(" 3- Id Categoria\n");
    printf(" 4- Id Marca\n\n");
    control = getInt(opcion, "Ingrese opcion: ", "Error, opcion invalida. Reingrese: ", 1, 4, 3);
    switch(*opcion){
        case 1:
            control = getString(nuevaDesc, "\n\nIngrese nueva descripcion: ", "Error, ingrese solo letras respetando el rango (3 a 19): ", 3, 19, 3);
            if(control == 0){
                printf("\nNo se pudo registrar la descripcion!");
            }else{
                strcpy((lista+indice)->descripcion, nuevaDesc);
            }
            break;
        case 2:
            control = getFloat(nuevoImporte, "\n\nIngrese nuevo importe: ", "\nError, ingrese solo numeros respetando el rango (100 - 500): ", 100, 500, 3);
            if(control == 0){
                printf("\nNo se pudo registrar el importe!\n");
            }else{
                (lista+indice)->importe = *nuevoImporte;
            }
            break;
        case 3:
            control = getInt(nuevaIdCat, "\nIngrese nueva Id de Categoria: ", "Error, ingrese solo numeros respetando el rango (1 - 5). Reingrese: ", 1, 5, 3);
            if(control == 0){
                printf("\nNo se pudo registrar la nueva Id de Categoria\n");
            }else{
                (lista+indice)->idCategoria = *nuevaIdCat;
            }
            break;
        case 4:
            control = getInt(nuevaIdMarca, "\nIngrese nueva Id de Marca: ", "Error, ingrese solo numeros respetando el rango (1 - 5). Reingrese: ", 1, 5, 3);
            if(control == 0){
                printf("\nNo se pudo registrar la nueva Id de Marca\n");
            }else{
                (lista+indice)->idMarca = *nuevaIdMarca;
            }
            break;
        default:
            break;
    }
    free(opcion);
    free(nuevaIdCat);
    free(nuevaIdMarca);
    free(nuevaDesc);
    free(nuevoImporte);
    return control;
}

int bajaJuego(eJuego* lista, int TAM_JUEGOS, int *codigo, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS){
    int* indice = (int*) malloc(sizeof(int));
    int* control = (int*) malloc(sizeof(int));
    int bandera;
    char* seguir = (char*) malloc(sizeof(char));

    system("cls");
    printf("  *** Baja Juego ***\n\n");
    *control = getInt(codigo, "Ingrese codigo de Juego: ", "Error, ingrese solo numeros respetando el rango (1 - 10): ", 1, 10, 3);
    if(*control != 1){
        bandera = 0;
        printf("\nNo se obtuvo el codigo de Juego.");
    }else{
        *indice = buscarJuego(lista, TAM_JUEGOS, *codigo);
        if(*indice == -1){
            bandera = -1;
        }else{
            printf("Codigo   Descripcion   Marca  Importe    Categoria\n\n");
            mostrarJuego((lista+(*indice)), categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);// d
            printf("\nConfirma baja? s/n: ");
            fflush(stdin);
            scanf("%c", seguir);
            *control = validarRespuesta(seguir);
            while(*control != 1){
                printf("Error, solo debe ingresar 's' o 'n', reingrese: ");
                fflush(stdin);
                scanf("%c", seguir);
            }
            if(*seguir == 'n' || *seguir == 'N'){
                bandera = 0;
            }else{
                (lista+(*indice))->isEmpty = VACIO;
                bandera = 1;
            }
        }
    }
    free(indice);
    free(control);
    free(seguir);
    return bandera;
}

void hardcodearJuegos(eJuego* lista, int TAM_JUEGOS){
    int* contador = (int*) malloc(sizeof(int));
    eJuego nuevaLista[10] ={
        { 1, "bodoo", 1, 150, 5, 0},
        { 2, "bingo", 5, 120, 2, 0},
        { 3, "pictionary", 4, 160, 4, 0},
        { 4, "ajedrez", 2, 120, 3, 0},
        { 5, "ludo", 1, 150, 1, 0},
        { 6, "chin-chon", 3, 140, 1, 0},
        { 7, "billar", 5, 180, 4, 0},
        { 8, "generala", 3, 140, 2, 0},
        { 9, "TEG", 2, 170, 3, 0},
        { 10, "cadabra", 4, 130, 5, 0}
    };
    for(*contador = 0; *contador < TAM_JUEGOS; (*contador)++){
        *(lista+(*contador)) = *(nuevaLista+(*contador));
    }
    free(contador);
}

void mostrarListadoDeJuegos_queNoSuperanElImportePromedio(eJuego* lista, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS, float* promedio, eMarca* marcas, int TAM_MARCAS){
    int* contador = (int*) malloc(sizeof(int));
    int* cantJuegos = (int*) malloc(sizeof(int));
    *cantJuegos = 0;
    if(lista != NULL && categorias != NULL){
        printf("   ****  Listado de Juegos  **** \n\n");
        printf("Codigo   Descripcion   Marca  Importe    Categoria\n\n");
        for(*contador=0; *contador < TAM_JUEGOS; (*contador)++){
            if((lista+(*contador))->importe <= *promedio){
                mostrarJuego((lista+(*contador)), categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
                (*cantJuegos)++;
            }
        }
        printf("\n");
        printf("El Importe Promedio por juegos alquilados es: %.2f\n", *promedio);
        printf("La cantidad de juegos que no superan el promedio es: %d\n\n", *cantJuegos);
    }
    free(contador);
    free(cantJuegos);
}

eJuego* inicializarEnCero(eJuego* juegos, int TAM_JUEGOS){
    int* contador = (int*) malloc(sizeof(int));

    for(*contador = 0; *contador < TAM_JUEGOS; (*contador)++){
        (juegos+(*contador))->codigo = 0;
        strcpy((juegos+(*contador))->descripcion, " ");
        (juegos+(*contador))->idCategoria = 0;
        (juegos+(*contador))->importe = 0;
        (juegos+(*contador))->isEmpty = 0;
    }
    free(contador);
    return juegos;
}

void listarJuegosOrdenadosXimporteDescendente(eJuego* juegos, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS){
    int* contador = (int*) malloc(sizeof(int));
    int* count = (int*) malloc(sizeof(int));
    eJuego* auxJuegos = (eJuego*) malloc(sizeof(eJuego));
    system("cls");
    for(*contador = 0; *contador < TAM_JUEGOS-1; (*contador)++){
        for(*count = *contador+1; *count < TAM_JUEGOS; (*count)++){
            if((juegos+(*contador))->importe < (juegos+(*count))->importe){
                *auxJuegos = *(juegos+(*count));
                *(juegos+(*count)) = *(juegos+(*contador));
                *(juegos+(*contador)) = *auxJuegos;
            }
        }
    }
    mostrarListadoDeJuegos(juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);

    free(auxJuegos);
    free(count);
    free(contador);
}

void getMarca(eMarca* lista, int TAM_MARCAS, int juegoIdMarca, char* cadena){
    int* contador = (int*) malloc(sizeof(int));
    for(*contador = 0; *contador < TAM_MARCAS; (*contador)++){
        if((lista+(*contador))->idMarca == juegoIdMarca){
            strcpy(cadena, (lista+(*contador))->nombre);
        }
    }
    free(contador);
}

int menuSeleccionarMarca(eMarca* lista, int TAM_MARCAS){
    int opcion, control;
    system("cls");
    printf("\n ****  Menu de Marcas  ****\n\n");
    mostrarListadoDeMarcas(lista, TAM_MARCAS);
    control = getInt(&opcion, "\nSeleccione Marca: ", "Error, ingrese una marca de la lista: ", 1, 5, 3);
    if(control == 0){
        opcion = 0;
    }
    return opcion;
}

void mostrarListadoDeMarcas(eMarca* lista, int TAM_MARCAS){
    printf("   ****  Listado de Marcas  **** \n\n");
    printf("id   Nombre\n\n");
    for(int contador=0; contador < TAM_MARCAS; contador++){
        mostrarMarca(lista+contador);
    }
    printf("\n");
}

void mostrarMarca(eMarca* marca){
    printf("%2d %10s\n", marca->idMarca, marca->nombre);
}

void hardcodearMarca(eMarca* lista, int TAM_MARCAS){
    eMarca nuevaLista[]={
        { 1, "Ditoys"},
        { 2, "Vulcanita"},
        { 3, "Yetem"},
        { 4, "Ruibal"},
        { 5, "TopToys"}
    };
    for(int contador=0; contador<TAM_MARCAS; contador++){
        *(lista+contador) = *(nuevaLista+contador);
    }
}

void JuegosDeUnaMarcaDeterminada(eJuego* juegos, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS){
    int opcion;
    system("cls");
    opcion = menuSeleccionarMarca(marcas, TAM_MARCAS);
    printf("\n   ****  Listado de Juegos  **** \n\n");
    printf("Codigo   Descripcion   Marca  Importe    Categoria\n\n");
    for(int contador = 0; contador < TAM_JUEGOS; contador++){
        for(int count = 0; count < TAM_MARCAS; count++){
            if((juegos+contador)->idMarca == opcion){
                if((marcas+count)->idMarca == opcion){
                    mostrarJuego((juegos+contador), categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
                }
            }
        }
    }
    printf("\n");
    mostrarListadoDeJuegos(juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
    printf("\n");
}
