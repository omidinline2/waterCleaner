 
 
#include <LiquidCrystal.h>
#include "LcdKeypad.h"
#include "MenuData.h"
#include "Config.h"
#include <TimerOne.h>
#include <OneWire.h> 
      
         #define ALARM_PIN 22
          bool val  ;
          bool BizzarStop;
          bool flowIsWorking;
          bool pauseStateBtn = false;
          bool currentStateBtn = true;
          ///////////// 
          int buttonPressTime2 = 250;   // Number of milliseconds to hold outputs o
 ///////////////////Flower ///EEPROM
 // flow1
byte sensorInterrupt = 0;  // 0 = pin 2; 1 = pin 3
float calibrationFactor = 4.5;
volatile byte pulseCount2;  
float flowRate;
unsigned int flowMilliLitres;
unsigned long oldTime;

 //last pressed Btn
 uint8_t  EEPROMaddress = 50;
 int lastPressed;
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
 
unsigned int l_hour;  
 unsigned long currentTime;
unsigned long cloopTime;
volatile unsigned long isrCounter;
unsigned long pulseCount = 0;
  #include <avr/sleep.h>
void countP() 
{
isrCounter++;
}
          
          
 ////////////////////////// 
        
          const byte lowLevel = 42;
          const byte highLevel = 43;
          const byte highPressureStorage = 44;
          const byte backWash1In = 45;
        
          int valve1 = 31;
          int air = 32;
          int DC = 33;
          int motor = 34;
          int valve2 = 35; 
          int backWash1Out = 36;          
          int backWash2Out = 37;
          int valve4= 38;
          
          const byte LED=13; // LED (built-in on Uno)
          unsigned long buttonPushedMillis; // when button was released
          unsigned long buttonPushedMillis2; // when button was released
          unsigned long buttonPushedMillis3; // when button was released
          unsigned long buttonPushedMillisBizz = 0;
          unsigned long ledTurnedOnAt; // when led was turned on
          unsigned long ledTurnedOnAt2; // when led was turned on
          unsigned long ledTurnedOnAt3; // when led was turned on
          unsigned long turnOnDelay = 0; // wait to turn on LED
          unsigned long turnOffDelay = 7000; // turn off LED after this time
          unsigned long turnOnDelay2 = 0; // wait to turn on LED
          unsigned long turnOffDelay2 = 10000; // turn off LED after this time
          unsigned long turnOnDelay3 = 10000; // wait to turn on LED
          unsigned long turnOffDelay3 = 10000; // turn off LED after this time
          unsigned long turnOnDelayBizz = 10000; // wait to turn on LED
          bool ledReady = false; // flag for when button is let go
          bool ledState = false; // for LED is on or not.
          bool ledReady2 = false;  
          bool ledState2 = false;  
          bool ledReady3 = false;  
          bool ledState3 = false;  
           ///////////////////////////// temp
          // First we include the libraries
          
          #include <DallasTemperature.h>
          // Data wire is plugged into pin 2 on the Arduino 
          #define ONE_WIRE_BUS 46 
          // Setup a oneWire instance to communicate with any OneWire devices  
          // (not just Maxim/Dallas temperature ICs) 
          OneWire oneWire(ONE_WIRE_BUS); 
          // Pass our oneWire reference to Dallas Temperature. 
          DallasTemperature sensors(&oneWire);
         
 enum AppModeValues
{
  APP_NORMAL_MODE,
  APP_TIMER_RUNNING,
  APP_ALARM,
  APP_MENU_MODE,
  APP_PROCESS_MENU_CMD,
  APP_MENU_MODE_END
};
 
 
byte appMode = APP_NORMAL_MODE;

char strbuf[LCD_COLS + 1]; // one line of lcd display
long timerCurrentValue[3];
unsigned long alarmStartTime;
short timerFineGrainedCounter[3];
unsigned long lastMilliSecondTimerValue = 0;
char currentTimerIdx = 0;
byte btn;
Config currentConfig;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

MenuManager Menu1(cd_timer_menu_Root, menuCount(cd_timer_menu_Root));

void printTimerValue(byte timerIdx, byte showTimerName = false);

