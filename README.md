# ESP32-IoT-Weather-Station
Local IoT web server displaying real-time temperature and humidity using ESP32 and DHT22
# ESP32 IoT Local Weather Station

A localized Internet of Things (IoT) weather station built with an ESP32 microcontroller and a DHT22 sensor. The system hosts an asynchronous web server that delivers real-time environmental data directly to any browser on the local network.

## Features
* **Built-in Web Server:** ESP32 acts as a standalone web server (no external hosting required).
* **Real-Time AJAX Updates:** Sensor data on the web page updates automatically every 2 seconds without page refreshes.
* **mDNS Resolution:** Accessible via `http://stotele.local` instead of a hard-to-remember IP address.
* **Metric Data:** Displays temperature accurately in Celsius (°C) and relative humidity (%).

## Hardware Requirements
* ESP32 Development Board (NodeMCU Type-C)
* DHT22 Temperature & Humidity Sensor Module
* Breadboard (830 tie-points)
* Jumper Wires (Dupont M/M )

## Circuit / Wiring
Connecting the DHT22 module to the ESP32:

| DHT22 Pin | ESP32 Pin |
| :--- | :--- |
| **VCC (+)** | 3V3 (3.3V) |
| **DATA (OUT)** | GPIO 4 (D4) |
| **GND (-)** | GND |

*Note: Since I am using a DHT22 module (pre-soldered on a PCB), the 10kΩ pull-up resistor is already built-in.*

## Software & Libraries
Compiled using the Arduino IDE. Ensure you have the ESP32 board manager installed, along with the following library:
* **DHT sensor library** by Adafruit (Install via Arduino Library Manager)

## How to Use
1. Clone this repository or download the `.ino` file.
2. Open the file in the Arduino IDE.
3. Modify the network credentials in the code:
   ```cpp
   const char* ssid = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";
