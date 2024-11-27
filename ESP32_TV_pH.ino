#define PH_PIN 34  // Pin analógico donde está conectado el sensor
#define SAMPLES 10 // Número de muestras para promediar

// Calibración del sensor
float neutralVoltage = 1500;  // Voltaje a pH 7 (ajusta según tu calibración)
float acidVoltage = 2032;     // Voltaje a pH 4 (ajusta según tu calibración)

// Función para mapear el voltaje a pH
float calculatePH(float voltage) {
  float slope = (7.0 - 4.0) / ((neutralVoltage - acidVoltage) / 1000.0);
  float intercept = 7.0 - slope * (neutralVoltage / 1000.0);
  return slope * voltage + intercept;
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Sensor de pH SEN0161 v2 inicializado.");
}

void loop() {
  int analogValue = 0;

  // Promedio de muestras para reducir ruido
  for (int i = 0; i < SAMPLES; i++) {
    analogValue += analogRead(PH_PIN);
    delay(10);
  }
  analogValue /= SAMPLES;

  // Convertir el valor analógico a voltaje
  float voltage = analogValue * 3.3 / 4095.0;  // ADC a 12 bits, voltaje de referencia 3.3V

  // Calcular el pH
  float ph = calculatePH(voltage);

  // Imprimir resultados
  Serial.print("Voltaje: ");
  Serial.print(voltage, 3);
  Serial.println(" V");

  Serial.print("pH: ");
  Serial.println(ph, 2);

  // Esperar antes de la próxima lectura
  delay(1000);
}
