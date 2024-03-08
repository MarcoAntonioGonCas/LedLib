#ifndef LedLib_h
#define LedLib_h


#include <Arduino.h>

//#define DEBUGLEDLIB

typedef unsigned long ulong_t;

/// @brief Indica el tipo de LED Anodo, Catodo
enum TipoLed : int
{
    Catodo,
    Anodo
};

/// @brief Clase para manejar LEDS de forma sencilla.
class LedLib
{
private:
    // Tiempo inicial.
    ulong_t _tiempoIni;
    // Duracion de LED prendido.
    ulong_t _tiempoPrendido;
    // Duracion de LED apagado.
    ulong_t _tiempoApagado;
    // Veces del ciclo.
    uint32_t _veces;
    // Pin del led.
    uint8_t _pinLed;

    // Indica si se trata de un bucle infinito.
    bool _infinito = false;
    // Indica como Se prendera un led util para cuando el tipo de LED cambia Anodo, Catodo.
    bool _onLed = HIGH;
    bool _offLed = LOW;

    
    void loopInfinito();
      /// @brief Indica como polariza para encender el LED. Anodo aplica voltaje POSITIVO (HIGH) para encender, Catodo aplica un voltaje NEGATIVO (LOW) para encender.
    /// @param tipo 
    void fijarTipoLed(TipoLed tipo);

    /// @brief Indica en que pin se encuentra el LED.
    /// @param pin Pin en donde se encuentra el LED.
    void setPin(uint8_t pin);

     /// @brief Apaga el LED tomando en cuanta el tipo de LED.
    void apagar();

    /// @brief Prende el LED tomando en cuanta el tipo de LED.
    void prender();

    
public:
    // Indica si un proceso aun no se completa.
    bool enEjecucion();

    /// @brief Inicia el LED indicando el pin y el tipo de LED Anodo,Catado.
    /// @param pin El pin en donde se encuentra el LED.
    /// @param tipoLed Indica como polariza para encender el LED. Anodo aplica voltaje POSITIVO (HIGH) para encender, Catodo aplica un voltaje NEGATIVO (LOW) para encender.
    void begin(uint8_t pin, TipoLed tipoLed = TipoLed::Anodo);


    /// @brief Termina o forza la ejecucion, en caso de que el tiempo indicado para prender el LED no haya terminado.
    void parar();
    /// @brief Apaga el LED para le ejecucion.
    void apagarLED();
    /// @brief Prende el LED de forma infinita.
    void prenderLED();
    /// @brief Prende el LED por un tiempo indicado en ms.
    /// @param tiempoEn 
    void prender(ulong_t tiempoEn);

    /// @brief Prende el LED por una duracion especifica.
    /// @param tiempoEn Tiempo en que estara prendido el LED durante un ciclo.
    /// @param tiempoApa Tiempo en que estara apagado el LED durante un ciclo.
    /// @param veces Cantidad de ciclos. 
    void prender(ulong_t tiempoEn, ulong_t tiempoApa, uint32_t veces);

    /// @brief Prende el LED de forma infinita indicando el tiempo prendido y apagado durante un ciclo.
    /// @param tiempoEn Tiempo en que estara prendido el LED durante un ciclo.
    /// @param tiempoApa Tiempo en que estara apagado el LED durante un ciclo.
    /// @param veces Cantidad de ciclos. 
    void prenderInfinito(ulong_t tiempoEn, ulong_t tiempoApa);

    /// @brief Prende el LED por un tiempo indicado en ms utiliza codigo bloqueante -> delay().
    /// @param tiempoEn 
    void prenderBloqueante(ulong_t tiempoEn);


     /// @brief Prende el LED por una duracion especifica utiliza codigo bloqueante -> delay().
    /// @param tiempoEn Tiempo en que estara prendido el LED durante un ciclo.
    /// @param tiempoApa Tiempo en que estara apagado el LED durante un ciclo.
    /// @param veces Cantidad de ciclos. 
    void prenderBloqueante(ulong_t tiempoEn, ulong_t tiempoApa, uint32_t veces);



    /// @brief Se incluye dentro del metodo loop para el funcionamiento de los metodos.
    void loop();


    LedLib();
};



#endif