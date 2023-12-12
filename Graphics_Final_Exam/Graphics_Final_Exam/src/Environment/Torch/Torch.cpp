#include <Graphics/Light.h>
#include <Graphics/Timer.h>

#include "Torch.h"
#include "../Grid/DungeonGrid.h"
#include "../../Utilities/RendererInstance.h"
#include <Graphics/LightManager.h>
#include "../../Utilities/Remap.h"
#include <glm/glm.hpp>

Torch::Torch()
{
	torchLeft = new Model();
	torchRight = new Model();
	torchTop = new Model();
	torchDown = new Model();
	lightBase = new Model();
	flame1 = new Model();

	InitializeEntity(this);
}



void Torch::Start()
{
	Load();
}

void Torch::Update(float deltaTime)
{
	ScaleFlame();
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

	flame1->LoadModel("Assets/Models/Torch/Fire 1.fbx");
	flame1->meshes[0]->material->AsMaterial()->alphaMask->
		LoadTexture("Assets/Models/Torch/Fire 1.fbm/Fire_Alpha.png");
	flame1->meshes[0]->material->AsMaterial()->useMaskTexture = true;
	flame1->transform.SetScale(glm::vec3(0.002f));
	flame1->transform.SetRotation(glm::vec3(0,0,0));

		
}

void Torch::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

void Torch::ScaleFlame()
{
	if (listOfFlame.size() == 0) return;

	timeStep += Timer::GetInstance().deltaTime;
	float varyingIntensity = sin(timeStep * flickerSpeed);

	float scaleAddValue = varyingIntensity * 0.1f * 0.0001f;
	float lightAddValue = varyingIntensity * 0.01f;

	float scale = listOfFlame[0]->transform.scale.x + scaleAddValue;
	scale = glm::clamp(scale, 0.0f, 1.0f);

	int i = 0;
	for (Model* model : listOfFlame)
	{
		
		model->transform.SetScale(glm::vec3(scale));

		listOfLight[i]->intensity += lightAddValue;
		i++;
	}

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
	std::vector<glm::vec3>  flamePos;
	std::vector<glm::vec3>  flameRot;

	glm::vec3 lightPos1 = glm::vec3(pos1.x + 0.05f, pos1.y + 0.05f, pos1.z);
	glm::vec3 lightPos2 = glm::vec3(pos2.x, pos2.y + 0.05f, pos2.z + 0.05f);
	glm::vec3 lightPos3 = glm::vec3(pos3.x, pos3.y + 0.05f, pos3.z + 0.05f);
	lightPos.push_back(lightPos1);
	lightPos.push_back(lightPos2);
	lightPos.push_back(lightPos3);

	flamePos.push_back(lightPos1 + glm::vec3(-0.01f, -0.01f, 0));
	flamePos.push_back(lightPos2 + glm::vec3(0, -0.01f, -0.01f));
	flamePos.push_back(lightPos2 + glm::vec3(0, -0.01f, -0.01f));

	flameRot.push_back(glm::vec3(0, 0, -25));
	flameRot.push_back(glm::vec3(25, 0, 0));
	flameRot.push_back(glm::vec3(25, 0, 0));

	int i = 0;
	for (glm::vec3& pos : lightPos)
	{
		Model* flame = new Model();
		flame->CopyFromModel(*flame1);
		flame->transform.SetPosition(flamePos[i]);
		flame->transform.SetRotation(flameRot[i]);
		renderer->AddModel(flame, RendererInstance::GetInstance().alphaCutOutShader);

		listOfFlame.push_back(flame);

		Model* lightModel1 = new Model();
		lightModel1->CopyFromModel(*lightBase);
		lightModel1->transform.SetPosition(pos);
		//renderer->AddModel(lightModel1, shader);


		Light* light1 = new Light();
		light1->InitializeLight(lightModel1, Point);
		light1->SetLightColor(lightColor);
		light1->attenuation = atten;
		light1->intensity = 1.5f;
		RendererInstance::GetInstance().lightManager->AddLight(light1);

		listOfLight.push_back(light1);

		i++;
	}

#pragma endregion


}
