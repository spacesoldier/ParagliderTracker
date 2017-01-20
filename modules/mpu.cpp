#include "mpu.h"

void MPU::init(){
  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_8G)){
//    logData("MPU6050 not found. Wiring?");
    delay(500);
  }

  // Calibrate gyroscope. The calibration must be at rest.
  mpu.calibrateGyro();
  // Set threshold sensivty. Default 3.
  mpu.setThreshold(3);
}


float MPU::calcAccelValue(){
  return sqrt(pow(accel.XAxis,2)+pow(accel.YAxis,2)+pow(accel.ZAxis,2));
}

Vector MPU::readAccel(){
	accel = mpu.readNormalizeAccel();
	return accel;
}

Vector MPU::readGyro(){
	rotate = mpu.readNormalizeGyro();
	return rotate;
}
