
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>


// #include "aStruct.h"
#include "cFuncArch.h"

using namespace std;

//FUNCIONES DE ARCHIVO

//PRE: La lista archivos debe estar creada
//POST: Devuelve true si la lista es vacia, false en otro caso
bool isEmptyArchivo(Archivo a){
    return (a == NULL);
}

//PRE: recibe una lista con por lo menos 1 elemento.
//POST: Retorna la lista sin su primer elemento.
Archivo TailArchivo(Archivo a){
    return a->sig;
}

//PRE: la lista de archivos debe contener al menos un archivo
//POST: Compara nom y ext con los archivos de la lista para saber si estan repetidos
bool existeArchivo(Archivo ArchivosCol, char nom[], char ext[]){
    if(!isEmptyArchivo(ArchivosCol)){
        if((strcmp(ArchivosCol->nombre, nom) == 0) && (strcmp(ArchivosCol->extension, ext) == 0)){
            return true;
        }else{
            return existeArchivo(TailArchivo(ArchivosCol), nom, ext);
        }
    }
   return false;
}


//PRE: deben haber archivos sino no imprime
//POST: muestra toda la coleccion de archivos
void Imprimir_archivos(Archivo arch){

    while(arch != NULL){
        cout << arch->nombre <<"."<< arch->extension << "     " << "Archivo     " << arch->tamanio << endl; //Imprimo el renglon
        arch = TailArchivo(arch);
    }
}

//pre: recibe una ListaArchivos creada.
//pos: busca en la lista el archivo y lo devuelve.
Archivo buscarArchivo(Sistema s, char nom[], char ext[]){
    bool encontre = false;
    Archivo auxArchivos = s->dirActual->aprimero;
    Archivo res;


    while(auxArchivos != NULL && !encontre){

      if ((strcmp(auxArchivos->nombre, nom) == 0) && (strcmp(auxArchivos->extension, ext) == 0)){
         encontre = true;
         res = auxArchivos;
       }else{
         auxArchivos = TailArchivo(auxArchivos);
       }

    }

    return res;
}
bool tienePunto(char nom[]){
    int cont=0, i=0;
    while(nom[i] != '\0'){
          if(nom[i] == '.'){
            cont++;
            if(nom[i+1] == '\0'){
                return false;
            }
          }
          i++;
    }
    return (cont == 1);
}

// void ordenarArchs(sistema &s){
//    Directorio DirCol = s->dirActual;
//    Archivo arch = DirCol->aprimero;
//
//
//    if(arch != NULL){
//           while(arch != NULL){
//                while()
//           }
//    }
//
//
//
// }
