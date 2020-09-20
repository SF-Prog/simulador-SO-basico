
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

// #include "aStruct.h"
#include "xFuncOb1.h"
#include "xFuncOb2.h"


#include "bFuncDir.h"
#include "cFuncArch.h"
#include "dFuncLin.h"
#include "fFuncPap.h"

using namespace std;




 // FUNCIONES PARA LA PRIMERA PARTE DEL OBLIGATORIO

 // FUNCIONES TIPO 1

 //PRE: No tiene, solo que si no hay arch u directorios no los puede mostrar
 //POST: Muestra los archivos y directorios creados en el sistema
 TipoRet DIR(Sistema &s, char parametro[]/*, char &error[]*/){
   TipoRet Respuesta;
   char mensaje[TEXTO_LARGO];
   Directorio dirActual;
   Directorio auxSubDir;
   Archivo aux_archivo;
   parametro = NULL;

   dirActual   = s->dirActual;
   aux_archivo = dirActual->aprimero;

   if ((isEmptyDirectorio(dirActual->der)) && (isEmptyArchivo(aux_archivo))){
     strcpy (mensaje, "No hay nada en el sistema");
     Respuesta = ERROR;
   }else{
     //hay cosas
     //si no estoy en raiz, si estoy en un sub nivel
     auxSubDir   = subDir(dirActual);

     // Hay que ir recorriendo el sistema hasta NULL
     if(!isEmptyArchivo(aux_archivo)){
       Imprimir_archivos(aux_archivo);
     }
     if(!isEmptyDirectorio(auxSubDir)){
       Imprimir_directorios(auxSubDir, parametro);
     }
     strcpy (mensaje, "--------------------");
     Respuesta = OK;

     }

     cout << mensaje << endl;
     return Respuesta;
    }



 //PRE: No Tiene
