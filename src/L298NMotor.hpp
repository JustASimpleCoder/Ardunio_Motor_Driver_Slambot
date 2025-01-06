
#ifndef L298NMotor_HPP
#define L298NMotor_HPP
#include "Arduino.h"
class Motor{
    private:
        int m_pwm_pin;
        int m_dir1_pin;
        int m_dir2_pin;
    public:
        Motor(int pwm, int dir1, int dir2);
        
        void setSpeed(int speed);
        void setDirection(bool forward);
        void pinModeSetup();
};
#endif

