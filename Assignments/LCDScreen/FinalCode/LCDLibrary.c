// Imports
#include <LiquidCrystal.h>
#include <string.h>

// Init LiquidCrystal
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Params
// Dim and Brighten
int LCD_BACKLIGHT_PIN = 10;
int LCD_CONTRAST_PIN = 6;

int BACKLIGHT = 255;
int CONTRAST = 10;

// Text
// 0 - Static
// 1 - Scroll
// 2 - Blinking
char text_top[] = "This is";
char text_bottom[] = "Scrolling Text";
int text_mode = 2;
int text_delay = -1;

// Main Functions
void ScrollingText(char Text_Top[], char Text_Bottom[], int scroll_delay)
{
  text_mode = 1;
  text_delay = scroll_delay;
  strcpy(text_top, Text_Top);
  strcpy(text_bottom, Text_Bottom);
  
  lcd.setCursor(0,0);
  lcd.print(Text_Top);
  lcd.setCursor(0,1);
  lcd.print(Text_Bottom);
}

void StaticText(char Text_Top[], char Text_Bottom[])
{
  text_mode = 0;
  text_delay = -1;
  strcpy(text_top, Text_Top);
  strcpy(text_bottom, Text_Bottom);
  
  lcd.setCursor(0,0);
  lcd.print(Text_Top);
  lcd.setCursor(0,1);
  lcd.print(Text_Bottom);
}

void BlinkingText(char Text_Top[], char Text_Bottom[], int blink_delay)
{
  text_mode = 2;
  text_delay = blink_delay;
  strcpy(text_top, Text_Top);
  strcpy(text_bottom, Text_Bottom);
  
  lcd.setCursor(0,0);
  lcd.print(Text_Top);
  lcd.setCursor(0,1);
  lcd.print(Text_Bottom);
}

void Dim(int delay_val)
{
  for(int i=255;i>0;i--)
  {
    analogWrite(LCD_BACKLIGHT_PIN, i);
  	analogWrite(LCD_CONTRAST_PIN, 255-i);
    delay(delay_val);
  }
}

void Brighten(int delay_val)
{
  for(int i=0;i<255;i++)
  {
    analogWrite(LCD_BACKLIGHT_PIN, i);
  	analogWrite(LCD_CONTRAST_PIN, 255-i);
    delay(delay_val);
  }
}

// Util Functions


void setup() {
  // Set initial BACKLIGHT AND CONTRAST
  analogWrite(LCD_BACKLIGHT_PIN, BACKLIGHT);
  analogWrite(LCD_CONTRAST_PIN, CONTRAST);
  
  // LCD Columns and Rows
  lcd.begin(16, 2);
  /*
  lcd.setCursor(0,0);
  lcd.print("This is");
  lcd.setCursor(0,1);
  lcd.print("Scrolling Text");
  */
  
  //StaticText(text_top, text_bottom);
  ScrollingText(text_top, text_bottom, 1000);
  //BlinkingText(text_top, text_bottom, 1000);
  
  // Scroll
  if (text_mode == 1)
  {
    // Initial Scroll Right 16 times
    unsigned int i=0;
    while(i<16){ 
       if(i>=0)
      {lcd.command(0x1C);}
     delay(text_delay);
     i++;
     }

    for(int it=0;it<32;it++)
      lcd.command(0x18);
  }
  
}

void loop() {
  // Dim and Brighten
  Dim(10);
  Brighten(10);

  // Scroll
  if (text_mode == 1)
  {
    // Scroll Right 32 times
    unsigned int i=0;
    while(i<32){ 
       if(i>=0)
      {lcd.command(0x1C);}
     delay(text_delay);
     i++;
     }
	
    // Reset pos as -16
    for(int it=0;it<32;it++)
      lcd.command(0x18);
  }
  // Blinking
  else if(text_mode == 2)
  {
    for(int it=0;it<1;it++)
    {
      // Clear
      lcd.clear();
      
      // Delay
      delay(text_delay);
      
      // Rewrite
      lcd.setCursor(0,0);
      lcd.print(text_top);
      lcd.setCursor(0,1);
      lcd.print(text_bottom);
      
      // Delay
      delay(text_delay);
    }
  }
}