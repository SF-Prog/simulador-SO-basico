
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

// #include "aStruct.h"
#include "fFuncPap.h"

using namespace std;


//------------------------------------------------------------------------------------------------
//Funciones auxiliares para implementar el DELETE y UNDELET
//REVISAR


// void push(Papelera &p, Archivo aux){
//   Papelera papNuevo = new struct str_papelera;
//   Archivo archNuevo = new struct nodo_archivo;
//
//   strcpy(archNuevo->nombre,aux->nombre);
//   strcpy(archNuevo->extension,aux->extension);
//   archNuevo->tamanio    = aux->tamanio;
//   archNuevo->lprimero   = aux->lprimero;
//   archNuevo->lultimo    = aux->lultimo;
//
//   //guardamos el anterior y el siguiente del archivo que estoy guardando para
//   //el UNDELETE, para saber donde ubcarlo.
//   archNuevo->ant = aux->ant;
//   archNuevo->sig = aux->sig;
//
//   papNuevo->deleted_arch = archNuevo;
//   if(!isEmptyStack(p)){ // Este if no funciona correctamente pero realiza lo que necesito de todas formas
//     papNuevo->sig = p;
//   }else{
//     papNuevo->sig = NULL;
//   }
//
//   p = papNuevo;
//
// }
//
// bool isEmptyStack(Papelera p){
//   return (p == NULL);
// }
// Archivo pop(Papelera &p){
//    Archivo arch = p->deleted_arch;
//    Papelera post = p;
//    p = p->sig;
//    return arch;
//    delete post; //DUDA sobre si hay que borrar este espacio de memory
// }
//
// int height(Papelera p){
//    int cont = 0;
//    while(!isEmptyStack){
//         cont ++;
//         p = p->sig;
//    }
//    return cont;
// }


// TipoRet DIRPAPELERA(Papelera &p/*, char * parametro, char &error[]*/){
//   char mensaje[100];
//   TipoRet Respuesta;
//   Respuesta = OK;
//
//   cout << "\n Dir-Papelera:  " << endl;
//   if(p == NULL){
//     cout << "Error: No hay archivos para mostrar" << endl;
//     Respuesta = ERROR;
//
//   }else{ // Hay que ir recorriendo el sistema hasta NULL
//     Papelera pap = p;
//
//     // Hay que ir recorriendo el sistema hasta NULL
//     while(!isEmptyStack(pap)){
//       cout << pap->deleted_arch->nombre << endl; //Imprimo el renglon
//       pap = pap->sig;
//     };
//
//   }
//
//   cout << "\n " << endl;
//   return Respuesta;
// }
