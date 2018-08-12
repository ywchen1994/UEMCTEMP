#pragma once
#include<vector>
class Pt
{
public:
	Pt();
	Pt(double _x, double _y);
	Pt(double _x, double _y,double _range,double _theta);
	double x;
	double y;
	double range;
	double theta;
	double velcity;
	int cluster = 0;
	int pointType = 1;//1 noise 2 border 3 core
	int pts = 0;//points in MinPts 
	std::vector<int> corepts;
	int visited = 0;
	
	Pt(float a, float b, int c) {
		x = a;
		y = b;
		cluster = c;
	}
};

