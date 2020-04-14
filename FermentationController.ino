//Pin Allocation- for info: https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/
//D0=GPIO16,D1=5,D2=4,D3=2,D4=2,D5=14,D6=12,D7=13,D8=15
//For fermentation controller: D7 = Relay, D5 = DHT11, D6 = Probes 
#define relayPin 13
#define DHTPin 14
#define tempProbesPin 12

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>

//Ambient temp
#include "DHTesp.h" 
#include <DHT.h>
#define DHTType DHT11
DHT dht(DHTPin, DHTType);

//Temp Probes
#include <OneWire.h> //For the DS18B20 
#include <DallasTemperature.h>
OneWire oneWire(tempProbesPin);  
DallasTemperature probes(&oneWire);
#include "TempProfile.h" //Define the desired temp profile in here

//OLED
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif 
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ 16, /* clock=*/ 5, /* data=*/ 4);

//MQQT
#include "WifiSettings.h" //Contains the SSID and Password
#define mqttServer "192.168.10.116" //Raspberry PI IP
#define mqttTopic "homebrew"
WiFiClient espClient;
PubSubClient client(espClient);

//Tags used in the influxdb for each probe
#define tag1 "SARS-Cov2-Ale" 
#define tag2 "Poitin"

//Relays are active low
#define relayON 0  
#define relayOFF 1

int nProbes = 0, relayStatus=0; 
float wortTemp[8], ambientTemp, ambientRH;

void setup()
{
  probes.begin();  
  Serial.begin(115200);
  u8g2.begin();
  u8g2.setFontMode(0);  //Transparent is faster
  probes.begin();
  dht.begin();

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin,relayOFF);
  
  ConnectWifi();
  nProbes = probes.getDeviceCount();
  mqttSetup();
  
}

void loop()
{
  ReadTemperatures();
  UpdateDisplay();
  mqttSend();
  delay(1000);
}
