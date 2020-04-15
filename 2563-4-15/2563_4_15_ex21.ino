#define PWM_MOTOR 6
#define INT_PIN_1 2
#define INT_PIN_2 3
#define LED 4

#define CLOCK_PIN 13 //SHCP
#define SS_PIN_1 10 //STCP
#define DATA_PIN 11 //DS
#define SS_PIN_2 9 //DS

bool previous_read;
int pos=0,last_pos=0;
int fbspeed=0;
int sp=0;
String inString = "";
char a[7],b[2];
double PID_Speed=1,PWM;
double derivative;
double proportional;
double intergral;
double last_proportional;
double rpmpulse=1;
char number[10]= {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67};
int n;
unsigned long previouse_millis=0;



void setup()
{
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,OUTPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(6,OUTPUT);
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
  attachInterrupt(digitalPinToInterrupt(INT_PIN_1), ISR_C, RISING);
  //attachInterrupt(digitalPinToInterrupt(INT_PIN_2), ISR_D, RISING);
}

void loop()
{
  unsigned long current_millis=millis();
  if(current_millis-previouse_millis>=100)
  {
    previouse_millis=current_millis;
    fbspeed=pos/0.1;
  	pos=0;
  }
  if(Serial.available())
  {
    inString=Serial.readString();    
    inString.toCharArray(a, 7);
    if(a[1]=='-')
    {
      b[0]=a[2];
      b[1]=a[3];
      String s(b);
      sp=s.toInt();
      sp=sp*-1;
    }
    else
    {
      b[0]=a[1];
      b[1]=a[2];
      String s(b);
      sp=s.toInt();
    }
 
    if(sp>15)
    {
      Serial.println("The program doesn't support that number setting... to 15");
      sp=15;
    }
    if(sp<-15)
    {
      Serial.println("The program doesn't support that number setting... to -15");
      sp=-15;
    }
    rpmpulse=sp*(5500/((30/4.0)*21));
  }
  Serial.print(a);
  Serial.print(" , ");
  Serial.print((double)fbspeed*(30/4.0)*21/5500.0);
  Serial.print(" , ");
  Serial.print(rpmpulse*(30/4.0)*21/5500.0);
  Serial.println(" rpm ");
}

ISR(TIMER1_COMPA_vect){
  proportional=fbspeed-rpmpulse;
  derivative=proportional-last_proportional;
  last_proportional=proportional;
  intergral+=proportional;
  PID_Speed=proportional*0.05+derivative*0.05+intergral*0.00004;
  PWM-=PID_Speed;
  if(PWM<1&&PWM>-1)
  {
    PWM=1;
  }
  setSpeed(-PWM);
  //Serial.print(PWM);
  //Serial.print(" , ");

  //Serial.println(PID);
}


void ISR_C()
{
  if(digitalRead(INT_PIN_2)==0)
  {
    pos--;
  }
  else
  {
    pos++;
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