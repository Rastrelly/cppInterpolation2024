#pragma once

#include <iostream>
#include <vector>
#include <boost/math/interpolators/cardinal_cubic_b_spline.hpp>

struct point
{
	float x, y;
};

typedef std::vector<point> pVec;

class multiInterpolator
{
private:
	pVec dataSet;
	boost::math::interpolators::cardinal_cubic_b_spline<float> *spline;
public:

	//constructor
	multiInterpolator(int l)
	{
		makeDataSet(l);
	}

	//general data management
	point getDataPoint(int id)
	{
		return dataSet[id];
	}
	int getDataSetSize()
	{
		return dataSet.size();
	}
	point nativeFunction(float x);	
	void makeDataSet(int l);
	void printData();

	//linear interpolation
	void findNearestNeighbours(point &p1, point &p2, float sx);
	point lInterp(float x);
	
	//lagrange interpolation
	float findLJ(int j, float x, pVec ds);
	point lagrangeInterp(float x);

	//newton interpolate
    //https://gist.github.com/komasaru/6a10c02cf3f5e5fe411d7fb3987b36dd
	point newtonInterp(float x);

	//spline interp
	void prepSpline();
	point splineInterp(float x);

};

