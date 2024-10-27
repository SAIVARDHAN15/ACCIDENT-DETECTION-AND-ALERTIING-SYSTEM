# Accident Detection System with GPS & GSM

## Overview
This project is an **Accident Detection System** built using **TinyGPS, MPU6050, and a GSM module**. The system is designed to detect accidents based on sudden changes in gyroscope values and send an emergency SMS with the GPS coordinates to a predefined phone number. It also has a feature to make an emergency call if the accident is confirmed.

## Features
- **Accident Detection** based on the gyroscope sensor (MPU6050) readings.
- **Automatic Location Sharing** via an SMS with a Google Maps link.
- **Emergency Call** after accident detection.
- **Manual Override** button to cancel the emergency call if the user is safe.
- **LCD Display** to show system status.

## Components Used
- **Arduino Uno** or compatible board
- **MPU6050 Gyroscope Sensor**
- **SIM800L GSM Module**
- **TinyGPS Module**
- **Push Button** (for user confirmation)
- **16x2 LCD Display**

## Circuit Connections
- **MPU6050 Connections**: `xPin` (A1), `yPin` (A2), `zPin` (A3)
- **GSM Module Connections**: RX → Pin 8, TX → Pin 9
- **GPS Module Connections**: RX → Pin 0, TX → Pin 1
- **LCD Pins**: RS (12), E (11), D4 (7), D5 (6), D6 (5), D7 (4)
- **Push Button**: Digital Pin 13

## Working Explanation
1. The **MPU6050 gyroscope sensor** measures the angular velocity. If the angular velocity exceeds a certain threshold (`accidentThreshold`), it is considered an accident.
2. Upon accident detection, the system waits for **10 seconds**. During this time, the user can press the button if they are safe.
3. If the button is not pressed within 10 seconds, the system fetches the GPS coordinates and sends an emergency **SMS** with the location.
4. Additionally, the system **makes a call** to the predefined emergency number.
5. The LCD displays system status messages like "Accident Detected," "Waiting for 10s," "User is Safe," and "Location Sent".

## Code Explanation
- **Setup Function (`setup()`)**:
  - Initializes the serial communication and the LCD display.
  - Configures the button as an input.
  - Prints "System Ready" to the LCD when the system initializes successfully.

- **Main Loop (`loop()`)**:
  - Reads values from the MPU6050 gyroscope sensor on all three axes (X, Y, Z).
  - Calculates the **angular velocity** and checks if it exceeds the threshold (`accidentThreshold`).
  - If an accident is detected, the system waits for **10 seconds**.
  - During the waiting time, it checks the button state. If the button is pressed, it considers the user safe.
  - If the button is not pressed, it sends an **SMS** and **makes an emergency call**.

- **Sending Location and Making a Call (`sendLocationAndCall()`)**:
  - Fetches the GPS coordinates using the TinyGPS library.
  - Sends an SMS with a **Google Maps link** to the predefined phone number.
  - Makes a call to the predefined phone number using AT commands.

## Dependencies
- **Arduino SoftwareSerial** library for serial communication with the GSM and GPS modules.
- **TinyGPS library** for decoding GPS data.
- **Wire.h** for I2C communication with the MPU6050.
- **LiquidCrystal library** to control the 16x2 LCD display.

## Installation and Setup
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/yourusername/Accident-Detection-System.git
   cd Accident-Detection-System
2. **Install Arduino Libraries**:
- TinyGPS++
- LiquidCrystal (available through Arduino IDE's Library Manager)
- Wire (comes pre-installed with Arduino IDE)

3. **Upload the Code**:
-Open the Accident_Detection_System.ino file in the Arduino IDE.
- Connect the Arduino board to your PC.
- Choose the correct board and port in the Arduino IDE.
- Click on Upload to upload the code.


## Future Enhancements
- Add fall detection using accelerometer data for enhanced safety.
- Implement additional safety features like heart rate monitoring for real-time health data.
- Integrate with a cloud platform for central monitoring and accident data analytics.
## License
This project is open-source and licensed under the MIT License. Feel free to contribute, modify, and enhance this project!
---