//POST: Crea un archivo nuevo en el sistema (Si cumple con las comprobaciones)
TipoRet CREATE (Sistema &s, char nombreArchivo[]/*, string &mensaje*/){

    TipoRet Respuesta;
    char mensaje[TEXTO_LARGO]; // para mostrar el error en la pantalla

    Archivo nuevo = new struct nodo_archivo;
    Directorio dirActual;
    char nombreArchivoActual[ARCH_NOM_MAX];
    char nom[NOMBRE_MAX];
    char ext[EXT_MAX];
    char aux[200];
    bool encontre = false;
    char nomCompleto[ARCH_NOM_MAX];

    char ruta[200],dato[200];

    //RUTA

    if(esRuta(nombreArchivo)){
      CortarRuta(nombreArchivo,ruta,dato);

      if((CD(s,ruta)) == OK){
        nombreArchivo[0]= '\0';
        strcpy(nombreArchivo, dato);
      } else {
        strcpy (mensaje, "La ruta no es correcta");
        Respuesta = ERROR;
        cout << mensaje << endl;
        return Respuesta;
      }
      //------------------------------------

    } else {
      strcpy(nombreArchivo,nombreArchivo);

    }

    strcpy(nomCompleto, nombreArchivo);


    dirActual   = s->dirActual;
  if(!tienePunto(nombreArchivo)){

    strcpy (mensaje, "El nombre del archivo es invalido");
    Respuesta = ERROR;

  }else{
    //dividimos nomArch para poder estudiarlo mejor
    strcpy(nom,strtok(nombreArchivo, "."));
    strcpy(ext,strtok(NULL, "\n"));

  //comprobamos que cumpla con las condiciones para ser ingresado
  if(strlen(nombreArchivo) > (NOMBRE_MAX + EXT_MAX + 1)){
      strcpy (mensaje, "El largo del archivo excede los caracteres permitidos");
      Respuesta = ERROR;
    }else if((strlen(nom) >= NOMBRE_MAX) || (strlen(ext) >= EXT_MAX) ){

       strcpy (mensaje, "Nombre de archivo no valido, supera el largo de caracteres");
       Respuesta = ERROR;
   }else{

     //Cumple los requisitos minimos, copiamos al archivo nuevo
      strcpy(aux, nom);
      strcpy(nuevo->nombre,aux);
      strcpy(aux, ext);
      strcpy(nuevo->extension,aux);
      nuevo->tamanio = 0;

     // if (isEmptySistema(s)) {
     if (isEmptyArchivo(dirActual->aprimero)) {
         //Sistema vacio
         nuevo->sig           = NULL;
         nuevo->ant           = NULL;
         nuevo->lprimero      = NULL;
         nuevo->lultimo       = NULL;
         dirActual->aprimero  = nuevo;
         dirActual->aultimo   = nuevo;
         s->dirActual         = dirActual;

         strcpy (mensaje, "Se ha creado el archivo.");
         Respuesta = OK;
     }else{
        //Hay archivos en el sistema, comprobamos su existencia
        //Para hacerlo, nos guardamos la posicion del primer archivo
        //dirActual   = s->directorio;
        Archivo ArchivosCol = dirActual->aprimero;

        if(existeArchivo(ArchivosCol, nom, ext)){
          //El archivo existe y por lo tanto no podemos crearlo
          strcpy (mensaje, "Lo lamento, el archivo ya existe");
          Respuesta = ERROR;
        } else {

          //Restablecemos ArchivosCol al inicio ya que la funcion existeArchivo lo mueve
          ArchivosCol = dirActual->aprimero;
          //Mientras no llegue al final y no encuentre lugar donde colocar el archivo ordenado
          while((ArchivosCol != NULL) && (encontre == false)){


            //Armo el nombre completo del archivo para comparar el criterio de ordenamiento
            strcpy(nombreArchivoActual,ArchivosCol->nombre);
            strcat(nombreArchivoActual,".");
            strcat(nombreArchivoActual,ArchivosCol->extension);

            // Compara, si es menor va antes
            if(strcmp(nomCompleto,nombreArchivoActual) < 0){
              encontre = true;
            // }else if(ArchivosCol->sig != NULL){
            //   cout << " else if .. encontro " << endl;
            //   encontre = true;
            }else{
              ArchivosCol = TailArchivo(ArchivosCol);
            }

          }

          //No encontre donde colocar el archivo asi que va a lo ultimo
          if(!encontre){
            ArchivosCol = dirActual->aultimo;
          }
          //Estudiamos donde colocar
          if((ArchivosCol->ant == NULL) && (ArchivosCol->sig == NULL) && (strcmp(nomCompleto,nombreArchivoActual) > 0)){
            //Si solo se inserto el primer archivo/directorio quiere decir que mi anterior y mi siguiente es NULL y
            //mi nombre de archivo es mayor al ultimo nombre de archivo recorrido en el while. (rebuscado para mi gusto...pero funciona!)
            nuevo->sig        = NULL;
            nuevo->ant        = ArchivosCol;
            nuevo->lprimero = NULL;
            nuevo->lultimo = NULL;
            ArchivosCol->sig  = nuevo;
            dirActual->aultimo        = nuevo;
            s->dirActual         = dirActual;

          }else if(ArchivosCol->ant == NULL){
            //Si hay que ingresar en el primer lugar
            nuevo->ant        = NULL;
            nuevo->sig        = ArchivosCol;
            nuevo->lprimero = NULL;
            nuevo->lultimo = NULL;
            ArchivosCol->ant  = nuevo;
            dirActual->aprimero       = nuevo;
            s->dirActual         = dirActual;

          }else if((ArchivosCol->sig == NULL) && (!encontre)){
            //Si estoy en el ultimo lugar ingreso al final
            nuevo->sig        = NULL;
            nuevo->ant        = ArchivosCol;
            nuevo->lprimero = NULL;
            nuevo->lultimo = NULL;
            ArchivosCol->sig  = nuevo;
            dirActual->aultimo        = nuevo;
            s->dirActual         = dirActual;

          }else{
            //Hay que colocar en el medio
            nuevo->ant              = ArchivosCol->ant;
            nuevo->sig              = ArchivosCol;
            nuevo->lprimero = NULL;
            nuevo->lultimo = NULL;
            ArchivosCol->ant->sig   = nuevo;
            ArchivosCol->ant        = nuevo;
          }

        strcpy (mensaje, "Se ha creado el archivo.");
         Respuesta = OK;

        }
     }
  }
}

    s->dirActual = s->directorio;
  cout << mensaje << endl;
  return Respuesta;
}

