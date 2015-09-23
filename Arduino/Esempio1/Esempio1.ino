
const int G1 = 9;   // the pin for the LED
const int G2 = 8;   // the pin for the LED
const int G3 = 7;   // the pin for the LED
const int Y1 = 6;   // the pin for the LED
const int Y2 = 5;   // the pin for the LED
const int Y3 = 4;   // the pin for the LED
const int R1 = 3;   // the pin for the LED
const int R2 = 2;   // the pin for the LED
const int R3 = 1;   // the pin for the LED
int val = 0;        // variable used to store the value


void setup()
{
pinMode(G1, OUTPUT);
pinMode(Y1,OUTPUT);
pinMode(R1,OUTPUT);
pinMode(G2, OUTPUT);
pinMode(Y2,OUTPUT);
pinMode(R2,OUTPUT);
pinMode(G3, OUTPUT);
pinMode(Y3,OUTPUT);
pinMode(R3,OUTPUT);
}
void loop()
{
val = analogRead(0); 
  
  val = analogRead(0); // read the value from
  val=val/4;                  // the sensor
 if (val<27){                      
  digitalWrite(G1, LOW); // turn the LED on at
  digitalWrite(G2, LOW); // turn the LED on at
  digitalWrite(G3, LOW); // turn the LED on at
  digitalWrite(Y1, LOW); // turn the LED on at
  digitalWrite(Y2, LOW); // turn the LED on at
  digitalWrite(Y3, LOW); // turn the LED on at
  digitalWrite(R1, LOW); // turn the LED on at
  digitalWrite(R2, LOW); // turn the LED on at
  digitalWrite(R3, HIGH); // turn the LED on at     
}
 if ((val>27) && (val<54)){                      
  digitalWrite(G1, LOW); // turn the LED on at
  digitalWrite(G2, LOW); // turn the LED on at
  digitalWrite(G3, LOW); // turn the LED on at
  digitalWrite(Y1, LOW); // turn the LED on at
  digitalWrite(Y2, LOW); // turn the LED on at
  digitalWrite(Y3, LOW); // turn the LED on at
  digitalWrite(R1, LOW); // turn the LED on at
  digitalWrite(R2, HIGH); // turn the LED on at
  digitalWrite(R3, LOW); // turn the LED on at     
}
 if ((val>54) && (val<81)){                      
  digitalWrite(G1, LOW); // turn the LED on at
  digitalWrite(G2, LOW); // turn the LED on at
  digitalWrite(G3, LOW); // turn the LED on at
  digitalWrite(Y1, LOW); // turn the LED on at
  digitalWrite(Y2, LOW); // turn the LED on at
  digitalWrite(Y3, LOW); // turn the LED on at
  digitalWrite(R1, HIGH); // turn the LED on at
  digitalWrite(R2, LOW); // turn the LED on at
  digitalWrite(R3, LOW); // turn the LED on at     
}
 if ((val>81) && (val<108)){                      
  digitalWrite(G1, LOW); // turn the LED on at
  digitalWrite(G2, LOW); // turn the LED on at
  digitalWrite(G3, LOW); // turn the LED on at
  digitalWrite(Y1, LOW); // turn the LED on at
  digitalWrite(Y2, LOW); // turn the LED on at
  digitalWrite(Y3, HIGH); // turn the LED on at
  digitalWrite(R1, LOW); // turn the LED on at
  digitalWrite(R2, LOW); // turn the LED on at
  digitalWrite(R3, LOW); // turn the LED on at     
}
 if ((val>108) && (val<135)){                      
  digitalWrite(G1, LOW); // turn the LED on at
  digitalWrite(G2, LOW); // turn the LED on at
  digitalWrite(G3, LOW); // turn the LED on at
  digitalWrite(Y1, LOW); // turn the LED on at
  digitalWrite(Y2, HIGH); // turn the LED on at
  digitalWrite(Y3, LOW); // turn the LED on at
  digitalWrite(R1, LOW); // turn the LED on at
  digitalWrite(R2, LOW); // turn the LED on at
  digitalWrite(R3, LOW); // turn the LED on at     
}
 if ((val>135) && (val<162)){                      
  digitalWrite(G1, LOW); // turn the LED on at
  digitalWrite(G2, LOW); // turn the LED on at
  digitalWrite(G3, LOW); // turn the LED on at
  digitalWrite(Y1, HIGH); // turn the LED on at
  digitalWrite(Y2, LOW); // turn the LED on at
  digitalWrite(Y3, LOW); // turn the LED on at
  digitalWrite(R1, LOW); // turn the LED on at
  digitalWrite(R2, LOW); // turn the LED on at
  digitalWrite(R3, LOW); // turn the LED on at     
}
 if ((val>162) && val<(189)){                      
  digitalWrite(G1, LOW); // turn the LED on at
  digitalWrite(G2, LOW); // turn the LED on at
  digitalWrite(G3, HIGH); // turn the LED on at
  digitalWrite(Y1, LOW); // turn the LED on at
  digitalWrite(Y2, LOW); // turn the LED on at
  digitalWrite(Y3, LOW); // turn the LED on at
  digitalWrite(R1, LOW); // turn the LED on at
  digitalWrite(R2, LOW); // turn the LED on at
  digitalWrite(R3, LOW); // turn the LED on at     
}
 if ((val>189) && (val<216)){                      
  digitalWrite(G1, LOW); // turn the LED on at
  digitalWrite(G2, HIGH); // turn the LED on at
  digitalWrite(G3, LOW); // turn the LED on at
  digitalWrite(Y1, LOW); // turn the LED on at
  digitalWrite(Y2, LOW); // turn the LED on at
  digitalWrite(Y3, LOW); // turn the LED on at
  digitalWrite(R1, LOW); // turn the LED on at
  digitalWrite(R2, LOW); // turn the LED on at
  digitalWrite(R3, LOW); // turn the LED on at     
}
 if ((val>216) && (val<256)){                      
  digitalWrite(G1, HIGH); // turn the LED on at
  digitalWrite(G2, LOW); // turn the LED on at
  digitalWrite(G3, LOW); // turn the LED on at
  digitalWrite(Y1, LOW); // turn the LED on at
  digitalWrite(Y2, LOW); // turn the LED on at
  digitalWrite(Y3, LOW); // turn the LED on at
  digitalWrite(R1, LOW); // turn the LED on at
  digitalWrite(R2, LOW); // turn the LED on at
  digitalWrite(R3, LOW); // turn the LED on at     
}


  delay(100); // stop the program for
             // some time  

}
