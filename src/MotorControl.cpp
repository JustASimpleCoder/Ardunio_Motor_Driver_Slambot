#include "MotorControl.hpp"
void Motor::setSpeed(int speed) {
    analogWrite(m_pwm_pin, speed);
}

void Motor::setDirection(bool forward) {
    digitalWrite(m_dir1_pin, forward ? HIGH : LOW);
    digitalWrite(m_dir2_pin, forward ? LOW : HIGH);
}

void Motor::pinModeSetup(){
    pinMode(this->m_pwm_pin, OUTPUT);
    pinMode(this->m_dir1_pin, OUTPUT);
    pinMode(this->m_dir2_pin, OUTPUT);
}

void MotorCommands::increaseSpeed() {
   changeSpeed(true);
}
void MotorCommands::decreaseSpeed() {
   changeSpeed(false);
}

void MotorCommands::changeSpeed(bool increase) {
    m_wheel_speed += (increase) ?  SPEED_INCREASE_STEP : -SPEED_INCREASE_STEP;
    m_wheel_speed = (m_wheel_speed > static_cast<int>(SpeedLimit::MAX)) ? static_cast<int>(SpeedLimit::MAX) : m_wheel_speed;
    m_wheel_speed = (m_wheel_speed < static_cast<int>(SpeedLimit::MIN)) ? static_cast<int>(SpeedLimit::MIN) : m_wheel_speed;
    
    m_left_back.setSpeed(m_wheel_speed);
    m_left_front.setSpeed(m_wheel_speed);
    m_right_back.setSpeed(m_wheel_speed);
    m_right_front.setSpeed(m_wheel_speed);
}

void MotorCommands::setStartingSpeed() {
    if (m_wheel_speed == 0){
        m_wheel_speed = static_cast<int>(SpeedLimit::MIN);
    }
}

void MotorCommands::setSingleMotorDirection(Motor * motor, Direction direction){
    motor->setDirection(direction);
}

void MotorCommands::setTwoMotorDirection(   Motor * motor1, Direction direction1,
                                            Motor * motor2, Direction direction2){
                                                
    motor1->setDirection(direction1);
    motor2->setDirection(direction2);
}

void MotorCommands::setTwoMotorSpeed(Motor * motor1, Motor * motor2){
                                                
    motor1->setSpeed(m_wheel_speed);
    motor2->setSpeed(m_wheel_speed);
}


void MotorCommands::SetAllMotorDirection(
                    Direction left_front_wheel_forward, 
                    Direction left_back_wheel_forward,
                    Direction right_front_wheel_forward, 
                    Direction right_back_wheel_forward){

    m_right_front.setDirection(right_front_wheel_forward);
    m_right_back.setDirection(right_back_wheel_forward);

    m_left_front.setDirection(left_front_wheel_forward);
    m_left_back.setDirection(left_back_wheel_forward);
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

    setStartingSpeed();
    SetAllMotorDirection(FORWARD, BACKWARD, FORWARD, BACKWARD);
    setMotorSpeed();
}

void MotorCommands::moveBackward() {
    setStartingSpeed();
    SetAllMotorDirection(BACKWARD, FORWARD, BACKWARD, FORWARD);
    setMotorSpeed();
}

void MotorCommands::turnLeft() {
    setStartingSpeed();
    SetAllMotorDirection(BACKWARD, FORWARD, FORWARD, BACKWARD);
    setMotorSpeed();
}

void MotorCommands::turnRight() {
    setStartingSpeed();
    SetAllMotorDirection(FORWARD, BACKWARD, BACKWARD, FORWARD);
    setMotorSpeed();
}

void MotorCommands::moveRight(){
    // move lateral right
    setStartingSpeed();
    SetAllMotorDirection(FORWARD, FORWARD, BACKWARD, BACKWARD);
    setMotorSpeed();
}

void MotorCommands::moveLeft(){
    setStartingSpeed();
    SetAllMotorDirection(BACKWARD, BACKWARD, FORWARD, FORWARD);
    setMotorSpeed();

    // executeAllWheelMove(RobotMovement::MOVE_LEFT);
}

