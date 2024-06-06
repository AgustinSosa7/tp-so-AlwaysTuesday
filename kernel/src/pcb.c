#include "../includes/pcb.h"


t_pcb* crearPcb(){
	t_pcb* pcb = malloc(sizeof(t_pcb*));
	pcb->pid = asignarPID();
    pcb->quantum = QUANTUM;
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

void cambiar_estado(t_pcb* un_pcb, estado_pcb nuevo_estado){
    estado_pcb estado_anterior = un_pcb->estado_pcb;
	un_pcb->estado_pcb = nuevo_estado;

    log_info(kernel_logger, "PID: <%d> - Estado Anterior: <%s> - Estado Actual: <%s>",un_pcb->pid, enum_a_string(estado_anterior),enum_a_string(nuevo_estado));

	switch(nuevo_estado)
    {
    case NEW:
        queue_push(cola_new,un_pcb);
        break;
    case READY:
        queue_push(cola_ready,un_pcb);
        //log info(Ingreso a Ready: “Cola Ready <COLA>: [<LISTA DE PIDS>]”)

        break;
    case EXEC:
        list_add(lista_exec,un_pcb);
        break;
    case EXIT:
        queue_push(cola_exit,un_pcb);
        break;
    case READYPLUS:
        queue_push(cola_ready_plus,un_pcb);
        break;    
    default:
        break;
    }
    
}

void inicializar_registros(t_pcb* un_pcb){
	un_pcb->registros_cpu->PC= 0;
    un_pcb->registros_cpu->AX= 0;
    un_pcb->registros_cpu->BX= 0;
    un_pcb->registros_cpu->CX= 0;
    un_pcb->registros_cpu->DX= 0;
    un_pcb->registros_cpu->EAX= 0;
    un_pcb->registros_cpu->EBX= 0;
    un_pcb->registros_cpu->ECX= 0;
    un_pcb->registros_cpu->EDX= 0;
    un_pcb->registros_cpu->SI= 0;
    un_pcb->registros_cpu->DI= 0;
}

