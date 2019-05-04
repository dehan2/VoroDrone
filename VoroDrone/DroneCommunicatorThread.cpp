#include "DroneCommunicatorThread.h"

DroneCommunicatorThread::DroneCommunicatorThread(QObject *parent, QMutex* mutex)
	:QThread(parent)
{
	droneInstance = nullptr;

	droneLat = 0.0f;
	droneLon = 0.0f;
	droneAlt = 0.0f;

	homeLat = 0.0f;
	homeLon = 0.0f;
	homeAlt = 0.0f;

	droneLat2 = 0.0f;
	droneLon2 = 0.0f;
	droneAlt2 = 0.0f;

	homeLat2 = 0.0f;
	homeLon2 = 0.0f;
	homeAlt2 = 0.0f;

	m_mutex = mutex;

	bTakeOff = false;
	bLand = false;
}

DroneCommunicatorThread::~DroneCommunicatorThread()
{
}



void DroneCommunicatorThread::run()
{
	while (true)
	{
		m_mutex->lock();

		if (bTakeOff == true)
		{
			armNtakeoffDrone(10);
			bTakeOff = false;
		}

		if (bLand == true)
		{
			land();
			bLand = false;
		}

		if (bGoTo == true)
		{
			go_to_location(targetX, targetY, targetZ);
			bGoTo = false;
		}

		getDroneLocation();
		m_mutex->unlock();
		emit hunter_location_updated();
		msleep(100);
	}
}



array<float, 3> DroneCommunicatorThread::translate_coord_to_gps(const float& x, const float& y, const float& z)
{
	double  RADIUS_EARTH_EQUATOR = 6378245.0;    // 지구 적도 반경 (단위:m)
	double  RADIUS_EARTH_POLAR = 6356863.0;    // 지구 극 반경 (단위:m)
	double  RATIO_MILE_TO_METER = 1609.344;    // 1 mile을 meter로 변환
	double  NORTH_TILT_MAGNETIC_TO_MAP = 6.5;
	int     RADAR_ACP_COUNT = 4096;     // ACP 분해각 개수
										// 전역 변수 정의
	double  Base_Dist_Latitude;  // 현 위도에서의 위도 1도에 대한 거리 (단위:m)
	double  Base_Dist_Longuitude;  // 현 위도에서의 경도 1도에 대한 거리 (단위:m)
	double  Radius_Earth;   // 현 위도에서의 지구 반경

							//double  RADAR_LATITUDE = 35.181692;    // RADAR 위치 : 위도
							//double  RADAR_LONGUITUDE = 128.950575;    // RADAR 위치 : 경도


	Radius_Earth = RADIUS_EARTH_POLAR + (RADIUS_EARTH_EQUATOR - RADIUS_EARTH_POLAR) * sin(degreeToRadian(homeLat));
	Base_Dist_Longuitude = 2.0 * M_PI * Radius_Earth / 360.0 * cos(degreeToRadian(homeLat));
	Base_Dist_Latitude = 2.0 * M_PI * Radius_Earth / 360.0;

	array<float, 3> gpsCoord{ homeLat + (y / Base_Dist_Latitude), homeLon + (x / Base_Dist_Longuitude), homeAlt + z };
	return gpsCoord;
}



array<float, 3> DroneCommunicatorThread::translate_gps_to_coord(const float& lat, const float& lon, const float& alt)
{
	double  RADIUS_EARTH_EQUATOR = 6378245.0;    // 지구 적도 반경 (단위:m)
	double  RADIUS_EARTH_POLAR = 6356863.0;    // 지구 극 반경 (단위:m)
	double  RATIO_MILE_TO_METER = 1609.344;    // 1 mile을 meter로 변환
	double  NORTH_TILT_MAGNETIC_TO_MAP = 6.5;
	int     RADAR_ACP_COUNT = 4096;     // ACP 분해각 개수
										// 전역 변수 정의
	double  Base_Dist_Latitude;  // 현 위도에서의 위도 1도에 대한 거리 (단위:m)
	double  Base_Dist_Longuitude;  // 현 위도에서의 경도 1도에 대한 거리 (단위:m)
	double  Radius_Earth;   // 현 위도에서의 지구 반경

							//double  RADAR_LATITUDE = 35.181692;    // RADAR 위치 : 위도
							//double  RADAR_LONGUITUDE = 128.950575;    // RADAR 위치 : 경도


	Radius_Earth = RADIUS_EARTH_POLAR + (RADIUS_EARTH_EQUATOR - RADIUS_EARTH_POLAR) * sin(degreeToRadian(homeLat));
	Base_Dist_Longuitude = 2.0 * M_PI * Radius_Earth / 360.0 * cos(degreeToRadian(homeLat));
	Base_Dist_Latitude = 2.0 * M_PI * Radius_Earth / 360.0;

	float x = (lon - homeLon)*Base_Dist_Longuitude;
	float y = (lat - homeLat)*Base_Dist_Latitude;
	float z = alt - homeAlt;

	array<float, 3> coord{ x, y, z};
	return coord;
}



