// nero = 0
// bianco = 1

// Definisci tutti i pin per i diversi motori/sensori
#define E1 6
#define E2 5
#define M1 8
#define M2 7

#define pinSensoreSinistro 11
#define pinSensoreDestro 12


//int pinSensoreSinistro = 11;
//int pinSensoreDestro = 12;
int Speed = 255;
int valoreDaSottrarreAVelocita = 10;


int primaSinistra = 1;
int primaDestra = 1;

void setup()
{
  int i;
  for(i=5;i<=8;i++)
    pinMode(i, OUTPUT);
  pinMode(pinSensoreSinistro, INPUT);
  pinMode(pinSensoreDestro, INPUT);
  
  Serial.begin(9600);
}
void STOP()
{
  analogWrite (E1,Speed);
  digitalWrite(M1,LOW);
  analogWrite (E2,Speed);
  digitalWrite(M2,LOW);
  delay(50);
  analogWrite (E1,0);
  digitalWrite(M1,LOW);
  analogWrite (E2,0);
  digitalWrite(M2,LOW);  
}
void sinistra()
{
  
  analogWrite (E1,Speed - valoreDaSottrarreAVelocita);
  digitalWrite(M1,LOW);
  analogWrite (E2,Speed);
  digitalWrite(M2,HIGH);
}
void destra()
{
  analogWrite (E1,Speed);
  digitalWrite(M1,HIGH);
  analogWrite (E2, Speed - valoreDaSottrarreAVelocita);
  digitalWrite(M2,LOW);
}
void dritto()
{
  analogWrite (E1,Speed);
  digitalWrite(M1,HIGH);
  analogWrite (E2,Speed);
  digitalWrite(M2,HIGH);
}
void loop()
{
  
  
  // Leggi valore dei sensori. Puo essere 0 o 1. Rispettivamente nero e bianco
  int valoreSensoreSinistro = digitalRead(pinSensoreSinistro);
  int valoreSensoreDestro = digitalRead(pinSensoreDestro);
  
  Serial.print("Sinistra: ");
  Serial.print(valoreSensoreSinistro);
  Serial.print("Destra: ");
  Serial.println(valoreSensoreDestro);
  
  
  
  if (primaSinistra != valoreSensoreSinistro || primaDestra != valoreSensoreDestro){
    STOP();
  }
  
  primaSinistra = valoreSensoreSinistro;
  primaDestra = valoreSensoreDestro;
  

  if (valoreSensoreSinistro == 0 && valoreSensoreDestro == 1){
    Speed = 150;
      sinistra();  
  } else if (valoreSensoreSinistro == 1 && valoreSensoreDestro == 0) {
      Speed = 150;
      destra();  
  } else {
    Speed = 200;
    dritto();
  }
  

}
