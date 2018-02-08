#include "DroneSimulator.h"
#include <random>
#include <ctime>
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>

DroneSimulator::DroneSimulator()
{
	m_n = 0;
	m_r = 0.0;
	m_theta = 0.0;
	m_minV = 1.0;
	m_maxV = 1.0;

	m_fenceLength = 50.0;
	m_fenceWidth = 50.0;
	m_fenceHeight = 10.0;
	m_pathComputationInterval = 0.5;

	m_simulationType = LINEAR;
	m_hunter.set_type(LINEAR_BALL);
	m_bug.set_type(LINEAR_BALL);
	m_hunter.set_time(0);
	m_bug.set_time(0);
	

}


DroneSimulator::~DroneSimulator()
{
}


void DroneSimulator::generate_drones()
{
	m_hunter.set_ID(0);
	m_hunter.set_sphere_center(rg_Point3D());
	m_hunter.set_sphere_radius(m_r + m_theta);

	m_bug.set_ID(1);
	
	m_bug.set_sphere_radius(m_r + m_theta);

	generate_drones_in_fence(m_fenceLength, m_fenceWidth, m_fenceHeight, 0.5);
}



void DroneSimulator::generate_drones_in_fence(const float& fenceLength, const float& fenceWidth, const float& fenceHeight, const float& margin)
{
	default_random_engine engine;
	engine.seed(time(0));

	float obstacleRadius = m_r + m_theta;
	float cellSize = 2*obstacleRadius + margin;
	//float cellSize = 2*(m_r + m_theta) + m_maxV*m_pathComputationInterval+margin;

	int numCell_x = floor(fenceLength / (2*cellSize));
	int numCell_y = floor(fenceWidth / (2*cellSize));
	int numCell_z = floor(fenceHeight / (2*cellSize));

	set<int> indexForFilledCell;
	int lastCellIndex = numCell_x * numCell_y*numCell_z;
	uniform_int_distribution<int> iRand{ 0, lastCellIndex };
	while (indexForFilledCell.size() < m_n)
	{
		int cellIndex = iRand(engine);
		if (indexForFilledCell.count(cellIndex) == 0)
			indexForFilledCell.insert(cellIndex);
	}

	rg_Point3D startCorner(-cellSize *numCell_x, -cellSize *numCell_y, (m_fenceHeight-2* cellSize*numCell_z)/2);
	for (int k = 0; k < numCell_z; k++)
	{
		for (int j = 0; j < numCell_y; j++)
		{
			for (int i = 0; i < numCell_x; i++)
			{
				int cellIndex = i + numCell_x*(j + numCell_y *k) ;
				if (indexForFilledCell.count(cellIndex) > 0)
				{
					uniform_real_distribution<float> fRand{ -margin, margin };
					Sphere sphere(rg_Point3D(fRand(engine)*margin + (2 * i + 1)* cellSize, fRand(engine)*margin + (2 * j+ 1)* cellSize, 
						fRand(engine)*margin + (2 * k + 1)* cellSize)+startCorner, obstacleRadius);
					rg_Point3D velocity = rg_Point3D(fRand(engine), fRand(engine), fRand(engine));
					float ratio = fRand(engine);
					velocity = velocity.getUnitVector()*((1 - ratio)*m_maxV + ratio * m_minV);
					m_obstacles.push_back(DynamicBall(m_obstacles.size() + 2, LINEAR_BALL, sphere, velocity));
				}
			}
		}
	}
}



