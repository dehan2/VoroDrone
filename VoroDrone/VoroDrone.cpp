#include "VoroDrone.h"
#include <random>
#include <ctime>

VoroDrone::VoroDrone(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	m_playSpeed = 1.0;
	
	m_simulationTimer = new QTimer(this);
	connect(m_simulationTimer, SIGNAL(timeout()), this, SLOT(increase_simulation_time()));
	
	m_pathFindingTimer = new QTimer(this);
	connect(m_pathFindingTimer, SIGNAL(timeout()), this, SLOT(generate_path_from_hunter_to_bug()));
	
	//m_droneTimer = new QTimer(this);
	//connect(m_droneTimer, SIGNAL(timeout()), this, SLOT(update_drone_information()));

	connect(this, SIGNAL(current_time_updated(double)), this, SLOT(go_to_target_time(double)));

	m_droneCommunicator = nullptr;

	ui.comboBox_bug_generation_mode->insertItem(0, "On fence");
	ui.comboBox_bug_generation_mode->insertItem(1, "Random");
	ui.comboBox_bug_generation_mode->setCurrentIndex(0);

	xyView = new DroneDisplayerWidget();
	xzView = new DroneDisplayerWidget();
	yzView = new DroneDisplayerWidget();
	
	xyView->m_bDisableRotation = true;
	xzView->m_bDisableRotation = true;
	yzView->m_bDisableRotation = true;

	xzView->localZ = rg_Point3D(0, 1, 0);
	xzView->localY = rg_Point3D(0, 0, 1);
	yzView->localZ = rg_Point3D(1, 0, 0);
	yzView->localY = rg_Point3D(0, 0, 1);

	showMaximized();
}



string VoroDrone::translate_to_window_path(const QString& QfilePath) const
{
	string filePath = QfilePath.toStdString();

	size_t i = filePath.find('/');
	while (i != string::npos)
	{
		string part1 = filePath.substr(0, i);
		string part2 = filePath.substr(i + 1);
		filePath = part1 + R"(\)" + part2; // Use "\\\\" instead of R"(\\)" if your compiler doesn't support C++11's raw string literals
		i = filePath.find('/', i + 1);
	}
	return filePath;
}



void VoroDrone::update_current_time_widgets()
{
	float currTime = m_simulator.get_dynamic_VD().get_current_time();
	float timeWindow = m_simulator.get_dynamic_VD().get_time_window();
	int newTimePos = currTime / timeWindow * ui.horizontalSlider_time->maximum();
	ui.horizontalSlider_time->setSliderPosition(newTimePos);

	QString currTimeString = QString::number(currTime);
	ui.lineEdit_time->setText(currTimeString);
}



void VoroDrone::synchronize_show_option()
{
	xyView->m_pSimulator = ui.droneDisplayer->m_pSimulator;
	xyView->m_bShowDVD = ui.droneDisplayer->m_bShowDVD;
	xyView->m_hunterVisualizationOption = ui.droneDisplayer->m_hunterVisualizationOption;
	xyView->m_bugVisualizationOption = ui.droneDisplayer->m_bugVisualizationOption;
	xyView->m_obstacleVisualizationOption = ui.droneDisplayer->m_obstacleVisualizationOption;
	xyView->m_bShowNeighbors = ui.droneDisplayer->m_bShowNeighbors;
	xyView->m_bShowHunterTrajectory = ui.droneDisplayer->m_bShowHunterTrajectory;
	xyView->localOrigin = ui.droneDisplayer->localOrigin;

	xzView->m_pSimulator = ui.droneDisplayer->m_pSimulator;
	xzView->m_bShowDVD = ui.droneDisplayer->m_bShowDVD;
	xzView->m_hunterVisualizationOption = ui.droneDisplayer->m_hunterVisualizationOption;
	xzView->m_bugVisualizationOption = ui.droneDisplayer->m_bugVisualizationOption;
	xzView->m_obstacleVisualizationOption = ui.droneDisplayer->m_obstacleVisualizationOption;
	xzView->m_bShowNeighbors = ui.droneDisplayer->m_bShowNeighbors;
	xzView->m_bShowHunterTrajectory = ui.droneDisplayer->m_bShowHunterTrajectory;
	xzView->localOrigin = ui.droneDisplayer->localOrigin;

	yzView->m_pSimulator = ui.droneDisplayer->m_pSimulator;
	yzView->m_bShowDVD = ui.droneDisplayer->m_bShowDVD;
	yzView->m_hunterVisualizationOption = ui.droneDisplayer->m_hunterVisualizationOption;
	yzView->m_bugVisualizationOption = ui.droneDisplayer->m_bugVisualizationOption;
	yzView->m_obstacleVisualizationOption = ui.droneDisplayer->m_obstacleVisualizationOption;
	yzView->m_bShowNeighbors = ui.droneDisplayer->m_bShowNeighbors;
	yzView->m_bShowHunterTrajectory = ui.droneDisplayer->m_bShowHunterTrajectory;
	yzView->localOrigin = ui.droneDisplayer->localOrigin;
}



