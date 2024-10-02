#include <ESP8266WiFi.h>
#include <espnow.h>

const int buttonPins[] = {0, 1, 2, 3}; // GPIO pins for the buttons
const int numButtons = 4;

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x48, 0x3F, 0xDA, 0x4C, 0xE7, 0x26};

typedef struct struct_message {
  int buttonState[numButtons];
} struct_message;

struct_message myData;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0) {
    Serial.println("Delivery success");
  } else {
    Serial.println("Delivery fail");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT);
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);

  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
  for (int i = 0; i < numButtons; i++) {
    int currentState = digitalRead(buttonPins[i]);
    if (currentState != myData.buttonState[i]) {
      myData.buttonState[i] = currentState;
      esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));
      delay(30); // Adjust the delay if needed to avoid multiple rapid transmissions
    }
  }
}