void DroneSimulator::prepare_simulation(const double& timeWindow)
{
	//m_dynamicBalls.push_back(&m_bug);
	for (list<DynamicBall>::iterator itForBall = m_obstacles.begin(); itForBall != m_obstacles.end(); itForBall++)
	{
		m_dynamicBalls.push_back(&*itForBall);
	}
	
	rg_Point3D tetrahedronVertices[8];
	tetrahedronVertices[0] = 200*rg_Point3D(1, 0, -0.707);
	tetrahedronVertices[1] = 200 *rg_Point3D(-1, 0, -0.707);
	tetrahedronVertices[2] = 200 *rg_Point3D(0, 1, 0.707);
	tetrahedronVertices[3] = 200 *rg_Point3D(0, -1, 0.707);
	tetrahedronVertices[4] = 150 *rg_Point3D(-1, 0, 0.707);
	tetrahedronVertices[5] = 150 *rg_Point3D(1, 0, 0.707);
	tetrahedronVertices[6] = 150 *rg_Point3D(0, -1, -0.707);
	tetrahedronVertices[7] = 150 *rg_Point3D(0, 1, -0.707);

	int beginningIDOfPhantom = m_dynamicBalls.size() + 3;
	for (int i = 0; i < 8; i++)
	{
		m_dynamicBalls.push_back(new DynamicBall(beginningIDOfPhantom + i, STATIC_BALL, Sphere(tetrahedronVertices[i], m_r), rg_Point3D()));
	}

	m_dynamicVD.construct_initial_VD(m_dynamicBalls);
	m_dynamicVD.set_time_window(timeWindow);
	m_dynamicVD.construct_initial_event_queue();
	m_dynamicVD.fenceLength = m_fenceLength;
	m_dynamicVD.fenceWidth = m_fenceWidth;
	m_dynamicVD.fenceHeight = m_fenceHeight;
	check_collision_between_fence_and_obstacles();
	color_next_event();
}



void DroneSimulator::save_drone_informations(const string& filePath)
{
	ofstream droneInfoFile(filePath);

	droneInfoFile << m_n << "\t"<<m_r<<"\t"<< m_theta << "\t" << m_minV << "\t" << m_maxV << "\t" << m_fenceLength << "\t" << m_fenceWidth << "\t" << m_fenceHeight << "\t" << m_pathComputationInterval <<"\n";
	for (auto& obstacle : m_obstacles)
	{
		rg_Point3D obstacleCenter = obstacle.get_sphere().getCenter();
		rg_Point3D obstacleVelocity = obstacle.get_velocity_vector();
		droneInfoFile << obstacle.get_ID() << "\t" << obstacleCenter.getX() << "\t" << obstacleCenter.getY() << "\t" << obstacleCenter.getZ() << "\t" << obstacleVelocity.getX() << "\t" << obstacleVelocity.getY() << "\t" << obstacleVelocity.getZ() << "\n";
	}
	droneInfoFile.close();
}



void DroneSimulator::load_drone_informations(const string& filePath)
{
	ifstream fin;
	fin.open(filePath.c_str());

	const char* seps = " \t\n";
	char buffer[200];

	while (fin.getline(buffer, 200))
	{
		if (buffer[0] != '#')
		{
			break;
		}
	};

	m_n = atoi(strtok(buffer, seps));
	m_r = atof(strtok(NULL, seps));
	m_theta = atof(strtok(NULL, seps));
	m_minV = atof(strtok(NULL, seps));
	m_maxV = atof(strtok(NULL, seps));
	m_fenceLength = atof(strtok(NULL, seps));
	m_fenceWidth = atof(strtok(NULL, seps));
	m_fenceHeight = atof(strtok(NULL, seps));
	m_pathComputationInterval = atof(strtok(NULL, seps));

	float obstacleRadius = m_r + m_theta;

	for (int i = 0; i < m_n-2; i++)
	{
		//for obstacle
		fin.getline(buffer, 200);
		int id = atoi(strtok(buffer, seps));
		float x = atof(strtok(NULL, seps));
		float y = atof(strtok(NULL, seps));
		float z = atof(strtok(NULL, seps));

		float vecX = atof(strtok(NULL, seps));
		float vecY = atof(strtok(NULL, seps));
		float vecZ = atof(strtok(NULL, seps));
		rg_Point3D center(x, y, z);
		rg_Point3D velocity(vecX, vecY, vecZ);
		m_obstacles.push_back(DynamicBall(id, LINEAR_BALL, Sphere(center, obstacleRadius), velocity));
	}

	fin.close();

	m_hunter.set_ID(0);
	m_hunter.set_sphere_center(rg_Point3D());
	m_hunter.set_sphere_radius(m_r + m_theta);

	m_bug.set_ID(1);
	m_bug.set_sphere_radius(m_r + m_theta);

}


