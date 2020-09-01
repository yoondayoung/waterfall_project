#pragma once

#include "ofMain.h"
#include "others.h"
#include <vector>

class waterObj {

	public:
		int x;
		double y;
		int continue_;
		vector<WaterLine> waterset;

		waterObj() {
			x = 0;
			y = 0;
			continue_ = 0;
			waterset.clear();
		}

		waterObj(WaterPoint wp) {
			x = wp.Xp;
			y = wp.Yp;
			continue_ = 0;
			waterset.clear();
		}

		void move(WaterPoint, vector<WaterLine>, int);
};