#include <OneWire.h>
#include <DallasTemperature.h>

// Pin al que está conectado el terminal DATA del DS18B20
#define ONE_WIRE_BUS 4 

// Configuración de OneWire
OneWire oneWire(ONE_WIRE_BUS);

// Configuración del sensor de temperatura
DallasTemperature sensors(&oneWire);

void setup() {
  // Inicializar comunicación serie
  Serial.begin(115200);
  delay(1000);

  // Inicializar sensores
  sensors.begin();
}

void loop() {
  // Solicitar temperatura al sensor
  sensors.requestTemperatures();
  
  // Leer la temperatura en grados Celsius
  float tempC = sensors.getTempCByIndex(0);  // Index 0 para el primer sensor
  
  Serial.print("Temperatura: ");
  Serial.print(tempC);
  Serial.println(" °C");

  // Esperar un segundo antes de la próxima lectura
  delay(1000);
}
