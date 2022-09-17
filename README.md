# KalaKritiHTM3.0

// Sck of OLED is connected to D1 or GPIO 5 & SDA of OLED is connected to D2 or GPIO 4

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1                                 //  This for reset. It is not Important to write                // OLED rest in node mcu mean write -1 and in Uno its 4
#define WIRE Wire

int sensor = A0;
//int fan = 13 ;                                  //13 is GPIO pin  in NodeMcu & D7 is digital pin in Node Mcu
//int relay = 13;                               //13 is GPIO pin  in NodeMcu & D7 is digital pin in Node Mcu
int buzzer = 16;                            //16 is GPIO pin  in NodeMcu & D0 is digital pin in Node Mcu
int red = 13;                                //2 is GPIO pin  in NodeMcu & D4 is digital pin in Node Mcu
int green = 12;                             //14 is GPIO pin  in NodeMcu & D5 is digital pin in Node Mcu
int blue = 14;                            //12 is GPIO pin  in NodeMcu & D6 is digital pin in Node Mcu
int gasLevel = 0;                                  //int variable for gas level
String quality = "";

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &WIRE);



//char auth[] = " rT_MtHSAJNYZEb2mnKe-VJ8pxw8iMYkR";
//char ssid[] = "ATL";
//char pass[] = "ATL@bgnR";

void setup()
{

  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5,20);
  display.print("Kala-Kriti");
  display.setCursor(0,0);
  display.display();
  delay(4000);

  pinMode(buzzer, OUTPUT);                       //set beeper for output
  pinMode(sensor, INPUT);                       //set sensor for input
  //pinMode (relay, OUTPUT);
  //pinMode (fan, OUTPUT);
  pinMode (red, OUTPUT);
  pinMode (green, OUTPUT);
  pinMode (blue, OUTPUT);
  //Blynk.begin(auth, ssid, pass);
  //timer.setInterval(1000L, gassensor); // new data will be updated every 10 sec
  delay(1000);
}


void loop()
{

  gasLevel = analogRead(sensor);
  Serial.print(" Gas Level:");
  Serial.println(gasLevel);
  digitalWrite (green, LOW);
  digitalWrite (red, LOW);
  digitalWrite (blue, LOW);
  digitalWrite (buzzer, LOW);
  //digitalWrite (fan, LOW);
  //digitalWrite (relay, HIGH);


  if (gasLevel < 400) {
    quality = "GOOD";
    //digitalWrite(relay, HIGH);
    digitalWrite (green, HIGH);
    delay(500);
  }

  else if (gasLevel > 400 and gasLevel < 500) {
    quality = "Unhealthy";
    //digitalWrite(relay, LOW);
    //digitalWrite(fan, HIGH);
    digitalWrite (blue, HIGH);
    tone(buzzer, 800, 50);
    delay(200);
  }

  else if (gasLevel > 500) {
    quality = "Hazardous ";
    //digitalWrite(relay, LOW);
    //digitalWrite(fan, HIGH);
    digitalWrite (red, HIGH);
    digitalWrite( buzzer, HIGH);
    delay(200);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(5, 5);
  display.setTextSize(1);
  display.print("Air Quality is: ");
  display.setCursor(100, 5);
  display.setTextSize(1);
  display.print(gasLevel);
  display.setTextSize(2);
  display.setCursor(10, 30);
  display.println(quality);
  display.display();
  delay(500);
}
