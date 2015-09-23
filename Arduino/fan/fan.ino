
int dir1PinB = 6;
int dir2PinB = 7;
int dir1PinA = 8;
int dir2PinA = 9; 

unsigned long time; 
int dir; 

void setup () 
{
pinMode (dir1PinB, OUTPUT); 
pinMode (dir2PinB, OUTPUT); 
pinMode (dir1PinA, OUTPUT); 
pinMode (dir2PinA, OUTPUT); 
time = millis (); 
dir = 1;
} 

void loop () 
{

if (1 == dir) 
{
digitalWrite (dir1PinB, HIGH); 
digitalWrite (dir2PinB, LOW);
digitalWrite (dir1PinA, HIGH); 
digitalWrite (dir2PinA, LOW);
} 
else 
{
digitalWrite (dir1PinB, LOW); 
digitalWrite (dir2PinB, HIGH);
digitalWrite (dir1PinA, LOW); 
digitalWrite (dir2PinA, HIGH);
} 

if (millis () - time> 5000) 
{
time = millis (); 
if (1 == dir) 
{dir = 0;} 
else 
{dir = 1;}
}
}

