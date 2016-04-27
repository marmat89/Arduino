#include <OneWire.h>

//Digital Sensor Pin
int shockPin = 2;
int DS18B20_Pin = 4;
OneWire ds(DS18B20_Pin);

//Analog Sensor Pin
int levelPin = A0;

//INIT VAR
int levelvalue = 0;
int count;


//SerialCom
char recv; // byte received on the serial port
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup()
{
  Serial.begin(9600);
  count=0;
  //temp SETUP
  pinMode (DS18B20_Pin, INPUT);
  pinMode(shockPin, INPUT);
  //Interrupt 0 is digital pin 2, so that is where the IR detector is connected
  //Triggers on FALLING (change from HIGH to LOW)
  attachInterrupt(0, shockCount, CHANGE);
}

void loop() {
  if (stringComplete) {
    // confirm values received in serial monitor window

    if (inputString == "getTemp") {
      //Serial.println("--Arduino exeCommand: getTemp ");
      Serial.println(getTemp());
    }
    if (inputString == "getShock") {
      //Serial.println("--Arduino exeCommand: getSpeed ");
      Serial.println(getShock());
    }
    if (inputString == "getHumidity") {
      // Serial.println("--Arduino exeCommand: getHumidity ");
      Serial.println(getHumidity());
    }
    inputString = "";
    stringComplete = false;
  }
}

float getTemp() {
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
  ds.write(0x44, 1); // start conversion, with parasite power on at the end
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
  TemperatureSum = tempRead / 16;
  }
  return TemperatureSum;
}

//count shock of station
int getShock()
{
  //Don't process interrupts during calculations
  detachInterrupt(0);
  //Restart the interrupt processing
  int old = count;
  count = 0;
  attachInterrupt(0, shockCount, CHANGE);
  return (int)old;
}

// Get Ground Humidity
int getHumidity() {
  levelvalue = analogRead(levelPin);
  //Serial.print("RAIN VALUE = " );
  //Serial.println(sensorvalue);

  levelvalue = map(levelvalue, 1023, 0, 1, 100);
  return (int) levelvalue;
}

//Function that count # of shock
void shockCount()
{
  count=count+1;
}

//Use for handler
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    if (inChar == '=') {
      stringComplete = true;
    }
    else {
      inputString += inChar;
      // if the incoming character is a newline, set a flag
      // so the main loop can do something about it:
    }
  }
}

