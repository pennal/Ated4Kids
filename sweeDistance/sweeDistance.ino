#include <Servo.h>
// Init Servo
Servo myservo;
int E1 = 6;
int E2 = 5;
int M1 = 8;
int M2 = 7;
int Speed = 255;
double n = 87.5;
const int servoPin = 11;
const int pingPin = 3;
const int deg = 180;

int delta = 5;
int l = deg/delta;


void setup() {
  // put your setup code here, to run once:
  myservo.attach(servoPin);
  Serial.begin(9600);

  int i;
  for(i=5;i<=8;i++)
    pinMode(i, OUTPUT);
}
void aspetta()
{
  analogWrite (E1,0);
  digitalWrite(M1,HIGH);
  analogWrite (E2,0);
  digitalWrite(M2,HIGH);
  
}
void destra()
{
  analogWrite (E1,Speed);
  digitalWrite(M1,LOW);
  analogWrite (E2,Speed);
  digitalWrite(M2,HIGH);
}
void sinistra()
{
  Serial.println("IN");
  analogWrite (E1,Speed);
  digitalWrite(M1,HIGH);
  analogWrite (E2, Speed);
  digitalWrite(M2,LOW);
}
void loop() {
  // put your main code here, to run repeatedly:

  int a[l];
  myservo.write(0);
  
  for (int i=0; i<l; i++){
    a[i] = getLength();
    Serial.println(getLength());
    myservo.write((i+1) * delta);
    delay(150);
  }
  myservo.write(0);

  // Trova la distanza maggiore
  double maxValue = a[0];
  int maxPointer = 0;
  for (int j=0; j<l; j++){
    if (a[j] > maxValue){
      maxValue = a[j];
      maxPointer = j;
    }
  }

  Serial.print("Valore massimo: ");
  Serial.println(maxValue);
  Serial.print("Posizione: ");
  Serial.println(maxPointer);
  
  int v;
  int angolo = maxPointer * delta;
  if(angolo < 90)
  {
    v = 90 - angolo;
  }
  else
  {
     v = angolo - 90;
  }

  double rr = ((double)v/180.0)*3.14;
  Serial.print("rr: ");
  Serial.println(rr);
  double rot = rr * 3;

  if(angolo < 90)
  {
    double V = (double)Speed/255.0;
    double t = (rot * n)/V; 
    Serial.print("V: ");
    Serial.println(V);
    Serial.print("t: ");
    Serial.println(t);
    
    sinistra();
    delay(t);
    aspetta();
  }
  else
  {
    double V = (double)Speed/255.0;
    double t = (rot * n)/V; 
    destra();
    delay(t);
    aspetta();
  }
  
  //delay(5000);
  
}

double getLength(){
  long duration, inches, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(20);
  pinMode(pingPin, INPUT);
  
  duration = pulseIn(pingPin, HIGH);

  return microsecondsToCentimeters(duration);
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
