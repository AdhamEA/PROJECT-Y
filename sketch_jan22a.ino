
int value= 0;
int led= 12;
int led1= 11;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(led, OUTPUT);
  pinMode(led1,OUTPUT);
  Serial.begin(9600);
  Serial.println("conection established ...");
}

// the loop function runs over and over again forever
void loop() {
  while(Serial.available())
  {
    value = Serial.read();
    Serial.println(value);
    }
    if (value=='1'){
  digitalWrite(led, HIGH);}
    else if (value=='0'){
      digitalWrite(led, LOW);
      
      }
       else if (value=='2'){
      digitalWrite(led1, HIGH);}
      else if (value=='3'){
      digitalWrite(led1, LOW);}
     
    
}
    


  // turn the LED on (HIGH is the voltage level)
                        // wait for a second
