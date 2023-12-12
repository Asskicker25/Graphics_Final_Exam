#include "Beholder.h"
#include "../../Utilities/RendererInstance.h"

Beholder::Beholder()
{
	model = new Model();
	lightModel = new Model();
	coneModel = new Model();

	InitializeEntity(this);

}

void Beholder::Start()
{
}

void Beholder::Update(float deltaTime)
{
}

void Beholder::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	model->LoadModel("Assets/Models/Beholder/BeholderSketchfab_xyz_n_uv.ply");
	model->transform.SetPosition(glm::vec3(5.45f, 0.3, 4.8f));
	model->transform.SetRotation(glm::vec3(0.0f, -90, 0));
	model->transform.SetScale(glm::vec3(0.1f));

	renderer->AddModel(model, shader);

	coneModel->LoadModel("Assets/Models/Beholder/vision_cone.ply");
	coneModel->transform.SetScale(glm::vec3(0.1f));

	lightModel->LoadModel("res/Models/DefaultSphere.fbx");
	lightModel->transform.SetScale(glm::vec3(0.01f));
	renderer->AddModel(lightModel,shader);


	std::vector<glm::vec3> lightPos;
	std::vector<glm::vec3> lightRot;
	std::vector<glm::vec3> lightColor;
	std::vector<glm::vec3> coneScale;

	lightPos.push_back(glm::vec3(5.454f, 0.386, 4.968f));
	lightPos.push_back(glm::vec3(5.414f, 0.453, 4.717f));
	lightPos.push_back(glm::vec3(5.46f, 0.28, 4.98f));


	lightRot.push_back(glm::vec3(-4, -64, 0));
	lightRot.push_back(glm::vec3(-15, -110, 0));
	lightRot.push_back(glm::vec3(-20, -110, 0));


	lightColor.push_back(glm::vec3(1.0f, 0.8f, 0.2f));
	lightColor.push_back(glm::vec3(1.0f, 0.0f, 0.1f));
	lightColor.push_back(glm::vec3(0.7f, 0.4f, 0.9f));

	coneScale.push_back(glm::vec3(0.1f, 0.1f, 0.17f));
	coneScale.push_back(glm::vec3(0.1f, 0.1f, 0.17f));
	coneScale.push_back(glm::vec3(0.06f, 0.06f, 0.092f));

	int i = 0;
	for (glm::vec3 pos : lightPos)
	{
		Model* lightModel1 = new Model();
		lightModel1->CopyFromModel(*lightModel);
		lightModel1->transform.SetPosition(pos);
		lightModel1->transform.SetRotation(lightRot[i]);
		renderer->AddModel(lightModel1, shader);

		Model* coneModel1 = new Model();
		coneModel1->CopyFromModel(*coneModel);
		coneModel1->transform.SetPosition(pos);
		coneModel1->transform.SetRotation(lightRot[i]);
		coneModel1->transform.SetScale(coneScale[i]);
		coneModel1->meshes[0]->material->AsMaterial()->SetBaseColor(glm::vec4(lightColor[i].x,
			lightColor[i].y, lightColor[i].z, 0.5f));

		renderer->AddModel(coneModel1, RendererInstance::GetInstance().alphaBlendShader);

		Light* light1 = new Light();
		light1->InitializeLight(lightModel1, Spot);
		light1->intensity = 10.0f;
		light1->innerAngle = 2.5;
		light1->outerAngle = 3;
		light1->attenuation = atten;
		light1->SetLightColor(glm::vec4(lightColor[i].x,
			lightColor[i].y, lightColor[i].z, 1.0f));
		RendererInstance::GetInstance().lightManager->AddLight(light1);

		i++;
	}

	

}

void Beholder::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
