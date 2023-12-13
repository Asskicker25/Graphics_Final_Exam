#pragma once

#include "../../EntityManager/Entity.h"
#include "../../LoaderBase.h"


class Floor : public Entity, public LoaderBase
{

public:
	Model* floor1;
	Model* floor2;
	Model* floor3;
	Model* floor4;


	Model* wall1Left;
	Model* wall1Right;
	Model* wall1Top;
	Model* wall1Bottom;

	Model* wall2Left;
	Model* wall2Right;
	Model* wall2Top;
	Model* wall2Bottom;

	Floor();


	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

	// Inherited via LoaderBase
	void Load() override;
};

