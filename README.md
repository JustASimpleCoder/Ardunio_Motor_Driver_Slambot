# Arduino Uno Code for 4-Wheel Mecanum Drive

This repository contains Arduino Uno code to be used with Platformio for controlling a 4-wheel differential mecanum drive. The motors used are inexpensive "TT motors," each with two wires: one for voltage input and one for output. An L298N motor driver is used to control the left-side and right-side motors.

# Features

* Omnidirectional Movement: The mecanum wheel design allows for precise movement in all directions by controlling the speed and direction of individual motors.

* Customizable Pin Configuration: Pin connections are stored in the Motor class and initialized using the MotorCommand class. You can set up your pins however you prefer, but ensure that the speed pin is connected to one of the PWM pins on the Arduino.

# Pin Configuration 

Ensure that:

* The left-side motors are connected to one channel of the L298N motor driver.
* The right-side motors are connected to the other channel of the L298N motor driver.
* Speed pins are attached to PWM pins on the Arduino for proper speed control.

The four wheel mecanum wheel can provide omnidirectional movement, by control each motors direction and speed.

# Command Interface

The robot accepts serial commands to control movement, which are mapped using the following enum class:

enum class RobotMovement: char{
    STOP = 'x',  <br />
    MOVE_FORWARD = 'w',  <br />
    MOVE_BACKWARD = 's', <br />
    MOVE_LEFT = 'l', <br />
    MOVE_RIGHT = 'r', <br />
    ROTATE_LEFT = 'a', <br />
    ROTATE_RIGHT = 'd', <br />
    DIAG_FORWARD_RIGHT = 'e', <br />
    DIAG_BACKWARD_RIGHT = 'c', <br />
    DIAG_FORWARD_LEFT = 'q', <br />
    DIAG_BACKWARD_LEFT = 'z', <br />
    FASTER = '+', <br />
    SLOWER = '-', <br />
    INVALID = '?' <br />
}; <br />

* STOP: Halts all motor activity.
* MOVE_FORWARD / MOVE_BACKWARD: Moves the robot forward or backward.
* ROTATE_LEFT / ROTATE_RIGHT: Rotates the robot in place to the left (CCW when looking down) or right (CW when look down).
* MOVE_LEFT / MOVE_RIGHT: Performs lateral strafing motions to the left or right.
* DIAG_FORWARD_RIGHT/ DIAG_BACKWARD_RIGHT / DIAG_FORWARD_LEFT DIAG_BACKWARD_LEFT: moves diagnoanlly in left/right along with front/back
* FASTER / SLOWER: Adjusts the robot's speed incrementally.
* INVALID: Handles unrecognized commands.

Additional commands will be added in future updates.

# How it works

1. Motor Initialization:
*  Motors are initialized via the Motor class, which handles pin configurations and operations.
* Motor classes are instatitated by the MotorCommands class, to change pin configurations you need to update the constructor in MotorCommand class to properly call the Motor class with the correct pin configs.
2. Command Processing:
* Serial commands are read and translated into movements using the RobotMovement enum.
* Serial communication invokes the Arduino Serial library and is set to a baud rate of 9600 by default.

3. Omnidirectional Control:
* By adjusting motor speed and direction, the robot achieves full omnidirectional movement.
* MotorCommand class contains functions that move the robot by controlling each motor, using the Mecanum Wheel for omnidirectional control (see Visual Representation section below for help).


# Visual Representation

![alt text](README_Images/MecanumWheelDiagram.png)

source: https://www.researchgate.net/figure/Movements-of-a-Mecanum-wheel-driven-robot-to-any-directions-side-arrows-indicate-wheel_fig1_367879750

# Future updates
Planned improvements:

* Adding more movement commands. (have forward/back, lateral, diagonally and rotation around center, can add more rotations and other wheel movements)
* Enhancing motor control algorithms for smoother performance.
* Support for additional motor driver configurations.


Feel free to explore, modify, and contribute to this project! If you encounter any issues or have suggestions for improvement, open an issue or submit a pull request.

# useful links
https://www.matec-conferences.org/articles/matecconf/pdf/2021/12/matecconf_mse21_08003.pdf

https://control.ros.org/rolling/doc/ros2_controllers/doc/mobile_robot_kinematics.html#mobile-robot-kinematics

https://robofoundry.medium.com/ros2-control-differential-drive-robot-project-part-1-mechanical-build-2a323da04992