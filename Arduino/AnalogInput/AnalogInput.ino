

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorvalue = 0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);

  }

void loop() {
  delay(1000);
  // read the value from the sensor:
  sensorvalue = analogRead(sensorPin);    
  
Serial.print("analogue value = " );
Serial.println(sensorvalue);
}
