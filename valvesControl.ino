
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
 
void setup() {

  Serial.begin(9600); 
 
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
}
 
void loop() {
                   /////////////// air and DC
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
 
             



} 
