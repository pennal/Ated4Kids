#include "Arduino.h"

#include "Rover.h"

#define E1 6
#define E2 5
#define M1 8
#define M2 7
#define rotationalDelay 2000


Rover::Rover(){
	int i;
  	for(i=5;i<=8;i++) {
    	pinMode(i, OUTPUT);
    }
  Serial.println("Rover Constructed");
}

void Rover::turnLeft(){
	analogWrite (E1,_speed - _valoreDaSottrarreAVelocita);
  	digitalWrite(M1,LOW);
  	analogWrite (E2,_speed);
  	digitalWrite(M2,HIGH);
}

void Rover::turnRight(){
	analogWrite (E1,_speed);
  	digitalWrite(M1,HIGH);
  	analogWrite (E2, _speed - _valoreDaSottrarreAVelocita);
  	digitalWrite(M2,LOW);

}

void Rover::forward(){
	analogWrite (E1,_speed);
  	digitalWrite(M1,HIGH);
  	analogWrite (E2,_speed);
  	digitalWrite(M2,HIGH);
}

void Rover::stop(){
	analogWrite (E1,_speed);
  	digitalWrite(M1,LOW);
  	analogWrite (E2,_speed);
  	digitalWrite(M2,LOW);
  	delay(50);
  	analogWrite (E1,0);
  	digitalWrite(M1,LOW);
  	analogWrite (E2,0);
  	digitalWrite(M2,LOW);
}

void Rover::turnRightWithDefaultDelay(){
	turnRightWithDelay(turnDelay);
}

void Rover::turnLeftWithDefaultDelay(){
	turnLeftWithDelay(turnDelay);
}


void Rover::turnRightWithDelay(int theDelay){
	turnRight();
	delay(theDelay);
}

void Rover::turnLeftWithDelay(int theDelay){
	turnLeft();
	delay(theDelay);
}

void Rover::setSpeed(int speed){
	_speed = speed;
}

void Rover::rotateForAngle(double angolo){
  double ratio = angolo/360.0;
  double speedRatio = (255.0/_speed);

if (ratio > 0){
    analogWrite (E1,_speed);
    digitalWrite(M1,LOW);
    analogWrite (E2,_speed);
    digitalWrite(M2,HIGH);
    
    delay(rotationalDelay*ratio*speedRatio*0.8);

    analogWrite (E1,_speed);
    digitalWrite(M1,HIGH);
    analogWrite (E2,_speed);
    digitalWrite(M2,LOW);

    
} else {
  analogWrite (E1,_speed);
    digitalWrite(M1,HIGH);
    analogWrite (E2,_speed);
    digitalWrite(M2,LOW);
    
    delay(rotationalDelay*ratio*(-1)*speedRatio*0.8);

    analogWrite (E1,_speed);
    digitalWrite(M1,LOW);
    analogWrite (E2,_speed);
    digitalWrite(M2,HIGH);

}
  delay(50);

    analogWrite (E1,0);
    digitalWrite(M1,LOW);
    analogWrite (E2,0);
    digitalWrite(M2,LOW);


}



