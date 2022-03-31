#include "IMU_data.h"

bool  IMU_data::containsAccel() const {
	return _containsAccel;
}
bool IMU_data::containsMagneticField() const {
	return _containsMagneticField;
}
bool IMU_data::containsOrientationEuler() const {
	return _containsOrientationEuler;
}
bool IMU_data::containsOrientationQuaternion() const {
	return _containsOrientationQuaternion;
}
bool IMU_data::containsGravity()const {
	return _containsGravity;
}
bool  IMU_data::containsAngularSpeed()const
{
	return _containsAngularSpeed;
}
IMU_Vector3d  IMU_data::getAccel() const
{
	return _accel;
}
IMU_Vector3d IMU_data::getMagneticField() const {
	return _magneticField;
}
IMU_Vector3d IMU_data::getGravity()const {
	return _gravity;
}
IMU_Vector3d  IMU_data::getOrientationEuler()const
{
	return _orientationEuler;
}
IMU_Quaternion IMU_data::getOrientationQuaternion()const {
	return _orientationQuaternion;
}
IMU_Vector3d  IMU_data::getAngularSpeed()const
{
	return _angularSpeed;
}
void IMU_data::setMagneticField(const IMU_Vector3d& magneticField) {
	_magneticField = magneticField;
	_containsMagneticField = true;
}
void IMU_data::setGravity(const IMU_Vector3d& angularSpeed) {
	_angularSpeed = angularSpeed;
	_containsGravity = true;
}
void IMU_data::setAccel(const IMU_Vector3d& accel)
{
	_accel = accel;
	_containsAccel = true;
}
void IMU_data::setOrientationEuler(const IMU_Vector3d& orientationEuler)
{
	_orientationEuler = orientationEuler;
	_containsOrientationEuler = true;
}
void IMU_data::setOrientationQuaternion(const IMU_Quaternion& orientationQuaternion) {
	_orientationQuaternion = orientationQuaternion;
}
void IMU_data::setAngularSpeed(const IMU_Vector3d& angularSpeed)
{
	_angularSpeed = angularSpeed;
	_containsAngularSpeed = true;
}

