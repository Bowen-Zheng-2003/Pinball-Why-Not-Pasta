int motorPin = 3;
 
void setup() 
{ 
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
  while (! Serial);
  Serial.println("Speed 0 to 255");
} 
 
 
void loop() 
{ 
for(int motorValue = 0 ; motorValue <= 255; motorValue +=5){
 analogWrite(motorPin, motorValue); 
 delay(5);      
 }
 for(int motorValue = 255 ; motorValue >= 0; motorValue -=5){
 analogWrite(motorPin, motorValue); 
 delay(5);      
 }
  
} 
