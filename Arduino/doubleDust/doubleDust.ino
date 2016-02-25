/*
 Standalone Sketch to use with a Arduino UNO and a
 Sharp Optical Dust Sensor GP2Y1010AU0F
*/

//Shinyei Model PPD42NS Particle Sensor
int pin25 = 11;
int pin05 = 9;

unsigned long sampletime_ms = 20000;
unsigned long duration;
unsigned long starttime;
unsigned long lowpulseoccupancy = 0;

//SENSOR connection pin 
int measurePin = 0; //Connect dust sensor to Arduino A0 pin
int ledPower = 12;   //Connect 3 led driver pins of dust sensor to Arduino 12 pin

//SET PIN : Used for blinking control led
int led_blu_measure =7; //  Connect led Blue led to 7 pin ON used during measue BLINK if error calc
int led_red_measure =6; //  Connect led function to 13 pin
 
//AVG : Number of time for more accurate measure
int MEASURE_LENGTH=20; 
int count=0;

//COUNTER : count of succes and error 
int errorCount=0;
int successCount=0;
//COUNTER : count of succes and error 
int errorCount05=0;
int successCount05=0;
//COUNTER : count of succes and error 
int errorCount25=0;
int successCount25=0;

void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  pinMode(led_blu_measure, OUTPUT);
  pinMode(led_red_measure, OUTPUT);
  
  pinMode(pin05,INPUT);
  pinMode(pin25,INPUT);
  
}

void loop(){
  sharp();
  shinyei05();
  shinyei25();
}
  

  
void shinyei05(){
  float dustDensity=0;
  float dustDensityMG=0;
  float calcVoltage = 0;
  float ratio = 0;
  starttime = millis();
  while (dustDensity==0){
  duration = pulseIn(pin05, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;
  blinkLed(led_blu_measure,20,1);
  if ((millis()-starttime) > sampletime_ms )
    {
      ratio = lowpulseoccupancy/((millis()-starttime)*10.0);  // Integer percentage 0=>100
      dustDensity = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
       /* convert into concentration in particles per 0.01 cft */
      //dustDensity = 1.438e5 * pow(ratio, 2.0) + 4.488e4 * ratio;
      calcVoltage=(dustDensity/120000)+0.0256;
      dustDensityMG = (0.172 * calcVoltage - 0.00999);
      if (ratio>0)
        {
        delay(1000);              // wait for a second
        blinkLed(led_blu_measure,100,5);
        successCount05++;
        Serial.print("Shinyei_PM_05");
        Serial.print('&');
        printDouble(calcVoltage,4);
        Serial.print('&');
        Serial.print((float)dustDensity);
        Serial.print('&');
        printDouble((float)dustDensityMG,8);
        Serial.print('&');
        Serial.println(successCount05);
      }else{
        delay(1000);              // wait for a second
        errorCount05++;
        Serial.print("ERROR");
        Serial.print('&');
        Serial.print("Shinyei_PM_05");
        Serial.print('&');
        Serial.print("001_negative voltage");
        Serial.print('&');
        Serial.println(errorCount05);
        blinkLed(led_red_measure,100,5);
      }
      float dustDensity=1;
      lowpulseoccupancy = 0;
      starttime = millis();
    }
  }
}


void shinyei25(){
  float dustDensity=0;
  float dustDensityMG=0;
  float calcVoltage = 0;
  float ratio = 0;
  starttime = millis();
  while (dustDensity==0){
  duration = pulseIn(pin05, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;
  blinkLed(led_blu_measure,20,1);
  if ((millis()-starttime) > sampletime_ms )
    {
      ratio = lowpulseoccupancy/((millis()-starttime)*10.0);  // Integer percentage 0=>100
      dustDensity = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
       /* convert into concentration in particles per 0.01 cft */
      //dustDensity = 1.438e5 * pow(ratio, 2.0) + 4.488e4 * ratio;
      calcVoltage=(dustDensity/120000)+0.0256;
      dustDensityMG = (0.172 * calcVoltage - 0.00999);
      if (ratio>0)
        {
        delay(1000);              // wait for a second
        blinkLed(led_blu_measure,100,5);
        successCount25++;
        Serial.print("Shinyei_PM_25");
        Serial.print('&');
        printDouble(calcVoltage,4);
        Serial.print('&');
        Serial.print((float)dustDensity);
        Serial.print('&');
        printDouble((float)dustDensityMG,8);
        Serial.print('&');
        Serial.println(successCount25);
      }else{
        delay(1000);              // wait for a second
        errorCount25++;
        Serial.print("ERROR");
        Serial.print('&');
        Serial.print("Shinyei_PM_25");
        Serial.print('&');
        Serial.print("001_negative voltage");
        Serial.print('&');
        Serial.println(errorCount25);
        blinkLed(led_red_measure,100,5);
      }
      float dustDensity=1;
      lowpulseoccupancy = 0;
      starttime = millis();
    }
  }
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
    dustDensity+=(calcVoltage-0.0256)*120000; //mg/m^3
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
