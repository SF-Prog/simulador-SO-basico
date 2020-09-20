
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

// #include "aStruct.h"
#include "dFuncLin.h"

using namespace std;

// FUNCIONES AUX Linea


//PRE:El archivo debe estar creado
//POST:Devulve la cantidad de filas de un archivo
int CantLineas(Linea l){
    int cantL = 0;
    while (l != NULL){
          cantL ++;
          l = l->sig;
    }
    return cantL;
}

//PRE: La lista de lineas debe estar creada
//POST: Devuelve true si la lista es vacia, false en otro caso
bool isEmptyArchivoLineas(Linea l){
    return (l == NULL);
}
