

#define USE_USBCON
#include <ros.h>
#include <sensor_msgs/LaserScan.h>
#include <Wire.h>
#include <LIDARLite.h>

//Setting ROS
ros::NodeHandle nh;
sensor_msgs::LaserScan lidar_msg;
ros::Publisher lidar_pub("laser_scan", &lidar_msg);

//Settings LidarSensore
LIDARLite myLidarLite;

float DistanceArray[] = {0,0,0,0,0,0};
int sensorPins[] = {6,5,7,8,9,10}; // Array of pins connected to the sensor Power Enable lines
unsigned char addresses[] = {0x68,0x76,0x72,0x84,0x88,0x92};
int numberLidar = 6;

void setup()
{

  
  // Initialize ROS node handle, advertise and subscribe the topics
  nh.initNode();
  delay(1000);
  nh.getHardware()->setBaud(115200);
  delay(1000);
  nh.advertise(lidar_pub);
  delay(1000);
  // Set LaserScan Definition
  lidar_msg.header.frame_id = "lidar";
  lidar_msg.angle_min = 0.0;               // start angle of the scan [rad]
  lidar_msg.angle_max = 3.14*2;            // end angle of the scan [rad]
  lidar_msg.angle_increment = 3.14*2/360;  // angular distance between measurements [rad]
  lidar_msg.range_min = 0.05;               // minimum range value [m]
  lidar_msg.range_max = 500.0;              // maximum range value [m]
  lidar_msg.ranges_length = 6;
  lidar_msg.intensities_length = 6;
  
  //Initialize lidarAddress
  delay(100);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  
  delay(100);

  
  for(int i=0; i<numberLidar; i++){
    myLidarLite.begin(0, false, 0x62);
    delay(100);
    digitalWrite(sensorPins[i], HIGH);
    delay(100);
    myLidarLite.setI2Caddr(addresses[i], 1, 0x62);
    myLidarLite.configure(0,addresses[i]);
    myLidarLite.begin(0, false, addresses[i]);
    delay(100);
    Wire.endTransmission(true);
    } 
}

void loop()
{
  Wire.beginTransmission(0x68);
  DistanceArray[0] = myLidarLite.distance(0, 0x68);
  Wire.endTransmission(true);

  delay(5);
  Wire.beginTransmission(0x76);
  DistanceArray[1] = myLidarLite.distance(0, 0x76);
  Wire.endTransmission(true);

  delay(5);
  Wire.beginTransmission(0x72);
  DistanceArray[2] = myLidarLite.distance(0, 0x72);
  Wire.endTransmission(true);

  delay(5);
  Wire.beginTransmission(0x84);
  DistanceArray[3] = myLidarLite.distance(0, 0x84);
  Wire.endTransmission(true);

  delay(5);
  Wire.beginTransmission(0x88);
  DistanceArray[4] = myLidarLite.distance(0, 0x88);
  Wire.endTransmission(true);

  delay(5);
  Wire.beginTransmission(0x92);
  DistanceArray[5] = myLidarLite.distance(0, 0x92);
  Wire.endTransmission(true);


  lidar_msg.ranges = DistanceArray;
  lidar_msg.header.stamp = nh.now();
  lidar_pub.publish(&lidar_msg);
  delay(100);
  nh.spinOnce();

}
