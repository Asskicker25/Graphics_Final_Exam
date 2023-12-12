#pragma once

#include "../../EntityManager/Entity.h"
#include "../../LoaderBase.h"

class Torch : public Entity, public LoaderBase
{

public:
	Model* torchLeft;
	Model* torchRight;
	Model* torchTop;
	Model* torchDown;

	Model* bigTorch;

	Model* flame1;
	Model* flame2;

	Model* lightBase;

	float timeStep = 0;
	float flickerSpeed = 5.0f;

	glm::vec4 lightColor = glm::vec4(1.0f, 0.5f, 0.0f, 1.0f);
	glm::vec4 atten = glm::vec4(1.0f, 5.0f, 2.5f, 0.01f);

	std::vector<Model*> listOfFlame;
	std::vector<Light*> listOfLight;

	Torch();

	void ScaleFlame();

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

	// Inherited via LoaderBase
	void Load() override;
};

