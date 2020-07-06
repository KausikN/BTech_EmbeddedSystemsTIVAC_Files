/*
  Piano

  Plays 8 piano notes 
*/

// Params
int OUT_PIN = 10;
int LADDER_OUT = A0;

int DURATION = 100;
int KeyFrequencies[] = {262, 294, 330, 350, 392, 440, 496, 510};
int KeyBinaries[][8] = {{1,0,0,0,0,0,1,1}, 
						{1,0,0,1,0,0,1,1}, 
                       	{1,0,1,0,0,1,0,1}, 
						{1,0,1,0,1,1,1,1}, 
                       	{1,1,0,0,0,1,0,0}, 
						{1,1,0,1,1,1,0,0}, 
                       	{1,1,1,1,1,0,0,0}, 
						{1,1,1,1,1,1,1,1}};
int LadderPins[] = {A5, A4, A3, A2, A1, 11, 12, 13};

// Main Functions
void setup()
{  
  // Set Input Pins
  /*
  for(int i=2;i<=9;i++)
  {
    pinMode(i, INPUT);
  }
  */
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  
  // Set Output Pins
  pinMode(OUT_PIN, OUTPUT);
}

void loop()
{
  // Check if Buttons Pressed
  /*
  for(int i=2;i<=9;i++)
  {
    if (digitalRead(i) == HIGH)
  	{
      analogWrite(OUT_PIN, KeyFrequencies[i-2]);
    }
  }
  */
  
  if (digitalRead(8) == HIGH)
  {
    //tone(OUT_PIN, KeyFrequencies[0], DURATION);
    
    for(int i=0;i<8;i++)
    {
      if (KeyBinaries[0][i] == 1)
      {
        digitalWrite(LadderPins[i], HIGH);
      }
      else
      {
        digitalWrite(LadderPins[i], LOW);
      }
    }
    delay(1);
    tone(OUT_PIN, analogRead(LADDER_OUT)*2, DURATION);
  }
  else if (digitalRead(9) == HIGH)
  {
    //tone(OUT_PIN, KeyFrequencies[1], DURATION);
    
    for(int i=0;i<8;i++)
    {
      if (KeyBinaries[1][i] == 1)
      {
        digitalWrite(LadderPins[i], HIGH);
      }
      else
      {
        digitalWrite(LadderPins[i], LOW);
      }
    }
    delay(1);
    tone(OUT_PIN, analogRead(LADDER_OUT), DURATION);
  }
  else if (digitalRead(2) == HIGH)
  {
    //tone(OUT_PIN, KeyFrequencies[2], DURATION);
    
    for(int i=0;i<8;i++)
    {
      if (KeyBinaries[2][i] == 1)
      {
        digitalWrite(LadderPins[i], HIGH);
      }
      else
      {
        digitalWrite(LadderPins[i], LOW);
      }
    }
    delay(1);
    tone(OUT_PIN, analogRead(LADDER_OUT)*2, DURATION);
  }
  else if (digitalRead(3) == HIGH)
  {
    //tone(OUT_PIN, KeyFrequencies[3], DURATION);
    
    for(int i=0;i<8;i++)
    {
      if (KeyBinaries[3][i] == 1)
      {
        digitalWrite(LadderPins[i], HIGH);
      }
      else
      {
        digitalWrite(LadderPins[i], LOW);
      }
    }
    delay(1);
    tone(OUT_PIN, analogRead(LADDER_OUT)*2, DURATION);
  }
  else if (digitalRead(4) == HIGH)
  {
    //tone(OUT_PIN, KeyFrequencies[4], DURATION);
    
    for(int i=0;i<8;i++)
    {
      if (KeyBinaries[4][i] == 1)
      {
        digitalWrite(LadderPins[i], HIGH);
      }
      else
      {
        digitalWrite(LadderPins[i], LOW);
      }
    }
    delay(1);
    tone(OUT_PIN, analogRead(LADDER_OUT)*2, DURATION);
  }
  else if (digitalRead(5) == HIGH)
  {
    //tone(OUT_PIN, KeyFrequencies[5], DURATION);
    
    for(int i=0;i<8;i++)
    {
      if (KeyBinaries[5][i] == 1)
      {
        digitalWrite(LadderPins[i], HIGH);
      }
      else
      {
        digitalWrite(LadderPins[i], LOW);
      }
    }
    delay(1);
    tone(OUT_PIN, analogRead(LADDER_OUT)*2, DURATION);
  }
  else if (digitalRead(6) == HIGH)
  {
    //tone(OUT_PIN, KeyFrequencies[6], DURATION);
    
    for(int i=0;i<8;i++)
    {
      if (KeyBinaries[6][i] == 1)
      {
        digitalWrite(LadderPins[i], HIGH);
      }
      else
      {
        digitalWrite(LadderPins[i], LOW);
      }
    }
    delay(1);
    tone(OUT_PIN, analogRead(LADDER_OUT)*2, DURATION);
  }
  else if (digitalRead(7) == HIGH)
  {
    //tone(OUT_PIN, KeyFrequencies[7], DURATION);
    
    for(int i=0;i<8;i++)
    {
      if (KeyBinaries[7][i] == 1)
      {
        digitalWrite(LadderPins[i], HIGH);
      }
      else
      {
        digitalWrite(LadderPins[i], LOW);
      }
    }
    delay(1);
    tone(OUT_PIN, analogRead(LADDER_OUT)*2, DURATION);
  }

  delay(10); // Delay a little bit to improve simulation performance
}