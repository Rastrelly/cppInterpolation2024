#include "multiInterpolator.h"

point multiInterpolator::nativeFunction(float x)
{
	return { x, 10 * sin(5.0f*x*3.14f / 180.0f) + 5 * cos(15.0f*x*3.14f / 180.0f + 3.14f / 4.0f) };
	//return { x, (float)(rand() % 101 - 50) };
}

void multiInterpolator::makeDataSet(int l)
{
	dataSet.resize(l);
	float xStart = (rand() % 100 + 10)*(-1);
	float xEnd = (rand() % 100 + 10);
	float step = (xEnd - xStart) / ((float)l);
	for (int i = 0; i < l; i++) dataSet[i] = { xStart + (float)i*step, nativeFunction(xStart + (float)i * step).y };
}

void multiInterpolator::printData()
{
	int i = 0;
	for (point p : dataSet)
	{
		i++;
		std::cout << i << ") ";
		std::cout << p.x << "; " << p.y << "\n";
	}
}

void multiInterpolator::findNearestNeighbours(point &p1, point &p2, float sx)
{
	int l = dataSet.size();
	p1 = dataSet[0];
	p2 = dataSet[1];
	for (int i = 0; i < l - 1; i++)
	{
		if ((abs(dataSet[i].x - sx) < abs(p1.x - sx)) && (sx > dataSet[i].x))
		{
			p1 = dataSet[i];
			p2 = dataSet[i + 1];

			//std::cout << "P1: " << p1.x << "; " << p1.y << "; ";
			//std::cout << "P2: " << p2.x << "; " << p2.y << "\n";
		}
	}
}

point multiInterpolator::lInterp(float x)
{
	point n1; point n2;
	findNearestNeighbours(n1, n2, x);
	float y = (((n2.y - n1.y)*(x - n1.x)) / (n2.x - n1.x)) + n1.y;
	return { x,y };
}

float multiInterpolator::findLJ(int j, float x, pVec ds)
{
	int l = ds.size();
	float res = 1;
	for (int i = 0; i < l; i++)
	{
		if (i == j) continue;
		res *= (x - ds[i].x) / (ds[j].x - ds[i].x);
	}
	return res;
}

point multiInterpolator::lagrangeInterp(float x)
{
	int l = dataSet.size();
	float sum = 0;
	for (int i = 0; i < l; i++)
	{
		sum += dataSet[i].y*findLJ(i, x, dataSet);
	}
	return { x, sum };
}

point multiInterpolator::newtonInterp(float x)
{
	int n = dataSet.size();
	std::vector<float> w = {};
	w.resize(n);
	std::vector<float> c = {};
	c.resize(n);
	for (int i = 0; i < n; i++) {
		w[i] = dataSet[i].y;
		for (int j = i - 1; j >= 0; j--)
			w[j] = (w[j + 1] - w[j]) / (dataSet[i].x - dataSet[j].x);
		c[i] = w[0];
	}

	float s = c[n - 1];
	for (int i = n - 2; i >= 0; i--)
		s = s * (x - dataSet[i].x) + c[i];

	return { x,s };
}

void multiInterpolator::prepSpline()
{
	//1 separate Y values
	std::vector<float> valY = {};
	valY.resize(dataSet.size());
	int i = 0;
	for (point cp : dataSet)
	{
		valY[i++] = cp.y;
	}

	//2 use boost
	float step = dataSet[1].x - dataSet[0].x;
	spline = new boost::math::interpolators::cardinal_cubic_b_spline<float>(valY.begin(), valY.end(), dataSet[0].x, step);
}

point multiInterpolator::splineInterp(float x)
{
	float y = spline->operator()(x);
	return {x,y};
}