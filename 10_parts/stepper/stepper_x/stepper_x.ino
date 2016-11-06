#include "AccelStepper.h"

#define X_STEP_PIN 54
#define X_DIR_PIN 55
#define X_ENABLE_PIN 38


//x-motor
//#define X_STEP_PIN 54
//#define X_DIR_PIN 55
//#define X_ENABLE_PIN 38

//y-motor
//#define Y_STEP_PIN         60
//#define Y_DIR_PIN          61
//#define Y_ENABLE_PIN       56

//z-motor
//#define Z_STEP_PIN         46
//#define Z_DIR_PIN          48
//#define Z_ENABLE_PIN       62

AccelStepper stepper(1, X_STEP_PIN, X_DIR_PIN); // 1 = Driver

int targetvalue = 1000;

void setup() {
  //stepper.setMaxSpeed(500);
  stepper.setAcceleration(1000);

  stepper.setEnablePin(X_ENABLE_PIN); 
  stepper.setPinsInverted(false, false, true); //invert logic of enable pin
  stepper.enableOutputs();
  stepper.setSpeed(1000);
}

void loop() { 
  //stepper.runSpeed();
  stepper.runToNewPosition(0);

  stepper.moveTo(targetvalue);
  while (stepper.currentPosition() != targetvalue)
    stepper.run();
   
  stepper.runToNewPosition(0);

  stepper.moveTo(-targetvalue);
  while (stepper.currentPosition() != -targetvalue)
    stepper.run();
 
  //stepper.setCurrentPosition(600);

}

