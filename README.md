# ESP32 Object Follower Robot using OpenCV

## Description
This project showcases a robot equipped with the ESP32 AI Thinker module, which is capable of capturing live video. The video is then analyzed using OpenCV to identify and track a yellow ball. The ESP32 receives detection data through a WebSocket connection and utilizes it to direct the robot's motions in order to track the ball. This combines computer vision, real-time processing, and robotics to be used in IoT applications.

## Table of Contents
* [Prerequisites]
* [Installation]
* [License]
* [Contributors]

## Prerequisites
* ESP32 AI Thinker module
* ESP WROOM 32 Module
* L298N Motor Driver
* BO Motors
* Wheels (2 Wheels + 1 Caster Wheel)
* Conntecting Wires
* Python 3.x
* OpenCV
* ESP32 development environment


## Installation
### **1. Setting up Environment:**
* Setting up Python:
- Install Python from the [official website](https://www.python.org/).
- Ensure Python is added to your system PATH during installation.

* Verify Installation:
- ```python --version```

* Install pip:
- pip usually comes with python but it can be upgradedd by:
- ```python -m pip install --upgrade pip```

* Install OpenCV:
- ```pip install opencv-python```

### 2. Setting up IDE
* [Arduino IDE](https://www.arduino.cc/en/software) or any other similar IDE can be used for this project.

## License
This project is open-source and distributed under the MIT License, which allows you to use, modify, and distribute the code while giving appropriate credit to the original work.

## Contributors
1. [Shishir Ravi Jois](https://github.com/ShishirRJ)
2. [Srikanth Ravi Jois](https://github.com/SrikanthRaviJois)