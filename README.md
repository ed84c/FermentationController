# FermentationController
Controls and logs fermentation temeperature using ESP8266 Chip on a Wifi-Kit-8 Dev board. 
+ Single relay control
+ Logs from arbitrary number of temperature probes
+ DHT11 Atmospherics logged
+ Sends messages through MTQQ to a raspberry Pi inorder to log in influxdb

# Pre-Requisites
## Hardware
+ ESP8266
+ Raspberry Pi with Telegraf/InfluxDB setup (and Grafana to view the data)
+ DHT11
+ DS18B20's 
+ Relay, power supplies and brew heater

## Arduino Libraries 
+ ESP8266Wifi
+ PubSubClient
+ DHTEsp
+ OneWire
+ DallasTemperautre
+ U8g2lib
+ Wire
+ The NodeMCU board in the Arduino IDE

# Setup
You need to create a "WifiSettings.h" which defines your wifi password and SSID e.g.
```
const char* ssid     = "EdsCoolRouter";         
const char* password = "EdsH0TP4sSw0rd";
```
Edit Temp Profile.h to the desired temp and hold times
