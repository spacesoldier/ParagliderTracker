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


	bool cardInit;

	String callDirName();
	String callFileName();
	bool logging;
public:
	Logger();
	void initSDCard();
	void logData(String in);
	void startLog(String dirname, String filename);
	void stopLog();
	void logStartStop();
	bool isLogging(){
		return logging;
	}
};



#endif
