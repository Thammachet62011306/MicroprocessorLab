#define PWM_MOTOR 6
#define INT_PIN 2
#define En_PIN 3
#define LED 4

#define CLOCK_PIN 13 //SHCP
#define SS_PIN_1 10 //STCP
#define DATA_PIN 11 //DS
#define SS_PIN_2 9 //DS

bool previous_read;
int pos=0;
int sp=0;
String inString = "";
int PID=1;
int derivative;
int proportional;
int intergral;
int last_proportional;
char number[10]= {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
int n;



void setup()
{
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(A3,INPUT);
  pinMode(CLOCK_PIN,OUTPUT);
  pinMode(SS_PIN_1,OUTPUT);
  pinMode(DATA_PIN,OUTPUT);
  pinMode(SS_PIN_2,OUTPUT);
  Serial.begin(9600);
  Serial.println("Started Encoder");
  cli(); // stop interrupts
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 50 Hz increments
  OCR1A = 39999; // = 16000000 / (8 * 50) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 8 prescaler
  TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts
  attachInterrupt(digitalPinToInterrupt(INT_PIN), ISR_C, RISING);
}

void loop()
{
  sp=analogRead(A3);
  delay(100);
}

ISR(TIMER1_COMPA_vect){//timer0 interrupt 2kHz toggles pin 8
//generates pulse wave of frequency 2kHz/2 = 1kHz (takes two cycles for full wave- toggle high then toggle low)
  proportional=pos-sp;
  derivative=proportional-last_proportional;
  last_proportional=proportional;
  intergral+=proportional;
  PID=proportional*15+derivative*1.5+intergral*0.0001;
  if(PID==0)
  {
    PID=1;
  }
  setSpeed(PID);
  Serial.print(sp);
  Serial.print(",");
  Serial.println(pos);
  //Serial.print(",");
  //Serial.println(PID);
}


void ISR_C()
{
  if(digitalRead(En_PIN)==0)
  {
    pos--;
  }
  else
  {
    pos++;
  }
  if(pos<0)
    digitalWrite(LED,HIGH);
  else
  {
  	digitalWrite(LED,LOW);
    n=pos/100;
    spi_write_1(number[n%10]);
    n=n/10;
    spi_write_2(number[n%10]);
  }
}

void setSpeed(int a)
{
  if(a<=0)
  {
    digitalWrite(A1,HIGH);
  	digitalWrite(A2,LOW);
  }
  else
  {
    digitalWrite(A1,LOW);
  	digitalWrite(A2,HIGH);
  }
  if(ab(a)>255)
  {
     analogWrite(PWM_MOTOR,255);
  }
  else
  {
    analogWrite(PWM_MOTOR,ab(a));
  }
}

int ab(int t)
{
  if(t<0)
    return t*-1;
  else
    return t;
}

void spi_write_1(unsigned char cData)
{
  shiftOut(DATA_PIN,CLOCK_PIN,MSBFIRST,cData);
  digitalWrite(SS_PIN_1,HIGH);
  digitalWrite(SS_PIN_1,LOW);
}
void spi_write_2(unsigned char cData)
{
  shiftOut(DATA_PIN,CLOCK_PIN,MSBFIRST,cData);
  digitalWrite(SS_PIN_2,HIGH);
  digitalWrite(SS_PIN_2,LOW);
}