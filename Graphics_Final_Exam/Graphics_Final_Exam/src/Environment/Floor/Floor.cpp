#include "Floor.h"
#include "../Grid/DungeonGrid.h"

Floor::Floor()
{
	InitializeEntity(this);
}

void Floor::Start()
{
	Load();
}

void Floor::Update(float deltaTime)
{
}

void Floor::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	AssignRenderer(renderer, shader);
}

void Floor::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

void Floor::Load()
{
	SetCurrentModel("Assets/Models/Floor/SM_Env_Dwarf_Floor_02.ply",
		glm::vec3(0.0f, 0.0f, 0.0f));

	//Left to Right
	// 
	//Floor

	DungeonGrid::GetInstance().IsGridOccupied(0, 0);

	for (Rect& floor : DungeonGrid::layout)
	{
		for (int i = 0; i < floor.h; i++)
		{
			for (int j = 0; j < floor.w; j++)
			{
				DungeonGrid::GetInstance().SetGridTrue(floor.x + j, floor.y + i);

				AddModelPos({ floor.x * unitSize + j * unitSize, 0.0f, floor.y * unitSize + i * unitSize });
			}
		}
	}

	DungeonGrid().GetInstance().PrintGrid();

	SetCurrentModel("Assets/Models/Walls/SM_Env_Dwarf_Wall_01.ply",
		glm::vec3(0.0f, 0.0f, 0.0f));

	Model* leftWall = new Model("Assets//Models/Walls/SM_Env_Dwarf_Wall_01.ply");
	leftWall->transform.SetRotation(glm::vec3(0, -90, 0));
	leftWall->transform.SetScale(glm::vec3(0.001f));

	Model* topWall = new Model();
	topWall->CopyFromModel(*leftWall);
	topWall->transform.SetRotation(glm::vec3(0, 180, 0));

	Model* rightWall = new Model("Assets//Models/Walls/SM_Env_Dwarf_Wall_01.ply");
	rightWall->CopyFromModel(*leftWall);
	rightWall->transform.SetRotation(glm::vec3(0, 90, 0));

	Model* bottomWall = new Model("Assets//Models/Walls/SM_Env_Dwarf_Wall_01.ply");
	bottomWall->CopyFromModel(*leftWall);
	bottomWall->transform.SetRotation(glm::vec3(0, 0, 0));


	for (int i = 0; i < 35; i++)
	{
		for (int j = 0; j < 35; j++)
		{
			if (!DungeonGrid::GetInstance().IsGridOccupied(j, i)) continue;


			if (!DungeonGrid::GetInstance().IsGridOccupied(j, i - 1))
			{
				SetCurrentModel(topWall);
				AddModelPos({
					j * unitSize - unitSize, 0.0f, (i - 1) * unitSize
					});
			}

			if (!DungeonGrid::GetInstance().IsGridOccupied(j, i + 1))
			{
				SetCurrentModel(bottomWall);
				AddModelPos({
					j * unitSize, 0.0f, (i + 1) * unitSize - unitSize
					});
			}

			if (!DungeonGrid::GetInstance().IsGridOccupied(j - 1, i))
			{
				SetCurrentModel(leftWall);
				AddModelPos({
					(j - 1) * unitSize, 0.0f, i * unitSize
					});
			}

			if (!DungeonGrid::GetInstance().IsGridOccupied(j + 1, i))
			{
				SetCurrentModel(rightWall);
				AddModelPos({
					(j + 1) * unitSize - unitSize, 0.0f, i * unitSize - unitSize
					});
			}

		}
	}


	AddToRenderers();
}
