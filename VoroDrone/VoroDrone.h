#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VoroDrone.h"
#include "DroneSimulator.h"
#include "DroneCommunicatorThread.h"
#include <QMutex>

#include "BallSetVoronoiDiagramCore.h"

using namespace BULL;
using namespace CoreTier;

class VoroDrone : public QMainWindow
{
	Q_OBJECT

	DroneSimulator m_simulator;
	float m_playSpeed;
	bool m_bOnPlay;
	QTimer* m_simulationTimer;
	QTimer* m_pathFindingTimer;
	QMutex m_mutex;
	QMutex m_mutex2;

	BallSetVoronoiDiagramCore m_SVD;

	DroneCommunicatorThread* m_droneCommunicator;
	DroneCommunicatorThread* m_droneCommunicator2;
	int m_pathComputationCounter;

	DroneDisplayerWidget* xyView;
	DroneDisplayerWidget* xzView;
	DroneDisplayerWidget* yzView;

public:
	VoroDrone(QWidget *parent = Q_NULLPTR);

private:
	Ui::VoroDroneClass ui;

private:
	string translate_to_window_path(const QString& QfilePath) const;
	void update_current_time_widgets();
	void synchronize_show_option();
	void update_displayers();
	void update_SVD();

signals:
	void current_time_updated(double currentTime);
	void update_current_time_string(QString currTimeString);
	void update_current_time_slider(int currTimePos);

public slots:

void generate_drones_and_prepare_simulation();

void show_option_changed();

void play_simulation();
void increase_simulation_time();
void reset_to_initial_state();
void go_to_target_time(double targetTime);

void play_speed_changed(double playSpeed);
void current_time_changed_by_edit();
void current_time_changed_by_slider();

void save_drone_informations();
void load_drone_informations();

void connect_to_hunter();
void take_off_hunter();
void hunt_bug();
void land_hunter();

void update_drone_information();

void generate_path_from_hunter_to_bug();

void generate_bug();

inline void make_xy_view_widget() { xyView->show(); }
inline void make_xz_view_widget() { xzView->show(); }
inline void make_yz_view_widget() { yzView->show(); }

/*void load_file();
	


	void go_to_next_event_time();
	void go_to_prev_event_time();

	*/
};
