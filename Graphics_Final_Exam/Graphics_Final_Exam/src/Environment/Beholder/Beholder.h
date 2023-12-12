#pragma once

#include "../../EntityManager/Entity.h"
#include "Beholder.h"

class Beholder : public Entity
{
public:

	Model* model;
	Model* coneModel;
	Model* lightModel;

	glm::vec4 atten = glm::vec4(1.0f, 5.0f, 1.0f, 0.01f);

	Beholder();


private:

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;
};

