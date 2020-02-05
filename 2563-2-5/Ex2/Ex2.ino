int clk_pin = 13; //SHCP
int latch_pin = 10; //STCP
int data_pin = 11; //DS
int count = 0;
int i;
char rx_byte = 0;


long data[10] = {111111101, 101100000, 111011010, 111110010, 101100111, 110110111
                 , 110111111, 111100001, 111111111 , 111110111
                };
long temp;

void setLed()
{
  digitalWrite(latch_pin, LOW);
  temp = data[i];
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
  setLed();
  Serial.begin(9600);
}
void loop()
{
  if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();       // get the character
    if ((rx_byte >= '0') && (rx_byte <= '9')) {
      i = rx_byte-'0';
    }
    else {
    }
  }
  //put yourmaincodehere,torunrepeatedly:
  setLed();
}
