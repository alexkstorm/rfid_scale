
#include "scale.h"

#include <HX711.h>

#define DOUT_PIN 16
#define SCK_PIN  4

namespace {

HX711 scale;

} // namespace

void scale_setup()
{
  scale.begin(DOUT_PIN, SCK_PIN, false);
  scale.set_offset(-257102);
  scale.set_scale(448.689789);
  scale.set_average_mode();
  scale.tare();
}

float scale_get_weight()
{
  return scale.get_units(5); // Sample 5 times, average of 5 if average mode.
}

void scale_calibrate()
{
  Serial.println("\n\nCALIBRATION\n===========");
  Serial.println("remove all weight from the loadcell");
  //  flush Serial input
  while (Serial.available()) Serial.read();

  Serial.println("and press enter\n");
  while (Serial.available() == 0);

  Serial.println("Determine zero weight offset");
  //  average 20 measurements.
  scale.tare(20);
  int32_t offset = scale.get_offset();

  Serial.print("OFFSET: ");
  Serial.println(offset);
  Serial.println();


  Serial.println("place a weight on the loadcell");
  //  flush Serial input
  while (Serial.available()) Serial.read();

  Serial.println("enter the weight in (whole) grams and press enter");
  uint32_t weight = 0;
  while (Serial.peek() != '\n')
  {
    if (Serial.available())
    {
      char ch = Serial.read();
      if (isdigit(ch))
      {
        weight *= 10;
        weight = weight + (ch - '0');
      }
    }
  }
  Serial.print("WEIGHT: ");
  Serial.println(weight);
  scale.calibrate_scale(weight, 20);
  float scale_factor = scale.get_scale();

  Serial.print("SCALE:  ");
  Serial.println(scale_factor, 6);

  Serial.print("\nuse scale.set_offset(");
  Serial.print(offset);
  Serial.print("); and scale.set_scale(");
  Serial.print(scale_factor, 6);
  Serial.print(");\n");
  Serial.println("in the setup of your project");

  Serial.println("\n\n");
}