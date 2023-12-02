/* 
 Created by: Roy Cuadra
 Date: 12/02/2023
*/

// Blynk BLYNK_AUTH_TOKEN Here


#include <ESP8266WiFi.h>
#include <Wire.h>
#include "MQ135.h"
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Arduino.h>

#define LENG 31
unsigned char buf[LENG];

int PM01Value = 0;
int PM2_5Value = 0;
int PM10Value = 0;
float air_quality = 0;

const char *ssid = "Polaris";
const char *password = "cuadra123";

// DHT settings
#define DHTPIN 5       // Pin where the DHT11 is connected
#define DHTTYPE DHT11   // Type of DHT sensor

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Initialize Blynk with your Auth Token
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  // Printing the ESP IP address
  Serial.println(WiFi.localIP());

  // Start the DHT sensor
  dht.begin();
}

void loop()
{
  if (Serial.find(0x42))
  {
    Serial.readBytes(buf, LENG);

    if (buf[0] == 0x4d)
    {
      if (checkValue(buf, LENG))
      {
        PM01Value = transmitPM01(buf);
        PM2_5Value = transmitPM2_5(buf);
        PM10Value = transmitPM10(buf);

        // Send sensor data to Blynk
        Blynk.virtualWrite(V1, PM01Value); // PM1.0 value
        Blynk.virtualWrite(V2, PM2_5Value); // PM2.5 value
        Blynk.virtualWrite(V3, PM10Value); // PM10 value
      }
    }
  }

  static unsigned long OledTimer = millis();
  if (millis() - OledTimer >= 1000)
  {
    OledTimer = millis();

    Serial.print("PM1.0: ");
    Serial.print(PM01Value);
    Serial.println("  ug/m3");

    Serial.print("PM2.5: ");
    Serial.print(PM2_5Value);
    Serial.println("  ug/m3");

    Serial.print("PM10 : ");
    Serial.print(PM10Value);
    Serial.println("  ug/m3");
    Serial.println();

    MQ135 gasSensor = MQ135(A0);
    air_quality = gasSensor.getPPM();
    Serial.print("Air Quality: ");
    Serial.print(air_quality);
    Serial.println("  PPM");
    Serial.println();

    Blynk.virtualWrite(V4, air_quality); // Air quality value

    // Read temperature and humidity from DHT sensor
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Send DHT data to Blynk
    Blynk.virtualWrite(V5, temperature); // Temperature value
    Blynk.virtualWrite(V6, humidity);    // Humidity value
  }

  Blynk.run();
}

char checkValue(unsigned char *thebuf, char leng)
{
  char receiveflag = 0;
  int receiveSum = 0;

  for (int i = 0; i < (leng - 2); i++)
  {
    receiveSum = receiveSum + thebuf[i];
  }
  receiveSum = receiveSum + 0x42;

  if (receiveSum == ((thebuf[leng - 2] << 8) + thebuf[leng - 1]))
  {
    receiveSum = 0;
    receiveflag = 1;
  }
  return receiveflag;
}

int transmitPM01(unsigned char *thebuf)
{
  return ((thebuf[3] << 8) + thebuf[4]);
}

int transmitPM2_5(unsigned char *thebuf)
{
  return ((thebuf[5] << 8) + thebuf[6]);
}

int transmitPM10(unsigned char *thebuf)
{
  return ((thebuf[7] << 8) + thebuf[8]);
}