void DroneSimulator::find_shortest_path_from_hunter_to_bug()
{
	ShorestPathAvoidingSphericalObstacles   shortestPath;
	list<Sphere> enlargedObstacles;
	for (list<DynamicBall>::const_iterator itForObstacle = m_obstacles.cbegin(); itForObstacle != m_obstacles.cend(); itForObstacle++)
	{
		Sphere enlargedObstacle((*itForObstacle).get_sphere().getCenter(), (*itForObstacle).get_sphere().getRadius() + shortestPathMargin);
		if (enlargedObstacle.intersect(m_hunter.get_sphere()) == SI_NOT_INTERSECT)
		{
			enlargedObstacles.push_back(enlargedObstacle);
		}
	}
	//cout << "Obstacle radius: " << m_obstacles.front().get_sphere().getRadius() << ", to path comp: " << enlargedObstacles.front().getRadius()<<endl;
	shortestPath.set_problem(m_hunter.get_sphere().getCenter(), m_bug.get_sphere().getCenter(), m_hunter.get_sphere(), enlargedObstacles);
	shortestPath.find_the_shortest_path();
	generate_hunter_way_points(shortestPath);
}



void DroneSimulator::check_collision_between_fence_and_obstacles()
{
	for (list<DynamicBall>::iterator itForObstacle = m_obstacles.begin(); itForObstacle != m_obstacles.end(); itForObstacle++)
	{
		DECIMAL collisionTime = m_dynamicVD.compute_possible_collision_time_with_fence(&*itForObstacle);
		if (collisionTime < m_dynamicVD.get_time_window())
		{
			m_dynamicVD.add_velocity_change_event((*itForObstacle).get_ID(), collisionTime);
		}
	}
}



bool DroneSimulator::is_collide_to_fence(const DynamicBall& ball) const
{
	rg_Point3D center = ball.get_sphere().getCenter();
	float radius = ball.get_sphere().getRadius();
	if (center.getX() > (m_fenceLength / 2 - radius)
		|| center.getX() < (-m_fenceLength / 2 + radius)
		|| center.getY() > (m_fenceWidth / 2 - radius)
		|| center.getY() < (-m_fenceWidth / 2 + radius)
		|| center.getZ() > (m_fenceHeight - radius)
		|| center.getZ() < radius)
		return true;
	else
		return false;
}



void DroneSimulator::increase_time(const DECIMAL& timeIncrement)
{
	DynamicSimulator3D::increase_time(timeIncrement);
	//update_hunter(m_dynamicVD.get_current_time());
	//cout << "Curr time: " << m_dynamicVD.get_current_time() << endl;
	update_bug(m_dynamicVD.get_current_time());
	update_hunter_trajectory();
}



void DroneSimulator::go_to_time(const DECIMAL& time)
{
	DynamicSimulator3D::go_to_time(time);
	//update_hunter(m_dynamicVD.get_current_time());
	update_bug(m_dynamicVD.get_current_time());
	update_hunter_trajectory();
}



void DroneSimulator::generate_hunter_way_points(const ShorestPathAvoidingSphericalObstacles& path)
{
	m_hunterWayPoints.clear();
	DECIMAL timeForPathPoint = m_hunter.get_time();
	rg_Point3D lastPoint = m_hunter.get_sphere().getCenter();
	float totalDistance = 0;

	for (vector<rg_Point3D>::const_iterator itForPath = path.points_on_the_shortest_path().cbegin();
		itForPath != path.points_on_the_shortest_path().cend(); itForPath++)
	{
		float distance = (*itForPath).distance(lastPoint);
		timeForPathPoint += distance / m_hunterSpeed;
		m_hunterWayPoints.push_back(make_pair(*itForPath, timeForPathPoint));
		lastPoint = *itForPath;

		totalDistance += distance;
		//cout << m_hunterWayPoints.size() << "th wp: " << totalDistance << ", " << timeForPathPoint << endl;
	}
}





void DroneSimulator::generate_bug_way_points(const float& bugSpeed, const float& currTime)
{
	//cout << "Generate new way point at " <<m_dynamicVD.get_current_time()<< endl;

	m_bugWayPoints.clear();
	switch (m_bugGenerationMode)
	{
	case ON_FENCE:
		generate_bug_way_points_on_fence_boundary(bugSpeed, currTime);
		break;
	case RANDOM:
	default:
		generate_bug_way_points_to_random_point(bugSpeed, currTime);
		break;
	}

	rg_Point3D& nextPoint = m_bugWayPoints.front().first;
	rg_Point3D velocity = (nextPoint - m_bug.get_sphere().getCenter()).getUnitVector()*bugSpeed;
	m_bug.set_velocity_vector(velocity);
}



