#include <LiquidCrystal.h>

int intensity= A1;
int sensorvalue = 0;
int TMP36 = A0;
int temperature = 0;
int temp[10];
int time= 20;
LiquidCrystal lcd(12, 11, 6, 5, 4, 3);
void setup() {
  Serial.begin(9600);
lcd.begin(16, 2);
}
void loop() {
  
sensorvalue =analogRead(intensity);
lcd.setCursor(0, 1);
lcd.print(sensorvalue);
delay(1000);
}
