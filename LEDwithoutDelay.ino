
const int ledPin = 13;
int ledState = LOW;
int relay = 32; 
int relays = LOW;
 
long previousMillis = 0;
long interval = 1000;

void call(){
  unsigned long currntMillis = millis();

  if(currntMillis  - previousMillis > interval){
  previousMillis = currntMillis;
  if(ledState==LOW)
  ledState = HIGH;
  else
  ledState = LOW;
  digitalWrite(ledPin, ledState);
  }
}

void call2(){
  unsigned long currntMillis = millis();
  delay(4000);
  if(currntMillis  - previousMillis > interval){
  previousMillis = currntMillis;
  if(ledState==LOW)
  ledState = HIGH;
  else
  ledState = LOW;
  digitalWrite(ledPin, ledState);
  }
}


void call3(){
  unsigned long currntMillis = millis();
  delay(4000);
  if(currntMillis  - previousMillis > interval){
  previousMillis = currntMillis;
  if(relays==LOW)
  relays = HIGH;
  else
  relays = LOW;
  digitalWrite(relay, relays);
  }
}

void setup() {
pinMode(ledPin, OUTPUT);
pinMode(relay, OUTPUT);

}

void loop() {
call();
call2();
call3();


  //delay(10000);
}
