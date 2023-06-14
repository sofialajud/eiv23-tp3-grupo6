#include <maquina_estado_impl.h>
#include <mi_maquina.h>

static Resultado estadoEspera(Maquina *ctx, Evento e);
static Resultado estadodeCuenta(Maquina *ctx, Evento e);

void MiMaquina_init(MiMaquina *self, Maquina *receptorEventos){
    Maquina_init(&self->maquina, estadoEspera);
    self->receptorEventos=receptorEventos;
}

Maquina *MiMaquina_asMaquina(MiMaquina *self){
    return (Maquina*)self;
}

static Resultado estadoEspera(Maquina *ctx, Evento e){

}

static Resultado estadodeCuenta(Maquina *ctx, Evento e){
    
}


