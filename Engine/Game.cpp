/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(gfx,2, 2, 2, 1),
	rng(std::random_device()()),
	snek({2, 2}, brd),
	food(brd)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();

	++counter;
	if (!started)
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
			started = true;
	}
	else
	{
		if (!gameOver)
		{
			if (wnd.kbd.KeyIsPressed(VK_RIGHT))
				loc = { 1, 0 };
			if (wnd.kbd.KeyIsPressed(VK_LEFT))
				loc = { -1, 0 };
			if (wnd.kbd.KeyIsPressed(VK_DOWN))
				loc = { 0, 1 };
			if (wnd.kbd.KeyIsPressed(VK_UP))
				loc = { 0, -1 };


			if (counter * dt >= frames * dt)
			{
				/*speedCounter++;
				if (speedCounter >= 60)
				{
					if (frames > 0)
						--frames;

					speedCounter = 0;
				}*/

				Location tempLoc = snek.GetLocation();
				tempLoc.Add(loc);
				gameOver = snek.SelfCollide(loc) || !brd.IsInsideBoard(tempLoc);

				counter = 0;

				if (!gameOver)
				{
					snek.MoveBy(loc);
				}
			}

			bool eaten = food.IsEaten(snek);

			if (eaten)
			{
				if (frames > 0)
					--frames;

				food.Respawn();
				snek.Grow();
				eaten = false;
			}
		}
	}
}

void Game::ComposeFrame()
{
	if (started)
	{
		//brd.DrawBoard(Colors::Gray);
		brd.DrawBorder();
		food.Draw(brd);

		snek.Draw(brd);

		if (gameOver)
			SpriteCodex::DrawGameOver(200, 200, gfx);
	}
	else
		SpriteCodex::DrawTitle(100, 100, gfx);
}
