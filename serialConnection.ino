
// Use pins 5 through 12 as the digital outputs int output1 = 5;
int output2 = 6;
int output3 = 7;
int output4 = 8;
int output5 = 9;
int output6 = 10; 
int output7 = 11; 
int output8 = 12; 
int buttonPressTime = 250;   // Number of milliseconds to hold outputs o

void setup() {  
 // Open the serial connection to listen for commands from the host 
  Serial.begin(38400); 
  // Set up the pins as outputs  
pinMode(output1, OUTPUT);  
pinMode(output2, OUTPUT); 
pinMode(output3, OUTPUT); 
pinMode(output4, OUTPUT); 
pinMode(output5, OUTPUT);
pinMode(output6, OUTPUT); 
pinMode(output7, OUTPUT);  
pinMode(output8, OUTPUT); // Make sure the outputs are all set LOW initally   digitalWrite(output1, LOW);  
digitalWrite(output2, LOW);  
digitalWrite(output3, LOW); 
digitalWrite(output4, LOW);  
digitalWrite(output5, LOW); 
digitalWrite(output6, LOW);  
 digitalWrite(output7, LOW);
   digitalWrite(output8, LOW); 
}






void loop() {  
 byte val;   // Check if a value has been sent by the host   
if(Serial.available()) {  
   val = Serial.read();  
    if(val == '1') {       // Pulse the 1st button  
     Serial.println("Output 1 ON");  
     digitalWrite(output1, HIGH);   
    delay(buttonPressTime);  
     digitalWrite(output1, LOW);  
     Serial.println("Output 1 OFF"); 
 
 
    }
 else if(val == '2') {       // Pulse the 2nd button  
Serial.println("Output 2 ON");    
   digitalWrite(output2, HIGH);    
   delay(buttonPressTime);     
  digitalWrite(output2, LOW);  
     Serial.println("Output 2 OFF");  
   } 
  else if(val == '3') {       // Pulse the 3rd button    
     Serial.println("Output 3 ON");   
      digitalWrite(output3, HIGH);   
      delay(buttonPressTime);   
      digitalWrite(output3, LOW);   
    Serial.println("Output 3 OFF");   
  }
 else if(val == '4') {       // Pulse the 4th button  
     Serial.println("Output 4 ON");   
    digitalWrite(output4, HIGH); 
      delay(buttonPressTime);      
 digitalWrite(output4, LOW);    
   Serial.println("Output 4 OFF"); 
    } else if(val == '5') {       // Pulse the 5th button
       Serial.println("Output 5 ON");    
       digitalWrite(output5, HIGH);   
    delay(buttonPressTime);  
     digitalWrite(output5, LOW);     
  Serial.println("Output 5 OFF");   
  
  } else if(val == '6') {       // Pulse the 6th button       Serial.println("Output 6 ON");   
    digitalWrite(output6, HIGH);     
  delay(buttonPressTime); 

      digitalWrite(output6, LOW);    
   Serial.println("Output 6 OFF");  
   } 
else if(val == '7') {  // Pulse the 7th button    
   Serial.println("Output 7 ON");    
   digitalWrite(output7, HIGH); 
      delay(buttonPressTime);    
   digitalWrite(output7, LOW);    
   Serial.println("Output 7 OFF");   
   }
   else if(val == '8') {       // Pulse the 8th button       Serial.println("Output 8 ON"); 
      digitalWrite(output8, HIGH); 
      delay(buttonPressTime);    
   digitalWrite(output8, LOW);   
    Serial.println("Output 8 OFF"); 
           }  
        } 
    }
