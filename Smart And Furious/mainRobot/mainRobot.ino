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
#define pinSensoreSinistro A4
#define pinSensoreDestro A5
#define pinSensoreCentro A3

// [FINALI] Pin lettore RFID.
// =====> ATTENZIONE, PIN PREDEFINITI, LEGGERE UltrasonicScanner.h PER SPECIFICHE <=====
// =====> DAL PIN 9 AL PIN 13 SONO RISERVATI <=====
#define RST_PIN 9
#define SS_PIN 10

// Pin TouchSensor
#define tcPinSensoreSinistro 2
#define tcPinSensoreDestro 3


// Inizializza gli oggetti richiesti per eseguire il percorso
Rover *rover;
LineFollower *lf;
TouchSensor *tc;
//RFIDReader *rfid;


void labirintoSemplice(){
  tc->updateAll();
  Serial.print(tc->leftValue);
  Serial.print("\t");
  Serial.println(tc->rightValue);
  delay(100);
}

void rampa(){

}


void followLine(){
  lf->updateAll();
  
  if (lf->leftValue == 0 && lf->rightValue == 1){
    while(lf->centerValue != 0){
      rover->turnLeft();
      lf->updateCenterValue();
    }
  } else if (lf->leftValue == 1 && lf->rightValue == 0){
    while(lf->centerValue != 0){
      rover->turnRight();
      lf->updateCenterValue();
    }
  } else {
    rover->forward();
  }
}

void sweep(){

}



void setup()
{
  Serial.begin(9600);
  lf = new LineFollower(pinSensoreSinistro,pinSensoreDestro,pinSensoreCentro);
  rover = new Rover();

  // rfid = new RFIDReader(RST_PIN,SS_PIN);
  tc = new TouchSensor(tcPinSensoreSinistro, tcPinSensoreDestro);

  rover->setSpeed(180);
  rover->setInternalSpeed(-70);
  
  int START_BARRIERA_MULTIPLA[] = {657};
  int END_BARRIERA_MULTIPLA[] = {420,480,496,642};

  int START_BARRIERA[] = {462};
  int END_BARRIERA[] = {516,542,339,413};

  int START_RAMPA[] = {481};
  int END_RAMPA[] = {419,777,458,562};

  int START_BIRILLI[] = {328};
  int END_BIRILLI[] = {395,269,633,523};

  int termineOstacoli[] = {420,480,496,642,516,542,339,413,419,777,458,562,395,269,633,523}

  int contatoreLoop = 0;




  int currentOperation = 0;

}


bool containsItem(int &rfidVals, int val){
  for (int i = 0; i < rfidVals.length; i++){
    if (rfidVals[i] == val){
      return true;
    }
  }

  return false;
}

void rampa(){
  rover->setSpeed(250);
  rover->setSpeed(-50);
  
  tc->updateAll();
  
  if (tc->rightValue == 1){
    rover->turnLeftWithDelay(80);
  } else if (tc->leftValue == 1){
    rover->turnRightWithDelay(80);
  } else {
    rover->forward();
  }

}

void birilli(){

}



void followWall(){
  tc->updateAll();
  rover->setSpeed(140);

  Serial.println(tc->rightValue);
  if (tc->rightValue == 1){
    rover->turnRightWithDelay(80);
  }
  rover->forward();
  delay(50);
  
}

void loop()
{
  if (contatoreLoop >= 2){
    // Ottieni il valore dalla scheda
    int rfidValue = 633;
    // Se il valore non è "null", procedi a capire che opzione va eseguita
    if (containsItem(termineOstacoli, rfidValue)){
      // Torna al follow line
      currentOperation = 0;
    } else if (containsItem(START_BARRIERA_MULTIPLA, rfidValue)){
      // Nel caso del labirinto complicato, facciamo il follow line
      currentOperation = 0;
    } else if (containsItem(START_BARRIERA, rfidValue)){
      currentOperation = 1;
    } else if (containsItem(START_RAMPA, rfidValue)){
      currentOperation = 2;  
    } else if (containsItem(START_BIRILLI, rfidValue)){
      currentOperation = 3;
    }
    // Reset del contatore
    contatoreLoop = 0;
  } 
  // Aggiorna il contatore
  contatoreLoop++;

  switch (currentOperation) {
      case 0:
        followLine();
        break;
      case 1:
        // do something
        labirintoSemplice();
        break;
      case 2:
        rampa();
        break;
      case 3:
        birilli();
        break;
      default:
        followLine();
  }
}
