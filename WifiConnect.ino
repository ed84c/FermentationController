void ConnectWifi()
{

  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  u8g2.clearBuffer();
  int i = 0; 
  while (WiFi.status() != WL_CONNECTED && i<10) { // Wait for the Wi-Fi to connect
    delay(1000);    
    WriteDisplay(i,20,".",false);
    i++;
  }

  if (i==10)
  {
    WriteDisplay(0,20, "Wifi Fail");
    delay(3000);   
  }
  else
  {
    WriteDisplay(0,20, "Wifi OK");
    delay(3000);
    char cha[30];
    IPAddress ip = WiFi.localIP();
    sprintf(cha, "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
    WriteDisplay(0,20,cha,true);
    delay(3000);
  } 
}
