#include <soporte_placa.h>
#include "controlador_luz.h"
#include <pulsador.h>
#include <despacho_retardado.h>
#include <stddef.h>
#include "mi_maquina.h"

#define PIN_LUZ SP_PC13
#define PIN_PULSADOR SP_PB9

#define HISTERESIS_ANTIRREBOTE 5

#define LUZ_ON 0

#define PULSADOR_NIVEL_ACTIVO 0

#define TIEMPO_ON 60000


static Maquina * controlador;
static Pulsador pulsador[1];
static DespachoRetardado despachoRetardado[1];
static Maquina * mimaquina;

/**
 * @brief Inicializa el estado del programa para iniciar la ejecución
 * 
 */
static void setup(void);


int main(void){    
    setup();
    for (;;){
        Maquina_procesa(controlador);
        DespachoRetardado_procesa(despachoRetardado);
        Pulsador_procesa(pulsador);
        Maquina_procesa(mimaquina);
    }
    return 0;
}



static void setup(void){
    static ControladorLuz instanciaControlador;
    static MiMaquina instanciaMiMaquina;
    
    SP_init();
    
    DespachoRetardado_init(despachoRetardado);

    ControladorLuz_init(&instanciaControlador,TIEMPO_ON,PIN_LUZ,LUZ_ON,despachoRetardado);  
    controlador = ControladorLuz_asMaquina(&instanciaControlador);
    Maquina_procesa(controlador); // Reset inicializa pin con luz apada

    MiMaquina_init(&instanciaMiMaquina, controlador, despachoRetardado);
    mimaquina = MiMaquina_asMaquina(&instanciaMiMaquina);
    Maquina_procesa(mimaquina);

    Pulsador_init(pulsador, 
                  controlador,
                  EV_BOTON_PULSADO,
                  PIN_PULSADOR,
                  PULSADOR_NIVEL_ACTIVO,
                  HISTERESIS_ANTIRREBOTE);
}
// VERSION CON ABSTRACCIÓN
// #include <soporte_placa.h>
// 
// #define LUZ_ON 0
// #define LUZ_OFF 1
// #define PULSADOR_ACTIVO 0
// #define PULSADOR_NORMAL 1
// 
// 
// int main(void){
//     SP_init();
//     SP_Pin_setModo(SP_PB9,SP_PIN_ENTRADA_PULLUP);
//     SP_Pin_setModo(SP_P_LED,SP_PIN_SALIDA);
//     SP_Pin_write(SP_P_LED,LUZ_OFF);
//     for (;;){
//         while(SP_Pin_read(SP_PB9) != PULSADOR_ACTIVO);
//         SP_Pin_write(SP_P_LED,LUZ_ON);
//         SP_delay(60000);
//         SP_Pin_write(SP_P_LED,LUZ_OFF);
//     }
//     return 0;
// }

//   VERSIÓN CON FUERZA BRUTA
//  #include <stm32f1xx.h>
//  
//  #define LUZ_ON 0           
//  #define LUZ_OFF 1           
//  #define PULSADOR_ACTIVO 0  
//  #define PULSADOR_NORMAL 1  
//  
//  int main(void){ 
//          RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN; // Máscara para encender los puertos B y C 
//  
//      // B9 pulsador, con resistencia pull hacia el nivel normal
//      GPIOB->BSRR = 1 << (9+((PULSADOR_NORMAL)? 0:16)); /*Evalúa la expresión que está a la izquierda de "?" si es verdadero el resultado de la expresión
//                                                        es lo que está a la izquierda de ":" si es falso lo que está a la derecha.
//                                                        BSRR registro que tiene dos partes de 16 bit, la primera es la parte de BIT SET, la segunda es la de BIT RESET
//                                                        Aquí si pulsador normal es verdadero o distinto de 0 escribe un 1 en la posición 9+0 osea 9 (lo pone en 1)
//                                                        si pulsador normal es 0 escribe un 1 en la posición 9+16=25, el 9 de la segunda parte (lo pone en 0)*/ 
//      GPIOB->CRH =   (GPIOB->CRH & ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9)) /* Lee el registro CRH (donde está la configuración del pin 9). 
//                                                                      Modifica en dos partes: 1) Puesta a cero: pone a 0 los bits de configuración del pin 9*/
//                      | GPIO_CRH_CNF9_1;                           //         2) BIT SET: pone a 1 solo los bits de configuración que se suponen que estén a 1
//      
//      // C13 luz, inicialmente apagada
//      GPIOC->BSRR = 1 << (13+((LUZ_OFF)? 0:16));        // Si LUZ_OFF es: distinto de 0 escribe un 1 en la posición 13 (lo pone en 1), 0 escribe un 1 en la posición 13 de la segunda parte (lo pone en 0)
//      GPIOC->CRH =   (GPIOC->CRH & ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13)) // Lee, puesta a cero
//                      | GPIO_CRH_MODE13_1;                              // Set a 1
//                      
//      for(;;){ // Lazo principal infinito
//          while((GPIOB->IDR & (1<<9)) != (PULSADOR_ACTIVO << 9)); /* Lee el registro IDR (de entrada) y aplica una máscara  donde está en 1 el bit 9 se compara con
//                                                                  PULSADOR_ACTIVO  desplazado 9 lugares*/ 
//          GPIOC->BSRR = 1 << (13+((LUZ_ON)? 0:16)); //Encender la luz
//          for(int j=0;j<60000;++j){ //Retardo por fuerza bruta
//              for(int volatile i=0;i<(8000000/(1000*13));++i); //Calibro para que sea de 1 milisegundo, Calificar como volatile para que el compilador no lo elimine
//          }
//          GPIOC->BSRR = 1 << (13+((LUZ_OFF)? 0:16)); //Apago la luz
//      }
//      return 0;
//  }