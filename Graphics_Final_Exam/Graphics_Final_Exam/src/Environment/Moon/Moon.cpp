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
	model->transform.SetPosition(glm::vec3(-10, 50, -50));
	model->transform.SetScale(glm::vec3(5));

	model->meshes[0]->material = new MoonMaterial();
	MoonMaterial* moonMat = (MoonMaterial*)model->meshes[0]->material;
	moonMat->emissionValue = 0.35;
	
	moonMat->diffuseTexture->LoadTexture("Assets/Models/Moon/lroc_color_poles_4k.jpg");

	renderer->AddModel(model, RendererInstance::GetInstance().moonShader);
}

void Moon::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
