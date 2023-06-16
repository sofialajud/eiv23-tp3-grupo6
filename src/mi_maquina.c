#include <maquina_estado_impl.h>
#include "mi_maquina.h"
#include "eventos_aplicacion.h"
#include <despacho_retardado.h>

static Resultado estadoEspera(Maquina *ctx, Evento e);
static Resultado estadodeCuenta(Maquina *ctx, Evento e);

void MiMaquina_init(MiMaquina *self, Maquina *receptorEventos, DespachoRetardado *despacho){
    Maquina_init(&self->maquina, estadoEspera);
    self->receptorEventos=receptorEventos;
    self->despacho=despacho;
    self->Contador=0;
    self->tiempoMaximo=1000;

}

Maquina *MiMaquina_asMaquina(MiMaquina *self){
    return (Maquina*)self;
}

static Resultado estadoEspera(Maquina *ctx, Evento e){
    MiMaquina *self=(MiMaquina*) ctx;
    Resultado r={0};
    switch (e)
    {
    case EV_RESET:
        r.codigo=RES_PROCESADO;
    break; case EV_BOTON_PULSADO:
        r.codigo=RES_TRANSICION;
        self-> Contador=1;
        r.nuevoEstado=estadodeCuenta;
        DespachoRetardado_programa(self->despacho, ctx, EV_TIMEOUT_MIMAQUINA, self->tiempoMaximo);
        Maquina_despacha(self->receptorEventos,EV_BOTON_PULSADO);
    break; default:
        r.codigo=RES_IGNORADO;
    break;
    }
    return r;
}

static Resultado estadodeCuenta(Maquina *ctx, Evento e){
    MiMaquina *self=(MiMaquina*) ctx;
    Resultado r={0};
    switch (e)
    {
    case EV_TIMEOUT_MIMAQUINA:
        r.codigo=RES_TRANSICION;
        r.nuevoEstado=estadoEspera;
    break; case EV_BOTON_PULSADO:
        ++(self-> Contador);
        r.codigo=RES_PROCESADO;
        if (self-> Contador>2)
        {
            r.codigo=RES_TRANSICION;
            r.nuevoEstado=estadoEspera;
            Maquina_despacha(self->receptorEventos,EV_TOQUE_TRIPLE);
        }
        
    break; default:
        r.codigo=RES_IGNORADO;
    break;
    }
    return r;
}


