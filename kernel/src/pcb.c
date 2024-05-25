#include "../includes/pcb.h"
#include <../src/utils/utils_connections.h>


#include <semaphore.h>
void _enviar_pcb_a_CPU_por_dispatch(t_pcb* un_pcb){
	t_paquete* un_paquete = crear_paquete(EJECUTAR_PROCESO_KC); //Ejecutar, ver si tiene ese nombre;
	agregar_algo_a_paquete(un_paquete, un_pcb->pid);
    agregar_algo_a_paquete(un_paquete, un_pcb->program_counter);
    agregar_algo_a_paquete(un_paquete, un_pcb->quantum);
    agregar_registro_a_paquete(un_paquete, un_pcb->registros_cpu);
	enviar_paquete(un_paquete, fd_cpu_dispatch);
	eliminar_paquete(un_paquete);
} 



t_pcb* crearPcb(){
	t_pcb* pcb = malloc(sizeof(t_pcb*));
	pcb->pid = asignarPID();
    pcb->program_counter = 0;
    pcb->quantum= QUANTUM;
    pcb->registros_cpu = malloc(sizeof(t_registros_cpu*));
	inicializar_registros(pcb);
    pcb->estado_pcb = NEW;
	return pcb;
}
//deberia poner una variable global PID=0
int asignarPID(){
	int a;
	//pthread_mutex_lock(mutex_pid); ARREGLAR SEMAFORO
	pid_global ++;
	a = pid_global;
	//pthread_mutex_unlock(mutex_pid); ARREGLAR SEMAFORO
	return a;
}

void cambiar_estado(t_pcb* un_pcb, estado_pcb* nuevo_estado){
	un_pcb->estado_pcb = nuevo_estado;
}

void inicializar_registros(t_pcb* un_pcb){
	un_pcb->registros_cpu->AX= 0;
}