#include <soporte_placa.h>
#include <stm32f1xx.h>

// Implementación

typedef struct Pin{
    GPIO_TypeDef * puerto;
    int nrPin;
}Pin;

Pin const pines[SP_HPIN_LIMITE] = {
    [SP_PB9]={.puerto=GPIOB,.nrPin=9},
    [SP_PC13]={.puerto=GPIOC,.nrPin=13},
};

#define PIN_DE_HANDLE(hpin) (pines[hpin])

//...comtinuar con la implementación. Lo primero que se puede hacer es copiar la definicion de las declaraciones

void SP_Pin_setModo(SP_HPin pin, SP_Pin_Modo modo){

}

bool SP_Pin_read(SP_HPin pin);{

}

bool SP_Pin_write(SP_HPin pin, bool valor);{
    
}

