#include <unity.h>
#include <soporte_placa.h>
#include <stm32f1xx.h>


void setUp(void){// Preparación común a todas las pruebas: resetear el puerto B 
    __disable_irq();
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;   // Activa el reloj del puerto B
    RCC->APB2RSTR = RCC_APB2RSTR_IOPBRST; // Resetea el puerto
    RCC->APB2RSTR = 0;                    // Colocar en 0 el registro del rst
    RCC->APB2ENR &= ~RCC_APB2ENR_IOPBEN;  // Desactiva el reloj del puerto B
    __enable_irq();
}

void tearDown(void){

} 

/*La manera de nombrar las funciones para las pruebas es:test_NOMBRE__DEBE_hacer...
  Al definirlas antes de main quedan tambien declaradas
  Definirlas static para que muetre advertencias si no se las usa
  La manera de formularlas es:
    1) Preparar el Entorno
    2) Ejecutar una función
    3) Fijarse los resultados que devuelve
    LAS PRUEBAS LAS HAREMOS EN EL PIN B6*/
//static void test_SP_Pin_setModo_ENTRADA_FLOTANTE__DEBE_configurar_pin_como_ENTRADA_FLOTANTE(void){
//    uint32_t OFFSET = 4U;                               //Offset de configuración pin 9
//    uint32_t MASK_PIN9_MODO = (0xF << OFFSET);          //Máscara para los bits de CRH del pin 9
//    uint32_t MODO_ESPERADO = 0b0100;   
//
//    SP_Pin_setModo(SP_PB9,SP_PIN_SALIDA);
//    uint32_t CRL_ANTERIOR = GPIOB->CRL;                    
//    uint32_t CRH_ANTERIOR = GPIOB->CRH;
//    uint32_t ODR_ANTERIOR = GPIOB->ODR;
//
//    SP_Pin_setModo(SP_PB9,SP_PIN_ENTRADA);
//    uint32_t CRL_ACTUAL = GPIOB->CRL;                  
//    uint32_t CRH_ACTUAL = GPIOB->CRH;
//    uint32_t ODR_ACTUAL = GPIOB->ODR;
//    uint32_t DELTA_CRL = CRL_ANTERIOR ^ CRL_ACTUAL;       //Guardan en 1 los bits que se cambiaron y en 0 los que no se cambiaron
//    uint32_t DELTA_CRH = CRH_ANTERIOR ^ CRH_ACTUAL; 
//    uint32_t DELTA_ODR = ODR_ANTERIOR ^ ODR_ACTUAL;
//    uint32_t MODO_ACTUAL = (GPIOB->CRH & MASK_PIN9_MODO) >> OFFSET; //Extrae los 4 bits de modo de CRH para el pin 9
//    bool RELOJ_PUERTO_B_ON = RCC->APB2ENR & RCC_APB2ENR_IOPBEN;     //Sera verdadedo si el puerto B está encendido
//    TEST_ASSERT_TRUE(RELOJ_PUERTO_B_ON);                            //Es verdadero si se encendió el reloj del puerto B
//    TEST_ASSERT_FALSE(DELTA_CRL);                                   //
//    TEST_ASSERT_FALSE(DELTA_ODR);                                   //
//    TEST_ASSERT_BITS_LOW(~MASK_PIN9_MODO,DELTA_CRH);                //se espera que los bits de CRH que no pertenezcan al modo del pin9 no cambien
//    TEST_ASSERT_TRUE(MODO_ESPERADO & MODO_ACTUAL);                  //se espera que los 4 bits de modo extraidos sean iguales a los de modo esperado

