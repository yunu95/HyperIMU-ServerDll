#include "IMU_Vector3d.h"
#include "IMU_Quaternion.h"
#pragma once

class IMU_data
{
private:
	bool _containsAccel = false;
	bool _containsMagneticField = false;
	bool _containsOrientationEuler = false;
	bool _containsOrientationQuaternion = false;
	bool _containsGravity = false;
	bool _containsAngularSpeed = false;
	IMU_Vector3d _accel;
	IMU_Vector3d _magneticField;
	IMU_Vector3d _orientationEuler;
	IMU_Quaternion _orientationQuaternion;
	IMU_Vector3d _gravity;
	IMU_Vector3d _angularSpeed;
public:
	bool containsAccel() const;
	bool containsMagneticField() const;
	bool containsOrientationEuler() const;
	bool containsOrientationQuaternion() const;
	bool containsGravity()const;
	bool containsAngularSpeed()const;
	IMU_Vector3d getAccel() const;
	IMU_Vector3d getMagneticField() const;
	IMU_Vector3d getOrientationEuler()const;
	IMU_Quaternion getOrientationQuaternion()const;
	IMU_Vector3d getGravity()const;
	IMU_Vector3d getAngularSpeed()const;

	void setAccel(const IMU_Vector3d& accel);
	void setMagneticField(const IMU_Vector3d& magneticField);
	void setOrientationEuler(const IMU_Vector3d& orientationEuler);
	void setOrientationQuaternion(const IMU_Quaternion& orientationQuaternion);
	void setGravity(const IMU_Vector3d& angularSpeed);
	void setAngularSpeed(const IMU_Vector3d& angularSpeed);
};
