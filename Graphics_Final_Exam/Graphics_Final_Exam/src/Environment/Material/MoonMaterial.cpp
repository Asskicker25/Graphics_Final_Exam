#include "MoonMaterial.h"

MoonMaterial::MoonMaterial()
{
    diffuseTexture = new Texture("res/Textures/DefaultTextures/Diffuse_Default.png");
    baseColor = glm::vec4(1.0f);
}

glm::vec4 MoonMaterial::GetBaseColor()
{
    return baseColor;

}

void MoonMaterial::SetBaseColor(glm::vec4 color)
{
    this->baseColor = color;
}

void MoonMaterial::UpdateMaterial(Shader* shader)
{
    shader->Bind();

    shader->SetUniform4f("solidColor", baseColor.x, baseColor.y, baseColor.z, baseColor.z);
    shader->SetUniform1f("emissionStrength", emissionValue);

    if (this->diffuseTexture != nullptr)
    {
        this->diffuseTexture->SetTextureSlot(0);
        shader->SetUniform1i("texture_diffuse", 0);
        this->diffuseTexture->Bind();
    }
}

void MoonMaterial::ResetMaterial(Shader* shader)
{
}

BaseMaterial* MoonMaterial::CloneMaterial()
{
    return nullptr;
}
