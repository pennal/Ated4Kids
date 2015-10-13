#include "Arduino.h"
#include "TouchSensor.h"

TouchSensor::TouchSensor(int pinLeft, int pinRight, int pinCenter){
    pinMode(pinLeft,INPUT);
    pinMode(pinRight,INPUT);
    pinMode(pinCenter,INPUT);
    Serial.println("TouchSensor Constructed");

  

    _pinCenter = pinCenter;
    _pinLeft = pinLeft;
    _pinRight = pinRight;

}

void TouchSensor::updateCenterValue(){
    centerValue = digitalRead(_pinCenter);
//  Serial.print("CenterValue: ");
//  Serial.println(centerValue);
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
    updateCenterValue();

}
