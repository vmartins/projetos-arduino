#include <Adafruit_ST7735.h>

const int PIN_CLK = 5;
const int PIN_SDA = 7;
const int PIN_RS = 4;
const int PIN_RST = 3;
const int PIN_CS = 2;

Adafruit_ST7735 tft = Adafruit_ST7735(PIN_CS, PIN_RS, PIN_SDA, PIN_CLK, PIN_RST);

void setup(void) {
  tft.initR(INITR_BLACKTAB);
}

void loop() {
  delay(1500);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 10);
  
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.println("Texto #1");

  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println("Texto #2");

  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Texto #3");

  tft.setTextWrap(false); // desabilita quebra de linha
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(5);
  tft.println("Texto #4");

  // x, y, largura, altura, cor
  tft.drawRect(1, 120, 20, 30, ST77XX_WHITE);
  tft.fillRect(25, 120, 20, 30, ST77XX_YELLOW);

  // x, y, raio, cor
  tft.drawCircle(60, 135, 10, ST77XX_RED);
  tft.fillCircle(85, 135, 10, ST77XX_GREEN); 
}
