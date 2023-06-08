#include <unity.h>
#include <soporte_placa.h>
#include <stm32f1xx.h>

void setUp(void){}    // no se las define static porque esta función esta declarada en unity
void tearDown(void){} // no se las define static porque esta función esta declarada en unity

/* Al definir las funciones antes del main, hace de declaración y definición*/
static void test_siempre_pasa(void){ // Al definirla static nos genera una advertencia si no se la llama en main 
    TEST_ASSERT_TRUE(1);
    TEST_ASSERT_FALSE(0);
    TEST_ASSERT_EQUAL_INT (10, 10);
}
static void test_siempre_falla(void){ 
    TEST_ASSERT_TRUE(1);// esta es verdadera
    TEST_ASSERT_FALSE(1);
    TEST_ASSERT_EQUAL_INT (10, -10);
}

int main(void){
    SP_init();
    SP_delay(1000);
    UNITY_BEGIN();
    RUN_TEST(test_siempre_pasa);// Ejecución de prueba: al poner la lista de argumentos a continuación del nombre de la funcíon entonces el nombre se convierte en objeto función que se evalúa a un puntero a función y esto se pasa como argumento a la macro RUN_TEST (en C los nombres de las funciones se evalúan a la dirección de memoria de la función)
    RUN_TEST(test_siempre_falla);
    UNITY_END();
    return 0;
}