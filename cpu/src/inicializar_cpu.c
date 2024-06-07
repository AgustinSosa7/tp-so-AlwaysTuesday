#include "../includes/inicializar_cpu.h"


void inicializar_cpu(char* path){
    inicializar_logs();
    iniciar_config(path);
    imprimir_config();
    inicializar_estructuras();
}

void inicializar_logs(){
    cpu_logger = log_create("cpu.log","CPU_LOG",1,LOG_LEVEL_INFO);
    if (cpu_logger == NULL) {
	    perror("Algo raro pasa con el log. No se pudo crear o encontrar el archivo.");
	    exit(EXIT_FAILURE);
	}


    cpu_log_debug = log_create("cpu.log","CPU_LOG",1,LOG_LEVEL_INFO);
    if (cpu_log_debug == NULL) {
	    perror("Algo raro pasa con el log. No se pudo crear o encontrar el archivo.");
	    exit(EXIT_FAILURE);
	}

    log_info(cpu_log_debug, "Se inicializo el cpu debug logger"); //Sacar eventualmente

}

void iniciar_config(char* path){
    cpu_config = config_create(path);
    if (cpu_config == NULL) {
        perror("Error al intentar cargar el config.");
        exit(EXIT_FAILURE);
    }

    IP_MEMORIA = config_get_string_value(cpu_config,"IP_MEMORIA");
    IP_CPU = config_get_string_value(cpu_config, "IP_CPU"); 
    PUERTO_MEMORIA = config_get_string_value(cpu_config,"PUERTO_MEMORIA");
    PUERTO_ESCUCHA_DISPATCH = config_get_string_value(cpu_config,"PUERTO_ESCUCHA_DISPATCH");
    PUERTO_ESCUCHA_INTERRUPT = config_get_string_value(cpu_config,"PUERTO_ESCUCHA_INTERRUPT");
    CANTIDAD_ENTRADAS_TLB = config_get_int_value(cpu_config,"CANTIDAD_ENTRADAS_TLB");
    ALGORITMO_TLB = config_get_string_value(cpu_config,"ALGORITMO_TLB");    

}

void imprimir_config(){
    log_info(cpu_logger, "IP_MEMORIA: %s", IP_MEMORIA);
    log_warning(cpu_log_debug, "PUERTO_MEMORIA: %s", PUERTO_MEMORIA);
    log_debug(cpu_log_debug, "PUERTO_ESCUCHA_DISPATCH: %s", PUERTO_ESCUCHA_DISPATCH);
    log_trace(cpu_log_debug,"PUERTO_ESCUCHA_INTERRUPT: %s", PUERTO_ESCUCHA_INTERRUPT);
}

void inicializar_estructuras(){
    contexto_ejecucion = malloc(sizeof(t_contexto_ejecucion*));
    contexto_ejecucion->registros_cpu = malloc(sizeof(t_registros_cpu*));
}