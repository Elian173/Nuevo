#ifndef CATEGORIAS_H_INCLUDED
#define CATEGORIAS_H_INCLUDED

typedef struct{
    int id;
    char descripcion[50];
    int isEmpty;
}eCategoria;

/** \brief
 * \param
 * \param
 * \return
 */
int iniciarCategorias(eCategoria* lista, int TAM_CATEGORIAS);

/** \brief
 * \param
 * \param
 * \param
 * \param
 */
void getCategoria(eCategoria* lista, int TAM_CATEGORIAS, int juegoIdCat, char* cadena);

/** \brief
 * \param
 * \param
 * \return
 */
void hardcodearCategorias(eCategoria* lista, int TAM_CATEGORIAS);

/** \brief
 * \param
 * \param
 * \return
 */
int menuSeleccionarCategoria(eCategoria* lista, int TAM_CATEGORIAS);

/** \brief
 * \param
 * \param
 * \return
 */
void mostrarListadoDeCategorias(eCategoria* lista, int TAM_CATEGORIAS);

/** \brief
 * \param
 * \return
 */
void mostrarCategoria(eCategoria* categoria);

#endif // CATEGORIAS_H_INCLUDED
