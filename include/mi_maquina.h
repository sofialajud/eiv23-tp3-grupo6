#ifndef MI_MAQUINA_H
#define MI_MAQUINA_H
#include <maquina_estado.h>
#include <stdint.h>
#include <stddef.h>

typedef struct MiMaquina
{
    Maquina maquina;
    Maquina *receptorEventos;
    int Contador;
}MiMaquina;

void MiMaquina_init(MiMaquina *self, Maquina *receptorEvento);

#endif
