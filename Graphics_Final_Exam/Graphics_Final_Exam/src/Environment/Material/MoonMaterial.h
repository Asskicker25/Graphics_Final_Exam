#pragma once

#include <Graphics/Texture.h>
#include <Graphics/Model.h>

class MoonMaterial : public BaseMaterial
{
private:

	glm::vec4 baseColor;

public:
	float emissionValue = 1;

	MoonMaterial();

	Texture* diffuseTexture;

	glm::vec4 GetBaseColor();
	void SetBaseColor(glm::vec4 color);

	// Inherited via BaseMaterial
	void UpdateMaterial(Shader* shader) override;
	void ResetMaterial(Shader* shader) override;
	BaseMaterial* CloneMaterial() override;
};

