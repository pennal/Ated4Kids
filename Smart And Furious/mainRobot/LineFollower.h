#ifndef LineFollower_h
#define LineFollower_h

#include "Arduino.h"


class LineFollower {
	public:
		// Constructor
		LineFollower(int pinLeft, int pinRight, int pinCenter);

		// Read sensor values. 
		void updateCenterValue();
		void updateLeftValue();
		void updateRightValue();
		void updateAll();

		// Values of sensors. Use <obj>.leftValue to read
		int leftValue;
		int rightValue;
		int centerValue;

	private:
		int _pinCenter;
		int _pinLeft;
		int _pinRight;
};

#endif