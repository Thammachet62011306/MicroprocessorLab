#include<SPI.h>

#define CLOCK_PIN 13 //SHCP
#define SS_PIN_1 10 //STCP
#define DATA_PIN 11 //DS
#define SS_PIN_2 9 //DS

int count = 0;

char number[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};

void spi_write_1(unsigned char cData)
{
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, cData);
  digitalWrite(SS_PIN_1, HIGH);
  digitalWrite(SS_PIN_1, LOW);
}
void spi_write_2(unsigned char cData)
{
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, cData);
  digitalWrite(SS_PIN_2, HIGH);
  digitalWrite(SS_PIN_2, LOW);
}

void setup()
{
  //put your setup code here,to run once:
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(SS_PIN_1, OUTPUT);
  pinMode(SS_PIN_2, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  //put yourmaincodehere,torunrepeatedly:

  if (digitalRead(A0) == 0)
  {
    count++;
    delay(1000);
  }
  if (digitalRead(A1) == 0)
  {
    count--;
    delay(1000);
  }
  if (digitalRead(A2) == 0)
  {
    count = 0;
    tone(6, 1000);
    delay(1000);
    noTone(6);
  }
  if (count > 99)
  {
    count = 0;

  }
  spi_set(count);
}
void spi_set(int n)
{
  spi_write_1(number[n % 10]);
  n = n / 10;
  spi_write_2(number[n % 10]);
}
