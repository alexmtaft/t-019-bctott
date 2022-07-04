
#include "SPI.h"

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv screen;


#define ledcount

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF 
#define GREY    0x7BEF

/* from pins_arduino.h
#define PIN_SPI_SS    (53)
#define PIN_SPI_MOSI  (51)
#define PIN_SPI_MISO  (50)
#define PIN_SPI_SCK   (52)
*/


uint16_t ID;

#define TIME_BUF_SIZE 300
#define SCREEN_TIME_X_START 300
#define SCREEN_TIME_Y_START 400
#define SCREEN_TIME_YSCALE 4

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
 // pinMode(CS, OUTPUT);
  
 // digitalWrite(CS, 1);
  SPI.begin();
  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
  
  // setup screen
  Serial.begin(9600);
  screen.reset();
  ID = screen.readID();
  Serial.print("TFT ID = 0x");
  Serial.println(ID, HEX);
    //    if (ID == 0x00D3) ID = 0x9481; // write-only shield
  if (ID == 0x00D3) ID = 0x9486; // write-only shield
  screen.begin(ID);
  screen.setRotation(0);
  screen.fillScreen(BLUE);
  
  
}

  uint8_t sec[TIME_BUF_SIZE] = {0};
  uint8_t min[TIME_BUF_SIZE] = {0};
  uint8_t hor[TIME_BUF_SIZE] = {0};
  void incBuf(uint8_t *buf){

    for(int i = TIME_BUF_SIZE-1; i > 0; i--){
      buf[i] = buf[i-1];
    }
  }

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  //delay(2000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  //delay(10);                       // wait for a second

  uint8_t countEn = 1;
  uint8_t b = Serial.read();
  if(b == 's'){
    countEn = 1;
  }
  else if(b == 'e'){
    countEn = 0;
  }
  //Serial.println(ID, HEX);
  Serial.println(b);

 // digitalWrite(CS, 1);
  static uint8_t z = 6;
  static uint8_t y = 15;
  static uint8_t x = 0;

  SPI.transfer(x);
  //digitalWrite(CS, 0);
  
  #ifdef ledline
  x = x<<1;
  if (x==0x40){ x = 1;
  }
  #endif
  


  #ifdef ledcount
  if(countEn == 1){
    x += 1;
    if(x == 61){
      x = 0;
      //incBuf(min);
      y += 1;  
      if(y == 61){
        y = 0;
        z += 1;
        if(z == 12){
          z = 0;
        }
      }
    }
    screen.setTextSize(4);
    screen.setCursor(0,10);
    screen.setTextColor(MAGENTA,BLUE);
    screen.print("hr :");
    screen.println(z);
    screen.setTextColor(RED,BLUE);
    screen.print("min:");
    screen.println(y);
    screen.setTextColor(WHITE,BLUE);
    screen.print("sec:");
    screen.print(x);
   
    //incBuf();
    //sec[0] = x;
    
  }
  #endif

uint8_t drawTimeEn = 1;
if(drawTimeEn == 1){

  incBuf(hor);
  hor[0] = z;
  for(int i = 0; i < TIME_BUF_SIZE-1; i++){
    screen.drawPixel(SCREEN_TIME_X_START-i,SCREEN_TIME_Y_START-SCREEN_TIME_YSCALE*5*hor[i+1],BLUE);
    screen.drawPixel(SCREEN_TIME_X_START-i,SCREEN_TIME_Y_START-SCREEN_TIME_YSCALE*5*hor[i],MAGENTA);
  }

/*
  for(int i = 0; i < TIME_BUF_SIZE-1; i++){
    screen.drawPixel(SCREEN_TIME_X_START-i,SCREEN_TIME_Y_START-2*min[i],BLUE);
  }
  incBuf(min);
  min[0] = y;
  for(int i = 0; i < TIME_BUF_SIZE-1; i++){
    screen.drawPixel(SCREEN_TIME_X_START-i,SCREEN_TIME_Y_START-2*min[i],RED);
  }
  */
  incBuf(min);
  min[0] = y;
  for(int i = 0; i < TIME_BUF_SIZE-1; i++){
    screen.drawPixel(SCREEN_TIME_X_START-i,SCREEN_TIME_Y_START-SCREEN_TIME_YSCALE*min[i+1],BLUE);
    screen.drawPixel(SCREEN_TIME_X_START-i,SCREEN_TIME_Y_START-SCREEN_TIME_YSCALE*min[i],RED);
  }
    //screen.fillScreen(BLUE);

  /*
  for(int i = 0; i < TIME_BUF_SIZE-1; i++){
    screen.drawPixel(SCREEN_TIME_X_START-i,SCREEN_TIME_Y_START-2*sec[i],BLUE);
  }
  incBuf(sec);
  sec[0] = x;
  for(int i = 0; i < TIME_BUF_SIZE-1; i++){
    screen.drawPixel(SCREEN_TIME_X_START-i,SCREEN_TIME_Y_START-2*sec[i],WHITE);
  }
  */

  incBuf(sec);
  sec[0] = x;
  for(int i = 0; i < TIME_BUF_SIZE-1; i++){
    screen.drawPixel(SCREEN_TIME_X_START-i,SCREEN_TIME_Y_START-SCREEN_TIME_YSCALE*sec[i+1],BLUE);
    screen.drawPixel(SCREEN_TIME_X_START-i,SCREEN_TIME_Y_START-SCREEN_TIME_YSCALE*sec[i],WHITE);
  }

}

}


