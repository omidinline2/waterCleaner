 
 
#include <LiquidCrystal.h>
#include "LcdKeypad.h"
#include "MenuData.h"
#include "Config.h"
#include <TimerOne.h>
#include <OneWire.h> 
#include <EEPROM.h>

///////////////////////////////////////////////////////////////////////////////////////////
         
          
          #define ALARM_PIN 22
          bool val  ;
          bool BizzarStop;
          bool flowIsWorking;
          bool pauseStateBtn = false;
          bool currentStateBtn = true;
          ///////////// 
          int buttonPressTime2 = 250;   // Number of milliseconds to hold outputs o
          
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
          
          volatile unsigned long isrCounter;
          unsigned long pulseCount;
          unsigned long stopCount = 100000;
          
          const byte lowLevel = 42;
          const byte highLevel = 43;
          const byte highPressureStorage = 44;
          const byte backWash1In = 45;
          const byte backWash2In = 47;
          
          
          int valve1 = 31;
          int air = 32;
          int DC = 33;
          int motor = 34;
          int valve2 = 35;
          int valve3 = 36;
          int backWash1Out = 37;
          int backWash2Out = 38;
          
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
          #include <OneWire.h> 
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
          ////////////////////// temp
          // start serial port 
          sensors.begin();            //////////////// flower
          attachInterrupt(0, countP, RISING);
          //////////////////// machine
          pinMode(valve1, OUTPUT);
          pinMode(air, OUTPUT);
          pinMode(DC, OUTPUT);
          pinMode(valve2, OUTPUT);
          pinMode(valve3, OUTPUT);
          pinMode(motor, OUTPUT);
          pinMode(backWash1Out, OUTPUT);
          pinMode(backWash2Out, OUTPUT);
          
          digitalWrite(valve1, 1);
          digitalWrite(air, 1);
          digitalWrite(DC, 1);
          digitalWrite(valve2, 1);
          digitalWrite(valve3, 1);
          digitalWrite(motor, 1);
          digitalWrite(backWash1Out, 1);
          digitalWrite(backWash2Out, 1);
          
          
          pinMode(highPressureStorage, INPUT_PULLUP);
          pinMode(backWash1In, INPUT_PULLUP);
          pinMode(backWash2In, INPUT_PULLUP);
          pinMode(highLevel, INPUT_PULLUP);
          pinMode(lowLevel, INPUT_PULLUP);
          pinMode(LED, OUTPUT);
          digitalWrite(LED, LOW);
          //////EEPROM
                    //////EEPROM
          isrCounter = EEPROM.read(0);
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
 currentTime = millis();
}
 

 
void loop()
{
  turnOffDelay =  currentConfig.alarmDuration * 1000 ;
  turnOffDelay2 =  currentConfig.BV1Duration * 1000 ;
  turnOffDelay3 =  currentConfig.BV2Duration * 1000 ;
 
           if ( digitalRead(valve2) == HIGH && flowIsWorking  ){
              alarm(true);
          }
 
       currentTime = millis();
          // Every second, calculate and print litres/hour
          if(currentTime >= (cloopTime + 1000))
          {
          cloopTime = currentTime; // Updates cloopTime
          long pulseCount = isrCounter;
 
          if (pulseCount > 5){
              flowIsWorking = true;
          }
          if (pulseCount > stopCount)
          { 
          
          lcd.print("TV");
          lcd.print(pulseCount);
          lcd.print("pu");
          while(true) {}   
          }
          
          }
          EEPROM.write(0,isrCounter);
 
          ////////////////machine
          
          unsigned long currentMillis = millis(); 
           
          if (digitalRead(highLevel) == LOW) {
            if (state == false){
                digitalWrite(valve1, HIGH);
                buttonPushedMillis = currentMillis;
                ledReady = true;
                state = true;
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
          }
 
          //////////////////////////////////// BV1 
          else if (digitalRead(backWash1In) == HIGH){
          buttonPushedMillis2 = currentMillis;
          ledReady2 = true;
          }
          
          if (ledReady2) {
          if ((unsigned long)(currentMillis - buttonPushedMillis2) >=  turnOnDelay2) {
          digitalWrite(backWash1Out, LOW);
          digitalWrite(valve3, LOW);
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
          digitalWrite(valve3, HIGH);
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
          digitalWrite(valve3, HIGH);
          digitalWrite(valve2, HIGH); ///khamosh
          digitalWrite(motor, HIGH); 
          ledTurnedOnAt3 = currentMillis;
          }
          }
           //////////////////////////////// presure 
          else if (digitalRead(highPressureStorage) == HIGH || digitalRead(air) == LOW || digitalRead(DC)==  LOW || digitalRead(valve1)==LOW  ){
          
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
     
         if(digitalRead(valve1)==LOW){
           lcd.setCursor(0,0);
           lcd.println("First Storage ");
           lcd.setCursor(0,1);
           lcd.println("Is filling"); 
         }else if (digitalRead(valve2)==LOW || digitalRead(motor)==LOW){
           lcd.setCursor(0,0);
           lcd.println("Transfer Water to ");
           lcd.setCursor(0,1);
           lcd.println("Main Storage");
         }else if( digitalRead(backWash1Out) == LOW){
            lcd.setCursor(0,0);
           lcd.println("Back Wash 1");
           lcd.setCursor(0,1);
           lcd.println("Is Running");
         }else if( digitalRead(backWash2Out) == LOW){
            lcd.setCursor(0,0);
           lcd.println("Back Wash 2");
           lcd.setCursor(0,1);
           lcd.println("Is Running");
         }
      if (btn == BUTTON_SELECT_PRESSED )
      {
       lcd.clear();
      // isrCounter = EEPROM.read(0);
       lcd.println(isrCounter); 
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
          digitalWrite(valve3, LOW);
          digitalWrite(valve2, LOW);  
          digitalWrite(motor, LOW); 
          delay(5000);
          digitalWrite(backWash1Out, HIGH);
          digitalWrite(backWash2Out, HIGH);
          digitalWrite(valve1, HIGH);
          digitalWrite(valve3, HIGH);
          digitalWrite(valve2, LOW);  
          digitalWrite(motor, LOW); 
      }
      else if (btn == BUTTON_UP_LONG_PRESSED)
      {
         appMode = APP_MENU_MODE;
         refreshMenuDisplay(REFRESH_DESCEND);

        
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
          while (true){
          delay(250);
          digitalWrite(backWash1Out, HIGH);
          digitalWrite(backWash2Out, HIGH);
          digitalWrite(valve1, HIGH);
          digitalWrite(valve3, HIGH);
          digitalWrite(valve2, HIGH);  
          digitalWrite(motor, HIGH); 
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("PAUSE-->Please");
          lcd.setCursor(0,1);
          lcd.print("Press Reset");
         }
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

void countP() 
{
isrCounter++;
}

 int alarm( int val){
           if (val == 1){
            /*
          digitalWrite(DC, HIGH);
          digitalWrite(valve1, HIGH);
          digitalWrite(valve2, HIGH);  //// valve2 & 3 are together
          digitalWrite(valve3, HIGH);  
          digitalWrite(air, HIGH);
          digitalWrite(motor, HIGH);
          lcd.clear();
          lcd.setCursor (0,0);
         
          lcd.setCursor (0,1);
          lcd.print("Corrct & Reset");
           
            }
            else if (val == false){
            digitalWrite(valve2, LOW);  //// valve2 & 3 are together
            digitalWrite(motor, LOW);
            lcd.clear();
            }
          /////Bizzer

          ///change lcd color

          ///send to bluetoooth alarm both oprator and customer

          ///reset with SELECT btn
          */
          }
 }

