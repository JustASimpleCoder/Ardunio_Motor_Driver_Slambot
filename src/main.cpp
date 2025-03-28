#include "ManualMotorControl.hpp"
#include "MotorCommands.hpp"
#define MANUAL true

#if MANUAL
ManualControl commands;
#else
//AutonomousControl commands
#endif

void setup() { 
    commands.setupArduino(); 
}

void loop() {
    commands.updateMotorControl();
}
