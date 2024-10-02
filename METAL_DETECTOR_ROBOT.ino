// Include the library files
#define BLYNK_PRINT Serial 
//connect the NodeMCU ESP8266 board to our WiFi Network.
#include <ESP8266WiFi.h>
//connect our device to Blynk IoT Cloud.
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h> 

// Define the motor pins
#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENB D5
// Variables for the Blynk widget values
int x = 50;
int y = 50;
int Speed;

char auth[] = "u53leI5HJcCHaN2iFG5Ka2jwdXNxYtH6"; // Blynk auth token
char ssid[] = "Raju"; //Enter your WIFI name
char pass[] = "thekingsuv1901"; //Enter your WIFI passowrd

SimpleTimer timer; //object from simpletimer library

int vr = A0;// sensor pin
int sdata = 0;// variable to store sensor data

void myTimerEvent()
{
  // can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}
void setup() {
  Serial.begin(9600);
  //Set the motor pins as output pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(vr,  INPUT); //METAL DETECTOR INPUT TO MCU BOARD

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
 
  //timer interval for the function to call every second
   timer.setInterval(1000L,sensorvalue);
}

// Get the joystick values through blink application
BLYNK_WRITE(V0) {
  x = param[0].asInt();
}
// Get the joystick values through blink application
BLYNK_WRITE(V1) {
  y = param[0].asInt();
}
BLYNK_WRITE(V2) {
  Speed = param.asInt();
}

// Check these values using the IF condition
void smartcar() {
  if (y > 70) {
    carForward();
    Serial.println("carForward");
  } else if (y < 30) {
    carBackward();
    Serial.println("carBackward");
  } else if (x < 30) {
    carLeft();
    Serial.println("carLeft");
  } else if (x > 70) {
    carRight();
    Serial.println("carRight");
  } else if (x < 70 && x > 30 && y < 70 && y > 30) {
    carStop();
    Serial.println("carstop");
  }
}
void loop() {
  Blynk.run();// Run the blynk function
  smartcar();// Call the main function
  timer.run();//run the timer function
}
// function to read sensor value
void sensorvalue()
{
  // read sensor data
  sdata = analogRead(vr); 
  // write sensor value to blynk application
  Blynk.virtualWrite(V2,sdata);
}

/**************Motor movement functions*****************/
 // function to move forward
void carForward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
// function to move backward
void carBackward() { 
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
// function to move left
void carLeft() { 
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
// function to move right
void carRight() { 
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
// function to stop 
void carStop() { 

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}