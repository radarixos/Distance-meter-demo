/* selfedu ino, EchoLocator v.0.1
 * measure distance by obstacle in cm
 * sending values to serial and display via I2C
 * alarming obstacle closer < 20cm
 */

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 9;          //triggerPin on ultrasonic SR04
const int echoPin = 10;         //echoPin on ultrasonic SR04
const int piskle = 11;          //buzzer; H if obstacle distance < then safetyDistance
const int ledPin = 12;          //led ; H if obstacle distance < then safetyDistance
int x = 20;                     //distance of alerting <= in cm
long duration; 
int distance; 
int safetyDistance; 

void setup() {
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
pinMode(piskle, OUTPUT);
pinMode(ledPin, OUTPUT); 
Serial.begin(9600);             //copy $distance to serial
lcd.begin();
lcd.noBacklight();
lcd.clear();
delay(500);
lcd.backlight();
lcd.home();
lcd.print("EchoLoc v.0.1");
lcd.setCursor(0,1);
lcd.print("OK1VBR (cl)2019");
delay(1000);
lcd.clear();
} 

void loop() { 
// clears the trigPin+transmit+calculate distance
digitalWrite(trigPin, LOW);
delayMicroseconds(2); 
digitalWrite(trigPin, HIGH);
delayMicroseconds(10); 
digitalWrite(trigPin, LOW); 
duration = pulseIn(echoPin, HIGH); 
distance = duration*0.034/2; 
safetyDistance = distance; 

//safetyDistance is in (cm)
if (safetyDistance <= x){ 
  digitalWrite(piskle, HIGH); 
  digitalWrite(ledPin, HIGH); 
  } 
  
else { 
    digitalWrite(piskle, LOW); 
    digitalWrite(ledPin, LOW); 
  } 
  
//send EchoLoc to serial
Serial.print("Distance: "); 
Serial.println(distance); 

//if Echo signal is lost or distance >33m
if (distance >=3300) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Lost of echo    ");
  lcd.setCursor(0, 1);
  lcd.print("or distance >33m");
  }
  
//else print to display value of Echo
else
  lcd.clear();
  lcd.print("DISTANCE: ");
  lcd.print(distance);
  lcd.print("cm");
delay(50);
}


