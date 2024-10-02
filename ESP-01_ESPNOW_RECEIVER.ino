#include <ESP8266WiFi.h>
#include <espnow.h>

const int ledPins[] = {0,1,2,3}; // GPIO pins for the LEDs
const int numLeds = 4;

typedef struct struct_message {
  int buttonState[numLeds];
} struct_message;

struct_message myData;

void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));

  for (int i = 0; i < numLeds; i++) {
    if (myData.buttonState[i] == HIGH) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Nothing to do here, waiting for ESP-NOW messages
}


