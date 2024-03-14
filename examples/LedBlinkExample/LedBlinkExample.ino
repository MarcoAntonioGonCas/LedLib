/*
  Este ejemplo muestra cómo usar la librería LedLib para parpadear un LED cada 30 segundos.
  El LED se enciende por un breve período de tiempo cada vez que ha transcurrido el tiempo especificado.
*/
#include <LedLib.h>


#define PINLED1 2     // Pin en donde se encuentra el LED.
#define ESPERA 7000  // Tiempo de espera para hacer parpadear el LED.

LedLib led1;

void setup(){
  // Iniciamos el led indicando en que pin se encuentra y el tipo de LED.
  // Anodo aplica voltaje POSITIVO (HIGH) para encender, Catodo aplica un voltaje NEGATIVO (LOW) para encender.
  led1.begin(PINLED1,Anodo);
}

// Variable auxialiar para el seguimiento de tiempo transcurrido.
long tiempoInicial = 0;

// Parpadeamos el LED cada 7 segundos 70000ms.
void loop(){
   // Método loop de la librería LedLib requerido.
  led1.loop();

  // Verificamos si aun no se lleva a cabo el seguimiento del tiempo.
  if(tiempoInicial == 0){
    // Establecemos el punto de referencia para calcular el tiempo transcurrido.
    tiempoInicial = millis();
  }

  // Calculamos el tiempo transcurrido y verificamos si este tiempo es mayor o igual al de espera.
  if(millis() - tiempoInicial >= ESPERA){
    // Prende el LED por 10 ciclos -> cada ciclo consta de 200ms prendido y 80ms apagado.
    led1.prender(200,80,10);

    // Reiniciamos el contador del tiempo.
    tiempoInicial = millis();
  }

}