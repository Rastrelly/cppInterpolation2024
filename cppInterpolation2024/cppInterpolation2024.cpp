#include <iostream>
#include "multiInterpolator.h"

int main()
{
    std::cout << "Input search X:\n";
	float x;
	std::cin >> x;
	multiInterpolator MI(10);
	MI.printData();
	float y = MI.lInterp(x).y;
	point nativeValue = MI.nativeFunction(x);
	std::cout << "Interpolated: " << x << "; " << y << "\n";
	std::cout << "Real: " << nativeValue.x << "; " << nativeValue.y << "\n";
}