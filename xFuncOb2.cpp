
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

// #include "aStruct.h"
#include "xFuncOb2.h"


#include "bFuncDir.h"
#include "cFuncArch.h"
#include "dFuncLin.h"
#include "fFuncPap.h"

using namespace std;



TipoRet MKDIR (Sistema &s, char nombreDirectorio[]/*, string &mensaje*/){

  TipoRet Respuesta;
  char mensaje[TEXTO_LARGO]; // para mostrar el error en la pantalla

  bool encontre = false;
  bool insertOk = false;
  char nomDirAct[NOMBRE_MAX];
  char raiz[NOMBRE_MAX]={'\\'};
  char nom[NOMBRE_MAX];
  char ruta[200],dato[200];

  //RUTA

  if(esRuta(nombreDirectorio)){
    CortarRuta(nombreDirectorio,ruta,dato);

    if((CD(s,ruta)) == OK){
      strcpy(nom, dato);
    } else {
      strcpy (mensaje, "La ruta no es correcta");
      Respuesta = ERROR;
      cout << mensaje << endl;
      return Respuesta;
    }
    //------------------------------------

  } else {
    strcpy(nom,nombreDirectorio);

  }


  //Creamos nueva estructura para directorio
  Directorio nuevo = new struct str_directorio;
  Directorio DirCol, DirSiguiente;


  //comprobamos que cumpla con las condiciones para ser ingresado
  if(strlen(nom) > (NOMBRE_MAX)){
    strcpy (mensaje, "El largo del Directorio excede los caracteres permitidos");
    Respuesta = ERROR;

  } else if (strcmp(raiz, nom) == 0) {
    strcpy (mensaje, "No puede llamarse como la raiz");
    Respuesta = ERROR;

  } else {

   //Cumple los requisitos minimos, copiamos al dir nuevo :
   strcpy(nuevo->nombre,nom);
   nuevo->tamanio          = 0;
   //nuevo->ruta_absoluta[0] = '\\'; ACA ESTARIA DEPENDIENDO DE DIR ACTUAL
   nuevo->padre = s->dirActual;
   nuevo->aprimero         = NULL;
   nuevo->aultimo          = NULL;
   nuevo->izq              = NULL;
   nuevo->der              = NULL;

   DirCol = s->dirActual->der;

   if (existeDir(DirCol, nom)){
     //el dir existe y por lo tanto no podemos crearlo
     strcpy (mensaje, "Lo lamento, el dir ya existe");
     Respuesta = ERROR;

   } else {
     //el dir no existe y hay que insertarlo ordenadamente
     //reseteamos el dircol
     DirCol = s->dirActual->der;
     while((DirCol != NULL)/* && (encontre == false)*/){
       //comparamos en que lugar colocar
       //Armo el nombre completo del DIR para comparar el criterio de ordenamiento
       strcpy(nomDirAct,DirCol->nombre);
       // Compara, si es mayor va despues
       if(strcmp(nom,nomDirAct) > 0){
         DirSiguiente = DirCol;
         encontre = true;

       }

       DirCol = siguienteDir(DirCol);
     }

     DirCol = DirSiguiente;
     if((!encontre) && (!isEmptyDirectorio(s->dirActual->der))) {
       //Inserto al comienzo pero ya existen directorio, antonces arreglo en enganche
       nuevo->izq = s->dirActual->der;
       s->dirActual->der = nuevo;
       insertOk = true;

     }else if((!encontre) && (isEmptyDirectorio(s->dirActual->der))) {
       //Inserto al comienzo cuando no existen directorios en el arbol
       s->dirActual->der = nuevo;
       insertOk = true;

     } else {
       //inserto al final o al medio
       nuevo->izq = DirCol->izq;
       DirCol->izq = nuevo;
       insertOk = true;

     }
     if (insertOk) {

       strcpy (mensaje, "Se ha creado el archivo.");
       Respuesta = OK;


     }else{
       Respuesta = ERROR;

     }
   }
  }

    s->dirActual = s->directorio;
  cout << mensaje << endl;
  return Respuesta;
  }

