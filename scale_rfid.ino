
#include <Arduino.h>

#include "rfid.h"
#include "scale.h"

void print_hex(byte *buffer, byte size)
{
  for (byte i = 0; i < size; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

void setup()
{
  Serial.begin(115200);
  scale_setup();
  rfid_setup();
}

Id id;

void loop()
{
  if(!rfid_get_id(id)) {
    return;
  }

  Serial.println(F("The tag ID is:"));
  Serial.print(F("In hex: "));
  print_hex(id.bytes, id.size);
  Serial.println();

  const float weight = scale_get_weight();
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" g");
  Serial.println();
}