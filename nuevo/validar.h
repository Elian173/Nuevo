#ifndef VALIDAR_H_INCLUDED
#define VALIDAR_H_INCLUDED


/** \brief
 * \return
 */
int menu();

/** \brief
 * \param
 * \param
 * \param
 * \param
 * \param
 * \param
 * \return
 */
int getInt(int *x, char* ing, char* err, int inf, int sup, int chances);

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
int getCharSexo(char *letra, char* ing, char* err, int chances);

/** \brief
 * \param
 * \return
 */
int validarSexo(char* sexo);

/** \brief
 * \param
 * \param
 * \return
 */
int validarNumero(char* numero, int tam);

/** \brief
 * \param
 * \return
 */
int validarRespuesta(char* respuesta);

/** \brief
 * \param
 * \return
 */
int validStrArr(char* cadena);

/** \brief
 * \param
 * \param
 * \param
 * \param
 * \param
 * \param
 * \return
 */
int getString(char* cadena, char* ing, char* err, int inf, int sup, int chances);

/** \brief
 * \param
 * \param
 * \param
 * \param
 * \return
 */
int getCharResp(char *letra, char* ing, char* err, int chances);

/** \brief
 * \param
 * \param
 * \param
 * \param
 * \return
 */
int getNumb(char* numero, int tam, char* ing, char* err, int chances);

/** \brief
 * \param
 * \param
 * \param
 * \param
 * \param
 * \param
 * \return
 */
int getFloat(float *x, char* ing, char* err, int inf, int sup, int chances);

#endif // VALIDAR_H_INCLUDED
