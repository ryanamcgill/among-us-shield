#include <Vector.h>
#include <Adafruit_TFTLCD.h> 
#include <Adafruit_GFX.h>    
#include <TouchScreen.h>

#define LCD_CS A3 
#define LCD_CD A2 
#define LCD_WR A1 
#define LCD_RD A0 
#define LCD_RESET A4 

#define TS_MINX 120
#define TS_MAXX 900
#define TS_MINY 70
#define TS_MAXY 920

#define YP A2  
#define XM A3  
#define YM 8  
#define XP 9  

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define ORANGE  0xA233

#define TALK_W  10

#define BUTTON_COL1 10
#define BUTTON_ROW1 10
#define BUTTON_H    10
#define BUTTON_W    10

#define SCREEN_H    240
#define SCREEN_W    320

#define HEAD_OFFS_H  5
#define HEAD_OFFS_W  5 


#define TALK_R1 3
#define TALK_R2 23
#define TALK_H  40
#define TALK_O  3

#define TEXT_O  17
#define HEAD_O  10
//Setup TFT shield and touchscreen
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);


/**
 * Draws setup board and buttons
 */
void setup() {
  Serial.begin(9600);

  tft.reset(); 
  tft.begin(0x9341);
  tft.setRotation(1);
  tft.fillScreen(BLACK); // Background screen
  tft.fillRect(TALK_O,TALK_R1+10,SCREEN_W-20,TALK_H,WHITE);
  //tft.drawRect(TALK_O,TALK_R1,SCREEN_W-20,TALK_H,WHITE);
  tft.setCursor(40,TALK_R1+TEXT_O);
  tft.setTextColor(BLACK); // Text color
  tft.setTextSize(2);
  tft.print("yo ryan sus bro"); // Text above the button
  draw_head(5,5);

  
}


void loop() {
  TSPoint p = ts.getPoint(); 
  
  if (p.z > ts.pressureThreshhold) {
    // A touch is detected
    p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, 240);
       
    
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    if (p.x > BUTTON_COL1 && p.x < (BUTTON_COL1+BUTTON_W) &&
        p.y > BUTTON_ROW1 && p.y < (BUTTON_ROW1+BUTTON_H)) {
      // Button was pressed
      
    }
      

    delay(10);  
  }
}

void draw_head(uint16_t x, uint16_t y) {
  // Draw row by row
  boolean black_mat[16][16] = 
  {
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  };

  int16_t e_row = 0;
  for (int16_t row=0;row<16;row++) {
    int16_t e_col = 0;
    for (int16_t col=0; col<16; col++) {
      if (black_mat[col][row]) {
        tft.drawPixel(x+e_row,y+e_col,BLACK);
        tft.drawPixel(x+e_row+1,y+e_col,BLACK);
        tft.drawPixel(x+e_row+1,y+e_col+1,BLACK);
        tft.drawPixel(x+e_row,y+e_col+1,BLACK);       
      }
      e_col = e_col +2;
    }
    e_row = e_row+2;
  }

}





