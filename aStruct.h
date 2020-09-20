#ifndef ASTRUCT_H
#define ASTRUCT_H

#define MAX 50
#define NOMBRE_MAX 16
#define EXT_MAX 4
#define ARCH_NOM_MAX 21
#define RENGLON_LARGO_MAX 50
#define TEXTO_LARGO 100
#define RUTA 100


// DEFINIMOS FUNCION ERROR
enum retorno{
    OK, ERROR, NO_IMPLEMENTADA
};typedef enum retorno TipoRet;


// DEFINIMOS EL NODO LINEA
struct nodo_linea{
    char renglon[RENGLON_LARGO_MAX];
    int cantCaracteres;
    struct nodo_linea *ant;
    struct nodo_linea *sig;
};
typedef struct nodo_linea * Linea;


// DEFINIMOS NODO ARCH CON EL CABEZAL DE LINEA
struct nodo_archivo{
char nombre[NOMBRE_MAX];
 char extension[EXT_MAX];
int tamanio;
 struct nodo_archivo *sig;
 struct nodo_archivo *ant;
    // Cabezal linea
  Linea lprimero;
 Linea lultimo;
};
typedef struct nodo_archivo * Archivo;


//DEFINIMOS NODO DIRECTORIO CON SUS CABEZALES
struct str_directorio{
  char nombre[NOMBRE_MAX];
  //int cota;
  int tamanio;
  char ruta_absoluta[RUTA];
  Archivo aprimero;
  Archivo aultimo;

  struct str_directorio * padre;
  struct str_directorio * izq;
  struct str_directorio * der;

};typedef struct str_directorio * Directorio;


//DEFINIMOS PAPELERA // no es necesario hacerla pero la dejamos para el final.
struct str_papelera{
  Archivo deleted_arch;
  struct str_papelera * sig;
};
typedef struct str_papelera * Papelera;


// DEFINIMOS SISTEMA
struct str_sistema{
    Directorio directorio;
    Directorio dirActual;
   //Inicio quitar 
    Archivo aprimero;
    Archivo aultimo;

    //Papelera
    Papelera papelera;

};typedef str_sistema * Sistema;


// CREACIÓN SISTEMA
// -----------------
Linea crearLinea();
Archivo crearArchivo();
Directorio crearDirectorio();
Papelera crearPapelera();
Sistema crearSistema();


void init(Linea &l, Archivo &a, Directorio &d, Papelera &p, Sistema &s);




//func aux para el main

//pre:recibe un array
//pos:devuelve true en caso de que el texto se encuentr entre comiilas, false en caso contrario.
bool okComillas(char texto[]);


// func aux para sistema

//PRE: la lista sistema debe estar creada;
//POST: Devuele true si la lista es vacia, false en otro caso.
bool isEmptySistema(Sistema s);









#endif
