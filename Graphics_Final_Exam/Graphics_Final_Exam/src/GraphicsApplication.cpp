#include "GraphicsApplication.h"
#include "EntityManager/EntityManager.h"
#include "Environment/Terrain/Terrain.h"
#include "Environment/Floor/Floor.h"
#include "Environment/Moon/Moon.h"
#include "Utilities/RendererInstance.h"
#include "Environment/Torch/Torch.h"
#include "Environment/Water/Water.h"
#include "Environment/Beholder/Beholder.h"
#include "Environment/Crystals/Crystals.h"

void GraphicsApplication::SetUp()
{
	moveSpeed = 5;

	camera->InitializeCamera(PERSPECTIVE, windowWidth, windowHeight, 0.01f, 1000.0f, 45.0f);

	/*camera->transform.SetPosition(glm::vec3(-0.1, 0.3, 0.7));
	camera->transform.SetRotation(glm::vec3(-10, 96, 0));*/

	/*camera->transform.SetPosition(glm::vec3(5.0f, 1.8f, 5.9f));
	camera->transform.SetRotation(glm::vec3(-56, 1.7, 0));*/

	camera->transform.SetPosition(glm::vec3(2.9f, 9.2f, 10.2f));
	camera->transform.SetRotation(glm::vec3(-50,-30, 0));
	
	/*camera->transform.SetPosition(glm::vec3(10, 3, 11));
	camera->transform.SetRotation(glm::vec3(-53, -1, 0));*/

	EntityManager::GetInstance().AddToRendererAndPhysics(&renderer, &defShader, &physicsEngine);

#pragma region Skybox

	skyBox->meshes[0]->material = new SkyBoxMaterial();
	SkyBoxMaterial* skyboxMat = skyBox->meshes[0]->material->AsSkyBoxMaterial();

	skyboxMat->skyBoxTexture->LoadTexture({
		"Assets/Textures/Skybox/Right.jpg",
		"Assets/Textures/Skybox/Left.jpg",
		"Assets/Textures/Skybox/Up.jpg",
		"Assets/Textures/Skybox/Down.jpg",
		"Assets/Textures/Skybox/Front.jpg",
		"Assets/Textures/Skybox/Back.jpg",
		});

#pragma endregion

#pragma region Shader

	moonShader = new Shader("Assets/Shader/Moon.shader");
	moonShader->applyInverseModel = false;
	moonShader->blendMode = OPAQUE;
	Debugger::Print("MoonShaderID : ", moonShader->GetShaderId());

	reflectionShader = new Shader("Assets/Shader/Reflection.shader");
	reflectionShader->applyInverseModel = false;
	reflectionShader->blendMode = ALPHA_BLEND;
	Debugger::Print("ReflectionShaderID: ", reflectionShader->GetShaderId());

#pragma endregion


#pragma region Light

	Model* lightModel = new Model("res/Models/DefaultSphere.fbx", false);
	lightModel->transform.SetScale(glm::vec3(0.01f));
	//renderer.AddModel(lightModel, &solidColorShader);

	Light* pointLight = new Light();
	pointLight->InitializeLight(lightModel, Point);
	pointLight->intensity = 2.5f;
	pointLight->attenuation = glm::vec4(1.0f,0.5f,0.2f,0.1f);
	pointLight->transform->SetPosition(glm::vec3(9, 3, 5));
	pointLight->SetLightColor(glm::vec4(0.5f, 0.4f, 0.3f, 1.0f));

	Model* dirLightModel = new Model("res/Models/DefaultSphere.fbx", false);
	dirLightModel->transform.SetScale(glm::vec3(0.01f));
	//renderer.AddModel(lightModel, &solidColorShader);

	Light* dirLight = new Light();
	dirLight->InitializeLight(dirLightModel, Directional);
	dirLight->intensity = 0.22f;
	dirLight->SetLightColor(glm::vec4(1.0f,1.0f,1.0f,1.0f));


	lightManager.AddLight(dirLight);
	lightManager.AddLight(pointLight);
	lightManager.AddShader(reflectionShader);

#pragma endregion

	RendererInstance::GetInstance().SetRenderer(&renderer);
	RendererInstance::GetInstance().moonShader = moonShader;
	RendererInstance::GetInstance().reflectionShader = reflectionShader;
	RendererInstance::GetInstance().alphaCutOutShader = &alphaCutOutShader;
	RendererInstance::GetInstance().alphaBlendShader = &alphaBlendShader;
	RendererInstance::GetInstance().lightManager = &lightManager;
	RendererInstance::GetInstance().skyMaterial = skyboxMat;

	Terrain* terrain = new Terrain();
	Floor* floor = new Floor();
	Moon* moon = new Moon();
	Torch* torch = new Torch();
	Crystals* crystals = new Crystals;
	Water* water = new Water();
	Beholder* beholder = new Beholder();

	EntityManager().GetInstance().Start();

}

void GraphicsApplication::PreRender()
{

	moonShader->Bind();
	moonShader->SetUniformMat("projection", camera->GetMatrix());
	moonShader->SetUniformMat("view", view);
	//moonShader->SetUniform3f("viewPos", camera->transform.position.x, camera->transform.position.y,
	//	camera->transform.position.z);

	reflectionShader->Bind();
	reflectionShader->SetUniformMat("projection", camera->GetMatrix());
	reflectionShader->SetUniformMat("view", view);
	reflectionShader->SetUniform3f("viewPos", camera->transform.position.x, camera->transform.position.y,
		camera->transform.position.z);

	EntityManager().GetInstance().Update(Timer::GetInstance().deltaTime);
}

void GraphicsApplication::PostRender()
{
}

void GraphicsApplication::ProcessInput(GLFWwindow* window)
{
	std::stringstream ssTitle;
	ssTitle << "Camera Pos : "
		<< camera->transform.position.x << " , "
		<< camera->transform.position.y << " , "
		<< camera->transform.position.z
		<< "  Camera Pitch : "
		<< camera->transform.rotation.x
		<< "  Camera Yaw : "
		<< camera->transform.rotation.y
		<< "  Camera Z : "
		<<camera->transform.rotation.z;

	std::string theTitle = ssTitle.str();


	glfwSetWindowTitle(window, theTitle.c_str());
}

void GraphicsApplication::KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods)
{
}

void GraphicsApplication::MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods)
{
}