bool state = false;
void setup() {
  //
          ////////////////////// temp
          // start serial port 
          sensors.begin();            
            //////////////// flower && EPROM
           // flow1
           
            pulseCount2        = 0;
            flowRate          = 0.0;
            flowMilliLitres   = 0;
            oldTime           = 0;
          
           // attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  
          if (lastPressed = lowLevel){
            digitalWrite(valve1, LOW);
          }else if (lastPressed = highLevel){
            digitalWrite(valve1, HIGH);
          }
              // attachInterrupt(0, countP, RISING);  
               isrCounter = EEPROMReadlong(0);
        //////////////////// machine
          pinMode(valve1, OUTPUT);
          pinMode(air, OUTPUT);
          pinMode(DC, OUTPUT);
          pinMode(valve2, OUTPUT);
           
          pinMode(valve4, OUTPUT);
          pinMode(motor, OUTPUT);
          pinMode(backWash1Out, OUTPUT);
          pinMode(backWash2Out, OUTPUT);
          
         // digitalWrite(valve1, 1);
          digitalWrite(air, 1);
          digitalWrite(DC, 1);
          digitalWrite(valve2, 1);
          
          digitalWrite(valve4, 1);
          digitalWrite(motor, 1);
          digitalWrite(backWash1Out, 1);
          digitalWrite(backWash2Out, 1);
          
          
          pinMode(highPressureStorage, INPUT_PULLUP);
          pinMode(backWash1In, INPUT_PULLUP);
           
          pinMode(highLevel, INPUT_PULLUP);
          pinMode(lowLevel, INPUT_PULLUP);
          pinMode(LED, OUTPUT);
          digitalWrite(LED, LOW);
        
/////////////////////////////////////////////////////////////////////////////////////////
   
  pinMode(ALARM_PIN, OUTPUT);
  digitalWrite(ALARM_PIN, LOW);
  pinMode(highLevel, INPUT_PULLUP);
  
  backLightOn();
  // set up the LCD's number of columns and rows:
  lcd.begin(LCD_COLS, LCD_ROWS);
  currentConfig.load();
//   initTimers();

  //printTimerValue(0, true);

  // Use soft PWM for backlight, as hardware PWM must be avoided for some LCD shields.
 Timer1.initialize();
 Timer1.attachInterrupt(lcdBacklightISR, 500);
 
  setBacklightBrightness(currentConfig.displayBrightness);
  
 Serial.begin(9600);
 }
 

 
