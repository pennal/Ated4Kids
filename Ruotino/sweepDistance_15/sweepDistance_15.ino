#include <Servo.h>
// Init Servo
Servo myservo;
int E1 = 6;
int E2 = 5;
int M1 = 8;
int M2 = 7;
int Speed = 100;
double n = 87.5;

#define trigPin 13
#define echoPin 9 

const int servoPin = 2;
const int deg = 180;

int delta = 5;
int l = deg/delta;


void setup() {
  // put your setup code here, to run once:
  myservo.attach(servoPin);
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

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


void loop() {
//  // put your main code here, to run repeatedly:
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
//  delayMicroseconds(1000); - Removed this line
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
