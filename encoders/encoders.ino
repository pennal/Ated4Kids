int E1 = 6; //M1 Speed Control
int E2 = 5; //M2 Speed Control
int M1 = 8; //M1 Direction Control
int M2 = 7; //M2 Direction Control


void setup() {
    int i;
    for(i=5;i<=8;i++)
        pinMode(i, OUTPUT);
    Serial.begin(9600);
    
    int leftspeed = 255; //255 is maximum speed
    int rightspeed = 255;
}

/**
 *  Returns the number of clicks required for the length given as an input
 *
 *  @param lengthInCm Length in cm
 *
 *  @return Number of clicks needed
 */
double numberOfClicksForLength(double lengthInCm){
    int diameterOfWheelInMM = 32;
    double lengthOfRotation = 2*3.14*(diameterOfWheelInMM/20.0);
    double ratioOfLength = lengthInCm/lengthOfRotation;
    double numberOfClicks = 16 * ratioOfLength;
    
    return numberOfClicks;
}

/**
 *  Create an artificial delay, by using the required clicks to be elapsed before continuing
 *
 *  @param numberOfClicks Number of clicks required for the desired length. Obtained through double numberOfClickForLength(..)
 */
void delayForNumberOfClicks(double numberOfClicks){
    int rawsensorValue = 0; // variable to store the value coming from the sensor
    int sensorcount0 = 0;
    int sensorcount1 = 0;
    long count = 0;
    
    
    
    while(count <= numberOfClicks){
        analogWrite (10,255);
        digitalWrite(12,LOW);
        analogWrite (11,255);
        digitalWrite(13,LOW);
        delay(20);
        rawsensorValue = analogRead(0);
        if (rawsensorValue < 720){ //Min value is 400 and max value is 800, so state chance can be done at 600.
            sensorcount1 = 1;
        } else {
            sensorcount1 = 0;
        }
        
        if (sensorcount1 != sensorcount0){
            count ++;
        }
        sensorcount0 = sensorcount1;
    }
    
    rawsensorValue = 0; // variable to store the value coming from the sensor
    sensorcount0 = 0;
    sensorcount1 = 0;
    count = 0;
}

/**
 *  Move forward
 *
 *  @param cm amount in Cm tho which the robot has to move
 */
void moveForward(double cm){
    double numberOfClicks = numberOfClicksForLength(cm);
    
    // Move forward
    analogWrite (E1,255);
    digitalWrite(M1,HIGH);
    analogWrite (E2,255);
    digitalWrite(M2,HIGH);
    
    
    delayForNumberOfClicks(numberOfClicks);
    
    analogWrite (E1,255);
    digitalWrite(M1,LOW);
    analogWrite (E2,255);
    digitalWrite(M2,LOW);
    delay(50);
    analogWrite (E1,0);
    digitalWrite(M1,LOW);
    analogWrite (E2,0);
    digitalWrite(M2,LOW);
    
}

void moveBackwards(double cm){
    double numberOfClicks = numberOfClicksForLength(cm);
    
    // Move backwards
    analogWrite (E1,255);
    digitalWrite(M1,LOW);
    analogWrite (E2,255);
    digitalWrite(M2,LOW);
    
    
    delayForNumberOfClicks(numberOfClicks);
    
    analogWrite (E1,255);
    digitalWrite(M1,HIGH);
    analogWrite (E2,255);
    digitalWrite(M2,HIGH);
    delay(50);
    
    analogWrite (E1,0);
    digitalWrite(M1,LOW);
    analogWrite (E2,0);
    digitalWrite(M2,LOW);
    
}


void loop() {
    moveForward(20);
    delay(2000);
    moveBackwards(20);
    delay(2000);
    
}
