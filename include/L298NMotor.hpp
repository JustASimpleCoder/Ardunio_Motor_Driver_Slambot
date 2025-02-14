
#ifndef L298NMotor_HPP
#define L298NMotor_HPP
#include "Arduino.h"

enum Direction {
    BACKWARD = 0,
    FORWARD,
};

class Motor{
    private:
        const uint8_t m_pwm_pin;
        const uint8_t m_dir1_pin;
        const uint8_t m_dir2_pin;

        //keep track of variables, useful for testing
        uint8_t m_speed;
        Direction m_dir;
    public:
        Motor(const uint8_t & pwm, const uint8_t & dir1, const uint8_t & dir2);
        
        void setSpeed(const uint8_t & speed);
        void setDirection(bool forward);
        void pinModeSetup();

        uint8_t getSpeed() const;
        Direction getDirection() const;
    
};
#endif

