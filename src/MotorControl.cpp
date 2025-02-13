#include "MotorControl.hpp"


MotorCommands::MotorCommands()
                :   m_wheel_speed(0),
                    m_right_back(PIN_RB_PWM, PIN_RB_DIR_1, PIN_RB_DIR_2), 
                    m_right_front(PIN_RF_PWM, PIN_RF_DIR_1, PIN_RF_DIR_2),
                    m_left_front(PIN_LB_PWM, PIN_LB_DIR_1, PIN_LB_DIR_2), 
                    m_left_back(PIN_LF_PWM, PIN_LF_DIR_1,PIN_LF_DIR_2)
                {};

void MotorCommands::increaseSpeed() {
   changeSpeed(true);
}

void MotorCommands::decreaseSpeed() {
   changeSpeed(false);
}

void MotorCommands::changeSpeed(bool increase) {
    m_wheel_speed += (increase) ?  SPEED_INCREASE_STEP : -SPEED_INCREASE_STEP;   
    m_wheel_speed = constrain(m_wheel_speed, SPEED_LIMIT_MIN, SPEED_LIMIT_MAX);
    setMotorSpeed();
}

void MotorCommands::setStartingSpeed() {
    if (m_wheel_speed == 0){
        m_wheel_speed = SPEED_LIMIT_MIN; //static_cast<int>(SpeedLimit::MIN);
    }
}

void MotorCommands::setSingleMotorDirection(Motor& motor, const Direction& direction){
    motor.setDirection(direction);
}

void MotorCommands::setTwoMotorDirection(   Motor& motor1, const Direction& direction1,
                                            Motor& motor2, const Direction& direction2){                                            
    motor1.setDirection(direction1);
    motor2.setDirection(direction2);
}

void MotorCommands::setTwoMotorSpeed(Motor& motor1, Motor& motor2){                    
    motor1.setSpeed(m_wheel_speed);
    motor2.setSpeed(m_wheel_speed);
}


void MotorCommands::SetAllMotorDirection(
                    const Direction& left_front_wheel_forward, 
                    const Direction& left_back_wheel_forward,
                    const Direction& right_front_wheel_forward, 
                    const Direction& right_back_wheel_forward){
    // motor wont start turning until pwm signal is approx ~120 - 150
    setStartingSpeed();
    m_right_front.setDirection(right_front_wheel_forward);
    m_right_back.setDirection(right_back_wheel_forward);

    m_left_front.setDirection(left_front_wheel_forward);
    m_left_back.setDirection(left_back_wheel_forward);
    setMotorSpeed();
}

void MotorCommands::stopMotors() {
    //Serial.println("stopping motor");
    m_wheel_speed = 0;
    
    m_right_back.setSpeed(0);
    m_right_front.setSpeed(0);

    m_left_back.setSpeed(0);
    m_left_front.setSpeed(0);
}
void MotorCommands::stopTwoMotor(Motor & motor1, Motor & motor2){
    motor1.setSpeed(0);
    motor2.setSpeed(0);
}

void MotorCommands::setMotorSpeed(){
    m_right_back.setSpeed(m_wheel_speed);
    m_right_front.setSpeed(m_wheel_speed);

    m_left_back.setSpeed(m_wheel_speed);
    m_left_front.setSpeed(m_wheel_speed);
}

void MotorCommands::moveForward() {
    SetAllMotorDirection(FORWARD, BACKWARD, FORWARD, BACKWARD);
}

void MotorCommands::moveBackward() {
    SetAllMotorDirection(BACKWARD, FORWARD, BACKWARD, FORWARD);
}

void MotorCommands::turnLeft() {
    SetAllMotorDirection(BACKWARD, FORWARD, FORWARD, BACKWARD);
}

void MotorCommands::turnRight() {
    SetAllMotorDirection(FORWARD, BACKWARD, BACKWARD, FORWARD);
}

void MotorCommands::moveRight(){
    // move lateral right
    SetAllMotorDirection(FORWARD, FORWARD, BACKWARD, BACKWARD);
}