void DroneSimulator::generate_bug_way_points_on_fence_boundary(const float& bugSpeed, const float& currTime)
{
	m_bug.set_sphere_center(rg_Point3D(m_fenceLength / 2, m_fenceWidth / 2, m_fenceHeight));

	list<rg_Point3D> pathPoints;
	pathPoints.push_back(rg_Point3D(-m_fenceLength / 2, m_fenceWidth / 2, m_fenceHeight));
	pathPoints.push_back(rg_Point3D(-m_fenceLength / 2, m_fenceWidth / 2, 0));
	pathPoints.push_back(rg_Point3D(-m_fenceLength / 2, -m_fenceWidth / 2, 0));
	pathPoints.push_back(rg_Point3D(-m_fenceLength / 2, -m_fenceWidth / 2, m_fenceHeight));
	pathPoints.push_back(rg_Point3D(m_fenceLength / 2, -m_fenceWidth / 2, m_fenceHeight));
	pathPoints.push_back(rg_Point3D(m_fenceLength / 2, -m_fenceWidth / 2, 0));
	pathPoints.push_back(rg_Point3D(m_fenceLength / 2, m_fenceWidth / 2, 0));
	pathPoints.push_back(rg_Point3D(m_fenceLength / 2, m_fenceWidth / 2, m_fenceHeight));

	//cout << "Generate bug way points!" << endl;

	rg_Point3D lastPoint = m_bug.get_sphere().getCenter();
	DECIMAL timeToNextPoint = currTime;
	while (!pathPoints.empty())
	{
		rg_Point3D& nextPoint = pathPoints.front();
		timeToNextPoint += lastPoint.distance(nextPoint) / bugSpeed;
		//cout << "time to wp: " << timeToNextPoint << endl;
		m_bugWayPoints.push_back(make_pair(nextPoint, timeToNextPoint));
		lastPoint = nextPoint;
		pathPoints.pop_front();
	}
}



void DroneSimulator::generate_bug_way_points_to_random_point(const float& bugSpeed, const float& currTime)
{
	default_random_engine engine;
	engine.seed(time(0));
	uniform_int_distribution<int> iRand{ 0, int(m_randomBugLocationCandidates.size()) -1 };

	list<Sphere> enlargedObstacles;
	for (list<DynamicBall>::const_iterator itForObstacle = m_obstacles.cbegin(); itForObstacle != m_obstacles.cend(); itForObstacle++)
	{
		Sphere enlargedObstacle((*itForObstacle).get_sphere().getCenter(), (*itForObstacle).get_sphere().getRadius() + 0.4);
		enlargedObstacles.push_back(enlargedObstacle);
	}
	ShorestPathAvoidingSphericalObstacles   shortestPath;

	rg_Point3D& randomDestination = m_randomBugLocationCandidates.at(iRand(engine));
	while (m_bug.get_sphere().distance(randomDestination) < 10 || shortestPath.points_on_the_shortest_path().size() <= 2)
	{
		randomDestination = m_randomBugLocationCandidates.at(iRand(engine));
		shortestPath.set_problem(m_bug.get_sphere().getCenter(), randomDestination, m_bug.get_sphere(), enlargedObstacles);
		shortestPath.find_the_shortest_path();
	}
	
	DECIMAL timeForPathPoint = m_bug.get_time();
	rg_Point3D lastPoint = m_bug.get_sphere().getCenter();

	for (int i=0; i<shortestPath.points_on_the_shortest_path().size(); i++)
	{	
		const rg_Point3D& currPt = shortestPath.points_on_the_shortest_path().at(i);
		float distance = lastPoint.distance(currPt);
		if (distance > 1)
		{
			timeForPathPoint += distance/bugSpeed;
			m_bugWayPoints.push_back(make_pair(currPt, timeForPathPoint));
			lastPoint = currPt;
		}
	}
	//cout << "Target point [" << randomDestination.getX() << " " << randomDestination.getY() << " " << randomDestination.getZ() << "], distance: " <<randomDestination.distance(m_bug.get_sphere().getCenter())<< endl;
}



