#ifndef BAROMETER_H
#define BAROMETER_H

// sensor library
#include "../lib/BMP180/src/SFE_BMP180.h"

class Barometer{
private:
	SFE_BMP180 pressure;

	double baseline; // baseline pressure

	float baroAlt;
	// for exponential pressure smoothing
	float alpha;

	float prevSmooth = 0;

public:
	Barometer();

	void init();

	double getPressure();
	double getAltitude();
	float getSmoothedAltitude();

	float calcBaroVertSpd();

	// implements exponential smoothing for the altitude
	float smoothAltitudeExp(float a);

	void readAltitude();
};




#endif
