
char sr;
int ledPin = 13;   //il PIN a cui è connesso il LED

// Impostazione del sensore 
void setup(){
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  }

void loop(){
  delay(1000);
   sr= (char)Serial.read();
   Serial.write(sr);
     if(sr == '0'){
       digitalWrite(ledPin, HIGH);   //Accendiamo il LED
   }
     if( sr == '1'){     
       digitalWrite(ledPin, LOW);  //Si spegne il LED  
       }
  }