//PRE: El archivo debe estar creado
//POST: Inserta una linea al final del archivo
TipoRet IF(Sistema &s, char nombreArchivo[], char texto[]/*, char error[]*/){

  TipoRet Respuesta;
  char mensaje[TEXTO_LARGO]; //texto de la linea o del error
  char nom[NOMBRE_MAX]; //nombre del archivo partido
  char ext[EXT_MAX]; //extension archivo partido
  bool encontre = false; // para la func que busca y nos posiciona arriba del arch a insertar

  char ruta[200],dato[200];

  //RUTA

  if(esRuta(nombreArchivo)){
    CortarRuta(nombreArchivo,ruta,dato);

    if((CD(s,ruta)) == OK){
      strcpy(nombreArchivo, dato);

    } else {
      strcpy (mensaje, "La ruta no es correcta");
      Respuesta = ERROR;
      cout << mensaje << endl;
      return Respuesta;
    }
    //------------------------------------

  } else {
    strcpy(nombreArchivo,nombreArchivo);

  }


  //partimos el nomarch en nom y ext
  strcpy(nom,strtok(nombreArchivo, "."));
  strcpy(ext,strtok(NULL, "\n"));

  //Primera comprobacion, no hay archivos
  if (isEmptySistema(s)){
    strcpy (mensaje, "No hay archivos en el sistema");
    Respuesta = ERROR;
  } else {

    //Primero nos hacemos una copia del primero para restablecer el sistema al final del proceso
    Archivo dirPrim = s->dirActual->aprimero;

    //Ya que no es vacia copiamos el primer archivo de la lista para manejarla desde ahi
    Archivo auxArchivos = s->dirActual->aprimero;

    //Comprobamos que el texto a ingresar no supere los 50 caracteres
    if ((strlen(texto) > TEXTO_LARGO)) {
       strcpy (mensaje, "El largo del texto es mayor al soportado por el archivo");
       Respuesta = ERROR;

    //----------------------------------------------------------------------------------------------------
    } else if (!existeArchivo(auxArchivos, nom, ext)) {

      //Esta funcion comprueba sobre toda la lista de arch si hay coincidencia de nom y ext
      strcpy (mensaje, "No existe el archivo");
      Respuesta = ERROR;

    } else {

      // Ya que el archivo existe en el sistema, hay que pararse sobre el para poder escribir
      // Fuerzo aux a ser el primero nuevamente porque la func existearchivo lo mueve de lugar
      auxArchivos = s->dirActual->aprimero;
      //Recorro la estructura para hayar el arch a escribir
      while ((auxArchivos != NULL) && (encontre == false)) {
        if ((strcmp(auxArchivos->nombre, nom) == 0) && (strcmp(auxArchivos->extension, ext) == 0)){
          encontre = true;
        }else{
          auxArchivos = TailArchivo(auxArchivos);
        }
       }

       // Hay que pensar una funcion que haga que existearch diga donde, nos ahorrariamos pila de codigo
       // Para la segunda entrega porque ahora no hay tiempo
       //-------------------------------------------------------------------------------------------------------
       // Ya sabemos que el arch existe y estamos sobre el, solo qeda insertar las lineas
       // En este caso, al FINAL


       Linea newline = new struct nodo_linea;
       //le agregamos el texto a la nueva linea
       strcpy (newline->renglon, texto);
       //contamos cuantos caracteres vamos a ingresar
       newline->cantCaracteres = strlen(texto);

       //Primero preguntamos si es Vacio
       if(isEmptyArchivoLineas(auxArchivos->lultimo)){

         newline->sig  = NULL;
         newline->ant  = NULL;
         auxArchivos->lprimero  = newline;
         auxArchivos->lultimo   = newline;
         auxArchivos->tamanio   = newline->cantCaracteres;

         strcpy (mensaje, "Se inserto la linea");
         Respuesta = OK;


       }else{

         //Hay mas lineas escritas
         newline->sig               = NULL;
         newline->ant               = auxArchivos->lultimo;

         auxArchivos->lultimo->sig  = newline;

         auxArchivos->lultimo       = newline;


         //suma los caracteres de la nueva linea al total
         auxArchivos->tamanio       = auxArchivos->tamanio + newline->cantCaracteres;
         strcpy (mensaje, "Se inserto la linea");
         Respuesta = OK;

        }
    }
    //Restablecemos la estructura sistema ya que se corrio para pararse sobre el arch


    s->dirActual->aprimero = dirPrim;

}
cout << mensaje << endl;
return Respuesta;
}

//PRE: El archivo debe existir
//POST: Muestra el contenido del archivo
TipoRet TYPE( Sistema &s, char nombreArchivo[]/*, char error[]*/ ){

   TipoRet Respuesta;
   char mensaje[TEXTO_LARGO];
   bool encontre = false;
   char nom[NOMBRE_MAX];
   char ext[EXT_MAX];

   //Limpiamos la variable mensaje
    mensaje[0] = '\0';

    char ruta[200],dato[200];

    //RUTA

    if(esRuta(nombreArchivo)){
      CortarRuta(nombreArchivo,ruta,dato);

      if((CD(s,ruta)) == OK){
        strcpy(nombreArchivo, dato);
      } else {
        strcpy (mensaje, "La ruta no es correcta");
        Respuesta = ERROR;
        cout << mensaje << endl;
        return Respuesta;
      }
      //------------------------------------

    } else {
      strcpy(nombreArchivo,nombreArchivo);

    }


   strcpy(nom,strtok(nombreArchivo, "."));
   strcpy(ext,strtok(NULL, "\n"));

   if (isEmptySistema(s)){
        strcpy (mensaje, "No hay archivos en el sistema");
        Respuesta = ERROR;
   } else {

     //Para poder restablecer el sistema
     Archivo auxArchivos = s->dirActual->aprimero;
     //Recorro en busca del arch a leer
    while ((auxArchivos != NULL) && (encontre == false)) {
        if ((strcmp(auxArchivos->nombre, nom) == 0) && (strcmp(auxArchivos->extension, ext) == 0)){
          encontre = true;
        }else{
          auxArchivos = TailArchivo(auxArchivos);
        }
      }
      //si encontre es true quiere decir que existe el archivo y a su vez estoy sobre el
      if (encontre == true) {
        //Si lo encontre compruebo si tiene lineas escritas
        if(isEmptyArchivoLineas(auxArchivos->lprimero)){
          strcpy (mensaje, "No hay lineas escritas");
          Respuesta = ERROR;
        } else {
          //Tiene lineas asi que imprimimos todo
           Linea auxLinea = auxArchivos->lprimero;
            while (auxLinea != NULL) {
                 //Imprime
                 cout << auxLinea->renglon << endl;
                 auxLinea = auxLinea->sig;
               }
         }
      } else {
        //no existe el archivo
        strcpy (mensaje, "No existe el archivo");
        Respuesta = ERROR;
      }
    }
  cout << "\n" << mensaje << endl;
  return Respuesta;
}