//}
//static void test_SP_Pin_setModo_ENTRADA_PULLUP_PULLDN__DEBE_configurar_pin_como_ENTRADA_PULLUP_PULLDN(void){}
//static void test_SP_Pin_setModo_SALIDA_2MHz__DEBE_configurar_pin_como_SALIDA_2MHz(void){}
//static void test_SP_Pin_setModo_SALIDA_2MHz_OPEN_DRAIN__DEBE_configurar_pin_como_SALIDA_2MHz_OPEN_DRAIN(void){}
static void test_SP_Pin__SI_el_pin_esta_configurado_como_SALIDA_Push_Pull_y_se_escribe_un_CERO_debiera_leerse_0(void){
    SP_Pin_setModo(SP_PB6 , SP_PIN_SALIDA);
    SP_Pin_write(SP_PB6, 0);
    TEST_ASSERT_FALSE(SP_Pin_read(SP_PB6));
}

static void test_SP_Pin__SI_el_pin_esta_configurado_como_SALIDA_Push_Pull_y_se_escribe_un_UNO_debiera_leerse_1(void){
    SP_Pin_setModo(SP_PB6 , SP_PIN_SALIDA);
    SP_Pin_write(SP_PB6, 1);
    TEST_ASSERT_TRUE(SP_Pin_read(SP_PB6));
}

static void test_SP_Pin__SI_un_pin_configurado_como_ENTRADA_que_tiene_un_nivel_ALTO_debiera_leerse_1(void){
    SP_Pin_setModo(SP_PB6 , SP_PIN_SALIDA); // Se configura como salida
    SP_Pin_write(SP_PB6, 1);                // El pin se pone en ese nivel lógico y se queda en ese nivel
    SP_Pin_setModo(SP_PB6 , SP_PIN_ENTRADA);// Al ponerlo como entrada se desconecta el driver de salida, entonces queda cargado el capacitor del pin
    SP_Pin_write(SP_PB6, 0);                // Se cambia el valor de la salida pero ya no está conectada
    TEST_ASSERT_TRUE(SP_Pin_read(SP_PB6));  // Debe leer el valor que tenía antes

}

static void test_SP_Pin__SI_un_pin_configurado_como_ENTRADA_que_tiene_un_nivel_BAJO_debiera_leerse_0(void){
    SP_Pin_setModo(SP_PB6 , SP_PIN_SALIDA); // Se configura como salida
    SP_Pin_write(SP_PB6, 0);                // El pin se pone en ese nivel lógico y se queda en ese nivel
    SP_Pin_setModo(SP_PB6 , SP_PIN_ENTRADA);// Al ponerlo como entrada se desconecta el driver de salida, entonces queda cargado el capacitor del pin
    SP_Pin_write(SP_PB6, 1);                // Se cambia el valor de la salida pero ya no está conectada
    TEST_ASSERT_FALSE(SP_Pin_read(SP_PB6));  // Debe leer el valor que tenía antes}
}

int main(void){
    SP_init();
    SP_delay(1000);
    UNITY_BEGIN();
//    RUN_TEST(test_SP_Pin_setModo_ENTRADA_FLOTANTE__DEBE_configurar_pin_como_ENTRADA_FLOTANTE); // Ejecución de prueba: al poner la lista de argumentos a continuación del nombre de la funcíon entonces el nombre se convierte en objeto función que se evalúa a un puntero a función y esto se pasa como argumento a la macro RUN_TEST (en C los nombres de las funciones se evalúan a la dirección de memoria de la función)
    RUN_TEST(test_SP_Pin__SI_el_pin_esta_configurado_como_SALIDA_Push_Pull_y_se_escribe_un_CERO_debiera_leerse_0);
    RUN_TEST(test_SP_Pin__SI_el_pin_esta_configurado_como_SALIDA_Push_Pull_y_se_escribe_un_UNO_debiera_leerse_1);
    RUN_TEST(test_SP_Pin__SI_un_pin_configurado_como_ENTRADA_que_tiene_un_nivel_ALTO_debiera_leerse_1);
    RUN_TEST(test_SP_Pin__SI_un_pin_configurado_como_ENTRADA_que_tiene_un_nivel_BAJO_debiera_leerse_0);
    UNITY_END();
    return 0;
}