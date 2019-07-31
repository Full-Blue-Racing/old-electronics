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

// Cannot serial print on this as this massively ruins/ effects the received data

#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"
#include <math.h>

// These are 'flexible' lines that can be changed
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST -1 // RST can be set to -1 if you tie it to Arduino's reset

// Use hardware SPI (on Uno & Nano, #13, #12, #11) and the above for CS/DC
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);

// SoftSPI - note that on some processors this might be *faster* than hardware SPI!
//Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, MOSI, SCK, TFT_RST, MISO);

int rpm = 0;
int rpm_temp;         // Temp values are used for input checks
int clt;
int clt_temp;
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

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

      // variables to hold the parsed data
char messageFromPC[numChars] = {0};
int integer1FromPC = 0;
int integer2FromPC = 0;

boolean newData = false;

 // USed for flashing
const long interval = 150;           // interval at which to blink (milliseconds)
unsigned long previousMillis = 0;        // will store last time LED was updated

void setup() {
  Serial.begin(9600);
  tft.begin();

  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(HX8357_RDPOWMODE);

  tft.setRotation(1);                            // Setting orientation of screen
  tft.setTextColor(HX8357_WHITE, HX8357_BLACK);  // Setting the text colour
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
    recvWithStartEndMarkers();
    if (newData == true) {
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
        showParsedData();
        newData = false;
    }
      

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
    


    // LED light up section
    if (rpm < 12500)
    {
      if (rpm > 600)
      {
        digitalWrite(LED_G_1, HIGH);
      }
      else
      {
        digitalWrite(LED_G_1, LOW);
      }
      if (rpm > 600)
      {
        digitalWrite(LED_G_2, HIGH);
      }
      else
      {
        digitalWrite(LED_G_2, LOW);
      }
      if (rpm > 1900)
      {
        digitalWrite(LED_G_3, HIGH);
      }
      else
      {
        digitalWrite(LED_G_3, LOW);
      }
      if (rpm > 3200)
      {
        digitalWrite(LED_G_4, HIGH);
      }
      else
      {
        digitalWrite(LED_G_4, LOW);
      }
      if (rpm > 4500)
      {
        digitalWrite(LED_R_5, HIGH);
      }
      else
      {
        digitalWrite(LED_R_5, LOW);
      }
      if (rpm > 5800)
      {
        digitalWrite(LED_R_6, HIGH);
      }
      else
      {
        digitalWrite(LED_R_6, LOW);
      }
      if (rpm > 7100)
      {
        digitalWrite(LED_R_7, HIGH);
      }
      else
      {
        digitalWrite(LED_R_7, LOW);
      }
      if (rpm > 8400)
      {
        digitalWrite(LED_R_8, HIGH);
      }
      else
      {
        digitalWrite(LED_R_8, LOW);
      }   
      if ((rpm > 9700) & (rpm <= 12500))
      {
        digitalWrite(LED_R_9, HIGH);
      }
      else
      {
        digitalWrite(LED_R_9, LOW);
      } 
      if (rpm > 11000)
      {
        digitalWrite(LED_B_10, HIGH);
      }
      else
      {
        digitalWrite(LED_B_10, LOW);
      } 
      if (rpm > 12000)
      {
        digitalWrite(LED_B_11, HIGH);
      }
      else
      {
        digitalWrite(LED_B_11, LOW);
      }
      digitalWrite(LED_B_12, LOW);
      digitalWrite(LED_B_13, LOW);  
      flash = 0;    
    }
    else
    {
      set_blue();
    }
}


//============

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,",");      // get the first part - the string
    rpm_temp = atoi(strtokIndx);     // convert this part to an integer
    strtokIndx = strtok(NULL, ",");
    clt_temp = atof(strtokIndx);     // convert this part to an integer
    if (((rpm_temp > 200) & (rpm_temp <= 20000)) & ((clt_temp > 0) & (clt_temp <= 200)))
    {
      rpm = rpm_temp;
      clt = clt_temp;
    }
}

//============

void showParsedData() {
    // Displaying RPM
    /*
    tft.setCursor(60, 50);     // Commented out because this corrupts? the serial data being sent
    tft.print(rpm);
    tft.print("  ");

    // Displaying CLT

    if (skips == 10)          // This controls the ratio at which rpm is updated relative to clt,
    {                         // Meaning the relative refresh rate is rpm:clt = skips:1
      tft.setCursor(120, 200);
      tft.print(clt);
      tft.print(" "); 
      skips = 0;  
    }
    skips += 1; */
}


unsigned long set_black(){
  tft.fillScreen(HX8357_BLACK);                  // Setting the background colour
}

unsigned long set_blue(){
  // The code to flash LEDs goes here, this doesnt affect the screen at all
  if (flash == 0)
  {
    digitalWrite(LED_G_1, HIGH);
    digitalWrite(LED_G_2, HIGH);
    digitalWrite(LED_G_3, HIGH);
    digitalWrite(LED_G_4, HIGH);
    
    digitalWrite(LED_R_5, HIGH);
    digitalWrite(LED_R_6, HIGH);
    digitalWrite(LED_R_7, HIGH);
    digitalWrite(LED_R_8, HIGH);
    digitalWrite(LED_R_9, HIGH);
    
    digitalWrite(LED_B_10, HIGH);
    digitalWrite(LED_B_11, HIGH);
    digitalWrite(LED_B_12, HIGH);
    digitalWrite(LED_B_13, HIGH);  
    flash = 1;  
  }
  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LEDs are off turn it on and vice-versa:
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
}

unsigned long set_red(){
  tft.fillScreen(HX8357_RED);                  // Setting the background colour

  tft.setTextSize(8);

  tft.setCursor(120, 100);
  tft.print(clt);
}
