#include "timer.h"

Timer::Timer(){
	timestr = "";
}

String Timer::makeLogName(){
	timeNow = rtc.now();
	String result = String(timeNow.month());
	result += String(timeNow.day());
	result += String(timeNow.hour());
	result += String(timeNow.minute());
	return result;
}

void Timer::readDateTime(){
    timeNow = rtc.now();
    timestr = "";
    timestr.concat(timeNow.year());
    timestr.concat('-');
    timestr.concat(timeNow.month());
    timestr.concat('-');
    timestr.concat(timeNow.day());
    timestr.concat(' ');
    if (timeNow.hour()<10){
      timestr.concat('0');
    }
    timestr.concat(timeNow.hour());
    timestr.concat(':');
    if (timeNow.minute()<10){
      timestr.concat('0');
    }
    timestr.concat(timeNow.minute());
    timestr.concat(':');
    if (timeNow.second()<10){
      timestr.concat('0');
    }
    timestr.concat(timeNow.second());
}


void Timer::init(){
  if (! rtc.begin()) {
//    logData("RTC fail");
  }

//  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  if (! rtc.isrunning()) {
//    logData("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

const DateTime& Timer::getTimeNow() const {
	return timeNow;
}

const String& Timer::getTimestr() const {
	return timestr;
}
