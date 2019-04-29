#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validar.h"


int menu(){ // bien!
    int opcion;
    int* control = (int*) malloc(sizeof(int));
    system("cls");
    printf("-------------------------------------------------------------------------------------------");
    printf("\n\t\t>>> Menu de Opciones <<<\n\n");
    printf("-------------------------------------------------------------------------------------------\n");
    printf("*** Clientes ***\n\n");
    printf("  1- Alta\n");
    printf("  2- Modificar\n");
    printf("  3- Baja\n");
    printf("  4- Listado\n");
    printf("-------------------------------------------------------------------------------------------\n");
    printf("*** Alquileres ***\n\n");
    printf("  5- Alta\n");
    printf("  6- Modificar\n");
    printf("  7- Baja\n");
    printf("  8- Listado\n");
    printf("-------------------------------------------------------------------------------------------\n");
    printf("*** Juegos ***\n\n");
    printf("  9- Alta\n");
    printf(" 10- Modificar\n");
    printf(" 11- Baja\n");
    printf(" 12- Listado\n");
    printf("-------------------------------------------------------------------------------------------\n");
    printf("*** Informes ***\n\n");
    printf(" 13- Total y Promedio de los Importes de los Juegos Alquilados\n");
    printf(" 14- Cantidad de Juegos que no superan el Promedio de los Importes de los Juegos Alquilados\n");
    printf(" 15- Clientes que alquilaron un determinado juego\n");
    printf(" 16- Juegos alquilados por un determinado cliente\n");
    printf(" 17- El o los Juegos menos alquilados\n");
    printf(" 18- El o los Clientes que realizaron mas alquileres\n");
    printf(" 19- Juegos alquilados en una determinada fecha\n");
    printf(" 20- Clientes que alquilaron en una determinada fecha\n");
    printf(" 21- Juegos ordenados por importe (descendente)\n");
    printf(" 22- Clientes ordenados por apellido (ascendente - insercion)\n");
    printf("-------------------------------------------------------------------------------------------\n");
    printf("*** Recuperatorio ***\n\n");
    printf(" 23- Juegos de una Marca determinada\n");
    printf(" 24- Contador de alquileres para una Marca determinada\n");
    printf(" 25- Clientes que alquilaron Juegos de una Marca determinada\n");
    printf("-------------------------------------------------------------------------------------------\n");
    printf(" 30- Salir\n\n");
    *control = getInt(&opcion, "Ingrese opcion: ", "Error, ingrese una opcion de la lista: ", 1, 30, 3);
    if(*control == -1){
        opcion = 0;
    }
    free(control);
    return opcion;
}

int getInt(int *x, char* ing, char* err, int inf, int sup, int chances){
    int* control = (int*) malloc(sizeof(int));
    int bandera = 0;
    int* aux = (int*) malloc(sizeof(int));

    printf("%s", ing);
    *control = scanf("%d", aux);
    chances--;
    while((*control != 1 || *aux < inf || *aux > sup) && chances>=1){
        printf("%s", err);
        fflush(stdin);
        *control = scanf("%d", aux);
        chances--;
    }
    if(*control == 1){
        bandera = 1;
        *x = *aux;
    }
    free(control);
    free(aux);
    return bandera; // si (bandera == 0) no obtuvo el entero.
}

int getFloat(float *x, char* ing, char* err, int inf, int sup, int chances){
    int* control = (int*) malloc(sizeof(int));
    int bandera = 0;
    float* aux = (float*) malloc(sizeof(float));

    printf("%s", ing);
    *control = scanf("%f", aux);
    chances--;
    while((*control != 1 || *aux < inf || *aux > sup) && chances>=1){
        printf("%s", err);
        fflush(stdin);
        *control = scanf("%f", aux);
        chances--;
    }
    if(*control == 1){
        bandera = 1;
        *x = *aux;
    }
    free(control);
    free(aux);
    return bandera; // si (bandera == 0) no obtuvo el entero.
}

