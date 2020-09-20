#ifndef XFUNCOB1_H
#define XFUNCOB1_H

#include "aStruct.h"


// ------ FUNCIONES PRIMERA PARTE DEL OBLIGATORIO
// --- FUNCIONES TIPO 1

//PRE: No tiene, solo que si no hay arch u directorios no los puede mostrar
//POST: Muestra los archivos y directorios creados en el sistema
TipoRet DIR(Sistema &s, char parametro[]/*, char &error*/);

//PRE: No Tiene
//POST: Crea un archivo nuevo en el sistema (Si cumple con las comprobaciones)
TipoRet CREATE(Sistema &s, char nombreArchivo[]/*, char &error*/);

//PRE: El archivo debe estar creado
//POST: Inserta una linea al final del archivo
TipoRet IF(Sistema &s, char nombreArchivo[], char texto[]/*, char error[]*/);

//PRE: El archivo debe existir
//POST: Muestra el contenido del archivo
TipoRet TYPE(Sistema &s, char nombreArchivo[]/*, char error[]*/);


// --- FUNCIONES TIPO 2

//PRE: El archivo a eliminar debe estar creado
//POST: "Borra" un archivo del sistema
TipoRet DELETE(Sistema &s, char nombreArchivo[]/*, char &error*/);

//PRE: El archivo debe estar creado
//POST: Devuelve el archivo con k menos lineas al final
TipoRet BF(Sistema &s, char nombreArchivo[], int k/*, char error[]*/);

//PRE: Los dos archivos deben existir y el segundo archvo debe tener lineas escritas
//POST: Concatena dos archivos (copia el cont de uno al final del otro)
TipoRet CAT(Sistema &s, char nombreArchivo1[], char nombreArchivo2[]/*, char error[]*/);


// --- FUNCIONES TIPO 3

//PRE: El archivo debe estar creado
//POST: Inserta una linea al comienzo del archivo
TipoRet IC(Sistema &s, char nombreArchivo[], char texto[]/*, char error[]*/);

//PRE: El archivo debe estar creado
//POST: Devuelve el archivo con k menos lineas al comienzo
TipoRet BC(Sistema &s, char nombreArchivo[], int k/*, char error[]*/);

//PRE: El archivo a restaurar no puede tener el mismo nombr que otro arch en el sist
//POST: Restaura un arch previamente borrado
TipoRet UNDELETE(Sistema &s/*, char &error*/);


#endif
