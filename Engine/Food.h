#pragma once
#include <random>
#include "Board.h"
#include "Location.h"
#include "Snake.h"

class Food
{
public:
	Food(Board& brd);
	void Respawn();
	bool IsEaten(Snake& snek) const;
	void Draw(Board& brd) const;
private:
	Board& brd;
	std::mt19937 rnd;
	std::random_device rd;
	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> yDist;
	static constexpr Color c = Colors::Yellow;
	Location loc;
};