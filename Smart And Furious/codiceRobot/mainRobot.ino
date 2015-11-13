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

// [FINALI] Pin lettore RFID.
// =====> ATTENZIONE, PIN PREDEFINITI, LEGGERE UltrasonicScanner.h PER SPECIFICHE <=====
// =====> DAL PIN 9 AL PIN 13 SONO RISERVATI <=====
#define RST_PIN 9
#define SS_PIN 10

// Pin TouchSensor
#define tcPinSensoreSinistro 2
#define tcPinSensoreDestro 4


// Inizializza gli oggetti richiesti per eseguire il percorso
Rover *rover;
LineFollower *lf;
TouchSensor *tc;
RFIDReader *rfid;

  
  int START_BARRIERA_MULTIPLA[] = {657};
  int END_BARRIERA_MULTIPLA[] = {420,480,496,642};

  int START_BARRIERA[] = {462};
  int END_BARRIERA[] = {516,542,339,413};

  int START_RAMPA[] = {481};
  int END_RAMPA[] = {419,777,458,562};

  int START_BIRILLI[] = {328};
  int END_BIRILLI[] = {395,269,633,523};

  int termineOstacoli[] = {420,480,496,642,516,542,339,413,419,777,458,562,395,269,633,523};

  int contatoreLoop = 0;


int rfidValue = 0;

int currentOperation = 0;


void labirintoSemplice(){
  rover->setSpeed(150);
  rover->setInternalSpeed(110);
  delay(1000);
  while (rfid->getUID() == 0){
    tc->updateAll();
    if (tc->rightValue == 0){
      rover->stop();
      rover->backward();
      delay(1000);
      rover->setInternalSpeed(-110);
      rover->turnLeft();
      delay(150);
      rover->setInternalSpeed(110);
      
      rover->forward();
    } else if (tc->leftValue == 0){
      rover->stop();
      rover->backward();
      delay(1000);
      rover->setInternalSpeed(-110);
      rover->turnRight();
      delay(150);
      rover->setInternalSpeed(110);
      rover->forward();  
      
    }
    
    
  }

  rfidValue = rfid->getUID();
  contatoreLoop = 11;
  
}



void followLine(){
    rover->setSpeed(180);
  rover->setInternalSpeed(-40);
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
  rover->forward();
  delay(2000);
  rover->turnRightWithDelay(600);
  rover->stop();

  tc->updateAll();
  while(tc->leftValue == 1 && tc->rightValue){
    rover->forward();
    tc->updateAll();
  }
  rover->stop();
  rover->turnLeftWithDelay(800);
  rover->forward();
  
  while (rfid->getUID() == 0){
    tc->updateAll();
    if (tc->rightValue == 0){
      rover->stop();
      rover->backward();
      delay(1000);
      rover->setInternalSpeed(-110);
      rover->turnLeft();
      delay(150);
      rover->setInternalSpeed(110);
      
      rover->forward();
    } else if (tc->leftValue == 0){
      rover->stop();
      rover->backward();
      delay(1000);
      rover->setInternalSpeed(-110);
      rover->turnRight();
      delay(150);
      rover->setInternalSpeed(110);
      rover->forward();  
      
    }
  }

     rfidValue = rfid->getUID();
  contatoreLoop = 11;
  
  
}



void setup()
{
  Serial.begin(9600);
  lf = new LineFollower(pinSensoreSinistro,pinSensoreDestro,pinSensoreCentro);
  rover = new Rover();

  rfid = new RFIDReader(RST_PIN,SS_PIN);
  tc = new TouchSensor(tcPinSensoreSinistro, tcPinSensoreDestro);

  rover->setSpeed(180);
  rover->setInternalSpeed(-70);


}


 bool containsItem(int* rfidVals, int rfidValsLength, int val){
   for (int i = 0; i < rfidValsLength; i++){
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
  
  if (tc->rightValue == 0){
    rover->turnRightWithDelay(80);
  } else if (tc->leftValue == 0){
    rover->turnLeftWithDelay(80);
  } else {
    rover->forward();
  }
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

    if (contatoreLoop >= 10){
        // Ottieni il valore dalla scheda
//        int rfidVals[3] = {};
//        for (int j = 0; j < 3; j++){
//            rfidValue = rfid->getUID();
//            if (rfidValue != 0){
//                break;
//            }
//        }

        rfidValue = rfid->getUID();

        // Se il valore non è "null", procedi a capire che opzione va eseguita
        if (rfidValue != 0){
          Serial.println(rfidValue);
            if (containsItem(termineOstacoli,16, rfidValue)){
                // Torna al follow line
                currentOperation = 0;
            } else if (containsItem(START_BARRIERA_MULTIPLA, 1,  rfidValue)){
                // Nel caso del labirinto complicato, facciamo il follow line
                currentOperation = 4;
            } else if (containsItem(START_BARRIERA,1, rfidValue)){
                currentOperation = 1;
            } else if (containsItem(START_RAMPA,1, rfidValue)){
                currentOperation = 2;  
            } else if (containsItem(START_BIRILLI,1, rfidValue)){
                currentOperation = 3;
            }
        }
        // Reset del contatore
        contatoreLoop = 0;
    }
    // Aggiorna il contatore
    contatoreLoop++;

    switch (currentOperation) {
        case 0:
        Serial.println("FollowLine");
        followLine();
        break;
        case 1:
        // do something
        Serial.println("Labirinto Semplice");
        labirintoSemplice();
        break;
        case 2:
        Serial.println("Rampa");
        rampa();
        break;
        case 3:
        Serial.println("birilli");
        sweep();
        break;
        case 4:
        labirintoSemplice();
        break;
        default:
        followLine();
    }
}
