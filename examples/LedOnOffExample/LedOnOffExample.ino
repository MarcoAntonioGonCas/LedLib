/*
  Este ejemplo muestra cómo usar la librería LedLib para prender o apagar un LED.
  Ejemplo por actualizar :)
*/
#include <LedLib.h>


#define PINLED1 2     // Pin en donde se encuentra el LED.
#define PINBUTTON 4   // Pin en donde se encuentra el boton.

LedLib led1;
bool estadoLED = LOW; // Estado actual del led -> proximamente cambios :)

void setup(){
  // Iniciamos el led indicando en que pin se encuentra y el tipo de LED.
  // Anodo aplica voltaje POSITIVO (HIGH) para encender, Catodo aplica un voltaje NEGATIVO (LOW) para encender.
  led1.begin(PINLED1,Anodo);
  pinMode(PINBUTTON,INPUT_PULLUP);
}



void loop(){
   // Método loop de la librería LedLib requerido.
  led1.loop();

  // Verificamos si se presiono el boton.
  if(digitalRead(PINBUTTON) == LOW){
    while(digitalRead(PINBUTTON) == LOW){}

    // Si actualmente esta apagado prendemos el LED.
    if(estadoLED == LOW){
        led1.prenderLED();
    // Si actualmente esta prendido apagamos el LED.
    }else{
        led1.apagarLED();
    }
    estadoLED = !estadoLED;
  }
}