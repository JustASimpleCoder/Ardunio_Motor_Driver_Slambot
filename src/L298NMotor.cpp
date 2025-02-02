#include "L298NMotor.hpp"

Motor::Motor(int pwm, int dir1, int dir2)
            : m_pwm_pin(pwm), m_dir1_pin(dir1), m_dir2_pin(dir2) {};

void Motor::setSpeed(int speed) {
    analogWrite(m_pwm_pin, speed);
}

void Motor::setDirection(bool forward) {
    digitalWrite(m_dir1_pin, forward ? HIGH : LOW);
    digitalWrite(m_dir2_pin, forward ? LOW : HIGH);
}

void Motor::pinModeSetup(){
    pinMode(m_pwm_pin, OUTPUT);
    pinMode(m_dir1_pin, OUTPUT);
    pinMode(m_dir2_pin, OUTPUT);
}
