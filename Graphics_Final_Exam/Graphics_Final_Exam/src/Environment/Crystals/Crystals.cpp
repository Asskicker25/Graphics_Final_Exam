#include "Crystals.h"
#include "../../Utilities/RendererInstance.h"
#include "../Material/ReflectiveMaterial.h"

Crystals::Crystals()
{
	model = new Model();
	InitializeEntity(this);
}

void Crystals::Start()
{
}

void Crystals::Update(float deltaTime)
{
}

void Crystals::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{

	model->LoadModel("Assets/Models/Crystals/SM_Env_Crystals_Cluster_Large_01.ply");
	model->transform.SetScale(glm::vec3(0.001f));
	model->transform.SetPosition(glm::vec3(0.5f, 0, 0.5f));

	model->meshes[0]->material = new ReflectiveMaterial();
	ReflectiveMaterial* mat = (ReflectiveMaterial*)model->meshes[0]->material;

	mat->showReflection = true;
	mat->reflectValue = 1;
	mat->SetBaseColor(glm::vec4(0.5, 0, 0.5, 0.5));


	std::vector<glm::vec3> pos;
	std::vector<glm::vec4> color;

	pos.push_back(glm::vec3(0.5f, 0, 0.5f));
	pos.push_back(glm::vec3(8.2f, 0, 4.87f));
	pos.push_back(glm::vec3(10.4f, 0, 0.73f));
	pos.push_back(glm::vec3(11.15f, 0, 4.77f));

	color.push_back(glm::vec4(0.2, 0.8, 0.3, 0.5f));
	color.push_back(glm::vec4(0.2, 0.2, 0.8, 0.5f));
	color.push_back(glm::vec4(0.3, 0.5, 0.6, 0.5f));
	color.push_back(glm::vec4(0.8, 0.2, 0.2, 0.5f));

	for (int i = 0; i < pos.size(); i++)
	{
		Model* crystal = new Model();
		crystal->CopyFromModel(*model);

		crystal->transform.SetPosition(pos[i]);
		((ReflectiveMaterial*) (crystal->meshes[0]->material))->SetBaseColor (color[i]);
		renderer->AddModel(crystal, RendererInstance::GetInstance().reflectionShader);
	}

}

void Crystals::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}

