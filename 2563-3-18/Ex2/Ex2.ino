#define INT_PIN 3
#define LED 2


int toggle=1;
int timer1_counter;
int Mode_Select=1;
int count=0;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(INT_PIN, INPUT);
  noInterrupts();
  TCCR1A=0;
  TCCR1B=0;
  
  timer1_counter = 0;
  TCNT1 = timer1_counter;
  TCCR1B |= (1<<CS12);
  TIMSK1 |= (1<<TOIE1);
  
  interrupts();
  attachInterrupt(digitalPinToInterrupt(INT_PIN), ISR_Callback,RISING);
  Serial.begin(9600);
}

ISR(TIMER1_OVF_vect)
{
  TCNT1=timer1_counter;
  if(count%Mode_Select==0)
  {
    digitalWrite(LED,toggle);
    toggle = !toggle;
  }
  count++;
}

void loop()
{
  
}

void ISR_Callback()
{
  if(Mode_Select<3)
  {
    Mode_Select+=1;
  }
  else
  {
    Mode_Select=1;
  }
  Serial.println(Mode_Select);
}