void loop()
{

  turnOffDelay =  currentConfig.alarmDuration * 1000 ;
  turnOffDelay2 =  currentConfig.BV1Duration * 1000 ;
  turnOffDelay3 =  currentConfig.BV2Duration * 1000 ;
 
           if ( digitalRead(valve2) == HIGH && flowIsWorking  ){
              alarm(true);
          }
        
           ///////////////////////////////////flow& EEPROM
           // flow 1
           if((millis() - oldTime) > 1000)    // Only process counters once per second
            {
              detachInterrupt(sensorInterrupt);
              flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount2) / calibrationFactor;
              oldTime = millis();       
              if (int(flowRate) > 1){}
              lcd.setCursor(0,1);
              lcd.print(int(flowRate));   
              lcd.print(" L");
              lcd.print("/min");
              pulseCount2 = 0;
              
              // Enable the interrupt again now that we've finished sending output
             attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
            }
             if ( flowRate> 7){
                 flowIsWorking = true;
              }else{
                flowIsWorking = false;
              }
            flowRate  = 0;
           //last Pressed
           EEPROM.write(EEPROMaddress, lastPressed);
          long address=0;
          //flow2
          currentTime = millis();
          if(currentTime >= (cloopTime + 1000))
          {
          cloopTime = currentTime; // Updates cloopTime
          unsigned long  pulseCount = isrCounter ;
          lcd.setCursor(8,1); 
          Serial.println(pulseCount);
          lcd.print(EEPROMReadlong(0)/59);
          lcd.print("L");
          EEPROMWritelong(address, 0);
          address+=5;
         } 

          ///////flow Finished
         ///////////////////////////machine        
          unsigned long currentMillis = millis(); 
          if (digitalRead(highLevel) == LOW) {
            if (state == false){
                digitalWrite(valve1, HIGH);
                buttonPushedMillis = currentMillis;
                ledReady = true;
                state = true;
                lastPressed = highLevel;
            }
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
          digitalWrite(motor, LOW); 
          
           }
          }
          
          /////////////////////////////////////
          else if (digitalRead(lowLevel) == LOW  ){
          state = false;
          digitalWrite(valve1, LOW);
          digitalWrite(valve2, HIGH); ///khamosh
          digitalWrite(motor, HIGH);   
          lastPressed = lowLevel;
          }
 
          //////////////////////////////////// BV1 
          else if (digitalRead(backWash1In) == HIGH){
          buttonPushedMillis2 = currentMillis;
          ledReady2 = true;
          }
          
          if (ledReady2) {
          if ((unsigned long)(currentMillis - buttonPushedMillis2) >=  turnOnDelay2) {
          digitalWrite(backWash1Out, LOW);
          digitalWrite(valve2, HIGH); ///khamosh
          digitalWrite(motor, HIGH); 
          ledState2 = true;
          ledTurnedOnAt2 = currentMillis;
          ledReady2 = false;
          }
          }
          
          else if (ledState2) {
          if ((unsigned long)(currentMillis - ledTurnedOnAt2) >= turnOffDelay2) {
          digitalWrite(backWash1Out, HIGH);
          digitalWrite(backWash2Out, LOW);
          digitalWrite(valve2, HIGH); ///khamosh
          digitalWrite(motor, HIGH); 
          ledState3 = true;
          ledTurnedOnAt3 = currentMillis;
          ledState2 = false;
          }
          }
          else if (ledState3) {
          if ((unsigned long)(currentMillis - ledTurnedOnAt3) >= turnOffDelay3) {
          ledState3 = false;
          digitalWrite(backWash2Out, HIGH); 
          digitalWrite(valve2, HIGH); ///khamosh
          digitalWrite(motor, HIGH); 
          ledTurnedOnAt3 = currentMillis;
          }
          }
           //////////////////////////////// presure 
          else if (digitalRead(highPressureStorage) == HIGH || digitalRead(air) == LOW ||  digitalRead(DC) == LOW || digitalRead(valve1)==LOW  ){
          
          digitalWrite(valve2, HIGH); ///khamosh
 
          digitalWrite(motor, HIGH);   
          }
          else if (digitalRead(highPressureStorage) == LOW && digitalRead(lowLevel) == HIGH && digitalRead(highLevel) == HIGH  ){
          digitalWrite(valve2, LOW);  
 
          digitalWrite(motor, LOW);  
          } 
          /////////senario nashti event
          else if ( digitalRead(valve2) == HIGH &&   digitalRead(lowLevel) == LOW   ){
             alarm(true);
          }
          if ( digitalRead(valve2) == LOW  && digitalRead(backWash1Out) == LOW  ){
              digitalWrite(valve2, HIGH);
              digitalWrite(motor, HIGH);
          }
         if ( digitalRead(motor) == LOW  && digitalRead(backWash1Out) == LOW  ){
              digitalWrite(valve2, HIGH);
              digitalWrite(motor, HIGH);
          }
         if ( digitalRead(valve2) == LOW  && digitalRead(backWash2Out) == LOW  ){
              digitalWrite(valve2, HIGH);
              digitalWrite(motor, HIGH);
          }
         if ( digitalRead(motor) == LOW  && digitalRead(backWash2Out) == LOW  ){
              digitalWrite(valve2, HIGH);
              digitalWrite(motor, HIGH);
          }
 //////////////////////////////////////////////////////////////////////////////////////////////////
  btn = getButton();

  if (btn && currentConfig.buttonBeep && appMode != APP_ALARM)
  {
    byte btnFlags = btn & 192;

    if (btnFlags == BUTTON_PRESSED_IND)   // if any button pressed.
    {
      digitalWrite(ALARM_PIN, HIGH);
      delay(3);
      digitalWrite(ALARM_PIN, LOW);
    }
  }
  
