#ifndef MPU_H
#define MPU_H

// sensor library
#include "../lib/MPU6050/MPU6050.h"

class MPU{
private:
	MPU6050 mpu;

	// Pitch, Roll and Yaw values
	float pitch = 0;
	float roll = 0;
	float yaw = 0;

	float yawRate = 0;

	// acceleration vector
	Vector accel;
	// rotate angles vector
	Vector rotate;

public:
	Vector readGyro();
	Vector readAccel();
	void init();
	float calcAccelValue();

	const Vector& getAccel() const {
		return accel;
	}

	float getPitch() const {
		return pitch;
	}

	float getRoll() const {
		return roll;
	}

	const Vector& getRotate() const {
		return rotate;
	}

	float getYaw() const {
		return yaw;
	}

	float getYawRate() const {
		return yawRate;
	}

	void setPitch(float pitch = 0) {
		this->pitch = pitch;
	}

	void setRoll(float roll = 0) {
		this->roll = roll;
	}

	void setYaw(float yaw = 0) {
		this->yaw = yaw;
	}

	void setYawRate(float yawRate = 0) {
		this->yawRate = yawRate;
	}
};




#endif
