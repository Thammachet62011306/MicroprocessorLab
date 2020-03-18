int clk_pin=13;//SHCP
int latch_pin=10;//STCP
int data_pin=11;//DS
int count =0;
int timer1_counter;

long data[10] = {111111101, 101100000, 111011010, 111110010, 101100111, 110110111
                , 110111111, 111100001, 111111111 , 111110111
               };
long temp;

void setLed()
{
  digitalWrite(latch_pin,LOW);
  temp=data[count];
  for(int i=0;i<8;i++)
  {
    digitalWrite(data_pin,temp%10);
    digitalWrite(clk_pin,HIGH);
    digitalWrite(clk_pin,LOW);
    temp=temp/10;
  }
  digitalWrite(latch_pin,HIGH);
}
void setup()
{
  //put your setup code here,to run once:
  pinMode(clk_pin,OUTPUT);
  pinMode(latch_pin,OUTPUT);
  pinMode(data_pin,OUTPUT);
  setLed();
  noInterrupts();
  TCCR1A=0;
  TCCR1B=0;
  
  timer1_counter = 0;
  TCNT1 = timer1_counter;
  TCCR1B |= (1<<CS12);
  TIMSK1 |= (1<<TOIE1);
  
  interrupts();
}

ISR(TIMER1_OVF_vect)
{
  TCNT1=timer1_counter;
  count++;
  if(count>9)
  {
    count=0;
  }
}

void loop()
{
  setLed();
}
