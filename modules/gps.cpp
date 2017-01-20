#include "gps.h"

GPS::GPS(){
	gpsResult = "";
	lastGPSData = "no_lat no_lng no_alt no_v_spd no_spd";
//	gpsSerial = new SoftwareSerial(RXPin, TXPin);
	encoded = false;
}

void GPS::getGPSData(){
//  if (gpsSerial->available() > 0){
    // Get information every time a new sentence is correctly encoded.
//    while (gpsSerial->available() > 0){
//      char c = gpsSerial->read();
//      if (gps.encode(c)){
//        parseGPSInfo();
//      }
//    }
//  }
    while (Serial2.available() > 0){
      char c = Serial2.read();
      gps.encode(c);
      if (gps.encode(c)){
        encoded = true;
      }
    }

}


void GPS::parseGPSInfo(){
	if (encoded){
		 lastGPSData = "parsed";
		  // parse location data
		  if (gps.location.isValid()){
			  lat = gps.location.lat();
		      lastGPSData.concat(String(gps.location.lat(), 6));
		      lastGPSData.concat(' ');
		      lon = gps.location.lng();
		      lastGPSData.concat(String(gps.location.lng(), 6));
		  } else {
			  lastGPSData.concat(noPosMsg);
		  }
		  // parse altitude and calculate the vertical speed
		  lastGPSData += ' ';
		  if (gps.altitude.isValid()){
			  alt = gps.altitude.meters();
		      float altitude = gps.altitude.meters();
		      lastGPSData += String(altitude,6);
		      lastGPSData += ' ';
		      lastGPSData += String(calcGPSVertSpd(altitude),6);
		  } else {
			  lastGPSData += noAltMsg;
		  }

		   //get the speed
		    lastGPSData.concat(' ');
		    if (gps.speed.isValid()){
		      spd = gps.speed.kmph();
		      lastGPSData.concat(String(gps.speed.kmph(),6));
		    } else {
		    	lastGPSData.concat(noSpdMsg);
		    }
		    encoded = false;
	}

}


double last_gps_alt = 0;
unsigned long lastVSpdTake;

double GPS::calcGPSVertSpd(double alt){
  unsigned long currTime = micros();
  double result = 1000000*(alt - last_gps_alt)/(currTime - lastVSpdTake);
  lastVSpdTake = currTime;
  last_gps_alt = alt;
  return result;
}

void GPS::init(){
//	gpsSerial->begin(GPSBaud);
	Serial2.begin(GPSBaud);
}
