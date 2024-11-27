#define SOIL_SENSOR_PIN 32  // Pin ADC donde está conectado el sensor
#define SAMPLES 10          // Número de muestras para promediar

// Calibración inicial (ajusta según las lecturas de tu sensor)
int dryValue = 700;   // Valor analógico cuando el sensor está completamente seco
int wetValue = 1500;  // Valor analógico estimado para el sensor completamente mojado

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Sensor de humedad de suelo inicializado.");
}

void loop() {
  int analogValue = 0;

  // Promediar lecturas para reducir el ruido
  for (int i = 0; i < SAMPLES; i++) {
    analogValue += analogRead(SOIL_SENSOR_PIN);
    delay(10);
  }
  analogValue /= SAMPLES;

  // Mapear el valor analógico a porcentaje de humedad
  int moisturePercentage = map(analogValue, dryValue, wetValue, 0, 100);
  moisturePercentage = constrain(moisturePercentage, 0, 100);  // Limitar entre 0 y 100%

  // Imprimir los resultados
  Serial.print("Valor analógico: ");
  Serial.println(analogValue);

  Serial.print("Humedad del suelo: ");
  Serial.print(moisturePercentage);
  Serial.println("%");

  // Esperar antes de la próxima lectura
  delay(1000);
}
