
#ifndef BFUNCDIR_H
#define BFUNCDIR_H

#include "aStruct.h"
#include "cFuncArch.h"




// FUNCIONES AUXILIARES PARA DIRECTORIO

//nuevas
bool esRuta(char ruta[]);
void CortarRuta (const std::string &ruta, char rutaFinal[], char datoFinal[]);

//
bool existeDir(Directorio DirCol, char nom[]);
bool existeDir2(Sistema &s, char nom[]);
bool buscoDir(Sistema &s, char nom[]);
void agregarBarraFinal(char nom[]);
bool PrimerCBarra(char nombreDirS[]);

//PWD
void imprimoPadres(Directorio d);

//DIR
void Imprimir_directorios(Directorio d, char parametro[]);

//BASICAS
Directorio siguienteDir(Directorio d);
Directorio subDir(Directorio d);
bool isEmptyDirectorio(Directorio d);

//RMDIR
void borrarDir(Directorio &d, char NombreDir[]);
void borrarArchivos(Archivo &a);
void borrarSubDir(Directorio &d);
void borrarLineas(Linea l);


// ???
bool ultimaVuelta(char nombreDirectorio[]);
bool esRutaAbsoluta(char nombreDirectorio[]);
void NomDirRutaAbsoluta(char nombreDirectorio[], char retorno[]);




// ????????? ???????? ????? sin uso al momento
int valor(Directorio d);
Directorio Buscar(Directorio d, char NombreDir[]);
Directorio buscarMinimo(Directorio d);
Directorio buscarMaximo(Directorio d);
void insertar(Directorio &d, char NombreDir[], int cota);
void inOrden(Directorio d);
void postOrden(Directorio d);
void preOrden(Directorio d);
void borrarTodo(Directorio &d);







#endif