switch (appMode)
  {
    case APP_NORMAL_MODE :
     
         if(digitalRead(valve1)==LOW && digitalRead(highPressureStorage) == HIGH){
           lcd.setCursor(0,0);
           lcd.println("[filling][Full]");
         }else if(digitalRead(valve1)==LOW && digitalRead(highPressureStorage) == LOW){
           lcd.setCursor(0,0);
           lcd.println("[filling][Empty]");
         }else if(digitalRead(valve1)==HIGH && digitalRead(highPressureStorage) == HIGH){
           lcd.setCursor(0,0);
           lcd.println("[Full]  [Full]");
         }else if ( digitalRead(air)==LOW && digitalRead(highPressureStorage) == HIGH ){
           lcd.setCursor(0,0);
           lcd.println("[Air+DC] [Full]");
         }else if ( digitalRead(air)==LOW && digitalRead(highPressureStorage) == LOW ){
           lcd.setCursor(0,0);
           lcd.println("[Air+DC] [Empty]");
         }else if (digitalRead(valve2)==LOW && digitalRead(highPressureStorage) == HIGH){
           lcd.setCursor(0,0);
           lcd.println("[Pure]>>>[Full]");
         }else if (digitalRead(valve2)==LOW && digitalRead(highPressureStorage) == LOW){
           lcd.setCursor(0,0);
           lcd.println("[Pure]>>>[Empty]");
         }
 
         
         else if( digitalRead(backWash1Out) == LOW){
           lcd.setCursor(0,0);
           lcd.println("Washing Filter 1");
         }else if( digitalRead(backWash2Out) == LOW){
           lcd.setCursor(0,0);
           lcd.println("Washing Filter 2");
           }
      if (btn == BUTTON_SELECT_PRESSED )
      {
     //lcd.print(l_hour2, DEC);
      delay(5000);
      }
      else if (btn == BUTTON_SELECT_LONG_PRESSED)
      { ///////////////////////////Test Nashti
     //   timerCurrentValue[currentTimerIdx] = currentConfig.getTimerReloadValue(currentTimerIdx);
      //  printTimerValue(currentTimerIdx);
      //  lcd.println(pulseCount);
          digitalWrite(backWash1Out, HIGH);
          digitalWrite(backWash2Out, HIGH);
          digitalWrite(valve1, HIGH);
           
          digitalWrite(valve2, LOW);  
          digitalWrite(motor, LOW); 
          delay(5000);
          digitalWrite(backWash1Out, HIGH);
          digitalWrite(backWash2Out, HIGH);
          digitalWrite(valve1, HIGH); 
          digitalWrite(valve2, LOW);  
          digitalWrite(motor, LOW); 
      }
      else if (btn == BUTTON_UP_LONG_PRESSED)
      {
         appMode = APP_MENU_MODE;
         refreshMenuDisplay(REFRESH_DESCEND);

        
      }

      else if (btn == BUTTON_UP_SHORT_RELEASE)
      {
        currentTimerIdx = --currentTimerIdx < 0 ? 0 : currentTimerIdx;
       // printTimerValue(currentTimerIdx, true);
 
      }
      else if (btn == BUTTON_DOWN_SHORT_RELEASE)
      {
        currentTimerIdx = ++currentTimerIdx > 2 ? 2 : currentTimerIdx;
        //printTimerValue(currentTimerIdx, true);
        //while(btn != BUTTON_UP_SHORT_RELEASE){ 
        // lcd.clear();
  
      }
       else if (btn == BUTTON_DOWN_LONG_RELEASE )
      {  //////////////////// pause 
           
          
          digitalWrite(backWash1Out, HIGH);
          digitalWrite(backWash2Out, HIGH);
          digitalWrite(valve1, HIGH); 
          digitalWrite(valve2, HIGH);  
          digitalWrite(motor, HIGH); 
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("PAUSE-->Please");
          lcd.setCursor(0,1);
          lcd.print("Press Reset");
          if(btn = BUTTON_UP_PRESSED ) 
          delay(15000);
       }
       else if (btn == BUTTON_LEFT_PRESSED )
      {
        lcd.clear();
        sensors.requestTemperatures(); // Send the command to get temperature readings 
        lcd.clear(); 
        lcd.setCursor(0,0);           
        lcd.print("Tempreture = ");
        lcd.setCursor(0,1);    
        lcd.print(sensors.getTempCByIndex(0));
        lcd.setCursor(9,1);             
        lcd.print("deg C"); 
        delay(5000); 
        lcd.clear(); 
      }else if (btn == BUTTON_RIGHT_SHORT_RELEASE ){
             
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("1 glass Water");
            lcd.setCursor(0,1); 
            lcd.print(">>>>");
            digitalWrite(valve4, LOW);
            delay(5000);
            digitalWrite(valve4, HIGH);
            lcd.clear();
      } else if (btn == BUTTON_RIGHT_LONG_PRESSED ){
       
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("[]>>>>>>>>[]");
            digitalWrite(valve4, LOW); 
      }else if (btn == BUTTON_RIGHT_LONG_RELEASE ){
            lcd.clear();
            digitalWrite(valve4, HIGH); 
      }

     break;
    case APP_TIMER_RUNNING :
      if (btn == BUTTON_SELECT_SHORT_RELEASE || btn == BUTTON_SELECT_LONG_RELEASE)
      {
         lcd.println("APP_TIMER_RUNNING");
      }
 
      if (appMode == APP_NORMAL_MODE || appMode == APP_ALARM)
      {
        printTimerValue(currentTimerIdx);
        lcd.setCursor(8, 0);
        lcd.print("APP_TIMER_RUNNING");
      }
      break;
    case APP_ALARM:
      if (btn)
      {
        byte btnFlags = btn & 192;

        if (btnFlags == BUTTON_SHORT_RELEASE_IND || btnFlags == BUTTON_LONG_RELEASE_IND)
        {
          appMode = APP_NORMAL_MODE;
        }
      }
      else if (millis() - alarmStartTime >= turnOffDelay)
      {
        appMode = APP_NORMAL_MODE;
      }

      if (appMode == APP_NORMAL_MODE)
      {
        digitalWrite(ALARM_PIN, LOW);
      }
      break;
    case APP_MENU_MODE :
    {
      byte menuMode = Menu1.handleNavigation(getNavAction, refreshMenuDisplay);

      if (menuMode == MENU_EXIT)
      {
        // Tidy up display
        printTimerValue(currentTimerIdx, true);
        appMode = APP_MENU_MODE_END;
      }
      else if (menuMode == MENU_INVOKE_ITEM)
      {
        appMode = APP_PROCESS_MENU_CMD;

        // Highlight selected item (if not reset command).
        if (Menu1.getCurrentItemCmdId() != mnuCmdResetToDefaults)
        {
          lcd.setCursor(0, 1);
          strbuf[0] = 0b01111110; // forward arrow representing input prompt.
          strbuf[1] = 0;
          lcd.print(strbuf);
        }
      }
      break;
    }
    case APP_PROCESS_MENU_CMD :
    {
      byte processingComplete = processMenuCommand(Menu1.getCurrentItemCmdId());

      if (processingComplete)
      {
        appMode = APP_MENU_MODE;
        // Unhighlight selected item
        lcd.setCursor(0, 1);
        strbuf[0] = ' '; // clear forward arrow
        strbuf[1] = 0;
        lcd.print(strbuf);
      }
      break;
    }
    case APP_MENU_MODE_END :
      if (btn == BUTTON_SELECT_SHORT_RELEASE || btn == BUTTON_SELECT_LONG_RELEASE)
      {
        appMode = APP_NORMAL_MODE;
      }
      break;
  }
}

 

