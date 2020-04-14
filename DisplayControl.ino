void WriteLine(int x, int y,char *cha)
{
  u8g2.setFont(u8g2_font_b16_b_t_japanese1);
  u8g2.drawUTF8(x,y, cha);
  u8g2.sendBuffer();
}

void WriteDisplay(int x, int y,char *cha,bool clearBuf = true, bool scroll = false, int delayTime = 3000)
{
  if(clearBuf)
  {
    u8g2.clearBuffer();
  }
  WriteLine(x,y,cha);
  delay(delayTime);
  if(scroll)
  {
    ScrollText(cha);
    delay(1000);
  }
}


void UpdateDisplay()
{
  char cha[30];

  sprintf(cha,"Amb Temp : %2.1fC",ambientTemp);
  WriteDisplay(0,20,cha,true, true);
  sprintf(cha,"Amb RH : %2.1f%%",ambientRH);
  WriteDisplay(0,20,cha,true, true);
   
  for (int i = 0;  i < nProbes;  i++)
  {
    sprintf(cha,"Probe %01i : %2.1fC",i+1,wortTemp[i]);
    WriteDisplay(0,20,cha,true, true);
  }
  
}

void ScrollText(char* cha)
{
   //Scroll the text for effect 
    for(int xOffset = 0; xOffset<u8g2.getDisplayWidth()*0.5;xOffset++)
    {
      u8g2.clearBuffer();
      WriteLine(xOffset,20,cha);
    }
}
