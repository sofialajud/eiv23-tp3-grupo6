#ifndef MI_MAQUINA_H
#define MI_MAQUINA_H
#include <maquina_estado.h>
#include <stdint.h>
#include <stddef.h>
#include <despacho_retardado.h>

typedef struct MiMaquina
{
    Maquina maquina;
    Maquina *receptorEventos;
    DespachoRetardado *despacho;
    uint32_t Contador;
    uint32_t tiempoMaximo;
}MiMaquina;

void MiMaquina_init(MiMaquina *self, Maquina *receptorEvento, DespachoRetardado *despacho);

Maquina *MiMaquina_asMaquina(MiMaquina *self);
#endif
