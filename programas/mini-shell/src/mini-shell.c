#include "sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100
/*
Hacer control de errores 
Hacer bien las funciones 
Describirlas 
Hacer test
*/
void reserva_terminal(int id_persona) {
    printf("Reservando asiento para la persona con ID: %d\n", id_persona);
    reserva_asiento(id_persona);
}

void libera_terminal(int id_persona) {
    printf("Liberando asiento para la persona con ID: %d\n", id_persona);
    libera_asiento(id_persona);
}

void estado_asiento_terminal(int id_asiento) {
    printf("Obteniendo estado del asiento con ID: %d\n", id_asiento);
    int estado = estado_asiento(id_asiento);
    if (estado > 0) {
        printf("El asiento está ocupado por la persona con ID: %d\n", estado);
    } else if (estado == 0) {
        printf("El asiento está libre\n");
    }
}

void estado_sala_terminal() {
    printf("Obteniendo estado de la sala\n");
    printf("Capacidad de la sala: %d\n", capacidad_sala());
    printf("Asientos ocupados: %d\n", asientos_ocupados());
    printf("Asientos libres: %d\n", asientos_libres());
}

void cerrar_sala_terminal() {
    printf("Cerrando la sala y finalizando el proceso\n");
    elimina_sala();
    exit(0);
}

void mostrar_ayuda() {
    printf("Uso:\n");
    printf("  reserva <id_persona>    : Reservar asiento para la persona con ID especificado\n");
    printf("  libera <id_persona>     : Liberar asiento ocupado por la persona con ID especificado\n");
    printf("  estado_asiento <id_asiento> : Obtener estado del asiento con ID especificado\n");
    printf("  estado_sala             : Obtener estado de la sala\n");
    printf("  cerrar_sala             : Cerrar la sala y finalizar el proceso\n");
    printf("  help                    : Mostrar esta ayuda\n");
}

void parse_command(char *command, char *action, int *argument) {
    char *token = strtok(command, " ");
    if (token != NULL) {
        strcpy(action, token);
        token = strtok(NULL, " ");
        if (token != NULL) {
            *argument = atoi(token);
        } else {
            *argument = -1; // Valor por defecto para argumentos no especificados
        }
    } else {
        strcpy(action, "");
        *argument = -1; // Valor por defecto para comandos no especificados
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s <capacidad>\n", argv[0]);
        return 1;
    }

    int capacidad = atoi(argv[1]);
    crea_sala(capacidad);

    char input[MAX_INPUT_LENGTH];
    char action[MAX_INPUT_LENGTH];
    int argument;

    // Bucle infinito para el mini-shell interactivo
    while (1) {
        printf("Ingrese su comando: ");
        fgets(input, MAX_INPUT_LENGTH, stdin);
        input[strcspn(input, "\n")] = '\0'; // Eliminar el salto de línea del final

        // Parsear el comando
        parse_command(input, action, &argument);

        // Ejecutar la acción correspondiente utilizando switch
        if (strcmp(action, "help") == 0) {
            mostrar_ayuda();
        } else {
            if (strcmp(action, "reserva") == 0) {
                if (argument != -1) {
                    reserva_terminal(argument);
                } else {
                    printf("Error: ID de persona no especificado\n");
                }
            } else if (strcmp(action, "libera") == 0) {
                if (argument != -1) {
                    libera_terminal(argument);
                } else {
                    printf("Error: ID de persona no especificado\n");
                }
            } else if (strcmp(action, "estado_asiento") == 0) {
                if (argument != -1) {
                    estado_asiento_terminal(argument);
                } else {
                    printf("Error: ID de asiento no especificado\n");
                }
            } else if (strcmp(action, "estado_sala") == 0) {
                estado_sala_terminal();
            } else if (strcmp(action, "cerrar_sala") == 0) {
                cerrar_sala_terminal();
            } else {
                printf("Error: Comando no reconocido\n");
            }
        }
    }

    return 0;
}

