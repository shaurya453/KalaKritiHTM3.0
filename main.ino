// Sck of OLED is connected to D1 or GPIO 5 & SDA of OLED is connected to D2 or GPIO 4

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1                                 //  This for reset. It is not Important to write                // OLED rest in node mcu mean write -1 and in Uno its 4
#define WIRE Wire
#include "ESP8266WiFi.h"
#include <ESP8266HTTPClient.h>
#include <Arduino.h>

int sensor = A0;
int buzzer = 16;                            //16 is GPIO pin  in NodeMcu & D0 is digital pin in Node Mcu
int red = 13;                                //2 is GPIO pin  in NodeMcu & D4 is digital pin in Node Mcu
int green = 12;                             //14 is GPIO pin  in NodeMcu & D5 is digital pin in Node Mcu
int blue = 14;                            //12 is GPIO pin  in NodeMcu & D6 is digital pin in Node Mcu
int gasLevel = 0;                            //int variable for gas level
String quality;

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &WIRE);

const char *WIFI_SSID = "YeagerEren";
const char *WIFI_PASSWORD = "pweu6570";

String boolData;
char strVal[10] = {0};

WiFiClient client;
HTTPClient httpClient;

void setup(){
  
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5,20);
  display.print("Kala-Kriti");
  display.setTextSize(1);
  display.setCursor(5,50);
  display.print("Connecting...");
  display.display();
  delay(1000);

  pinMode(buzzer, OUTPUT);                       //set beeper for output
  pinMode(sensor, INPUT);                       //set sensor for input
  pinMode (red, OUTPUT);
  pinMode (green, OUTPUT);
  pinMode (blue, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("Connected");
  Serial.println(WiFi.localIP());
  
  delay(1000);
  display.clearDisplay();
  display.display();
  
}

void loop(){
  
  gasLevel = analogRead(sensor);
  digitalWrite (green, LOW);
  digitalWrite (red, LOW);
  digitalWrite (blue, LOW);
  digitalWrite (buzzer, LOW);

  if (gasLevel <= 570) {
    itoa(gasLevel, strVal, 10);
    myFunction("http://kalakritioof.herokuapp.com/save/", "GOOD", "false", strVal, green);
    quality = ("Good");

  }

  else if (gasLevel > 570 and gasLevel < 650) {
    itoa(gasLevel, strVal, 10);
    myFunction("http://kalakritioof.herokuapp.com/save/", "UNHEALTHY", "true", strVal, blue);
    quality = ("Unhealthy");



  }

  else if (gasLevel > 650) {
    itoa(gasLevel, strVal, 10);
    myFunction("http://kalakritioof.herokuapp.com/save/", "HAZARDOUS", "true", strVal, red);
    quality = ("Hazardous");
    tone(16, 1000, 500);
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

void myFunction(String url, String quality, String boolData, String strVal, int led) {
  
  String URL = url + "/" + boolData + "/" + strVal + "/" + quality;
  digitalWrite(led, HIGH);

  httpClient.begin(client, URL);
  httpClient.POST(URL);
  Serial.println(URL);
  delay(100);

}
