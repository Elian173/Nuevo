#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "validar.h"
#include "clientes.h"

#define OCUPADO 0
#define VACIO 1

int iniciarClientes(eCliente* lista, int TAM_CLIENTES){ // bien!
    int retorno = -1;
    if(TAM_CLIENTES > 0 && lista != NULL){
        retorno = 0;
        for(int contador=0; contador < TAM_CLIENTES; contador++){
            (lista+contador)->isEmpty = VACIO;
        }
    }
    return retorno;
}

void hardcodearClientes(eCliente* lista, int TAM_CLIENTES){
    eCliente nuevaLista[7]={
        { 1, "Jacinto", 'm', "2234156201", 0},
        { 2, "Epifania", 'f', "1123415265", 0},
        { 3, "Adalberto", 'm', "1121544103", 0},  ////  seguir cargando !!!
        { 4, "Magnolia", 'f', "2224504871", 0},
        { 5, "Virgilio", 'm', "2132636541", 0},
        { 6, "Evarista", 'f', "1122400556", 0},
        { 7, "Augusto", 'm', "3126340115", 0}
    };
    for(int contador=0; contador< 7; contador++){
        *(lista+contador) = *(nuevaLista+contador);
    }
}

int buscarLibreClientes(eCliente* lista, int TAM_CLIENTES){
    int indice = -1;
    if(TAM_CLIENTES > 0 && lista != NULL){
        indice = -2;
        for(int contador=0; contador < TAM_CLIENTES; contador++){
            if((lista+contador)->isEmpty == VACIO){
                indice = contador;
                break;
            }
        }
    }
    return indice;
}

int buscarCliente(eCliente* lista, int TAM_CLIENTES, int codigo){
    int indice = -1;
    if(TAM_CLIENTES > 0 && lista != NULL){
        indice = -2;
        for(int contador=0; contador < TAM_CLIENTES; contador++){
            if((lista+contador)->codigo == codigo && (lista+contador)->isEmpty == OCUPADO){
                indice = contador;
                break;
            }
        }
    }
    return indice;
}

void mostrarCliente(eCliente* cliente){
    printf("%4d %10s %5c     %10s\n", cliente->codigo, cliente->nombre, cliente->sexo, cliente->telefono);
}

int mostrarListadoDeClientes(eCliente* lista, int TAM_CLIENTES){
    int retorno = -1;
    printf("   ****  Listado de Clientes  **** \n\n");
    printf("Codigo   Nombre   Sexo      Telefono\n\n");
    if(TAM_CLIENTES > 0 && lista != NULL){
        retorno = 0;
        for(int contador=0; contador < TAM_CLIENTES; contador++){
            if((lista+contador)->isEmpty == 0){
                mostrarCliente(lista+contador);
            }
        }
    }
    printf("\n");
    return retorno;
}

int comprobarRegistroClientes(eCliente* lista, int TAM_CLIENTES){
    int bandera = -1;
    if(TAM_CLIENTES > 0 && lista != NULL){
        for(int contador=0; contador < TAM_CLIENTES; contador++){
            if((lista+contador)->isEmpty == OCUPADO){
                bandera = contador;
                break;
            }
        }
    }
    return bandera;
}

void ordenarClientesXsexoYnombre(eCliente* lista, int TAM_CLIENTES){
    int* count = (int*) malloc(sizeof(int));
    int* contador = (int*) malloc(sizeof(int));
    eCliente* aux = (eCliente*) malloc(sizeof(eCliente));

    if(aux == NULL || lista == NULL){
        printf("No se consiguio memoria para ordenar el listado\n");
        exit(1);
    }else{
        if(TAM_CLIENTES > 0){
            for(*count = 0; *count < TAM_CLIENTES-1; (*count)++){
                for(*contador = *count+1; *contador < TAM_CLIENTES; (*contador)++){
                    if((lista+(*count))->sexo > (lista+(*contador))->sexo){
                        *aux = *(lista+(*count));
                        *(lista+(*count)) = *(lista+(*contador));
                        *(lista+(*contador)) = *aux;
                    }else{
                        if((lista+(*count))->sexo == (lista+(*contador))->sexo && strncmp((lista+(*count))->nombre, (lista+(*contador))->nombre, 6) > 0){
                            *aux = *(lista+(*count));
                            *(lista+(*count)) = *(lista+(*contador));
                            *(lista+(*contador)) = *aux;
                        }
                    }
                }
            }
        }else{
            printf("El tamanio del array debe ser mayor a 0.");
        }
    }
    free(count);
    free(contador);
    free(aux);
}

