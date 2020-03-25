#define PWM_MOTOR 6
#define INT_PIN 2
#define En_PIN 3

bool previous_read;
int count=0;
int Speed_INPUT=1;
String inString = "";

void setup()
{
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(6,OUTPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(INT_PIN), ISR_C, RISING);
  Serial.println("Started Encoder");
}

void loop()
{
  setSpeed(Speed_INPUT);
  if(Serial.available()>0)
  {
    inString=Serial.readString();
    Speed_INPUT=inString.toInt();
    setSpeed(Speed_INPUT);
  }
}

void ISR_C()
{
  count++;
  if(digitalRead(En_PIN)==0)
  {
    Serial.print("-");
  }
  else
  {
    Serial.print("+");
  }
  Serial.println(count);
}

void setSpeed(int a)
{
  if(a<=0)
  {
    digitalWrite(A1,LOW);
    digitalWrite(A2,HIGH);
  }
  else
  {
    digitalWrite(A1,HIGH);
    digitalWrite(A2,LOW);
  }
  analogWrite(PWM_MOTOR,ab(a));
}

int ab(int t)
{
  if(t<0)
    return t*-1;
  else
    return t;
}
