#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 4 

int rpmcount;
float rpm;
long timeold;

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorLPin = A1;    // select the input pin for the potentiometer
int sensorvalue = 0;  // variable to store the value coming from the sensor
int lightvalue=0;
void setup(){
  Serial.begin(9600);
     //Interrupt 0 is digital pin 2, so that is where the IR detector is connected
   //Triggers on FALLING (change from HIGH to LOW)
   attachInterrupt(0, rpm_fun, CHANGE);

   rpmcount = 0;
   rpm = 0;
   timeold = 0;
}
  
void loop(){
 getTemp();
 delay(2000);
 getSpeed();
 delay(2000);
 getRain();
 delay(2000);
 getLumen();
 delay(2000);
}
void getTemp(){
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
  int chk;
  Serial.print("DHT11, \t");
  chk = DHT.read(DHT11_PIN);    // READ DATA
  switch (chk){
    case DHTLIB_OK:  
                Serial.print("OK,\t"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.print("Checksum error,\t"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.print("Time out error,\t"); 
                break;
    default: 
                Serial.print("Unknown error,\t"); 
                break;
  }
 // DISPLAT DATA
  Serial.print(DHT.humidity,1);
  Serial.print(",\t");
  Serial.println(DHT.temperature,1);
}

 void getSpeed()
 {
   //Don't process interrupts during calculations
   detachInterrupt(0);
   //Note that this would be 60*1000/(millis() - timeold)*rpmcount if the interrupt
   //happened once per revolution instead of twice. Other multiples could be used
   //for multi-bladed propellers or fans
   float giri=(float)rpmcount/20;
   
    rpm =(float)((60000/(millis() - timeold))*giri);


   Serial.println("RPM=");
   Serial.println((float)rpm);
   //rpm =(int) 60*1000/(millis() - timeold)*(rpmcount/2);
   timeold = millis();
   rpmcount = 0;
   //Restart the interrupt processing
   attachInterrupt(0, rpm_fun, CHANGE);
  }
  void rpm_fun()
 {
   //Each rotation, this interrupt function is run twice, so take that into consideration for 
   //calculating RPM
   //Update count
      rpmcount++;
 }
 
void getRain() {
sensorvalue = analogRead(sensorPin);    
Serial.print("RAIN VALUE = " );

  sensorvalue = map(sensorvalue, 1023, 0, 0, 100);
Serial.println(sensorvalue);
}
void getLumen() {
lightvalue= analogRead(sensorLPin);   

  lightvalue = map(lightvalue, 1023, 0, 0, 100);
Serial.print("LIGHT VALUE = " );
Serial.println(lightvalue);
}