void printTimerValue(byte timerIdx, byte showTimerName)
{
  if (showTimerName)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    char intbuf[2];

    inttostr(intbuf, timerIdx + 1);
    
    fmt(strbuf, 2, "Timer ", intbuf);
    lcd.print(strbuf);
  }

  lcd.setCursor(0,1);
  toTimeStr(strbuf, timerCurrentValue[timerIdx]);
  lcd.print(strbuf);
}
 
//----------------------------------------------------------------------
// Addition or removal of menu items in MenuData.h will require this method
// to be modified accordingly. 
byte processMenuCommand(byte cmdId)
{
  byte complete = false;  // set to true when menu command processing complete.
  byte configChanged = false;

  if (btn == BUTTON_SELECT_PRESSED)
  {
    if (cmdId != mnuCmdResetToDefaults) complete = true;
  }

  switch (cmdId)
  {
 
    case mnuCmdAlarmDuration:
      configChanged = true;
      if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED)
      {
        currentConfig.alarmDuration = ++currentConfig.alarmDuration > 500 ? 500 : currentConfig.alarmDuration;
     //   turnOffDelay =  currentConfig.alarmDuration *1000     ;
        
      }
      else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED)
      {
        currentConfig.alarmDuration = --currentConfig.alarmDuration < 1 ? 1 : currentConfig.alarmDuration;
       // turnOffDelay = currentConfig.alarmDuration * 1000 ;
      }
      else
      {
        configChanged = false;
      }
      break;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
    case BV1:
      configChanged = true;
      if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED)
      {
        currentConfig.BV1Duration =  (++currentConfig.BV1Duration) >500 ? 500: currentConfig.BV1Duration;
     //   turnOffDelay2 =  currentConfig.BV1Duration * 1000 ;
      }
      else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED)
      {
        currentConfig.BV1Duration = --currentConfig.BV1Duration < 1  ? 1  : currentConfig.BV1Duration;
      //  turnOffDelay2 =  currentConfig.BV1Duration * 1000 ;

       }
      else
      {
        configChanged = false;
        
      }
      break;
 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 

    case BV2:
      configChanged = true;
      if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED)
      {
        currentConfig.BV2Duration =  (++currentConfig.BV2Duration) > 500 ? 500: currentConfig.BV2Duration;
       //  turnOffDelay3 = (short)currentConfig.BV2Duration * 1000 ;
      }
      else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED)
      {
        currentConfig.BV2Duration = --currentConfig.BV2Duration <1  ? 1  : currentConfig.BV2Duration;
      //  turnOffDelay3 = (short)currentConfig.BV2Duration * 1000 ;
       }
      else
      {
        configChanged = false;
        
      }
      break;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
     
    case mnuCmdButtonBeep:
      configChanged = true;
      if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED)
      {
        currentConfig.buttonBeep = true;
      }
      else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED)
      {
        currentConfig.buttonBeep = false;
      }
      else
      {
        configChanged = false;
      }
      break;
 
 
      break;
  }

  if (configChanged && cmdId != mnuCmdResetToDefaults)
  {
    lcd.setCursor(1, 1);
    lcd.print(rpad(strbuf, currentConfig.getFormattedStr(cmdId))); // Display config value.
  }
  if (complete)
  {
    currentConfig.save();
    
  }
  return complete;
}


