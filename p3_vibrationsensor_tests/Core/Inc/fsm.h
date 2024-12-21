
#ifndef FSM_H //Si no está definido el header, se define el header

#define FSM_H



typedef struct fsm_t fsm_t; //Definir una estructura de tipo fsm_t con nombre fsm_t.



typedef int (*fsm_input_func_t) (fsm_t*); 
//Declaro un puntero a una función fsm_input_func_t que toma como argumento un puntero a un dato fsm_t. 
//Esta función fsm_input_func_t será la función que se ejecuta al llegar a un estado (entradas de la fsm). 

typedef void (*fsm_output_func_t) (fsm_t*);
//Igual. Esta será la función de salida de un estado (lo que pasa en una transición, o las salidas de la fsm).


typedef struct fsm_trans_t { //Creo otra estructura fsm_trans_t que contiene todos los datos de una transición. 

  int orig_state; 

  fsm_input_func_t in;

  int dest_state;

  fsm_output_func_t out;

} fsm_trans_t;



struct fsm_t { //Aquí desarrollo la estructura fsm_t antes declarada, con un estado actual y un puntero a la transición

  int current_state;

  fsm_trans_t* tt;

};



fsm_t* fsm_new (fsm_trans_t* tt); //Función de creado de una nueva FSM. Devuelve puntero a fsm_t, toma argumento de transición. 

void fsm_init (fsm_t* this, fsm_trans_t* tt); //Inicia la máquina de estados con un estado y una transición. 

void fsm_fire (fsm_t* this); //Dispara la máquina de estados. 



#endif