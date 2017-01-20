#include "compass.h"

Compass::Compass(){
	previousDegree = 0;
	heading = 0.0;
}

void Compass::init(){
  // Initialize HMC5883L
  while (!compass.begin()){
    delay(500);
  }

  compass.setRange(HMC5883L_RANGE_1_3GA);
  compass.setMeasurementMode(HMC5883L_CONTINOUS);
  compass.setDataRate(HMC5883L_DATARATE_30HZ);
  compass.setSamples(HMC5883L_SAMPLES_8);

  // Set calibration offset. See HMC5883L_calibration.ino
  compass.setOffset(-8, -128);
}

float Compass::correctHeading(float heading){
    heading += declinationAngle;
      // Correct for heading < 0deg and heading > 360deg
    if (heading < 0){
      heading += 2 * PI;
    }

    if (heading > 2 * PI){
      heading -= 2 * PI;
    }

    // Convert to degrees
    float headingDegrees = heading * 57.29578;// 180/M_PI;

    // Fix HMC5883L issue with angles
    float fixedHeadingDegrees;

    if (headingDegrees >= 1 && headingDegrees < 240){
        fixedHeadingDegrees = map(headingDegrees, 0, 239, 0, 179);
    } else if (headingDegrees >= 240){
        fixedHeadingDegrees = map(headingDegrees, 240, 360, 180, 360);
    }

    // Smooth angles rotation for +/- 3deg
    int smoothHeadingDegrees = round(fixedHeadingDegrees);

    if (smoothHeadingDegrees < (previousDegree + 3) && smoothHeadingDegrees > (previousDegree - 3))
    {
      smoothHeadingDegrees = previousDegree;
    }

    previousDegree = smoothHeadingDegrees;

    return smoothHeadingDegrees;
}

Vector Compass::getNormalized(){
	m_field = compass.readNormalize();
	return m_field;
}

float Compass::getHeading(){
	// Calculate heading
	heading = atan2(m_field.YAxis, m_field.XAxis);
	return correctHeading(heading);
}
