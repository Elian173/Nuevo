#include <stdio.h>
#include <stdlib.h>
#include "alquileres.h"
#include "validar.h"

#define OCUPADO 0
#define VACIO 1

int iniciarAlquileres(eAlquiler* lista, int TAM_ALQUILERES){ // bien!
    int retorno = -1;
    if(TAM_ALQUILERES > 0 && lista != NULL){
        retorno = 0;
        for(int contador=0; contador < TAM_ALQUILERES; contador++){
            (lista+contador)->isEmpty = 1;
        }
    }
    return retorno;
}

int buscarLibreAlquileres(eAlquiler* lista, int TAM_ALQUILERES){
    int indice = -1;
    if(TAM_ALQUILERES > 0 && lista != NULL){
        indice = -2;
        for(int contador=0; contador < TAM_ALQUILERES; contador++){
            if((lista+contador)->isEmpty == 1){
                indice = contador;
                break;
            }
        }
    }
    return indice;
}

int buscarAlquiler(eAlquiler* lista, int TAM_ALQUILERES, int codigo){
    int indice = -1;
    if(TAM_ALQUILERES > 0 && lista != NULL){
        indice = -2;
        for(int contador=0; contador < TAM_ALQUILERES; contador++){
            if((lista+contador)->codigoDeAlquiler == codigo && (lista+contador)->isEmpty == OCUPADO){
                indice = contador;
                break;
            }
        }
    }
    return indice;
}

int comprobarRegistroAlquiler(eAlquiler* lista, int TAM_ALQUILERES){
    int bandera = -1;
    if(TAM_ALQUILERES > 0 && lista != NULL){
        for(int contador=0; contador < TAM_ALQUILERES; contador++){
            if((lista+contador)->isEmpty == OCUPADO){
                bandera = contador;
                break;
            }
        }
    }
    return bandera;
}

int ingresarAlquiler(eAlquiler* lista, int TAM_ALQUILERES, eCliente* clientes, int TAM_CLIENTES, eJuego* juegos, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS){
    int* indice = (int*) malloc(sizeof(int));
    int control;
    int* codigoCliente = (int*) malloc(sizeof(int));
    char* respuesta = (char*) malloc(sizeof(char));
    eAlquiler* nuevoAlquiler = (eAlquiler*) malloc(sizeof(eAlquiler));
    eFecha* nuevaFecha = (eFecha*) malloc(sizeof(eFecha));

    if(lista != NULL && clientes != NULL && juegos != NULL && categorias != NULL){
        *indice = buscarLibreAlquileres(lista, TAM_ALQUILERES);
        system("cls");
        printf("*** Alta Alquiler ***\n\n");
        if(*indice == -1){
            control = -1;
        }else{
            nuevoAlquiler->codigoDeAlquiler = *indice + 1;
            control = menuSeleccionarJuego(juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS);
            if(control == 0){
                printf("\nSe agotaron las chances y no se pudo ingresar el codigo de juego.\n");
            }else{
                nuevoAlquiler->codigoDeJuego = control;
                control = getInt(codigoCliente, "Ingrese codigo de cliente: ", "Error, ingrese solo numeros respetando el rango (1 - 10): ", 1, 10, 3);
                *indice = buscarCliente(clientes, TAM_CLIENTES, *codigoCliente);
                if(*indice == -1){
                    printf("\nNo se encontro el cliente correspondiente al codigo %i", nuevoAlquiler->codigoDeCliente);
                }else{
                    nuevoAlquiler->codigoDeCliente = *codigoCliente;
                    printf("\nCodigo   Nombre   Sexo      Telefono\n");
                    mostrarCliente(clientes+(*indice));
                    control = getCharResp(respuesta, "\nConfirmar cliente?.. s/n: ", "Error, ingrese 's' o 'n': ", 3);
                    if(*respuesta == 'n' || *respuesta == 'N'){
                        control = 0;
                    }
                    if(control == 0){
                        printf("\nNo confirmo el cliente.\n");
                    }else{
                        control = ingresarFecha(*nuevaFecha);
                        if(control == 0){
                            printf("\nLa fecha no se cargo correctamente.\n");
                        }else{
                            nuevoAlquiler->fecha = *nuevaFecha;
                            nuevoAlquiler->isEmpty = OCUPADO;
                            *(lista+(*indice)) = *nuevoAlquiler;
                        }
                    }
                }
            }
        }
    }
    free(indice);
    free(codigoCliente);
    free(respuesta);
    free(nuevoAlquiler);
    free(nuevaFecha);
    return control;
}

