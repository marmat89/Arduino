#include <LiquidCrystal.h>
int trigger=8;
int echo=9;
long time=0;
double dist=0;
int lamp=0;
LiquidCrystal lcd(12, 11, 6, 5, 4, 3);
void setup()
{
pinMode(lamp, OUTPUT);
pinMode(trigger, OUTPUT);
pinMode(echo, INPUT);
lcd.begin(16, 2);
}
void loop()
{
digitalWrite(trigger, LOW);
delay(5);
digitalWrite(trigger, HIGH);
delay(10);
digitalWrite(trigger, LOW);
time = pulseIn(echo, HIGH);
dist = (time/2) / 29.1;
if ( dist >= 500 || dist <= 0)
{
Serial.println("Nomeasurement");
}
else
{
lcd.clear();
lcd.setCursor(0, 0);
lcd.print(dist);
lcd.print("cm");
if (dist<10){
  digitalWrite(lamp,HIGH);
}else{
  digitalWrite(lamp,LOW);
}

delay(1000);
}}
