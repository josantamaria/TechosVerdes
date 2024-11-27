#define TURBIDITY_PIN 35  // Pin ADC donde está conectado el sensor
#define SAMPLES 10        // Número de muestras para promediar

// Calibración (ajusta estos valores según tus condiciones)
const float clearWaterVoltage = 2.5; // Voltaje para agua clara (ajustar según la calibración)
const float maxTurbidityVoltage = 4.2; // Voltaje para máxima turbidez (ajustar según calibración)

// Función para mapear el voltaje a NTU (Nephelometric Turbidity Units)
float calculateNTU(float voltage) {
  // Ajustar estos valores a partir de la tabla del fabricante o la calibración
  float maxNTU = 1000.0;  // Rango máximo de NTU (puedes ajustarlo según tu calibración)
  return (1.0 - ((voltage - clearWaterVoltage) / (maxTurbidityVoltage - clearWaterVoltage))) * maxNTU;
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Sensor de turbidez SEN0189 inicializado.");
}

void loop() {
  int analogValue = 0;

  // Promediar lecturas para reducir el ruido
  for (int i = 0; i < SAMPLES; i++) {
    analogValue += analogRead(TURBIDITY_PIN);
    delay(10);
  }
  analogValue /= SAMPLES;

  // Convertir el valor analógico a voltaje
  float voltage = analogValue * 3.3 / 4095.0;  // ADC a 12 bits, referencia 3.3V

  // Calcular la turbidez en NTU
  float turbidity = calculateNTU(voltage);

  // Imprimir resultados
  Serial.print("Voltaje: ");
  Serial.print(voltage, 2);
  Serial.println(" V");

  Serial.print("Turbidez: ");
  Serial.print(turbidity, 2);
  Serial.println(" NTU");

  // Esperar antes de la próxima lectura
  delay(1000);
}
