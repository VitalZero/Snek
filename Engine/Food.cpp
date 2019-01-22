#include "Food.h"


Food::Food(Board& brd)
	:
	brd(brd),
	rnd(rd()),
	xDist(brd.GetX(), brd.GetGridWidth() - 1),
	yDist(brd.GetY(), brd.GetGridHeight() - 1)
{
	loc = { xDist(rnd), yDist(rnd) };
}

void Food::Respawn()
{
	loc = { xDist(rnd), yDist(rnd) };
}

bool Food::IsEaten(Snake& snek) const
{
	Location newLoc = snek.GetLocation();
	if((newLoc.x == loc.x) && (newLoc.y == loc.y))
		return true;

	return false;
}

void Food::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}
