#pragma once

#include <Arduino.h>

struct Id
{
  byte bytes[10];
  byte size;
};

void rfid_setup();

bool rfid_get_id(Id& id);