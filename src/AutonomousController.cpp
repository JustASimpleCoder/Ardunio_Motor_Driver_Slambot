#include "AutonomousController.hpp"


AutonomousController::AutonomousController()
{
}

AutonomousController::~AutonomousController()
{
}

// struct VelCmdValues
// {
//     uint8_t pwm_values[4] = {0,0,0,0};
//     Direction dir_values[4] = {FORWARD,FORWARD,FORWARD,FORWARD};
// };
 
// parseMessage is following a communication protocol:
// "speed,dir,speed,dir,speed,dir,speed,dir\r\n"
VelCmdValues AutonomousController::parseMessage(const char* buffer) {
    VelCmdValues vel_cmd;
    uint8_t current_wheel = 0;
    bool is_pwm = true;  // Start with parsing PWM values
    uint8_t value = 0;   // Temporary variable to store parsed values

    for (int i = 0; i < BUFFER_SIZE; i++) {
        char current_char = buffer[i];

        // End of message
        if (current_char == '\r' || current_char == '\n') {
            break;
        }

        // Handle comma separator
        if (current_char == ',') {
            if (is_pwm) {
                vel_cmd.pwm_values[current_wheel] = value;
            } else {
                vel_cmd.dir_values[current_wheel] = static_cast<Direction>(value);
                current_wheel++;  // Move to the next wheel
            }
            value = 0;  // Reset the temporary value
            is_pwm = !is_pwm;  // Toggle between PWM and direction
            continue;
        }

        if (current_char >= '0' && current_char <= '9') {
            value = (is_pwm) ? (value * 10 + (current_char - '0')) : (current_char - '0');
        }
    }

    return vel_cmd;
}

// Function to update motor speed and direction
void AutonomousController::updateSpeedAndDirection(const VelCmdValues & vel_cmd) {
    for (int i = 0; i < 4; i++) {
        setMotorSpeed(*m_motors[i], vel_cmd.pwm_values[i]);
        setMotorDirection(*m_motors[i], vel_cmd.dir_values[i]);
    }
}

// Main loop for motor control
void AutonomousController::updateMotorControl() {
    char buffer[BUFFER_SIZE] = {0};
    if (Serial.available() > 0) {
        size_t num_read = Serial.readBytesUntil('\n', buffer, BUFFER_SIZE - 1);
        buffer[num_read] = '\0';
        
        VelCmdValues vel_cmd = parseMessage(buffer);
        updateSpeedAndDirection(vel_cmd);
    }
}
