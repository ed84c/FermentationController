void ReadTemperatures()
{
  ReadProbes();
  ReadAmbient();
}

void ReadAmbient()
{
  ambientRH = dht.readHumidity();
  ambientTemp = dht.readTemperature();
}
void ReadProbes()
{
  probes.requestTemperatures(); 
  for (int i = 0;  i < nProbes;  i++)
  {
    wortTemp[i] = probes.getTempCByIndex(i);
    char cha[30];
    sprintf(cha, "Probe %02i = %02.5f DegC",i+1,wortTemp[i]);
    HeatController(wortTemp[i]);
  }
}
