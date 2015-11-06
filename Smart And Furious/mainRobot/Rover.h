#ifndef Rover_h
#define Rover_h

#include "Arduino.h"


class Rover {
	public:
		// Constructor
		Rover();
		
		// Methods. Use to command the robot
		void turnLeft();
		void turnRight();
		void forward();
		void stop();

		void turnRightWithDefaultDelay();
    void turnLeftWithDefaultDelay();
    void turnRightWithDelay(int theDelay);
		void turnLeftWithDelay(int theDelay);
	 	
	 	void setSpeed(int speed);
    void setInternalSpeed(int speed);

		void rotateForAngle(double angolo);


		void rotateForTime(int t);

		int turnDelay = 80;

	private:
		int _externalSpeed = 140;
    int _internalSpeed = 140;
};

#endif
