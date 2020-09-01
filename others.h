#pragma once

#include "ofMain.h"

struct WaterLine {
	int X1;
	double Y1;
	int X2;
	double Y2;
};

struct WaterPoint {
	int Xp;
	int Yp;
	int water_activate; // selecting start point
};
