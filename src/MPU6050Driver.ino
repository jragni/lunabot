#include <Wire.h> // Include Wire library for I2C communication
#include <Adafruit_MPU6050.h> // Include MPU6050 library

// Define I2C communication pins
const int MPU_SCL_PIN = A5; // Arduino uno
const int MPU_SDA_PIN = A4; // Arduino uno

// Create an MPU6050 object

Adafruit_MPU6050 mpu;

void setup() {

  Serial.begin(115200); // Start serial communication for data output

  while (!mpu.begin()) { // Check for successful MPU6050 connection
    Serial.println("MPU6050 Connection failed! Waiting...");
    delay(1000); // Wait for 1 second before trying again
  }

  Serial.println("MPU6050 connection successful!");
}

void loop() {

  // Read accelerometer and gyroscope data
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);
  // Print sensor data to serial monitor
  // Serial.print(accel.acceleration.x, accel.acceleration.y, accel.acceleration.z, gyro.gyro.x, gyro.gyro.y, gyro.gyro.z);
  float accX = accel.acceleration.x;
  float accY = accel.acceleration.y;
  float accZ = accel.acceleration.z;

  float gyroX = gyro.gyro.roll;
  float gyroY = gyro.gyro.pitch;
  float gyroZ = gyro.gyro.heading;

  Serial.print(accX);
  Serial.print(' ');
  Serial.print(accY);
  Serial.print(' ');
  Serial.print(accZ);
  Serial.print(' ');
  Serial.print(gyroX);
  Serial.print(' ');
  Serial.print(gyroY);
  Serial.print(' ');
  Serial.print(gyroZ);
  Serial.println();

}