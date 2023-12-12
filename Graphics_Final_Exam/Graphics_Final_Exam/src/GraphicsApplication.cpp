#include "GraphicsApplication.h"
#include "EntityManager/EntityManager.h"
#include "Environment/Terrain/Terrain.h"
#include "Environment/Floor/Floor.h"
#include "Environment/Moon/Moon.h"
#include "Utilities/RendererInstance.h"
#include "Environment/Torch/Torch.h"

void GraphicsApplication::SetUp()
{
	moveSpeed = 5;

	camera->InitializeCamera(PERSPECTIVE, windowWidth, windowHeight, 0.1f, 1000.0f, 45.0f);

	camera->transform.SetPosition(glm::vec3(1, 7, 4));
	camera->transform.SetRotation(glm::vec3(-50, 0, 0));

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

#pragma endregion


#pragma region Light

	Model* lightModel = new Model("res/Models/DefaultSphere.fbx", false);
	lightModel->transform.SetScale(glm::vec3(0.01f));
	//renderer.AddModel(lightModel, &solidColorShader);

	Light* dirLight = new Light();
	dirLight->InitializeLight(lightModel, Directional);
	dirLight->intensity = 0.5f;
	dirLight->transform->SetRotation(glm::vec3(-30, 180, 0));

	lightManager.AddLight(dirLight);

#pragma endregion

	RendererInstance::GetInstance().SetRenderer(&renderer);
	RendererInstance::GetInstance().moonShader = moonShader;
	RendererInstance::GetInstance().alphaCutOutShader = &alphaCutOutShader;
	RendererInstance::GetInstance().lightManager = &lightManager;

	Terrain* terrain = new Terrain();
	Floor* floor = new Floor();
	Moon* moon = new Moon();
	Torch* torch = new Torch();

	EntityManager().GetInstance().Start();

}

void GraphicsApplication::PreRender()
{

	moonShader->Bind();
	moonShader->SetUniformMat("projection", camera->GetMatrix());
	moonShader->SetUniformMat("view", view);
	//moonShader->SetUniform3f("viewPos", camera->transform.position.x, camera->transform.position.y,
	//	camera->transform.position.z);

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