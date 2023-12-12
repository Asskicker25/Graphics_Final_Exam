#include "Moon.h"
#include "../../Utilities/RendererInstance.h"
#include "../Material/MoonMaterial.h"

Moon::Moon()
{
	model = new Model();

	InitializeEntity(this);
}

void Moon::Start()
{
}

void Moon::Update(float deltaTime)
{
}

void Moon::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	model->LoadModel("Assets/Models/Moon/UV_Sphere_Cylindrical_UIV_Projection_.ply");
	model->transform.SetPosition(glm::vec3(-10, 80, -80));
	model->transform.SetRotation(glm::vec3(90, 90, 0));
	model->transform.SetScale(glm::vec3(8));

	model->meshes[0]->material = new MoonMaterial();
	MoonMaterial* moonMat = (MoonMaterial*)model->meshes[0]->material;
	moonMat->emissionValue = 0.2;
	
	moonMat->diffuseTexture->LoadTexture("Assets/Models/Moon/lroc_color_poles_4k.jpg");

	renderer->AddModel(model, RendererInstance::GetInstance().moonShader);
}

void Moon::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
