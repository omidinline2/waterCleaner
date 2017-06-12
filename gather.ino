 #include <LiquidCrystal.h>
 
 LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
 
 int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
 
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);       
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 if (adc_key_in < 50)   return btnRIGHT; 
 if (adc_key_in < 195)  return btnUP;
 if (adc_key_in < 380)  return btnDOWN;
 if (adc_key_in < 555)  return btnLEFT;
 if (adc_key_in < 790)  return btnSELECT;  
 return btnNONE;  // when all others fail, return this...
}


/////////////serial
int buttonPressTime = 250;   // Number of milliseconds to hold outputs o

 ///////////////////Flower 
 volatile int flow_frequency; // Measures flow sensor pulses
unsigned int l_hour; // Calculated litres/hour
unsigned char flowsensor = 2; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
void flow () // Interrupt function
{
   flow_frequency++;
}
///////////////////////////// temp
// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 46 
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
//////////////////////// machine

   
 int valve1 = 31;
 const byte lowLevel = 42;
 const byte highLevel = 43;
 const byte highPressureStorage = 44;
 int air = 32;
 int DC = 33;
 int motor = 34;
 int valve2 = 35;
 int valve3 = 36;
 int backWash1 = 37;
 int backWash2 = 38;
 
const byte LED=13; // LED (built-in on Uno)
 
unsigned long buttonPushedMillis; // when button was released
unsigned long ledTurnedOnAt; // when led was turned on
unsigned long turnOnDelay = 0; // wait to turn on LED
unsigned long turnOffDelay = 5000; // turn off LED after this time
bool ledReady = false; // flag for when button is let go
bool ledState = false; // for LED is on or not.

///////////////////////////////
void setup()
{
 
  //////////////// flower
   pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
   Serial.begin(9600);
   attachInterrupt(0, flow, RISING); // Setup Interrupt
   sei(); // Enable interrupts
   currentTime = millis();
   cloopTime = currentTime;
////////////////////// temp
   // start serial port 
sensors.begin(); 
 //////////////////// machine
 pinMode(valve1, OUTPUT);
pinMode(air, OUTPUT);
pinMode(DC, OUTPUT);
pinMode(valve2, OUTPUT);
pinMode(valve3, OUTPUT);
pinMode(motor, OUTPUT);

digitalWrite(valve1, 1);
digitalWrite(air, 1);
digitalWrite(DC, 1);
digitalWrite(valve2, 1);
digitalWrite(valve3, 1);
digitalWrite(motor, 1);

 pinMode(highPressureStorage, INPUT_PULLUP);
 pinMode(highLevel, INPUT_PULLUP);
 pinMode(lowLevel, INPUT_PULLUP);
 pinMode(LED, OUTPUT);
 digitalWrite(LED, LOW);
///////////////////////////////////////
  
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 lcd.print("Push the buttons"); // print a simple message
 lcd.clear();
}
  
void loop()
{
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

         else {
       
  //////////////flower  //////////////flower  //////////////flower
  //////////////flower  //////////////flower  //////////////flower
   currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
      cloopTime = currentTime; // Updates cloopTime
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      flow_frequency = 0; // Reset Counter
      lcd.setCursor(0,0);
      lcd.print("Masraf: ");
      lcd.print(l_hour, DEC);  
      lcd.println(":L/h");
   }
////////////////////////////// temp
 sensors.requestTemperatures(); // Send the command to get temperature readings 
 lcd.setCursor(0,1);           
 lcd.print("Temp = ");
 lcd.print(sensors.getTempCByIndex(0));
 lcd.setCursor(14,1);             
 lcd.print("*C");
   ////////////////machine
     
             unsigned long currentMillis = millis(); 
             if (digitalRead(highLevel) == LOW) {
                  digitalWrite(valve1, HIGH);
                  buttonPushedMillis = currentMillis;
                  ledReady = true;
             }
             else if (digitalRead(lowLevel) == LOW  ){
                   digitalWrite(valve1, LOW);
                   digitalWrite(valve2, HIGH); ///khamosh
                   digitalWrite(valve3, HIGH);
                   digitalWrite(motor, HIGH);   
             }
            else if (digitalRead(highPressureStorage) == LOW || digitalRead(air) == LOW || digitalRead(DC)==  LOW || digitalRead(valve1)==LOW ){
                    
                   digitalWrite(valve2, HIGH); ///khamosh
                   digitalWrite(valve3, HIGH);
                   digitalWrite(motor, HIGH);   
             }
            else if (digitalRead(highPressureStorage) == HIGH && digitalRead(lowLevel) == HIGH && digitalRead(highLevel) == HIGH  ){
                    digitalWrite(valve2, LOW); ///khamosh
                   digitalWrite(valve3, LOW);
                   digitalWrite(motor, LOW);  
      
             }
             if (ledReady) {
                if ((unsigned long)(currentMillis - buttonPushedMillis) >= turnOnDelay) {
                  digitalWrite(air, LOW);
                  digitalWrite(DC, LOW);                  
                  ledState = true;
                  ledTurnedOnAt = currentMillis;
                  ledReady = false;
               }
             }

              if (ledState) {
                if ((unsigned long)(currentMillis - ledTurnedOnAt) >= turnOffDelay) {
                 ledState = false;
                 digitalWrite(air, HIGH);
                 digitalWrite(DC, HIGH);
                 digitalWrite(valve2, LOW);
                 digitalWrite(valve3, LOW);
                 digitalWrite(motor, LOW); 

                 }
             }
 
 ///////////////////////  LCD shield buttons
 lcd.setCursor(0,1);            
 lcd_key = read_LCD_buttons();   
 
 switch (lcd_key)               
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
     lcd.print("");
     break;
     }
 }
 
}
}
