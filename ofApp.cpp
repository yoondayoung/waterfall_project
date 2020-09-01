#include "ofApp.h"
#include <fstream>


//--------------------------------------------------------------
void ofApp::setup(){
	//바탕화면 색 -> 하얀색
	ofSetBackgroundColor(255, 255, 255);
	// 선분의 굵기 -> 5
	ofSetLineWidth(5);

	this->draw_flag = 0;
	this->start_flag = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (this->start_flag == 1) {
		fallingwater.move(this->waterpoints[this->target], this->waterlines, ofGetHeight());
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (this->draw_flag) {

		for (int i = 0; i < this->waterlines.size(); i++) {
			ofSetColor(165, 42, 42); // 갈색으로 그리기
			WaterLine wl = this->waterlines[i];
			ofDrawLine(wl.X1, wl.Y1, wl.X2, wl.Y2);
		}

		for (int i = 0; i < this->waterpoints.size(); i++) {
			WaterPoint wp = this->waterpoints[i];
			DrawProperCircle(wp);
		}

	}

	if (this->start_flag == 1) {
		for (int i = 0; i < this->fallingwater.waterset.size(); i++) {
			ofSetColor(0, 0, 255);
			WaterLine wl = this->fallingwater.waterset[i];
			ofDrawLine(wl.X1, wl.Y1, wl.X2, wl.Y2);
		}
	}
}

void ofApp::DrawProperCircle(WaterPoint p)
{
	if (p.water_activate) {
		ofSetColor(255, 0, 0); // 빨강색으로 그리기
	}
	else {
		ofSetColor(0, 0, 0); // 검정색으로 그리기
	}
	ofDrawCircle(p.Xp, p.Yp, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	ofFileDialogResult fileResult;
	
	switch (key) {
	case 'L':
	case 'l': 
		cout << "L Pressed: Load" << endl;
		fileResult = ofSystemLoadDialog("Load input file");
		processOpenFileSelection(fileResult);
		break;
	case 'D':
	case 'd':
		cout << "D Pressed: Draw" << endl;
		this->draw_flag = 1;
		break;
	case 'S':
	case 's':
		cout << "S pressed: Start the waterfall program" << endl;
		this->start_flag = 1;
		this->fallingwater = waterObj(this->waterpoints[this->target]);
		break;
	case 'E':
	case 'e':
		cout << "E pressed: End the waterfall program" << endl;
		this->start_flag = 0;
		break;
	case 'Q':
	case 'q':
		cout << "Q pressed: Quit" << endl;
		vector<WaterLine>().swap(this->waterlines);
		vector<WaterPoint>().swap(this->waterpoints);
		vector<WaterLine>().swap(this->fallingwater.waterset);
		ofExitCallback();
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == OF_KEY_LEFT) {
		this->waterpoints[target].water_activate = 0;
		DrawProperCircle(this->waterpoints[target]);
		if (this->target == 0) { // 제일 왼쪽이면 제일 오른쪽으로 타겟 변경
			this->target = this->waterpoints.size() - 1;
		}
		else { // 제일 왼쪽이 아니면 다음 왼쪽으로 타겟 변경
			this->target--;
		}
		this->waterpoints[target].water_activate = 1;
		DrawProperCircle(this->waterpoints[target]);
	}

	if (key == OF_KEY_RIGHT) {
		this->waterpoints[target].water_activate = 0;
		DrawProperCircle(this->waterpoints[target]);
		if (this->target == this->waterpoints.size() - 1) { // 제일 오른쪽이면 제일 쪽으로 타겟 변경
			this->target = 0;
		}
		else {
			this->target++;
		}
		this->waterpoints[target].water_activate = 1;
		DrawProperCircle(this->waterpoints[target]);
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

bool cmp(const WaterPoint& a, const WaterPoint& b)
{
	if (a.Xp < b.Xp) return true;
	else if (a.Xp == b.Xp) {
		if (a.Yp < b.Yp) return true;
	}
	return false;
}

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult)
{	
	// 선, 점 정보 배열 초기화
	this->waterlines.clear();
	this->waterpoints.clear(); 

	if (openFileResult.bSuccess) {
		int lines, X1, Y1, X2, Y2, Xp, Yp;
		int width = ofGetWidth();
		int height = ofGetHeight();
		string path = openFileResult.getPath();
		ifstream inputFile;
		inputFile.open(path);

		if (!inputFile.is_open()) {
			cout << "Failed to open file" << endl;
			return;
		}

		inputFile >> lines;
		for (int i = 0; i < lines; i++) {
			inputFile >> X1;
			inputFile >> Y1;
			inputFile >> X2;
			inputFile >> Y2;
			if (0 > X1 || 0 > Y1 || 0 > X2 || 0 > Y2 || width < X1 || height < Y1 || width < X2 || height < Y2) {
				cout << "Unvalid coordination value" << endl;
				return;
			}
			cout << "read waterline: x1: " << X1 << ", y1: " << Y1 << ", x2: " << X2 << ", y2: " << Y2 << endl;
			WaterLine wl;
			wl.X1 = X1;
			wl.Y1 = Y1;
			wl.X2 = X2;
			wl.Y2 = Y2;
			this->waterlines.push_back(wl);
		}

		inputFile >> lines;
		for (int i = 0; i < lines; i++) {
			inputFile >> Xp;
			inputFile >> Yp;
			if (0 > Xp || 0 > Yp || width < Xp || height < Yp) {
				cout << "Unvalid coordination value" << endl;
				return;
			}
			cout << "read waterpoint: x: " << Xp << ", y: " << Yp << endl;
			WaterPoint wp;
			wp.Xp = Xp;
			wp.Yp = Yp;
			if (i == 0) {
				wp.water_activate = 1;
				this->target = i;
			}
			else {
				wp.water_activate = 0;
			}
			this->waterpoints.push_back(wp);
		}
		sort(this->waterpoints.begin(), this->waterpoints.end(), cmp); // x좌표 기준 오름차순 정렬
		inputFile.close();
	}
}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
