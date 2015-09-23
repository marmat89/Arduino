int ZPin = A2;
int YPin = A1;
int XPin = A0;
int valz[10];
int valy[10];
int valx[10];
int sommaz;
int sommay;
int sommax;
int mediaz;
int mediay;
int mediax;
int cal = 8;
int calz;
int caly;
int calx;
int z;
int y;
int x;
void setup() {
  Serial.begin(9600);
  Serial.println("MMA 7361");
  pinMode (cal, INPUT);
  digitalWrite (8, HIGH);
  calz = 0;
  caly = 0;
  calx = 0;
}
void loop() {
  for (int i=0;i<10;i++)
  {
    valz[i] = analogRead(ZPin);
    valy[i] = analogRead(YPin);
    valx[i] = analogRead(XPin);
    delay(40);
  }
  sommax = 0;
  sommay = 0;
  sommaz = 0;
  for(int i=0; i<10; i++){
    sommaz = sommaz + valz[i];
    sommay = sommay + valy[i];
    sommax = sommax + valx[i];
  }
  mediaz = sommaz / 10;
  mediay = sommay / 10;
  mediax = sommax / 10;
  int buttonState = digitalRead(cal);
  if (buttonState == LOW)
  {
    calz = mediaz;
    caly = mediay;
    calx = mediax;
  }
  z = mediaz-calz;
  y = mediay-caly;
  x = mediax-calx;
  Serial.print("Z: ");
  Serial.print(z);
  Serial.print("  Y: ");
  Serial.print(y);
  Serial.print("  X: ");
  Serial.println(x);
  delay(500);
}
