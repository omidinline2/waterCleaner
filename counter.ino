#include <LiquidCrystal.h>
#include "LcdKeypad.h"
#include "MenuData.h"
#include "Config.h"
#include <TimerOne.h>
#define ALARM_PIN 48 
//////////////////////////
            ///////////////////////////// temp
          /// First we include the libraries
 
         

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
          int lastPressed;
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
          int valve4= 30;
          
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
          unsigned long turnOffDelay4 = 10000; // turn off LED after this time

          
          unsigned long turnOnDelayBizz = 10000; // wait to turn on LED
          bool ledReady = false; // flag for when button is let go
          bool ledState = false; // for LED is on or not.
          bool ledReady2 = false;  
          bool ledState2 = false;  
          bool ledReady3 = false;  
          bool ledState3 = false;  
          
          bool val  ;
        bool state = false;
 


          
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
 

MenuManager Menu1(cd_timer_menu_Root, menuCount(cd_timer_menu_Root));

void printTimerValue(byte timerIdx, byte showTimerName = false);


void setup() {

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
          //////////////////////////////////
  pinMode(ALARM_PIN, OUTPUT);
  digitalWrite(ALARM_PIN, LOW);
  
  backLightOn();
  // set up the LCD's number of columns and rows:
  lcd.begin(LCD_COLS, LCD_ROWS);
  currentConfig.load();

  initTimers();

  printTimerValue(0, true);

  // Use soft PWM for backlight, as hardware PWM must be avoided for some LCD shields.
  Timer1.initialize();
  Timer1.attachInterrupt(lcdBacklightISR, 500);
  setBacklightBrightness(currentConfig.displayBrightness);
  
  //Serial.begin(9600);
}


