#include <SPI.h>
#include <WiFi101.h>
#include <MQTT.h>
#include <dht11.h>
#define DHT11PIN 4

dht11 DHT11;
const char ssid[] = "Ste-adele";
const char pass[] = "allo1234";

WiFiClient net;
MQTTClient client;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("arduino", "public", "public")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");


}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);

  client.begin("broker.emqx.io", net);

  connect();
}

void loop() {
  int chk = DHT11.read(DHT11PIN);

  int humidity = (int)DHT11.humidity;

  int temperature= (int)DHT11.temperature;


  client.loop();

  if(!client.connected()) {
    connect();
  }
  // Publish a message

  client.publish("django/mqtt","t", temperature);
  client.publish("django/mqtt","h", humidity);
   
    delay(1000);
  }

//sources : 
// https://www.hackster.io/officine/interfacing-arduino-mkr-or-esp-via-mqtt-node-red-101-4833bc
// https://docs.arduino.cc/tutorials/mkr-1000-wifi/mkr-1000-mqtt-device-to-device
// https://projecthub.arduino.cc/arcaegecengiz/using-dht11-12f621



