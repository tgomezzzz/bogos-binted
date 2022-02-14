#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define LTRED   0xFC10
#define LTBLUE  0x841F
#define LTGRAY  0xC618
#define LTGREEN 0x87F0
#define BROWN   0x8200
#define ORANGE  0xFC00
unsigned int firstColors[7] = {BLUE, GREEN, CYAN, LTBLUE, LTGRAY, LTGREEN, BROWN};
unsigned int secondColors[6] = {RED, MAGENTA, YELLOW, WHITE, LTRED, ORANGE};
unsigned int firstColor;
unsigned int secondColor;

char firstText[] = {'H', 'e', 'y', '!', ' ', 'D', 'i', 'd', ' ', 'y', 'o', 'u', ' ', 'g', 'e', 't',
                   ' ', 't', 'h', 'e', 'p', 'h', 'o', 't', 'o', 's', ' ', 'p', 'r', 'i', 'n',
                   't', 'e', 'd', '?'};
char *secondText = "bogos binted?";
char thirdText[] = {'.', '.', '.', ' ', 'W', 'h', 'a', 't', '?'};

void setup(void) {
  tft.init();
  tft.setRotation(1);
  Serial.begin(9600);
  randomSeed(analogRead(5)); 
  tft.setTextColor(TFT_BLACK);
  firstColor = pickColor(firstColors, 7);
  secondColor = pickColor(secondColors, 6);
}

void loop() {
  tft.fillScreen(firstColor);

  int xPos = 10;
  int yPos = (tft.height() / 2) - 13;
  for (int i = 0; i < 35; i++) {
    xPos += tft.drawChar(firstText[i], xPos, yPos, 4);
    if (xPos > tft.width() - 10) {
      xPos = 10;
      yPos += 26;
    }
    delay(150);
  }

  delay(2000);
  tft.fillScreen(secondColor);
  xPos = tft.width() + 10;
  yPos = tft.height() / 2;
  for (xPos = tft.width() + 10; xPos > -160; xPos--) {
    tft.fillRect(xPos, yPos, tft.width(), 30, secondColor);
    tft.drawString(secondText, xPos, yPos, 4);
    delay(10);
  }
  tft.fillScreen(secondColor);
  delay(2000);

  tft.fillScreen(firstColor);
  xPos = 60;
  yPos = tft.height() / 2;
  for (int i = 0; i < 9; i++) {
    xPos += tft.drawChar(thirdText[i], xPos, yPos, 4);
    if (i < 4) {
      delay(300);
    } else {
      delay(150);
    }
  }
  delay(2000);
  firstColor = pickColor(firstColors, 7);
  secondColor = pickColor(secondColors, 6);


}

unsigned int pickColor(unsigned int colors[], int size) {
  int color = random(size);
  return colors[color];
}
