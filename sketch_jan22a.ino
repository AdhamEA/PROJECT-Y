#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(5,6,8,9,10,11);


#define pinservo 12;
#define sensorPin  A1



 Servo servo;

int redled2 = 13;  
int redled = 2;
int led2 = 1;
int greenled = 7;
int buzzer = 4;
int sensor = A0;
int sensorThresh =500;
int tempSensor =A1;
float temp;
int Mcc = 3;


void setup()
{
  servo.attach(12);
pinMode(1, OUTPUT);
pinMode(2,OUTPUT);
pinMode(7, OUTPUT);
pinMode(13, OUTPUT);
pinMode(3,OUTPUT);
pinMode(buzzer,OUTPUT);
pinMode(sensor,INPUT);
pinMode(tempSensor,INPUT);
pinMode(12,INPUT);

Serial.begin(9600);
lcd.begin(16,2);

}

void loop()
{
  temp = analogRead(A1)*0.004882814;
  temp=(temp-0.5)*100;
  int gaz = analogRead(sensor);
  lcd.setCursor(0,0);
 lcd.print("Tmp= ");
  lcd.setCursor(4,0);
  lcd.print(temp);
  lcd.setCursor(9, 0);
 lcd.print("Gaz= ");
  lcd.setCursor(13,0);
  lcd.print(gaz);
delay(1000);
  lcd.clear();
  
  if(gaz>sensorThresh && temp <= 45)
  {
    servo.write(-180);
 digitalWrite(7,LOW);
 digitalWrite(redled,HIGH);
 digitalWrite(13,LOW);
 digitalWrite(1,HIGH);
 analogWrite(3,255);
 tone(buzzer,800,1000);
 lcd.setCursor(0,1);
 lcd.print("alert Gas leak ");
 delay(1000);
 lcd.clear();

  }
    if(gaz<sensorThresh && temp <= 45)

  {
    servo.write(180);


    digitalWrite(1,HIGH);
    digitalWrite(13,LOW);
    digitalWrite(7,HIGH);
    digitalWrite(2,LOW);
    analogWrite(3,0);

    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("SAFE");
    delay(500);
    lcd.setCursor(0,1);
    lcd.print("ALL CLEAR");
    delay(1000);
    lcd.clear();

  }  
     if (temp >= 45 && gaz<sensorThresh) {

  digitalWrite(13, HIGH);
  digitalWrite(2,LOW);
  digitalWrite(7,HIGH);
  digitalWrite(1,LOW);
  analogWrite(3,255);
  tone(buzzer,800,1000);
  lcd.setCursor(0,1);
  lcd.print("fire detected");
  delay(1000);
  lcd.clear();

  }
  if (temp >= 45 && gaz>sensorThresh) {

 digitalWrite(13, HIGH);
 digitalWrite(2,HIGH);
 digitalWrite(7,LOW);
 digitalWrite(1,LOW);
 analogWrite(3,255);
 tone(buzzer,800,1000);
 lcd.setCursor(0,1);
 lcd.print("Fire & Gaz leak");
 delay(1000);
 lcd.clear();
  }
      delay(900);

}
