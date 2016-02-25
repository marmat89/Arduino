/*
 Interface to Shinyei Model PPD42NS Particle Sensor
 Program by Mariani Matteo
 Written Feb 2016
 
 http://www.seeedstudio.com/depot/grove-dust-sensor-p-1050.html
 http://www.sca-shinyei.com/pdf/PPD42NS.pdf
 
 JST Pin 1 (Black Wire)  => Arduino GND
 JST Pin 3 (Red wire)    => Arduino 5VDC
 JST Pin 4 (Yellow wire) => Arduino Digital Pin 8
 */

int pin25 = 11;
int pin05 = 9;

unsigned long sampletime_ms = 10000;
unsigned long duration;
unsigned long starttime;
unsigned long lowpulseoccupancy = 0;
  
//SET PIN : Used for blinking control led
int led_blu_measure =7; //  Connect led Blue led to 7 pin ON used during measue BLINK if error calc
int led_red_measure =6; //  Connect led function to 13 pin

//COUNTER : count of succes and error 
int errorCount=0;
int successCount=0;


void setup() {
  Serial.begin(9600);
  starttime = millis();
  pinMode(led_blu_measure, OUTPUT);
  pinMode(led_red_measure, OUTPUT);
  pinMode(pin05,INPUT);
  pinMode(pin25,INPUT);
}

void loop() {
  shinyei();
  }

void shinyei(){
  
  float dustDensity=0;
  float dustDensityMG=0;
  float calcVoltage = 0;
  float ratio = 0;
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
        successCount++;
        Serial.print("Shinyei_PM_25");
        Serial.print('&');
        printDouble(calcVoltage,4);
        Serial.print('&');
        Serial.print((float)dustDensity);
        Serial.print('&');
        printDouble((float)dustDensityMG,8);
        Serial.print('&');
        Serial.println(successCount);
      }else{
        delay(1000);              // wait for a second
        errorCount++;
        Serial.print("ERROR");
        Serial.print('&');
        Serial.print("Shinyei_PM_25");
        Serial.print('&');
        Serial.print("001_negative voltage");
        Serial.print('&');
        Serial.println(errorCount);
        blinkLed(led_red_measure,100,5);
      }
      lowpulseoccupancy = 0;
      starttime = millis();
    }
  }
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
