#pragma once

#include "../../EntityManager/Entity.h"
#include "../../LoaderBase.h"

class Crystals : public Entity, public LoaderBase
{
public:
	Model* model;

	Crystals();

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

	// Inherited via LoaderBase
	void Load() override;
};

