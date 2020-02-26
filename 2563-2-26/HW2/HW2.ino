#include<SPI.h>
#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>
#include<ThreeWire.h>
#include<RtcDS1302.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

ThreeWire myWire(4, 5, 2);
RtcDS1302<ThreeWire> Rtc(myWire);

void setup()
{
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //initialize I2C addr 0x3c
  display.clearDisplay(); // clears the screen and buffer

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 6);
  display.println("SW1");
  display.drawCircle(64, 12, 12, WHITE);
  display.setCursor(0, 30);
  display.setTextSize(2);
  display.println("SW2");
  display.drawCircle(64, 36, 12, WHITE);
  display.setTextColor(BLACK, WHITE);
  display.display();

  Rtc.Begin();
  RtcDateTime setting_time(2020, 2, 26, 10, 48, 50);
  printDateTime(setting_time);
  Rtc.SetDateTime(setting_time);
}
void loop() {
  RtcDateTime now = Rtc.GetDateTime();
  printDateTime(now);
  delay(100);
}
void printDateTime(const RtcDateTime& dt)
{
  display.clearDisplay(); // clears the screen and buffer
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 6);
  display.print(dt.Hour(), DEC);
  display.print(':');
  display.print(dt.Minute(), DEC);
  display.print(':');
  display.print(dt.Second(), DEC);
  display.println();
  display.setCursor(0, 30);
  display.setTextSize(1);
  display.setTextColor(BLACK, WHITE);
  display.print(dt.Year(), DEC);
  display.print("/");
  display.print(dt.Month(), DEC);
  display.print("/");
  display.print(dt.Day(),DEC);
  display.display();

}
