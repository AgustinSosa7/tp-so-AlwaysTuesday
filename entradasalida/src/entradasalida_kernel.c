#include "../includes/entradasalida_kernel.h"


void atender_entradasalida_kernel(){
    bool control_key = 1;
    while (control_key) {
        int cod_op = recibir_operacion(fd_kernel);
        t_paquete* paquete = recibir_paquete(fd_kernel);
	  log_info(entradasalida_logger, "Se recibio algo de Kernel..");

        switch (cod_op)
        {
        case ATENDER_PETICION_INTERFAZ_KERNEL:
            t_peticion* peticion = recibir_peticion(paquete); //Ya tengo en peticion todos los datos que necesito.
            procesar_peticion(peticion->instruccion, peticion->parametros);
            free(peticion);
            finalizar_peticion(fd_kernel);
            break;
        case RECONOCER_INSTRUCCION:
            char* instruccion = recibir_instruccion(paquete);
            validar_tipo_instruccion(instruccion);    
            break;
        case -1:
          //  log_error(logger, "Desconexion de CPU - DISPATCH");      
            control_key = 0;
        default:
           // log_warning(logger, "Operacion desconocida de CPU - DISPATCH");
            break;
        }
        eliminar_paquete(paquete);
    }
}

t_peticion* recibir_peticion(t_paquete* paquete){
    t_peticion* peticion = malloc(sizeof(t_peticion));

    leer_string_del_paquete(paquete, &peticion->instruccion);
    leer_del_paquete(paquete, (void**)&peticion->parametros->tiempo_espera, sizeof(int));

    return peticion;
} 

void procesar_peticion(char* instruccion, t_peticion_param* parametros) {
      
      if(strcmp(instruccion,"IO_GEN_SLEEP") == 0){
            int tiempo_espera = TIEMPO_UNIDAD_TRABAJO * parametros->tiempo_espera;
            sleep(tiempo_espera);
      }else if (strcmp(instruccion,"IO_STDIN_READ") == 0)
      {
            /* code */
      }else if (strcmp(instruccion,"IO_STDOUT_WRITE") == 0)
      {
            /* code */
      }else if (strcmp(instruccion,"IO_FS_CREATE") == 0)
      {
            /* code */
      }else if (strcmp(instruccion,"IO_FS_DELETE") == 0)
      {
            /* code */
      }else if (strcmp(instruccion,"IO_FS_TRUNCATE") == 0)
      {
            /* code */
      }else if (strcmp(instruccion,"IO_FS_WRITE") == 0)
      {
            /* code */
      }else //la instruccion que llego fue IO_FS_READ
      {
            /* code */
      }
}      

char* recibir_instruccion(t_paquete* paquete){
      char* instruccion;
      leer_string_del_paquete(paquete, &instruccion);
      return instruccion;
}

void validar_tipo_instruccion(char* instruccion){
      if(list_any_satisfy(INSTRUCCIONES_POSIBLES, (void*)la_instruccion_esta_en_la_lista)){
            void* coso_a_enviar = malloc(sizeof(bool));
	      bool saludar = true;
	      memcpy(coso_a_enviar, &saludar, sizeof(int));
	      send(fd_kernel, coso_a_enviar, sizeof(int),0);
	      free(coso_a_enviar);
      }else{
            void* coso_a_enviar = malloc(sizeof(bool));
	      bool saludar = true;
	      memcpy(coso_a_enviar, &saludar, sizeof(int));
	      send(fd_kernel, coso_a_enviar, sizeof(int),0);
	      free(coso_a_enviar);
            }
}

bool la_instruccion_esta_en_la_lista(char* instruccion_posible, char* instruccion){
      if(strcmp(instruccion_posible,instruccion)==0){
            return true;
      }else{return false;}
}

void finalizar_peticion(){
      send(fd_kernel, true, sizeof(bool), 0);
}