TipoRet RMDIR (Sistema &s, char nombreDirectorio[]){


  TipoRet Respuesta;
  char mensaje[TEXTO_LARGO]; // para mostrar el error en la pantalla

  bool encontre = false;
  char nomDirAct[NOMBRE_MAX];
  char raiz[NOMBRE_MAX]={'\\'};
  char nom[NOMBRE_MAX];
  char nomAux[NOMBRE_MAX];
  Directorio DirCol;

  char ruta[200],dato[200];

  //RUTA

  if(esRuta(nombreDirectorio)){
    CortarRuta(nombreDirectorio,ruta,dato);

    if((CD(s,ruta)) == OK){
      strcpy(nom, dato);
    //  std::cout << "1" << '\n';

    } else {
      strcpy (mensaje, "La ruta no es correcta");
      Respuesta = ERROR;
      cout << mensaje << endl;
      return Respuesta;
    }
    //------------------------------------

  } else {
    //std::cout << "2" << '\n';
    strcpy(nom,nombreDirectorio);

  }


  //consulto si hay algun otro dir
  DirCol = s->dirActual->der;
  if (!existeDir(DirCol, nom)){
    strcpy (mensaje, "Lo lamento, el dir a eliminar no existe");
    Respuesta = ERROR;

  } else {
    //reseteamos el dircol
    DirCol = s->dirActual->der;
    borrarDir(DirCol,nombreDirectorio);

  }

}



TipoRet CD (Sistema &s, char nombreDirS[]){

    TipoRet Respuesta;

    //te guardas la posicion en caso de que falle y tengas que resetear
    Directorio dirActual;
    dirActual = s->dirActual;

    char mensaje[100];
    char nomruta[200];
    nomruta[0]= '\0';

    // aca cargarmos el nom en algo manejable
    strcpy (nomruta, nombreDirS);

    if(strcmp(nomruta, "..") == 0){
      if(s->dirActual->padre != NULL){
        s->dirActual = s->dirActual->padre;
      //  cout << "estamos en: " << s->dirActual->nombre << endl;
        Respuesta = OK;
        return Respuesta;
      }else{
         cout << "No se puede ejecutar ese comando" << endl;
         Respuesta = ERROR;
         return Respuesta;
    }
  }






    // Se le agrega la barra para poder usar la func buscodir
    agregarBarraFinal(nomruta);

        //consultamos si es abs o relativo
        if(PrimerCBarra(nomruta)){
          // nos paramos al inicio del arbol y e igualamos el dir col a eso
          s->dirActual = s->directorio;
        }
        //sino, dejamos el dir actual como esta


        if(buscoDir(s, nomruta)){
          strcpy(mensaje, "");
          //strcpy(mensaje, "OK: La busqueda se ejecuto satisfactoriamente, estamos parados sobre el dir deseado");
          Respuesta = OK;
        }else{
          //reseteamos porque busco dir nos dejo en cualquier lado
          s->dirActual = dirActual;
          strcpy(mensaje, "Error: La ruta es invalida");
          Respuesta = ERROR;
        }

    cout << mensaje << endl;
  //  cout << "Estamos en : " << s->dirActual->nombre << endl;
    return Respuesta;

}




TipoRet PWD(Sistema &s, char nombreDirectorio[]){

      TipoRet Respuesta = OK;
      char nombreDir[100], mensaje[100];
      Directorio DirCol;

      //Coloco mi puntero DirActual o lo identifico desde el sistema para empezara a leer los padres
      DirCol = s->dirActual;
      strcpy(nombreDir , nombreDirectorio);

      if (isEmptyDirectorio(s->directorio)) { // capaz izquierdo

              strcpy(mensaje, "no hay directorios en el sistema");
              cout << mensaje << endl;

      }else{
            //  cout << DirCol->nombre << "/" ;
              imprimoPadres(DirCol);
      }
      return Respuesta;
}
