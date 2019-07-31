/***************************************************
  This is our library for the Adafruit HX8357D Breakout
  ----> http://www.adafruit.com/products/2050

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"
#include <math.h>

// These are 'flexible' lines that can be changed
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST -1 // RST can be set to -1 if you tie it to Arduino's reset - Didn't physically tie anything, might need to check this

// Use hardware SPI (on Uno & Nano, #13, #12, #11) and the above for CS/DC
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);

// SoftSPI - note that on some processors this might be *faster* than hardware SPI!
//Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, MOSI, SCK, TFT_RST, MISO);

float rpm = 500;
float clt = 50;
int skips = 0;        // Used to set how many times RPM updates before CLT does
int screen_state = 0; // 0 = black background, 1 = red background
int flash = 0;        // Used to detect when set blue is called the first time 

// LED assignments
const int LED_G_1 = A5;
const int LED_G_2 = A4;
const int LED_G_3 = A3;
const int LED_G_4 = A2;
const int LED_R_5 = A1;
const int LED_R_6 = A0;
const int LED_R_7 = 2;
const int LED_R_8 = 3;
const int LED_R_9 = 4;
const int LED_B_10 = 5;
const int LED_B_11 = 6;
const int LED_B_12 = 7;
const int LED_B_13 = 8;

// Button assignments
const int button_L = A6;

void setup() {
  Serial.begin(9600);
  Serial.println("HX8357D Test!"); 
  tft.begin();

  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(HX8357_RDPOWMODE);

  set_black();

  // Setting up each of the pins as LED outputs
  pinMode(LED_G_1, OUTPUT);
  pinMode(LED_G_2, OUTPUT);
  pinMode(LED_G_3, OUTPUT);
  pinMode(LED_G_4, OUTPUT);
  pinMode(LED_R_5, OUTPUT);
  pinMode(LED_R_6, OUTPUT);
  pinMode(LED_R_7, OUTPUT);
  pinMode(LED_R_8, OUTPUT);
  pinMode(LED_R_9, OUTPUT);
  pinMode(LED_B_10, OUTPUT);
  pinMode(LED_B_11, OUTPUT);
  pinMode(LED_B_12, OUTPUT);
  pinMode(LED_B_13, OUTPUT);

  // Setting up the buttons
  pinMode(button_L, INPUT_PULLUP);
}


void loop(void) {
    update_screen();  // Changes displayed values


    if (clt > 107)            // This is the high alert warning threshold
    {
      screen_state = 1;
      set_black();
      set_red();
    }
    else if (clt > 100)       // This is the caution threshold
    {
      if (screen_state != 1)
      {
        set_red();
      }
      screen_state = 1;
    }
    else
    {
      if (screen_state != 0)
      {
        set_black();
      }
      screen_state = 0;
    }
    
    if (rpm > 12500)       // This is the upshift indication threshold
    {
      set_blue();
    }
    else
    {
      flash = 0;
    }


    // LED light up section
    if ((rpm > 600) & (rpm <= 12500))
    {
      digitalWrite(LED_G_1, HIGH);
    }
    else if (rpm <= 12500)
    {
      digitalWrite(LED_G_1, LOW);
    }
    if ((rpm > 600) & (rpm <= 12500))
    {
      digitalWrite(LED_G_2, HIGH);
    }
    else if (rpm <= 12500)
    {
      digitalWrite(LED_G_2, LOW);
    }
    if ((rpm > 1900) & (rpm <= 12500))
    {
      digitalWrite(LED_G_3, HIGH);
    }
    else if (rpm <= 12500)
    {
      digitalWrite(LED_G_3, LOW);
    }
    if ((rpm > 3200) & (rpm <= 12500))
    {
      digitalWrite(LED_G_4, HIGH);
    }
    else if (rpm <= 12500)
    {
      digitalWrite(LED_G_4, LOW);
    }
    if ((rpm > 4500) & (rpm <= 12500))
    {
      digitalWrite(LED_R_5, HIGH);
    }
    else if (rpm <= 12500)
    {
      digitalWrite(LED_R_5, LOW);
    }
    if ((rpm > 5800) & (rpm <= 12500))
    {
      digitalWrite(LED_R_6, HIGH);
    }
    else if (rpm <= 12500)
    {
      digitalWrite(LED_R_6, LOW);
    }
    if ((rpm > 7100) & (rpm <= 12500))
    {
      digitalWrite(LED_R_7, HIGH);
    }
    else if (rpm <= 12500)
    {
      digitalWrite(LED_R_7, LOW);
    }
    if ((rpm > 8400) & (rpm <= 12500))
    {
      digitalWrite(LED_R_8, HIGH);
    }
    else if (rpm <= 12500)
    {
      digitalWrite(LED_R_8, LOW);
    }   
    if ((rpm > 9700) & (rpm <= 12500))
    {
      digitalWrite(LED_R_9, HIGH);
    }
    else if (rpm <= 12500)
    {
      digitalWrite(LED_R_9, LOW);
    } 
    if ((rpm > 11000) & (rpm <= 12500))
    {
      digitalWrite(LED_B_10, HIGH);
    }
    else if (rpm <= 12500)
    {
      digitalWrite(LED_B_10, LOW);
    } 
    if ((rpm > 12000) & (rpm <= 12500))
    {
      digitalWrite(LED_B_11, HIGH);
    }
    else if (rpm <= 12500)
    {
      digitalWrite(LED_B_11, LOW);
    }                  
}

unsigned long set_black(){
  tft.fillScreen(HX8357_BLACK);                  // Setting the background colour
  tft.setTextColor(HX8357_WHITE, HX8357_BLACK);  // Setting the text colour
  tft.setRotation(1);                            // Setting orientation of screen

  tft.setTextSize(3);
  
  tft.setCursor(0, 0);
  tft.println("RPM:");

  tft.setCursor(0, 150);
  tft.println("CLT:");

  tft.setTextSize(8);
}

unsigned long set_blue(){
  // The code to flash LEDs goes here
  if (flash == 0)
  {
    flash = 1;
    digitalWrite(LED_B_12, HIGH);
    digitalWrite(LED_B_13, HIGH);
  }
  digitalWrite(LED_G_1, !digitalRead(LED_G_1));
  digitalWrite(LED_G_2, !digitalRead(LED_G_2));
  digitalWrite(LED_G_3, !digitalRead(LED_G_3));
  digitalWrite(LED_G_4, !digitalRead(LED_G_4));

  
  digitalWrite(LED_R_5, !digitalRead(LED_R_5));
  digitalWrite(LED_R_6, !digitalRead(LED_R_6));
  digitalWrite(LED_R_7, !digitalRead(LED_R_7));
  digitalWrite(LED_R_8, !digitalRead(LED_R_8));
  digitalWrite(LED_R_9, !digitalRead(LED_R_9));
  
  digitalWrite(LED_B_10, !digitalRead(LED_B_10));
  digitalWrite(LED_B_11, !digitalRead(LED_B_11));
  digitalWrite(LED_B_12, !digitalRead(LED_B_12));
  digitalWrite(LED_B_13, !digitalRead(LED_B_13));
}

unsigned long set_red(){
  tft.fillScreen(HX8357_RED);                  // Setting the background colour
  tft.setTextColor(HX8357_WHITE, HX8357_BLACK);  // Setting the text colour
  tft.setRotation(1);                            // Setting orientation of screen

  tft.setTextSize(3);
  
  tft.setCursor(0, 0);
  tft.println("RPM:");

  tft.setCursor(0, 150);
  tft.println("CLT:");

  tft.setTextSize(8);
}

unsigned long update_screen() {
  // Displaying RPM

  tft.setCursor(60, 50);
  tft.print((int)rpm);
  tft.print("  ");

  rpm = rpm + 50;
  if (rpm == 20000)
  {
    rpm = 500;
  }

  // Displaying CLT

  if (skips == 10)
  {
   tft.setCursor(120, 200);
   tft.print((int)clt);
   tft.print(" "); 
   skips = 0;  

   clt = clt;// + 1;
   if (clt == 120)
   {
    clt = 50;
   }
  }
  skips += 1;
}
