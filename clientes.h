#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

typedef struct{
    int codigo;
    char nombre[51];
    char sexo;
    char telefono[21];
    int isEmpty;
}eCliente;

/** \brief
 * \param
 * \param
 * \return
 */
int iniciarClientes(eCliente lista[], int TAM_CLIENTES);

/** \brief
 * \param
 * \param
 */
void hardcodearClientes(eCliente* lista, int TAM_CLIENTES);

/** \brief
 * \param
 * \param
 * \return
 */
int buscarLibreClientes(eCliente* lista, int TAM_CLIENTES);

/** \brief
 * \param
 * \param
 * \param
 * \return
 */
int buscarCliente(eCliente* lista, int TAM_CLIENTES, int codigo);

/** \brief
 * \param
 */
void mostrarCliente(eCliente* cliente);

/** \brief
 * \param
 * \param
 * \return
 */
int mostrarListadoDeClientes(eCliente* lista, int TAM_CLIENTES);

/** \brief
 * \param
 * \param
 * \return
 */
int comprobarRegistroClientes(eCliente* lista, int TAM_CLIENTES);

/** \brief
 * \param
 * \param
 * \return
 */
void ordenarClientesXsexoYnombre(eCliente* lista, int TAM_CLIENTES);

/** \brief
 * \param
 * \param
 * \return
 */
int ingresarCliente(eCliente* lista, int TAM_CLIENTES);

/** \brief
 * \param
 * \param
 * \param
 * \return
 */
int menuModificarCliente(eCliente* lista, int indice, int TAM_CLIENTES);

/** \brief
 * \param
 * \param
 * \param
 * \return
 */
int modificarCliente(eCliente* lista, int TAM_CLIENTES, int *codigo);

/** \brief
 * \param
 * \param
 * \param
 * \return
 */
int bajaCliente(eCliente* lista, int TAM_CLIENTES, int *codigo);

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
int menuSeleccionarCliente(eCliente* lista, int TAM_CLIENTES);

void listarClientesXapellidoAscendente_Insercion(eCliente* clientes, int TAM_CLIENTES);

int esHombre(eCliente* clientes, int TAM_CLIENTES, int codigo);

#endif // CLIENTES_H_INCLUDED
