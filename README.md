> Project: "Baro-meter"

> Owner: "Luca Navilli"

> Date: "2019:07"

---

# LidarLite_rosserial

## Description of the project
Script Arduino that read six lidarLite V3 and send via USB the distances of all the sensors through the \LaserScan ROS topic.

## Installation procedure
You have to install rosserial_arduino, follow this procedure:
[HERE](http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup)

You need also to install Arduino IDE and the LIDARV3 library if you want to modify the script.

## User Guide
You will find 2 folders:
1) "GetDistanceI2C_changeAddr.ino" is the Arduino script that you have to upload on your arduino micro
2) LIDARLite_Arduino_library-master is the arduino library of the LidarLite v3 that you have to install in order to modify the arduino script

If you want to modify the script download Arduino IDE or similar.

If you want just use the sensors, upload the script into your Arduino Micro and by terminale type:

'sudo chmod 777 /dev/<YOURDEV>'
'rosrun rosserial_python serial_node.py /dev/<YOURDEV> -baud:=115200'



More detailed information about markdown style for README.md file [HERE](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)
