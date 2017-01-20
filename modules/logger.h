#ifndef LOGGER_H
#define LOGGER_H

// platform libraries
#include <SPI.h>
#include <SD.h>

class Logger{
private:
	// chip select pin on GPS shield is 10.
	// chip select pin on data logger shield is 8

	const int CS_gps = 10;
	const int CS_data = 8;

	File myFile;
	String logName;
	void initSDCard(String fname);
public:
	Logger();
	void logData(String in);
	void startLog(String name);
};



#endif
