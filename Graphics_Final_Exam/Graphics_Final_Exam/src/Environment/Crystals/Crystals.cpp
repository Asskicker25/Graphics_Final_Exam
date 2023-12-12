#include "Crystals.h"
#include "../../Utilities/RendererInstance.h"

Crystals::Crystals()
{
	model = new Model();
	InitializeEntity(this);
}

void Crystals::Start()
{
	Load();
}

void Crystals::Update(float deltaTime)
{
}

void Crystals::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	AssignRenderer(renderer, RendererInstance::GetInstance().reflectionShader);

	model->LoadModel("Assets/Models/Crystals/SM_Env_Crystals_Cluster_Large_01.ply");
	model->transform.SetScale(glm::vec3(0.001f));
	model->meshes[0]->material->AsMaterial()->SetBaseColor(glm::vec4(0.5, 0, 0.5, 0.5));

}

void Crystals::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

void Crystals::Load()
{
	SetCurrentModel(model);

	AddModelPos({ 0.5f,0,0.5f });
	AddModelPos({ 8.2f,0,4.87f });
	AddModelPos({ 10.4f,0,0.73f });
	AddModelPos({ 11.15f,0,4.77f });

	AddToRenderers();
}
