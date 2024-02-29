#define BLYNK_TEMPLATE_ID "XXX"
#define BLYNK_TEMPLATE_NAME "XXXX" //These are provided by Blynk when you do a new project
#define BLYNK_AUTH_TOKEN "XXXX"
#define BLYNK_PRINT Serial
#include <Wire.h>
#include "Adafruit_HTU21DF.h"
#include "Adafruit_BMP280.h"
#include <ESP8266WiFi.h>
#include <Blynk.h>
#include <BlynkSimpleEsp8266.h>



Adafruit_BMP280 bme; //adress 0x76
Adafruit_HTU21DF htu = Adafruit_HTU21DF(); //adress 0x40

char auth[] = "XXXX";          //blink token
char ssid[] = "XXXX";      //Wifi name
char pass[] = "XXXX"; //Wifi pass


BlynkTimer timer;

void sendData(){
  //float temp = htu.readTemperature(); //Reads Temperature from HTU21D sensor / will use the BMP280 to get this value
  float temp = bme.readTemperature();   //Reads Temperature from BMP280 sensor
  float pre  = bme.readPressure();      //Reads Pressure from BMP280 sensor
  float hum  = htu.readHumidity();      //Reads Humidity from HTU21D sensor
  //Prints Obtained readings
  Serial.print("\nTemperatura(°C): ");
  Serial.print(temp);
  Serial.print("\t\t");
  Serial.print("\nHumedad(%): ");
  Serial.print(hum);
  Serial.print("\t\t");
  Serial.print("\nPresion(Pa): ");
  Serial.print(pre);

  //send data to Blynk app
  Blynk.virtualWrite(V1, temp); //sends BMP280 temperature
  Blynk.virtualWrite(V2, hum);  //sends HTU21D humidity
  Blynk.virtualWrite(V3,pre);   //sends BMP280 pressure
}

void setup() {
 
  Serial.begin(115200);

  Blynk.begin(auth,ssid,pass);
  delay(1000); //hang on a second there
  Serial.begin(115200);
  
  if(!bme.begin()){
    Serial.println("BMP280 not found.");
    while(1); //stays here till its detected
  }

  if (!htu.begin()){
    Serial.println("HTU21D not found.");
    while(1); //stays here till its detected
  }

  timer.setInterval(1000L, sendData);

}

void loop() {

  Blynk.run();
  timer.run();

}


