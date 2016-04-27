
#include <OneWire.h>

//speed VAR pin 4
int rpmcount;
float rpm;
long timeold;

//temp VAR
int DS18B20_Pin =4;
OneWire ds(DS18B20_Pin);

//level VAR
int levelPin = A0;    // select the input pin for the WaterLevel

//SerialCom
char recv; // byte received on the serial port
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup(){
  Serial.begin(9600);
  //speed SETUP
  //Interrupt 0 is digital pin 2, so that is where the IR detector is connected
  //Triggers on FALLING (change from HIGH to LOW)
  attachInterrupt(0, rpm_fun, CHANGE);
  rpmcount = 0;
  rpm = 0;
  timeold = 0;
  //temp SETUP

}

void loop(){
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
    if (inputString=="getLevel"){
      //Serial.println("--Arduino exeCommand: getHumidity ");
      Serial.println(getLevel()); 
    }
    inputString = "";
    stringComplete = false;
  }
}
float getTemp(){
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
  return TemperatureSum;

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
  return (float)rpm;
}
void rpm_fun()
{
  //Each rotation, this interrupt function is run twice, so take that into consideration for 
  //calculating RPM
  //Update count
  rpmcount++;
}

int getLevel() {
  // read the value from the sensor:
  int levelvalue = 0;  // variable to store the value coming from the sensor
  levelvalue = analogRead(levelPin);
  levelvalue = map(levelvalue, 0,800, 1, 100);//
  return(levelvalue);
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

