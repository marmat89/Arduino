/*
 Standalone Sketch to use with a Arduino UNO and a
 Sharp Optical Dust Sensor GP2Y1010AU0F
*/
  
int measurePin = 0; //Connect dust sensor to Arduino A0 pin
int ledPower = 2;   //Connect 3 led driver pins of dust sensor to Arduino D2
  
int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
  
int count=0;
float avg=0;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
  
/*
 Interface to Shinyei Model PPD42NS Particle Sensor
 Program by Christopher Nafis 
 Written April 2012
 */
 
int pin = 9;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;
 
void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  pinMode(8,INPUT);
  starttime = millis();
}
  void loop(){
    sharp();
    Shinyei();
  }
void sharp(){
   while(count<29){
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);
  
  voMeasured = analogRead(measurePin); // read the dust value
  
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);
  
  // 0 - 5V mapped to 0 - 1023 integer values
  // recover voltage
  calcVoltage = voMeasured * (5.0 / 1024.0);
  dustDensity=(calcVoltage-0.0356)*120000;
  
  
  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  //dustDensity = 0.17 * calcVoltage - 0.1;
 
    
  count++;
  avg=avg+dustDensity;
    delay(1000);
  }
  
    avg=(float)avg/count;
    
  Serial.print("Sharp");
  Serial.print("-");
  Serial.print(calcVoltage);
  Serial.print("-");
  Serial.println(avg);
  avg=0;
  count=0;
  
}

void Shinyei() {
   while ((millis()-starttime) < sampletime_ms )
  {
  
  duration = pulseIn(pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;
  
  
 
    ratio = lowpulseoccupancy/((millis()-starttime)*10.0);  // Integer percentage 0=>100
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; // using spec sheet curve
     /* convert into concentration in particles per 0.01 cft */
    //concentration = 1.438e5 * pow(ratio, 2.0) + 4.488e4 * ratio;
    
  }
  Serial.print("Shinyei");
    Serial.print("-");
    Serial.print(ratio);
    Serial.print("-");
    Serial.println(concentration);
    lowpulseoccupancy = 0;
    starttime = millis();
}


