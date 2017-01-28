#ifndef GPS_H
#define GPS_H

// platform library
#include <SoftwareSerial.h>

// module library
#include "../lib/TinyGPSPlus/TinyGPS++.h"
//#include "../lib/TinyGPS-13/TinyGPS.h"

class GPS{
private:
	// Choose two Arduino pins to use for software serial
	// The GPS Shield uses D6 and D7 by default
//	const int RXPin = 52;
//	const int TXPin = 50;

	// The Skytaq uBlox Neo 6 GPS module included in the GPS Shield Kit
	// uses 9600 baud by default
	int GPSBaud = 9600;

	// Create a TinyGPS++ object called "gps"
	TinyGPSPlus gps;
//	TinyGPS gps;

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

	bool gpsStatus[7] = {false, false, false, false, false, false, false};
	unsigned long start;
	void configureUblox(byte *settingsArrayPointer);
	void calcChecksum(byte *checksumPayload, byte payloadSize);
	void sendUBX(byte *UBXmsg, byte msgLength);
	byte getUBX_ACK(byte *msgID);
	void printHex(uint8_t *data, uint8_t length);
	void setBaud(byte baudSetting);

	String buff; // here we place all characters received from GPS

	bool ready;
public:
	GPS();
	void init();
	void getGPSData();
	void parseGPSInfo();
	double calcGPSVertSpd(double alt);
	bool isReady();
	String getLastGpsData() {
		return lastGPSData;
	}
};




#endif
