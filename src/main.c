#include <stm32f1xx.h>

int main (void)
{
//////ejemplos de expresiones and or xor etc

    unsigned volatile A=0x800000000U, B=1U<<2, C=1U<<4, D=1U<<7;
    
    //bit set
    A | = B;
    A | = C;
    A | = D;

    //bit clear
    A&= B;
    A&= C;

    //bit flip
    A&= B;//not b - simbolo de la ondita 
    A&= C;
//////


        RCC->APB2ENR | = RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;
        
        GPIOC-> CRH = (CPIOC->CRH & //ONDITA etc  ) 

}