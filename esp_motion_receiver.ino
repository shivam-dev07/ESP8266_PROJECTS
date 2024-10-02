#include <ESP8266WiFi.h>

const char* ssid = "Raju";
const char* password = "thekingsuv1901";

WiFiServer server(80);

int motion_detected = 0;
int timer = 0;
int led_pin = D2;
int relay_pin1= D5;
int relay_pin2= D6;
int relay_pin3= D7;
int relay_pin4= D8;
void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(relay_pin1,OUTPUT);
  pinMode(relay_pin2,OUTPUT);
  pinMode(relay_pin3,OUTPUT);
  pinMode(relay_pin4,OUTPUT);
  digitalWrite(led_pin, LOW);
  digitalWrite(relay_pin1, HIGH);
  digitalWrite(relay_pin2, HIGH);
  digitalWrite(relay_pin3, HIGH);
  digitalWrite(relay_pin4, HIGH);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  server.begin();
  Serial.println("Server started");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    if (request.indexOf("/motion-detected") != -1) {
      motion_detected = 1;
      digitalWrite(led_pin, HIGH);
      digitalWrite(relay_pin1, LOW);
      digitalWrite(relay_pin2, LOW);
      digitalWrite(relay_pin3, LOW);
      digitalWrite(relay_pin4, LOW);
    }
    client.flush();
    client.stop();
  }
  
  if (motion_detected) {
    timer++;
    delay(1000);
    if (timer == 10) {
      motion_detected = 0;
      digitalWrite(led_pin, LOW);
      digitalWrite(relay_pin1, HIGH);
      digitalWrite(relay_pin2, HIGH);
      digitalWrite(relay_pin3, HIGH);
      digitalWrite(relay_pin4, HIGH);
      timer = 0;
    }
  }
}

 /*if (digitalRead(MOTION_SENSOR_PIN) == LOW) {  // check for motion detection
            motion_detected = 1;  // set motion_detected as True
            digitalWrite(LED_PIN, HIGH);  // turn on the LED
        }
        if (motion_detected) {
            timer++;  // increment the timer
            delay(1000);  // wait for 1 second
            if (timer == 10) {  // check if 10 seconds have passed
                motion_detected = 0;  // set motion_detected as False
                digitalWrite(LED_PIN, LOW);  // turn off the LED
                timer = 0;  // reset the timer
            }

}
}*/












