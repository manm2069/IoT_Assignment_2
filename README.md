# IoT_Assignment_2

Assignment by:
Francis Andrei Alivio
Juan Miguel Salvador

Explanation of each file:
config.json - a json file that contains all of the setpoints, and what to do with said setpoints in the IoT system.
sensor.ino - an ino file that recieves the values from the sensors of the IoT system and sends it to the control.py file.
control.py - a python file that recieves the values from the sensor.ino and compares those messages to the setpoints in the config.json and sends over the command corresponding to said setpoint to the actor.py.
actor.py - a python file that recieves the command from the control.py to make changes to the system.

Video Demonstration:
https://drive.google.com/file/d/1XR5ruCAgv4AOYd8vIc4qv19HPR1jTnu4/view?usp=sharing