void loop()
{
 
  /////////////////////
  turnOffDelay =  currentConfig.alarmDuration * 1000 ;
    turnOffDelay2 =  currentConfig.alarmDuration2 * 1000 ;
      turnOffDelay3 =  currentConfig.alarmDuration3 * 1000 ;
      turnOffDelay4 =  currentConfig.alarmDuration4 * 1000 ;
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
 

  /////////////////////
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
         }  else if( digitalRead(backWash1Out) == LOW){
           lcd.setCursor(0,0);
           lcd.println("Washing Filter 1");
         }else if( digitalRead(backWash2Out) == LOW){
           lcd.setCursor(0,0);
           lcd.println("Washing Filter 2");
           } 
      if (btn == BUTTON_SELECT_SHORT_RELEASE)
      {
            backLightOn();
            lcd.setCursor(0,1); 
            lcd.print("1 Glass Water >>>>");
            digitalWrite(valve4, LOW);
            delay( turnOffDelay4);
            
            digitalWrite(valve4, HIGH);
            delay(1000);
            backLightOff();
            lcd.clear();
      }
      else if (btn == BUTTON_SELECT_LONG_PRESSED)
      {
            backLightOn();
            lcd.setCursor(0,1); 
            lcd.print("Water Out >>>>>>>>>");
            digitalWrite(valve4, LOW);  
        //timerCurrentValue[currentTimerIdx] = currentConfig.getTimerReloadValue(currentTimerIdx);
        //printTimerValue(currentTimerIdx);
      }else if (btn == BUTTON_SELECT_LONG_RELEASE ){
            digitalWrite(valve4, HIGH); 
            delay(1000);
            backLightOff();
            lcd.clear();
      }
      else if (btn == BUTTON_UP_LONG_PRESSED)
      {
        appMode = APP_MENU_MODE;
        refreshMenuDisplay(REFRESH_DESCEND);
      }  else if (btn == BUTTON_UP_PRESSED)
      {
        backLightOn();
        //currentTimerIdx = --currentTimerIdx < 0 ? 0 : currentTimerIdx;
       // printTimerValue(currentTimerIdx, true);
      }
      else if (btn == BUTTON_UP_SHORT_RELEASE)
      {
        backLightOff();
        //currentTimerIdx = --currentTimerIdx < 0 ? 0 : currentTimerIdx;
       // printTimerValue(currentTimerIdx, true);
      }
     else if (btn == BUTTON_DOWN_LONG_RELEASE )
      {  //////////////////// pause 
          backLightOn(); 
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
          backLightOff();
       }
      else if (btn == BUTTON_DOWN_SHORT_RELEASE)
      {
        backLightOn();
        //currentTimerIdx = ++currentTimerIdx > 2 ? 2 : currentTimerIdx;
        //printTimerValue(currentTimerIdx, true);
      }else if (btn == BUTTON_LEFT_SHORT_RELEASE )
      {
         backLightOff();
      } else if (btn == BUTTON_RIGHT_SHORT_RELEASE ){
            backLightOn();
            delay(2000);
            backLightOff();

      }


            
      break;
    case APP_TIMER_RUNNING :
      if (btn == BUTTON_SELECT_SHORT_RELEASE || btn == BUTTON_SELECT_LONG_RELEASE)
      {
        appMode = APP_NORMAL_MODE;
      }
      else
      {
        short msDelta = (millis() - lastMilliSecondTimerValue);

        if (msDelta > 0)
        {
          lastMilliSecondTimerValue = millis();
          timerFineGrainedCounter[currentTimerIdx] += msDelta;
          
          if (timerFineGrainedCounter[currentTimerIdx] >= 1000)
          {
            timerFineGrainedCounter[currentTimerIdx] -= 1000;                     
            timerCurrentValue[currentTimerIdx]-=1;
            //printTimerValue(currentTimerIdx);
  
            if (timerCurrentValue[currentTimerIdx] <= 0)
            {
              timerCurrentValue[currentTimerIdx] = currentConfig.getTimerReloadValue(currentTimerIdx);
              appMode = APP_ALARM;
              alarmStartTime = millis();
              digitalWrite(ALARM_PIN, HIGH);
            }
          }
        }
      }
      if (appMode == APP_NORMAL_MODE || appMode == APP_ALARM)
      {
       // printTimerValue(currentTimerIdx);
       // lcd.setCursor(8, 0);
       // lcd.print("       ");
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
      else if (millis() - alarmStartTime >= (short)currentConfig.alarmDuration * 1000)
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
        //printTimerValue(currentTimerIdx, true);
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


//----------------------------------------------------------------------
void printTimerValue(byte timerIdx, byte showTimerName)
{
  if (showTimerName)
  {
   // lcd.clear();
   // lcd.setCursor(0,0);
   // char intbuf[2];

   // inttostr(intbuf, timerIdx + 1);
    
   // fmt(strbuf, 2, "Timer ", intbuf);
   // lcd.print(strbuf);
  }

  //lcd.setCursor(0,1);
  //toTimeStr(strbuf, timerCurrentValue[timerIdx]);
 // lcd.print(strbuf);
}


void initTimers()
{
  timerCurrentValue[0] = currentConfig.timer1ReloadValue;
  timerCurrentValue[1] = currentConfig.timer2ReloadValue;
  timerCurrentValue[2] = currentConfig.timer3ReloadValue;

  timerFineGrainedCounter[0] = 0;
  timerFineGrainedCounter[1] = 0;
  timerFineGrainedCounter[2] = 0;
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
    // Process menu commands here:
    case mnuCmdT1Hours :
      configChanged = true;
      if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED)
      {
        currentConfig.timer1ReloadValue = addToTime(3600, currentConfig.timer1ReloadValue);
      }
      else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED)
      {
        currentConfig.timer1ReloadValue = addToTime(-3600, currentConfig.timer1ReloadValue);
      }
      else
      {
        configChanged = false;
      }
      break;
    case mnuCmdT1Mins :
      configChanged = true;
      if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED)
      {
        currentConfig.timer1ReloadValue = addToTime(60, currentConfig.timer1ReloadValue);
      }
      else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED)
      {
        currentConfig.timer1ReloadValue = addToTime(-60, currentConfig.timer1ReloadValue);
      }
      else
      {
        configChanged = false;
      }
      break;
    case mnuCmdT1Secs :
      configChanged = true;
      if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED)
      {
        currentConfig.timer1ReloadValue = addToTime(1, currentConfig.timer1ReloadValue);
      }
      else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED)
      {
        currentConfig.timer1ReloadValue = addToTime(-1, currentConfig.timer1ReloadValue);
      }
      else
      {
        configChanged = false;
      }
      break;
    case mnuCmdT2Hours :
      configChanged = true;
      if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED)
      {
        currentConfig.timer2ReloadValue = addToTime(3600, currentConfig.timer2ReloadValue);
      }
      else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED)
      {
        currentConfig.timer2ReloadValue = addToTime(-3600, currentConfig.timer2ReloadValue);
      }
      else
      {
        configChanged = false;
      }
      break;
    case mnuCmdT2Mins :
      configChanged = true;
      if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED)
      {
        currentConfig.timer2ReloadValue = addToTime(60, currentConfig.timer2ReloadValue);
      }
      else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED)
      {
        currentConfig.timer2ReloadValue = addToTime(-60, currentConfig.timer2ReloadValue);
      }
      else
      {
        configChanged = false;
      }
      break;
    case mnuCmdT2Secs :
      configChanged = true;
      if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED)
      {
        currentConfig.timer2ReloadValue = addToTime(1, currentConfig.timer2ReloadValue);
      }
      else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED)
      {
        currentConfig.timer2ReloadValue = addToTime(-1, currentConfig.timer2ReloadValue);
      }
      else
      {
        configChanged = false;
      }
      break;
    case mnuCmdT3Hours :
      configChanged = true;
      if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED)
      {
        currentConfig.timer3ReloadValue = addToTime(3600, currentConfig.timer3ReloadValue);
      }
      else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED)
      {
        currentConfig.timer3ReloadValue = addToTime(-3600, currentConfig.timer3ReloadValue);
      }
      else
      {
        configChanged = false;
      }
      break;
    case mnuCmdT3Mins :
      configChanged = true;
      if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED)
      {
        currentConfig.timer3ReloadValue = addToTime(60, currentConfig.timer3ReloadValue);
      }
      else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED)
      {
        currentConfig.timer3ReloadValue = addToTime(-60, currentConfig.timer3ReloadValue);
      }
      else
      {
        configChanged = false;
      }
      break;
    case mnuCmdT3Secs :
      configChanged = true;
      if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED)
      {
        currentConfig.timer3ReloadValue = addToTime(1, currentConfig.timer3ReloadValue);
      }
      else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED)
      {
        currentConfig.timer3ReloadValue = addToTime(-1, currentConfig.timer3ReloadValue);
      }
      else
      {
        configChanged = false;
      }
      break;
      ////////////////////////////////
    case mnuCmdAlarmDuration:
      configChanged = true;
      if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED)
      {
        
        currentConfig.alarmDuration =  ++currentConfig.alarmDuration   > 500 ? 500 : (currentConfig.alarmDuration );
        
      }
      else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED)
      {
        currentConfig.alarmDuration =  --currentConfig.alarmDuration   < 1 ? 1 : (currentConfig.alarmDuration );
         

      }
      else
      {
        configChanged = false;
      }
      break;
      ////////////////////
      case mnuCmdAlarmDuration2:
      configChanged = true;
      if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED)
      {
        currentConfig.alarmDuration2 = ++currentConfig.alarmDuration2 > 500 ? 500 : currentConfig.alarmDuration2;
      }
      else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED)
      {
        currentConfig.alarmDuration2 = --currentConfig.alarmDuration2 < 1 ? 1 : currentConfig.alarmDuration2;
      }
      else
      {
        configChanged = false;
      }
      break;
      /////////
      case mnuCmdAlarmDuration3:
      configChanged = true;
      if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED)
      {
        currentConfig.alarmDuration3 = ++currentConfig.alarmDuration3 > 500 ? 500 : currentConfig.alarmDuration3;
      }
      else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED)
      {
        currentConfig.alarmDuration3 = --currentConfig.alarmDuration3 < 1 ? 1 : currentConfig.alarmDuration3;
      }
      else
      {
        configChanged = false;
      }
      break;
      //////
      case mnuCmdAlarmDuration4:
      configChanged = true;
      if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED)
      {
        currentConfig.alarmDuration4 = ++currentConfig.alarmDuration4 > 50 ? 50 : currentConfig.alarmDuration4;
      }
      else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED)
      {
        currentConfig.alarmDuration4 = --currentConfig.alarmDuration4 < 1 ? 1 : currentConfig.alarmDuration4;
      }
      else
      {
        configChanged = false;
      }
      break;
      ///////////
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
    case mnuCmdDisplayBrightness :
      configChanged = true;
      if (btn == BUTTON_UP_PRESSED || btn == BUTTON_UP_LONG_PRESSED)
      {
        currentConfig.displayBrightness++;
        currentConfig.displayBrightness = constrain(currentConfig.displayBrightness, 1, 4);
        setBacklightBrightness(currentConfig.displayBrightness);
      }
      else if (btn == BUTTON_DOWN_PRESSED || btn == BUTTON_DOWN_LONG_PRESSED)
      {
        currentConfig.displayBrightness--;
        currentConfig.displayBrightness = constrain(currentConfig.displayBrightness, 1, 4);
        setBacklightBrightness(currentConfig.displayBrightness);
      }
      else
      {
        configChanged = false;
      }

      break;
       case mnuCmdResetToDefaults:
      if (btn == BUTTON_SELECT_LONG_PRESSED)
      {
        currentConfig.setDefaults();
        setBacklightBrightness(currentConfig.displayBrightness);
        lcd.setCursor(1, 1);
        lcd.print("Defaults loaded");
      }
      else if (/*btn == BUTTON_SELECT_SHORT_RELEASE ||*/ btn == BUTTON_SELECT_LONG_RELEASE)
      {
        complete = true;
      }
      break;
    default:
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
    initTimers();
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
