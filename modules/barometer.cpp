#include "barometer.h"

Barometer::Barometer(){
	baseline = 0.0; // baseline pressure

	baroAlt = 0.0;
	// for exponential pressure smoothing
	alpha = 0.3;
}

void Barometer::init(){
  //start barometer
  if (!pressure.begin()){
//    logData("BMP180 fail (wiring?)");
  }

  // initial barometer read
  baseline = getPressure();
  prevSmooth = 0;

}

double Barometer::getPressure()
{
  char status;
  double T,P,p0,a;

  // You must first get a temperature measurement to perform a pressure reading.

  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Use '&T' to provide the address of T to the function.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(1);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Use '&P' to provide the address of P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P,T);
        if (status != 0){
          return(P);
        }
      }
    }
  }
  return 0;
}

float last_baro_alt = 0;
unsigned long lastBaroVSpdTake;

float Barometer::calcBaroVertSpd(){
  unsigned long currTime = micros();
  float result = 1000000*(baroAlt - last_baro_alt)/(currTime - lastBaroVSpdTake);
  lastBaroVSpdTake = currTime;
  last_baro_alt = baroAlt;
  return result;
}

float Barometer::smoothAltitudeExp(float a){
  // exponential smoothing:
  float as = a*alpha + (1-alpha)*prevSmooth;
  prevSmooth = as;
  return as;
}

void Barometer::readAltitude(){
	// Get a new pressure reading:
	 double P = Barometer::getPressure();
	// Show the relative altitude difference between
	// the new reading and the baseline reading:
	 baroAlt = pressure.altitude(P,baseline);
}

float Barometer::getSmoothedAltitude(){
	return smoothAltitudeExp(baroAlt);
}
