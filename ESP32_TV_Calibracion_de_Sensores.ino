//////////////////////////Librerias y constantes//////////////////////////
#define PIN 34
#define SAMPLES 10

/////////////////////////////////Setup////////////////////////////////////
void setup() {
  Serial.begin(115200);
  analogReadResolution(10);
}

//////////////////////////////////Loop////////////////////////////////////
void loop() {
  float adc_valor = voltage_filter(PIN);
  float voltage_valor = voltage_filter(PIN);
  println(adc_valor,0);
  println(voltage_valor,2);
}

/////////////////////////////////Funcionnes///////////////////////////////
float adc_filter(int pin){
  int value = 0;
  for (int i=0; i<SAMPLES; i++) {
    value += analogRead(pin);
    delay(10);
  }
  value /= SAMPLES;
  return value;
}

float voltage_filter(int pin){
  int value = 0;
  for (int i=0; i<SAMPLES; i++) {
    value += analogRead(pin);
    delay(10);
  }
  value /= SAMPLES;
  float voltage = value * 3.3 / 4095.0;
  return voltage;
}
