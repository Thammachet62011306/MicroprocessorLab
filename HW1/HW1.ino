/*
  This program blinks pin 13 of the Arduino (the
  built-in LED)
*/
int count = 0;
bool reverse = false;
byte segments = 0b00000001;
long lastm = 0;
int a;

void setup()
{
  DDRD = 0b11111111;
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
}

void loop()
{
  if (analogRead(0) >= 1000)
  {
    if (millis() - lastm >= ab(analogRead(1)))
    {
      PORTD = segments;
      lastm = millis();
      if (count >= 7)
      {
        reverse = true;
      }
      if (count <= 0)
      {
        reverse = false;
      }
      if (reverse == false)
      {
        segments = segments << 1;
        count++;
      }
      else
      {
        segments = segments >> 1;
        count--;
      }
    }
  }
}

float ab(float in)
{
  if (in < 0) return in * -1;
  else return in;
}
