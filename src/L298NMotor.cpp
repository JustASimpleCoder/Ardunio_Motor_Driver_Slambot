#include "L298NMotor.hpp"

Motor::Motor(const uint8_t & pwm, const uint8_t & dir1, const uint8_t & dir2)
            :   m_pwm_pin(pwm), m_dir1_pin(dir1), m_dir2_pin(dir2),
                m_speed(0), m_dir(FORWARD) {};

void Motor::setSpeed(const uint8_t & speed) {
    analogWrite(m_pwm_pin, speed);
    m_speed = speed;
}

void Motor::setDirection(bool forward) {
    digitalWrite(m_dir1_pin, forward ? HIGH : LOW);
    digitalWrite(m_dir2_pin, forward ? LOW : HIGH);
    m_dir = static_cast<Direction>(forward);
}

void Motor::pinModeSetup(){
    pinMode(m_pwm_pin, OUTPUT);
    pinMode(m_dir1_pin, OUTPUT);
    pinMode(m_dir2_pin, OUTPUT);
}

uint8_t Motor::getSpeed() const {
    return m_speed;
}

Direction Motor::getDirection() const {
    return m_dir;
}
