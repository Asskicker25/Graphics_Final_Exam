#include <Graphics/Light.h>

#include "Torch.h"
#include "../Grid/DungeonGrid.h"
#include "../../Utilities/RendererInstance.h"
#include <Graphics/LightManager.h>

Torch::Torch()
{
	torchLeft = new Model();
	torchRight = new Model();
	torchTop = new Model();
	torchDown = new Model();
	lightBase = new Model();

	InitializeEntity(this);
}

void Torch::Start()
{
	Load();
}

void Torch::Update(float deltaTime)
{
}

void Torch::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	AssignRenderer(renderer, RendererInstance::GetInstance().alphaCutOutShader);

	lightBase->LoadModel("res/Models/DefaultSphere.fbx");
	lightBase->transform.SetScale(glm::vec3(0.01f));

	torchLeft->LoadModel("Assets/Models/Torch/SM_Prop_Dwarf_Torch_01.fbx");
	torchLeft->transform.SetScale(glm::vec3(0.001f));
	torchLeft->transform.SetRotation(glm::vec3(0, -90, 0));

	torchRight->CopyFromModel(*torchLeft);
	torchRight->transform.SetRotation(glm::vec3(0, 90, 0));

	torchTop->CopyFromModel(*torchLeft);
	torchTop->transform.SetRotation(glm::vec3(0, 180, 0));
}

void Torch::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

void Torch::Load()
{
	SetCurrentModel(torchLeft);

	glm::vec3 pos1 = { -0.9f * unitSize, unitSize * 0.5f + 0.1f, 1 * unitSize + unitSize * 0.5f };
	glm::vec3 pos2 = { 4.0f * unitSize, unitSize * 0.5f, 1.1f * unitSize };
	glm::vec3 pos3 = { 7.0f * unitSize + unitSize, unitSize * 0.5f, -1.1f * unitSize };

	AddModelPos({ pos1.x,pos1.y,pos1.z });

	SetCurrentModel(torchTop);
	AddModelPos({ pos2.x,pos2.y,pos2.z });
	AddModelPos({ pos3.x,pos3.y,pos3.z });

	AddToRenderers();



#pragma region Light


	std::vector<glm::vec3>  lightPos;

	lightPos.push_back(glm::vec3(pos1.x + 0.05f, pos1.y + 0.05f, pos1.z));
	lightPos.push_back(glm::vec3(pos2.x, pos2.y + 0.05f, pos2.z + 0.05f));
	lightPos.push_back(glm::vec3(pos3.x, pos3.y + 0.05f, pos3.z + 0.05f));


	for (glm::vec3& pos : lightPos)
	{
		Model* lightModel1 = new Model();
		lightModel1->CopyFromModel(*lightBase);
		lightModel1->transform.SetPosition(pos);
		renderer->AddModel(lightModel1, shader);

		Light* light1 = new Light();
		light1->InitializeLight(lightModel1, Point);
		light1->SetLightColor(lightColor);
		light1->attenuation = atten;
		light1->intensity = 1.5f;
		RendererInstance::GetInstance().lightManager->AddLight(light1);

	}

#pragma endregion


}
