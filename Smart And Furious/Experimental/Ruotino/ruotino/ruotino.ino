#include <Servo.h>
Servo myservo;
int E1 = 6;
int E2 = 5;
int M1 = 8;
int M2 = 7;
int BNa = 11;
int BNb = 12;
int Centro = 10;
int Speed;
int Meta;
int Speed = 100;
double n = 87.5;

#define trigPin 13
#define echoPin 9 

const int servoPin = 2;
const int deg = 180;

int delta = 5;
int l = deg/delta;


void setup() {
  myservo.attach(servoPin);
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(BNa, INPUT);
  pinMode(BNb, INPUT);
  pinMode(Centro, INPUT);
  

  int i;
  for(i=5;i<=8;i++)
    pinMode(i, OUTPUT);
  myservo.write(90);
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

void avanti()
{
  
  analogWrite (E1,Speed);
  digitalWrite(M1,HIGH);
  analogWrite (E2, Speed);
  digitalWrite(M2,HIGH);
}

void rotateForAngle(double angolo){
  int v;

  if(angolo < 90)
  {
    v = 90 - angolo;
  }
  else
  {
     v = angolo - 90;
  }

  double rr = 2*((double)v/180.0)*3.14;
  Serial.print("rr: ");
  Serial.println(rr);
  double rot = rr * 1;
  Serial.print("Rot: ");
  Serial.println(rot);
  
  n = 270;
  
  if(angolo < 90)
  {
    double V = (double)Speed/255.0;
    double t = (rot * n)/V;
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
  n = 87.5;
}

void SweepDistance() {
  int dist = getLength();
  int minDist = 30;
  if (dist < minDist){
    aspetta();
    int a[l];
  myservo.write(0);
  
  for (int i=0; i<l; i++){
    a[i] = getLength();
    Serial.print(getLength());
    Serial.print("cm, at deg ");
    Serial.println(i*delta);
    myservo.write((i+1) * delta);
    delay(150);
  }
  myservo.write(90);

  // Trova la distanza maggiore
  double maxValue = a[0];
  int maxPointer = 0;
  for (int j=0; j<l; j++){
    if (a[j] > maxValue){
      maxValue = a[j];
      maxPointer = j;
    }
  }

  int angolo = maxPointer * delta;
  
  
  Serial.println(angolo);
  rotateForAngle(angolo);
  } else {
    avanti();
  }
  
  delay(50);
  
}

double getLength(){
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  return distance;
}

long microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
  
}
void SeguiLinea() {

    int valBNa = digitalRead(BNa);
  int valBNb = digitalRead(BNb);
  int valCentro = digitalRead(Centro);

  
  Serial.print("Bna: ");
  Serial.print(valBNa);

  Serial.print("; Bnb: ");
  Serial.print(valBNb);
  Serial.println();

  if (valCentro == 0) {
    Speed = 180;
  } else {
    Speed = 140;
  }

  if (valBNa == 0 && valBNb == 1){
    Meta = Speed + 60;
      destra();  
  } else if (valBNa == 1 && valBNb == 0) {
      Meta = Speed + 60;
      sinistra();  
  } else if(valBNa == 0 && valBNb == 0) {
    dritto();
  } else {
      dritto();
  }
  delay(30);
  
}
void Birilli() {
  
  }
void Lettura() {
  
  }
void Ponte() {
  
  }
void loop() {
  if(Lettura() == Schedina)
  {
    SweepDistance();
  }
  else if(Lettura() == Schedina)
  {
    Birilli();
  }
  else if(Lettura() == Schedina)
  {
    Ponte();
  }
  else
  {
    SeguiLinea();
  }
}
