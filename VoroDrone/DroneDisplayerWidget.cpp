#include "DroneDisplayerWidget.h"
#include "constForDroneDisplayer.h"
#include "ShorestPathAvoidingSphericalObstacles.h"
#include <set>

DroneDisplayerWidget::DroneDisplayerWidget(QWidget *parent)
	: VDRCOpenGLWidget(parent)
{
	m_pSimulator = nullptr;
	m_bShowDVD = false;
	m_bShowNeighbors = false;
	m_bShowHunterTrajectory = false;
}



DroneDisplayerWidget::~DroneDisplayerWidget()
{
}



void DroneDisplayerWidget::draw_objects(const Color3f& hunterColor, const Color3f& bugColor, const Color3f& obstacleColor)
{
	if (m_pSimulator != nullptr)
	{
		if (m_pSimulator->get_hunter().get_ID() != FAKE_ID)
		{
			switch (m_hunterVisualizationOption)
			{
			case H_POINT:
				draw_point(m_pSimulator->get_hunter().get_sphere().getCenter(), 10.0, hunterColor);
				//draw_point(m_pSimulator->get_hunter2().get_sphere().getCenter(), 10.0, hunterColor);
				break;
			case H_BALL:
				draw_sphere(m_pSimulator->get_hunter().get_sphere().getCenter(), m_pSimulator->get_hunter().get_sphere().getRadius(), hunterColor);
				//draw_sphere(m_pSimulator->get_hunter2().get_sphere().getCenter(), m_pSimulator->get_hunter2().get_sphere().getRadius(), hunterColor);
				break;
			case H_HIDE:
			default:
				break;
			}
		}

		if (m_pSimulator->get_bug().get_ID() != FAKE_ID)
		{
			switch (m_bugVisualizationOption)
			{
			case B_POINT:
				draw_point(m_pSimulator->get_bug().get_sphere().getCenter(), 10.0, bugColor);
				break;
			case B_BALL:
				draw_sphere(m_pSimulator->get_bug().get_sphere().getCenter(), m_pSimulator->get_bug().get_sphere().getRadius(), bugColor);
				//draw_velocity_cone(&m_pSimulator->get_bug(), bugColor);
				break;
			case B_HIDE:
			default:
				break;
			}
		}

		if (!m_pSimulator->get_obstacles().empty())
		{
			if (m_bShowNeighbors)
				m_pSimulator->color_hunter_neighbors(YELLOW);

			float enlargedValue = m_pSimulator->get_r()+m_pSimulator->get_theta()+m_pSimulator->get_maxV()*m_pSimulator->get_path_computation_interval();

			const map<const DynamicBall*, Color3f>& obstacleColorMap = m_pSimulator->get_obstacle_color_map();
			for (list<DynamicBall>::const_iterator itForObstacle = m_pSimulator->get_obstacles().cbegin(); itForObstacle != m_pSimulator->get_obstacles().cend(); itForObstacle++)
			{
				rg_Point3D obstacleCenter = (*itForObstacle).calculate_center_at_time(m_pSimulator->get_dynamic_VD().get_current_time());
				Color3f colorForBall = obstacleColor;
				if (obstacleColorMap.count(&*itForObstacle) > 0)
				{
					colorForBall = obstacleColorMap.at(&*itForObstacle);
				}
				
				switch (m_obstacleVisualizationOption)
				{
				case O_POINT:
					draw_point(obstacleCenter, 10.0, colorForBall);
					break;
				case O_BALL:
					draw_sphere(obstacleCenter, (*itForObstacle).get_sphere().getRadius()-enlargedValue, colorForBall);
					//draw_velocity_cone(&(*itForObstacle), obstacleColor);
					break;
				case O_ENLARGED:
					draw_sphere(obstacleCenter, (*itForObstacle).get_sphere().getRadius(), colorForBall);
					//draw_velocity_cone(&(*itForObstacle), obstacleColor);
					break;
				case O_HIDE:
				default:
					break;
				}
			}
		}

		draw_fence(m_pSimulator->get_fence_length(), m_pSimulator->get_fence_width(), m_pSimulator->get_fence_height());
	}
}