void VoroDrone::update_displayers()
{
	ui.droneDisplayer->update();
	xyView->update();
	xzView->update();
	yzView->update();
}



void VoroDrone::update_SVD()
{
	m_SVD.clear();

	list<tuple<Sphere, void*, int>> dynamicBalls;
	list<BallGeneratorCore*> generators;
	m_simulator.get_dynamic_VD().getAllGenerators(generators);
	int counter = 0;
	for (auto& generator : generators)
	{
		if (generator->getInputID() >= 2)
		{
			DynamicBall* dynamicBall = static_cast<DynamicBall*>(generator->getUserData());
			dynamicBalls.push_back(make_tuple(generator->getBall(), dynamicBall, dynamicBall->get_ID()));
		}
	}
	m_SVD.compute(dynamicBalls, TOPOLOGY_ORIENTED_INCREMENTAL);
}



void VoroDrone::generate_drones_and_prepare_simulation()
{
	m_simulator.set_n(ui.lineEdit_n->text().toInt());
	m_simulator.set_r(ui.lineEdit_r->text().toFloat());
	m_simulator.set_theta(ui.lineEdit_theta->text().toFloat());
	m_simulator.set_fence_length(ui.lineEdit_fence_length->text().toFloat());
	m_simulator.set_fence_width(ui.lineEdit_fence_width->text().toFloat());
	m_simulator.set_fence_height(ui.lineEdit_fence_height->text().toFloat());
	m_simulator.set_path_compuation_interval(ui.lineEdit_path_computation_interval->text().toFloat());

	float timeWindow = QInputDialog::getDouble(0, tr(""), tr("Simulation time window: "), 1000.0);

	m_simulator.generate_drones();
	m_simulator.prepare_simulation(timeWindow);
	generate_bug();

	//m_pathFindingTimer->setInterval((int)(1000 * m_simulator.get_path_computation_interval()));
	ui.horizontalSlider_time->setMaximum((int)timeWindow);


	//m_simulator.save_path_information();
	m_simulator.save_drone_informations(string("autoSave.dif"));

	ui.droneDisplayer->m_pSimulator = &m_simulator;
	ui.droneDisplayer->set_local_origin(0, 0, m_simulator.get_fence_height() / 2);
	
	//update_SVD();
	ui.droneDisplayer->m_pVD = &m_SVD;

	show_option_changed();
}