array<float, 3> DroneCommunicatorThread::calculate_drone_coord()
{
	return translate_gps_to_coord(droneLat, droneLon, droneAlt);
}

void DroneCommunicatorThread::initialize(const string& address, const string& address2)
{
	Py_Initialize();
	PyObject* dronekit_module = PyImport_ImportModule("droneConnector");
	PyObject* drone_get_class = PyObject_GetAttrString(dronekit_module, "drone_get");
	string inputConnect(address);
	string inputConnect2(address2);
	PyObject* pyInputConnect = PyTuple_New(2);
	PyTuple_SetItem(pyInputConnect, 0, PyString_FromString(inputConnect.c_str()));
	PyTuple_SetItem(pyInputConnect, 1, PyString_FromString(inputConnect2.c_str()));
	droneInstance = PyObject_CallObject(drone_get_class, pyInputConnect);

	PyObject *pyLat, *pyLon, *pyAlt;
	char func_name[] = "getLocation";
	PyObject* result = PyObject_CallMethod(droneInstance, func_name, NULL);

	pyLat = PyList_GetItem(result, 0);
	pyLon = PyList_GetItem(result, 1);
	pyAlt = PyList_GetItem(result, 2);
	homeLat = (float)PyFloat_AsDouble(pyLat);
	homeLon = (float)PyFloat_AsDouble(pyLon);
	//homeAlt = (float)PyFloat_AsDouble(pyAlt);
	homeAlt = 10;

	PyObject *pyLat2, *pyLon2, *pyAlt2;
	pyLat2 = PyList_GetItem(result, 3);
	pyLon2 = PyList_GetItem(result, 4);
	pyAlt2 = PyList_GetItem(result, 5);
	homeLat2 = (float)PyFloat_AsDouble(pyLat2);
	homeLon2 = (float)PyFloat_AsDouble(pyLon2);
	//homeAlt = (float)PyFloat_AsDouble(pyAlt);
	homeAlt2 = 10;
}

void DroneCommunicatorThread::finalize()
{
	Py_Finalize();
}


void DroneCommunicatorThread::getDroneLocation()
{
	PyObject *pyLat, *pyLon, *pyAlt;
	PyObject *pyLat2, *pyLon2, *pyAlt2;
	char func_name[] = "getLocation";
	PyObject* result = PyObject_CallMethod(droneInstance, func_name, NULL);

	pyLat = PyList_GetItem(result, 0);
	pyLon = PyList_GetItem(result, 1);
	pyAlt = PyList_GetItem(result, 2);
	droneLat = (float)PyFloat_AsDouble(pyLat);
	droneLon = (float)PyFloat_AsDouble(pyLon);
	droneAlt = (float)PyFloat_AsDouble(pyAlt);

	pyLat2 = PyList_GetItem(result, 3);
	pyLon2 = PyList_GetItem(result, 4);
	pyAlt2 = PyList_GetItem(result, 5);
	droneLat2 = (float)PyFloat_AsDouble(pyLat2);
	droneLon2 = (float)PyFloat_AsDouble(pyLon2);
	droneAlt2 = (float)PyFloat_AsDouble(pyAlt2);
}



void DroneCommunicatorThread::armNtakeoffDrone(float inputAlt)
{
	//inputalt (m)
	char func_name[] = "armNtakeoff";
	char format[] = "f";
	PyObject* takeOff = PyObject_CallMethod(droneInstance, func_name, format, inputAlt);
}



void DroneCommunicatorThread::land()
{
	char func_name[] = "land";
	PyObject* Landing = PyObject_CallMethod(droneInstance, func_name, NULL);
}



void DroneCommunicatorThread::simplGotoDrone(float nextLat, float nextLon, float nextAlt, float groundspeed)
{
	
		//groundsped (m/s)
		char func_name[] = "simpleGoto";
		char format[] = "fff";
		PyObject* simpleGoTo = PyObject_CallMethod(droneInstance, func_name, format, nextLat, nextLon, nextAlt);

}



void DroneCommunicatorThread::go_to_location(const float& x, const float& y, const float& z)
{
	array<float, 3> gpsCoord = translate_coord_to_gps(x, y, z);
	//groundsped (m/s)
	char func_name[] = "simpleGoto";
	char format[] = "fff";
	PyObject* simpleGoTo = PyObject_CallMethod(droneInstance, func_name, format, gpsCoord.at(0), gpsCoord.at(1), gpsCoord.at(2));
}
