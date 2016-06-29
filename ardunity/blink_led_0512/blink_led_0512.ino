#include "Ardunity.h"
#include "DigitalOutput.h"

DigitalOutput dOutput0(0, 13);

void setup()
{
  ArdunityApp.attachController((ArdunityController*)&dOutput0);
  ArdunityApp.resolution(256, 1024);
  ArdunityApp.timeout(5000);
  ArdunityApp.begin(115200);
}

void loop()
{
  ArdunityApp.process();
}
