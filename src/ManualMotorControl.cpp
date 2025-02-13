#include "ManualMotorControl.hpp"
ManualControl::ManualControl()
                :   m_wheel_speed(0)
                {};

ManualControl::~ManualControl(){};

void ManualControl::moveForward() {
    setMotorSpeed(m_wheel_speed);
    setMotorDirection(FORWARD, BACKWARD, FORWARD, BACKWARD);
}

void ManualControl::moveBackward() {
    setMotorSpeed(m_wheel_speed);
    setMotorDirection(BACKWARD, FORWARD, BACKWARD, FORWARD);
}

void ManualControl::turnLeft() {
    setMotorSpeed(m_wheel_speed);
    setMotorDirection(BACKWARD, FORWARD, FORWARD, BACKWARD);
}

void ManualControl::turnRight() {
    setMotorSpeed(m_wheel_speed);
    setMotorDirection(FORWARD, BACKWARD, BACKWARD, FORWARD);
}

void ManualControl::moveRight(){
    // move lateral right
    setMotorSpeed(m_wheel_speed);
    setMotorDirection( FORWARD, FORWARD,  BACKWARD, BACKWARD);
}

void ManualControl::moveLeft(){
    setMotorSpeed(m_wheel_speed);
    setMotorDirection(BACKWARD, BACKWARD, FORWARD, FORWARD);
}
void ManualControl::moveForwardRightDiag(){
    //left_front wheel forward
    //left_back_wheel OFF
    //right_Front wheel OFF
    //right_back wheel "forward" -> back wheel "forwards" is backwards
    setStartingSpeed();
    // m_left_back.setSpeed(0);
    // m_right_front.setSpeed(0);
    //stopMotors(m_left_back, m_right_front);
    stopMotors(*m_motors[LB], *m_motors[RF]);
    //setMotorDirection(m_left_front, FORWARD, m_right_back, BACKWARD);
    setMotorDirection(*m_motors[LF], FORWARD, *m_motors[RB], BACKWARD);
    setMotorSpeed(*m_motors[LF], m_wheel_speed, *m_motors[RB], m_wheel_speed);
}
void ManualControl::moveForwardLeftDiag(){
    //left_front wheel OFF
    //right_front wheel Forward
    //left_back wheel "forward" -> back wheel "forwards" is backwards
    //right_Back  wheel OFF 
    setStartingSpeed();
    // m_left_front.setSpeed(0);
    // m_right_back.setSpeed(0);
    //stopMotors(m_left_front, m_right_back);
    stopMotors(*m_motors[LF], *m_motors[RB]);
    //setMotorDirection(m_left_back, FORWARD, m_right_front, BACKWARD);
    setMotorDirection(*m_motors[LB], FORWARD, *m_motors[RF], BACKWARD);
    setMotorSpeed(*m_motors[LB], m_wheel_speed, *m_motors[RF], m_wheel_speed);

}

void ManualControl::moveBackwardRightDiag(){
    //opposite of forward left
    setStartingSpeed();
    // m_left_front.setSpeed(0);
    // m_right_back.setSpeed(0);
    //stopMotors(m_left_back, m_right_back);
    stopMotors(*m_motors[LB], *m_motors[RB]);
    //setMotorDirection(m_left_front, BACKWARD, m_right_back, FORWARD);
    setMotorDirection(*m_motors[LF], FORWARD, *m_motors[RB], BACKWARD);
    setMotorSpeed(*m_motors[LF], m_wheel_speed, *m_motors[RB], m_wheel_speed);
}

void ManualControl::moveBackwardLeftDiag(){
    //opposite of forward right
    setStartingSpeed();
    // m_left_back.setSpeed(0);
    // m_right_front.setSpeed(0);
    // stopMotors(m_left_back, m_right_back);
    stopMotors(*m_motors[LB], *m_motors[RB]);
    // setMotorDirection(m_left_back, FORWARD, m_right_front, BACKWARD);
    setMotorDirection(*m_motors[LB], FORWARD, *m_motors[RF], BACKWARD);
    setMotorSpeed(*m_motors[LB], m_wheel_speed, *m_motors[RF], m_wheel_speed);
}

void ManualControl::increaseSpeed() {
    changeSpeed(true);
}
 
void ManualControl::decreaseSpeed() {
    changeSpeed(false);
}
 
void ManualControl::changeSpeed(bool increase) {
    m_wheel_speed += (increase) ?  SPEED_INCREASE_STEP : -SPEED_INCREASE_STEP;   
    m_wheel_speed = constrain(m_wheel_speed, SPEED_LIMIT_MIN, SPEED_LIMIT_MAX);
    setMotorSpeed(m_wheel_speed, m_wheel_speed, m_wheel_speed, m_wheel_speed);
}


void ManualControl::loopMotorControl() {

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


