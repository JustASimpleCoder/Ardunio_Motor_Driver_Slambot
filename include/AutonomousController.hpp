
//OOP abstraction for arduino sketch to control the robot
#ifndef AUTONOMOUSCONTROLLER_HPP
#define AUTONOMOUSCONTROLLER_HPP

// #define ANALOG_WRITE_WHEEL_MAX 255
// #define ANALOG_WRITE_WHEEL_MIN 125


#include "Arduino.h"
#include "L298NMotor.hpp"
#include "MotorCommands.hpp"

class AutonomousController: public MotorCommands
{
private:
    /* data */
public:
    AutonomousController(/* args */);
    ~AutonomousController();
    void loopMotorControl();
};






// enum Direction {
//     BACKWARD = 0,
//     FORWARD,
//  };

// enum class RobotMovement: char{
//     STOP = 'x',
//     MOVE_FORWARD = 'w',
//     MOVE_BACKWARD = 's',
//     MOVE_LEFT = 'l',
//     MOVE_RIGHT = 'r',
//     ROTATE_LEFT = 'a',
//     ROTATE_RIGHT = 'd',
//     DIAG_FORWARD_RIGHT = 'e',
//     DIAG_BACKWARD_RIGHT = 'c',
//     DIAG_FORWARD_LEFT = 'q',
//     DIAG_BACKWARD_LEFT = 'z',
//     FASTER = '+',
//     SLOWER = '-',
//     INVALID = '?'
// };


// class MotorCommands {
//     public:
    
//         MotorCommands();
//         ~MotorCommands(){
//             //stopMotors();
//         }

//         void setupArduino();
//         void loopMotorControl();

//         void setSingleMotorDirection(Motor &motor, const Direction& direction);
//         void setTwoMotorSpeed(      Motor& motor1, Motor& motor2);
//         void setTwoMotorDirection(  Motor& motor1, const Direction& direction1,
//                                     Motor& motor2, const Direction& direction2);
//         void SetAllMotorDirection(  const Direction& left_front_wheel_forward, 
//                                     const Direction& left_back_wheel_forward,
//                                     const Direction& right_front_wheel_forward, 
//                                     const Direction& right_back_wheel_forward);
//         void moveForward();
//         void moveBackward();
//         void moveRight();
//         void moveLeft();

//         void moveForwardRightDiag();
//         void moveForwardLeftDiag();
//         void moveBackwardRightDiag();
//         void moveBackwardLeftDiag();

//         void turnLeft();
//         void turnRight();
        
//         void stopMotors();
//         void stopTwoMotor(Motor & motor1, Motor & motor2);

//         void setMotorSpeed();
//         void changeSpeed(bool increase);
//         void increaseSpeed();
//         void decreaseSpeed();
//         void setStartingSpeed();

//     private:
//         unsigned int m_wheel_speed;

//         Motor m_right_back;
//         Motor m_right_front;
//         Motor m_left_front;
//         Motor m_left_back;
// };

#endif