#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alquileres.h"
#include "validar.h"
#include "juegos.h"

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

int ingresarAlquiler(eAlquiler* lista, int TAM_ALQUILERES, eCliente* clientes, int TAM_CLIENTES, eJuego* juegos, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS){
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
            control = menuSeleccionarJuego(juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
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

float total_y_promedio_importes_de_juegos_alquilados(eAlquiler *lista, int TAM_ALQUILERES, eJuego* juegos, int TAM_JUEGOS){
    float* acumImporte = (float*) malloc(sizeof(float));
    int* cantJuegos = (int*) malloc(sizeof(int));
    int* contador = (int*) malloc(sizeof(int));
    int* count = (int*) malloc(sizeof(int));
    float promedio;
    *acumImporte = 0;
    *cantJuegos = 0;
    if(lista != NULL && juegos != NULL){
        for(*contador=0; *contador < TAM_ALQUILERES; (*contador)++){
            if((lista+(*contador))->isEmpty == OCUPADO){
                for(*count = 0; *count < TAM_JUEGOS; (*count)++){
                    *acumImporte = *acumImporte + (juegos+(*count))->importe;
                    (*cantJuegos)++;
                }
            }
        }
    }
    promedio = *acumImporte / (float) (*cantJuegos);
    printf("El total de importes por juegos alquilados es: %.2f\nEl promedio de importes por juegos alquilados es: %.2f\n\n", *acumImporte, promedio);
    free(acumImporte);
    free(cantJuegos);
    free(contador);
    free(count);
    return promedio;
}

void hardcodearAlquileres(eAlquiler* lista, int TAM_ALQUILERES){
    int* contador = (int*) malloc(sizeof(int));
    eAlquiler nuevaLista[12] ={
        { 1, 3, 2, {12, 1, 2018}, 0},
        { 2, 6, 6, {17, 2, 2018}, 0},
        { 3, 1, 1, {23, 2, 2018}, 0},
        { 4, 4, 4, {7, 3, 2018}, 0},
        { 5, 7, 3, {3, 4, 2018}, 0},
        { 6, 5, 7, {12, 4, 2018}, 0},
        { 7, 10, 2, {21, 5, 2018}, 0},
        { 8, 1, 5, {29, 5, 2018}, 0},
        { 9, 9, 1, {10, 6, 2018}, 0},
        { 10, 5, 3, {15, 7, 2018}, 0},
        { 11, 3, 3, {15, 7, 2018}, 0},
        { 12, 5, 3, {21, 7, 2018}, 0}
    };
    for(*contador = 0; *contador < TAM_ALQUILERES; (*contador)++){
        *(lista+(*contador)) = *(nuevaLista+(*contador));
    }
    free(contador);
}

void listadoDeClientesQueALquilaronUnDeterminadoJuego(eAlquiler* lista, int TAM_ALQUILERES, eCliente* clientes, int TAM_CLIENTES, eJuego* juegos, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS){
    int* contador = (int*) malloc(sizeof(int));
    int* opcion = (int*) malloc(sizeof(int));
    int* count = (int*) malloc(sizeof(int));
    int* bandera = (int*) malloc(sizeof(int));
    char* descript = (char*) malloc(sizeof(char)*20);
    *bandera = 0;
    if(lista != NULL && clientes != NULL && juegos != NULL && categorias != NULL){
        *opcion = menuSeleccionarJuego(juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
        printf("\n");
        mostrarListadoDeAlquileres(lista, TAM_ALQUILERES);
        for(*contador = 0; *contador < TAM_JUEGOS; (*contador)++){
            if((juegos+(*contador))->codigo == *opcion){
                strcpy(descript, (juegos+(*contador))->descripcion);
            }
        }
        printf("\n   ****  Listado de Clientes que Alquilaron el Juego %s **** \n\n", descript);
        printf("Codigo   Nombre   Sexo      Telefono\n\n");
        for(*contador = 0; *contador < TAM_ALQUILERES; (*contador)++){
            if((lista+(*contador))->codigoDeJuego == *opcion){
                for(*count = 0; *count < TAM_CLIENTES; (*count)++){
                    if((lista+(*contador))->codigoDeCliente == (clientes+(*count))->codigo){
                        mostrarCliente(clientes+(*count));
                        *bandera = 1;
                    }
                }
            }
        }
        if(*bandera == 0){
            printf("No hay registros de alquiler para el juego %s\n", descript);
        }
    }
    printf("\n");
    free(contador);
    free(opcion);
    free(count);
    free(descript);
    free(bandera);
}

void listadoDeJuegosQueALquiloUnDeterminadoCliente(eAlquiler* lista, int TAM_ALQUILERES, eCliente* clientes, int TAM_CLIENTES, eJuego* juegos, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS){
    int* contador = (int*) malloc(sizeof(int));
    int* opcion = (int*) malloc(sizeof(int));
    int* count = (int*) malloc(sizeof(int));
    int* bandera = (int*) malloc(sizeof(int));
    char* name = (char*) malloc(sizeof(char)*51);
    *bandera = 0;
    if(lista != NULL && clientes != NULL && juegos != NULL && categorias != NULL){
        *opcion = menuSeleccionarCliente(clientes, TAM_CLIENTES);
        for(*contador = 0; *contador < TAM_CLIENTES; (*contador)++){
            if((clientes+(*contador))->codigo == *opcion){
                strcpy(name, (clientes+(*contador))->nombre);
            }
        }
        printf("\n");
        mostrarListadoDeAlquileres(lista, TAM_ALQUILERES);
        printf("\n   ****  Listado de Juegos alquilados por %s **** \n\n", name);
        printf("Codigo   Descripcion   Marca   Importe    Categoria\n\n");
        for(*contador = 0; *contador < TAM_ALQUILERES; (*contador)++){
            if((lista+(*contador))->codigoDeCliente == *opcion){
                for(*count = 0; *count < TAM_JUEGOS; (*count)++){
                    if((juegos+(*count))->codigo == (lista+(*contador))->codigoDeJuego){
                        mostrarJuego(juegos+(*count), categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
                        *bandera = 1;
                    }
                }
            }
        }
        if(*bandera == 0){
            printf("No hay registros de alquiler del cliente %s\n", name);
        }
    }
    printf("\n");
    free(contador);
    free(opcion);
    free(count);
    free(bandera);
    free(name);
}

void juegosMenosAlquilados(eAlquiler* alquileres, int TAM_ALQUILERES, eJuego* juegos, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS){
    int* contador = (int*) malloc(sizeof(int));
    int* count = (int*) malloc(sizeof(int));
    int* contJuego = (int*) malloc(sizeof(int)*TAM_JUEGOS);
    int* acumulador = (int*) malloc(sizeof(int));
    float* promedio = (float*) malloc(sizeof(float));
    int* cantidad = (int*) malloc(sizeof(int));
    *cantidad = 0;
    *acumulador = 0;

    for(*contador = 0; *contador < TAM_JUEGOS; (*contador)++){
        *(contJuego+(*contador)) = 0;
    }
    for(*contador = 0; *contador < TAM_ALQUILERES; (*contador)++){
        for(*count = 0; *count < TAM_JUEGOS; (*count)++){
            if((alquileres+(*contador))->codigoDeJuego == (juegos+(*count))->codigo){
                *(contJuego+(*count)) += 1;
            }
        }
    }
    for(*contador = 0; *contador < TAM_JUEGOS; (*contador)++){
       *acumulador += *(contJuego+(*contador));
       *cantidad += 1;
    }
    *promedio = *acumulador / (float) (*cantidad);
    system("cls");
    printf("   ****  Listado de Juegos Menos Alquilados **** \n\n");
    printf("Codigo   Descripcion   Marca   Importe    Categoria\n\n");
    for(*contador = 0; *contador < TAM_JUEGOS; (*contador)++){
        if(*(contJuego+(*contador)) < (*promedio)){
            mostrarJuego((juegos+(*contador)), categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
        }
    }
    printf("\n");
    mostrarListadoDeAlquileres(alquileres, TAM_ALQUILERES);
    free(cantidad);
    free(acumulador);
    free(promedio);
    free(count);
    free(contador);
    free(contJuego);
}

void clientesQueRealizaronMasAlquileres(eAlquiler* alquileres, int TAM_ALQUILERES, eCliente* clientes, int TAM_CLIENTES){
    int* contador = (int*) malloc(sizeof(int));
    int* count = (int*) malloc(sizeof(int));
    int* contAlquileres = (int*) malloc(sizeof(int)*TAM_CLIENTES);
    int* acumulador = (int*) malloc(sizeof(int));
    float* promedio = (float*) malloc(sizeof(float));
    int* cantidad = (int*) malloc(sizeof(int));
    *cantidad = 0;
    *acumulador = 0;

    for(*contador = 0; *contador < TAM_CLIENTES; (*contador)++){
        *(contAlquileres+(*contador)) = 0;
    }
    for(*contador = 0; *contador < TAM_ALQUILERES; (*contador)++){
        for(*count = 0; *count < TAM_CLIENTES; (*count)++){
            if((alquileres+(*contador))->codigoDeCliente == (clientes+(*count))->codigo){
                *(contAlquileres+(*count)) += 1;
            }
        }
    }
    for(*contador = 0; *contador < TAM_CLIENTES; (*contador)++){
       *acumulador += *(contAlquileres+(*contador));
       *cantidad += 1;
    }
    *promedio = *acumulador / (float) (*cantidad);
    system("cls");
    printf("   ****  Listado de Clientes que realizaron mas alquileres  **** \n\n");
    printf("Codigo   Nombre   Sexo      Telefono\n\n");
    for(*contador = 0; *contador < TAM_CLIENTES; (*contador)++){
        if(*(contAlquileres+(*contador)) > (*promedio)){
            mostrarCliente(clientes+(*contador));
        }
    }
    printf("\n");
    mostrarListadoDeAlquileres(alquileres, TAM_ALQUILERES);
    free(cantidad);
    free(acumulador);
    free(promedio);
    free(count);
    free(contador);
    free(contAlquileres);
}

void listadoDeJuegosAlquiladosEnUnaDeterminadaFecha(eAlquiler* alquileres, int TAM_ALQUILERES, eJuego* juegos, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS){
    int* contador = (int*) malloc(sizeof(int));
    int* count = (int*) malloc(sizeof(int));
    int* bandera = (int*) malloc(sizeof(int));
    eFecha* auxFecha = (eFecha*) malloc(sizeof(eFecha));
    *bandera = 0;
    if(alquileres != NULL && juegos != NULL && categorias != NULL){
        getFecha(auxFecha);
        system("cls");
        printf("\n   ****  Listado de Juegos alquilados en la fecha %d/%d/%d **** \n\n", auxFecha->dia, auxFecha->mes, auxFecha->anio);
        printf("Codigo   Descripcion   Marca   Importe    Categoria\n\n");
        for(*contador = 0; *contador < TAM_ALQUILERES; (*contador)++){
            if(compararFecha((alquileres+(*contador))->fecha, *auxFecha)){
                for(*count = 0; *count < TAM_JUEGOS; (*count)++){
                    if((alquileres+(*contador))->codigoDeJuego == (juegos+(*count))->codigo){
                        mostrarJuego(juegos+(*count), categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
                        *bandera = 1;
                    }
                }
            }
        }
        printf("\n");
        mostrarListadoDeAlquileres(alquileres, TAM_ALQUILERES);
        if(*bandera == 0){
            printf("No hay registros de alquiler en esa fecha.\n");
        }
    }
    printf("\n");
    free(contador);
    free(bandera);
    free(count);
    free(auxFecha);
}

void ClientesQueAlquilaronEnUnaDeterminadaFecha(eAlquiler* alquileres, int TAM_ALQUILERES, eCliente* clientes, int TAM_CLIENTES){
    int* contador = (int*) malloc(sizeof(int));
    int* count = (int*) malloc(sizeof(int));
    int* bandera = (int*) malloc(sizeof(int));
    int* cantAlq = (int*) malloc(sizeof(int));
    int* yaPaso = (int*) malloc(sizeof(int)*TAM_CLIENTES);
    eFecha* auxFecha = (eFecha*) malloc(sizeof(eFecha));
    *bandera = 0;
    *cantAlq = 0;
    for(*contador = 0; *contador < TAM_CLIENTES; (*contador)++){
        *(yaPaso+(*contador)) = 0;
    }
    if(alquileres != NULL && clientes != NULL && auxFecha != NULL){
        getFecha(auxFecha);
        system("cls");
        printf("\n   ****  Listado de Clientes que alquilaron en la fecha %d/%d/%d **** \n\n", auxFecha->dia, auxFecha->mes, auxFecha->anio);
        printf("Codigo   Nombre   Sexo      Telefono\n\n");
        for(*contador = 0; *contador < TAM_ALQUILERES; (*contador)++){
            if(compararFecha((alquileres+(*contador))->fecha, *auxFecha)){
                for(*count = 0; *count < TAM_CLIENTES; (*count)++){
                    if((alquileres+(*contador))->codigoDeCliente == (clientes+(*count))->codigo){
                        (*cantAlq)++;
                        if(*(yaPaso+(*count)) == 0){
                            mostrarCliente(clientes+(*count));
                            *bandera = 1;
                            *(yaPaso+(*count)) = 1;
                        }
                    }
                }
            }
        }
        printf("\n\nEn la fecha determinada se realizaron %i alquileres.\n\n", *cantAlq);
        mostrarListadoDeAlquileres(alquileres, TAM_ALQUILERES);
        if(*bandera == 0){
            printf("No hay registros de alquiler en esa fecha.\n");
        }
    }
    printf("\n");
    free(contador);
    free(bandera);
    free(count);
    free(cantAlq);
    free(yaPaso);
    free(auxFecha);
}

void contadorDeAlquileresParaUnaMarcaDeterminada(eAlquiler* alquileres, int TAM_ALQUILERES, eJuego* juegos, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS){
    int opcion, acumulador = 0;
    system("cls");
    opcion = menuSeleccionarMarca(marcas, TAM_MARCAS);
    for(int contador = 0; contador < TAM_JUEGOS; contador++){
        if((juegos+contador)->idMarca == opcion){
            for(int count = 0; count < TAM_ALQUILERES; count++){
                if((juegos+contador)->codigo == (alquileres+count)->codigoDeJuego){
                    acumulador++;
                }
            }
        }
    }
    printf("\n");
    mostrarListadoDeJuegos(juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
    mostrarListadoDeAlquileres(alquileres, TAM_ALQUILERES);
    if(acumulador != 0){
        printf("\nSe registraron %d alquileres de la marca determinada.\n\n", acumulador);
    }
    else{
        printf("\n no hay registros de juegos alquilados con esa marca.\n\n");
    }
}

void clientesQueAlquilaronJuegosDeUnaDeterminadaMarca(eAlquiler* alquileres, int TAM_ALQUILERES, eCliente* clientes, int TAM_CLIENTES, eJuego* juegos, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS){
    int opcion, bandera = 0;
    system("cls");
    opcion = menuSeleccionarMarca(marcas, TAM_MARCAS);
    printf("\nCodigo   Nombre   Sexo      Telefono\n\n");
    for(int contador = 0; contador < TAM_JUEGOS; contador++){
        if((juegos+contador)->idMarca == opcion){
            for(int count = 0; count < TAM_ALQUILERES; count++){
                if((juegos+contador)->codigo == (alquileres+count)->codigoDeJuego){
                    for(int contar = 0; contar < TAM_CLIENTES; contar++){
                        if((alquileres+count)->codigoDeCliente == (clientes+contar)->codigo){
                            mostrarCliente(clientes+contar);
                            bandera = 1;
                        }
                    }
                }
            }
        }
    }
    printf("\n");
    mostrarListadoDeJuegos(juegos, TAM_JUEGOS, categorias, TAM_CATEGORIAS, marcas, TAM_MARCAS);
    printf("\n");
    mostrarListadoDeAlquileres(alquileres, TAM_ALQUILERES);
    printf("\n");
    mostrarListadoDeClientes(clientes, TAM_CLIENTES);
    printf("\n");
    if(bandera != 1){
        printf("\n no hay registros de alquileres para esa marca.\n\n");
    }
}
