/********************************************************************************
** Form generated from reading UI file 'VoroDrone.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VORODRONE_H
#define UI_VORODRONE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "DroneDisplayerWidget.h"

QT_BEGIN_NAMESPACE

class Ui_VoroDroneClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    DroneDisplayerWidget *droneDisplayer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_theta;
    QLineEdit *lineEdit_r;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *lineEdit_n;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_10;
    QLineEdit *lineEdit_fence_length;
    QLineEdit *lineEdit_fence_width;
    QLineEdit *lineEdit_fence_height;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QLineEdit *lineEdit_path_computation_interval;
    QPushButton *pushButton_generate_drones;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_save_drones;
    QPushButton *pushButton_load_drones;
    QGroupBox *groupBox_9;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QLineEdit *lineEdit_bug_speed;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *comboBox_bug_generation_mode;
    QPushButton *pushButton_make_new_bug;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_12;
    QLineEdit *lineEdit_hunter_speed;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_11;
    QLineEdit *lineEdit_drone_address;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_9;
    QLabel *label_hunter_lat;
    QLabel *label_hunter_lon;
    QLabel *label_hunter_alt;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_13;
    QLineEdit *lineEdit_drone_address2;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_14;
    QLabel *label_hunter_lat2;
    QLabel *label_hunter_lon2;
    QLabel *label_hunter_alt2;
    QHBoxLayout *horizontalLayout_14;
    QPushButton *pushButton_connect_drone;
    QPushButton *pushButton_take_off;
    QPushButton *pushButton_hunter_land;
    QPushButton *pushButton_hunt_bug;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QLineEdit *lineEdit_time;
    QSlider *horizontalSlider_time;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButton_play;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBox_play_speed;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_16;
    QRadioButton *radioButton_hunter_ball;
    QRadioButton *radioButton_hunter_point;
    QRadioButton *radioButton_hunter_hide;
    QCheckBox *checkBox_hunter_trajectory;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *radioButton_bug_point;
    QRadioButton *radioButton_bug_ball;
    QRadioButton *radioButton_bug_hide;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_7;
    QRadioButton *radioButton_obstacle_point;
    QRadioButton *radioButton_obstacle_ball;
    QRadioButton *radioButton_obstacle_with_safe_distance;
    QRadioButton *radioButton_obstacle_hide;
    QGroupBox *groupBox_8;
    QHBoxLayout *horizontalLayout_15;
    QCheckBox *checkBox_neighbors;
    QGroupBox *groupBox_7;
    QHBoxLayout *horizontalLayout_10;
    QCheckBox *checkBox_show_DVD;
    QHBoxLayout *horizontalLayout_18;
    QPushButton *pushButton_open_xy_view;
    QPushButton *pushButton_open_xz_view;
    QPushButton *pushButton_open_yz_view;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QMainWindow *VoroDroneClass)
    {
        if (VoroDroneClass->objectName().isEmpty())
            VoroDroneClass->setObjectName(QStringLiteral("VoroDroneClass"));
        VoroDroneClass->resize(716, 876);
        centralWidget = new QWidget(VoroDroneClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        droneDisplayer = new DroneDisplayerWidget(centralWidget);
        droneDisplayer->setObjectName(QStringLiteral("droneDisplayer"));

        horizontalLayout->addWidget(droneDisplayer);

        VoroDroneClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(VoroDroneClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 716, 21));
        VoroDroneClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VoroDroneClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        VoroDroneClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(VoroDroneClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        VoroDroneClass->setStatusBar(statusBar);
        dockWidget_2 = new QDockWidget(VoroDroneClass);
        dockWidget_2->setObjectName(QStringLiteral("dockWidget_2"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dockWidget_2->sizePolicy().hasHeightForWidth());
        dockWidget_2->setSizePolicy(sizePolicy);
        dockWidget_2->setMinimumSize(QSize(412, 770));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        verticalLayout = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(dockWidgetContents_2);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_4 = new QVBoxLayout(tab);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEdit_theta = new QLineEdit(groupBox);
        lineEdit_theta->setObjectName(QStringLiteral("lineEdit_theta"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_theta->sizePolicy().hasHeightForWidth());
        lineEdit_theta->setSizePolicy(sizePolicy2);
        lineEdit_theta->setMaximumSize(QSize(50, 16777215));
        lineEdit_theta->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_theta, 2, 1, 1, 1);

        lineEdit_r = new QLineEdit(groupBox);
        lineEdit_r->setObjectName(QStringLiteral("lineEdit_r"));
        sizePolicy2.setHeightForWidth(lineEdit_r->sizePolicy().hasHeightForWidth());
        lineEdit_r->setSizePolicy(sizePolicy2);
        lineEdit_r->setMinimumSize(QSize(0, 0));
        lineEdit_r->setMaximumSize(QSize(50, 16777215));
        lineEdit_r->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_r, 1, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        lineEdit_n = new QLineEdit(groupBox);
        lineEdit_n->setObjectName(QStringLiteral("lineEdit_n"));
        sizePolicy2.setHeightForWidth(lineEdit_n->sizePolicy().hasHeightForWidth());
        lineEdit_n->setSizePolicy(sizePolicy2);
        lineEdit_n->setMaximumSize(QSize(50, 16777215));
        lineEdit_n->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(lineEdit_n, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setAlignment(Qt::AlignCenter);

        horizontalLayout_12->addWidget(label_10);

        lineEdit_fence_length = new QLineEdit(groupBox);
        lineEdit_fence_length->setObjectName(QStringLiteral("lineEdit_fence_length"));
        lineEdit_fence_length->setMaximumSize(QSize(30, 16777215));
        lineEdit_fence_length->setAlignment(Qt::AlignCenter);

        horizontalLayout_12->addWidget(lineEdit_fence_length);

        lineEdit_fence_width = new QLineEdit(groupBox);
        lineEdit_fence_width->setObjectName(QStringLiteral("lineEdit_fence_width"));
        lineEdit_fence_width->setMaximumSize(QSize(30, 16777215));
        lineEdit_fence_width->setAlignment(Qt::AlignCenter);

        horizontalLayout_12->addWidget(lineEdit_fence_width);

        lineEdit_fence_height = new QLineEdit(groupBox);
        lineEdit_fence_height->setObjectName(QStringLiteral("lineEdit_fence_height"));
        lineEdit_fence_height->setMaximumSize(QSize(30, 16777215));
        lineEdit_fence_height->setAlignment(Qt::AlignCenter);

        horizontalLayout_12->addWidget(lineEdit_fence_height);


        verticalLayout_2->addLayout(horizontalLayout_12);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(label_8);

        lineEdit_path_computation_interval = new QLineEdit(groupBox);
        lineEdit_path_computation_interval->setObjectName(QStringLiteral("lineEdit_path_computation_interval"));
        lineEdit_path_computation_interval->setMinimumSize(QSize(0, 0));
        lineEdit_path_computation_interval->setMaximumSize(QSize(50, 16777215));
        lineEdit_path_computation_interval->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(lineEdit_path_computation_interval);


        verticalLayout_2->addLayout(horizontalLayout_9);

        pushButton_generate_drones = new QPushButton(groupBox);
        pushButton_generate_drones->setObjectName(QStringLiteral("pushButton_generate_drones"));

        verticalLayout_2->addWidget(pushButton_generate_drones);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_save_drones = new QPushButton(groupBox);
        pushButton_save_drones->setObjectName(QStringLiteral("pushButton_save_drones"));

        horizontalLayout_2->addWidget(pushButton_save_drones);

        pushButton_load_drones = new QPushButton(groupBox);
        pushButton_load_drones->setObjectName(QStringLiteral("pushButton_load_drones"));

        horizontalLayout_2->addWidget(pushButton_load_drones);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_4->addWidget(groupBox);

        groupBox_9 = new QGroupBox(tab);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        verticalLayout_9 = new QVBoxLayout(groupBox_9);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(groupBox_9);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_4);

        lineEdit_bug_speed = new QLineEdit(groupBox_9);
        lineEdit_bug_speed->setObjectName(QStringLiteral("lineEdit_bug_speed"));
        sizePolicy2.setHeightForWidth(lineEdit_bug_speed->sizePolicy().hasHeightForWidth());
        lineEdit_bug_speed->setSizePolicy(sizePolicy2);
        lineEdit_bug_speed->setMaximumSize(QSize(60, 16777215));
        lineEdit_bug_speed->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(lineEdit_bug_speed);


        verticalLayout_9->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(groupBox_9);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_5);

        comboBox_bug_generation_mode = new QComboBox(groupBox_9);
        comboBox_bug_generation_mode->setObjectName(QStringLiteral("comboBox_bug_generation_mode"));

        horizontalLayout_5->addWidget(comboBox_bug_generation_mode);


        verticalLayout_9->addLayout(horizontalLayout_5);

        pushButton_make_new_bug = new QPushButton(groupBox_9);
        pushButton_make_new_bug->setObjectName(QStringLiteral("pushButton_make_new_bug"));

        verticalLayout_9->addWidget(pushButton_make_new_bug);


        verticalLayout_4->addWidget(groupBox_9);

        groupBox_6 = new QGroupBox(tab);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        verticalLayout_7 = new QVBoxLayout(groupBox_6);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_12 = new QLabel(groupBox_6);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setAlignment(Qt::AlignCenter);

        horizontalLayout_17->addWidget(label_12);

        lineEdit_hunter_speed = new QLineEdit(groupBox_6);
        lineEdit_hunter_speed->setObjectName(QStringLiteral("lineEdit_hunter_speed"));
        lineEdit_hunter_speed->setMaximumSize(QSize(60, 16777215));
        lineEdit_hunter_speed->setAlignment(Qt::AlignCenter);

        horizontalLayout_17->addWidget(lineEdit_hunter_speed);


        verticalLayout_7->addLayout(horizontalLayout_17);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        label_11 = new QLabel(groupBox_6);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setAlignment(Qt::AlignCenter);

        horizontalLayout_13->addWidget(label_11);

        lineEdit_drone_address = new QLineEdit(groupBox_6);
        lineEdit_drone_address->setObjectName(QStringLiteral("lineEdit_drone_address"));
        lineEdit_drone_address->setMaximumSize(QSize(200, 16777215));
        lineEdit_drone_address->setAlignment(Qt::AlignCenter);

        horizontalLayout_13->addWidget(lineEdit_drone_address);


        verticalLayout_7->addLayout(horizontalLayout_13);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        label_9 = new QLabel(groupBox_6);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(label_9);

        label_hunter_lat = new QLabel(groupBox_6);
        label_hunter_lat->setObjectName(QStringLiteral("label_hunter_lat"));
        label_hunter_lat->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(label_hunter_lat);

        label_hunter_lon = new QLabel(groupBox_6);
        label_hunter_lon->setObjectName(QStringLiteral("label_hunter_lon"));
        label_hunter_lon->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(label_hunter_lon);

        label_hunter_alt = new QLabel(groupBox_6);
        label_hunter_alt->setObjectName(QStringLiteral("label_hunter_alt"));
        label_hunter_alt->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(label_hunter_alt);


        verticalLayout_7->addLayout(horizontalLayout_11);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        label_13 = new QLabel(groupBox_6);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setAlignment(Qt::AlignCenter);

        horizontalLayout_19->addWidget(label_13);

        lineEdit_drone_address2 = new QLineEdit(groupBox_6);
        lineEdit_drone_address2->setObjectName(QStringLiteral("lineEdit_drone_address2"));
        lineEdit_drone_address2->setMaximumSize(QSize(200, 16777215));
        lineEdit_drone_address2->setAlignment(Qt::AlignCenter);

        horizontalLayout_19->addWidget(lineEdit_drone_address2);


        verticalLayout_7->addLayout(horizontalLayout_19);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        label_14 = new QLabel(groupBox_6);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_20->addWidget(label_14);

        label_hunter_lat2 = new QLabel(groupBox_6);
        label_hunter_lat2->setObjectName(QStringLiteral("label_hunter_lat2"));
        label_hunter_lat2->setAlignment(Qt::AlignCenter);

        horizontalLayout_20->addWidget(label_hunter_lat2);

        label_hunter_lon2 = new QLabel(groupBox_6);
        label_hunter_lon2->setObjectName(QStringLiteral("label_hunter_lon2"));
        label_hunter_lon2->setAlignment(Qt::AlignCenter);

        horizontalLayout_20->addWidget(label_hunter_lon2);

        label_hunter_alt2 = new QLabel(groupBox_6);
        label_hunter_alt2->setObjectName(QStringLiteral("label_hunter_alt2"));
        label_hunter_alt2->setAlignment(Qt::AlignCenter);

        horizontalLayout_20->addWidget(label_hunter_alt2);


        verticalLayout_7->addLayout(horizontalLayout_20);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        pushButton_connect_drone = new QPushButton(groupBox_6);
        pushButton_connect_drone->setObjectName(QStringLiteral("pushButton_connect_drone"));

        horizontalLayout_14->addWidget(pushButton_connect_drone);

        pushButton_take_off = new QPushButton(groupBox_6);
        pushButton_take_off->setObjectName(QStringLiteral("pushButton_take_off"));

        horizontalLayout_14->addWidget(pushButton_take_off);

        pushButton_hunter_land = new QPushButton(groupBox_6);
        pushButton_hunter_land->setObjectName(QStringLiteral("pushButton_hunter_land"));

        horizontalLayout_14->addWidget(pushButton_hunter_land);


        verticalLayout_7->addLayout(horizontalLayout_14);

        pushButton_hunt_bug = new QPushButton(groupBox_6);
        pushButton_hunt_bug->setObjectName(QStringLiteral("pushButton_hunt_bug"));

        verticalLayout_7->addWidget(pushButton_hunt_bug);


        verticalLayout_4->addWidget(groupBox_6);

        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_7);

        lineEdit_time = new QLineEdit(groupBox_2);
        lineEdit_time->setObjectName(QStringLiteral("lineEdit_time"));
        lineEdit_time->setMaximumSize(QSize(100, 16777215));
        lineEdit_time->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(lineEdit_time);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalSlider_time = new QSlider(groupBox_2);
        horizontalSlider_time->setObjectName(QStringLiteral("horizontalSlider_time"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(horizontalSlider_time->sizePolicy().hasHeightForWidth());
        horizontalSlider_time->setSizePolicy(sizePolicy3);
        horizontalSlider_time->setMaximumSize(QSize(300, 16777215));
        horizontalSlider_time->setMaximum(1000);
        horizontalSlider_time->setOrientation(Qt::Horizontal);

        verticalLayout_3->addWidget(horizontalSlider_time);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        pushButton_play = new QPushButton(groupBox_2);
        pushButton_play->setObjectName(QStringLiteral("pushButton_play"));

        horizontalLayout_8->addWidget(pushButton_play);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_6);

        doubleSpinBox_play_speed = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_play_speed->setObjectName(QStringLiteral("doubleSpinBox_play_speed"));
        doubleSpinBox_play_speed->setMaximumSize(QSize(100, 16777215));
        doubleSpinBox_play_speed->setAlignment(Qt::AlignCenter);
        doubleSpinBox_play_speed->setDecimals(1);
        doubleSpinBox_play_speed->setMinimum(0.1);
        doubleSpinBox_play_speed->setMaximum(10);
        doubleSpinBox_play_speed->setSingleStep(0.1);
        doubleSpinBox_play_speed->setValue(1);

        horizontalLayout_8->addWidget(doubleSpinBox_play_speed);


        verticalLayout_3->addLayout(horizontalLayout_8);


        verticalLayout_4->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_5 = new QVBoxLayout(tab_2);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_8 = new QVBoxLayout(groupBox_3);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        radioButton_hunter_ball = new QRadioButton(groupBox_3);
        radioButton_hunter_ball->setObjectName(QStringLiteral("radioButton_hunter_ball"));
        radioButton_hunter_ball->setChecked(false);

        horizontalLayout_16->addWidget(radioButton_hunter_ball);

        radioButton_hunter_point = new QRadioButton(groupBox_3);
        radioButton_hunter_point->setObjectName(QStringLiteral("radioButton_hunter_point"));
        radioButton_hunter_point->setChecked(false);

        horizontalLayout_16->addWidget(radioButton_hunter_point);

        radioButton_hunter_hide = new QRadioButton(groupBox_3);
        radioButton_hunter_hide->setObjectName(QStringLiteral("radioButton_hunter_hide"));
        radioButton_hunter_hide->setChecked(true);

        horizontalLayout_16->addWidget(radioButton_hunter_hide);


        verticalLayout_8->addLayout(horizontalLayout_16);

        checkBox_hunter_trajectory = new QCheckBox(groupBox_3);
        checkBox_hunter_trajectory->setObjectName(QStringLiteral("checkBox_hunter_trajectory"));

        verticalLayout_8->addWidget(checkBox_hunter_trajectory);


        verticalLayout_5->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(tab_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        horizontalLayout_6 = new QHBoxLayout(groupBox_4);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        radioButton_bug_point = new QRadioButton(groupBox_4);
        radioButton_bug_point->setObjectName(QStringLiteral("radioButton_bug_point"));
        radioButton_bug_point->setChecked(false);

        horizontalLayout_6->addWidget(radioButton_bug_point);

        radioButton_bug_ball = new QRadioButton(groupBox_4);
        radioButton_bug_ball->setObjectName(QStringLiteral("radioButton_bug_ball"));
        radioButton_bug_ball->setCheckable(true);
        radioButton_bug_ball->setChecked(false);

        horizontalLayout_6->addWidget(radioButton_bug_ball);

        radioButton_bug_hide = new QRadioButton(groupBox_4);
        radioButton_bug_hide->setObjectName(QStringLiteral("radioButton_bug_hide"));
        radioButton_bug_hide->setChecked(true);

        horizontalLayout_6->addWidget(radioButton_bug_hide);


        verticalLayout_5->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(tab_2);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        horizontalLayout_7 = new QHBoxLayout(groupBox_5);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        radioButton_obstacle_point = new QRadioButton(groupBox_5);
        radioButton_obstacle_point->setObjectName(QStringLiteral("radioButton_obstacle_point"));

        horizontalLayout_7->addWidget(radioButton_obstacle_point);

        radioButton_obstacle_ball = new QRadioButton(groupBox_5);
        radioButton_obstacle_ball->setObjectName(QStringLiteral("radioButton_obstacle_ball"));
        radioButton_obstacle_ball->setLayoutDirection(Qt::LeftToRight);
        radioButton_obstacle_ball->setChecked(false);

        horizontalLayout_7->addWidget(radioButton_obstacle_ball);

        radioButton_obstacle_with_safe_distance = new QRadioButton(groupBox_5);
        radioButton_obstacle_with_safe_distance->setObjectName(QStringLiteral("radioButton_obstacle_with_safe_distance"));
        radioButton_obstacle_with_safe_distance->setChecked(true);

        horizontalLayout_7->addWidget(radioButton_obstacle_with_safe_distance);

        radioButton_obstacle_hide = new QRadioButton(groupBox_5);
        radioButton_obstacle_hide->setObjectName(QStringLiteral("radioButton_obstacle_hide"));

        horizontalLayout_7->addWidget(radioButton_obstacle_hide);


        verticalLayout_5->addWidget(groupBox_5);

        groupBox_8 = new QGroupBox(tab_2);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        horizontalLayout_15 = new QHBoxLayout(groupBox_8);
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        checkBox_neighbors = new QCheckBox(groupBox_8);
        checkBox_neighbors->setObjectName(QStringLiteral("checkBox_neighbors"));

        horizontalLayout_15->addWidget(checkBox_neighbors);


        verticalLayout_5->addWidget(groupBox_8);

        groupBox_7 = new QGroupBox(tab_2);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        horizontalLayout_10 = new QHBoxLayout(groupBox_7);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        checkBox_show_DVD = new QCheckBox(groupBox_7);
        checkBox_show_DVD->setObjectName(QStringLiteral("checkBox_show_DVD"));
        checkBox_show_DVD->setChecked(false);

        horizontalLayout_10->addWidget(checkBox_show_DVD);


        verticalLayout_5->addWidget(groupBox_7);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        pushButton_open_xy_view = new QPushButton(tab_2);
        pushButton_open_xy_view->setObjectName(QStringLiteral("pushButton_open_xy_view"));

        horizontalLayout_18->addWidget(pushButton_open_xy_view);

        pushButton_open_xz_view = new QPushButton(tab_2);
        pushButton_open_xz_view->setObjectName(QStringLiteral("pushButton_open_xz_view"));

        horizontalLayout_18->addWidget(pushButton_open_xz_view);

        pushButton_open_yz_view = new QPushButton(tab_2);
        pushButton_open_yz_view->setObjectName(QStringLiteral("pushButton_open_yz_view"));

        horizontalLayout_18->addWidget(pushButton_open_yz_view);


        verticalLayout_5->addLayout(horizontalLayout_18);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_2);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        dockWidget_2->setWidget(dockWidgetContents_2);
        VoroDroneClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_2);

        retranslateUi(VoroDroneClass);
        QObject::connect(radioButton_hunter_point, SIGNAL(clicked()), VoroDroneClass, SLOT(show_option_changed()));
        QObject::connect(radioButton_hunter_ball, SIGNAL(clicked()), VoroDroneClass, SLOT(show_option_changed()));
        QObject::connect(radioButton_hunter_hide, SIGNAL(clicked()), VoroDroneClass, SLOT(show_option_changed()));
        QObject::connect(radioButton_bug_point, SIGNAL(clicked()), VoroDroneClass, SLOT(show_option_changed()));
        QObject::connect(radioButton_bug_ball, SIGNAL(clicked()), VoroDroneClass, SLOT(show_option_changed()));
        QObject::connect(radioButton_bug_hide, SIGNAL(clicked()), VoroDroneClass, SLOT(show_option_changed()));
        QObject::connect(radioButton_obstacle_with_safe_distance, SIGNAL(clicked()), VoroDroneClass, SLOT(show_option_changed()));
        QObject::connect(radioButton_obstacle_point, SIGNAL(clicked()), VoroDroneClass, SLOT(show_option_changed()));
        QObject::connect(radioButton_obstacle_ball, SIGNAL(clicked()), VoroDroneClass, SLOT(show_option_changed()));
        QObject::connect(radioButton_obstacle_hide, SIGNAL(clicked()), VoroDroneClass, SLOT(show_option_changed()));
        QObject::connect(lineEdit_time, SIGNAL(returnPressed()), VoroDroneClass, SLOT(current_time_changed_by_edit()));
        QObject::connect(horizontalSlider_time, SIGNAL(sliderReleased()), VoroDroneClass, SLOT(current_time_changed_by_slider()));
        QObject::connect(doubleSpinBox_play_speed, SIGNAL(valueChanged(double)), VoroDroneClass, SLOT(play_speed_changed(double)));
        QObject::connect(pushButton_play, SIGNAL(clicked()), VoroDroneClass, SLOT(play_simulation()));
        QObject::connect(pushButton_generate_drones, SIGNAL(clicked()), VoroDroneClass, SLOT(generate_drones_and_prepare_simulation()));
        QObject::connect(checkBox_show_DVD, SIGNAL(clicked()), VoroDroneClass, SLOT(show_option_changed()));
        QObject::connect(pushButton_save_drones, SIGNAL(clicked()), VoroDroneClass, SLOT(save_drone_informations()));
        QObject::connect(pushButton_load_drones, SIGNAL(clicked()), VoroDroneClass, SLOT(load_drone_informations()));
        QObject::connect(pushButton_connect_drone, SIGNAL(clicked()), VoroDroneClass, SLOT(connect_to_hunter()));
        QObject::connect(pushButton_take_off, SIGNAL(clicked()), VoroDroneClass, SLOT(take_off_hunter()));
        QObject::connect(pushButton_hunt_bug, SIGNAL(clicked()), VoroDroneClass, SLOT(hunt_bug()));
        QObject::connect(pushButton_hunter_land, SIGNAL(clicked()), VoroDroneClass, SLOT(land_hunter()));
        QObject::connect(checkBox_neighbors, SIGNAL(clicked()), VoroDroneClass, SLOT(show_option_changed()));
        QObject::connect(checkBox_hunter_trajectory, SIGNAL(clicked()), VoroDroneClass, SLOT(show_option_changed()));
        QObject::connect(pushButton_make_new_bug, SIGNAL(clicked()), VoroDroneClass, SLOT(generate_bug()));
        QObject::connect(pushButton_open_xy_view, SIGNAL(clicked()), VoroDroneClass, SLOT(make_xy_view_widget()));
        QObject::connect(pushButton_open_xz_view, SIGNAL(clicked()), VoroDroneClass, SLOT(make_xz_view_widget()));
        QObject::connect(pushButton_open_yz_view, SIGNAL(clicked()), VoroDroneClass, SLOT(make_yz_view_widget()));

        tabWidget->setCurrentIndex(0);
        comboBox_bug_generation_mode->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(VoroDroneClass);
    } // setupUi

    void retranslateUi(QMainWindow *VoroDroneClass)
    {
        VoroDroneClass->setWindowTitle(QApplication::translate("VoroDroneClass", "H-Mapper", 0));
        groupBox->setTitle(QApplication::translate("VoroDroneClass", "Generate Drones", 0));
        lineEdit_theta->setText(QApplication::translate("VoroDroneClass", "0.25", 0));
        lineEdit_r->setText(QApplication::translate("VoroDroneClass", "0.25", 0));
        label->setText(QApplication::translate("VoroDroneClass", "Drone radius(m)", 0));
        label_3->setText(QApplication::translate("VoroDroneClass", "#Obstacles", 0));
        lineEdit_n->setText(QApplication::translate("VoroDroneClass", "100", 0));
        label_2->setText(QApplication::translate("VoroDroneClass", "Safety distance(m)", 0));
        label_10->setText(QApplication::translate("VoroDroneClass", "Fence size(L/W/H, m)", 0));
        lineEdit_fence_length->setText(QApplication::translate("VoroDroneClass", "100", 0));
        lineEdit_fence_width->setText(QApplication::translate("VoroDroneClass", "100", 0));
        lineEdit_fence_height->setText(QApplication::translate("VoroDroneClass", "100", 0));
        label_8->setText(QApplication::translate("VoroDroneClass", "Path computation interval(s)", 0));
        lineEdit_path_computation_interval->setText(QApplication::translate("VoroDroneClass", "0.5", 0));
        pushButton_generate_drones->setText(QApplication::translate("VoroDroneClass", "Generate", 0));
        pushButton_save_drones->setText(QApplication::translate("VoroDroneClass", "Save", 0));
        pushButton_load_drones->setText(QApplication::translate("VoroDroneClass", "Load", 0));
        groupBox_9->setTitle(QApplication::translate("VoroDroneClass", "Bug Controller", 0));
        label_4->setText(QApplication::translate("VoroDroneClass", "Bug speed(m/s)", 0));
        lineEdit_bug_speed->setText(QApplication::translate("VoroDroneClass", "3.0", 0));
        label_5->setText(QApplication::translate("VoroDroneClass", "Bug generation mode", 0));
        comboBox_bug_generation_mode->setCurrentText(QString());
        pushButton_make_new_bug->setText(QApplication::translate("VoroDroneClass", "Make new bug", 0));
        groupBox_6->setTitle(QApplication::translate("VoroDroneClass", "Hunter Controller", 0));
        label_12->setText(QApplication::translate("VoroDroneClass", "Hunter speed(m/s)", 0));
        lineEdit_hunter_speed->setText(QApplication::translate("VoroDroneClass", "3.0", 0));
        label_11->setText(QApplication::translate("VoroDroneClass", "Address", 0));
        lineEdit_drone_address->setText(QApplication::translate("VoroDroneClass", "udp:127.0.0.1:14550", 0));
        label_9->setText(QApplication::translate("VoroDroneClass", "Lat./Lon./Alt.", 0));
        label_hunter_lat->setText(QApplication::translate("VoroDroneClass", "NULL", 0));
        label_hunter_lon->setText(QApplication::translate("VoroDroneClass", "NULL", 0));
        label_hunter_alt->setText(QApplication::translate("VoroDroneClass", "NULL", 0));
        label_13->setText(QApplication::translate("VoroDroneClass", "Address", 0));
        lineEdit_drone_address2->setText(QApplication::translate("VoroDroneClass", "udp:127.0.0.1:14550", 0));
        label_14->setText(QApplication::translate("VoroDroneClass", "Lat./Lon./Alt.", 0));
        label_hunter_lat2->setText(QApplication::translate("VoroDroneClass", "NULL", 0));
        label_hunter_lon2->setText(QApplication::translate("VoroDroneClass", "NULL", 0));
        label_hunter_alt2->setText(QApplication::translate("VoroDroneClass", "NULL", 0));
        pushButton_connect_drone->setText(QApplication::translate("VoroDroneClass", "Connect to drone", 0));
        pushButton_take_off->setText(QApplication::translate("VoroDroneClass", "Take off", 0));
        pushButton_hunter_land->setText(QApplication::translate("VoroDroneClass", "Land", 0));
        pushButton_hunt_bug->setText(QApplication::translate("VoroDroneClass", "Hunt bug", 0));
        groupBox_2->setTitle(QApplication::translate("VoroDroneClass", "Simulation", 0));
        label_7->setText(QApplication::translate("VoroDroneClass", "Time(s)", 0));
        lineEdit_time->setText(QApplication::translate("VoroDroneClass", "0.0", 0));
        pushButton_play->setText(QApplication::translate("VoroDroneClass", "\342\226\266/||", 0));
        label_6->setText(QApplication::translate("VoroDroneClass", "Play speed", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("VoroDroneClass", "Simulation", 0));
        groupBox_3->setTitle(QApplication::translate("VoroDroneClass", "Hunter", 0));
        radioButton_hunter_ball->setText(QApplication::translate("VoroDroneClass", "Ball", 0));
        radioButton_hunter_point->setText(QApplication::translate("VoroDroneClass", "Point", 0));
        radioButton_hunter_hide->setText(QApplication::translate("VoroDroneClass", "Hide", 0));
        checkBox_hunter_trajectory->setText(QApplication::translate("VoroDroneClass", "Trajectory", 0));
        groupBox_4->setTitle(QApplication::translate("VoroDroneClass", "Bug", 0));
        radioButton_bug_point->setText(QApplication::translate("VoroDroneClass", "Point", 0));
        radioButton_bug_ball->setText(QApplication::translate("VoroDroneClass", "Ball", 0));
        radioButton_bug_hide->setText(QApplication::translate("VoroDroneClass", "Hide", 0));
        groupBox_5->setTitle(QApplication::translate("VoroDroneClass", "Obstacles", 0));
        radioButton_obstacle_point->setText(QApplication::translate("VoroDroneClass", "Point", 0));
        radioButton_obstacle_ball->setText(QApplication::translate("VoroDroneClass", "Ball", 0));
        radioButton_obstacle_with_safe_distance->setText(QApplication::translate("VoroDroneClass", "Enlarged ", 0));
        radioButton_obstacle_hide->setText(QApplication::translate("VoroDroneClass", "Hide", 0));
        groupBox_8->setTitle(QApplication::translate("VoroDroneClass", "Proximity Informations", 0));
        checkBox_neighbors->setText(QApplication::translate("VoroDroneClass", "Neighbors", 0));
        groupBox_7->setTitle(QApplication::translate("VoroDroneClass", "Voronoi Diagram", 0));
        checkBox_show_DVD->setText(QApplication::translate("VoroDroneClass", "Show", 0));
        pushButton_open_xy_view->setText(QApplication::translate("VoroDroneClass", "XY View", 0));
        pushButton_open_xz_view->setText(QApplication::translate("VoroDroneClass", "XZ View", 0));
        pushButton_open_yz_view->setText(QApplication::translate("VoroDroneClass", "YZ View", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("VoroDroneClass", "Visualization", 0));
    } // retranslateUi

};

namespace Ui {
    class VoroDroneClass: public Ui_VoroDroneClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VORODRONE_H
