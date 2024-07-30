
# AtmoSense - IoT Air Quality Monitor
AtmoSense is an Internet of Things (IoT) project that use a ESP8266 microcontroller to monitor air quality.

## Features
- Real-time monitoring of particulate matter (PM1.0, PM2.5, PM10) levels.
- Gas concentration measurement using the MQ135 sensor.
- Temperature and humidity readings from the DHT11 sensor.
- Wireless connectivity for remote monitoring through the Blynk platform.
  
## Hardware Components
- ESP8266 (NodeMCU or similar)
- MQ135 Gas Sensor
- DHT11 Temperature and Humidity Sensor

## Wiring Instructions
- Connect the PM Sensor to the ESP8266.
- Connect the MQ135 Gas Sensor to the A0 pin on the ESP8266.
- Connect the DHT11 sensor to pin D5 on the ESP8266.

## Blynk Setup
- Create a Blynk account and obtain an authentication token.
- Create a Blynk project with three gauges (PM1.0, PM2.5, PM10), a value display (Air Quality), and two graphs (Temperature and Humidity).
- Replace BLYNK_AUTH_TOKEN in the code with your Blynk authentication token.
  
## WiFi Setup
- Replace "ssid" and "password" with your WiFi credentials.

## Usage
- Upload the code to your ESP8266 using the Arduino IDE.
- Open the Serial Monitor to view the connection status.
- Once connected, the ESP8266 will start monitoring and sending data to your Blynk project.

## License

This project is open-source and available under the MIT License. See the [LICENSE](LICENSE) file for more details.
