#include "../includes/cpu.h"


int main(int argc, char** argv){

   if(validar_parametros_incorrectos_main(argc, 2, argv)){
        return EXIT_FAILURE;
    }
    
    // Inicializar CPU
    inicializar_cpu(argv[1]);
    
    //ESTO ME SIRVE PARA VER COMO FUNCIONAN LOS CASTEOS:
    /*
    char * a = "256";
    int i = atoi(a);
    u_int8_t ax = 0;
    u_int32_t eax = 0;
    printf("El valor de i es %d, el valor de AX es %d, el valor de EAX es %d y el valor de a es %d \n", i, ax, eax, a);
    ax = i;
    eax = i;
    printf("El valor de i es %d, el valor de AX es %d, el valor de EAX es %d y el valor de a es %d \n", i, ax, eax, a);
    
    u_int8_t ax = 200;
    int bx = 50;
    u_int8_t cx = 0;
    printf("El valor de AX es %d, el valor de BX es %d y el valor de CX es %d \n", ax, bx, cx);
    cx = ax+bx;
    printf("El valor de AX es %d, el valor de BX es %d y el valor de CX es %d \n", ax, bx, cx);
    */

    // Conectarnos como cliente a MEMORIA
    log_info(cpu_logger, "Creando conexion con MEMORIA...");
    fd_memoria = crear_conexion(IP_MEMORIA, PUERTO_MEMORIA, cpu_logger);  
    gestionar_handshake_como_cliente(fd_memoria, "MEMORIA", cpu_logger);    
    
    // Pedimos el Tamaño de las Páginas y de la Memoria
    pedir_info_inicial_a_memoria();

    // Iniciar server de CPU - DISPATCH
    pthread_t hilo_conexion_dispatch;
    pthread_create(&hilo_conexion_dispatch, NULL, (void*)conexion_cpu_kernel_dispatch, NULL);
    pthread_detach(hilo_conexion_dispatch); 

    // Iniciar server de CPU - INTERRUPT
    pthread_t hilo_conexion_interrupt;
    pthread_create(&hilo_conexion_interrupt, NULL, (void*)conexion_cpu_kernel_interrupt, NULL);
    pthread_join(hilo_conexion_interrupt, NULL);

    // Atender los mensajes de Kernel - Dispatch
    pthread_t hilo_kernel_dispatch;
    pthread_create(&hilo_kernel_dispatch, NULL, (void*)atender_dispatch, NULL);
    pthread_detach(hilo_kernel_dispatch);    

    // Atender los mensajes de Kernel - Interrupt
    pthread_t hilo_kernel_interrupt;
    pthread_create(&hilo_kernel_interrupt, NULL, (void*)atender_interrupt, NULL);
    pthread_detach(hilo_kernel_interrupt);

    // Método principal
    pthread_t hilo_ciclo_instruccion;
    pthread_create(&hilo_ciclo_instruccion, NULL, (void*)ciclo_instruccion, NULL);
    pthread_join(hilo_ciclo_instruccion,NULL);

    return EXIT_SUCCESS;
}

void conexion_cpu_kernel_dispatch(){
    fd_cpu_dispatch = iniciar_servidor(PUERTO_ESCUCHA_DISPATCH, cpu_logger, IP_CPU);
    log_info(cpu_logger, "Esperando a DISPATCH...");
    fd_kernel_dispatch = esperar_cliente(fd_cpu_dispatch, cpu_logger, "KERNEL-DISPATCH");
    gestionar_handshake_como_server(fd_kernel_dispatch, cpu_logger, "KERNEL-DISPATCH");
}

void conexion_cpu_kernel_interrupt(){
    fd_cpu_interrupt= iniciar_servidor(PUERTO_ESCUCHA_INTERRUPT, cpu_logger, IP_CPU);
    log_info(cpu_logger, "Esperando a INTERRUPT...");
    fd_kernel_interrupt = esperar_cliente(fd_cpu_interrupt, cpu_logger, "KERNEL-INTERRUPT");
    gestionar_handshake_como_server(fd_kernel_interrupt, cpu_logger, "KERNEL-INTERRUPT");
}  