#include "Water.h"
#include "../Material/ReflectiveMaterial.h"
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
	model->LoadModel("Assets/Models/Water/Water_UV.ply");
	model->transform.SetPosition(glm::vec3(10.75,0.2f,9.2f));
	model->transform.SetScale(glm::vec3(0.0097f,0.005f,0.01f));

	model->meshes[0]->material = new ReflectiveMaterial();
	ReflectiveMaterial* mat = (ReflectiveMaterial*)model->meshes[0]->material;

	mat->textureTiling = glm::vec2(10, 20);
	mat->diffuseTexture->LoadTexture("Assets/Models/Water/Water.jpg");
	mat->SetBaseColor(glm::vec4(1.0f, 1.0f, 1.0f,0.6f));

	renderer->AddModel(model, RendererInstance::GetInstance().reflectionShader);
}

void Water::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
