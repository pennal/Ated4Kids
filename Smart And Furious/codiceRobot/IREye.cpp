#include "Arduino.h"
#include "IREye.h"



IREye::IREye(int pinUp, int pinRight, int pinLeft, int pinDown, int pinLEDs){
	pinMode(pinLEDs,OUTPUT);
	pinMode(pinUp,INPUT);
	pinMode(pinRight,INPUT);
	pinMode(pinLeft,INPUT);
 pinMode(pinDown,INPUT);
  	Serial.println("IREye Constructed");

	_pinUp = pinUp;
	_pinLeft = pinLeft;
	_pinRight = pinRight;
 _pinDown = pinDown;
	_pinLEDs = pinLEDs;

}

double IREye::measureDistance(){
  /* WARNING
  * The following code has been modified to only use three LEDs.
  * This is due to the fact that we do not have any additional pins on the arduino
  */
	digitalWrite(_pinLEDs,HIGH);// turn on IR LEDs to read TOTAL IR LIGHT (ambient + reflected) - attiva sensore IR (ambiente + riflessione)
  	delay(20);// Allow time for phototransistors to respond - aspetta per permettere la risposta dei fototransistors
  	int leftIRvalue = analogRead(_pinLeft);                             // TOTAL IR = AMBIENT IR + LED IR REFLECTED FROM OBJECT
  	int rightIRvalue = analogRead(_pinRight);                           // TOTAL IR = AMBIENT IR + LED IR REFLECTED FROM OBJECT
  	int upIRvalue = analogRead(_pinUp);                                 // TOTAL IR = AMBIENT IR + LED IR REFLECTED FROM OBJECT
   int downIRvalue = analogRead(_pinDown);                                 // TOTAL IR = AMBIENT IR + LED IR REFLECTED FROM OBJECT
  	
  	digitalWrite(_pinLEDs,LOW);                                   // turn off IR LEDs to read AMBIENT IR LIGHT (IR from indoor lighting and sunlight)- spegni IR per leggere luminosità ambientale (luce interna + sole)
  	delay(20);                                                   // Allow time for phototransistors to respond- aspetta per permettere la rispsta dei fototransistors
  	
  	leftIRvalue=leftIRvalue-analogRead(_pinLeft);                 // REFLECTED IR = TOTAL IR - AMBIENT IR
  	rightIRvalue=rightIRvalue-analogRead(_pinRight);              // REFLECTED IR = TOTAL IR - AMBIENT IR
  	upIRvalue=upIRvalue-analogRead(_pinUp);                       // REFLECTED IR = TOTAL IR - AMBIENT IR
  	downIRvalue = downIRvalue-analogRead(_pinDown);                                 // TOTAL IR = AMBIENT IR + LED IR REFLECTED FROM OBJECT

  double distance=(leftIRvalue+rightIRvalue+upIRvalue+downIRvalue)/4;// distance of object is average of reflected IR - la distanza dell'oggetto è la media di quanto riflesso dal sensore IR

  double finalDistance = 3.0*pow(10,-5)*pow(distance,2) - 0.0155*distance + 2.16;
  Serial.print("Distance EQ: ");
  Serial.println(finalDistance);

  
  return distance;
}
