#include <iostream>
#include <fstream>
#include <locale>
#include <ctime>
#include <string>
#include "multiInterpolator.h"

void interpToCSV();

int main()
{
	srand(time(NULL));
	std::locale::global(std::locale(""));
	interpToCSV();
}

void interpToCSV()
{
	int n = 20;
	multiInterpolator MI(n);
	std::ofstream fOutp("outp.csv");
	std::vector<float> vals = {};
	int ds = MI.getDataSetSize();
	float xMin = MI.getDataPoint(0).x;
	float xMax = MI.getDataPoint(ds-1).x;
	float dsR = (float)ds * 100.0f;
	float step = (xMax - xMin) / dsR;
	MI.prepSpline();
	for (int i = 0; i < dsR; i++)
	{
		//clear
		vals.clear();

		//interp with all methods
		float cx = xMin + i * step;
		vals.push_back(cx);
		float cy = MI.nativeFunction(cx).y;
		vals.push_back(cy);
		      cy = MI.lInterp(cx).y;
		vals.push_back(cy);
		      cy = MI.lagrangeInterp(cx).y;
		vals.push_back(cy);
		      cy = MI.newtonInterp(cx).y;
		vals.push_back(cy);
		      cy = MI.splineInterp(cx).y;
		vals.push_back(cy);
		if (i % 100 == 0)
		std::cout << "OP " << i + 1 << "/" << dsR << "\n";

		//print to file
		for (float cv : vals) fOutp << std::to_string(cv).c_str() << ";";
		fOutp << "\n";
	}
}