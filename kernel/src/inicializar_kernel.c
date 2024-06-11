#include <../includes/inicializar_kernel.h>

void inicializar_kernel(char* path){
    inicializar_logs();
    inicializar_configs(path);
	inicializar_listas();
	inicializar_semaforos();
	inicializar_pid();
}

void inicializar_logs(void){

kernel_logger = log_create("kernel.log","KERNEL_LOG",1,LOG_LEVEL_INFO);

if (kernel_logger == NULL) {
	perror("Algo raro pasa con el log. No se pudo crear o encontrar el archivo.");
	exit(EXIT_FAILURE);
    }

log_info(kernel_logger, "Se inicializo el kernel logger"); //Sacar eventualmente


kernel_log_debug = log_create("kernel_debug.log","KERNEL_DEBUG_LOG",1,LOG_LEVEL_INFO);
if (kernel_log_debug == NULL) {
	perror("Algo raro pasa con el log. No se pudo crear o encontrar el archivo.");
	exit(EXIT_FAILURE);
   }

log_info(kernel_log_debug, "Se inicializo el kernel debug logger"); //Sacar eventualmente

}    
    
void inicializar_configs(char* path) {

	kernel_config = config_create(path);
	if (kernel_config == NULL) {
		perror("Error al intentar cargar el config.");
		exit(EXIT_FAILURE);
    } 

PUERTO_ESCUCHA = config_get_string_value(kernel_config,"PUERTO_ESCUCHA");
IP_MEMORIA = config_get_string_value(kernel_config,"IP_MEMORIA");
IP_KERNEL = config_get_string_value(kernel_config,"IP_MEMORIA");
PUERTO_MEMORIA = config_get_string_value(kernel_config,"PUERTO_MEMORIA");
IP_CPU = config_get_string_value(kernel_config,"IP_CPU");
PUERTO_CPU_DISPATCH= config_get_string_value(kernel_config,"PUERTO_CPU_DISPATCH");
PUERTO_CPU_INTERRUPT = config_get_string_value(kernel_config,"PUERTO_CPU_INTERRUPT");
ALGORITMO_PLANIFICACION = config_get_string_value(kernel_config,"ALGORITMO_PLANIFICACION");
QUANTUM = config_get_int_value(kernel_config,"QUANTUM");
RECURSOS = config_get_array_value(kernel_config, "RECURSOS"); // REVISAR POR FAVOR EL TIPO DE DATO QUE SE MANEJA (kernel.h)
INSTANCIAS_RECURSOS = config_get_array_value(kernel_config, "INSTANCIAS_RECURSOS"); // REVISAR POR FAVOR EL TIPO DE DATO QUE SE MANEJA (kernel.h)
GRADO_MULTIPROGRAMACION = config_get_int_value(kernel_config,"GRADO_MULTIPROGRAMACION");

log_info(kernel_log_debug, "Se inicializan las configs..."); //Sacar eventualmente

log_info(kernel_log_debug, "PUERTO_ESCUCHA: %s", PUERTO_ESCUCHA); //Sacar eventualmente
log_info(kernel_log_debug, "IP_MEMORIA: %s", IP_MEMORIA); //Sacar eventualmente
log_info(kernel_log_debug, "PUERTO_MEMORIA: %s", PUERTO_MEMORIA); //Sacar eventualmente
log_info(kernel_log_debug, "IP_CPU: %s", IP_CPU); //Sacar eventualmente
log_info(kernel_log_debug, "PUERTO_CPU_DISPATCH: %s", PUERTO_CPU_DISPATCH); //Sacar eventualmente
log_info(kernel_log_debug, "PUERTO_CPU_INTERRUPT: %s", PUERTO_CPU_INTERRUPT); //Sacar eventualmente
//log_info(kernel_log_debug, "ALGORITMO_PLANIFICACION: %s", ALGORITMO_PLANIFICACION); //Sacar eventualmente
//log_info(kernel_log_debug, "QUANTUM: %d", QUANTUM); //Sacar eventualmente
//log_info(kernel_log_debug, "Falta RECURSOS:" %d); //Sacar eventualmente
//log_info(kernel_log_debug, "Falta INSTANCIAS_RECURSOS: %d", INSTANCIAS_RECURSOS); //Sacar eventualmente
//log_info(kernel_log_debug, "GRADO_MULTIPROGRAMACION: %d", GRADO_MULTIPROGRAMACION); //Sacar eventualmente

log_info(kernel_log_debug, "Se inicializaron las configs"); //Sacar eventualmente

}

void inicializar_listas(void){
	lista_new = list_create();
	lista_ready = list_create();
	lista_ready_plus = list_create();
	lista_exec = list_create();
	lista_exit = list_create();
	inicializar_listas_instrucciones();
}

void inicializar_listas_instrucciones(){
	INSTRUCCIONES_GEN = list_create();
	INSTRUCCIONES_STDIN = list_create();
	INSTRUCCIONES_STDOUT = list_create();
	INSTRUCCIONES_FS = list_create();
	list_add(INSTRUCCIONES_GEN, "IO_GEN_SLEEP");
	list_add(INSTRUCCIONES_STDIN, "IO_STDIN_READ");
	list_add(INSTRUCCIONES_STDOUT, "IO_STDOUT_WRITE");
	list_add(INSTRUCCIONES_FS, "IO_FS_CREATE");
	list_add(INSTRUCCIONES_FS, "IO_FS_DELETE");
	list_add(INSTRUCCIONES_FS, "IO_FS_TRUNCATE");
	list_add(INSTRUCCIONES_FS, "IO_FS_WRITE");
	list_add(INSTRUCCIONES_FS, "IO_FS_READ");
}

void inicializar_semaforos(){
	printf("arrancando sems...\n");
	
	sem_init(&sem_grado_multiprogram,0,GRADO_MULTIPROGRAMACION);
	printf("listo las GRADO_MULTIPROGRAMACION\n");
	sem_init(&sem_new_a_ready,0,0);
	sem_init(&sem_planificador_corto_plazo,0,0);
	printf("listo las sem_planificador_corto_plazo\n");

	
	pthread_mutex_init(&mutex_pid, NULL);
	printf("listo las mutex_pid\n");
	pthread_mutex_init(&mutex_io, NULL);
	pthread_mutex_init(&mutex_new, NULL);
	pthread_mutex_init(&mutex_ready, NULL);
	pthread_mutex_init(&mutex_exec, NULL);
	pthread_mutex_init(&mutex_ready_plus, NULL);
	pthread_mutex_init(&mutex_exit, NULL);
	printf("listo las mutex_exit\n");
}

void inicializar_pid(){
	pid_global = 0;
	} 