// FUNCIONES TIPO 2
//------------------------------------------------------------------


//----------- REVISAR COMENTARIOS-----------------------------------------

//PRE: El archivo a eliminar debe estar creado
//POST: "Borra" un archivo del sistema
TipoRet DELETE(Sistema& s, char nombreArchivo[]/*, char& error[]*/) {

    TipoRet Respuesta;
    char mensaje[TEXTO_LARGO]; //EN ESTE CASO MENSAJE DE ERROR
    char nom[NOMBRE_MAX]; //nombre del archivo partido
    char ext[EXT_MAX]; //extension archivo partido
    bool encontre = false;
    // Papelera p;
    // p = s->papelera;

    char ruta[200],dato[200];

    //RUTA

    if(esRuta(nombreArchivo)){
      CortarRuta(nombreArchivo,ruta,dato);

      if((CD(s,ruta)) == OK){
        strcpy(nombreArchivo, dato);
      } else {
        strcpy (mensaje, "La ruta no es correcta");
        Respuesta = ERROR;
        cout << mensaje << endl;
        return Respuesta;
      }
      //------------------------------------

    } else {
      strcpy(nombreArchivo,nombreArchivo);

    }

    //para poder hacer las modificaciones en el sistema
    Archivo aux = s->dirActual->aprimero;

    //partimos el nomarch en nom y ext para poder usar la func existeArch y de esa manera ya guardar el mismo en la papelera
    strcpy(nom,strtok(nombreArchivo, "."));
    strcpy(ext,strtok(NULL, "\n"));


    if (isEmptySistema(s)){
         strcpy (mensaje, "No hay archivos en el sistema");
         Respuesta = ERROR;

    } else if (!existeArchivo(aux, nom, ext)) {
      //esta funcion comprueba sobre toda la lista de arch si hay coincidencia de nom y ext
      strcpy (mensaje, "No existe el archivo");
      Respuesta = ERROR;
    } else {
      // Ya que el archivo existe en el sistema, hay que pararse sobre el para poder mandarlo a la papelera
      // Fuerzo aux a ser el primero nuevamente porque la func existearchivo lo mueve de lugar
      aux = s->dirActual->aprimero;

      //Recorro la estructura para hayar el arch a escribir
      while ((aux != NULL) && (encontre == false)) {
        if ((strcmp(aux->nombre, nom) == 0) && (strcmp(aux->extension, ext) == 0)){
          encontre = true;
        }else{
          aux = TailArchivo(aux);
        }
       }
       // Hay que pensar una funcion que haga que existearch diga donde, nos ahorrariamos pila de codigo
       // Para la segunda entrega porque ahora no hay tiempo
       //-------------------------------------------------------------------------------------------------------
       // Ya sabemos que el arch existe y estamos sobre el, solo qeda moverlo a la papelera

//********************* aca se pudrio la torta
// Parece qe eliminar elimina bien pero cuando tiramos la func push no la manda al Stack
// las funciones auxiliares del stackestan  al final del .cpp y tambien estan declaradas en el .h
          // push(p, aux);
          // //Actualizamos la papelera;
          // s->papelera = p;
          //Continuamos con la eliminacion
           if ((aux->sig  == NULL) && (aux->ant == NULL)){ //aca solo hay un archivo
                  s->dirActual->aprimero = NULL;
                  s->dirActual->aultimo = NULL;
                  Respuesta = OK;
                  strcpy (mensaje, "El archivo ha sido eliminado correctamente");

           }else if(aux->ant == NULL){    //tamos en el primero
                  s->dirActual->aprimero = s->dirActual->aprimero->sig;
                  s->dirActual->aprimero->ant = NULL;
                  Respuesta = OK;
                  strcpy (mensaje, "El archivo ha sido eliminado correctamente");

           }else if(aux->sig == NULL){ //tamos en el ultimo
                  s->dirActual->aultimo = s->dirActual->aultimo->ant;
                  s->dirActual->aultimo->sig = NULL;
                  Respuesta = OK;
                  strcpy (mensaje, "El archivo ha sido eliminado correctamente");

           }else{
             // en el medio
              aux->sig->ant = aux->ant;
              aux->ant->sig = aux->sig;
              Respuesta = OK;
              strcpy (mensaje, "El archivo ha sido eliminado correctamente");

           }

           delete aux;

     cout << mensaje << endl;
     return Respuesta;
   }
}
//---------------------------------------------------------------------------


