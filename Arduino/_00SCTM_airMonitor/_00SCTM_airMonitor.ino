#include <OneWire.h>
#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 4 

char recv; // byte received on the serial port
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

int rpmcount;
float rpm;
long timeold;

//temp VAR
int DS18B20_Pin =3;
OneWire ds(DS18B20_Pin);

int rainPin = A0;    // select the input pin rainSensor
int lightPin = A1;    // select the input pin LighSensor
int rainvalue = 0;  // variable to store the value coming from the sensor
int lightvalue=0;// variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);
  //Interrupt 0 is digital pin 2, so that is where the IR detector is connected
  //Triggers on FALLING (change from HIGH to LOW)
  attachInterrupt(0, rpm_fun, CHANGE);
  rpmcount = 0;
  rpm = 0;
  timeold = 0;
}

void loop()
{
  if (stringComplete) {
    // confirm values received in serial monitor window
    //Serial.println(inputString);
    if (inputString=="getTemp"){
      //Serial.println("--Arduino exeCommand: getTemp ");
      Serial.println(getTemp());
    }
    if (inputString=="getSpeed"){
      //Serial.println("--Arduino exeCommand: getSpeed ");
      Serial.println(getSpeed()); 
    } 
    if (inputString=="getHumidity"){
      //Serial.println("--Arduino exeCommand: getHumidity ");
      Serial.println(getHumidity()); 
    }
    if (inputString=="getRain"){
      //Serial.println("--Arduino exeCommand: getRain ");
      Serial.println(getRain()); 
    }   
    if (inputString=="getLight"){
      //Serial.println("--Arduino exeCommand: getLight ");
      Serial.println(getLight()); 
    }
    inputString = "";
    stringComplete = false;
  }
}

float getSpeed()
{
  //Don't process interrupts during calculations
  detachInterrupt(0);
  //Note that this would be 60*1000/(millis() - timeold)*rpmcount if the interrupt
  //happened once per revolution instead of twice. Other multiples could be used
  //for multi-bladed propellers or fans
  float giri=(float)rpmcount/20;
  rpm =(float)((60000/(millis() - timeold))*giri);
  //Serial.println("RPM=");
  //Serial.println((float)rpm);
  //rpm =(int) 60*1000/(millis() - timeold)*(rpmcount/2);
  timeold = millis();
  rpmcount = 0;
  //Restart the interrupt processing
  attachInterrupt(0, rpm_fun, CHANGE);
  float speedKM;
  if (rpm<250){
    speedKM = map(rpm,0, 199, 0, 10);
  }
  if (rpm >= 250 && rpm < 450){
    speedKM = map(rpm,250, 450, 10, 20);
  }
    if (rpm >= 450 && rpm <600){
    speedKM = map(rpm,450, 600, 20, 30);
  }
      if (rpm >= 600 && rpm <700){
    speedKM = map(rpm,600, 700, 30, 40);
  }
        if (rpm >= 700 && rpm <775){
    speedKM = map(rpm,700,775, 40, 50);
  }
          if (rpm >= 775){//non affidabile
    speedKM = map(rpm,775, 1400, 50, 100);
  }
 
  return (float)speedKM;
}

void rpm_fun()
{
  //Each rotation, this interrupt function is run twice, so take that into consideration for 
  //calculating RPM
  //Update count
  rpmcount++;
}

float getTemp(){
  
  float TemperatureSum=120;
  while(TemperatureSum>70){
  //returns the temperature from one DS18B20 in DEG Celsius
  byte data[12];
  byte addr[8];
  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }
  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }
  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }
  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end
  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }
  ds.reset_search();
  byte MSB = data[1];
  byte LSB = data[0];
  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
   }
  return TemperatureSum;
}
int getHumidity(){
  //Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
  int chk;
  //Serial.print("DHT11, \t");
  chk = DHT.read(DHT11_PIN);    // READ DATA

  // DISPLAT DATA
  //Serial.print(DHT.humidity,1);
  //Serial.print(",\t");
  //Serial.println(DHT.temperature,1);
  return (int)DHT.humidity;
}
int getRain() {
  rainvalue = analogRead(rainPin);    
  //Serial.print("RAIN VALUE = " );
  //Serial.println(sensorvalue);
  rainvalue = map(rainvalue,0, 1023, 100, 1);
  return (int)rainvalue;
}
int getLight() {
  lightvalue= analogRead(lightPin);    
  //Serial.print("LIGHT VALUE = " );
  //Serial.println(lightvalue);

  lightvalue = map(lightvalue, 0, 1023, 1, 100);
  return (int)lightvalue;
}
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    if (inChar == '=') {
      stringComplete = true;
    } 
    else{
      inputString += inChar;
      // if the incoming character is a newline, set a flag
      // so the main loop can do something about it:
    }
  }
}


