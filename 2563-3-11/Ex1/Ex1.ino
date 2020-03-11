char b[7];
int Led1=10;
int Led2=11;

void setup() {
  // put your setup code here, to run once:
  pinMode(Led1,OUTPUT);
  pinMode(Led2,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    String a = Serial.readString();
    a.toCharArray(b, 7);
    if(b[0]=='L')
    {
      if(b[1]=='1')
      {
        SetLed(1,convert(b));
      }
      if(b[1]=='2')
      {
        SetLed(2,convert(b));
      }
    }
  }
}

void SetLed(int f,int g)
{
  if(f==1)
  {
    analogWrite(Led1,map(g,0,100,0,255));
  }
  if(f==2)
  {
    analogWrite(Led2,map(g,0,100,0,255));
  }
}

int convert(char c[])
{
  char d[4];
  String e;
  for(int i=3;i<=5;i++)
  {
    d[i-3]=c[i];
  }
  e=String(d);
  return e.toInt();
}
