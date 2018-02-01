#pragma once

#include <QThread>
#include <Python.h>
#include <string>
#include <QMutex>
#include <array>

#define _USE_MATH_DEFINES 
#include <math.h>

using namespace std;

class DroneCommunicatorThread: public QThread
{
	Q_OBJECT

public:
	bool isConnected;

	PyObject *droneInstance;

	string droneAddress;
	float droneLat, droneLon, droneAlt;
	float homeLat, homeLon, homeAlt;

	QMutex* m_mutex;
	bool bTakeOff;
	bool bLand;
	bool bGoTo;
	float targetX, targetY, targetZ;

public:
	DroneCommunicatorThread(QObject *parent, QMutex* mutex);
	~DroneCommunicatorThread();

	void run();
	array<float, 3> translate_coord_to_gps(const float& x, const float& y, const float& z);
	array<float, 3> translate_gps_to_coord(const float& lat, const float& lon, const float& alt);
	array<float, 3> calculate_drone_coord();
	inline double  degreeToRadian(double a) const { return (M_PI * a / 180.0); }

signals:
	void start_communication();
	void hunter_location_updated();

	public slots:
	void initialize(const string& address);
	void finalize();
	void getDroneLocation();
	void armNtakeoffDrone(float inputAlt);
	void land();
	void simplGotoDrone(float nextLat, float nextLon, float nextAlt, float groundspeed);
	void go_to_location(const float& x, const float& y, const float& z);
};
