
//OOP abstraction for arduino sketch to control the robot
#ifndef ARDUINO_CLASS_HPP
#define ARDUINO_CLASS_HPP

#define ANALOG_WRITE_WHEEL_MAX 255
#define ANALOG_WRITE_WHEEL_MIN 125

# define PI 3.14159265358979323846
# define ARDUINO_SERIAL_BAUD_RATE 9600
# define SPEED_INCREASE_STEP 5

#include "Arduino.h"

// const int STOP = 0;
// const int MOVE_FORWARD = 1;
// const int MOVE_BACKWARD = 2;
// const int TURN_LEFT = 3;
// const int TURN_RIGHT = 4;
// const int TURN_LEFT_OPP = 5; // both side of robot move in opposite dir  
// const int TURN_RIGHT_OPP = 6; //both side of robot move in opposite dir  
// const int INVALID = -1;


enum Direction {
    BACKWARD = 0,
    FORWARD,
 };

enum class SpeedLimit {
    MIN = 150,
    MAX = 255
};

template <typename T>
inline bool operator>(T a, SpeedLimit b) {
    return a > static_cast<int>(b);
}

template <typename T>
inline bool operator<(T a, SpeedLimit b) {
    return a < static_cast<int>(b);
}

template <typename T>
inline bool operator==(T a, SpeedLimit b) {
    return a == static_cast<int>(b);
}

template <typename T>
inline bool operator>=(T a, SpeedLimit b) {
    return a >= static_cast<int>(b);
}

template <typename T>
inline bool operator<=(T a, SpeedLimit b) {
    return a <= static_cast<int>(b);
}

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


class MotorCommands {
    public:
        

        MotorCommands();
        ~MotorCommands(){
            //stopMotors();
        }

        void setupArduino();
        void loopMotorControl();

        void setSingleMotorDirection(Motor * motor, Direction direction);
        void setTwoMotorSpeed(Motor * motor1, Motor * motor2);
        void setTwoMotorDirection(  Motor * motor1, Direction direction1,
                                    Motor * motor2, Direction direction2);
        void SetAllMotorDirection(  Direction left_front_wheel_forward, 
                                    Direction left_back_wheel_forward,
                                    Direction right_front_wheel_forward, 
                                    Direction right_back_wheel_forward);
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


        void setMotorSpeed();
        void stopMotors();
        void changeSpeed(bool increase);
        void increaseSpeed();
        void decreaseSpeed();
        void setStartingSpeed();
        //void executeAllWheelMove(RobotMovement direction);
        
    private:
        unsigned int m_wheel_speed;
        
        Motor m_right_back;
        Motor m_right_front;
        Motor m_left_front;
        Motor m_left_back;
};

#endif