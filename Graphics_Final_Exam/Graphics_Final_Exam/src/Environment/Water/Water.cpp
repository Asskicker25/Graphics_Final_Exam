#include "Water.h"
#include "../../Utilities/RendererInstance.h"

Water::Water()
{
	model = new Model();

	InitializeEntity(this);
}

void Water::Start()
{
}

void Water::Update(float deltaTime)
{
}

void Water::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	model->LoadModel("Assets/Models/Water/Water.fbx");
	model->transform.SetPosition(glm::vec3(0,-10,0));
	model->transform.SetScale(glm::vec3(1));
	model->meshes[0]->material->AsMaterial()->SetBaseColor(glm::vec4(0.0f, 0.0f, 1.0f, 0.5f));

	renderer->AddModel(model, RendererInstance::GetInstance().alphaBlendShader);
}

void Water::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
