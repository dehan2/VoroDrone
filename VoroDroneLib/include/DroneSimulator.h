#pragma once

#include "DynamicSimulator3D.h"
#include "DynamicBall.h"
#include "rg_Sphere3D.h"
#include "rg_Point3D.h"
#include "constForVoroDroneLib.h"
#include "ShorestPathAvoidingSphericalObstacles.h"
#include <Python.h>

static const float shortestPathMargin = 0.3;
static const int numRandomPoints = 100;

class DroneSimulator : public DynamicSimulator3D
{
private:
	DynamicBall m_hunter;
	DynamicBall m_bug;
	list<DynamicBall> m_obstacles;

	list<pair<rg_Point3D, DECIMAL>> m_hunterWayPoints;
	list<pair<rg_Point3D, DECIMAL>> m_bugWayPoints;

	int m_n;
	float m_r;
	float m_theta;
	float m_minV, m_maxV;

	float m_fenceLength;	//X
	float m_fenceWidth;	//Y
	float m_fenceHeight;	//Z
	float m_pathComputationInterval;

	double m_homeLatitude;
	double m_homeLongtitude;
	double m_homeAltitude;

	map<const DynamicBall*, Color3f> m_obstacleColorMap;
	list<rg_Point3D> m_hunterTrajectory;
	float m_hunterSpeed;

	vector<rg_Point3D> m_randomBugLocationCandidates;
	float m_bugSpeed;
	BUG_GENERATION_MODE m_bugGenerationMode;

public:
	DroneSimulator();
	virtual ~DroneSimulator();

	inline int get_n() const { return m_n; }
	inline float get_r() const { return m_r; }
	inline float get_theta() const { return m_theta; }
	inline float get_minV() const { return m_minV; }
	inline float get_maxV() const { return m_maxV; }
	inline float get_bug_speed() const { return m_bugSpeed; }
	inline float get_fence_length() const { return m_fenceLength; }
	inline float get_fence_width() const { return m_fenceWidth; }
	inline float get_fence_height() const { return m_fenceHeight; }
	inline float get_path_computation_interval() const { return m_pathComputationInterval; }
	inline list<pair<rg_Point3D, DECIMAL>>& get_hunter_way_points() { return m_hunterWayPoints; }
	inline const list<pair<rg_Point3D, DECIMAL>>& get_bug_way_points() const { return m_bugWayPoints; }

	inline double get_home_latitude() const { return m_homeLatitude; }
	inline double get_home_longtitude() const { return m_homeLongtitude; }
	inline double get_home_altitude() const { return m_homeAltitude; }
	inline const map<const DynamicBall*, Color3f>& get_obstacle_color_map() const { return m_obstacleColorMap; }

	inline void set_n(const int& n) { m_n = n; }
	inline void set_r(const float& r) { m_r = r; }
	inline void set_theta(const float& theta) { m_theta = theta; }
	inline void set_minV(const float& minV) { m_minV = minV; }
	inline void set_maxV(const float& maxV) { m_maxV = maxV; }

	inline void set_fence_length(const float& fenceLength) { m_fenceLength = fenceLength; }
	inline void set_fence_width(const float& fenceWidth) { m_fenceWidth = fenceWidth; }
	inline void set_fence_height(const float& fenceHeight) { m_fenceHeight = fenceHeight; }
	inline void set_path_compuation_interval(const float& pathComputationInterval) { m_pathComputationInterval = pathComputationInterval; }

	inline void set_home_latitude(const double& latitude) { m_homeLatitude = latitude; }
	inline void set_home_longtitude(const double& longtitude) { m_homeLongtitude = longtitude; }
	inline void set_home_altitude(const double& altitude) { m_homeAltitude = altitude; }

	inline const DynamicBall& get_hunter() const { return m_hunter; }
	inline const DynamicBall& get_bug() const { return m_bug; }
	inline const list<DynamicBall>& get_obstacles() const { return m_obstacles; }
	inline const list<rg_Point3D>& get_hunter_trajectory() const { return m_hunterTrajectory; }

	inline void set_hunter_location(const float& x, const float& y, const float& z) { m_hunter.set_sphere_center(rg_Point3D(x, y, z)); }
	inline void set_hunter_speed(const float& hunterSpeed) { m_hunterSpeed = hunterSpeed; }
	inline void set_hunter_time(const float& time) { m_hunter.set_time(time); }

	inline void set_bug_speed(const float& bugSpeed) { m_bugSpeed = bugSpeed; }
	inline void set_bug_generation_mode(const BUG_GENERATION_MODE& mode) { m_bugGenerationMode = mode; }



	void generate_drones();
	void generate_drones_in_fence(const float& fenceLength, const float& fenceWidth, const float& fenceHeight, const float& margin);

	void prepare_simulation(const double& timeWindow);

	void save_drone_informations(const string& filePath);
	void load_drone_informations(const string& filePath);

	void find_shortest_path_from_hunter_to_bug();

	void check_collision_between_fence_and_obstacles();
	bool is_collide_to_fence(const DynamicBall& ball) const;


	virtual void increase_time(const DECIMAL& timeIncrement);
	virtual void go_to_time(const DECIMAL& time);
	
	void generate_hunter_way_points(const ShorestPathAvoidingSphericalObstacles& path);
	void generate_bug_way_points(const float& bugSpeed, const float& currTime);
	void generate_bug_way_points_on_fence_boundary(const float& bugSpeed, const float& currTime);
	void generate_bug_way_points_to_random_point(const float& bugSpeed, const float& currTime);
	void find_random_bug_location_candidate_using_VVtx();
	void make_random_bug_location_candidates();

	DynamicBall* find_closest_obstacle_from_hunter();
	Sphere find_tangent_sphere_between_hunter_and_neighbors();
	void color_hunter_neighbors(const Color3f& colorForNeighbor);
	inline void clear_color_map() { m_obstacleColorMap.clear(); }

	void make_new_bug();

	void update_hunter_trajectory();

	void set_hunter_target(const rg_Point3D& target);

private:
	void update_bug(const DECIMAL& time);
	bool is_included_in_balls(const rg_Point3D& point, const float& threshold);
};

