#include <Arduino.h>
#include "LedLib.h"

void LedLib::setPin(uint8_t pin)
{
    this->_pinLed = pin;
}

void LedLib::fijarTipoLed(TipoLed tipo){
    if(tipo == TipoLed::Anodo){

        this->_onLed  = HIGH;
        this->_offLed = LOW;
    }else if(tipo == TipoLed::Catodo){

        this->_onLed  = LOW;
        this->_offLed = HIGH;
    }
    apagar();
}

void LedLib::begin(uint8_t pin, TipoLed tipoLed)
{
    setPin(pin);
    fijarTipoLed(tipoLed);
    pinMode(_pinLed, OUTPUT);
    apagar();
}

bool LedLib::enEjecucion(){
    return _infinito || _tiempoIni != 0;
}

void LedLib::prender()
{
    digitalWrite(this->_pinLed, this->_onLed);
}
void LedLib::apagar()
{   
    digitalWrite(this->_pinLed, this->_offLed);
}
void LedLib::prenderLED()
{
    parar();
    prender();
}
void LedLib::apagarLED()
{   
    parar();
    apagar();
}

void LedLib::prender(ulong_t tiempoEn){
    ulong_t tiempoTranscurrido = millis() - _tiempoIni;

    // Si las configuraciones son las mismas, se omite
    if( tiempoEn == _tiempoPrendido and
        tiempoTranscurrido < tiempoEn){
        return;
    }

    parar();

    this->_tiempoIni = millis();
    this->_tiempoPrendido = tiempoEn;
    this->_tiempoApagado = 0;
    this->_veces = 1;
    this->_infinito = false;    

}

void LedLib::prender(ulong_t tiempoEn, ulong_t tiempoApa, uint32_t veces)
{
    ulong_t tiempoTranscurrido = millis() - _tiempoIni;
    ulong_t tiempoCiclo = _tiempoPrendido + _tiempoApagado;
    ulong_t tiempoTotal = tiempoCiclo * veces;

    // Si se llama a la función con los mismos parámetros antes de que el ciclo actual termine, se omite
    if( tiempoEn == this->_tiempoPrendido and
        tiempoApa == this->_tiempoApagado and 
        tiempoTranscurrido < tiempoTotal){
            return;
    }
    parar();

    this->_tiempoIni = millis();
    this->_tiempoPrendido = tiempoEn;
    this->_tiempoApagado = tiempoApa;
    this->_veces = veces;
    this->_infinito = false;
}

void LedLib::prenderInfinito(ulong_t tiempoEn, ulong_t tiempoApa){
    _infinito = true;

    // Si las configuraciones son las mismas, se omite
    if(this->_tiempoPrendido == tiempoEn &&
     this->_tiempoApagado == tiempoApa){
        return;
    }
    parar();

    this->_tiempoIni = millis();
    this->_tiempoPrendido = tiempoEn;
    this->_tiempoApagado = tiempoApa;
    this->_veces = 1;
}

void LedLib::prenderBloqueante(ulong_t tiempoEn){
    prender();
    delay(tiempoEn);
    apagar();
}
void LedLib::prenderBloqueante(ulong_t tiempoEn, ulong_t tiempoApa, uint32_t veces){

    for(uint32_t i = 0;i<veces;i++){
        prender();
        delay(tiempoEn);
        apagar();
        delay(tiempoApa);
    }

}

LedLib::LedLib()
{
    this->_pinLed = 0;
    this->_tiempoIni = 0;
    this->_infinito = false;
}
void LedLib::parar()
{
    this->_tiempoIni = 0;
    this->_tiempoPrendido = 0;
    this->_tiempoApagado = 0;
    this->_veces = 0;
    this->_infinito = false;
}
void LedLib::loopInfinito(){

    ulong_t tiempoActual = millis();
    ulong_t tiempoTranscurrido = tiempoActual - _tiempoIni;
    ulong_t tiempoCiclo = _tiempoPrendido + _tiempoApagado;


    if(tiempoTranscurrido % tiempoCiclo <  _tiempoPrendido){
        prender();
    }else{
        apagar();
    }

}
void LedLib::loop()
{
    if(_infinito){
        loopInfinito();
        return;
    }

    if (_tiempoIni == 0){
        
        return;
    }
    ulong_t tiempoActual = millis();

    ulong_t tiempoTranscurrido = tiempoActual - _tiempoIni;
    ulong_t tiempoCiclo = _tiempoPrendido + _tiempoApagado;
    ulong_t tiempoTotal = tiempoCiclo * _veces;

    

    if (tiempoTranscurrido < tiempoTotal)
    {

        if (tiempoTranscurrido % tiempoCiclo < _tiempoPrendido)
        {

            prender();
        }
        else
        {

            apagar();
        }


    }
    else
    {
        _tiempoIni = 0;
        apagar();
    }
}