//PRE: El archivo debe estar creado
//POST: Devuelve el archivo con k menos lineas al final
TipoRet BF(Sistema &s, char nombreArchivo[], int k/*, char error[]*/) {

  TipoRet Respuesta;
  char mensaje[TEXTO_LARGO]; //texto de la linea o del error
  char nom[NOMBRE_MAX]; //nombre del archivo partido
  char ext[EXT_MAX]; //extension archivo partido
  bool encontre = false; // para la func que busca y nos posiciona arriba del arch a insertar
  int  cantCaracteres = 0;

  char ruta[200],dato[200];

  //RUTA

  if(esRuta(nombreArchivo)){
    CortarRuta(nombreArchivo,ruta,dato);

    if((CD(s,ruta)) == OK){
      strcpy(nombreArchivo, dato);
    } else {
      strcpy (mensaje, "La ruta no es correcta");
      Respuesta = ERROR;
      cout << mensaje << endl;
      return Respuesta;
    }
    //------------------------------------

  } else {
    strcpy(nombreArchivo,nombreArchivo);

  }





  //partimos el nomarch en nom y ext
  strcpy(nom,strtok(nombreArchivo, "."));
  strcpy(ext,strtok(NULL, "\n"));

  //Primera comprobacion, no hay archivos
  if (isEmptySistema(s)){
    strcpy (mensaje, "No hay archivos en el sistema");
    Respuesta = ERROR;
  } else {
    //Primero nos hacemos una copia del primero para restablecer el sistema al final del proceso
    Archivo dirPrim = s->dirActual->aprimero;
    //Ya que no es vacia copiamos el primer archivo de la lista para manejarla desde ahi
    Archivo auxArchivos = s->dirActual->aprimero;

    if (!existeArchivo(auxArchivos, nom, ext)) {
      //Esta funcion comprueba sobre toda la lista de arch si hay coincidencia de nom y ext
      strcpy (mensaje, "No existe el archivo");
      Respuesta = ERROR;
    } else {
      // Ya que el archivo existe en el sistema, hay que pararse sobre el para poder borrar las k lineas
      // Fuerzo aux a ser el primero nuevamente porque la func existearchivo lo mueve de lugar
      auxArchivos = s->dirActual->aprimero;
      //Recorro la estructura para hayar el arch a escribir
      while ((auxArchivos != NULL) && (encontre == false)) {
        if ((strcmp(auxArchivos->nombre, nom) == 0) && (strcmp(auxArchivos->extension, ext) == 0)){
          encontre = true;
        }else{
          auxArchivos = TailArchivo(auxArchivos);
        }
       }
       // Hay que pensar una funcion que haga que existearch diga donde, nos ahorrariamos pila de codigo
       // Para la segunda entrega porque ahora no hay tiempo
       //-------------------------------------------------------------------------------------------------------
       // Ya sabemos que el arch existe y estamos sobre el, solo qeda borrar las lineas
       // En este caso, al FINAL

       Linea lineaPrim = auxArchivos->lprimero;

       //Primero preguntamos si es Vacio
       if(isEmptyArchivoLineas(auxArchivos->lultimo)){
            strcpy (mensaje, "No hay lineas escritas");
            Respuesta = ERROR;

        } else if (k >= CantLineas(auxArchivos->lprimero)) {
            //si tiene mas o igual lineas que k queda vacio
            auxArchivos->lprimero = NULL;
            auxArchivos->lultimo  = NULL;
            auxArchivos->tamanio  = 0;

            strcpy (mensaje, "El documento quedo vacio");
            Respuesta = OK;

        } else {

          auxArchivos->lprimero = lineaPrim;

          // tiene mas lineas que k
          for (int i=0; i<k; i++) {
            //borra k lineas del final
            cantCaracteres = cantCaracteres + strlen(auxArchivos->lultimo->renglon);
            auxArchivos->lultimo = auxArchivos->lultimo->ant;
          }

          auxArchivos->tamanio = auxArchivos->tamanio - cantCaracteres;
          auxArchivos->lultimo->sig = NULL; //apuntamos a sig null la lienea que no borro
          s->dirActual->aprimero = dirPrim; //reestablecemos la estructura original

          strcpy (mensaje, "Se borraron las k lineas");
          Respuesta = OK;
        }
      }
  }

  cout << mensaje << endl;
  return Respuesta;
}


