#ifndef FECHAS_H_INCLUDED
#define FECHAS_H_INCLUDED

typedef struct{
    int dia;
    int mes;
    int anio;
    int isEmpty;
}eFecha;

/** \brief
 * \param
 * \param
 * \return
 */
int iniciarFechas(eFecha* lista, int TAM_FECHAS);

/** \brief
 * \param
 * \return
 */
int ingresarFecha(eFecha fecha);

#endif // FECHAS_H_INCLUDED
