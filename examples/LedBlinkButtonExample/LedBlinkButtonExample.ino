/*
  Este ejemplo muestra cómo usar la librería LedLib para parpadear un LED cada que se presione un boton.
*/
#include <LedLib.h>


#define PINLED1 2     // Pin en donde se encuentra el LED.
#define PINBUTTON 4   // Pin en donde se encuentra el boton. 

LedLib led1;

void setup(){
  // Iniciamos el led indicando en que pin se encuentra y el tipo de LED.
  // Anodo aplica voltaje POSITIVO (HIGH) para encender, Catodo aplica un voltaje NEGATIVO (LOW) para encender.
  led1.begin(PINLED1,Anodo);
  
  pinMode(PINBUTTON,INPUT_PULLUP);
}



void loop(){
   // Método loop de la librería LedLib requerido. 
  led1.loop();


  // Verificamos si se preciono el boton
  if(digitalRead(PINBUTTON) == LOW){
    while(digitalRead(PINBUTTON) == LOW){}
    // Forzamos la ejecucion para que los ciclos se inicien de nuevo.
    led1.parar();
    // Prende el LED por 10 ciclos -> cada ciclo consta de 200ms prendido y 100ms apagado.
    led1.prender(200,20,10);
  }

}