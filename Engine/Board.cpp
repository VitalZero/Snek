#include "Board.h"

Board::Board(Graphics & gfx, int x, int y, int border, int padding)
	:
	gfx(gfx)
{
	this->x = x;
	this->y = y;
	this->padding = padding;
	this->border = border;
}

void Board::DrawCell(const Location & loc, const Color& c)
{
	assert(loc.x >= x);
	assert(loc.x < (width + x));
	assert(loc.y >= y);
	assert(loc.y < (height + y));

	gfx.DrawRectDim((loc.x * dimension) + padding + border, (loc.y * dimension) + padding + border, dimension-(padding*2), dimension- (padding*2) , c);
}

void Board::DrawBoard(const Color & c)
{
	for (int j = y; j < (height + y); ++j)
	{
		for (int i = x; i < (width + x); ++i)
		{
			//brd.DrawCell({ i, j }, (j%2==0) ? ((i % 2) ? Colors::LightGray : Colors::Cyan) : (i % 2 == 0) ? Colors::LightGray : Colors::Cyan, 1);
			DrawCell({ i ,j }, c);
		}
	}
}

void Board::DrawBorder()
{
	int x0 = x * dimension;
	int y0 = y * dimension;
	int x1 = ((width) * dimension);
	int y1 = ((height) * dimension);
	Color borderColor(120, 120, 200);

	//arriba
	gfx.DrawRectDim(x0, y0, x1+border, border, borderColor);
	//abajo
	gfx.DrawRectDim(x0, (y0 + y1)+border, x1+border, border, borderColor);

	//izquierda
	gfx.DrawRectDim(x0, y0, border, y1+border, borderColor);
	//derecha
	gfx.DrawRectDim((x0 + x1)+border, y0, border, y1+(border*2), borderColor);

}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

int Board::GetX() const
{
	return x;
}

int Board::GetY() const
{
	return y;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x >= x && loc.x < (width + x) &&
		loc.y >= y && loc.y < (height + y) ;
}

