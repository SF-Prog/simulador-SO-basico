//---------------------- MAIN REAL, LAS FUNCIONES ANDAN TODAS MENOS UNDELETE, ESTO TIENE QUE ANDARRRRRR !!!!!!!!

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <ctype.h>


//#include "aStruct.h"
#include "xFuncOb1.h"
#include "xFuncOb2.h"


#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif


using namespace std;


int main(){

	system(CLEAR);

    bool salir 	= false;
    bool msg 	= false;

    char comando[NOMBRE_MAX];
    char entradaCompleta[TEXTO_LARGO];
    char entradaSinComando[TEXTO_LARGO];
    char archivoNombre[ARCH_NOM_MAX];
    char archivoNombre2[ARCH_NOM_MAX];
    char texto[TEXTO_LARGO];
    // char op[LARGO_MAX];
    char mensaje[TEXTO_LARGO];
    char c_k[2];
    int k;
    // char dir[LARGO_PATH];
    int comm = 0;
    char finEnter;
    char caracterAux;
    int pos,posEspacio;
    TipoRet respuesta;

    //Inicializamos
		Linea l;
		Archivo a;
		Directorio d;
		Papelera p;
		Sistema s;

	init(l, a, d, p, s);




    while(!salir){

    	pos = 0;
    	posEspacio = 0;

		//Imprimimos path actual
		cout << "\n \\>";

		// === OPCIONES DE USUARIO ===

		//Leo el primer caracter
        scanf("%c", &finEnter);
        while(finEnter!= '\n'){
         	entradaCompleta[pos] = finEnter;
         	pos++;
         	scanf("%c", &finEnter);
        }

        //a la ultima posición le agrego el \0 para usar de bandera en el toUpper
        entradaCompleta[pos] = '\0';

        //convertimos a mayuscula
        for (int indice = 0; entradaCompleta[indice] != '\0'; ++indice){

			entradaCompleta[indice] = toupper(entradaCompleta[indice]);
			//guardamos la posición del espacio para saber si vamos a tener parametros
			if(isspace(entradaCompleta[indice])){
				posEspacio = indice;
			}
		}

 		//si la posición del espacio es mayor a 0 quiere decir que hay algo mas.
 		//de lo contrario copio solo en contenido de la variable que quiere decir que es un unico comando.
 		if(posEspacio > 0){
      strcpy(comando,strtok(entradaCompleta, " "));
			strcpy(entradaSinComando,strtok(NULL, "\n"));

 		}else{
 			strcpy(comando,entradaCompleta);
 		}


 		//Comparamos los comandos y llamamos
 		if(strcmp(comando,"DIR")==0){
 			respuesta = DIR(s,entradaSinComando);


 		}else if(strcmp(comando,"CREATE") == 0){
 			respuesta = CREATE(s, entradaSinComando);



 		}else if(strcmp(comando,"IF") == 0){
      // if(okComillas(entradaSinComando)){
		    strcpy(archivoNombre,strtok(entradaSinComando, " "));
				strcpy(texto,strtok(NULL, "\""));
	 			respuesta = IF (s, archivoNombre, texto);
 			// }else{
				// cout<<"El texto debe estar entre comillas."<<endl;
 			//  }



        }else if(strcmp(comando,"TYPE") == 0){
          respuesta = TYPE (s, entradaSinComando);



        }else if(strcmp(comando,"DELETE") == 0){
          respuesta = DELETE (s, entradaSinComando);



        }else if(strcmp(comando,"BF") == 0){
          strcpy(archivoNombre,strtok(entradaSinComando, " "));
        	strcpy(c_k,strtok(NULL, "\n"));
        	k = atoi(c_k);
          respuesta = BF (s, entradaSinComando, k);



        }else if(strcmp(comando,"CAT") == 0){
        	strcpy(archivoNombre,strtok(entradaSinComando, " "));
        	strcpy(archivoNombre2,strtok(NULL, "\n"));
        	respuesta = CAT (s, archivoNombre, archivoNombre2);


        }else if(strcmp(comando,"IC") == 0){
          // if(okComillas(entradaSinComando)){
			    	strcpy(archivoNombre,strtok(entradaSinComando, " "));
						strcpy(texto,strtok(NULL, "\""));
		 			 	respuesta = IC (s, archivoNombre, texto);
		 			// }else{
						// cout<<"El texto debe estar entre comillas."<<endl;
		 			//  }



        }else if(strcmp(comando,"BC") == 0){
          strcpy(archivoNombre,strtok(entradaSinComando, " "));
        	strcpy(c_k,strtok(NULL, "\n"));
        	k = atoi(c_k);
          respuesta = BC (s, entradaSinComando, k);



        }else if(strcmp(comando,"UNDELETE") == 0){

          cout << "Funcion no implementada" <<endl;



				}else if(strcmp(comando,"MKDIR") == 0){
					respuesta = MKDIR(s, entradaSinComando);

				}else if(strcmp(comando,"CD") == 0){
					respuesta = CD(s, entradaSinComando);

        }else if(strcmp(comando,"PWD") == 0){
					respuesta = PWD(s, entradaSinComando);

        }else if(strcmp(comando,"RMDIR") == 0){
					respuesta = RMDIR(s, entradaSinComando);

        }else if(strcmp(comando,"EXIT") == 0){
            system(CLEAR);
            salir = true;

        }

        //Finaliza la cadena de IF, ahora inicializamos variables para la siguiente vuelta del while
        // a no ser que se haya ingresado el comando exit
        entradaCompleta[0] = '\0';
        comando[0] = '\0';
        entradaSinComando[0] = '\0';
        c_k[0]= '\0';


    };


    return 0;

}













