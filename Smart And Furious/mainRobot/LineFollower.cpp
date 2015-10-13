#include "Arduino.h"
#include "LineFollower.h"

LineFollower::LineFollower(int pinLeft, int pinRight, int pinCenter){
	pinMode(pinLeft,INPUT);
	pinMode(pinRight,INPUT);
	pinMode(pinCenter,INPUT);
  Serial.println("LineFollower Constructed");

  

	_pinCenter = pinCenter;
	_pinLeft = pinLeft;
	_pinRight = pinRight;

}

void LineFollower::updateCenterValue(){
	centerValue = digitalRead(_pinCenter);
//  Serial.print("CenterValue: ");
//  Serial.println(centerValue);
}

void LineFollower::updateLeftValue(){
	leftValue = digitalRead(_pinLeft);
}

void LineFollower::updateRightValue(){
	rightValue = digitalRead(_pinRight);
}

void LineFollower::updateAll(){
	updateLeftValue();
	updateRightValue();
	updateCenterValue();

}
