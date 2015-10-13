// Librerie usate da altri file devono essere importati in doppio!
#include <Servo.h>
#include <MFRC522.h>
#include <SPI.h>

// Includi gli header per tutte le lib scritte da noi
#include "Rover.h"
#include "LineFollower.h"
#include "UltrasonicScanner.h"
#include "RFIDReader.h"
#include "TouchSensor.h"

// [FINALI] Pin Sensori linea
#define pinSensoreSinistro A5
#define pinSensoreDestro A4
#define pinSensoreCentro A3

//// [FINALI] Pin Sensore ultrasuoni
//#define trigPin 4
//#define echoPin 3 
//#define servoPin 2

// [FINALI] Pin lettore RFID.
// =====> ATTENZIONE, PIN PREDEFINITI, LEGGERE UltrasonicScanner.h PER SPECIFICHE <=====
// =====> DAL PIN 9 AL PIN 13 SONO RISERVATI <=====
#define RST_PIN 9
#define SS_PIN 10


// Pin TouchSensor
#define tcPinSensoreSinistro 2
#define tcPinSensoreDestro 3
#define tcPinSensoreCentro 4


// Inizializza gli oggetti richiesti per eseguire il percorso
Rover *rover;
LineFollower *lf;
UltrasonicScanner *us;
TouchSensor *tc;
//RFIDReader *rfid;


void labirintoSemplice(){
  tc->updateAll();

  
  Serial.print(tc->leftValue);
  Serial.print("\t");
  Serial.print(tc->centerValue);
  Serial.print("\t");
  Serial.println(tc->rightValue);
  delay(100);
}


void followLine(){
	// Aggiorna lo stato di tutti i sensori  
  lf->updateAll();
  rover->setSpeed(140);

	if (lf->leftValue == 0 && lf->rightValue == 1){
		rover->turnLeftWithDefaultDelay();
	} else if (lf->leftValue == 1 && lf->rightValue == 0){
		rover->turnRightWithDefaultDelay();
	} else if (lf->leftValue == 1 && lf->rightValue == 1){
		rover->forward();
	} else {
		rover->forward();
	}
}




void setup()
{
  Serial.begin(9600);
  lf = new LineFollower(pinSensoreSinistro,pinSensoreDestro,pinSensoreCentro);
  rover = new Rover();
  // us = new UltrasonicScanner(trigPin, echoPin, servoPin, 5);
  Serial.println("Left\tCenter\tRight");

  // rfid = new RFIDReader(RST_PIN,SS_PIN);
  tc = new TouchSensor(tcPinSensoreSinistro, tcPinSensoreDestro, tcPinSensoreCentro);
}


void angleTest(){
  
  delay(5000);

  //followLine();
  rover->rotateForAngle(90);
  delay(500);
  rover->rotateForAngle(-90);
  delay(500);
  rover->rotateForAngle(180);
  delay(500);
  rover->rotateForAngle(-180);

  delay(500);
  rover->rotateForAngle(360);
  delay(500);
  rover->rotateForAngle(-360);



}

void loop()
{
//  followLine();
labirintoSemplice();
}
