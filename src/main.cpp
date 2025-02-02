#include "MotorControl.hpp"
MotorCommands commands;

void setup() {
    commands.setupArduino();
}

void loop() {
    commands.loopMotorControl();
}
