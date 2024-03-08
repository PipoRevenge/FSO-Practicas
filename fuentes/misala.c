//programa para copiar archivos
// ./copia -o fichero_origen -d fichero_destino [-y]
#include <stdio.h>  //para printf / fprintf
#include <stdlib.h> //para exit
#include <getopt.h> //para getopt
#include <string.h> //para strlen
//cabeceras para archivos
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>
//programa sala.c
#include "../cabeceras/sala.h"

//variables globales
char* nombre_orig;
int capaci;
int num_asientos;
int contadorIDS;
int fid_o,fid_d;
int f_flag=0, c_flag=0,n_flag=0,a_flag=0, o_flag=0;

//Error por stderr que indica un error de sintaxis en el comando
void lanza_error()
{
  fprintf(stderr, "Error de sintaxis. \n");
  exit(1);
}


void lanza_error_crea()
{
  fprintf(stderr, "El fichero existía y no se ha especificado -o para sobreescribir. \n");
  exit(1);
}

//Error por stderr que indica que el archivo no es accesible porque no existe o no se tienen permisos
void lanza_error_ruta()
{
  fprintf(stderr, "Ruta no válida o no se tienen permisos. \n");
  exit(1);
}

//Error por stderr que indica que el número de asientos no coincide 
//con la suma de los ids de las personas que se pasan después
void lanza_error_reserva()
{
  fprintf(stderr, "El número de asientos no coincide con los asientos pasados por parámetros. \n");
  exit(1);
}

//Error por stderr que indica que el archivo número de asientos no es válido porque no es un entero > 0
void lanza_error_reserva2()
{
  fprintf(stderr, "El número de asientos no es válido. \n");
  exit(1);
}

//Error por stderr que indica los asientos que no se pudieron liberar porque excedían la capacidad de la sala
void lanza_error_anula(const char* a)
{
  fprintf(stderr, "Los siguientes asientos no se han podido liberar porque exceden la capacidad de la sala %s\n", a);
  exit(1);
}


//Función que detecta los modificadores pasados por parámetros
void extrae_modificadores(int argc, char* argv[])
{
  int c;
  while((c=getopt(argc, argv, "f:f[o]:c:n:a:o")) !=-1) {
     switch(c){
     
         //Si se detcta una -f se asigna un lugar en memoria y copiamos el nombre con strcpy
         //(Optarg guarda el argumento en este caso apunta a una cadena)
         case 'f': 
            nombre_orig=malloc(strlen(optarg)*sizeof(char));
            strcpy(nombre_orig,optarg);
            if (nombre_orig == NULL) lanza_error_ruta();
            f_flag=1;
            break;
            
         //Si se detecta una -c indica que lo que le sigue es la capacidad, por lo tanto,
         //Lo convertimos a int y lo asignamos a la variable global capaci
         case 'c':
            capaci=atoi(optarg);
            //Activamos bandera (Usaremos después)
            c_flag=1;
            break;
         
         //Si se detecta una -n indica que lo que le sigue es el número de asientos totales
         //que se van a reservar por lo tanto,
         case 'n':
            num_asientos=atoi(optarg);
            //Activamos bandera (Usaremos después)
            n_flag=1;
            break;
         
         //Si se detecta una -a indica que lo que le sigue son los ids de las personas  
         case 'a': 
            //Activamos bandera (Usaremos después)
            a_flag=1;
            break;
            
         //Si se detecta una -o indica que si el fichero existe se sobreescribirá su contenido
         //al crear la sala   
         case 'o':
            //Activamos bandera (Usaremos después)
            o_flag=1;
            break;
         
         //Comprobamos que no haya ningún parámetro no permitido
         case '?':
            printf("Parámetro no permitido.");
            lanza_error();
            break;
     }
  
  }
  
}

