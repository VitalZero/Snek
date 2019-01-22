#include "Snake.h"

Snake::Snake(const Location & loc, const Board& brd)
{
	constexpr int nBodyColors = 4;
	constexpr Color bodyColors[nBodyColors] = {
		{10, 100, 32},
		{10, 130, 48},
		{18, 160, 48},
		{10, 139, 48}
	};

	segments[0].InitHead({ loc.x + brd.GetX(), loc.y + brd.GetY()});

	for (int i = 1; i < nSegMax; ++i)
	{
		segments[i].InitBody(bodyColors[(i-1) % nBodyColors]);
	}
}

Location Snake::GetLocation() const
{
	return segments[0].GetLocation();
}

void Snake::MoveBy(const Location & deltaLoc)
{
	for (int i = nSegMax - 1; i > 0; --i)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(deltaLoc);
}

void Snake::Grow()
{
	if (nSegments < nSegMax)
	{
		++nSegments;
	}
}

void Snake::Draw(Board & brd) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		segments[i].Draw(brd);
	}
}

bool Snake::SelfCollide(const Location & deltaLoc) const
{
	bool selfCollide = false;

	for (int i = 1; i < nSegments-1; ++i)
	{
		Location bodyLoc = segments[i].GetLocation();
		Location headLoc = segments[0].GetLocation();

		headLoc.Add(deltaLoc);

		if ((bodyLoc.x == headLoc.x) && (bodyLoc.y == headLoc.y))
		{
			selfCollide = selfCollide | true;
		}
	}
	return selfCollide;
}

Snake::Segment::Segment()
	:
	rnd(rd()),
	colorDist(0, 255),
	loc({0, 0})
{
}

void Snake::Segment::InitHead(const Location & loc)
{
	this->loc = loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(const Color& newColor)
{
	//Color temp( colorDist(rnd)%200, colorDist(rnd)%200, colorDist(rnd));

	c = newColor;
}

void Snake::Segment::MoveBy(const Location & deltaLoc)
{
	assert(abs(deltaLoc.x) + abs(deltaLoc.y) == 1);
	loc.Add(deltaLoc);
}

void Snake::Segment::Follow(const Segment & next)
{
	loc = next.loc;
}

void Snake::Segment::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

Location Snake::Segment::GetLocation() const
{
	return loc;
}
