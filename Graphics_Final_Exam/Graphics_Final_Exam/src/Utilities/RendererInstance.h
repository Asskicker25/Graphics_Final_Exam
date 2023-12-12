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
	LightManager* lightManager;

	RendererInstance();

	static RendererInstance& GetInstance();
	void SetRenderer(Renderer* renderer);
	Renderer* GetRenderer();
	
};