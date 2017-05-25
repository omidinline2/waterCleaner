char BluetoothData; // the Bluetooth data received 

void setup() {

  Serial.begin(9600);
  
  //Set Digital Pins 4 to 7 as Output
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  
  //Set State of Pins all to LOW (0)
  digitalWrite(4,0);
  digitalWrite(5,0);
  digitalWrite(6,0);
  digitalWrite(7,0);

}

void loop() {

  if (Serial.available()){
  
    BluetoothData=Serial.read(); //Get next character from bluetooth
  
    if(BluetoothData=='R'){ // Red Button Pressed
      digitalWrite(4,1); //Turn digital out 4 to High
      digitalWrite(5,0); //Turn digital out 5 to Low
    }
    if(BluetoothData=='Y'){ // Yellow Button Pressed
    digitalWrite(5,1);
    digitalWrite(4,0);
    }
    if(BluetoothData=='r'||BluetoothData=='y'){ // Red or Yellow Button Released
      digitalWrite(4,0);
      digitalWrite(5,0);
    }
    if(BluetoothData=='G'){ // Green Button Pressed
      digitalWrite(6,1);
      digitalWrite(7,0);
    }
    if(BluetoothData=='B'){ // Blue Button Pressed
      digitalWrite(7,1);
      digitalWrite(6,0);
    }
    if(BluetoothData=='g'||BluetoothData=='b'){ // Green or Blue Button Released
      digitalWrite(7,0);
      digitalWrite(6,0);
    }
  
  }
  
  delay(10);// wait 10 ms

}
