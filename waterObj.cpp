#include "waterObj.h"

void waterObj::move(WaterPoint wp, vector<WaterLine> lines, int endp) {
	double epsilon1, epsilon2;
	WaterLine currentline = lines[0], newline;
	int find = 0;

	if (this->y >= endp) return;

	for (int i = 0; i < lines.size(); i++) {
		if (lines[i].X1<this->x&&this->x<lines[i].X2&&min((int)lines[i].Y1, (int)lines[i].Y2) <= this->y&&this->y <= max((int)lines[i].Y1,(int)lines[i].Y2)) {
			// 밑에 선분 있을 때 제일 가까운 선분 찾기
			if (find == 0) {
				currentline = lines[i];
				find = 1;
			}
			else if (min((int)currentline.Y1, (int)currentline.Y2) > min((int)lines[i].Y1, (int)lines[i].Y2)) {
				currentline = lines[i];
			}
		}
	}

	// 새로 추가될 line
	newline.X1 = this->x;
	newline.Y1 = this->y;
	if (find == 1) {
		epsilon1 = (this->y - currentline.Y1) / (this->x - currentline.X1);
		epsilon2 = (currentline.Y2 - currentline.Y1) / (currentline.X2 - currentline.X1);
		if (abs(epsilon1-epsilon2)<=0.04||continue_==1) {
			// 다음 경로 찾아 감(x2,y2 점)
			if (epsilon2 < 0&&(this->x) - 5>=currentline.X1) {
				this->continue_ = 1;
				this->x -= 5;
				this->y -= 5.0 * epsilon2;
				if ((this->x) - 5 < currentline.X1) this->continue_ = 0;
				newline.X2 = this->x;
				newline.Y2 = this->y;
				this->waterset.push_back(newline);
				return;
			}
			if(epsilon2 >= 0 && (this->x) + 5 <= currentline.X2){
				this->continue_ = 1;
				this->x += 5;
				this->y += 5.0 * epsilon2;
				if ((this->x) + 5 > currentline.X1) this->continue_ = 0;
				newline.X2 = this->x;
				newline.Y2 = this->y;
				this->waterset.push_back(newline);
				return;
			}
		}
	}
	this->y += 3;
	newline.X2 = this->x;
	newline.Y2 = this->y;
	this->waterset.push_back(newline);
}