int clk_pin = 13; //SHCP
int latch_pin = 10; //STCP
int data_pin = 11; //DS
int count = 0;

long data[10] = {111111101, 101100000, 111011010, 111110010, 101100111, 110110111
                , 110111111, 111100001, 111111111 , 111110111
               };
long temp;

void setLed()
{
  digitalWrite(latch_pin, LOW);
  temp = data[count];
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(data_pin, temp % 10);
    digitalWrite(clk_pin, HIGH);
    digitalWrite(clk_pin, LOW);
    temp = temp / 10;
  }
  digitalWrite(latch_pin, HIGH);
}
void setup()
{
  //put your setup code here,to run once:
  pinMode(clk_pin, OUTPUT);
  pinMode(latch_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  setLed();
  Serial.begin(9600);
}
void loop()
{
  //put yourmaincodehere,torunrepeatedly:
  Serial.print("A : ");
  Serial.println(analogRead(A0));
  Serial.print("B : ");
  Serial.println(analogRead(A1));
  if(analogRead(A0)>=1000)
  {
    count++;
    delay(500);
  }
  if(analogRead(A1)>=1000)
  {
    count--;
    delay(500);
  }
  if (count > 9) count = 0;
  if (count < 0) count = 9;
  setLed();
}
