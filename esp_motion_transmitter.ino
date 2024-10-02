#include <ESP8266WiFi.h>

const char* ssid = "MARCOS X";                          // Wi-Fi network name (SSID)
const char* password = "00000000";            // Wi-Fi network password
const char* server = "192.168.123.247";                 // IP address of the server
int motion_sensor_pin = D1;                          // Pin connected to the motion sensor

void setup() {
  WiFi.begin(ssid, password);                        // Connect to Wi-Fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.println("Connecting to WiFi...");         // Display connecting message
  }
  Serial.println("Connected to WiFi");               // Connection successful message
  pinMode(motion_sensor_pin, INPUT);                 // Set motion sensor pin as input
}

void loop() {
if (digitalRead(motion_sensor_pin) == 0) {      // Check if motion is detected
WiFiClient client;                              // Create WiFiClient object
if (client.connect(server, 80)) {               // Connect to the server
    client.println("GET /motion-detected HTTP/1.1"); // Send HTTP GET request
    client.println("Host: other_ESP8266_IP_address"); // Specify the host
    client.println();                               // Send empty line to end the request
    }
    delay(1000);                                     // Wait for 1 second
    client.stop();                                   // Stop the client connection
  }
}
