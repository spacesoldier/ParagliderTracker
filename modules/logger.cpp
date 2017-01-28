#include "logger.h"

Logger::Logger(){
	logName = "";
	cardInit = false;
	logging = false;
}

void Logger::logData(String in){
//  if (Serial){
//    Serial.println(in);
//  }

  if (myFile) {
      myFile.println(in);
      myFile.flush();
  }
}

void Logger::initSDCard(){
	if (!cardInit){
		pinMode(CS_data, OUTPUT);

		// Firstly initializing SD card on Data shield...
		if (!SD.begin(CS_data)) {
		    // initialization of SD on the Data shield failed. Try to init GPS shield
		    pinMode(CS_data, INPUT);
		    pinMode(CS_gps, OUTPUT);
		    if (!SD.begin(CS_gps)){
		      //initialization of SD slots failed.
		    	if (Serial){
		    		Serial.println("No SD card found.");
		    	}
		    }
		}
		cardInit = true;
		  //initialization done.
	}




}

void Logger::startLog(String dirname, String filename){
	if (!cardInit){
		initSDCard();
	}

	bool dirExist = false;
	String dir = dirname;
	if (dirname.length()>8){
		dir = "default";
	}
	if (!SD.exists(dir)){
		dirExist = SD.mkdir(dir);
	} else {
		dirExist = true;
	}

	String fname = filename;
	if (filename.length()>8){
		fname = filename.substring(0,7);
	}
	// open the file. note that only one file can be open at a time,
	// so you have to close this one before opening another.
	String lgname = ((dirExist)? dir+"/":"")+fname+".csv";
	myFile = SD.open(lgname, FILE_WRITE);
	if (!myFile){
		if (Serial){
				Serial.println("File not created: "+lgname);
		}
	}
	logging = true;
	if (Serial){
		Serial.println("Log started");
	}
}

void Logger::stopLog(){
	if (myFile){
		myFile.close();
	}
	if (Serial){
		Serial.println("Log stopped");
	}
	logging = false;
}

void Logger::logStartStop(){

}
