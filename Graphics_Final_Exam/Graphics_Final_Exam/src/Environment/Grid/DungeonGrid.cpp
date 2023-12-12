#include "DungeonGrid.h"
#include <iostream>

Rect DungeonGrid::layout[] =
{
       {-2, 1, 5, 3},
       {-4, 1, 1, 1},
       {4, 1, 1, 1},
       {-5, -3, 3, 3},
       {3, -3, 3, 3},
       {-8, -1, 2, 1},
       {7, -3, 4, 5},
       {-12, -2, 3, 3},
       {7, 3, 1, 1},
       {4, 3, 2, 1},
       {4, 5, 3, 4},
       {-2, 6, 5, 3},
       {8, 6, 5, 3},
       {8, 10, 1, 1},
       {10, 10, 1, 1},
       {8, 12, 5, 7},
       {0, 0, 1, 1},
       {-3, 1, 1, 1},
       {3, 1, 1, 1},
       {-4, 0, 1, 1},
       {4, 0, 1, 1},
       {-6, -1, 1, 1},
       {6, -1, 1, 1},
       {-9, -1, 1, 1},
       {7, 2, 1, 1},
       {6, 3, 1, 1},
       {5, 4, 1, 1},
       {3, 7, 1, 1},
       {7, 7, 1, 1},
       {8, 9, 1, 1},
       {9, 10, 1, 1},
       {10, 11, 1, 1},
       {10, 19, 1, 1},
       {3, 3, 1, 1}
};

DungeonGrid::DungeonGrid()
{
    UpdateLayoutWithOffset(12, 3);
}

DungeonGrid& DungeonGrid::GetInstance()
{
	static DungeonGrid instance;
	return instance;
}

void DungeonGrid::SetGridTrue(int x, int y)
{
    grid[x][y] = true;
}

void DungeonGrid::PrintGrid()
{
    for (int i = 0; i < 35; i++)
    {
        for (int j = 0; j < 35; j++)
        {
            if (grid[j][i] == true)
            {
                std::cout << "X";
            }
            else
            {
                std::cout << "_";
            }
        }
        std::cout << std::endl;
    }
}

bool DungeonGrid::IsGridOccupied(int x, int y)
{
    if (x < 0 || y < 0)
    {
        return false;
    }

    return grid[x][y];
}

void DungeonGrid::UpdateLayoutWithOffset(float x, float y)
{
    for (Rect& rect : layout)
    {
        rect.x += x;
        rect.y += y;
    }
}

