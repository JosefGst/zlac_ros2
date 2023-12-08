# ZLAC8015 ROS 2 motor hardware interface

![foxy badge](https://github.com/JosefGst/zlac_ros2/actions/workflows/foxy.yaml/badge.svg)
![humble badge](https://github.com/JosefGst/zlac_ros2/actions/workflows/humble.yaml/badge.svg)
![iron badge](https://github.com/JosefGst/zlac_ros2/actions/workflows/iron.yaml/badge.svg)
![rolling badge](https://github.com/JosefGst/zlac_ros2/actions/workflows/rolling.yaml/badge.svg)

ROS 2 hardware interface library package to use with ROS 2 control.

## Installation

    cd zlac_ros2
    sudo apt install python3-vcstool
    vcs import .. < my.repos

## Wiring

terminal resistor switch is **on** for "right motor"
![wiring diagram](https://github.com/JosefGst/zlac_ros2/blob/master/assets/zlac%20wiring.png)

## Run example

basic example for testing

    ros2 run zlac_ros2 zlac8015_example
