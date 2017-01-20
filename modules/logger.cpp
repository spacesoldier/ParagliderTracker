#include "logger.h"

Logger::Logger(){
	logName = "";
}

void Logger::logData(String in){
  if (Serial){
    Serial.println(in);
  }

  if (myFile) {
      myFile.println(in);
      // close the file:
      //myFile.close();
    }
}

void Logger::initSDCard(String fname){
  pinMode(CS_data, OUTPUT);

  // Firstly initializing SD card on Data shield...
  if (!SD.begin(CS_data)) {
    // initialization of SD on the Data shield failed. Try to init GPS shield
    pinMode(CS_data, INPUT);
    pinMode(CS_gps, OUTPUT);
    if (!SD.begin(CS_gps)){
      //initialization of SD slots failed.
    }
  }
  //initialization done.

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  String lgname = fname+".csv";
  myFile = SD.open(lgname, FILE_WRITE);

}

void Logger::startLog(String name){
  initSDCard(name);
}

