#pragma once

#include <Graphics/Debugger.h>
#include <Graphics/Texture.h>
#include <Graphics/BaseMaterial.h>
#include <Graphics/Material.h>
#include <Graphics/SkyBoxMaterial.h>


class ReflectiveMaterial : public BaseMaterial
{

private:
	glm::vec4 baseColor;
	glm::vec4 ambientColor;

public:

	Texture* diffuseTexture;
	Texture* specularTexture;
	Texture* alphaMask;

	CubeMapTexture* skyBoxTexture;

	AmbientType ambientType;

	float ambientValue;
	float specularValue;
	float shininess = 32;
	float alphaCutoffThreshold = 0.5f;

	bool useMaskTexture = false;

	glm::vec2 textureTiling = glm::vec2(1.0f);

	ReflectiveMaterial();
	ReflectiveMaterial(const ReflectiveMaterial& material);
	~ReflectiveMaterial();

	void ResetMaterial();
	float GetSpecularValue();
	glm::vec4 GetBaseColor();
	glm::vec4 GetAmbientColor();

	void SetBaseColor(glm::vec4 color);
	void SetAmbientColor(glm::vec4 color);

	// Inherited via BaseMaterial
	void UpdateMaterial(Shader* shader) override;
	void ResetMaterial(Shader* shader) override;

	// Inherited via BaseMaterial
	BaseMaterial* CloneMaterial() override;
};