// te confundiste con la ultima comprobación, te la marque en los COMENTARIOS
//hay que comprobar que los archivos tengan contenido sino imposible concatenar
//PRE: Los dos archivos deben existir y el segundo archvo debe tener lineas escritas
//POST: Concatena dos archivos (copia el cont de uno al final del otro)
TipoRet CAT(Sistema &s, char nombreArchivo1[], char nombreArchivo2[]/*, char error[]*/){

  TipoRet Respuesta;
  char mensaje[TEXTO_LARGO];
  char auxArchNombreCompleto_A[NOMBRE_MAX+EXT_MAX+2]; //+2 por las dudas
  char nomArch1[NOMBRE_MAX],nomArch2[NOMBRE_MAX] ; //nombre del archivo partido
  char extArch1[EXT_MAX], extArch2[EXT_MAX]; //extension archivo partido

  char ruta[200],dato[200],ruta2[200],dato2[200];

  //RUTA

  if(esRuta(nombreArchivo1)){
    CortarRuta(nombreArchivo1,ruta,dato);

    if((CD(s,ruta)) == OK){
      strcpy(nombreArchivo1, dato);
    } else {
      strcpy (mensaje, "La ruta no es correcta");
      Respuesta = ERROR;
      cout << mensaje << endl;
      return Respuesta;
    }
    //------------------------------------

  } else {
    strcpy(nombreArchivo1,nombreArchivo1);

  }



  if(esRuta(nombreArchivo2)){
    CortarRuta(nombreArchivo2,ruta,dato);

    if((CD(s,ruta)) == OK){
      strcpy(nombreArchivo2, dato);
    } else {
      strcpy (mensaje, "La ruta no es correcta");
      Respuesta = ERROR;
      cout << mensaje << endl;
      return Respuesta;
    }
    //------------------------------------

  } else {
    strcpy(nombreArchivo2,nombreArchivo2);

  }


  //nos quedamos con el nombre completo del archivo ya que luego se parte con el strtok
  //para poder decirle a la funcion ic qe en este archivo van a ir todas las lineas del arch 2
  strcpy(auxArchNombreCompleto_A,nombreArchivo1);

  Archivo Archivos1 = s->dirActual->aprimero;
  Archivo Archivos2 = s->dirActual->aprimero;

  //partimos el nombreArchivo1 en nom y ext
  strcpy(nomArch1,strtok(nombreArchivo1, "."));
  strcpy(extArch1,strtok(NULL, "\n"));
  Archivo arch_A = buscarArchivo(s, nomArch1,extArch1);

  //partimos el nombreArchivo2 en nom y ext
  strcpy(nomArch2,strtok(nombreArchivo2, "."));
  strcpy(extArch2,strtok(NULL, "\n"));
  Archivo arch_B = buscarArchivo(s, nomArch2,extArch2);

    // Controles:
    // 1 Hay archivos en sistema?
    // 2 verificar existencia de archivos
    // 3 si los dos archivs no son el mismo
    // 4 que tngan algo escrito

  //Primera comprobacion, no hay archivos
  if (isEmptySistema(s)){
    strcpy (mensaje, "ERROR: No hay archivos en el sistema");
    Respuesta = ERROR;

  } else if ((!existeArchivo(arch_A, nomArch1, extArch1)) || (!existeArchivo(arch_B, nomArch2, extArch2))) {
    //esta funcion comprueba sobre toda la lista de arch si hay coincidencia de nom y ext
    strcpy (mensaje, "ERROR: No existe el archivo");
    Respuesta = ERROR;

  } else if(arch_A == arch_B){ //Comparamos por dirección de memoria
    strcpy (mensaje, "ERROR: Los archivos deben ser diferentes.");
    Respuesta = ERROR;

  } else if (isEmptyArchivoLineas(arch_B->lprimero)) {
    // no sirve porque no tiene nada escrito
    strcpy (mensaje, "El segundo archivo no tiene nada escrito");
    Respuesta = ERROR;
  } else {

    //Primer renglon del archivo que voy a copiar
    Linea cabLinea = arch_B->lprimero;

    //recorro todas las lineas del archivo dos y inserto al final en el archivo uno.
    while(cabLinea != NULL){
      IF(s, auxArchNombreCompleto_A, cabLinea->renglon);
      cabLinea = cabLinea->sig;
    }

    strcpy (mensaje, "OK: Se copio el contenido correctamente.");
    Respuesta = OK;

  }

  cout << mensaje << endl;
  mensaje[0] = '\0';
  return Respuesta;

}