int main(int argc, char* argv[])
{
  
  /*
  
    He elaborado como un menú por así decirlo, ya que el programa lee lo primero el segundo argumento
    y en función de este actúa de una manera u otra.
  
  */
  
  
     /*Primera opción- misala crea -f[o] ruta -c capacidad*/
      
  if(strcmp(argv[1],"crea") == 0){
  
        //Comprobamos que existan los argumentos justos, ni más ni menos
        if(argc < 6 || argc > 7){
             lanza_error();
        }else{
        
            //Llamamos a extrae modificadores
            extrae_modificadores(argc,argv);
            if(f_flag==1 && c_flag==1 && o_flag==0) lanza_error_crea();
            
            //Si se especifica la sobreescritura sobre un fichero se hace los siguiente
            if (f_flag = 1 && c_flag == 1 && o_flag == 1){
            
                 //Se crea la sala
                 crea_sala(capaci);
                 
                 //Si al guardar devuelve -1 lanzamos error de ruta no válida
                 if(guarda_estado_sala(nombre_orig)== -1) lanza_error_ruta();
                 
                 //liberamos el espacio de memoria
                 free(nombre_orig);
                 
            }
        
        }
        
  }
       /*Segunda opción- misala reserva -f ruta -n n_asientos id_personas....*/
       
  else if(strcmp(argv[1],"reserva") == 0){
  
        //Si intentamos hacer una reserva suponemos que hay guardado en el fichero el 
        //estado de una sala, por lo tanto recuperamos el estado de esa sala y procedemos
        
        //Primero calculamos que los argumentos estén en el rango
        if(argc < 7){
             lanza_error();
        }else{
            //Extraemos modificadores
            extrae_modificadores(argc,argv);
            
            //Si el número de asientos que se pasa por parámetro no es válido se devuelve error
            if(num_asientos <= 0) lanza_error_reserva2();
            
            //Si existe error al recuperar el estado de la sala se lanza error de ruta
            if(recupera_estado_sala(nombre_orig)==-1) lanza_error_ruta();
            
            //Calculamos los ids que se pasan
            int ids = argc - 6;
            
            //Comprobamos que el número de ids sea igual al número de asientos a reservar
            if(ids != num_asientos){
                 lanza_error_reserva();
                 return -1;
            }
            
            //Si se detecta ruta y numero de asientos
            if (f_flag = 1 && n_flag == 1){
            
                 //Bucle para reservar asientos
                 for(int j = 6; j<argc;j++){
                     int a = atoi(argv[j]);
                     reserva_asiento(a);
                 }
                 //Guardamos el estado de la sala y comprobamos si da error
                 if(guarda_estado_sala(nombre_orig)== -1) lanza_error_ruta();
                 //Liberamos espacio en memoria
                 free(nombre_orig);
                 
            }
        
        }
  
  
     /*Tercera opción- misala anula -f ruta -a id_asientos....*/
     
  }else if(strcmp(argv[1], "anula") == 0){
        //Si intentamos hacer una reserva suponemos que hay guardado en el fichero el 
        //estado de una sala, por lo tanto recuperamos el estado de esa sala y procedemos
        
        //Primero calculamos que los argumentos estén en el rango
        if(argc < 6){
             lanza_error();
        }else{
            //Extraemos modificadores
            extrae_modificadores(argc,argv);
            
            //Recuperamos estado de sala del fichero y comprobamos si da error
            if(recupera_estado_sala(nombre_orig)==-1) lanza_error_ruta();
            
            //Si detectamos ruta y ids de los asientos
            if (f_flag = 1 && a_flag == 1){
                 
                 //Si el id no es válido se debe devolver en un mensaje de error, para ello:
                 
                 //Creamos dos cadenas, una que cogera número a número
                 //Y otra para ir guardando
                 char asientos_no_validos[50];
                 char cade[20];
                 for(int j = 4; j<argc;j++){
                 
                     //Pasamos el id actual a int
                     int a = atoi(argv[j]);
                     
                     //Comprobamos si excede la capacidad
                     if (a > capacidad()){
                          //Pasamos el número a cadena y añadimos a la cadena almacenante
                          sprintf(asientos_no_validos, "%d, ", a);
                          strcat(cade, asientos_no_validos);
                     }else{
                     
                          //Liberamos el asiento
                          libera_asiento(a);
                     } 
                     
                 }
                 //Comprobamos si la cadena está vacía (Que ningún numero pasado por parámetro exceda la capacidad
                 if(cade[0] != '\0') lanza_error_anula(cade);
                 
                 //Guardamos el estado de la sala y comprobamos si da error
                 if(guarda_estado_sala(nombre_orig)== -1) lanza_error_ruta();
                 
                 //Liberamos espacio en memoria
                 free(nombre_orig);
                 
            }
        
        }
        
        /*Cuarta opción- misala estado -f ruta */
        
  }else if(strcmp(argv[1], "estado")==0){
       //Si vamos a mostrar el estado de una sala por pantalla suponemos que hay guardado en el fichero el 
       //estado de esta, por lo tanto recuperamos el estado de esa sala y procedemos
       
       //Primero calculamos que los argumentos estén en el rango
       if(argc < 4){
             lanza_error();
        }else{
            //Extraemos modificadores
            extrae_modificadores(argc,argv);
            
            //Recuperamos el estado de la sala y comprobamos si da error
            if(recupera_estado_sala(nombre_orig)==-1) lanza_error_ruta();
            
            //Si se detecta la ruta
            if (f_flag = 1){
            
                 /*
                    Procedemos a mostrar por pantalla la capacidad
                    Asientos ocupados y asientos libres
                    Y por último los asientos uno por uno
                 */
                 printf("\n /*Estado de la sala*/ \n\n\n");
                 printf("Capacidad: %d\n\n", capacidad());
                 printf("Asientos ocupados: %d      Asientos libres: %d\n\n", asientos_ocupados(), asientos_libres());
                 printf("Asientos por orden con sus respectivos ids: \n");
                 
                 //Bucle para mostrar asientos
                 for(int i = 0; i < capacidad();i++){
                      //Si ya se han escrito 12 asientos en una línea se provoca un salto de línea
                      // en el siguiente añadido de asiento
                      if(i%12 == 0 && i != 0){
                          
                          //Se comprueba si el asiento está libre
                          if(estado_asiento(i) == 0) {
                                printf("[-1]");
                                
                          //Si no lo está
                          }else{
                                printf("[%d]\n", estado_asiento(i));
                          }
                                
                      }else{
                          //Se comprueba si el asiento está libre
                          if(estado_asiento(i) == 0) {
                                printf("[-1]");
                                
                          //Si no lo está
                          }else{
                                printf("[%d]", estado_asiento(i));
                          }
                      
                      }
                      
                 }
                 //Espacio
                 printf("\n\n\n");
                 
                 //Liberamos espacio de memoria
                 free(nombre_orig);   
            }
        
        }
  }else{
       //Si el segundo elemento del comando no es ninguno de los anteriores se devuelve error
       lanza_error();
  }
  
  return 0;
  
  
  
}