/*






#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "sistema.h"


using namespace std;


int main(){

	// Sistema s;
 	// s = crearSistema();
 	// Archivo a;
 	// a = crearArchivo();
	// Linea l;
	// l = crearLinea();


 Sistema s;
 Archivo a;
 Linea l;
 Papelera p;
 init (s, a, l, p);

 	TipoRet res;
 	char arch[100];
 	char arch2[100]; //para probar el cat


	strcpy(arch,"xyz.xyz");
 	res = CREATE (s, arch);
 	arch[0] = '\0';

   	strcpy(arch,"abc.abc");
   	res = CREATE (s, arch);
	arch[0] = '\0' ;

	strcpy(arch,"fff.fff");
  	res = CREATE (s, arch);
  	arch[0] = '\0';

	strcpy(arch,"bcd.bcd");
  	res = CREATE (s, arch);
  	arch[0] = '\0';

    strcpy(arch,"sss.sss");
  	res = CREATE (s, arch);
  	arch[0] = '\0';

	res = DIR (s);


//---- IF

	char linea[100];


    strcpy(arch,"fff.fff");
	strcpy (linea, "ingresa al final 1");
	res = IF (s, arch, linea);
	linea[0] = '\0' ;
	arch[0] = '\0' ;

	strcpy(arch,"fff.fff");
	strcpy (linea, "ingresa al final 2");
	res = IF (s, arch, linea);
	linea[0] = '\0' ;
	arch[0] = '\0' ;


	//--- IC

	strcpy(arch,"fff.fff");
	strcpy (linea, "ingresa al comienzo 1...");
	res = IC (s, arch, linea);
	linea[0] = '\0' ;
	arch[0] = '\0' ;

    strcpy(arch,"fff.fff");
	strcpy (linea, "Metemos ingresa el comienzo 2...");
	res = IC (s, arch, linea);
	linea[0] = '\0' ;
	arch[0] = '\0' ;


	strcpy(arch,"fff.fff");
	strcpy (linea, "5o...");
	res = IC (s, arch, linea);
	linea[0] = '\0' ;
	arch[0] = '\0' ;



    strcpy(arch,"abc.abc");
	strcpy (linea, "6...");
	res = IC (s, arch, linea);
	linea[0] = '\0' ;
	arch[0] = '\0' ;


//mostramos


	strcpy(arch,"fff.fff");
	res = TYPE (s, arch);
	arch[0] = '\0' ;

	strcpy(arch,"abc.abc");
	res = IC (s, arch);
	arch[0] = '\0' ;


/*

// BC Y BF

	strcpy(arch,"fff.fff");
	res = BF (s, arch, 1);
	linea[0] = '\0' ;
	arch[0] = '\0' ;

	strcpy(arch,"fff.fff");
	res = BC (s, arch, 1);
	linea[0] = '\0' ;
	arch[0] = '\0' ;


*/


//TYPE
/*

	strcpy(arch,"abc.abc");
	res = TYPE (s, arch);
	arch[0] = '\0' ;


/*
	strcpy(arch,"abc.abc");
	cout << "\n MANDAMOS TYPE EL ARCH abc.abc" << endl;
	res = TYPE (s, arch);
	arch[0] = '\0' ;


// dir

res = DIR (s);


//---------------------------- DIR CREATE IF TYPE ANDAN
//---------------------------- DELETE BF CAT ANDAN
//---------------------------- IC BC ANDAN




// DELETE
    strcpy(arch,"bcd.bcd");
	res = DELETE (s, arch);
	arch[0] = '\0' ;
	//cout << "\n DELETEAMOS EL ARCHIVO SSS.SSS" << endl;

res = DIR (s);

*/

// CAT
/*

cout << "\n ====  Comienza CAT ==== \n" << endl;


	arch[0] = '\0' ;
	arch2[0] = '\0' ;


    strcpy(arch,"abc.abc");
	strcpy(arch2,"fff.fff");
	res = CAT(s, arch, arch2);
	arch[0] = '\0' ;
	arch2[0] = '\0' ;


cout << "\n ====  MUESARTA FFF ==== \n" << endl;
    strcpy(arch,"fff.fff");
    res = TYPE (s, arch);
    arch[0] = '\0' ;


cout << "\n ====  MUESARTA ABC ==== \n" << endl;
    strcpy(arch,"abc.abc");
    res = TYPE (s, arch);
    arch[0] = '\0' ;



 	// char texto[150];
 	// char basura[150];
	// char total[150];
	// strcpy (texto, "hola \"amigos como estn\"");
	//  strcpy(basura,strtok(texto, "\""));
	//  strcpy(total,strtok(NULL, "\""));
	//   cout << basura <<endl;
	//  cout << total <<endl;





	return 0;


}

*/
