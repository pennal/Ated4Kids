// nero = 0
// bianco = 1
int E1 = 6;
int E2 = 5;
int M1 = 8;
int M2 = 7;
int BNa = 11;
int BNb = 12;
int Centro = 10;
int Speed;
int Meta;

void setup()
{
  int i;
  for(i=5;i<=8;i++)
    pinMode(i, OUTPUT);
  pinMode(BNa, INPUT);
  pinMode(BNb, INPUT);
  pinMode(Centro, INPUT);
  
  Serial.begin(9600);
}
void STOP()
{
  analogWrite (E1,0);
  digitalWrite(M1,HIGH);
  analogWrite (E2,0);
  digitalWrite(M2,HIGH);
}
void destra()
{
  analogWrite (E1,Meta);
  digitalWrite(M1,LOW);
  analogWrite (E2,Speed);
  digitalWrite(M2,HIGH);
  //delay(30);
  //STOP();
}
void sinistra()
{
  analogWrite (E1,Speed);
  digitalWrite(M1,HIGH);
  analogWrite (E2, Meta);
  digitalWrite(M2,LOW);
  //delay(30);
  //STOP();
}
void dritto()
{
  analogWrite (E1,Speed);
  digitalWrite(M1,HIGH);
  analogWrite (E2,Speed);
  digitalWrite(M2,HIGH);
  //delay(30);
  //STOP();
}
void loop()
{
  int valBNa = digitalRead(BNa);
  int valBNb = digitalRead(BNb);
  int valCentro = digitalRead(Centro);

  
  Serial.print("Bna: ");
  Serial.print(valBNa);

  Serial.print("; Bnb: ");
  Serial.print(valBNb);
  Serial.println();

  if (valCentro == 0) {
    Speed = 180;
  } else {
    Speed = 140;
  }

  if (valBNa == 0 && valBNb == 1){
    //Speed = 70;
    Meta = Speed + 60;
      destra();  
  } else if (valBNa == 1 && valBNb == 0) {
    //Speed = 70;
      Meta = Speed + 60;
      sinistra();  
  } else if(valBNa == 0 && valBNb == 0) {
    dritto();
  } else {
    //Speed = 90;
      dritto();
  }
  delay(30);
  
}