int validarSexo(char* sexo){
    int validar = 1;
    if (!(*sexo == 'm' || *sexo == 'f' || *sexo == 'F' || *sexo == 'M')){
        validar = 0;
    }
    return validar;
}

int validarNumero(char* numero, int tam){
    int* cantidad = (int*) malloc(sizeof(int));
    int* contador = (int*) malloc(sizeof(int));
    int validar = 1;
    *cantidad = strlen(numero);
    if(*cantidad >= tam){
        validar = 0;
    }
    for (*contador = 0; *contador < *cantidad; (*contador)++){
        if(*(numero+(*contador)) < '0' || *(numero+(*contador)) > '9'){
            validar = 0;
        }
    }
    free(cantidad);
    free(contador);
    return validar;
}

int validarRespuesta(char* respuesta){
    int validar = 1;
    if (!(*respuesta == 's' || *respuesta == 'n' || *respuesta == 'S' || *respuesta == 'N')){
        validar = 0;
    }
    return validar;
}

int validStrArr(char* cadena){
    int aux;
    int* contador = (int*) malloc(sizeof(int));
    for(*contador = 0; *contador < strlen(cadena); (*contador)++){ // recorre el array.
        if(!(isalpha(*(cadena+(*contador))))){
            aux = 0; // retorna 0 si algún caracter no es letra.
            break;
        }
        aux = 1;
    }
    free(contador);
    return aux; // retorna 1 si todos los caracteres son letras.
}

int getCharSexo(char *letra, char* ing, char* err, int chances){
    int* control = (int*) malloc(sizeof(int));
    int bandera = 0;
    char* auxChar = (char*) malloc(sizeof(char));

    printf("%s", ing);
    fflush(stdin);
    scanf("%c", auxChar);
    *control = validarSexo(auxChar);
    chances--;
    while(*control != 1 && chances>=1){
        printf("%s", err);
        fflush(stdin);
        scanf("%c", auxChar);
        *control = validarSexo(auxChar);
        chances--;
    }
    if(*control == 1){
        bandera = 1;
        *letra = *auxChar;
    }
    free(control);
    free(auxChar);
    return bandera; // si (bandera == 0) no obtuvo el caracter.
}

int getString(char* cadena, char* ing, char* err, int inf, int sup, int chances){
    int* length = (int*) malloc(sizeof(int));
    int control;

    printf("%s", ing);
    fflush(stdin);
    gets(cadena);
    control = validStrArr(cadena); // valida que todos los caracteres del array sean letras.
    *length = strlen(cadena); // contabiliza los caracteres del array.
    chances--;
    while((*length < inf || *length > sup || control == 0) && chances >= 1){
        chances--;
        printf("%s", err);
        fflush(stdin);
        gets(cadena);
        control = validStrArr(cadena);
    }
    free(length);
    return control; // si (control = 0) no obtuvo la cadena.
}

int getCharResp(char *letra, char* ing, char* err, int chances){
    int* control = (int*) malloc(sizeof(int));
    int bandera = 0;
    char* auxChar = (char*) malloc(sizeof(char));

    printf("%s", ing);
    fflush(stdin);
    scanf("%c", auxChar);
    *control = validarRespuesta(auxChar);
    chances--;
    while(!(*control == 1) && chances >= 1){
        printf("%s", err);
        fflush(stdin);
        scanf("%c", auxChar);
        *control = validarRespuesta(auxChar);
        chances--;
    }
    if(*control == 1){
        bandera = 1;
        *letra = *auxChar;
    }
    free(control);
    free(auxChar);
    return bandera; // si (bandera == 0) no obtuvo el caracter.
}

int getNumb(char* numero, int tam, char* ing, char* err, int chances){
    int control;

    printf("%s", ing);
    fflush(stdin);
    gets(numero);
    control = validarNumero(numero, tam); // valida que todos los caracteres del array sean numeros.
    chances--;
    while(control == 0 && chances >= 1){
        chances--;
        printf("%s", err);
        fflush(stdin);
        gets(numero);
        control = validarNumero(numero, tam);
    }
    return control; // si (control = 0) no obtuvo la cadena.
}
