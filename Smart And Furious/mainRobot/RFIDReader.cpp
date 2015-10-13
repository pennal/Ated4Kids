/* Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */


#include "Arduino.h"
#include "RFIDReader.h"

RFIDReader::RFIDReader(int RST_PIN, int SS_PIN){
	mfrc522 = new MFRC522(SS_PIN, RST_PIN);	// Create MFRC522 instance

	SPI.begin();			// Init SPI bus
	mfrc522->PCD_Init();
  Serial.println("RFIDReader Constructed");
}


long RFIDReader::getUID()
{
  // Look for new cards
  if ( ! mfrc522->PICC_IsNewCardPresent()) 
  {
    return 0;
  }
  
  // Select one of the cards
  if ( ! mfrc522->PICC_ReadCardSerial()) 
  {
    return 0;
  }
  
  //Transform Card id in long
  long ret = 0;
  for (byte i = 0; i < mfrc522->uid.size; i++) 
  {
    ret += mfrc522->uid.uidByte[i];
  }   
  
  return ret;
}



void RFIDReader::dumpCard() 
{
  // Dump debug info about the card; PICC_HaltA() is automatically called
  mfrc522->PICC_DumpToSerial(&(mfrc522->uid));
}

void RFIDReader::showCardID() 
{
  //Print Card ID
  for (byte i = 0; i < mfrc522->uid.size; i++) {
    Serial.print(mfrc522->uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522->uid.uidByte[i], HEX);
  } 
  Serial.println();
}

void RFIDReader::showReaderDetails() {
  // Get the MFRC522 software version
  byte v = mfrc522->PCD_ReadRegister(mfrc522->VersionReg);
  Serial.print("MFRC522 Software Version: 0x");
  Serial.print(v, HEX);
  if (v == 0x91)
    Serial.print(" = v1.0");
  else if (v == 0x92)
    Serial.print(" = v2.0");
  else
    Serial.print(" (unknown)");
  
  Serial.println("");
  // When 0x00 or 0xFF is returned, communication probably failed
  if ((v == 0x00) || (v == 0xFF)) {
    Serial.println("WARNING: Communication failure, is the MFRC522 properly connected?");
  }
}
