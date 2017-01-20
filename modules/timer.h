#ifndef TIMER_H
#define TIMER_H

// hardware library
#include "../lib/RTClib/RTClib.h"
//#include <RTClib.h>


class Timer{
private:
	RTC_DS1307 rtc;
	//char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	DateTime timeNow;
	String timestr;

public:
	Timer();
	void init();
	void readDateTime();

	const DateTime& getTimeNow() const ;

	const String& getTimestr() const ;

	String makeLogName();

};








#endif
