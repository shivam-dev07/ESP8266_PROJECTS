#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Your WiFi credentials
char ssid[] = "Raju";
char pass[] = "thekingsuv1901";
char auth[] = "AJgMhH7_D6KW5mCk8XxvVSGVSWdvC3kg";

// Hardware setup
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)

// Scrolling parameters
uint8_t frameDelay = 20;  // default frame delay value
// Global message buffers shared by Blynk and Scrolling functions
#define BUF_SIZE  512
char curMessage[BUF_SIZE];
char newMessage[BUF_SIZE];
bool newMessageAvailable = false;

// OLED setup
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  Wire.pins(0, 2);

  // Connect to Wi-Fi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wi-Fi connected");

  // Initialize Blynk
  Blynk.begin(auth, ssid, pass);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;) {}
  }

  // Set text size and color
  display.setTextSize(4);
  display.setTextColor(WHITE);
  // Enable text wrapping for continuous scrolling
  display.setTextWrap(false);
  // Register a virtual pin handler for receiving messages from Blynk
  Blynk.virtualWrite(V0, "Test Message from ESP8266!");
}

void loop() {
  // Run Blynk
  Blynk.run();
  // Check if a new message is available and update the display
  if (newMessageAvailable) {
    strcpy(curMessage, newMessage);
    newMessageAvailable = false;
    display.clearDisplay();
    display.setCursor(1, 0);
    display.print(curMessage);
    display.display();
    delay(50);
    scrollText(curMessage); // Start scrolling the text
  }
}
void scrollText(char *message) {
  int16_t totalWidth = strlen(message) * 18; // Assuming each character width is 50 pixels
  int16_t x = SCREEN_WIDTH;
  while (true) {
    for (int16_t i = x; i >= -totalWidth; i--) {
      display.clearDisplay();
      display.setCursor(i, 0);
      display.print(message);
      display.display();
      // Check if the message has fully scrolled
      if (i == -totalWidth) {
        // Reset the x position for continuous scrolling
        x = SCREEN_WIDTH;
        break;
      }
    }
  }
}
// Blynk virtual pin handler for receiving messages
BLYNK_WRITE(V0) {
  strncpy(newMessage, param.asString(), BUF_SIZE);
  newMessageAvailable = true;
}
