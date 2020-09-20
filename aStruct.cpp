
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "aStruct.h"

using namespace std;


Linea crearLinea(){
    Linea aux = new struct  nodo_linea;
    aux->renglon[0]   = '\0';
    aux->sig          = NULL;
    aux->ant          = NULL;
    return aux;
}


Archivo crearArchivo(){
    Archivo aux = new struct  nodo_archivo;
    aux->nombre[0]    = '\0';
    aux->extension[0] = '\0';
    aux->tamanio      = 0;
    aux->sig          = NULL;
    aux->ant          = NULL;
    aux->lprimero     = NULL;
    aux->lultimo      = NULL;
    return aux;
}


Directorio crearDirectorio(){
  Directorio aux = new struct  str_directorio;
  aux->nombre[0]        = '\\';
  //aux->cota             = 0;
  aux->tamanio          = 0;
  aux->ruta_absoluta[0] = '\\';
  aux->aprimero         = NULL;
  aux->aultimo          = NULL;
  aux->padre            = NULL;
  aux->izq              = NULL;
  aux->der              = NULL;
  return aux;
}


Papelera crearPapelera(){
    Papelera p = new struct str_papelera;
    p->sig          = NULL;
    p->deleted_arch = NULL;
    return p;
}


Sistema crearSistema(){
    Sistema aux = new struct  str_sistema;
    aux->directorio = NULL;
    aux->dirActual  = NULL;
    aux->aprimero   = NULL;
    aux->aultimo    = NULL;
    aux->papelera   = NULL;
    return aux;
}



// FUNCION INIT CREA EL SISTEMA LOS ARCHIVOS Y LAS LINEAS
void init(Linea &l, Archivo &a, Directorio &d, Papelera &p, Sistema &s){
  l = crearLinea();
  a = crearArchivo();
  d = crearDirectorio();
  p = crearPapelera();
 	s = crearSistema();

  // a->lprimero = l;
  // a->lultimo  = l;
  // s->aprimero = a;
  // s->aultimo  = a;
  s->directorio = d;
  s->dirActual = d;
  s->papelera = p;
 }






 //FUNCIONES DE SISTEMA


  //PRE: la lista sistema debe estar creada;
  //POST: Devuele true si la lista es vacia, false en otro caso.
  bool isEmptySistema(Sistema s){
      return (s->dirActual->aprimero == NULL);
  }


  //pre:recibe un array
  //pos:devuelve true en caso de que el texto se encuentr entre comiilas, false en caso contrario.
  bool okComillas(char texto[]){
    // int cantEncuentro = 0;
    // int indice = 0;
    // char comilla[1];
    // char texto2[100];

    // strcpy(texto2,texto);

    // while((texto[indice] != '\0') && (cantEncuentro < 2)){
    //   // strcpy(texto2, texto[indice]);
    //   if(strcmp(texto2,"\"") == 0){
    //     cantEncuentro++;
    //   }
    //   indice++;
    // }
    // cout << "cantEncuentro: " << cantEncuentro << endl;

    // if(cantEncuentro = 2){
    //   return true;
    // }else{
    //   return false;
    // }
  }
