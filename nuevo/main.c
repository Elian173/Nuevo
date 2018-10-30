#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "alquileres.h"
#include "fechas.h"
#include "juegos.h"
#include "categorias.h"
#include "validar.h"

#define TAM_CLIENTES 10
#define TAM_ALQUILERES 10
#define TAM_JUEGOS 10
#define TAM_CATEGORIAS 5
#define TAM_FECHAS 10
#define OCUPADO 0
#define VACIO 1

int main()
{   // Reserva de memoria estatica
    int ok, codigo, bandera=0;
    char respuesta;
    eCliente* clientes;
    eAlquiler* alquileres;
    eCategoria* categorias;
    eJuego* juegos;
    // Reserva de memoria dinamica
    clientes = (eCliente*) malloc(sizeof(eCliente)*TAM_CLIENTES);
    alquileres = (eAlquiler*) malloc(sizeof(eAlquiler)*TAM_ALQUILERES);
    categorias = (eCategoria*) malloc(sizeof(eCategoria)*TAM_CATEGORIAS);
    juegos = (eJuego*) malloc(sizeof(eJuego)*TAM_JUEGOS);
    // Iniciar y hardcodeos
    iniciarClientes(clientes, TAM_CLIENTES);
    iniciarAlquileres(alquileres, TAM_ALQUILERES);
    hardcodearCategorias(categorias, TAM_CATEGORIAS);
    hardcodearJuegos(juegos, TAM_JUEGOS);
    hardcodearClientes(clientes, TAM_CLIENTES);

    do{
        switch(menu()){
            case 1:
                ok = ingresarCliente(clientes, TAM_CLIENTES);
                if(ok == -1){
                    printf("\nNo se encontro espacio para el registro.\n\n");
                }else{
                    if(ok == 0){
                        printf("\nAlta cancelada.\n\n");
                    }else{
                        printf("\nAlta exitosa.\n\n");
                    }
                }
                system("pause");
                break;
            case 2:
                ok = comprobarRegistroClientes(clientes, TAM_CLIENTES);
                if(ok == -1){
                    printf("\nHasta el momento no se ha registrado ningun cliente.\n\n");
                }else{
                    ok = modificarCliente(clientes, TAM_CLIENTES, &codigo);
                    if(ok == -1){
                        printf("\nNo se encontro cliente correspondiente al codigo %i.\n\n", codigo);
                    }else{
                        if(ok == 0){
                            printf("\nModificacion cancelada.\n\n");
                        }else{
                            printf("\nModificacion exitosa.\n\n");
                        }
                    }
                }
                system("pause");
                break;
            case 3:
                ok = comprobarRegistroClientes(clientes, TAM_CLIENTES);
                if(ok == -1){
                    printf("\nHasta el momento no se ha registrado ningun cliente.\n\n");
                }else{
                    ok = bajaCliente(clientes, TAM_CLIENTES, &codigo);
                    if(ok == -1){
                        printf("\nNo se encontro cliente correspondiente al codigo %i.\n\n", codigo);
                    }else{
                        if(ok == 0){
                            printf("\nBaja cancelada.\n\n");
                        }else{
                            printf("\nBaja exitosa.\n\n");
                        }
                    }
                }
                system("pause");
                break;
            case 4:
                ok = comprobarRegistroClientes(clientes, TAM_CLIENTES);
                if(ok == -1){
                    printf("\nHasta el momento no se ha registrado ningun cliente.\n\n");
                }else{
                    ordenarClientesXsexoYnombre(clientes, TAM_CLIENTES);
                    mostrarListadoDeClientes(clientes, TAM_CLIENTES);
                }
                system("pause");
                break;
            case 5:
                ok = ingresarAlquiler(alquileres, TAM_ALQUILERES, clientes, TAM_CLIENTES, juegos, 10, categorias, 5);
                if(ok == -1){
                    printf("\nNo se encontro espacio para el registro.\n\n");
                }else{
                    if(ok == 0){
                        printf("\nAlta cancelada.\n\n");
                    }else{
                        printf("\nAlta exitosa.\n\n");
                    }
                }
                system("pause");
                break;
            case 6:
                ok = comprobarRegistroAlquiler(alquileres, TAM_ALQUILERES);
                if(ok == -1){
                    printf("\nHasta el momento no se ha registrado ningun Alquiler.\n\n");
                }else{
                    ok = ModificarAlquiler(alquileres, TAM_ALQUILERES, &codigo);
                    if(ok == -1){
                        printf("\nNo se encontro alquiler correspondiente al codigo %i.\n\n", codigo);
                    }else{
                        if(ok == 0){
                            printf("\nModificacion cancelada.\n");
                        }else{
                            printf("\nModificacion exitosa!\n");
                        }
                    }
                }
                system("pause");
                break;
            case 7:
                ok = comprobarRegistroAlquiler(alquileres, TAM_ALQUILERES);
                if(ok == -1){
                    printf("\nHasta el momento no se ha registrado ningun Alquiler.\n\n");
                }else{
                    ok = bajaAlquiler(alquileres, TAM_ALQUILERES, &codigo);
                    if(ok == -1){
                        printf("\nNo se encontro alquiler correspondiente al codigo %i.\n\n", codigo);
                    }else{
                        if(ok == 0){
                            printf("\nBaja cancelada.\n");
                        }else{
                            printf("\nBaja exitosa.\n");
                        }
                    }
                }
                system("pause");
                break;
            case 8:
                ok = comprobarRegistroAlquiler(alquileres, TAM_ALQUILERES);
                if(ok == -1){
                    printf("\nHasta el momento no se ha registrado ningun alquiler.\n\n");
                }else{
                    mostrarListadoDeAlquileres(alquileres, TAM_ALQUILERES);
                }
                system("pause");
                break;
            case 9:
                ok = ingresarJuego(juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS);
                if(ok == -1){
                    printf("\nNo se encontro espacio para el registro.\n\n");
                }else{
                    if(ok == 0){
                        printf("\nAlta cancelada.\n\n");
                    }else{
                        printf("\nAlta exitosa.\n\n");
                    }
                }
                system("pause");
                break;
            case 10:
                ok = comprobarRegistroJuegos(juegos, TAM_JUEGOS);
                if(ok == -1){
                    printf("\nHasta el momento no se ha registrado ningun juego.\n\n");
                }else{
                    modificarJuego(juegos, TAM_JUEGOS, &codigo, categorias, TAM_CATEGORIAS); //modificar juego !
                    if(ok == -1){
                        printf("\nNo se encontro alquiler correspondiente al codigo %i.\n\n", codigo);
                    }else{
                        if(ok == 0){
                            printf("\nModificacion cancelada.\n");
                        }else{
                            printf("\nModificacion exitosa!\n");
                        }
                    }
                }
                system("pause");
                break;
            case 11:
                ok = comprobarRegistroJuegos(juegos, TAM_JUEGOS);
                if(ok == -1){
                    printf("\nHasta el momento no se ha registrado ningun Juego.\n\n");
                }else{
                    ok = bajaJuego(juegos, TAM_JUEGOS, &codigo, categorias, TAM_CATEGORIAS);
                    if(ok == -1){
                        printf("\nNo se encontro juego correspondiente al codigo %i.\n\n", codigo);
                    }else{
                        if(ok == 0){
                            printf("\nBaja cancelada.\n");
                        }else{
                            printf("\nBaja exitosa.\n");
                        }
                    }
                }
                system("pause");
                break;
            case 12:
                ok = comprobarRegistroJuegos(juegos, TAM_JUEGOS);
                if(ok == -1){
                    printf("\nHasta el momento no se ha registrado ningun juego.\n\n");
                }else{
                    mostrarListadoDeJuegos(juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS);
                }
                system("pause");
                break;
            case 30:
                printf("\nSalir.\n\n");
                bandera = 1;
                break;
            default:
                printf("\nopcion invalida!\n\n");
        }
        if(bandera == 1){
            respuesta = 'n';
        }else{
            getCharResp(&respuesta, "\nDesea continuar?.. s/n: ", "Error, ingrese solo 's' o 'n': ", 3);
        }
    }while(respuesta == 's' || respuesta == 'S');

    free(clientes);
    free(alquileres);
    free(categorias);
    free(juegos);
    return 0;
}
