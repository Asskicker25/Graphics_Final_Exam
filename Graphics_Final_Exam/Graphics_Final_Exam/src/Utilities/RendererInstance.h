#pragma once

#include <Graphics/Renderer.h>
#include <Graphics/LightManager.h>

class RendererInstance
{
private:
	Renderer* renderer;

public:

	Shader* moonShader;
	Shader* alphaCutOutShader;
	Shader* alphaBlendShader;
	Shader* reflectionShader;
	LightManager* lightManager;

	SkyBoxMaterial* skyMaterial;

	RendererInstance();

	static RendererInstance& GetInstance();
	void SetRenderer(Renderer* renderer);
	Renderer* GetRenderer();
	
};