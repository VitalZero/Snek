#pragma once
#include "Board.h"
#include <random>


class Snake
{
private:
	class Segment
	{
	public:
		Segment();
		void InitHead(const Location& loc);
		void InitBody(const Color& newColor);
		void MoveBy(const Location& deltaLoc);
		void Follow(const Segment& next);
		void Draw(Board& brd) const;
		Location GetLocation() const;
	private:
		std::mt19937 rnd;
		std::random_device rd;
		std::uniform_int_distribution<int> colorDist;
		Location loc;
		Color c;
	};
public:
	Snake(const Location& loc, const Board& brd);
	void MoveBy(const Location& deltaLoc);
	void Grow();
	void Draw(Board& brd) const;
	Location GetLocation() const;
	bool SelfCollide(const Location& deltaLoc) const;
private:
	static constexpr int nSegMax = 100;
	static constexpr Color headColor = Colors::Red;
	static constexpr Color bodyColor = Colors::Blue;
	int nSegments = 1;
	Segment segments[nSegMax];
};