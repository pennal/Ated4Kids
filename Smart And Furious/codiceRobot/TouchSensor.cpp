#include "Arduino.h"
#include "TouchSensor.h"

TouchSensor::TouchSensor(int pinLeft, int pinRight){
    pinMode(pinLeft,INPUT);
    pinMode(pinRight,INPUT);

    Serial.println("TouchSensor Constructed");

  

    _pinLeft = pinLeft;
    _pinRight = pinRight;

}


void TouchSensor::updateLeftValue(){
    leftValue = digitalRead(_pinLeft);
}

void TouchSensor::updateRightValue(){
    rightValue = digitalRead(_pinRight);
}

void TouchSensor::updateAll(){
    updateLeftValue();
    updateRightValue();

}
