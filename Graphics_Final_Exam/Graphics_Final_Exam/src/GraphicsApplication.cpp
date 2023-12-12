#include "GraphicsApplication.h"
#include "EntityManager/EntityManager.h"
#include "Environment/Terrain/Terrain.h"
#include "Environment/Floor/Floor.h"

void GraphicsApplication::SetUp()
{
	moveSpeed = 1;

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


	Terrain* terrain = new Terrain();
	Floor* floor = new Floor();

	EntityManager().GetInstance().Start();

}

void GraphicsApplication::PreRender()
{
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
