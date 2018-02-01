#pragma once

#include "VDRCOpenGLWidget.h"

#include "DroneSimulator.h"
#include "constForDroneDisplayer.h"
#include "Color3f.h"

#include <list>

using namespace std;
using namespace BULL;
using namespace CoreTier;

class DroneDisplayerWidget : public VDRCOpenGLWidget
{
	Q_OBJECT

public:
	DroneSimulator * m_pSimulator;
	bool m_bShowDVD;

	SHOW_HUNTER		m_hunterVisualizationOption;
	SHOW_BUG				m_bugVisualizationOption;
	SHOW_OBSTACLE		m_obstacleVisualizationOption;

	bool m_bShowNeighbors;
	bool m_bShowHunterTrajectory;

public:
	explicit DroneDisplayerWidget(QWidget *parent = 0);
	virtual ~DroneDisplayerWidget();

	inline const DroneSimulator*		get_simulator() const { return m_pSimulator; }

	inline void set_simulator(DroneSimulator* simulator) { m_pSimulator = simulator; }

	void draw_objects(const Color3f& hunterColor, const Color3f& bugColor, const Color3f& obstacleColor);
	void draw_path(const int& width, const Color3f& color);
	void draw_velocity_cone(const DynamicBall* ball, const Color3f& color);
	void draw_fence(const float& fenceLength, const float& fenceWidth, const float& fenceHeight);
	void draw_line_from_hunter_to_closest_obstacle();
	void draw_tangent_sphere_with_hunter_and_neighbors();
	void draw_hunter_trajectory();

	virtual void draw();
	void draw_DVD_edges(const list<VEdgeCore*>& edges, const int& width, const Color3f& color, const float& A = 1.0);
};