int ingresarCliente(eCliente* lista, int TAM_CLIENTES){
    int* indice = (int*) malloc(sizeof(int));
    int control;
    eCliente* nuevoCliente = (eCliente*) malloc(sizeof(eCliente));

    if(nuevoCliente == NULL || lista == NULL){
        printf("No se consiguio memoria.\n");
        exit(1);
    }else{
        *indice = buscarLibreClientes(lista, TAM_CLIENTES);
        system("cls");
        printf("*** Alta cliente ***\n\n");
        if(*indice == -1){
            control = -1;
        }else{
            nuevoCliente->codigo = *indice + 1;
            control = getString(nuevoCliente->nombre, "Ingrese nombre: ", "Error, ingrese solo letras respetando el rango (3 - 51): ", 3, 51, 3);
            if(control == 0){
                printf("\nSe agotaron las chances y no se pudo ingresar el nombre.\n\n");
            }else{
                control = getCharSexo(&nuevoCliente->sexo, "Ingrese sexo: ", "Error, ingrese solo 'f' o 'm'. Reingrese: ", 3);
                if(control == 0){
                    printf("\nSe agotaron las chances y no se pudo ingresar el sexo.\n\n");
                }else{
                    control = getNumb(nuevoCliente->telefono, 22, "Ingrese telefono: ", "Error, ingrese solo numeros respetando el rango (hasta 22 digitos): ", 3);
                    if(control == 0){
                        printf("\nSe agotaron las chances y no se pudo ingresar el telefono.\n\n");
                    }else{
                        nuevoCliente->isEmpty = OCUPADO;
                        *(lista+(*indice)) = *nuevoCliente;
                    }
                }
            }
        }
    }
    free(indice);
    free(nuevoCliente);
    return control;
}

int menuModificarCliente(eCliente* lista, int indice, int TAM_CLIENTES){ // bien!
    int* opcion = (int*) malloc(sizeof(int));
    int control;
    char* nuevoNombre = (char*) malloc(sizeof(char)*52);
    char* nuevoSexo = (char*) malloc(sizeof(char));
    char* nuevoTelefono = (char*) malloc(sizeof(char)*21);
    if(lista != NULL && TAM_CLIENTES > 0){
        system("cls");
        printf("\nSeleccione el campo que desea modificar: \n\n");
        printf(" 1- Nombre\n");
        printf(" 2- Sexo\n");
        printf(" 3- Telefono\n\n");
        control = getInt(opcion, "Ingrese opcion: ", "Error, opcion invalida. Reingrese: ", 1, 3, 3);
        switch(*opcion){
        case 1:
            if(nuevoNombre == NULL){
                printf("No se encontro memoria para el nombre.\n");
                exit(1);
            }else{
                control = getString(nuevoNombre, "\n\nIngrese nuevo nombre: ", "Error, ingrese solo letras respetando el rango (3 a 51): ", 3, 51, 3);
                if(control == 0){
                    printf("\nNo se pudo registrar el nombre!\n");
                }else{
                    strcpy((lista+indice)->nombre, nuevoNombre);
                }
            }
            break;
        case 2:
            control = getCharSexo(nuevoSexo, "\n\nIngrese nuevo sexo: ", "\nError, ingrese solo 'f' o 'm'. Reingrese: ", 3);
            if(control == 0){
                printf("\nNo se pudo registrar el sexo!\n");
            }else{
                (lista+indice)->sexo = *nuevoSexo;
            }
            break;
        case 3:
            if(nuevoTelefono == NULL){
                printf("No se encontro memoria para el telefono.\n");
                exit(1);
            }else{
                control = getNumb(nuevoTelefono, 22, "\nIngrese nuevo telefono: ", "Error, ingrese solo numeros respetando el rango (hasta 21 digitos). Reingrese: ", 3);
                if(control == 0){
                    printf("\nNo se pudo registrar el telefono!\n");
                }else{
                    strcpy((lista+indice)->telefono, nuevoTelefono);
                }
            }
            break;
        }
    }
    free(opcion);
    free(nuevoNombre);
    free(nuevoSexo);
    free(nuevoTelefono);
    return control;
}

