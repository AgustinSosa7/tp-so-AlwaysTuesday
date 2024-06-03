#ifndef ENTRADASALIDA_H_
#define ENTRADASALIDA_H_

#include "es_gestor.h"
#include "inicializar_entradasalida.h"
#include "entradasalida_kernel.h"

#include <../src/utils/utils_connections.h>


// Variables GLOBALES

t_log* entradasalida_logger;
t_log* entradasalida_log_debug;
t_config* entradasalida_config;

int fd_entradasalida;  
int fd_memoria;
int fd_kernel;      

char* NOMBRE_INTERFAZ;
char* PUERTO_ESCUCHA;    
char* TIPO_INTERFAZ;
t_list* INSTRUCCIONES_POSIBLES;
int TIEMPO_UNIDAD_TRABAJO; 
char* IP_KERNEL;
char* PUERTO_KERNEL;
char* IP_MEMORIA;
char* PUERTO_MEMORIA;
char* PATH_BASE_DIALFS;
int BLOCK_SIZE;
int BLOCK_COUNT;
int RETRASO_COMPACTACION;
#endif
