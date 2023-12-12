#include "Terrain.h"

Terrain::Terrain()
{
	model = new Model();

	InitializeEntity(this);
}

void Terrain::Start()
{
}

void Terrain::Update(float deltaTime)
{
}

void Terrain::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	model->LoadModel("Assets/Models/TerrianFinal.ply");
	model->transform.SetPosition(glm::vec3(825, -0.05f, 500.0f));
	model->transform.SetRotation(glm::vec3(0, -60, 0));
	model->transform.SetScale(glm::vec3(10.0f));

	model->meshes[0]->material->AsMaterial()->SetBaseColor(glm::vec4(0.545f, 0.439f, 0.345f,1.0f));
	renderer->AddModel(model, shader);
}

void Terrain::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}