int modificarCliente(eCliente* lista, int TAM_CLIENTES, int *codigo){
    int* indice = (int*) malloc(sizeof(int));
    int* control = (int*) malloc(sizeof(int));
    int bandera;
    char* seguir = (char*) malloc(sizeof(char));

    if(lista != NULL && TAM_CLIENTES > 0){
        system("cls");
        printf("  *** Modificar cliente ***\n\n");
        *control = getInt(codigo, "Ingrese codigo de cliente: ", "Error, ingrese solo numeros respetando el rango (1 - 10): ", 1, 10, 3);
        if(*control != 1){
            bandera = 0;
            printf("\nNo se obtuvo el codigo de cliente.");
        }else{
            *indice = buscarCliente(lista, TAM_CLIENTES, *codigo);
            if(*indice == -1){
                bandera = -1;
            }else{
                printf("Legajo   Nombre   Apellido     Sueldo     Sector\n");
                mostrarCliente(lista+(*indice)); // d
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
                    bandera = menuModificarCliente(lista, *indice, TAM_CLIENTES);
                }
            }
        }
    }
    free(indice);
    free(control);
    free(seguir);
    return bandera;
}

int bajaCliente(eCliente* lista, int TAM_CLIENTES, int *codigo){
    int* indice = (int*) malloc(sizeof(int));
    int bandera, *control = (int*) malloc(sizeof(int));
    char* seguir = (char*) malloc(sizeof(char));

    if(lista != NULL && TAM_CLIENTES > 0){
        system("cls");
        printf("  *** Baja de cliente ***\n\n");
        *control = getInt(codigo, "Ingrese codigo de cliente: ", "Error, ingrese solo numeros respetando el rango (1 - 10): ", 1, 10, 3);
        if(*control != 1){
            bandera = 0;
            printf("\nNo se obtuvo el codigo de cliente.");
        }else{
            *indice = buscarCliente(lista, TAM_CLIENTES, *codigo);
            if(*indice == -1){
                bandera = -1;
            }else{
                printf("Legajo   Nombre   Apellido     Sueldo     Sector\n");
                mostrarCliente(lista+(*indice)); // d
                printf("\nDesea dar de baja este cliente?.. s/n: ");
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

int menuSeleccionarCliente(eCliente* lista, int TAM_CLIENTES){
    int opcion;
    int* control = (int*) malloc(sizeof(int));
    if(lista != NULL){
        system("cls");
        mostrarListadoDeClientes(lista, TAM_CLIENTES);
        *control = getInt(&opcion, "\nSeleccione Cliente: ", "Error, ingrese un cliente de la lista: ", 1, 7, 3);
        if(*control == 0){
            opcion = 0;
        }
    }
    free(control);
    return opcion;
}

void listarClientesXapellidoAscendente_Insercion(eCliente* clientes, int TAM_CLIENTES){
    int* posicion = (int*) malloc(sizeof(int));
    int* contador = (int*) malloc(sizeof(int));
    eCliente* aux = (eCliente*) malloc(sizeof(eCliente));
    int* bandera = (int*) malloc(sizeof(int));
    *bandera = 0;

    if(aux == NULL || clientes == NULL){
        printf("No se consiguio memoria para ordenar el listado\n");
        exit(1);
    }else{
        if(TAM_CLIENTES > 0){
            for(*contador = 1; *contador <= TAM_CLIENTES; (*contador)++){
                *posicion = *contador;
                while((*posicion > 0) && strcmp((clientes+(*posicion))->nombre, (clientes+(*posicion-1))->nombre) < 0){
                    *aux = *(clientes+(*posicion-1));
                    *(clientes+(*posicion-1)) = *(clientes+(*posicion));
                    *(clientes+(*posicion)) = *aux;
                    (*posicion)--;
                    *bandera = 1;
                }
            }
        }
        else{
            printf("El tamanio del array debe ser mayor a 0.");
        }
    }
    if(*bandera == 1){
        mostrarListadoDeClientes(clientes, TAM_CLIENTES);
    }
    else{
        printf("Problemas para ordenar el listado de clientes.");
    }
    free(bandera);
    free(posicion);
    free(contador);
    free(aux);
}

int esHombre(eCliente* clientes, int TAM_CLIENTES, int codigo){
    int bandera = 0;

    for(int contador = 0; contador < TAM_CLIENTES; contador++){
        if((clientes+contador)->codigo == codigo){
            if((clientes+contador)->sexo == 'm' || (clientes+contador)->sexo == 'M'){
                bandera = 1;
            }
        }
    }
    return bandera;
}
