
//OOP abstraction for arduino sketch to control the robot
#ifndef ARDUINO_CLASS_HPP
#define ARDUINO_CLASS_HPP

#define ANALOG_WRITE_WHEEL_MAX 255
#define ANALOG_WRITE_WHEEL_MIN 125

# define PI 3.14159265358979323846
# define ARDUINO_SERIAL_BAUD_RATE 9600

#include "Arduino.h"

// const int STOP = 0;
// const int MOVE_FORWARD = 1;
// const int MOVE_BACKWARD = 2;
// const int TURN_LEFT = 3;
// const int TURN_RIGHT = 4;
// const int TURN_LEFT_OPP = 5; // both side of robot move in opposite dir  
// const int TURN_RIGHT_OPP = 6; //both side of robot move in opposite dir  
// const int INVALID = -1;

enum class SpeedLimit {
    MIN = 125,
    MAX = 255
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

class Motor{
    private:
        int m_pwm_pin;
        int m_dir1_pin;
        int m_dir2_pin;
    public:
        Motor(int pwm, int dir1, int dir2)
            : m_pwm_pin(pwm), m_dir1_pin(dir1), m_dir2_pin(dir2) {}

        void setSpeed(int speed);
        void setDirection(bool forward);
        void pinModeSetup();
};

class MotorCommands {
    public:
        unsigned int m_wheel_speed;
        MotorCommands()
            :   m_wheel_speed(0),
                right_back(6, 4, 7), 
                right_front(5,2,3),
                left_front(9,11,8), 
                left_back(10,13,12)
                {}
        
        ~MotorCommands(){
            //stopMotors();
        }
    
        void getMotorData();
        
        void getOdom();

        void setupArduino();

        void SetSingleMotorDir(bool forward);

        void SetMotorDir(bool left_front_wheel_forward, bool left_back_wheel_forward,
                                bool right_front_wheel_forward, bool right_back_wheel_forward);

        void SetMotorDirTest();
        void SetMotorSpeed();

        void stopMotors();

        void moveForward();
        void moveBackward();


        void turnLeft();
        void turnRight();

        void moveRight();
        void moveLeft();

        void moveForwardRightDiag();
        void moveForwardLeftDiag();

        void moveBackwardRightDiag();
        void moveBackwardLeftDiag();
        

        void changeSpeed(bool increase);

        void increaseSpeed();

        void decreaseSpeed();

        void setStartingSpeed();

        void loopMotorControl();

        void turn(bool right);
        
    private:
        Motor right_back;
        Motor right_front;
        Motor left_front;
        Motor left_back;
        
        bool m_forwards = true;
        bool m_backwards = false;

        //3 inches is diamter -> 0.0762 m D -> 0.0281 for radius
        double m_wheel_radius = 0.0281;
        double m_wheel_circum  = 2*PI*m_wheel_radius;
        double m_wheel_base = 0.16002;
};
#endif