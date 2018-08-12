#include "celullar.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>

using namespace std;

int main()
{
	double diff = 0;
	clock_t launch = clock();
	const int mapXSize = 100, mapYSize = 450;
	Cellular c(mapXSize, mapYSize, 45, 6, 1);
	clock_t done = clock();
	diff = done - launch;
	auto map = c.GetMap();
	for (int y = 1; y <= mapXSize * mapYSize; y++)
	{
		std::clog << (map[y - 1] ? "X" : " ");
		if (y % mapXSize == 0)
			std::clog << std::endl;
	}
	cout << diff << " ms" << std::endl;
	diff = 0;

	for (int i = 0; i < 121; i++)
	{
		clock_t launch = clock();

		Cellular c(mapXSize, mapYSize, 45, 6, 1);

		clock_t done = clock();
		diff += done - launch;
	}
	cout << diff / 120 << " ms averaged 120 runs" << std::endl;
	cin.get();
	return 0;
}