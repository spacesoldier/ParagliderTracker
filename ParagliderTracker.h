// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _ParagliderTracker_H_
#define _ParagliderTracker_H_
#include "Arduino.h"

//add your includes for the project ParagliderTracker here
#include "lib/MahonyAHRS/src/MahonyAHRS.h"

// project module headers
#include "modules/timer.h"
#include "modules/compass.h"
#include "modules/barometer.h"
#include "modules/mpu.h"
#include "modules/gps.h"
#include "modules/logger.h"
//#include "modules/switch.h"
#include "lib/Button/Button.h"
//end of add your includes here


//add your function definitions for the project ParagliderTracker here

void initSchedule();

//Do not add code below this line
#endif /* _ParagliderTracker_H_ */