// FUNCIONES TIPO 3
//----------------------------------------------------------------

//PRE: El archivo debe estar creado
//POST: Inserta una linea al comienzo del archivo
TipoRet IC ( Sistema &s, char nombreArchivo[], char texto[]/*, char error[] */) {

  TipoRet Respuesta;
  char mensaje[TEXTO_LARGO]; //texto de la linea o del error
  char nom[NOMBRE_MAX]; //nombre del archivo partido
  char ext[EXT_MAX]; //extension archivo partido
  bool encontre = false; // para la func que busca y nos posiciona arriba del arch a insertar

  char ruta[200],dato[200];

  //RUTA

  if(esRuta(nombreArchivo)){
    CortarRuta(nombreArchivo,ruta,dato);

    if((CD(s,ruta)) == OK){
      strcpy(nombreArchivo, dato);
    } else {
      strcpy (mensaje, "La ruta no es correcta");
      Respuesta = ERROR;
      cout << mensaje << endl;
      return Respuesta;
    }
    //------------------------------------

  } else {
    strcpy(nombreArchivo,nombreArchivo);

  }




  //partimos el nomarch en nom y ext
  strcpy(nom,strtok(nombreArchivo, "."));
  strcpy(ext,strtok(NULL, "\n"));

  //Primera comprobacion, no hay archivos
  if (isEmptySistema(s)){
    strcpy (mensaje, "No hay archivos en el sistema");
    Respuesta = ERROR;
  } else {

    //Primero nos hacemos una copia del primero para restablecer el sistema al final del proceso
    Archivo dirPrim = s->dirActual->aprimero;
    //Ya que no es vacia copiamos el primer archivo de la lista para manejarla desde ahi
    Archivo auxArchivos = s->dirActual->aprimero;

    //Comprobamos que el texto a ingresar no supere los 50 caracteres
    if ((strlen(texto) > TEXTO_LARGO)) {
       strcpy (mensaje, "El largo del texto es mayor al soportado por el archivo");
       Respuesta = ERROR;

    //----------------------------------------------------------------------------------------------------
    } else if (!existeArchivo(auxArchivos, nom, ext)) {
      //Esta funcion comprueba sobre toda la lista de arch si hay coincidencia de nom y ext
      strcpy (mensaje, "No existe el archivo");
      Respuesta = ERROR;

    } else {

      // Ya que el archivo existe en el sistema, hay que pararse sobre el para poder escribir
      // Fuerzo aux a ser el primero nuevamente porque la func existearchivo lo mueve de lugar
      auxArchivos = s->dirActual->aprimero;
      //Recorro la estructura para hayar el arch a escribir
      while ((auxArchivos != NULL) && (encontre == false)) {
        if ((strcmp(auxArchivos->nombre, nom) == 0) && (strcmp(auxArchivos->extension, ext) == 0)){
          encontre = true;
        }else{
          auxArchivos = TailArchivo(auxArchivos);
        }
       }

       // Hay que pensar una funcion que haga que existearch diga donde, nos ahorrariamos pila de codigo
       // Para la segunda entrega porque ahora no hay tiempo
       //-------------------------------------------------------------------------------------------------------
       // Ya sabemos que el arch existe y estamos sobre el, solo qeda insertar las lineas
       // En este caso, al COMIENZO

       Linea newline = new struct nodo_linea;
       //le agregamos el texto a la nueva linea
       strcpy (newline->renglon, texto);
       //contamos cuantos caracteres vamos a ingresar
       newline->cantCaracteres = strlen(texto);

       //Primero preguntamos si es Vacio
       if(isEmptyArchivoLineas(auxArchivos->lprimero)){
         newline->sig  = NULL;
         newline->ant  = NULL;
         auxArchivos->lprimero  = newline;
         auxArchivos->lultimo   = newline;
         auxArchivos->tamanio   = newline->cantCaracteres;

         strcpy (mensaje, "Se inserto la linea");
         Respuesta = OK;

       }else{
         //no esta vacio asi que tengo que insertar al COMIENZO
           newline->sig = auxArchivos->lprimero;
           newline->ant = NULL;
           auxArchivos->lprimero->ant = newline;
           auxArchivos->lprimero      = newline;
           //suma los caracteres de la nueva linea al total
           auxArchivos->tamanio       = auxArchivos->tamanio + newline->cantCaracteres;

           strcpy (mensaje, "Se inserto la linea");
           Respuesta = OK;

        }
    }
    //Restablecemos la estructura sistema ya que se corrio para pararse sobre el arch
    s->dirActual->aprimero = dirPrim;
}
cout << mensaje << endl;
return Respuesta;
}


