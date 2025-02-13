
//OOP abstraction for arduino sketch to control the robot
#ifndef MOTORCOMMANDS_HPP
#define MOTORCOMMANDS_HPP

// #define ANALOG_WRITE_WHEEL_MAX 255
// #define ANALOG_WRITE_WHEEL_MIN 125

constexpr double PI = 3.14159265; // 358979323846
constexpr long ARDUINO_SERIAL_BAUD_RATE = 9600;
constexpr uint8_t SPEED_INCREASE_STEP = 5;
constexpr uint8_t SPEED_LIMIT_MIN = 150;
constexpr uint8_t SPEED_LIMIT_MAX = 255;

constexpr uint8_t PIN_RB_PWM = 5;
constexpr uint8_t PIN_RB_DIR_1 = 2;
constexpr uint8_t PIN_RB_DIR_2 = 3;

constexpr uint8_t PIN_RF_PWM = 6;
constexpr uint8_t PIN_RF_DIR_1 = 4;
constexpr uint8_t PIN_RF_DIR_2 = 7;

constexpr uint8_t PIN_LB_PWM = 9;
constexpr uint8_t PIN_LB_DIR_1 = 11;
constexpr uint8_t PIN_LB_DIR_2 = 8;

constexpr uint8_t PIN_LF_PWM = 10;
constexpr uint8_t PIN_LF_DIR_1 = 13;
constexpr uint8_t PIN_LF_DIR_2 = 12;



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
enum motorPlacement{
    RB = 0,
    RF = 1,
    LF = 2,
    LB = 3
};


class MotorCommands {
    public:
        MotorCommands();
        ~MotorCommands();

        void setMotorSpeed( Motor & motor, const uint8_t & speed);

        void setMotorSpeed( Motor & motor_1, const uint8_t & speed_1,
                            Motor & motor_2, const uint8_t & speed_2);

        void setMotorSpeed( const uint8_t & motor_LF_speed,
                            const uint8_t & motor_LB_speed,
                            const uint8_t & motor_RF_speed,
                            const uint8_t & motor_RB_speed); 

        void setMotorSpeed( const uint8_t & motor_LF_speed);

        void setMotorDirection( Motor & motor, const Direction & direction);

        void setMotorDirection( Motor & motor_1, const Direction & direction_1,
                                Motor & motor_2, const Direction & direction_2);

        void setMotorDirection( const Direction & motor_LF_direction, 
                                const Direction & motor_LB_direction,
                                const Direction & motor_RF_direction, 
                                const Direction & motor_RB_direction);
        
        void stopMotors(Motor & motor);
        void stopMotors(Motor & motor_1, Motor & motor_2);
        void stopMotors();
        
        void setStartingSpeed(Motor & motor);
        void setStartingSpeed(Motor & motor_1, Motor & motor_2);
        void setStartingSpeed();

        void setupArduino();

    protected:
        Motor * m_motors[4] = {&m_motor_RB, &m_motor_RF, &m_motor_LF, &m_motor_LB};
    private:
        Motor m_motor_RB;
        Motor m_motor_RF;
        Motor m_motor_LF;
        Motor m_motor_LB;
};

#endif