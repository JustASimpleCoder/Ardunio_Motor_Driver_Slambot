
//OOP abstraction for arduino sketch to control the robot
#ifndef ManualMotorControl_HPP
#define ManualMotorControl_HPP

#include "Arduino.h"
#include "L298NMotor.hpp"
#include "MotorCommands.hpp"

class ManualControl : public MotorCommands{
    public:
    
        ManualControl();
        ~ManualControl();

        void moveForward();
        void moveBackward();
        void moveRight();
        void moveLeft();

        void moveForwardRightDiag();
        void moveForwardLeftDiag();
        void moveBackwardRightDiag();
        void moveBackwardLeftDiag();

        void turnLeft();
        void turnRight();
               
        void changeSpeed(bool increase);
        void increaseSpeed();
        void decreaseSpeed();

        uint8_t getWheelSpeed();
        
        void updateMotorControl();

    private:
        uint8_t m_wheel_speed;
};

#endif