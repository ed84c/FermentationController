float CalcTargetTemp()
{
  //Loop through all steps and find which step we should currently be on, and hence what temp we target
  int t=0;
  int idx =0;
  bool stopCycle= true;
  float tTarget=-1;

  Serial.print("Time Elapsed:");
  Serial.println(millis()/1000);
  for(int i=0;i<nSteps;i++)
  {
    if(millis()/1000>t)
    {
      idx = i;
    }
    t = t + holdTime_1[i];
  }
  tTarget = temp_1[idx];

  //If we are past the end of the cycle return -1
  if(millis()/1000>t)
  {
      tTarget = -1;
  }
    
 return tTarget;
}

void actionRelays(uint8_t d)
{
  digitalWrite(relayPin,d);
  relayStatus = ~d;
}


void HeatController(float currentTemp)
{
  
  char cha[30];
  float targetTemp = CalcTargetTemp();

  //targetTemp= -1 implies we are at the end of the cycle
  sprintf(cha,"T Target : %2.1fC",targetTemp);
  WriteDisplay(0,20,cha,true, true); 
  Serial.println(cha);
  if ((targetTemp==-1) || (currentTemp>targetTemp ))
  {
    actionRelays(relayOFF);
    Serial.println("Relays OFF");
    WriteDisplay(0,20,"Relay OFF",true, true);
  }
  else
  {
    actionRelays(relayON);
    Serial.println("Relays ON");
    WriteDisplay(0,20,"Relay ON",true, true);
  }
}
