#pragma once
#include "Graphics.h"
#include "Location.h"
#include <cassert>

class Board
{
public:
	Board(Graphics& gfx, int x, int y, int border = 0, int padding = 0);
	void DrawCell(const Location& loc,const Color& c);
	void DrawBoard(const Color& c);
	void DrawBorder();
	int GetGridWidth() const;
	int GetGridHeight() const;
	int GetX() const;
	int GetY() const;
	bool IsInsideBoard(const Location& loc) const;
private:
	static constexpr int dimension = 20;
	static constexpr int width = 35;
	static constexpr int height = 25;
	int padding = 0;
	int border = 0;
	int x = 0;
	int y = 0;
	Graphics& gfx;
};