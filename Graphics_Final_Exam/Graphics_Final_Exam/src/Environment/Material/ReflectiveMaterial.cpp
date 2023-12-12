#include "ReflectiveMaterial.h"
#include "../../Utilities/RendererInstance.h"

ReflectiveMaterial::ReflectiveMaterial()
{
    ambientType = AmbientType::Value;
    ambientColor = glm::vec4(1.0f);
    baseColor = glm::vec4(1.0f);

	diffuseTexture = new Texture("res/Textures/DefaultTextures/Diffuse_Default.png");
	specularTexture = new Texture("res/Textures/DefaultTextures/Specular_Default.jpg");
	alphaMask = new Texture("res/Textures/DefaultTextures/Opacity_Default.png");

	skyBoxTexture = RendererInstance::GetInstance().skyMaterial->skyBoxTexture;

    ResetMaterial();
}

ReflectiveMaterial::ReflectiveMaterial(const ReflectiveMaterial& material)
{
	SetBaseColor(glm::vec4(material.baseColor.x, material.baseColor.y, material.baseColor.z, material.baseColor.w));
	SetAmbientColor(glm::vec4(material.ambientColor.x, material.ambientColor.y, material.ambientColor.z, material.ambientColor.w));
	diffuseTexture = material.diffuseTexture;
	specularTexture = material.specularTexture;
	alphaMask = material.alphaMask;

	ambientType = material.ambientType;
	ambientValue = material.ambientValue;
	specularValue = material.specularValue;
	shininess = material.shininess;
	useMaskTexture = material.useMaskTexture;
	alphaCutoffThreshold = material.alphaCutoffThreshold;
}

ReflectiveMaterial::~ReflectiveMaterial()
{
}

void ReflectiveMaterial::ResetMaterial()
{
	baseColor = glm::vec4(1.0f);
	ambientValue = 1.0f;
	specularValue = 0.5f;
}

float ReflectiveMaterial::GetSpecularValue()
{
    return specularValue;
}

glm::vec4 ReflectiveMaterial::GetBaseColor()
{
    return baseColor;
}

glm::vec4 ReflectiveMaterial::GetAmbientColor()
{
	switch (ambientType)
	{
	case AmbientType::Color:
		return ambientColor;
	case AmbientType::Value:
		return baseColor * ambientValue;
	}
}

void ReflectiveMaterial::SetBaseColor(glm::vec4 color)
{
	baseColor = color;
}

void ReflectiveMaterial::SetAmbientColor(glm::vec4 color)
{
	ambientColor = color;
}

void ReflectiveMaterial::UpdateMaterial(Shader* shader)
{
	shader->Bind();

	shader->SetUniform3f("textureTiling", this->textureTiling.x, this->textureTiling.y, 1.0f);

	shader->SetUniform4f("material.baseColor", this->GetBaseColor().x, this->GetBaseColor().y,
		this->GetBaseColor().z, this->GetBaseColor().w);

	shader->SetUniform4f("material.ambientColor", this->GetAmbientColor().x, this->GetAmbientColor().y,
		this->GetAmbientColor().z, this->GetAmbientColor().w);

	shader->SetUniform1f("material.specularValue", this->GetSpecularValue());
	shader->SetUniform1f("material.shininess", this->shininess);

	shader->SetUniform3f("alphaCutOut", shader->blendMode, this->useMaskTexture, this->alphaCutoffThreshold);

	if (this->diffuseTexture != nullptr)
	{
		this->diffuseTexture->SetTextureSlot(1);
		shader->SetUniform1i("texture_diffuse", 1);
		this->diffuseTexture->Bind();
	}

	if (this->specularTexture != nullptr)
	{
		this->specularTexture->SetTextureSlot(2);
		shader->SetUniform1i("texture_specular", 2);
		this->specularTexture->Bind();
	}

	if (this->alphaMask != nullptr)
	{
		this->alphaMask->SetTextureSlot(3);
		shader->SetUniform1i("texture_opacity", 3);
		this->alphaMask->Bind();
	}

	skyBoxTexture->SetTextureSlot(0);
	shader->SetUniform1i("skybox", 0);
	skyBoxTexture->Bind();

}

void ReflectiveMaterial::ResetMaterial(Shader* shader)
{
}

BaseMaterial* ReflectiveMaterial::CloneMaterial()
{
	ReflectiveMaterial* material = new ReflectiveMaterial();

	material->SetBaseColor(this->GetBaseColor());
	material->SetAmbientColor(this->GetAmbientColor());
	material->diffuseTexture = this->diffuseTexture;
	material->specularTexture = this->specularTexture;
	material->alphaMask = this->alphaMask;
	material->ambientType = this->ambientType;
	material->ambientValue = this->ambientValue;
	material->specularValue = this->specularValue;
	material->shininess = this->shininess;
	material->useMaskTexture = this->useMaskTexture;
	material->alphaCutoffThreshold = this->alphaCutoffThreshold;

	return material;
}
