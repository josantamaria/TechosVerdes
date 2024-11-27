#define SAMPLES 10

void setup() {
  Serial.begin(115200);
  analogReadResolution(10);
}

void loop() {
  int Value = 0;

  // Promediar lecturas para reducir el ruido
  for (int i = 0; i < SAMPLES; i++) {
    Value += analogRead(36);
    delay(10);
  }
  
  Value /= SAMPLES;

  Serial.println("Lectura analogica: " + String(Value));

}
