#ifndef COMPASS_H
#define COMPASS_H

// sensor libraries
#include "../lib/HMC5883L/HMC5883L.h"

class Compass{
private:
	HMC5883L compass;
	// Set declination angle on your location and fix heading
	// You can find your declination on: http://magnetic-declination.com/
	// (+) Positive or (-) for negative
	// For Moscow / Russia declination angle is 11'00E (positive)
	// Formula: (deg + (min / 60.0)) / (180 / M_PI);
	float declinationAngle = (11.0 + (0.0 / 60.0))*0.0017684; // / (180 / M_PI);
	int previousDegree;
	Vector m_field;
	float heading;
public:
	Compass();
	void init();
	float correctHeading(float heading);
	Vector getNormalized();
	float getHeading();
};


#endif
