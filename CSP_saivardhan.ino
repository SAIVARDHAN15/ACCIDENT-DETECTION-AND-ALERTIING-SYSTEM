#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <MPU6050.h>
#include <Sim800L.h>
#define xPin A1
#define yPin A2
#define zPin A3
SoftwareSerial Gsm(8, 9);
SoftwareSerial Gps(0, 1);  // Software Serial for GSM module
char phone_no[] = "+919492170279";  // Replace with the emergency phone number

TinyGPS gps;  // GPS object
int buttonPin = 13;  // Pin for the push button
 // Analog pin for gyroscope
int threshold = 500;
  // Adjust this threshold for accident detection
unsigned long accidentTime = 0; 
 // Timestamp for accident
boolean accidentDetected = false;

LiquidCrystal lcd(12, 11, 7, 6, 5, 4); // Pins for LCD
MPU6050 mpu;
void setup() {
  Serial.begin(9600);
  Gsm.begin(9600);
  lcd.begin(16, 2); // Initialize LCD
  pinMode(buttonPin, INPUT);  // Button with internal pull-up resistor

  lcd.print("System Ready");

}

void loop() {

  int gyroX = analogRead(xPin);
  int gyroY = analogRead(yPin);
  int gyroZ = analogRead(zPin);
Serial.print("Xaxis value: ");
Serial.print(gyroX);
Serial.print(", Yaxis value: ");
Serial.print(gyroY);
Serial.print(", Zaxis value: ");
Serial.println(gyroZ);
delay(100);

  // Calculate the angular velocity in degrees per second (dps)
  float angularVelocityX = gyroX / 131.0; // 131 LSB/dps for ±250 dps sensitivity
  
  // Define a threshold for accident detection (adjust as needed)
  float accidentThreshold = 3;
  int abs=abs(angularVelocityX); // Change this value based on your requirements
    Serial.print("ANG velocity: ");
    Serial.print(abs);
    
    

  // Check if the angular velocity exceeds the threshold on any axis
  if (abs(angularVelocityX) > accidentThreshold) {
      // Accident detected
      accidentTime = millis();
      accidentDetected = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Accident Detected");
      lcd.setCursor(0, 1);
      lcd.print("Waiting for 10s");
    }

    if (accidentDetected && millis() - accidentTime >= 10000) {
      // Waited for 10 seconds, check if the button is pressed
      int buttonStateAfterDelay = digitalRead(buttonPin);
      Serial.println(buttonStateAfterDelay);
      if (buttonStateAfterDelay == 1) {
        // Button is pressed, user is safe
        accidentDetected = false;
        lcd.clear();
        lcd.print("User is Safe");
        delay(1000);  // Debounce delay
      } else {
        // Send location, make an emergency call, and display status
        sendLocationAndCall();
      }
    }
  }


void sendLocationAndCall() {
  float flat, flon;
  unsigned long age;
  gps.f_get_position(&flat, &flon, &age);

  // Send SMS with GPS location
  Gsm.print("AT+CMGF=1\r");
  delay(400);
  Gsm.print("AT+CMGS=\"");
  Gsm.print(phone_no);
  Gsm.println("\"");
  Gsm.print("Accident detected at: http://maps.google.com/maps?q=loc:");
  Gsm.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
  Gsm.print(",");
  Gsm.print(flon == TinyGPS ::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
  Gsm.println((char)26);
  delay(200);

  // Make an emergency call
  Gsm.println("ATD" + String(phone_no) + ";");
  delay(15000);  // Call duration (adjust as needed)
  Gsm.println("ATH");
  delay(1000);

  // Display status
  lcd.clear();
  lcd.print("Accident Detected");
  lcd.setCursor(0, 1);
  lcd.print("Location Sent");
}