void DroneDisplayerWidget::draw_path(const int& width, const Color3f& color)
{
	if (m_pSimulator != nullptr)
	{
		const list<pair<rg_Point3D, DECIMAL>>& path = m_pSimulator->get_hunter_way_points();
		if (path.size() > 2)
		{
			list<pair<rg_Point3D, DECIMAL>>::const_iterator itForPoint = path.cbegin();
			rg_Point3D lastPoint = (*itForPoint).first;
			itForPoint++;
			while (itForPoint != path.cend())
			{
				const rg_Point3D& currPoint = (*itForPoint).first;
				draw_line(lastPoint, currPoint, width, color);
				lastPoint = currPoint;
				itForPoint++;
			}
		}	
	}
}




void DroneDisplayerWidget::draw_velocity_cone(const DynamicBall* ball, const Color3f& color)
{
	const Sphere& sphere = ball->get_sphere();
	const rg_Point3D& velocity = ball->get_velocity_vector();
	draw_octagonal_cone(sphere.getCenter(), velocity.getUnitVector()*5 +sphere.getCenter(), 0.2*sphere.getRadius(), color);
}



void DroneDisplayerWidget::draw_fence(const float& fenceLength, const float& fenceWidth, const float& fenceHeight)
{
	array<rg_Point3D, 8> fenceCorners;
	fenceCorners.at(0).setPoint(fenceLength / 2, fenceWidth / 2, 0);
	fenceCorners.at(1).setPoint(fenceLength / 2, -fenceWidth / 2, 0);
	fenceCorners.at(2).setPoint(-fenceLength / 2, -fenceWidth / 2, 0);
	fenceCorners.at(3).setPoint(-fenceLength / 2, fenceWidth / 2, 0);

	fenceCorners.at(4).setPoint(fenceLength / 2, fenceWidth / 2, fenceHeight);
	fenceCorners.at(5).setPoint(fenceLength / 2, -fenceWidth / 2, fenceHeight);
	fenceCorners.at(6).setPoint(-fenceLength / 2, -fenceWidth / 2, fenceHeight);
	fenceCorners.at(7).setPoint(-fenceLength / 2, fenceWidth / 2, fenceHeight);

	draw_line(fenceCorners.at(0), fenceCorners.at(1), 1.0, BLACK);
	draw_line(fenceCorners.at(1), fenceCorners.at(2), 1.0, BLACK);
	draw_line(fenceCorners.at(2), fenceCorners.at(3), 1.0, BLACK);
	draw_line(fenceCorners.at(3), fenceCorners.at(0), 1.0, BLACK);

	draw_line(fenceCorners.at(4), fenceCorners.at(5), 1.0, BLACK);
	draw_line(fenceCorners.at(5), fenceCorners.at(6), 1.0, BLACK);
	draw_line(fenceCorners.at(6), fenceCorners.at(7), 1.0, BLACK);
	draw_line(fenceCorners.at(7), fenceCorners.at(4), 1.0, BLACK);

	draw_line(fenceCorners.at(0), fenceCorners.at(4), 1.0, BLACK);
	draw_line(fenceCorners.at(1), fenceCorners.at(5), 1.0, BLACK);
	draw_line(fenceCorners.at(2), fenceCorners.at(6), 1.0, BLACK);
	draw_line(fenceCorners.at(3), fenceCorners.at(7), 1.0, BLACK);
}



void DroneDisplayerWidget::draw_line_from_hunter_to_closest_obstacle()
{
	DynamicBall* closestObstacle = m_pSimulator->find_closest_obstacle_from_hunter();
	draw_line(m_pSimulator->get_hunter().get_sphere().getCenter(), closestObstacle->calculate_center_at_time(m_pSimulator->get_dynamic_VD().get_current_time()), 5.0, VIOLET);
}



void DroneDisplayerWidget::draw_tangent_sphere_with_hunter_and_neighbors()
{
	Sphere neighborSphere = m_pSimulator->find_tangent_sphere_between_hunter_and_neighbors();
	draw_sphere(neighborSphere.getCenter(), neighborSphere.getRadius(), ORANGE);
}



void DroneDisplayerWidget::draw_hunter_trajectory()
{
	rg_Point3D lastPoint = m_pSimulator->get_hunter_trajectory().front();
	for (auto& point : m_pSimulator->get_hunter_trajectory())
	{
		draw_line(lastPoint, point, 5.0, VIOLET);
		lastPoint = point;
	}
}



