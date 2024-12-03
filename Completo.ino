////////////////////////////////// Librerias y constantes //////////////////////////////////////////
#include "thingProperties.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define PH_PIN 34   
#define TURBIDITY_PIN 35
#define SAMPLES 10
#define ONE_WIRE_BUS 4  

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

/////////////////////////////////////////// Setup //////////////////////////////////////////////////
void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 

  // Your code here
  sensors.begin();
  
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
   The following function allows you to obtain more information
   related to the state of network and IoT Cloud connection and errors
   the higher number the more granular information you’ll get.
   The default is 0 (only errors).
   Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

/////////////////////////////////////////// Loop //////////////////////////////////////////////////
void loop() {
  ArduinoCloud.update();
  
  // pH 
  float adc_ph = adc_filter(PH_PIN);
  float voltage_ph = voltage_filter(PH_PIN);
  valor_ph = calculatePH(voltage_ph);
  // Temperatura
  sensors.requestTemperatures();
  valor_temp = sensors.getTempCByIndex(0);
  // Turbidez
  float adc_turbidez = adc_filter(TURBIDITY_PIN);
  float voltage_turbidez = voltage_filter(TURBIDITY_PIN);
  valor_turbidez = calculateNTU(voltage_turbidez);

  delay(500); // Pausa para actualizar la lectura
}

/////////////////////////////////////////// Funciones //////////////////////////////////////////////////
float adc_filter(int pin){
  int value = 0;
  // Promediar lecturas para reducir el ruido
  for (int i=0; i<SAMPLES; i++) {
    value += analogRead(pin);
    delay(10);
  }
  value /= SAMPLES;
  return value;
}

float voltage_filter(int pin){
  int value = 0;
  // Promediar lecturas para reducir el ruido
  for (int i=0; i<SAMPLES; i++) {
    value += analogRead(pin);
    delay(10);
  }
  value /= SAMPLES;
  float voltage = value * 3.3 / 4095.0;
  return voltage;
}

float calculatePH(float voltage) {
  float slope = (7.0 - 4.0) / ((neutralVoltage - acidVoltage) / 1000.0);
  float intercept = 7.0 - slope * (neutralVoltage / 1000.0);
  return slope * voltage + intercept;
}

float calculateNTU(float voltage) {
  // Ajustar estos valores a partir de la tabla del fabricante o la calibración
  float maxNTU = 1000.0;  // Rango máximo de NTU (puedes ajustarlo según tu calibración)
  return (1.0 - ((voltage - clearWaterVoltage) / (maxTurbidityVoltage - clearWaterVoltage))) * maxNTU;
}

//////////////////////////////////////Funciones automaticas//////////////////////////////////////////////
void onCalPhHighChange()  {
  // Add your code here to act upon CalPhHigh change
}

void onCalPhLowChange()  {
  // Add your code here to act upon CalPhLow change
}

void onValorPhChange()  {
  // Add your code here to act upon ValorPh change
}

void onValorTempChange()  {
  // Add your code here to act upon ValorTemp change
}

void onClearWaterVoltageChange()  {
  // Add your code here to act upon ClearWaterVoltage change
}

void onMaxTurbidityVoltageChange()  {
  // Add your code here to act upon MaxTurbidityVoltage change
}

void onNeutralVoltageChange()  {
  // Add your code here to act upon NeutralVoltage change
}

void onAcidVoltageChange()  {
  // Add your code here to act upon AcidVoltage change
}

void onValorTurbidezChange()  {
  // Add your code here to act upon ValorTurbidez change
}
