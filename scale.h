#pragma once

#include <Arduino.h>

void scale_setup();

float scale_get_weight(); // [g]

void scale_calibrate();