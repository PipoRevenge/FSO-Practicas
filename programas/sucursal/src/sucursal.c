#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
/*
Arreglar que imprime al iniciar el hijo no al terminar
Hacer control de errores para las entradas 
Mirar alguna forma de registrar PID con el nombre de la sala 
*/

#define MAX_INPUT_LENGTH 100
#define MAX_SALAS 100

struct dic_salas {
  char nombre[MAX_INPUT_LENGTH];
  pid_t pid;
};

struct dic_salas salas[MAX_SALAS]; // Variable global para dic_salas

int num_salas = 0; // Variable global para el número de salas


char* buscar_sala_por_pid(pid_t pid) {
  for (int i = 0; i < num_salas; i++) {
    if (salas[i].pid == pid) {
      return salas[i].nombre;
    }
  }
  return NULL; // Retorna NULL si no se encuentra el PID en el diccionario
}

// Función para manejar la señal SIGCHLD
// Función para manejar la señal SIGCHLD
void sigchld_handler(int signum) {
  int status;
  pid_t pid;

  // Esperar por cualquier hijo que haya terminado
  while ((pid = wait(&status)) > 0) {
    if (WIFEXITED(status)) {
      // Obtener el estado de salida del hijo (0 si todos los asientos ocupados, 1 si algunos asientos libres)
      int exit_status = WEXITSTATUS(status);

      // Encontrar el nombre de la sala correspondiente al PID
      char *nombre_sala = buscar_sala_por_pid(pid);
      if (nombre_sala != NULL) {
        //printf("La sala '%s' ha cerrado con estado de terminación: %d\n", nombre_sala, exit_status);
      }
    }
  }
}


void crea_sucursal(const char* ciudad, int capacidad) {
  char capacidad_str[10]; // Suponemos que la capacidad no superará los 10 dígitos
  snprintf(capacidad_str, sizeof(capacidad_str), "%d", capacidad);

  pid_t pid = fork(); // Crear un nuevo proceso hijo
  if (pid == 0) {
    // Estamos en el proceso hijo
    execl("/usr/bin/gnome-terminal", "gnome-terminal", "--title", ciudad, "--", "./programas/mini-shell/mini-shell.o", capacidad_str, NULL);

    perror("Error en exec"); // Esto solo se ejecutará si execl falla
    _exit(EXIT_FAILURE); // Salir del proceso hijo si execl falla
  } else if (pid < 0) {
    // Error al crear el proceso hijo
    perror("Error en fork");
  } else {
    // Estamos en el proceso padre
    strcpy(salas[num_salas].nombre, ciudad);
    salas[num_salas].pid = pid;
    num_salas++;
     


  }
}



int main() {
	    // Configurar el manejador de la señal SIGCHLD después de iniciar el proceso hijo
	        struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
      perror("Error al configurar el manejador de SIGCHLD");
      exit(EXIT_FAILURE);
    } 
  char nombresala[MAX_INPUT_LENGTH];
  int capacidad = 10;

   
  while (1) {
    printf("\nIngrese el nombre de la ciudad y la capacidad (o 'salir' para terminar): ");
    scanf("%s", nombresala);
    if (strcmp("salir", nombresala) == 0) {
      break;
    }
    scanf("%d", &capacidad);
    crea_sucursal(nombresala, capacidad);
  }

  // Imprimir el diccionario de salas y sus PIDs
  printf("\nDiccionario de salas:\n");
  for (int i = 0; i < num_salas; i++) {
    printf("Sala: %s, PID: %d\n", salas[i].nombre, salas[i].pid);
  }

  // Esperar por la terminación de todos los hijos antes de salir
  for (int i = 0; i < num_salas; i++) {
    waitpid(salas[i].pid, NULL, 0);
  }

  return 0;
}
