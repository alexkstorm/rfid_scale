
#include "rfid.h"

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 22
#define SS_PIN  21
// Assuming SPI(VSPI) pins
// SCK 18
// MISO 19 
// MOSI 23

namespace {

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

} // namespace

void rfid_setup()
{
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

bool rfid_get_id(Id& id)
{
	if (!mfrc522.PICC_IsNewCardPresent()) {
		return false;
	}

	if (!mfrc522.PICC_ReadCardSerial()) {
		return false;
	}

  //Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  //Serial.println(mfrc522.PICC_GetTypeName(piccType));

  memcpy(id.bytes, mfrc522.uid.uidByte, mfrc522.uid.size);
  id.size = mfrc522.uid.size;

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  return true;
}