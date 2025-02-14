#include <AUnit.h>
#include "ManualMotorControl.hpp"
#include "ManualMotorControl.cpp"  // Include the source file

#include "L298NMotor.hpp"
#include "L298NMotor.cpp"

// Test fixture for ManualControl
ManualControl manualControl;
test(ManualControlTest) {
    Motor ** motors = manualControl.getMotors();

    // Test moveForward
    manualControl.moveForward();
    assertEqual(motors[LF]->getSpeed(), manualControl.getWheelSpeed());
    assertEqual(motors[LB]->getSpeed(), manualControl.getWheelSpeed());
    assertEqual(motors[RF]->getSpeed(), manualControl.getWheelSpeed());
    assertEqual(motors[RB]->getSpeed(), manualControl.getWheelSpeed());
    assertEqual(motors[LF]->getDirection(), FORWARD);
    assertEqual(motors[LB]->getDirection(), BACKWARD);
    assertEqual(motors[RF]->getDirection(), FORWARD);
    assertEqual(motors[RB]->getDirection(), BACKWARD);

    // Test moveBackward
    manualControl.moveBackward();
    assertEqual(motors[LF]->getSpeed(), manualControl.getWheelSpeed());
    assertEqual(motors[LB]->getSpeed(), manualControl.getWheelSpeed());
    assertEqual(motors[RF]->getSpeed(), manualControl.getWheelSpeed());
    assertEqual(motors[RB]->getSpeed(), manualControl.getWheelSpeed());
    assertEqual(motors[LF]->getDirection(), BACKWARD);
    assertEqual(motors[LB]->getDirection(), FORWARD);
    assertEqual(motors[RF]->getDirection(), BACKWARD);
    assertEqual(motors[RB]->getDirection(), FORWARD);

    // Test turnLeft
    manualControl.turnLeft();
    assertEqual(motors[LF]->getSpeed(), manualControl.getWheelSpeed());
    assertEqual(motors[LB]->getSpeed(), manualControl.getWheelSpeed());
    assertEqual(motors[RF]->getSpeed(), manualControl.getWheelSpeed());
    assertEqual(motors[RB]->getSpeed(), manualControl.getWheelSpeed());

    assertEqual(motors[LF]->getDirection(), BACKWARD);
    assertEqual(motors[LB]->getDirection(), FORWARD);
    assertEqual(motors[RF]->getDirection(), FORWARD);
    assertEqual(motors[RB]->getDirection(), BACKWARD);

     // Test turnRight
     manualControl.turnRight();
     assertEqual(motors[LF]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[LB]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[RF]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[RB]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[LF]->getDirection(), FORWARD);
     assertEqual(motors[LB]->getDirection(), BACKWARD);
     assertEqual(motors[RF]->getDirection(), BACKWARD);
     assertEqual(motors[RB]->getDirection(), FORWARD);
 
     // Test moveLeft
     manualControl.moveLeft();
     assertEqual(motors[LF]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[LB]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[RF]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[RB]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[LF]->getDirection(), BACKWARD);
     assertEqual(motors[LB]->getDirection(), BACKWARD);
     assertEqual(motors[RF]->getDirection(), FORWARD);
     assertEqual(motors[RB]->getDirection(), FORWARD);
 
     // Test moveRight
     manualControl.moveRight();
     assertEqual(motors[LF]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[LB]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[RF]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[RB]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[LF]->getDirection(), FORWARD);
     assertEqual(motors[LB]->getDirection(), FORWARD);
     assertEqual(motors[RF]->getDirection(), BACKWARD);
     assertEqual(motors[RB]->getDirection(), BACKWARD);
 
     // Test moveForwardRightDiag
     manualControl.moveForwardRightDiag();
     assertEqual(motors[LF]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[RB]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[LB]->getSpeed(), 0);
     assertEqual(motors[RF]->getSpeed(), 0);
     assertEqual(motors[LF]->getDirection(), FORWARD);
     assertEqual(motors[RB]->getDirection(), BACKWARD);
 
     // Test moveForwardLeftDiag
     manualControl.moveForwardLeftDiag();
     assertEqual(motors[LB]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[RF]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[LF]->getSpeed(), 0);
     assertEqual(motors[RB]->getSpeed(), 0);
     assertEqual(motors[LB]->getDirection(), FORWARD);
     assertEqual(motors[RF]->getDirection(), BACKWARD);
 
     // Test moveBackwardRightDiag
     manualControl.moveBackwardRightDiag();
     assertEqual(motors[LF]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[RB]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[LB]->getSpeed(), 0);
     assertEqual(motors[RF]->getSpeed(), 0);
     assertEqual(motors[LF]->getDirection(), FORWARD);
     assertEqual(motors[RB]->getDirection(), BACKWARD);
 
     // Test moveBackwardLeftDiag
     manualControl.moveBackwardLeftDiag();
     assertEqual(motors[LB]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[RF]->getSpeed(), manualControl.getWheelSpeed());
     assertEqual(motors[LF]->getSpeed(), 0);
     assertEqual(motors[RB]->getSpeed(), 0);
     assertEqual(motors[LB]->getDirection(), FORWARD);
     assertEqual(motors[RF]->getDirection(), BACKWARD);
}

void setup() {
    delay(1000);  // Wait for serial monitor to open
    manualControl.setupArduino();
    //Serial.begin(9600);
   // while (!Serial);  // For boards with native USB
}

void loop() {
    aunit::TestRunner::run();
}