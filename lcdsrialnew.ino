#include <LiquidCrystal.h>
 
// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
 
// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
 
// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 if (adc_key_in < 50)   return btnRIGHT; 
 if (adc_key_in < 195)  return btnUP;
 if (adc_key_in < 380)  return btnDOWN;
 if (adc_key_in < 555)  return btnLEFT;
 if (adc_key_in < 790)  return btnSELECT;  
 return btnNONE;  // when all others fail, return this...
}
 ////////////////////////////////
// Use pins 5 through 12 as the digital outputs int output1 = 5;
  
 const byte lowLevel = 42;
 const byte highLevel = 43;
 const byte highPressureStorage = 44;
 int valve1 = 31;
 int air = 32;
 int DC = 33;
 int motor = 34;
 int valve2 = 35;
 int valve3 = 36;
 int backWash1 = 37;
 int backWash2 = 38;
 
int buttonPressTime = 250;   // Number of milliseconds to hold outputs o

void setup() {  
  ///////////////////////////////////lcd
   lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 lcd.print("Push the buttons"); // print a simple message
 //////////////////////////////////////////////////
 // Open the serial connection to listen for commands from the host 
  Serial.begin(38400); 
  // Set up the pins as outputs  
pinMode(valve1, OUTPUT);  
pinMode(air, OUTPUT); 
pinMode(DC, OUTPUT); 
pinMode(motor, OUTPUT); 
pinMode(valve2, OUTPUT);
pinMode(valve3, OUTPUT); 
pinMode(backWash1, OUTPUT);  
pinMode(backWash2, OUTPUT); // Make sure the outputs are all set LOW initally   digitalWrite(output1, LOW);  
digitalWrite(valve1, LOW);  
digitalWrite(air, LOW); 
digitalWrite(DC, LOW);  
digitalWrite(motor, LOW); 
digitalWrite(valve3, LOW);  
 digitalWrite(backWash1, LOW);
   digitalWrite(backWash2, LOW); 
}






void loop() {  
  /////////////////////////
  lcd.setCursor(9,1);            // move cursor to second line "1" and 9 spaces over
 lcd.print(millis()/1000);      // display seconds elapsed since power-up
 
 
 lcd.setCursor(0,1);            // move to the begining of the second line
 lcd_key = read_LCD_buttons();  // read the buttons
 switch (lcd_key)               // depending on which button was pushed, we perform an action
 {
   case btnRIGHT:
     {
     lcd.print("RIGHT ");
     break;
     }
   case btnLEFT:
     {
     lcd.print("LEFT   ");
     break;
     }
   case btnUP:
     {
     lcd.print("UP    ");
     break;
     }
   case btnDOWN:
     {
     lcd.print("DOWN  ");
     break;
     }
   case btnSELECT:
     {
     lcd.print("SELECT");
     break;
     }
     case btnNONE:
     {
     lcd.print("NONE  ");
     break;
     }
 }
 /////////////////////////////
 byte val;   // Check if a value has been sent by the host   
if(Serial.available()) {  
   val = Serial.read();  
    if(val == '1') {       // Pulse the 1st button  
     Serial.println("Output 1 ON");  
     digitalWrite(valve1, HIGH);   
    delay(buttonPressTime);  
     digitalWrite(valve1, LOW);  
     Serial.println("Output 1 OFF"); 
 
 
    }
 else if(val == '2') {       // Pulse the 2nd button  
   lcd.println("Output 2 ON");    
   digitalWrite(air, HIGH);    
   delay(buttonPressTime);     
   digitalWrite(air, LOW);  
   lcd.println("Output 2 OFF");  
   } 
  else if(val == '3') {       // Pulse the 3rd button    
     lcd.println("Output 3 ON");   
      digitalWrite(DC, HIGH);   
      delay(buttonPressTime);   
      digitalWrite(DC, LOW);   
    lcd.println("Output 3 OFF");   
  }
 else if(val == '4') {       // Pulse the 4th button  
     Serial.println("Output 4 ON");   
    digitalWrite(motor, HIGH); 
      delay(buttonPressTime);      
 digitalWrite(motor, LOW);    
   lcd.println("Output 4 OFF"); 
    } else if(val == '5') {       // Pulse the 5th button
       Serial.println("Output 5 ON");    
       digitalWrite(valve3, HIGH);   
       delay(buttonPressTime);  
       digitalWrite(valve3, LOW);     
       lcd.println("Output 5 OFF");   
  
  } else if(val == '6') {       // Pulse the 6th button       Serial.println("Output 6 ON");   
    digitalWrite(backWash1, HIGH);     
    delay(buttonPressTime); 
    digitalWrite(backWash1, LOW);    
    lcd.println("Output 6 OFF");  
   } 
else if(val == '7') {  // Pulse the 7th button    
      lcd.println("Output 7 ON");    
      digitalWrite(backWash2, HIGH); 
      delay(buttonPressTime);    
      digitalWrite(backWash2, LOW);    
      lcd.println("Output 7 OFF");   
   }
 
        } 
    }
