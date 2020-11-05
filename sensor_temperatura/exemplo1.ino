#include "DHT.h"

const int PIN_OUT = 7;

DHT dht(PIN_OUT, DHT22);

void setup() {
  Serial.begin(9600);

  dht.begin();
}

void loop() {
  delay(2000);

  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha ao ler do sensor DHT!");
    return;
  }

  float indiceCalor = dht.computeHeatIndex(temperatura, umidade, false);

  Serial.print("Umidade: " + String(umidade) + "% ");
  Serial.print("Temperatura: " + String(temperatura) + "°C ");
  Serial.println("Indice de calor: " + String(indiceCalor) + "°C");
}