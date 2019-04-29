#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "alquileres.h"
#include "fechas.h"
#include "juegos.h"
#include "categorias.h"
#include "validar.h"

#define TAM_CLIENTES 10
#define TAM_ALQUILERES 12
#define TAM_JUEGOS 10
#define TAM_CATEGORIAS 5
#define TAM_FECHAS 10
#define TAM_MARCAS 5
#define OCUPADO 0
#define VACIO 1

int main()
{   // Reserva de memoria estatica
    int ok, codigo, bandera=0;
    char respuesta;
    // Reserva de memoria dinamica
    int* banderaPromedio = (int*) malloc(sizeof(int));
    float* promedio = (float*) malloc(sizeof(float));
    eCliente* clientes = (eCliente*) malloc(sizeof(eCliente)*TAM_CLIENTES);
    eAlquiler* alquileres = (eAlquiler*) malloc(sizeof(eAlquiler)*TAM_ALQUILERES);
    eCategoria* categorias = (eCategoria*) malloc(sizeof(eCategoria)*TAM_CATEGORIAS);
    eJuego* juegos = (eJuego*) malloc(sizeof(eJuego)*TAM_JUEGOS);
    eMarca* marcas = (eMarca*) malloc(sizeof(eMarca)*TAM_MARCAS);
    // Iniciar y hardcodeos
    *promedio = 0;
    *banderaPromedio = 0;
    iniciarClientes(clientes, TAM_CLIENTES);
    iniciarAlquileres(alquileres, TAM_ALQUILERES);
    hardcodearCategorias(categorias, TAM_CATEGORIAS);
    hardcodearJuegos(juegos, TAM_JUEGOS);
    hardcodearClientes(clientes, TAM_CLIENTES);
    hardcodearAlquileres(alquileres, TAM_ALQUILERES);
    hardcodearMarca(marcas, TAM_MARCAS);

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
                break;
            case 4:
                ok = comprobarRegistroClientes(clientes, TAM_CLIENTES);
                if(ok == -1){
                    printf("\nHasta el momento no se ha registrado ningun cliente.\n\n");
                }else{
                    ordenarClientesXsexoYnombre(clientes, TAM_CLIENTES);
                    system("cls");
                    mostrarListadoDeClientes(clientes, TAM_CLIENTES);
                }
                break;
            case 5:
                ok = ingresarAlquiler(alquileres, TAM_ALQUILERES, clientes, TAM_CLIENTES, juegos, TAM_ALQUILERES, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
                if(ok == -1){
                    printf("\nNo se encontro espacio para el registro.\n\n");
                }else{
                    if(ok == 0){
                        printf("\nAlta cancelada.\n\n");
                    }else{
                        printf("\nAlta exitosa.\n\n");
                    }
                }
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
                break;
            case 8:
                ok = comprobarRegistroAlquiler(alquileres, TAM_ALQUILERES);
                if(ok == -1){
                    printf("\nHasta el momento no se ha registrado ningun alquiler.\n\n");
                }else{
                    system("cls");
                    mostrarListadoDeAlquileres(alquileres, TAM_ALQUILERES);
                }
                break;
            case 9:
                ok = ingresarJuego(juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
                if(ok == -1){
                    printf("\nNo se encontro espacio para el registro.\n\n");
                }else{
                    if(ok == 0){
                        printf("\nAlta cancelada.\n\n");
                    }else{
                        printf("\nAlta exitosa.\n\n");
                    }
                }
                break;
            case 10:
                ok = comprobarRegistroJuegos(juegos, TAM_JUEGOS);
                if(ok == -1){
                    printf("\nHasta el momento no se ha registrado ningun juego.\n\n");
                }else{
                    modificarJuego(juegos, TAM_JUEGOS, &codigo, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS); //modificar juego !
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
                break;
            case 11:
                ok = comprobarRegistroJuegos(juegos, TAM_JUEGOS);
                if(ok == -1){
                    printf("\nHasta el momento no se ha registrado ningun Juego.\n\n");
                }else{
                    ok = bajaJuego(juegos, TAM_JUEGOS, &codigo, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
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
                break;
            case 12:
                ok = comprobarRegistroJuegos(juegos, TAM_JUEGOS);
                if(ok == -1){
                    printf("\nHasta el momento no se ha registrado ningun juego.\n\n");
                }else{
                    system("cls");
                    mostrarListadoDeJuegos(juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
                }
                break;
            case 13:
                system("cls");
                mostrarListadoDeJuegos(juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
                printf("\n");
                mostrarListadoDeAlquileres(alquileres, TAM_ALQUILERES);
                if(promedio != NULL){
                    *promedio = total_y_promedio_importes_de_juegos_alquilados(alquileres, TAM_ALQUILERES, juegos, TAM_JUEGOS);
                    *banderaPromedio = 1;
                }
                break;
            case 14:
                if(*banderaPromedio == 1){
                    system("cls");
                    mostrarListadoDeJuegos_queNoSuperanElImportePromedio(juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS, promedio, marcas, TAM_MARCAS);
                }else{
                    printf("\nNo se calculo el Promedio del Importe por Juegos Alquilados.\n\n");
                }
                break;
            case 15:
                listadoDeClientesQueALquilaronUnDeterminadoJuego(alquileres, TAM_ALQUILERES, clientes, TAM_CLIENTES, juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
                break;
            case 16:
                listadoDeJuegosQueALquiloUnDeterminadoCliente(alquileres, TAM_ALQUILERES, clientes, TAM_CLIENTES, juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
                break;
            case 17:
                juegosMenosAlquilados(alquileres, TAM_ALQUILERES, juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
                break;
            case 18:
                clientesQueRealizaronMasAlquileres(alquileres, TAM_ALQUILERES, clientes, TAM_CLIENTES);
                break;
            case 19:
                listadoDeJuegosAlquiladosEnUnaDeterminadaFecha(alquileres, TAM_ALQUILERES, juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
                break;
            case 20:
                ClientesQueAlquilaronEnUnaDeterminadaFecha(alquileres, TAM_ALQUILERES, clientes, TAM_CLIENTES);
                break;
            case 21:
                listarJuegosOrdenadosXimporteDescendente(juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
                break;
            case 22:
                listarClientesXapellidoAscendente_Insercion(clientes, TAM_CLIENTES);
                break;
            case 23:
                JuegosDeUnaMarcaDeterminada(juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
                break;
            case 24:
                contadorDeAlquileresParaUnaMarcaDeterminada(alquileres, TAM_ALQUILERES, juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
                break;
            case 25:
                clientesQueAlquilaronJuegosDeUnaDeterminadaMarca(alquileres, TAM_ALQUILERES, clientes, TAM_CLIENTES, juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
                break;
            case 30:
                printf("\nSalir.\n");
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
        system("pause");
    }while(respuesta == 's' || respuesta == 'S');

    free(clientes);
    free(alquileres);
    free(categorias);
    free(juegos);
    free(marcas);
    free(promedio);
    free(banderaPromedio);
    return 0;
}