// is thiw really better than above
// in each switch case in the arduino loop, it will have to go through this loop again
// its a
// void MotorCommands::executeAllWheelMove(RobotMovement move){
//     Direction l_Front;
//     Direction l_back;
//     Direction r_Front;
//     Direction r_back;
//     switch(move){
//         case RobotMovement::MOVE_FORWARD:
//             l_Front = FORWARD;
//             l_back = FORWARD;
//             r_Front = FORWARD;
//             r_back = FORWARD;
//             break;
//         case RobotMovement::MOVE_BACKWARD:
//             break;
//     }

//     setStartingSpeed();
//     SetAllMotorDirection(l_Front, l_back, r_Front, r_back);
//     setMotorSpeed();
// }

void MotorCommands::moveForwardRightDiag(){
    //left_front wheel forward
    //left_back_wheel OFF
    //right_Front wheel OFF
    //right_back wheel "forward" -> back wheel "forards" is backwards
    setStartingSpeed();
    m_left_back.setSpeed(0);
    m_right_front.setSpeed(0);
    setTwoMotorDirection(&m_left_front, FORWARD, &m_right_back, BACKWARD);
    setTwoMotorSpeed(&m_left_front, &m_right_back);
}
void MotorCommands::moveForwardLeftDiag(){
    //left_front OFF
    //right_front OFF
    //left_back OFF
    //right_Back  OFF
    setStartingSpeed();
    m_left_front.setSpeed(0);
    m_right_back.setSpeed(0);
    setTwoMotorDirection(&m_left_back, FORWARD, &m_right_front, BACKWARD);
    setTwoMotorSpeed(&m_left_back, &m_right_front);

}

void MotorCommands::moveBackwardRightDiag(){
    //opposite of forward left
    setStartingSpeed();
    m_left_front.setSpeed(0);
    m_right_back.setSpeed(0);

    setTwoMotorDirection(&m_left_front, BACKWARD, &m_right_back, FORWARD);
    setTwoMotorSpeed(&m_left_front, &m_right_back);
    
}

void MotorCommands::moveBackwardLeftDiag(){
    //opposite of forward right
    setStartingSpeed();
    m_left_back.setSpeed(0);
    m_right_front.setSpeed(0);

    setTwoMotorDirection(&m_left_back, FORWARD, &m_right_front, BACKWARD);
    setTwoMotorSpeed(&m_left_back, &m_right_front);
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
        Serial.println("You inputed input: " + input);
        //RobotMovement move = RobotMovement::INVALID;
        switch (input) {
            case static_cast<char>(RobotMovement::STOP):
                this->stopMotors();
                break;
            case static_cast<char>(RobotMovement::MOVE_FORWARD):
                this->moveForward();
                break;
            case static_cast<char>(RobotMovement::MOVE_BACKWARD):
                this->moveBackward();
                break;
            case static_cast<char>(RobotMovement::ROTATE_LEFT):
                this->turnLeft();
                break;
            case static_cast<char>(RobotMovement::ROTATE_RIGHT):
                this->turnRight();
                break;
            case static_cast<char>(RobotMovement::MOVE_LEFT):
                this->moveLeft();
                break;
            case static_cast<char>(RobotMovement::MOVE_RIGHT):
                this->moveRight();
                break;
            case static_cast<char>(RobotMovement::DIAG_BACKWARD_LEFT):
                this->moveBackwardLeftDiag();
                break;
            case static_cast<char>(RobotMovement::DIAG_BACKWARD_RIGHT):
                this->moveBackwardRightDiag();
                break;
            case static_cast<char>(RobotMovement::DIAG_FORWARD_LEFT):
                this->moveForwardLeftDiag();
                break;
            case static_cast<char>(RobotMovement::DIAG_FORWARD_RIGHT):
                this->moveForwardRightDiag();
                break;
            case static_cast<char>(RobotMovement::SLOWER):
                this->decreaseSpeed();
                break;
            case static_cast<char>(RobotMovement::FASTER):
                this->increaseSpeed();
                break;
            default: 
                //fall through for now, but may auto decrease speed so you must hold down button
                break;
        }
    }
    // do not want to overload CPU
    delay(500);


    // left_front.setDirection(FORWARD); // Forward
    // left_front.setSpeed(128);      // Half speed
    // delay(2000);

    // left_front.setDirection(BACKWARD); // Backward
    // left_front.setSpeed(128);
    // delay(2000);

    // left_front.setSpeed(0);         // Stop
    // delay(2000);
}