int ModificarAlquiler(eAlquiler* lista, int TAM_ALQUILERES, int *codigo){
    int* indice = (int*) malloc(sizeof(int));
    int* control = (int*) malloc(sizeof(int));
    int bandera;
    char* seguir = (char*) malloc(sizeof(char));

    if(TAM_ALQUILERES > 0 && lista != NULL){
        system("cls");
        printf("  *** Modificar Alquiler ***\n\n");
        *control = getInt(codigo, "Ingrese codigo de Alquiler: ", "Error, ingrese solo numeros respetando el rango (1 - 10): ", 1, 10, 3);
        if(*control != 1){
            bandera = 0;
            printf("\nNo se obtuvo el codigo de Alquiler.");
        }else{
            *indice = buscarAlquiler(lista, TAM_ALQUILERES, *codigo);
            if(*indice == -1){
                bandera = -1;
            }else{
                printf("Cod. Alquiler   Cod. Juego   Cod. Cliente     Fecha\n");
                mostrarAlquiler(lista+(*indice)); // d
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
                    bandera = menuModificarAlquiler(lista, *indice);
                }
            }
        }
    }
    free(indice);
    free(control);
    free(seguir);
    return bandera;
}

void mostrarAlquiler(eAlquiler* alquiler){
    if(alquiler != NULL){
        printf("%6d %14d %14d  %9i/%i/%i\n", alquiler->codigoDeAlquiler, alquiler->codigoDeJuego, alquiler->codigoDeCliente, alquiler->fecha.dia, alquiler->fecha.mes, alquiler->fecha.anio);
    }
}

int menuModificarAlquiler(eAlquiler* lista, int indice){ // bien!
    int* opcion = (int*) malloc(sizeof(int));
    int control;
    int* nuevoCodigoJuego = (int*) malloc(sizeof(int));
    int* nuevoCodigoCliente = (int*) malloc(sizeof(int));

    if(lista != NULL){
        system("cls");
        printf("\nSeleccione el campo que desea modificar: \n\n");
        printf(" 1- Codigo de Juego\n");
        printf(" 2- Codigo de Cliente\n");
        printf(" 3- Fecha\n\n");
        control = getInt(opcion, "Ingrese opcion: ", "Error, opcion invalida. Reingrese: ", 1, 3, 3);
        switch(*opcion){
        case 1:
            control = getInt(nuevoCodigoJuego, "\n\nIngrese nuevo codigo de juego: ", "Error, ingrese solo numeros respetando el rango (1 a 10): ", 1, 10, 3);
            if(control == 0){
                printf("\nNo se pudo registrar el codigo de juego!");
            }else{
                (lista+indice)->codigoDeJuego = *nuevoCodigoJuego;
            }
            break;
        case 2:
            control = getInt(nuevoCodigoCliente, "\n\nIngrese nuevo codigo de cliente: ", "Error, ingrese solo numeros respetando el rango (1 a 10): ", 1, 10, 3);
            if(control == 0){
                printf("\nNo se pudo registrar el codigo de cliente!\n");
            }else{
                (lista+indice)->codigoDeCliente = *nuevoCodigoCliente;
            }
            break;
        case 3:
            control = ingresarFecha((lista+indice)->fecha);
            if(control == 0){
                printf("\nNo se registro la fecha.\n\n");
            }else{
                printf("\nFecha modificada con exito!");
            }
            break;
        }
    }
    free(nuevoCodigoCliente);
    free(nuevoCodigoJuego);
    free(opcion);
    return control;
}

int bajaAlquiler(eAlquiler* lista, int TAM_ALQUILERES, int *codigo){
    int* indice = (int*) malloc(sizeof(int));
    int* control = (int*) malloc(sizeof(int));
    int bandera;
    char* seguir = (char*) malloc(sizeof(char));

    if(TAM_ALQUILERES > 0 && lista != NULL){
        system("cls");
        printf("  *** Baja Alquiler ***\n\n");
        *control = getInt(codigo, "Ingrese codigo de Alquiler: ", "Error, ingrese solo numeros respetando el rango (1 - 10): ", 1, 10, 3);
        if(*control != 1){
            bandera = 0;
            printf("\nNo se obtuvo el codigo de Alquiler.");
        }else{
            *indice = buscarAlquiler(lista, TAM_ALQUILERES, *codigo);
            if(*indice == -1){
                bandera = -1;
            }else{
                printf("Cod. Alquiler   Cod. Juego   Cod. Cliente     Fecha\n");
                mostrarAlquiler(lista+(*indice)); // d
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
    }
    free(indice);
    free(control);
    free(seguir);
    return bandera;
}

void mostrarListadoDeAlquileres(eAlquiler* lista, int TAM_ALQUILERES){
    if(TAM_ALQUILERES > 0 && lista != NULL){
        system("cls");
        printf("   ****  Listado de Alquileres  **** \n\n");
        printf("Cod. Alquiler   Cod. Juego   Cod. Cliente      Fecha\n\n");
        for(int contador=0; contador < TAM_ALQUILERES; contador++){
            if((lista+contador)->isEmpty == 0){
                mostrarAlquiler(lista+contador);
            }
        }
        printf("\n");
    }
}
