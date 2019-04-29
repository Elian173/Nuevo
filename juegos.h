#ifndef JUEGOS_H_INCLUDED
#define JUEGOS_H_INCLUDED
#include "categorias.h"

typedef struct{
    int codigo;
    char descripcion[20];
    int idMarca;
    float importe;
    int idCategoria;
    int isEmpty;
}eJuego;

typedef struct{
    int idMarca;
    char nombre[20];
}eMarca;

/** \brief
 * \param
 * \param
 * \return
 */
int iniciarJuegos(eJuego* lista, int TAM_JUEGOS);

/** \brief
 * \param
 * \param
 * \param
 * \return
 *
 */
int buscarJuego(eJuego* lista, int TAM_JUEGOS, int codigo);

/** \brief
 * \param
 * \param
 * \param
 * \return
 */
void mostrarJuego(eJuego* juego, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS);

/** \brief
 * \param
 * \param
 * \param
 * \param
 * \return
 */
void mostrarListadoDeJuegos(eJuego* lista, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS);

/** \brief
 * \param
 * \param
 * \param
 * \param
 * \return
 */
int menuSeleccionarJuego(eJuego* lista, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS);

/** \brief
 * \param
 * \param
 * \return
 */
void hardcodearJuegos(eJuego* lista, int TAM_JUEGOS);

/** \brief
 * \param
 * \param
 * \return
 */
int buscarLibreJuegos(eJuego* lista, int TAM_JUEGOS);

/** \brief
 * \param
 * \param
 * \return
 */
int comprobarRegistroJuegos(eJuego* lista, int TAM_JUEGOS);

/** \brief
 * \param
 * \param
 * \param
 * \param
 * \return
 */
int ingresarJuego(eJuego* lista, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS);

/** \brief
 * \param
 * \param
 * \param
 * \param
 * \param
 * \return
 */
int modificarJuego(eJuego* lista, int TAM_JUEGOS, int *codigo, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS);

/** \brief
 * \param
 * \param
 * \param
 * \return
 */
int menuModificarJuego(eJuego* lista, int indice, int TAM_JUEGOS);

/** \brief
 * \param
 * \param
 * \param
 * \param
 * \param
 * \return
 */
int bajaJuego(eJuego* lista, int TAM_JUEGOS, int *codigo, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS);

void mostrarListadoDeJuegos_queNoSuperanElImportePromedio(eJuego* lista, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS, float* promedio, eMarca* marcas, int TAM_MARCAS);

eJuego* inicializarEnCero(eJuego* juegos, int TAM_JUEGOS);

void listarJuegosOrdenadosXimporteDescendente(eJuego* juegos, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS);
void getMarca(eMarca* lista, int TAM_MARCAS, int juegoIdMarca, char* cadena);
int menuSeleccionarMarca(eMarca* lista, int TAM_MARCAS);
void mostrarListadoDeMarcas(eMarca* lista, int TAM_MARCAS);
void mostrarMarca(eMarca* marca);
void hardcodearMarca(eMarca* lista, int TAM_MARCAS);

void JuegosDeUnaMarcaDeterminada(eJuego* juegos, int TAM_JUEGOS, eCategoria* categorias, int TAM_CATEGORIAS, eMarca* marcas, int TAM_MARCAS);

#endif // JUEGOS_H_INCLUDED
