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
	model->LoadModel()
}

void Terrain::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
