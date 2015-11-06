#ifndef TouchSensor_h
#define TouchSensor_h

#include "Arduino.h"


class TouchSensor {
    public:
        // Constructor
        TouchSensor(int pinLeft, int pinRight);

        // Read sensor values. 
        
        void updateLeftValue();
        void updateRightValue();
        void updateAll();

        // Values of sensors. Use <obj>.leftValue to read
        int leftValue;
        int rightValue;
        

    private:
        int _pinLeft;
        int _pinRight;
};

#endif
