#ifndef TouchSensor_h
#define TouchSensor_h

#include "Arduino.h"


class TouchSensor {
    public:
        // Constructor
        TouchSensor(int pinLeft, int pinRight, int pinCenter);

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