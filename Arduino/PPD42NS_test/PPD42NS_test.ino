/*

 Interface to Shinyei Model PPD42NS Particle Sensor
 
 Based on code by Christopher Nafis April 2012
 Modified by David Holstius May 2012
 
 http://www.seeedstudio.com/depot/grove-dust-sensor-p-1050.html
 http://www.sca-shinyei.com/pdf/PPD42NS.pdf
 
 JST Pin 1 (Black Wire)  => Arduino GND
 JST Pin 3 (Red wire)    => Arduino 5VDC
 JST Pin 4 (Yellow wire) => Arduino Digital Pin 8
 
 */

#define BAUD        9600         // serial output
#define PIN            9        // input pin (digital)              
#define INTERVAL   15000         // sample duration (ms)
#define ALPHA        0.9         // controls smoothing

unsigned long t0;                // time of last serial dump
unsigned long elapsed;           // time since last serial dump (ms)
unsigned long acc;               // sum of time spent LOW
float raw;                       // fraction of time spent LOW
float filtered = 0.0;

void setup() {
  Serial.begin(BAUD);
  pinMode(9, INPUT);
  acc = 0;
  t0 = millis();
}

void loop() {
  acc += pulseIn(PIN, LOW);
  elapsed = millis() - t0;
  if (elapsed > INTERVAL) {
    raw = acc / (elapsed * 10.0);  // expressed as percentage
    filtered = ALPHA * filtered + (1.0 - ALPHA) * raw;
    Serial.print(raw, 4);
    Serial.print(",");
    Serial.println(filtered, 4);
    acc = 0;
    t0 = millis();
  }
}

