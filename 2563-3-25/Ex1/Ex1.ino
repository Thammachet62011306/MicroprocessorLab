#define PWM_MOTOR 6

bool previous_read;
int count=0;
int Speed_INPUT=1;
String inString = "";

void setup()
{
  pinMode(2,INPUT_PULLUP);
  pinMode(A1,OUTPUT);
  pinMode(A2,OUTPUT);
  pinMode(6,OUTPUT);
  Serial.begin(9600);
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
  bool current_read = digitalRead(2);
  if((previous_read==0)&&(current_read==1))
  {
    count++;
    Serial.println(count);
  }
  previous_read=current_read;
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
