#pragma once

#include <Graphics/Model.h>

struct ModelPos
{
	float x;
	float y;
	float z;
};

struct ModelWithPos
{
	Model* model;
	ModelPos modelPos;
};