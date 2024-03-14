/*
  Este ejemplo muestra cómo usar la librería LedLib para parpadear un LED infinitamente.
  El LED se enciende y apaga por un tiempo indicado.
*/
#include <LedLib.h>


#define PINLED1 2     // Pin en donde se encuentra el LED.


LedLib led1;

void setup(){
  // Iniciamos el led indicando en que pin se encuentra y el tipo de LED.
  // Anodo aplica voltaje POSITIVO (HIGH) para encender, Catodo aplica un voltaje NEGATIVO (LOW) para encender.
  led1.begin(PINLED1,Anodo);
}


void loop(){
   // Método loop de la librería LedLib requerido.
  led1.loop();
  
  // Verificamos que el LED no este ejecutando algun ciclo.
  if(!led1.enEjecucion()){
    // Prendemos el led infinitamente 200ms prendido y 90ms apagado.
    led1.prenderInfinito(200,90);
  }
}