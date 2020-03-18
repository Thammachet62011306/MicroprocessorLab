#define INT_PIN 3
#define LED 2

int Blink_time=1000;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(INT_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INT_PIN), ISR_Callback,RISING);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(LED,LOW);
  delay(Blink_time);
  digitalWrite(LED,HIGH);
  delay(Blink_time);
}

void ISR_Callback()
{
  if(Blink_time<3000)
  {
    Blink_time+=1000;
  }
  else
  {
    Blink_time=1000;
  }
}