void DroneSimulator::find_random_bug_location_candidate_using_VVtx()
{
	m_randomBugLocationCandidates.clear();

	list<VVertexCore*> VVertices;
	collect_vertices_for_drawing(VVertices);
	for (list<VVertexCore*>::const_iterator itForVVtx = VVertices.cbegin(); itForVVtx != VVertices.end(); itForVVtx++)
	{
		bool isCurrVtxValid = true;
		list<VCellCore*> boundingCells;
		(*itForVVtx)->findIncidentVCells(boundingCells);
		float distanceToBall = 0;
		for (list<VCellCore*>::const_iterator itForCell = boundingCells.cbegin(); itForCell != boundingCells.cend(); itForCell++)
		{
			BallGeneratorCore* generator = static_cast<BallGeneratorCore*>((*itForCell)->getGenerator());
			if (generator->getUserData() != NULL)
			{
				DynamicBall* corrBall = static_cast<DynamicBall*>(generator->getUserData());
				distanceToBall = corrBall->get_sphere().distance((*itForVVtx)->getPoint());
				if (corrBall->get_type() != LINEAR_BALL)
				{
					isCurrVtxValid = false;
					break;
				}
			}
		}

		if (isCurrVtxValid && distanceToBall > m_bug.get_sphere().getRadius()+ shortestPathMargin)
		{
			rg_Point3D location = (*itForVVtx)->getPoint();
			if(location.getX() > -m_fenceLength/2 && location.getX() < m_fenceLength / 2
				&& location.getY() > -m_fenceWidth / 2 && location.getY() < m_fenceWidth / 2
				&& location.getZ() > 0 / 2 && location.getZ() < m_fenceHeight)
					m_randomBugLocationCandidates.push_back(location);
		}
	}
}



void DroneSimulator::make_random_bug_location_candidates()
{
	default_random_engine engine;
	engine.seed(time(0));
	uniform_real_distribution<float> fRand{ 0, 1 };
	while (m_randomBugLocationCandidates.size() < numRandomPoints)
	{
		float xRatio = fRand(engine);
		float x = xRatio * m_fenceLength - m_fenceLength / 2;
		float yRatio = fRand(engine);
		float y = yRatio * m_fenceWidth - m_fenceWidth / 2;
		float zRatio = fRand(engine);
		float z = zRatio * m_fenceHeight;
		rg_Point3D randomPt(x, y, z);

		if (is_included_in_balls(randomPt, 2 * (m_r + m_theta) + shortestPathMargin) == false)
		{
			m_randomBugLocationCandidates.push_back(randomPt);
		}
	}

	uniform_int_distribution<unsigned int> iRand{ 0, m_randomBugLocationCandidates.size() - 1 };
	m_bug.set_sphere_center(m_randomBugLocationCandidates.at(iRand(engine)));
	m_bug.set_time(m_dynamicVD.get_current_time());
}



DynamicBall* DroneSimulator::find_closest_obstacle_from_hunter()
{
	VCellCore* closestCell = m_dynamicVD.findClosestVCell(m_hunter.get_sphere().getCenter());
	DynamicBall* corrBall = static_cast<DynamicBall*>(static_cast<BallGeneratorCore*>(closestCell->getGenerator())->getUserData());
	return corrBall;
}



Sphere DroneSimulator::find_tangent_sphere_between_hunter_and_neighbors()
{
	VCellCore* closestCell = m_dynamicVD.findClosestVCell(m_hunter.get_sphere().getCenter());
	
	VVertexCore* closestVVtxFromHunter = nullptr;
	list<VVertexCore*> boundingVertices;
	float closestDistance = FLT_MAX;

	closestCell->findBoundingVVertices(boundingVertices);
	
	for (list<VVertexCore*>::iterator itForVtx = boundingVertices.begin(); itForVtx != boundingVertices.end(); itForVtx++)
	{
		float distance = (*itForVtx)->getPoint().distance(m_hunter.get_sphere().getCenter());
		if (distance < closestDistance)
		{
			closestDistance = distance;
			closestVVtxFromHunter = *itForVtx;
		}
	}

	list<VCellCore*> incidentCells;
	closestVVtxFromHunter->findIncidentVCells(incidentCells);

	int counter = 0;
	array<Sphere, 4> tangentBalls;
	for (list<VCellCore*>::iterator itForCell = incidentCells.begin(); itForCell != incidentCells.end(); itForCell++)
	{
		if (*itForCell != closestCell)
		{
			tangentBalls.at(counter) = Sphere((*itForCell)->getGenerator()->getPoint(), m_r + m_theta/* + m_pathComputationInterval * m_maxV*/);
			counter++;
		}
	}
	tangentBalls.at(3) = m_hunter.get_sphere();

	Sphere tangentSpheres[2];

	int numOfTangentSpheres = computeSphereTangentTo4SpheresOutside(tangentBalls.at(0),
		tangentBalls.at(1),
		tangentBalls.at(2),
		tangentBalls.at(3),
		tangentSpheres);

	return tangentSpheres[0];
}



