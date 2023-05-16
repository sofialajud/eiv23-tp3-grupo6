#ifndef SOPORTE_PLACA_H
#define SOPORTE_PLACA_H 

#include <stdbool.h>
#include <stdint.h>

//Declaraciones
//Espacios de nombres: SP_

/**
 * @brief Handles correspondientes a los pines de entrada/salida, para 
 * usar en el parámetro hPin (primer parámetro) de las funciones SP_Pin_xxx
 * 
 */

enum SP_Pines{
    SP_PB9,
    SP_PC13,
    SP_P_LED = SP_PC13,
    SP_HPIN_LIMITE
};

/**
 * @brief Handle que representa un objeto Pin.
 * Toma valores de las constante SP_Pines 
 */
typedef int SP_HPin;

/**
 * @brief Definición de modo de operación de un Pin
 * 
 */
typedef enum SP_Pin_Modo{
    SP_PIN_ENTRADA,           // Entrada flotante
    SP_PIN_ENTRADA_PULLUP,    // Entrada con resistencia pull-up interna
    SP_PIN_ENTRADA_PULLON,    // Entrada con resistencia pull-down interna
    SP_PIN_SALIDA,            // Salida push-pull
    SP_PIN_SALIDA_OPEN_DRAIN, // Salida con drenador abierto
}SP_Pin_Modo;

/**
 * @brief Configura el modo de un pin
 * 
 * @param hpin Handle al objeto Pin
 * @param modo Modo a configurar
 */
void SP_Pin_setModo(SP_HPin hpin, SP_Pin_Modo modo);

/**
 * @brief Lee el buffer de enrada de un Pin
 * 
 * @param hpin Handle al objeto Pin
 * @return true   Entrada ALTA
 * @return false  Entrada BAJA
 */
bool SP_Pin_read(SP_HPin hpin);

/**
 * @brief Escribe el buffer de salida de un Pin
 * 
 * @param hpin  Handle al objeto Pin
 * @param valor 
 * @return true : Salida ALTA
 * @return false: Salida BAJA 
 */
void SP_Pin_write(SP_HPin hpin, bool valor);

/**
 * @brief Inicializa la librería. Es necesario llamar a
 * esta función antes de usar la misma.
 * 
 */
void SP_init(void);

/**
 * @brief Retardo con bloqueo durante un tiempo dado en milisegundos
 * @note Llamar a SP_init antes de usar.
 * @param tiempo Tiempo en milisegundos
 */
void SP_delay(uint32_t tiempo);

typedef void (*SP_TimeoutHandler)(void *param);

/**
 * @brief Llama a la función handler desde la rutina de servicio
 * de interrupción de SysTick luego de pasado el tiempo en milisegundos,
 * con el parámetro especificado.
 * 
 * @param tiempo Tiempo en milisegundos
 * @param handler Puntero a función handler
 * @param param Parámetro a pasar como argumento de la función handler (puntero void)
 * @return true Timeout programado
 * @return false Recursos insuficientes
 */
bool SP_Timeout(uint32_t tiempo,SP_TimeoutHandler handler,void *param);

#endif