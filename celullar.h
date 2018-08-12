﻿#pragma once

#include <vector>
#include <memory>
#include <queue>
#include <time.h>

class Cellular
{
	std::unique_ptr<bool[]> map;
	int width, height, size, chanceToStartAlive;
	unsigned int seed;
public:
	Cellular(
		const int & width,
		const int & height,
		const int & chanceToStartAlive = 44,
		const int & smoothingIterations = 4,
		const unsigned int & seed = time(nullptr),
		const int & wallThreshold = 50,
		const int & roomthreshold = 50)
		:
		width(width),
		height(height),
		size(height * width),
		chanceToStartAlive(chanceToStartAlive),
		seed(seed)
	{
		map = std::make_unique<bool[]>(size);

		Generate();
		for (int k = 0; k <= smoothingIterations; k++)
			Smooth();
	}
	auto GetMap() const { return map.get(); }

private:
	inline void Generate()
	{
		// Seed the random-number generator with the current time so that
		// the numbers will be different every time we run.
		srand(seed);

		for (int index = 0; index < size; index++)
			map[index] = rand() % 100 + 1 < chanceToStartAlive;
	}
	// Iterates through every tile in the map and decides if needs to be born, die, or remain unchanged
	inline void Smooth()
	{
		for (int index = 0; index < size; index++)
		{
			int newVal = countAliveNeighbours(index);
			if (map[index])
				map[index] = !(newVal < 3);
			else
				map[index] = newVal > 4;
		}
	}
	// Counts the number of "alive" cells around the target cell
	inline int8_t countAliveNeighbours(const int & index) const
	{
		int8_t count = 0;
		int x = index / width, y = index % width;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				int neighbour = (x + i) * width + (y + j);

				/*
				Count the neighbour as "alive" if:
				- it is within the map boundaries
				- was already deemed "alive"
				- is not the target cell
				*/
				if ((IsInBounds(neighbour) && map[neighbour]) && !(i == 0 && j == 0))
					count++;
			}
		}
		return count;
	}
	// Determines whether a cell is within the map
	inline constexpr bool IsInBounds(const int & index) const
	{
		return index >= 0 && index < size;
	}
};