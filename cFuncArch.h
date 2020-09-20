#ifndef CFUNCARCH_H
#define CFUNCARCH_H

#include "aStruct.h"

// FUNCIONES AUXILIARES ARCHIVOS

//pre: recibe una ListaArchivos creada.
//pos: busca en la lista el archivo y lo devuelve.
Archivo buscarArchivo(Sistema s, char nom[], char ext[]);


//PRE: La lista archivos debe estar creada
//POST: Devuelve true si la lista es vacia, false en otro caso
bool isEmptyArchivo(Archivo a);

//PRE: recibe una lista con por lo menos 1 elemento.
//POST: Retorna la lista sin su primer elemento.
Archivo TailArchivo(Archivo a);

//PRE: la lista de archivos debe contener al menos un archivo
//POST: Compara nom y ext con los archivos de la lista para saber si estan repetidos
bool existeArchivo(Archivo ArchivosCol, char nom[], char ext[]);

//PRE: deben haber archivos sino no imprime
//POST: muestra toda la coleccion de archivos
void Imprimir_archivos(Archivo arch);

//PRE: n/a
//POST: retorna true si tiene un solo punto para el arch

bool tienePunto(char nom[]);


// void ordenarArchs(sistema &s);



#endif