void VoroDrone::show_option_changed()
{
	if (ui.radioButton_hunter_point->isChecked()) { ui.droneDisplayer->m_hunterVisualizationOption = H_POINT; }
	if (ui.radioButton_hunter_ball->isChecked()) { ui.droneDisplayer->m_hunterVisualizationOption = H_BALL; }
	if (ui.radioButton_hunter_hide->isChecked()) { ui.droneDisplayer->m_hunterVisualizationOption = H_HIDE; }
	ui.droneDisplayer->m_bShowHunterTrajectory = ui.checkBox_hunter_trajectory->isChecked();

	if (ui.radioButton_bug_point->isChecked()) { ui.droneDisplayer->m_bugVisualizationOption = B_POINT; }
	if (ui.radioButton_bug_ball->isChecked()) { ui.droneDisplayer->m_bugVisualizationOption = B_BALL; }
	if (ui.radioButton_bug_hide->isChecked()) { ui.droneDisplayer->m_bugVisualizationOption = B_HIDE; }

	if (ui.radioButton_obstacle_with_safe_distance->isChecked()) { ui.droneDisplayer->m_obstacleVisualizationOption = O_ENLARGED; }
	if (ui.radioButton_obstacle_point->isChecked()) { ui.droneDisplayer->m_obstacleVisualizationOption = O_POINT; }
	if (ui.radioButton_obstacle_ball->isChecked()) { ui.droneDisplayer->m_obstacleVisualizationOption = O_BALL; }
	if (ui.radioButton_obstacle_hide->isChecked()) { ui.droneDisplayer->m_obstacleVisualizationOption = O_HIDE; }

	ui.droneDisplayer->m_bShowDVD = ui.checkBox_show_DVD->isChecked();
	ui.droneDisplayer->m_bShowNeighbors = ui.checkBox_neighbors->isChecked();
	if (ui.droneDisplayer->m_bShowNeighbors == false)
	{
		m_simulator.clear_color_map();
	}
	
	if (ui.checkBox_show_DVD->isChecked() || ui.droneDisplayer->m_bShowNeighbors)
	{
		m_simulator.set_update_VVtx_coordinate_option(true);
	}
	else
	{
		m_simulator.set_update_VVtx_coordinate_option(false);
	}

	synchronize_show_option();

	update_displayers();
}



void VoroDrone::play_simulation()
{
	if (m_simulationTimer->isActive() == false)
	{
		m_simulationTimer->start(100);
	}
	else
	{
		m_simulationTimer->stop();
	}
}



void VoroDrone::increase_simulation_time()
{
	float currTime = m_simulator.get_dynamic_VD().get_current_time();
	float timeWindow = m_simulator.get_dynamic_VD().get_time_window();

	if (currTime < timeWindow)
	{
		m_simulator.increase_time(m_playSpeed*0.1);
		update_current_time_widgets();

		//update_VD();

		//ui.droneDisplayer->update();
		update_displayers();
	}
	else
	{
		m_simulationTimer->stop();
	}
}



void VoroDrone::reset_to_initial_state()
{
	m_simulator.go_to_time(0.0);
	//ui.droneDisplayer->update();
	update_displayers();
}



void VoroDrone::go_to_target_time(double targetTime)
{
	float currTime = m_simulator.get_dynamic_VD().get_current_time();
	float timeWindow = m_simulator.get_dynamic_VD().get_time_window();

	if (currTime < timeWindow)
	{
		m_simulator.go_to_time(targetTime);

		//print_message();
		//update_proximity_informations();
		update_current_time_widgets();

		//ui.droneDisplayer->update();
		update_displayers();
	}
	else
	{
		m_simulationTimer->stop();
	}
}



void VoroDrone::play_speed_changed(double playSpeed)
{
	m_playSpeed = playSpeed;
}



void VoroDrone::current_time_changed_by_edit()
{
	float changedTime = ui.lineEdit_time->text().toDouble();
	float timeWindow = m_simulator.get_dynamic_VD().get_time_window();
	//int newTimePos = changedTime / timeWindow * ui.horizontalSlider_time->maximum();
	int newTimePos = changedTime;
	ui.horizontalSlider_time->setSliderPosition(newTimePos);

	m_simulator.go_to_time(changedTime);
	//ui.droneDisplayer->update();
	update_displayers();
}



void VoroDrone::current_time_changed_by_slider()
{
	float timeWindow = m_simulator.get_dynamic_VD().get_time_window();
	int timeSliderPos = ui.horizontalSlider_time->sliderPosition();

	float changedTime = timeSliderPos;
	//float changedTime = timeSliderPos / ui.horizontalSlider_time->maximum() * timeWindow;
	QString currTimeString = QString::number(changedTime);
	ui.lineEdit_time->setText(currTimeString);

	m_simulator.go_to_time(changedTime);
	//ui.droneDisplayer->update();
	update_displayers();
}



