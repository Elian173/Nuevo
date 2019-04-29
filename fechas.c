#include <stdio.h>
#include <stdlib.h>
#include "fechas.h"
#include "validar.h"


int iniciarFechas(eFecha* lista, int TAM_FECHAS){ // bien!
    int retorno = -1;
    if(TAM_FECHAS > 0 && lista != NULL){
        retorno = 0;
        for(int contador=0; contador < TAM_FECHAS; contador++){
            (lista+contador)->isEmpty = 1;
        }
    }
    return retorno;
}

int ingresarFecha(eFecha fecha){
    eFecha* nuevaFecha = (eFecha*) malloc(sizeof(eFecha));
    int control;
    control = getInt(&nuevaFecha->anio, "\nIngrese anio: ", "Error, ingrese numeros respetando el rango (2018 - 2020): ", 2018, 2024, 3);
    if(control == 0){
        printf("\nSe agotaron las chances y no se pudo ingresar el anio.\n");
    }else{
        control = getInt(&nuevaFecha->mes, "Ingrese mes: ", "\nError, ingrese numeros respetando el rango (1 - 12): ", 1, 12, 3);
        if(control == 0){
            printf("\nSe agotaron las chances y no se pudo ingresar el mes.\n");
        }else{
            switch(nuevaFecha->mes){
                case 2:
                    if(nuevaFecha->anio == 2020 || nuevaFecha->anio == 2024){
                        control = getInt(&nuevaFecha->dia, "Ingrese dia: ", "Error, ingrese numeros respetando el rango (1 - 29): ", 1, 29, 3);
                    }else{
                        control = getInt(&nuevaFecha->dia, "Ingrese dia: ", "Error, ingrese numeros respetando el rango (1 - 28): ", 1, 28, 3);
                    }
                    break;
                case 4:
                case 6:
                case 9:
                case 11:
                    control = getInt(&nuevaFecha->dia, "Ingrese dia: ", "Error, ingrese numeros respetando el rango (1 - 30): ", 1, 30, 3);
                    break;
                default:
                    control = getInt(&nuevaFecha->dia, "Ingrese dia: ", "Error, ingrese numeros respetando el rango (1 - 31): ", 1, 31, 3);
            }
            if(control == 0){
                printf("\nSe agotaron las chances y no se pudo ingresar el dia.\n");
            }else{
                fecha = *nuevaFecha;
            }
        }
    }
    free(nuevaFecha);
    return control;
}

int compararFecha(eFecha fecha1, eFecha fecha2){
    int esIgual = 0;

    if(fecha1.dia == fecha2.dia && fecha1.mes == fecha2.mes && fecha1.anio == fecha2.anio){
        esIgual = 1;
    }

    return esIgual;
}

void getFecha(eFecha* fecha){

    printf("ingrese dia: ");
    fflush(stdin);
    scanf("%d", &fecha->dia);
    printf("ingrese mes: ");
    scanf("%d", &fecha->mes);
    printf("ingrese anio: ");
    scanf("%d", &fecha->anio);

    fecha->isEmpty = 0;
}
