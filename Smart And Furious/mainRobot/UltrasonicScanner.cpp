#include "Arduino.h"
#include "UltrasonicScanner.h"



UltrasonicScanner::UltrasonicScanner(int trigPin, int echoPin, int servoPin, int delta){
	_trigPin = trigPin;
	_echoPin = echoPin;
	_servoPin = servoPin;


	servoDelta = delta;
	_l = _deg/servoDelta;


	pinMode(_trigPin,OUTPUT);
	pinMode(_echoPin,INPUT);

	myServo.attach(_servoPin);
	myServo.write(_startingServoPosition);
	delay(50);
	myServo.detach();


  Serial.println("UltrasonicReader Constructed");

}


void UltrasonicScanner::sweepForMaxDistance(){
	int a[_l];
	myServo.attach(_servoPin);
	myServo.write(0);

	for (int i=0; i<_l; i++){
		a[i] = getDistance();
		myServo.write((i+1) * servoDelta);
    	delay(150); // TODO: Check this delay if it is correct
	}

	myServo.write(_startingServoPosition);

	double maxValue = a[0];
 	int maxPointer = 0;
  	for (int j=0; j<_l; j++){
    	if (a[j] > maxValue){
      		maxValue = a[j];
      		maxPointer = j;
    	}
  	}

  	// Update the fields
  	maxLength = maxValue;
  	maxPosition = maxPointer;

  	rotationAngle = _l * maxPosition;

  	delay(50);


	myServo.detach();
}


double UltrasonicScanner::getDistance(){
	long duration, distance;
  	digitalWrite(_trigPin, LOW);
  	delayMicroseconds(2);
  	digitalWrite(_trigPin, HIGH);
  	delayMicroseconds(10);
  	digitalWrite(_trigPin, LOW);
  	duration = pulseIn(_echoPin, HIGH);
  	distance = (duration/2) / 29.1;
  	return distance;
}

long UltrasonicScanner::microsecondsToInches(long microseconds)
{
  return microseconds / 74 / 2;
}

long UltrasonicScanner::microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
