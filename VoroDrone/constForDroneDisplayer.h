#pragma once

#include "Color3f.h"

const Color3f HUNTER_COLOR		= BLUE;
const Color3f BUG_COLOR				= RED;
const Color3f OBSTACLE_COLOR	= GREY;

enum SHOW_HUNTER			{ H_HIDE, H_POINT, H_BALL };
enum SHOW_BUG				{ B_HIDE, B_POINT, B_BALL };
enum SHOW_OBSTACLE		{ O_HIDE, O_POINT, O_BALL, O_ENLARGED};

const int TIME_SLIDER_LENGTH = 1000;