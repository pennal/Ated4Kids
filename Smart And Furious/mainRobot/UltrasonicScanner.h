#ifndef UltrasonicScanner_h
#define UltrasonicScanner_h

#include "Arduino.h"
#include <Servo.h>


class UltrasonicScanner {
	public:
		// Constructor
		UltrasonicScanner(int trigPin, int echoPin, int servoPin, int delta);
		int servoDelta;

		

		void sweepForMaxDistance();

		int getMaxLength();
		int getMaxPosition();

		double maxLength;
		int maxPosition;

		int rotationAngle;


	private:
		// Some private methods
		int _trigPin;
		int _echoPin;
		int _servoPin;

		Servo myServo;

		int _startingServoPosition = 0;
		int _deg = 180;
		int _l;

		long microsecondsToInches(long microseconds);
		long microsecondsToCentimeters(long microseconds);
		double getDistance();

};

#endif
