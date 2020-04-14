void mqttSetup()
{
  client.setServer(mqttServer, 1883);
  int i = 0;
  
  while((!client.connected()) && i<5)
  {
    if (client.connect("ESP8266Client")) {
        Serial.println("connected");
        client.subscribe("homebrew");
        Serial.print("MQQT State =");
        Serial.println(client.state());
        WriteDisplay(0,20,"MQQT Connected",true, true);
      } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        WriteDisplay(0,20,"MQQT Not Connected",true, true);
      }
      i++;
      delay(2000);
    }
}

void mqttSend()
{
  //I found the MQTT kept disconnecting due to timing out whilst it was happily communicating its findings to the world using the OLED
  if (!client.connected()) {
    mqttSetup();
  }
  client.loop(); 
  
  char cha[200];
  sprintf(cha,"homebrew,tag1=%s,tag2=%s TAmb=%02.1f,RHAmb=%02.1f,TProbe1=%2.1f,TProbe2=%2.1f,bRelay=%01i",tag1,tag2,ambientTemp,ambientRH,wortTemp[0],wortTemp[1],relayStatus);
  Serial.println(cha);
  Serial.println(client.state());
  client.subscribe("homebrew");
  Serial.print("MQTT Publish State: ");
  Serial.println(client.publish("homebrew",cha, true));
}
