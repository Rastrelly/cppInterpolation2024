#pragma once

#include <iostream>
#include <vector>

struct point
{
	float x, y;
};

typedef std::vector<point> pVec;

class multiInterpolator
{
private:
	pVec dataSet;
public:
	point nativeFunction(float x)
	{
		return { x, pow(x, 2) };
	}
	multiInterpolator(int l)
	{
		makeDataSet(l);
	}
	void makeDataSet(int l)
	{
		dataSet.resize(l);
		for (int i = 0; i < l; i++) dataSet[i] = { (float)i, nativeFunction(i).y };
	}
	void findNearestNeighbours(point &p1, point &p2, float sx)
	{
		int l = dataSet.size();
		p1 = dataSet[0];
		p2 = dataSet[1];
		for (int i = 0; i < l - 1; i++)
		{
			if ((abs(dataSet[i].x - sx)<abs(p1.x - sx)) && (sx>dataSet[i].x))
			{
				p1 = dataSet[i];
				p2 = dataSet[i + 1];
				
				std::cout << "P1: " << p1.x << "; " << p1.y << "; ";
				std::cout << "P2: " << p2.x << "; " << p2.y << "\n";
			}
		}
	}
	point lInterp(float x)
	{
		point n1; point n2;
		findNearestNeighbours(n1, n2, x);
		float y = (((n2.y - n1.y)*(x - n1.x)) / (n2.x - n1.x)) + n1.y;
		return { x,y };
	}
	void printData()
	{
		int i = 0;
		for (point p : dataSet)
		{
			i++;
			std::cout << i << ") ";
			std::cout << p.x << "; " << p.y << "\n";
		}
	}
};