void MotorCommands::moveLeft(){
    SetAllMotorDirection(BACKWARD, BACKWARD, FORWARD, FORWARD);
}
void MotorCommands::moveForwardRightDiag(){
    //left_front wheel forward
    //left_back_wheel OFF
    //right_Front wheel OFF
    //right_back wheel "forward" -> back wheel "forwards" is backwards
    setStartingSpeed();
    // m_left_back.setSpeed(0);
    // m_right_front.setSpeed(0);
    stopTwoMotor(m_left_back, m_right_front);
    setTwoMotorDirection(m_left_front, FORWARD, m_right_back, BACKWARD);
    setTwoMotorSpeed(m_left_front, m_right_back);
}
void MotorCommands::moveForwardLeftDiag(){
    //left_front wheel OFF
    //right_front wheel Forward
    //left_back wheel "forward" -> back wheel "forwards" is backwards
    //right_Back  wheel OFF 
    setStartingSpeed();
    // m_left_front.setSpeed(0);
    // m_right_back.setSpeed(0);
    stopTwoMotor(m_left_front, m_right_back);
    setTwoMotorDirection(m_left_back, FORWARD, m_right_front, BACKWARD);
    setTwoMotorSpeed(m_left_back, m_right_front);

}

void MotorCommands::moveBackwardRightDiag(){
    //opposite of forward left
    setStartingSpeed();
    // m_left_front.setSpeed(0);
    // m_right_back.setSpeed(0);
    stopTwoMotor(m_left_back, m_right_back);
    setTwoMotorDirection(m_left_front, BACKWARD, m_right_back, FORWARD);
    setTwoMotorSpeed(m_left_front, m_right_back);
    
}

void MotorCommands::moveBackwardLeftDiag(){
    //opposite of forward right
    setStartingSpeed();
    // m_left_back.setSpeed(0);
    // m_right_front.setSpeed(0);
    stopTwoMotor(m_left_back, m_right_back);
    setTwoMotorDirection(m_left_back, FORWARD, m_right_front, BACKWARD);
    setTwoMotorSpeed(m_left_back, m_right_front);
}

void MotorCommands::setupArduino(){

    m_right_front.pinModeSetup();
    m_right_back.pinModeSetup();
    m_left_front.pinModeSetup();
    m_left_back.pinModeSetup();

    Serial.begin(ARDUINO_SERIAL_BAUD_RATE);
}

void MotorCommands::loopMotorControl() {

    if (Serial.available() > 0) {
        char input = Serial.read();
        switch (input) {
            case static_cast<char>(RobotMovement::STOP):
                stopMotors();
                break;
            case static_cast<char>(RobotMovement::MOVE_FORWARD):
                moveForward();
                break;
            case static_cast<char>(RobotMovement::MOVE_BACKWARD):
                moveBackward();
                break;
            case static_cast<char>(RobotMovement::ROTATE_LEFT):
                turnLeft();
                break;
            case static_cast<char>(RobotMovement::ROTATE_RIGHT):
                turnRight();
                break;
            case static_cast<char>(RobotMovement::MOVE_LEFT):
                moveLeft();
                break;
            case static_cast<char>(RobotMovement::MOVE_RIGHT):
                moveRight();
                break;
            case static_cast<char>(RobotMovement::DIAG_BACKWARD_LEFT):
                moveBackwardLeftDiag();
                break;
            case static_cast<char>(RobotMovement::DIAG_BACKWARD_RIGHT):
                moveBackwardRightDiag();
                break;
            case static_cast<char>(RobotMovement::DIAG_FORWARD_LEFT):
                moveForwardLeftDiag();
                break;
            case static_cast<char>(RobotMovement::DIAG_FORWARD_RIGHT):
                moveForwardRightDiag();
                break;
            case static_cast<char>(RobotMovement::SLOWER):
                decreaseSpeed();
                break;
            case static_cast<char>(RobotMovement::FASTER):
                increaseSpeed();
                break;
            default: 
                //fall through for now, but may auto decrease speed so you must hold down button
                break;
        }
    }
    // do not want to overload CPU and ensure all motor code finishes beofre next character check
    //delay(50);
}


