#ifndef M_GESTOR_H_
#define M_GESTOR_H_

#include <stdio.h>
#include <stdlib.h>

#include <../src/utils/utils_connections.h>

#include <commons/log.h>
#include <commons/config.h>
#include <commons/collections/list.h>
#include <commons/txt.h>

//Estructuras
typedef struct
{
	int pid;
	char* direccion_pseudocodigo;
	t_list* instrucciones;
} t_proceso;


typedef struct
{
	int pid;
	int pc;
} t_pedido;

//Variables GLOBALES

extern t_log* memoria_logger;
extern t_log* memoria_log_debug;
extern t_config* memoria_config;

extern t_list* procesos_memoria;

extern char* IP_MEMORIA;
extern char* PUERTO_ESCUCHA;
extern char* IP_FILESYSTEM;
extern char* PUERTO_FILESYSTEM;
extern int TAM_MEMORIA;
extern int TAM_PAGINA;
extern char* PATH_INSTRUCCIONES;
extern int RETARDO_RESPUESTA;
extern char* ALGORITMO_REEMPLAZO;

extern int fd_memoria;
extern int fd_entradasalida;
extern int fd_cpu;             
extern int fd_kernel;

extern char* server_name;


#endif /*M_GESTOR_H_*/

