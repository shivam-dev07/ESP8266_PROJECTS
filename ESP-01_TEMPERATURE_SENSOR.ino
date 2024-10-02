#define BLYNK_PRINT Serial    
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>


char auth[] = "8r7VqaR1DmU_9Vh0n9TiMjE6TfnzJftf"; 



char ssid[] = "Raju";  //Enter your WIFI Name
char pass[] = "thekingsuv1901";  //Enter your WIFI Password

#define DHTPIN 2          


#define DHTTYPE DHT11  


DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
  Blynk.virtualWrite(V4, h);  //V5 is for Humidity
  Blynk.virtualWrite(V2, t);  //V6 is for Temperature
}

void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass);

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}


