#include "MotorCommands.hpp"

MotorCommands::MotorCommands():        
                    m_motor_RB(PIN_RB_PWM, PIN_RB_DIR_1, PIN_RB_DIR_2), 
                    m_motor_RF(PIN_RF_PWM, PIN_RF_DIR_1, PIN_RF_DIR_2),
                    m_motor_LF(PIN_LB_PWM, PIN_LB_DIR_1, PIN_LB_DIR_2), 
                    m_motor_LB(PIN_LF_PWM, PIN_LF_DIR_1, PIN_LF_DIR_2)
                    {};

MotorCommands::~MotorCommands(){}

void MotorCommands::setMotorSpeed(Motor& motor, const uint8_t& speed){
    constrain(speed, SPEED_LIMIT_MIN, SPEED_LIMIT_MAX);
    motor.setSpeed(speed);
}

void MotorCommands::setMotorSpeed(  Motor& motor_1, const uint8_t& speed_1,
                                    Motor& motor_2, const uint8_t& speed_2)
{                  
    setMotorSpeed(motor_1, speed_1);
    setMotorSpeed(motor_2, speed_2);
}

void MotorCommands::setMotorSpeed(  const uint8_t& motor_LF_speed,
                                    const uint8_t& motor_LB_speed,
                                    const uint8_t& motor_RF_speed,
                                    const uint8_t& motor_RB_speed)
{
    setMotorSpeed(m_motor_LF, motor_LF_speed);
    setMotorSpeed(m_motor_LB, motor_LB_speed);
    setMotorSpeed(m_motor_RF, motor_RF_speed);
    setMotorSpeed(m_motor_RB, motor_RB_speed);
}

void MotorCommands::setMotorSpeed( const uint8_t& speed){
    setMotorSpeed(speed, speed, speed, speed);
}

void MotorCommands::setMotorDirection(Motor& motor, const Direction& direction){
    motor.setDirection(direction);
}


void MotorCommands::setMotorDirection(  Motor& motor_1, const Direction& direction_1,
                                        Motor& motor_2, const Direction& direction_2)
{                                            
    setMotorDirection(motor_1, direction_1);
    setMotorDirection(motor_2, direction_2);
}

void MotorCommands::setMotorDirection(const Direction& motor_LF_direction, 
                                      const Direction& motor_LB_direction,
                                      const Direction& motor_RF_direction, 
                                      const Direction& motor_RB_direction)
{
    setMotorDirection(m_motor_LF, motor_LF_direction);
    setMotorDirection(m_motor_LB, motor_LB_direction);
    setMotorDirection(m_motor_RF, motor_RF_direction);
    setMotorDirection(m_motor_RB, motor_RB_direction);
}

void MotorCommands::stopMotors(Motor& motor){
    setMotorSpeed(motor, 0);
}

void MotorCommands::stopMotors(Motor& motor_1, Motor& motor_2){
    stopMotors(motor_1);
    stopMotors(motor_2);
}
void MotorCommands::stopMotors()
{
    stopMotors(m_motor_LF);
    stopMotors(m_motor_LB);
    stopMotors(m_motor_RF);
    stopMotors(m_motor_RB);
}

void MotorCommands::setStartingSpeed(Motor& motor){
    setMotorSpeed(motor, SPEED_LIMIT_MIN);
}

void MotorCommands::setStartingSpeed(Motor& motor_1, Motor& motor_2){
    setStartingSpeed(motor_1);
    setStartingSpeed(motor_2);
}

void MotorCommands::setStartingSpeed()
{
    setStartingSpeed(m_motor_LF);
    setStartingSpeed(m_motor_LB);
    setStartingSpeed(m_motor_RF);
    setStartingSpeed(m_motor_RB);
}

void MotorCommands::setupArduino()
{
    m_motor_LF.pinModeSetup();
    m_motor_LB.pinModeSetup();
    m_motor_RF.pinModeSetup();
    m_motor_RB.pinModeSetup();

    Serial.begin(ARDUINO_SERIAL_BAUD_RATE);
}

Motor ** MotorCommands::getMotors(){
    return m_motors;
}