//----------------------------------------------------------------------
// Callback to convert button press to navigation action.
byte getNavAction()
{
  byte navAction = 0;
  byte currentItemHasChildren = Menu1.currentItemHasChildren();
  
  if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED) navAction = MENU_ITEM_PREV;
  else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED) navAction = MENU_ITEM_NEXT;
  else if (btn == BUTTON_SELECT_PRESSED || (btn == BUTTON_RIGHT_PRESSED && currentItemHasChildren)) navAction = MENU_ITEM_SELECT;
  //else if (btn == BUTTON_LEFT_PRESSED) navAction = MENU_BACK;
  return navAction;
}


//----------------------------------------------------------------------
const char EmptyStr[] = "";

// Callback to refresh display during menu navigation, using parameter of type enum DisplayRefreshMode.
void refreshMenuDisplay (byte refreshMode)
{
  char nameBuf[LCD_COLS+1];

  lcd.setCursor(0, 0);
  if (Menu1.currentItemHasChildren())
  {
    rpad(strbuf, Menu1.getCurrentItemName(nameBuf));
    strbuf[LCD_COLS-1] = 0b01111110;            // Display forward arrow if this menu item has children.
    lcd.print(strbuf);
    lcd.setCursor(0, 1);
    lcd.print(rpad(strbuf, EmptyStr));          // Clear config value in display
  }
  else
  {
    byte cmdId;
    rpad(strbuf, Menu1.getCurrentItemName(nameBuf));

    if ((cmdId = Menu1.getCurrentItemCmdId()) == 0)
    {
      strbuf[LCD_COLS-1] = 0b01111111;          // Display back arrow if this menu item ascends to parent.
      lcd.print(strbuf);
      lcd.setCursor(0, 1);
      lcd.print(rpad(strbuf, EmptyStr));        // Clear config value in display.
    }
    else
    {
      lcd.print(strbuf);
      lcd.setCursor(0, 1);
      lcd.print(" ");
      lcd.print(rpad(strbuf, currentConfig.getFormattedStr(cmdId))); // Display config value.
    }
  }
}
 
 int alarm( int val){
           if (val == 1){
          digitalWrite(valve1, HIGH);
          digitalWrite(valve2, HIGH);  //// valve2 & 3 are together 
          digitalWrite(valve4, HIGH); 
          digitalWrite(air, HIGH);
          digitalWrite(DC, HIGH);
          digitalWrite(motor, HIGH);
          lcd.clear();
          lcd.setCursor (0,0);
         
          lcd.setCursor (0,1);
          lcd.print("Corrct & Reset");
           
           for  (int i= 0; i<2000; i++){
          tone(22,i);
          i++;
           }
          delay(5000);
           
          ///change lcd color

          ///send to bluetoooth alarm both oprator and customer

          ///reset with SELECT btn
            }
            else if (val == false){
            digitalWrite(valve2, LOW);  //// valve2 & 3 are together
            digitalWrite(motor, LOW);
            lcd.clear();
            }
 }
 
void pulseCounter()
{
  // Increment the pulse counter
  pulseCount2++;
}
