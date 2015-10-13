#ifndef IREye_h
#define IREye_h

#include "Arduino.h"


class IREye {
	public:
		// Constructor
		IREye(int pinUp, int pinRight, int pinLeft, int pinDown, int pinLEDs);
		double measureDistance();
	private:
		int _pinUp;
		int _pinLeft;
		int _pinRight;
    int _pinDown;
		int _pinLEDs;
};

#endif

