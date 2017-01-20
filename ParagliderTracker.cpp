// Do not remove the include below
#include "ParagliderTracker.h"

Mahony filter;
unsigned long microsPerReading, microsPrevious;

int freq = 25; // angles measuring frequency
int p_freq = 50; // pressure measuring frequency


unsigned long baroReadTime, lastBaroRead;

String data = "";


int gps_freq = 100; // GPS read frequency

unsigned long lastGPSRead, timeToGetGPS;

Barometer barometer;
Compass compass;
MPU mpu;
Timer timer;
Logger logger;
GPS gps;


void initSchedule(){
  // init variables to time the GPS read
  timeToGetGPS = 1000000 / gps_freq;
  lastGPSRead = micros();

  // initialize variables to pace updates to correct rate
  microsPerReading = 1000000 / freq;
  microsPrevious = micros();

  // initialize variables to time the barometer read
  baroReadTime = 1000000 / p_freq;
  lastBaroRead = micros();
}



void setup() {

	initSchedule();

	mpu.init();
	compass.init();
	barometer.init();
	filter.begin(freq);
	timer.init();

	Serial.begin(115200);

	logger.startLog(timer.makeLogName());

	gps.init();

	delay(3000);
}

void loop() {
  unsigned long microsNow = micros();

//  if (microsNow - lastGPSRead >= timeToGetGPS){
//    gps.getGPSData();
//    lastGPSRead += timeToGetGPS;
//  }

  gps.getGPSData();

  if (microsNow - lastBaroRead >= baroReadTime){
	barometer.readAltitude();
    lastBaroRead += baroReadTime;
  }

  if (microsNow - microsPrevious >= microsPerReading) {
	timer.readDateTime();

	gps.parseGPSInfo();

    // Read normalized values
    Vector g_norm = mpu.readGyro();
    Vector a_norm = mpu.readAccel();
    float accel = mpu.calcAccelValue();

    Vector m_norm = compass.getNormalized();

    float heading = compass.correctHeading(heading);

    // update the filter, which computes orientation
    filter.update(
                      g_norm.XAxis,
                      g_norm.YAxis,
                      g_norm.ZAxis,
                      a_norm.XAxis,
                      a_norm.YAxis,
                      a_norm.ZAxis,
                      m_norm.XAxis,
                      m_norm.YAxis,
                      m_norm.ZAxis
                  );

    float oldYaw = mpu.getYaw();

    // print the heading, pitch and roll
    float roll = filter.getRoll();
    float pitch = filter.getPitch();
    float yaw = filter.getYaw();
    float yawRate = (oldYaw - yaw)*freq;

    // backup the values to MPU object
    mpu.setPitch(pitch);
    mpu.setRoll(roll);
    mpu.setYaw(yaw);

    data = "O: ";
    data+=String(yaw,4);
    data+=' ';
    data+=String(pitch,4);
    data+=' ';
    data+=String(roll,4);
    data+=' ';
    data+=String(yawRate,4);
    data+=' ';
    data+=String(mpu.calcAccelValue(),4);
    data+=' ';
    data+=String(barometer.getSmoothedAltitude(),4);
    data+=' ';
    data+=String(barometer.calcBaroVertSpd(),4);
    data+=' ';
    data+=String(heading,4);
    data+=' ';
    data+=timer.getTimestr();
    data+=' ';
    data+=gps.getLastGpsData();

    logger.logData(data);

    // increment previous time, so we keep proper pace
    microsPrevious += microsPerReading;
  }

}

