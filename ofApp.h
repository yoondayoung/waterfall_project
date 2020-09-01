#pragma once

#include "ofMain.h"
#include "waterObj.h"
#include <algorithm>
#include <vector>


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	// waterFall-realted member variables
	int draw_flag;
	int start_flag;
	vector<WaterLine> waterlines;
	vector<WaterPoint> waterpoints;
	int target;
	waterObj fallingwater;

	// waterFall-related member functions
	void processOpenFileSelection(ofFileDialogResult openFileResult);
	void DrawProperCircle(WaterPoint p);
};
