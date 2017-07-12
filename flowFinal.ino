
//Needed to access the eeprom read write functions
#include <EEPROM.h> 
 #include <avr/sleep.h>
 #include <avr/interrupt.h>
 long number2 = 987654321;

//This function will write a 4 byte (32bit) long to the eeprom at
//the specified address to address + 3.
void EEPROMWritelong(int address, long value)
      {
      //Decomposition from a long to 4 bytes by using bitshift.
      //One = Most significant -> Four = Least significant byte
      byte four = (value & 0xFF);
      byte three = ((value >> 8) & 0xFF);
      byte two = ((value >> 16) & 0xFF);
      byte one = ((value >> 24) & 0xFF);
      byte zero = ((value >> 32) & 0xFF);

      //Write the 4 bytes into the eeprom memory.
      EEPROM.write(address, four);
      EEPROM.write(address + 1, three);
      EEPROM.write(address + 2, two);
      EEPROM.write(address + 3, one);
      EEPROM.write(address + 4, zero);
  

      }

//This function will return a 4 byte (32bit) long from the eeprom
//at the specified address to address + 3.
long EEPROMReadlong(long address)
      {
      //Read the 4 bytes from the eeprom memory.
      long four = EEPROM.read(address);
      long three = EEPROM.read(address + 1);
      long two = EEPROM.read(address + 2);
      long one = EEPROM.read(address + 3);
      long zero = EEPROM.read(address + 4);

      //Return the recomposed long by using bitshift.
      return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF)+ ((zero << 32) & 0xFFFFFFFFFF);
      }
          
#include <LiquidCrystal.h>
  
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
unsigned int l_hour;  
unsigned char flowsensor = 2; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
volatile unsigned long isrCounter;
unsigned long pulseCount;
unsigned long stopCount = 100000;

void countP() 
{
isrCounter++;
}
          
          
void setup()
{

isrCounter = EEPROMReadlong(0);

   Serial.begin(9600);
   attachInterrupt(0, countP, RISING);  
}
void loop ()
{
 
long address=0;
currentTime = millis();
// Every second, calculate and print litres/hour
if(currentTime >= (cloopTime + 1000))
{
cloopTime = currentTime; // Updates cloopTime

 
unsigned long  pulseCount = isrCounter ;
lcd.setCursor(0,0); 
lcd.print(EEPROMReadlong(0)/590);
lcd.print("L");
EEPROMWritelong(address, pulseCount );
while (EEPROMReadlong(0)> 5900*100000  ){
  lcd.print("sleep");
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  cli();  // Disable interrupts
  sleep_mode();
    
}
address+=5;
  }
}