//PRE: El archivo debe estar creado
//POST: Devuelve el archivo con k menos lineas al comienzo

TipoRet BC(Sistema &s, char nombreArchivo[], int k/*, char error[]*/) {

TipoRet Respuesta;
  char mensaje[TEXTO_LARGO]; //texto de la linea o del error
  char nom[NOMBRE_MAX]; //nombre del archivo partido
  char ext[EXT_MAX]; //extension archivo partido
  bool encontre = false; // para la func que busca y nos posiciona arriba del arch a insertar
  int cantCaracteres = 0;

  char ruta[200],dato[200];

  //RUTA

  if(esRuta(nombreArchivo)){
    CortarRuta(nombreArchivo,ruta,dato);

    if((CD(s,ruta)) == OK){
      strcpy(nombreArchivo, dato);
    } else {
      strcpy (mensaje, "La ruta no es correcta");
      Respuesta = ERROR;
      cout << mensaje << endl;
      return Respuesta;
    }
    //------------------------------------

  } else {
    strcpy(nombreArchivo,nombreArchivo);

  }


  //partimos el nomarch en nom y ext
  strcpy(nom,strtok(nombreArchivo, "."));
  strcpy(ext,strtok(NULL, "\n"));

  //Primera comprobacion, no hay archivos
  if (isEmptySistema(s)){
    strcpy (mensaje, "No hay archivos en el sistema");
    Respuesta = ERROR;
  } else {
    //Primero nos hacemos una copia del primero para restablecer el sistema al final del proceso
    Archivo dirPrim = s->dirActual->aprimero;
    //Ya que no es vacia copiamos el primer archivo de la lista para manejarla desde ahi
    Archivo auxArchivos = s->dirActual->aprimero;

    if (!existeArchivo(auxArchivos, nom, ext)) {
      //Esta funcion comprueba sobre toda la lista de arch si hay coincidencia de nom y ext
      strcpy (mensaje, "No existe el archivo");
      Respuesta = ERROR;
    } else {
      // Ya que el archivo existe en el sistema, hay que pararse sobre el para poder borrar las k lineas
      // Fuerzo aux a ser el primero nuevamente porque la func existearchivo lo mueve de lugar
      auxArchivos = s->dirActual->aprimero;
      //Recorro la estructura para hayar el arch a escribir
      while ((auxArchivos != NULL) && (encontre == false)) {
        if ((strcmp(auxArchivos->nombre, nom) == 0) && (strcmp(auxArchivos->extension, ext) == 0)){
          encontre = true;
        }else{
          auxArchivos = TailArchivo(auxArchivos);
        }
       }
       // Hay que pensar una funcion que haga que existearch diga donde, nos ahorrariamos pila de codigo
       // Para la segunda entrega porque ahora no hay tiempo
       //-------------------------------------------------------------------------------------------------------
       // Ya sabemos que el arch existe y estamos sobre el, solo qeda borrar las lineas
       // En este caso, al COMIENZO


       Linea lineaPrim = auxArchivos->lprimero;

       //Primero preguntamos si es Vacio
       if(isEmptyArchivoLineas(auxArchivos->lprimero)){
            strcpy (mensaje, "No hay lineas escritas");
            Respuesta = ERROR;

        } else if (k >= CantLineas(auxArchivos->lprimero)) {
            //si tiene mas o igual lineas que k queda vacio
            auxArchivos->lprimero = NULL;
            auxArchivos->lultimo = NULL;
            auxArchivos->tamanio = 0;

            strcpy (mensaje, "El documento quedo vacio");
            Respuesta = OK;

        } else {

          auxArchivos->lprimero = lineaPrim;

          // tiene mas lineas que k
          for (int i=0; i<k; i++) {
            //borra k lineas del final
            auxArchivos->lprimero = auxArchivos->lprimero->sig;
            cantCaracteres = cantCaracteres + strlen(auxArchivos->lprimero->renglon);
          }

          auxArchivos->tamanio = auxArchivos->tamanio - cantCaracteres;
          auxArchivos->lprimero->ant = NULL; //apuntamos a sig null la lienea que no borro
          s->dirActual->aprimero = dirPrim; //reestablecemos la estructura original

          strcpy (mensaje, "Se borraron las k lineas");
          Respuesta = OK;
        }
      }
  }
  cout << mensaje << endl;
  return Respuesta;
}







//-----------------------------------------
// FALTA HACER
//PRE: El archivo a restaurar no puede tener el mismo nombr que otro arch en el sist
//POST: Restaura un arch previamente borrado
TipoRet UNDELETE(Sistema &s/*, char * &error*/){
    char * error;

    TipoRet Respuesta;

    Respuesta = NO_IMPLEMENTADA;
    strcpy(error, "Funcion no implementada");

    return Respuesta;

}
//----------------------------------------