void DroneSimulator::color_hunter_neighbors(const Color3f& colorForNeighbor)
{
	m_obstacleColorMap.clear();
	VCellCore* closestCell = m_dynamicVD.findClosestVCell(m_hunter.get_sphere().getCenter());
	DynamicBall* corrBall = static_cast<DynamicBall*>(static_cast<BallGeneratorCore*>(closestCell->getGenerator())->getUserData());
	m_obstacleColorMap[corrBall] = colorForNeighbor;

	list<VCellCore*> adjacentCells;
	closestCell->findAdjacentVCells(adjacentCells);
	for (list<VCellCore*>::iterator itForCell = adjacentCells.begin(); itForCell != adjacentCells.end(); itForCell++)
	{
		corrBall = static_cast<DynamicBall*>(static_cast<BallGeneratorCore*>((*itForCell)->getGenerator())->getUserData());
		m_obstacleColorMap[corrBall] = colorForNeighbor;
	}
}



void DroneSimulator::update_bug(const DECIMAL& time)
{
	pair<rg_Point3D, DECIMAL> wayPoint = m_bugWayPoints.front();
	while (time >= wayPoint.second)
	{
		//cout << "Next bug wp at " << wayPoint.second << " with d: " << wayPoint.first.distance(m_bug.get_sphere().getCenter()) << endl;
		m_bug.set_sphere_center(wayPoint.first);
		m_bug.set_time(wayPoint.second);
		m_bugWayPoints.pop_front();

		if (m_bugWayPoints.empty())
			generate_bug_way_points(m_bugSpeed, wayPoint.second);

		pair<rg_Point3D, DECIMAL> newWayPoint = m_bugWayPoints.front();
		m_bug.set_velocity_vector((newWayPoint.first - wayPoint.first) / (newWayPoint.second - wayPoint.second));
		wayPoint = newWayPoint;
	}
	//cout << "Move to time: " << time << endl;
	m_bug.move_to_time(time); 
}



bool DroneSimulator::is_included_in_balls(const rg_Point3D& point, const float& threshold)
{
	VCellCore* closestVCell = m_dynamicVD.findClosestVCell(point);
	float distanceToClosestBall = closestVCell->getGenerator()->getPoint().distance(point);
	return distanceToClosestBall < threshold;
}



void DroneSimulator::make_new_bug()
{
	m_hunterWayPoints.clear();
	m_bugWayPoints.clear();

	switch (m_bugGenerationMode)
	{
	case ON_FENCE:
		m_bug.set_sphere_center(rg_Point3D(m_fenceLength / 2, m_fenceWidth / 2, m_fenceHeight));
		break;
	case RANDOM:
	default:
		make_random_bug_location_candidates();
		break;
	}

	generate_bug_way_points(m_bugSpeed, m_bug.get_time());
}

void DroneSimulator::update_hunter_trajectory()
{
	if (!m_hunterTrajectory.empty())
	{
		rg_Point3D& lastPoint = m_hunterTrajectory.back();
		if (m_hunter.get_sphere().getCenter().distance(lastPoint) > 1)
			m_hunterTrajectory.push_back(m_hunter.get_sphere().getCenter());
	}
	else
	{
		m_hunterTrajectory.push_back(m_hunter.get_sphere().getCenter());
	}
}



void DroneSimulator::set_hunter_target(const rg_Point3D& target)
{
	rg_Point3D hunterLocation = m_hunter.get_sphere().getCenter();
	rg_Point3D velocity = (target - hunterLocation).getUnitVector();
	m_hunter.move_sphere_center(velocity*1);
}

