 /*
 Standalone Sketch to use with a Arduino UNO a
 Sharp Optical Dust Sensor GP2Y1010AU0F
 
 For Pin connections, please check the info_circuit png
 Authors: Mariani Matteo 
 
 Changelog:
 2015-Feb-25:  first relese.
 
 */

//SENSOR connection pin 
int measurePin = 0; //Connect dust sensor to Arduino A0 pin
int ledPower = 12;   //Connect 3 led driver pins of dust sensor to Arduino 12 pin

//SET PIN : Used for blinking control led
int led_blu_measure =7; //  Connect led Blue led to 7 pin ON used during measue BLINK if error calc
int led_red_measure =6; //  Connect led function to 13 pin
 
//AVG : Number of time for more accurate measure
int MEASURE_LENGTH=5; 
int count=0;

//COUNTER : count of succes and error 
int errorCount=0;
int successCount=0;

//SETUP : Set led INPUT and OUTPUT
void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  pinMode(led_blu_measure, OUTPUT);
  pinMode(led_red_measure, OUTPUT);
}
 
//LOOP : Avviare lettura
void loop(){
  sharp();
}


void sharp(){
  
  //SHARP : config var, used for setup measure
  int samplingTime = 280;
  int deltaTime = 40;
  int sleepTime = 9680;
  float voMeasured = 0;
  float calcVoltage = 0;

  //DUST : var for store information
  float dustDensity = 0;
  float dustDensityMG = 0;
  float voltage=0;
  
  
  while(count<MEASURE_LENGTH)
  {
    digitalWrite(led_red_measure,HIGH); // power on the LED
    digitalWrite(ledPower,LOW); // power on the LED
    delayMicroseconds(samplingTime);
    voMeasured = analogRead(measurePin); // read the dust value
    delayMicroseconds(deltaTime);
    digitalWrite(ledPower,HIGH); // turn the LED off
    digitalWrite(led_red_measure,LOW); // power on the LED
    delayMicroseconds(sleepTime);
   
    // 0 - 5V mapped to 0 - 1023 integer values
    // recover voltage
    calcVoltage = voMeasured * (5.0 / 1024.0);
  
    // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
    // Chris Nafis (c) 2012

    dustDensityMG += (0.172 * calcVoltage - 0.00999);
    dustDensity+=(calcVoltage-0.0356)*120000; //mg/m^3
    voltage+=calcVoltage;
    count++;
    delay(1000);
  }
  if (dustDensity/count>=0)
  {
    blinkLed(led_blu_measure,100,5);
    successCount++;
    Serial.print("Sharp_PM_1");
    Serial.print('&');
    printDouble(voltage/count,4);
    Serial.print('&');
    Serial.print((float)dustDensity/count);
    Serial.print('&');
    printDouble((float)dustDensityMG/count,8);
    Serial.print('&');
    Serial.println(successCount);
  }else{
    errorCount++;
    Serial.print("ERROR");
    Serial.print('&');
    Serial.print("Sharp_PM_1");
    Serial.print('&');
    Serial.print("001_negative voltage");
    Serial.print('&');
    Serial.println(errorCount);
    blinkLed(led_red_measure,100,5);
  }
    dustDensity=0;
    dustDensityMG=0;
    count=0;
    voltage=0;
}

void blinkLed(int led, int time, int count){
  for(int i=0;i<count;i++)
    {
      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(time);              // wait for a second
      digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
      delay(time/2);  
    }
}


void printDouble( double val, byte precision){
 // prints val with number of decimal places determine by precision
 // precision is a number from 0 to 6 indicating the desired decimial places
 // example: lcdPrintDouble( 3.1415, 2); // prints 3.14 (two decimal places)
  if(val < 0.0){
    Serial.print('-');
    val = -val;
  }
  Serial.print (int(val));  //prints the int part
  if( precision > 0) {
  Serial.print("."); // print the decimal point
  unsigned long frac;
  unsigned long mult = 1;
  byte padding = precision -1;
  while(precision--)
  mult *=10;
  if(val >= 0)
    frac = (val - int(val)) * mult;
  else
    frac = (int(val)- val ) * mult;
  unsigned long frac1 = frac;
  while( frac1 /= 10 )
    padding--;
  while(  padding--)
    Serial.print("0");
    Serial.print(frac,DEC) ;
  }
}
