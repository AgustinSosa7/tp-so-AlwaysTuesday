#include "../includes/planificador_largo_plazo.h"



void planif_largo_plazo(){
   while(1){
      detener_planificacion();
      sem_wait(&sem_new_a_ready);
 	    sem_wait(&sem_grado_multiprogram);
      if(!list_is_empty(lista_new)){
      cambiar_de_estado_y_de_lista(NEW, READY);
      sem_post(&sem_planificador_corto_plazo);
         }
      }
   }