void VoroDrone::save_drone_informations()
{
	QString QfilePath = QFileDialog::getSaveFileName(this, tr("Save Drone Information"), NULL, tr("Drone information file (*.dif)"));
	QFileInfo fileInfo(QfilePath);

	string filePath = translate_to_window_path(QfilePath);
	m_simulator.save_drone_informations(filePath);
}



void VoroDrone::load_drone_informations()
{
	QString QfilePath = QFileDialog::getOpenFileName(this, tr("Open Drone Information"), NULL, tr("Drone information file(*.dif)"));
	QFileInfo fileInfo(QfilePath);

	string filePath = translate_to_window_path(QfilePath);
	
	float timeWindow = QInputDialog::getDouble(0, tr(""), tr("Simulation time window: "), 1000.0);
	
	m_simulator.load_drone_informations(filePath);
	m_simulator.prepare_simulation(timeWindow);
	generate_bug();

	ui.horizontalSlider_time->setMaximum((int)timeWindow);

	update_SVD();
	ui.droneDisplayer->m_pVD = &m_SVD;

	ui.droneDisplayer->m_pSimulator = &m_simulator;
	ui.droneDisplayer->set_local_origin(0, 0, m_simulator.get_fence_height() / 2);
	show_option_changed();
}



void VoroDrone::connect_to_hunter()
{
	QString address = ui.lineEdit_drone_address->text();
	m_droneCommunicator = new DroneCommunicatorThread(this, &m_mutex);
	m_droneCommunicator->initialize(address.toStdString());
	connect(m_droneCommunicator, SIGNAL(hunter_location_updated()), this, SLOT(update_drone_information()));
	m_droneCommunicator->start();

	QString address2 = ui.lineEdit_drone_address2->text();
	m_droneCommunicator2 = new DroneCommunicatorThread(this, &m_mutex2);
	m_droneCommunicator2->initialize(address2.toStdString());
	m_droneCommunicator2->start();
}



void VoroDrone::take_off_hunter()
{
	m_droneCommunicator->bTakeOff = true;
	m_droneCommunicator2->bTakeOff = true;
}



void VoroDrone::hunt_bug()
{
	/*if (m_pathFindingTimer->isActive() == false)
	{
		m_pathFindingTimer->start(500);
	}
	else
	{
		m_pathFindingTimer->stop();
	}*/

	rg_Point3D hunterLocation1 = m_simulator.get_hunter().get_sphere_center();
	rg_Point3D hunterLocation2 = m_simulator.get_hunter2().get_sphere_center();

	default_random_engine engine;
	engine.seed(time(0));

	uniform_int_distribution<int> dist{ -1, 1 };
	int deltaX = dist(engine);
	int deltaY = dist(engine);

	m_droneCommunicator->targetX = hunterLocation1.getX() + deltaX;
	m_droneCommunicator2->targetX = hunterLocation2.getX() + deltaX;

	m_droneCommunicator->targetY = hunterLocation1.getY() + deltaY;
	m_droneCommunicator2->targetY = hunterLocation2.getY() + deltaY;

	m_droneCommunicator->bGoTo = true;
	m_droneCommunicator2->bGoTo = true;

	cout << "Drone will move to X: " << deltaX << ", Y: " << deltaY << endl;
	
	/*m_simulator.find_shortest_path_from_hunter_to_bug();
	const list<pair<rg_Point3D, double>>& wayPoints = m_simulator.get_hunter_way_points();
	const rg_Point3D& targetPoint = wayPoints.back().first;

	m_droneCommunicator->targetX = targetPoint.getX();
	m_droneCommunicator->targetY = targetPoint.getY();
	m_droneCommunicator->targetZ = targetPoint.getZ();
	m_droneCommunicator->bGoTo = true;*/
}



void VoroDrone::land_hunter()
{
	m_droneCommunicator->bLand = true;
	m_droneCommunicator2->bLand = true;
}



