          #include <LiquidCrystal.h>
          #include <EEPROM.h>

          bool val  ;
          bool BizzarStop;
          LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
           bool flowIsWorking;
          
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
          
          /////////////// EEPROM
 
          ///////////// 
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
          
          volatile unsigned long isrCounter;
          unsigned long pulseCount;
          unsigned long stopCount = 100000;
          
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
          unsigned long turnOffDelay = 4000; // turn off LED after this time
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
          ///////////////////////////////
               //////////////////out of loop
          int alarm( int val){
           if (val == 1){
          digitalWrite(DC, HIGH);
          digitalWrite(valve1, HIGH);
          digitalWrite(valve2, HIGH);  //// valve2 & 3 are together
          digitalWrite(valve3, HIGH);  
          digitalWrite(air, HIGH);
          digitalWrite(motor, HIGH);
          lcd.clear();
          lcd.setCursor (0,0);
          lcd.print("Tempreture HIGH ");
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
          
          }

   
          void setup()
          {
          Serial.begin(9600);
          //////////////// flower
          attachInterrupt(0, countP, RISING);
          
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
          isrCounter = EEPROM.read(0);

          ///////////////////////////////////////
          
          lcd.begin(16, 2);              // start the library
          lcd.setCursor(0,0);
          lcd.print("Push the buttons"); // print a simple message
          lcd.clear();
          }
          
          void loop()
          {
           if ( digitalRead(valve2) == HIGH && flowIsWorking  ){
              alarm(true);
          }
          //////////////flower  //////////////flower  //////////////flower
          //////////////flower  //////////////flower  //////////////flower
          currentTime = millis();
          // Every second, calculate and print litres/hour
          if(currentTime >= (cloopTime + 1000))
          {
          cloopTime = currentTime; // Updates cloopTime
          long pulseCount = isrCounter;
          
          
           
          lcd.setCursor(0,0); 
          lcd.print(pulseCount);
            ///////////////  EEPROM

            //////////////////
          lcd.print("L");
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
           

          
          
          ////////////////////////////// temp
          sensors.requestTemperatures(); // Send the command to get temperature readings 
          lcd.setCursor(7,0);           
          lcd.print("T= ");
          lcd.print(sensors.getTempCByIndex(0));
          lcd.setCursor(14,1);             
          lcd.print("*C");
          
          ///Ex Temp : warning 
          while (sensors.getTempCByIndex(0) > 66){
          alarm(1);
          }
          ////////////////machine
          
          unsigned long currentMillis = millis(); 
          if (digitalRead(highLevel) == LOW) {
          digitalWrite(valve1, HIGH);
          buttonPushedMillis = currentMillis;
          ledReady = true;
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
          digitalWrite(valve1, LOW);
          digitalWrite(valve2, HIGH); ///khamosh
          digitalWrite(motor, HIGH);   
          }
          
          ///////////////////////////////
          //////////////////////////////////// BV1 
          else if (digitalRead(backWash1In) == LOW    ){
          buttonPushedMillis2 = currentMillis;
          ledReady2 = true;
          }
          
          if (ledReady2) {
          if ((unsigned long)(currentMillis - buttonPushedMillis2) >= turnOnDelay2) {
          digitalWrite(backWash1Out, LOW);
          digitalWrite(valve2, HIGH); ///khamosh
          digitalWrite(motor, HIGH); 
          ledState2 = true;
          ledTurnedOnAt2 = currentMillis;
          ledReady2 = false;
          }
          }
          
          else if (ledState2) {
          if ((unsigned long)(currentMillis - ledTurnedOnAt2) >= turnOnDelay3) {
          
          digitalWrite(backWash1Out, HIGH);
          digitalWrite(backWash2Out, LOW);
          digitalWrite(valve3, LOW);
          digitalWrite(valve2, HIGH); ///khamosh
          digitalWrite(motor, HIGH); 
          ledState3 = true;
          ledTurnedOnAt3 = currentMillis;
          ledState2 = false;
          }
          }
          else if (ledState3) {
          if ((unsigned long)(currentMillis - ledTurnedOnAt3) >= 10000) {
          ledState3 = false;
          digitalWrite(backWash2Out, HIGH);
          digitalWrite(valve3, HIGH);
          digitalWrite(valve2, LOW); ///khamosh
          digitalWrite(motor, LOW); 
          ledTurnedOnAt3 = currentMillis;
          }
          }
           //////////////////////////////// presure 
          else if (digitalRead(highPressureStorage) == LOW || digitalRead(air) == LOW || digitalRead(DC)==  LOW || digitalRead(valve1)==LOW  ){
          
          digitalWrite(valve2, HIGH); ///khamosh
          digitalWrite(motor, HIGH);   
          }
          else if (digitalRead(highPressureStorage) == HIGH && digitalRead(lowLevel) == HIGH && digitalRead(highLevel) == HIGH  ){
          digitalWrite(valve2, LOW);  
          digitalWrite(motor, LOW);  
          } 
          /////////senario nashti event
          else if ( digitalRead(valve2) == HIGH &&   digitalRead(lowLevel) == LOW   ){
              alarm(true);
          }

          ///////////////////////  LCD shield buttons
          lcd.setCursor(0,1);            
          lcd_key = read_LCD_buttons();   
          
          switch (lcd_key)               
          {
          case btnRIGHT:
          {
          lcd.print("RIGHT ");
          
          Serial.println("Output 1 ON");  
          break;
          }
          case btnLEFT:
          {
          
          
          break;
          
          }
          case btnUP:
          {
          lcd.print("UP  ");
          break;
          }
          case btnDOWN:
          {
           
          tone(22,1000);
          delay(100);   
          noTone(22);
          break;
          }
          case btnSELECT:
          {
            
          alarm( true);

          lcd.clear();
          lcd.setCursor(1,1);
          lcd.print("RESET System");
          alarm(false);
          break;
          }
          case btnNONE:
          {
          lcd.print("");
          break;
          }
          }
          
 }
         
      
          void countP() 
          {
          isrCounter++;
          }
          