void DroneDisplayerWidget::draw()
{
	draw_objects(HUNTER_COLOR, BUG_COLOR, OBSTACLE_COLOR);

	if (m_pSimulator != nullptr && m_bShowDVD)
	{
		list<VEdgeCore*> VEdgesOfDVD;
		m_pSimulator->collect_edges_for_drawing(VEdgesOfDVD);
		draw_DVD_edges(VEdgesOfDVD, VEDGE_THICKNESS, BLACK);

		/*set<VVertexCore*> vertices;
		for (auto& edge : VEdgesOfDVD)
		{
			vertices.insert(edge->getStartVVertex());
			vertices.insert(edge->getEndVVertex());
		}

		for (auto& vertex : vertices)
		{
			if (m_pSimulator->get_infos().vertexColorMap.count(vertex) > 0)
			{
				draw_point(vertex->getPoint(), 10, m_pSimulator->get_infos().vertexColorMap.at(vertex), 5.0, vertex->getID()*NUM_PICKING_CLASS + CLASS_VVERTEX);
				/ *if (m_pSimulator->get_infos().vertexColorMap.at(vertex).getR() == RED.getR())
				{
					localOrigin = vertex->getPoint();
					m_eyeDistance = 10;
				}* /
					
			}
			else
			{
				draw_point(vertex->getPoint(), 10, BLACK, 1.0, vertex->getID()*NUM_PICKING_CLASS + CLASS_VVERTEX);
			}
		}
			
		enlist_VVertices(vertices);*/

		/*list<VEdgeCore*> edgesOfVD;
		list<VEdgeCore*> allEdges;
		m_pVD->getAllVEdges(allEdges);

		for (list<VEdgeCore*>::iterator itForEdge = allEdges.begin(); itForEdge != allEdges.end(); itForEdge++)
		{
			VEdgeCore* currEdge = *itForEdge;

			if (currEdge->isInfinite() == false && currEdge->will_be_deleted() == false)
			{
				edgesOfVD.push_back(currEdge);
			}
		}
		draw_DVD_edges(edgesOfVD, VEDGE_THICKNESS, RED);*/
	}

	if (m_bShowHunterTrajectory)
		draw_hunter_trajectory();

	draw_path(5.0, GREEN);
}



void DroneDisplayerWidget::draw_DVD_edges(const list<VEdgeCore*>& edges, const int& width, const Color3f& color, const float& A /*= 1.0*/)
{
	glDisable(GL_LIGHTING);
	for (auto& edge : edges)
	{
		/*list<VCellCore*> incCells;
		edge->findIncidentVCellsInRadialCCW(incCells);
		int counter = 0;
		for (auto& cell : incCells)
		{
		DynamicBall* ball = static_cast<DynamicBall*>(static_cast<BallGeneratorCore*>(cell->getGenerator())->getUserData());
		if (ball->get_type() == ORBITAL_BALL)
		counter++;
		}
		if (counter>=2)
		{
		rg_Point3D pt1 = edge->getStartVVertex()->getPoint();
		rg_Point3D pt2 = edge->getEndVVertex()->getPoint();
		draw_line(pt1, pt2, thickness, color, A);
		}*/

		rg_Point3D pt1 = edge->getStartVVertex()->getPoint();
		rg_Point3D pt2 = edge->getEndVVertex()->getPoint();
		//draw_line(pt1, pt2, width, color, A);

		if (m_pSimulator->get_infos().edgeColorMap.count(edge) > 0)
		{
			draw_line(pt1, pt2, 5*width, m_pSimulator->get_infos().edgeColorMap.at(edge), A);
		}
		else
		{
			draw_line(pt1, pt2, width, color, A);
		}

		/*if (pOrbitalSimulator->get_infos().edgeColorMap.count(edge) > 0)
		{
			Color3f& edgeBallColor = pOrbitalSimulator->get_infos().edgeColorMap.at(edge);
			draw_point(pt1, POINT_SIZE, edgeBallColor);
			draw_point(pt2, POINT_SIZE, edgeBallColor);
		}*/
	}
	glEnable(GL_LIGHTING);
}
