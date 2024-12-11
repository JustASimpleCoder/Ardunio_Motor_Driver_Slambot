#include "MotorControl.hpp"

// put function declarations here:
MotorCommands commands;

void setup() {
    commands.setupArduino();
}

void loop() {
    commands.loopMotorControl();
}
