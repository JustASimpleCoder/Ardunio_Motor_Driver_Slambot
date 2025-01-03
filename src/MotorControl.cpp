#include "MotorControl.hpp"
Motor::Motor(int pwm, int dir1, int dir2)
            : m_pwm_pin(pwm), m_dir1_pin(dir1), m_dir2_pin(dir2) {};

void Motor::setSpeed(int speed) {
    analogWrite(m_pwm_pin, speed);
}

void Motor::setDirection(bool forward) {
    digitalWrite(m_dir1_pin, forward ? HIGH : LOW);
    digitalWrite(m_dir2_pin, forward ? LOW : HIGH);
}

void Motor::pinModeSetup(){
    pinMode(m_pwm_pin, OUTPUT);
    pinMode(m_dir1_pin, OUTPUT);
    pinMode(m_dir2_pin, OUTPUT);
}

MotorCommands::MotorCommands()
                :   m_wheel_speed(0),
                m_right_back(5,2,3), 
                m_right_front(6,4,7),
                m_left_front(9,11,8), 
                m_left_back(10,13,12)
                {};

void MotorCommands::increaseSpeed() {
   changeSpeed(true);
}
void MotorCommands::decreaseSpeed() {
   changeSpeed(false);
}

void MotorCommands::changeSpeed(bool increase) {
    m_wheel_speed += (increase) ?  SPEED_INCREASE_STEP : -SPEED_INCREASE_STEP;
    m_wheel_speed = (m_wheel_speed > SPEED_LIMIT_MAX) ? SPEED_LIMIT_MAX : m_wheel_speed;
    m_wheel_speed = (m_wheel_speed < SPEED_LIMIT_MIN) ? SPEED_LIMIT_MIN : m_wheel_speed;
    
    m_left_back.setSpeed(m_wheel_speed);
    m_left_front.setSpeed(m_wheel_speed);
    m_right_back.setSpeed(m_wheel_speed);
    m_right_front.setSpeed(m_wheel_speed);
}

void MotorCommands::setStartingSpeed() {
    if (m_wheel_speed == 0){
        m_wheel_speed = SPEED_LIMIT_MIN; //static_cast<int>(SpeedLimit::MIN);
    }
}

void MotorCommands::setSingleMotorDirection(Motor& motor, Direction direction){
    motor.setDirection(direction);
}

void MotorCommands::setTwoMotorDirection(   Motor& motor1, Direction direction1,
                                            Motor& motor2, Direction direction2){
                                                
    motor1.setDirection(direction1);
    motor2.setDirection(direction2);
}

void MotorCommands::setTwoMotorSpeed(Motor& motor1, Motor& motor2){
                                                
    motor1.setSpeed(m_wheel_speed);
    motor2.setSpeed(m_wheel_speed);
}


void MotorCommands::SetAllMotorDirection(
                    Direction left_front_wheel_forward, 
                    Direction left_back_wheel_forward,
                    Direction right_front_wheel_forward, 
                    Direction right_back_wheel_forward){
    
    // motor wont start turning until pwm signal is approx ~120 - 150
    setStartingSpeed();
    m_right_front.setDirection(right_front_wheel_forward);
    m_right_back.setDirection(right_back_wheel_forward);

    m_left_front.setDirection(left_front_wheel_forward);
    m_left_back.setDirection(left_back_wheel_forward);
    setMotorSpeed();
}

void MotorCommands::stopMotors() {
    Serial.println("stopping motor");
    m_wheel_speed = 0;
    
    m_right_back.setSpeed(0);
    m_right_front.setSpeed(0);

    m_left_back.setSpeed(0);
    m_left_front.setSpeed(0);
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
    m_left_back.setSpeed(0);
    m_right_front.setSpeed(0);
    setTwoMotorDirection(m_left_front, FORWARD, m_right_back, BACKWARD);
    setTwoMotorSpeed(m_left_front, m_right_back);
}
void MotorCommands::moveForwardLeftDiag(){
    //left_front wheel OFF
    //right_front wheel Forward
    //left_back wheel "forward" -> back wheel "forwards" is backwards
    //right_Back  wheel OFF 
    setStartingSpeed();
    m_left_front.setSpeed(0);
    m_right_back.setSpeed(0);
    setTwoMotorDirection(m_left_back, FORWARD, m_right_front, BACKWARD);
    setTwoMotorSpeed(m_left_back, m_right_front);

}

void MotorCommands::moveBackwardRightDiag(){
    //opposite of forward left
    setStartingSpeed();
    m_left_front.setSpeed(0);
    m_right_back.setSpeed(0);

    setTwoMotorDirection(m_left_front, BACKWARD, m_right_back, FORWARD);
    setTwoMotorSpeed(m_left_front, m_right_back);
    
}

void MotorCommands::moveBackwardLeftDiag(){
    //opposite of forward right
    setStartingSpeed();
    m_left_back.setSpeed(0);
    m_right_front.setSpeed(0);

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

// Potential encapsulation of above move functions
// void MotorCommands::executeMove(RobotMovement direction) {
//     setStartingSpeed();

//     switch (direction) {
//     case RobotMovement::MOVE_FORWARD:
//         SetAllMotorDirection(FORWARD, BACKWARD, FORWARD, BACKWARD);
//         break;
//     case RobotMovement::MOVE_BACKWARD:
//         SetAllMotorDirection(BACKWARD, FORWARD, BACKWARD, FORWARD);
//         break;
//     case RobotMovement::ROTATE_LEFT:
//         SetAllMotorDirection(BACKWARD, FORWARD, FORWARD, BACKWARD);
//         break;
//     case RobotMovement::ROTATE_RIGHT:
//         SetAllMotorDirection(FORWARD, BACKWARD, BACKWARD, FORWARD);
//         break;
//     case RobotMovement::MOVE_LEFT:
//         SetAllMotorDirection(FORWARD, FORWARD, BACKWARD, BACKWARD);
//         break;
//     case RobotMovement::MOVE_RIGHT:
//         SetAllMotorDirection(BACKWARD, BACKWARD, FORWARD, FORWARD);
//         break;
//     case RobotMovement::DIAG_FORWARD_LEFT:
//         setTwoMotorDirection(&m_left_front, FORWARD, &m_right_back, BACKWARD);
//         break;
//     case RobotMovement::DIAG_FORWARD_RIGHT:
//         setTwoMotorDirection(&m_left_back, FORWARD, &m_right_front, BACKWARD);
//         break;
//     case RobotMovement::DIAG_BACKWARD_LEFT:
//         setTwoMotorDirection(&m_left_front, BACKWARD, &m_right_back, FORWARD);
//         break;
//     case RobotMovement::DIAG_BACKWARD_RIGHT:
//         setTwoMotorDirection(&m_left_back, BACKWARD, &m_right_front, FORWARD);
//         break;
//     }

//     setMotorSpeeds();
// }

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
    delay(500);
}


