#include <Servo.h>
// Init Servo
Servo myservo;

const int servoPin = 11;
const int pingPin = 3;
const int deg = 180;

int delta = 60;
int l = deg/delta;


void setup() {
  // put your setup code here, to run once:
  myservo.attach(servoPin);
  Serial.begin(9600);
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
  

  
  delay(5000);
  
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
