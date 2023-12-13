#include "Floor.h"
#include "../Grid/DungeonGrid.h"

#include "../../Utilities/Random.h"

Floor::Floor()
{
	floor1 = new Model();
	floor2 = new Model();
	floor3 = new Model();
	floor4 = new Model();

	wall1Left = new Model();
	wall1Right = new Model();
	wall1Bottom = new Model();
	wall1Top = new Model();

	wall2Left = new Model();
	wall2Right = new Model();
	wall2Bottom = new Model();
	wall2Top = new Model();

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

	floor1->LoadModel("Assets/Models/Floor/SM_Env_Dwarf_Floor_02.ply");
	floor2->LoadModel("Assets/Models/Floor/SM_Env_Dwarf_Floor_17.ply");
	floor3->LoadModel("Assets/Models/Floor/SM_Env_Dwarf_Floor_06.ply");
	floor4->LoadModel("Assets/Models/Floor/SM_Env_Dwarf_Floor_09.ply");

	floor1->transform.SetScale(glm::vec3(0.001f));
	floor2->transform.SetScale(glm::vec3(0.001f));
	floor3->transform.SetScale(glm::vec3(0.001f));
	floor4->transform.SetScale(glm::vec3(0.001f));

	wall1Left->LoadModel("Assets//Models/Walls/SM_Env_Dwarf_Wall_01.ply");
	wall1Left->transform.SetScale(glm::vec3(0.001f));
	wall1Left->transform.SetRotation(glm::vec3(0, -90, 0));

	wall1Right->CopyFromModel(*wall1Left);
	wall1Right->transform.SetRotation(glm::vec3(0, 90, 0));

	wall1Top->CopyFromModel(*wall1Left);
	wall1Top->transform.SetRotation(glm::vec3(0, 180, 0));

	wall1Bottom->CopyFromModel(*wall1Left);
	wall1Bottom->transform.SetRotation(glm::vec3(0, 0, 0));

	wall2Left->LoadModel("Assets//Models/Walls/SM_Env_Dwarf_Wall_02.ply");
	wall2Left->transform.SetScale(glm::vec3(0.001f));
	wall2Left->transform.SetRotation(glm::vec3(0, -90, 0));
		
	wall2Right->CopyFromModel(*wall2Left);
	wall2Right->transform.SetRotation(glm::vec3(0, 90, 0));
		
	wall2Top->CopyFromModel(*wall2Left);
	wall2Top->transform.SetRotation(glm::vec3(0, 180, 0));
		
	wall2Bottom->CopyFromModel(*wall2Left);
	wall2Bottom->transform.SetRotation(glm::vec3(0, 0, 0));

}

void Floor::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

void Floor::Load()
{

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
				int random = GetRandomIntNumber(0, 3);

				switch (random)
				{
				case 0:
					SetCurrentModel(floor1);
					break;
				case 1:
					SetCurrentModel(floor2);
					break;
				case 2:
					SetCurrentModel(floor3);
					break;
				case 3: 
					SetCurrentModel(floor4);
					break;
				}

				DungeonGrid::GetInstance().SetGridTrue(floor.x + j, floor.y + i);

				AddModelPos({ floor.x * unitSize + j * unitSize, 0.0f, floor.y * unitSize + i * unitSize });
			}
		}
	}

	DungeonGrid().GetInstance().PrintGrid();

	/*SetCurrentModel("Assets/Models/Walls/SM_Env_Dwarf_Wall_01.ply",
		glm::vec3(0.0f, 0.0f, 0.0f));*/


	for (int i = 0; i < 35; i++)
	{
		for (int j = 0; j < 35; j++)
		{
			if (!DungeonGrid::GetInstance().IsGridOccupied(j, i)) continue;

			int random = 0;

			if (!DungeonGrid::GetInstance().IsGridOccupied(j, i - 1))
			{
				if (random == 0)
				{
					SetCurrentModel(wall1Top);
				}
				else if (random == 1)
				{
					SetCurrentModel(wall2Top);
				}

				AddModelPos({
					j * unitSize - unitSize, 0.0f, (i - 1) * unitSize
					});
			}

			if (!DungeonGrid::GetInstance().IsGridOccupied(j, i + 1))
			{
				if (random == 0)
				{
					SetCurrentModel(wall1Bottom);
				}
				else if (random == 1)
				{
					SetCurrentModel(wall2Bottom);
				}

				AddModelPos({
					j * unitSize, 0.0f, (i + 1) * unitSize - unitSize
					});
			}

			if (!DungeonGrid::GetInstance().IsGridOccupied(j - 1, i))
			{
				if (random == 0)
				{
					SetCurrentModel(wall1Left);
				}
				else if (random == 1)
				{
					SetCurrentModel(wall2Left);
				}

				AddModelPos({
					(j - 1) * unitSize, 0.0f, i * unitSize
					});
			}

			if (!DungeonGrid::GetInstance().IsGridOccupied(j + 1, i))
			{
				if (random == 0)
				{
					SetCurrentModel(wall1Right);
				}
				else if (random == 1)
				{
					SetCurrentModel(wall2Right);
				}

				AddModelPos({
					(j + 1) * unitSize - unitSize, 0.0f, i * unitSize - unitSize
					});
			}

		}
	}


	AddToRenderers();
}
