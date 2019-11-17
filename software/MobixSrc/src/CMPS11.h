#include <Arduino.h>

void calibrateIMU(){
  // Function to calibrate the CMPS11 (IMU sensor)

  bool calibrating = 1;
  delay(100);
  Serial.println("Starting Calibration...");
  // Send bytes to start the calibration
  Serial2.write(0xF0);
  delay(50);
  Serial2.write(0xF5);
  delay(50);
  Serial2.write(0xF6);
  delay(50);

  Serial.println("Type 's' to stop the calibration");
  while(calibrating){
    while (Serial.available()) {
      int byte = Serial.read();
      if(byte=='s'){
        Serial.println("Stopping...");
        // Send byte to stop the calibration
        Serial2.write(0xF8);
        calibrating=0;
      }
    }
  }
}

void sendIMUdata(){
  // Function to send all data from the IMU sensor to the ROS topic

  // Get Raw magnetic data
  Serial2.write(0x19);
  while (Serial2.available()) {
    int byteXh = Serial2.read();
    int byteXl = Serial2.read();
    int byteYh = Serial2.read();
    int byteYl = Serial2.read();
    int byteZh = Serial2.read();
    int byteZl = Serial2.read();
    int dataX = (byteXh<<8)+byteXl;
    int dataY = (byteYh<<8)+byteYl;
    int dataZ = (byteZh<<8)+byteZl;
    Serial.printf("Magnetic data: X-%d Y-%d Z-%d\n",dataX,dataY,dataZ);
  }
  delay(100);
  // Get Raw accelerometer data
  Serial2.write(0x20);
  while (Serial2.available()) {
    int byteXh = Serial2.read();
    int byteXl = Serial2.read();
    int byteYh = Serial2.read();
    int byteYl = Serial2.read();
    int byteZh = Serial2.read();
    int byteZl = Serial2.read();
    int dataX = (byteXh<<8)+byteXl;
    int dataY = (byteYh<<8)+byteYl;
    int dataZ = (byteZh<<8)+byteZl;
    Serial.printf("Accel. data: X-%d Y-%d Z-%d\n",dataX,dataY,dataZ);
  }
  delay(100);
  // Get Raw gyro data
  Serial2.write(0x21);
  while (Serial2.available()) {
    int byteXh = Serial2.read();
    int byteXl = Serial2.read();
    int byteYh = Serial2.read();
    int byteYl = Serial2.read();
    int byteZh = Serial2.read();
    int byteZl = Serial2.read();
    int dataX = (byteXh<<8)+byteXl;
    int dataY = (byteYh<<8)+byteYl;
    int dataZ = (byteZh<<8)+byteZl;
    Serial.printf("Gyro data: X-%d Y-%d Z-%d\n",dataX,dataY,dataZ);
  }
}
