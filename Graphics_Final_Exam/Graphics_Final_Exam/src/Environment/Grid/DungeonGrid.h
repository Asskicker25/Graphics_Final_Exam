#pragma once

struct Rect
{
	int x, y, w, h;
};

static float unitSize = 0.5f;

class DungeonGrid
{
public:

    DungeonGrid();
    
    static DungeonGrid& GetInstance();
    static Rect layout[50];

    void SetGridTrue(int x, int y);

    void PrintGrid();
    bool IsGridOccupied(int x, int y);
    
private:

    void UpdateLayoutWithOffset(float x, float y);
    bool grid[35][35] = { false };
};

