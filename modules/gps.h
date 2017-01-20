#ifndef GPS_H
#define GPS_H

// platform library
#include <SoftwareSerial.h>

// module library
#include "../lib/TinyGPSPlus/TinyGPS++.h"

class GPS{
private:
	// Choose two Arduino pins to use for software serial
	// The GPS Shield uses D6 and D7 by default
	const int RXPin = 52;
	const int TXPin = 50;

	// The Skytaq uBlox Neo 6 GPS module included in the GPS Shield Kit
	// uses 9600 baud by default
	const int GPSBaud = 9600;

	// Create a TinyGPS++ object called "gps"
	TinyGPSPlus gps;

	String lastGPSData;

	// Create a software serial port called "gpsSerial"
//	SoftwareSerial* gpsSerial;
	// default string output values
	const String noPosMsg	= "no_lat no_lng";
	const String noAltMsg = "no_alt no_v_spd";
	const String noSpdMsg = "no_spd";
	String gpsResult;

	double lat;
	double lon;
	double alt;
	double spd;

	bool encoded;
public:
	GPS();
	void init();

	void getGPSData();

	void parseGPSInfo();

	double calcGPSVertSpd(double alt);

	String& getLastGpsData() {
		return lastGPSData;
	}
};




#endif
