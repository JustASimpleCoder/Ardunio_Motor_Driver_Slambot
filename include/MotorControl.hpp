
//OOP abstraction for arduino sketch to control the robot
#ifndef ARDUINO_CLASS_HPP
#define ARDUINO_CLASS_HPP

// #define ANALOG_WRITE_WHEEL_MAX 255
// #define ANALOG_WRITE_WHEEL_MIN 125

# define PI 3.14159265 // 358979323846
# define ARDUINO_SERIAL_BAUD_RATE 9600
# define SPEED_INCREASE_STEP 5
# define SPEED_LIMIT_MIN 150
# define SPEED_LIMIT_MAX 255

# define PIN_RB_PWM 5
# define PIN_RB_DIR_1 2
# define PIN_RB_DIR_2 3

# define PIN_RF_PWM 6
# define PIN_RF_DIR_1 4
# define PIN_RF_DIR_2 7

# define PIN_LB_PWM 9
# define PIN_LB_DIR_1 11
# define PIN_LB_DIR_2 8

# define PIN_LF_PWM 10
# define PIN_LF_DIR_1 13
# define PIN_LF_DIR_2 12



#include "Arduino.h"
#include "L298NMotor.hpp"

enum Direction {
    BACKWARD = 0,
    FORWARD,
 };

enum class RobotMovement: char{
    STOP = 'x',
    MOVE_FORWARD = 'w',
    MOVE_BACKWARD = 's',
    MOVE_LEFT = 'l',
    MOVE_RIGHT = 'r',
    ROTATE_LEFT = 'a',
    ROTATE_RIGHT = 'd',
    DIAG_FORWARD_RIGHT = 'e',
    DIAG_BACKWARD_RIGHT = 'c',
    DIAG_FORWARD_LEFT = 'q',
    DIAG_BACKWARD_LEFT = 'z',
    FASTER = '+',
    SLOWER = '-',
    INVALID = '?'
};


class MotorCommands {
    public:
    
        MotorCommands();
        ~MotorCommands(){
            //stopMotors();
        }

        void setupArduino();
        void loopMotorControl();

        void setSingleMotorDirection(Motor &motor, const Direction& direction);
        void setTwoMotorSpeed(      Motor& motor1, Motor& motor2);
        void setTwoMotorDirection(  Motor& motor1, const Direction& direction1,
                                    Motor& motor2, const Direction& direction2);
        void SetAllMotorDirection(  const Direction& left_front_wheel_forward, 
                                    const Direction& left_back_wheel_forward,
                                    const Direction& right_front_wheel_forward, 
                                    const Direction& right_back_wheel_forward);
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
        
        void stopMotors();

        void stopTwoMotor(Motor & motor1, Motor & motor2);
        void setMotorSpeed();

        void changeSpeed(bool increase);
        void increaseSpeed();
        void decreaseSpeed();
        void setStartingSpeed();
        
    private:
        unsigned int m_wheel_speed;

        Motor m_right_back;
        Motor m_right_front;
        Motor m_left_front;
        Motor m_left_back;
};

#endif