void VoroDrone::update_drone_information()
{
	float altitude = m_droneCommunicator->droneAlt;
	float longtitude = m_droneCommunicator->droneLon;
	float latitude = m_droneCommunicator->droneLat;

	ui.label_hunter_alt->setText(QString::number(altitude));
	ui.label_hunter_lat->setText(QString::number(latitude));
	ui.label_hunter_lon->setText(QString::number(longtitude));

	array<float, 3> coord = m_droneCommunicator->calculate_drone_coord();
	m_simulator.set_hunter_location(coord.at(0), coord.at(1), coord.at(2));
	array<float, 3> coord2 = m_droneCommunicator2->calculate_drone_coord();
	m_simulator.set_hunter_location(coord2.at(0), coord2.at(1), coord2.at(2));
	//m_simulator.update_hunter_trajectory();
	//ui.droneDisplayer->update();

	float altitude2 = m_droneCommunicator2->droneAlt;
	float longtitude2 = m_droneCommunicator2->droneLon;
	float latitude2 = m_droneCommunicator2->droneLat;

	ui.label_hunter_alt2->setText(QString::number(altitude2));
	ui.label_hunter_lat2->setText(QString::number(latitude2));
	ui.label_hunter_lon2->setText(QString::number(longtitude2));

	

	update_displayers();
}



void VoroDrone::generate_path_from_hunter_to_bug()
{
	m_simulator.set_hunter_speed(ui.lineEdit_hunter_speed->text().toFloat());

	rg_Point3D hunterLocation = m_simulator.get_hunter().get_sphere().getCenter();
	rg_Point3D bugLocation = m_simulator.get_bug().get_sphere().getCenter();

	if (bugLocation.distance(hunterLocation) < 3)
	{
		m_pathFindingTimer->stop();
		m_simulationTimer->stop();

		QMessageBox msgBox;
		msgBox.setWindowTitle("H-Mapper");
		msgBox.setText("Bug was hunted");
		msgBox.exec();
		generate_bug();
	}
	else
	{
		if (m_pathComputationCounter >= 2 * m_simulator.get_path_computation_interval())	//0.5 sec timer
		{
			m_simulator.find_shortest_path_from_hunter_to_bug();
			m_pathComputationCounter = 1;
		}
		
		list<pair<rg_Point3D, DECIMAL>>& wayPoints = m_simulator.get_hunter_way_points();
		
		//Simulation
		float targetTime = m_simulator.get_hunter().get_time();
		if (m_droneCommunicator != nullptr)
		{
			targetTime += 3;
		}
		else
		{
			targetTime += 0.45;
		}
		
		pair<rg_Point3D, DECIMAL>* targetWP = nullptr;
		for (auto& wp : wayPoints)
		{
			if (wp.second > targetTime)
			{
				targetWP = &wp;
				break;
			}
		}
		if (targetWP == nullptr)
			targetWP = &wayPoints.back();
		
		rg_Point3D target = targetWP->first;
		if (m_droneCommunicator != nullptr)
		{
			m_droneCommunicator->targetX = target.getX();
			m_droneCommunicator->targetY = target.getY();
			m_droneCommunicator->targetZ = target.getZ();
			m_droneCommunicator->bGoTo = true;
		}
		else
		{
			m_simulator.set_hunter_location(target.getX(), target.getY(), target.getZ());
		}
		m_simulator.set_hunter_time(targetWP->second);

		m_pathComputationCounter++;
	}
	
	//ui.droneDisplayer->update();
	update_displayers();
}



void VoroDrone::generate_bug()
{
	m_simulator.set_bug_speed(ui.lineEdit_bug_speed->text().toFloat());

	int bugGenerationModeIndex = ui.comboBox_bug_generation_mode->currentIndex();
	switch (bugGenerationModeIndex)
	{
	case 0:
		m_simulator.set_bug_generation_mode(ON_FENCE);
		break;
	case 1:
	default:
		m_simulator.set_bug_generation_mode(RANDOM);
		break;
	}

	m_simulator.make_new_bug();
	//ui.droneDisplayer->update();
	update_displayers();
}
