
#ifndef AUTONOMOUSCONTROLLER_HPP
#define AUTONOMOUSCONTROLLER_HPP

#include "Arduino.h"
#include "L298NMotor.hpp"
#include "MotorCommands.hpp"

constexpr uint8_t BUFFER_SIZE = 26;

struct VelCmdValues
{
    uint8_t pwm_values[4] = {0,0,0,0};
    Direction dir_values[4] = {FORWARD,FORWARD,FORWARD,FORWARD};
};

class AutonomousController: public MotorCommands
{
    public:
        AutonomousController();
        ~AutonomousController();
        VelCmdValues parseMessage(const char* buffer);
        void updateSpeedAndDirection(const VelCmdValues & cmd_vel);
        void updateMotorControl();

    private:
        
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