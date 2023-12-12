#include "LoaderBase.h"

void LoaderBase::AssignRenderer(Renderer* renderer, Shader* shader)
{
	this->renderer = renderer;
	this->shader = shader;
}

void LoaderBase::AddToRenderers()
{
	for (int i = 0; i < modelPos.size(); i++)
	{
		Model* newWall = new Model();
		newWall->CopyFromModel(*modelPos[i].model);

		newWall->transform.SetPosition(glm::vec3(modelPos[i].modelPos.x, modelPos[i].modelPos.y, modelPos[i].modelPos.z));

		renderer->AddModel(newWall, shader);
	}
}

void LoaderBase::AddModelPos(ModelPos modelPos)
{
	this->modelPos.push_back({ currentModel, modelPos });
}

void LoaderBase::SetCurrentModel(const std::string& path, glm::vec3 rotation, glm::vec3 scale)
{
	Model* obj;
	obj = new Model(path, true);
	obj->transform.SetRotation(rotation);
	obj->transform.SetScale(scale);
	currentModel = obj;
}

void LoaderBase::SetCurrentModel(Model* model)
{
	currentModel = model;
}
