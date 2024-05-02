#include "pch.h"
#include "ColorObject.h"
#include "Camera.h"
#include "SelectGDI.h"
#include "Texture.h"


ColorObject::ColorObject(Scene* _ownerScene)
	: m_eColorState(COLOR_TYPE::NONE)
	, GameObject(_ownerScene)
{

}

ColorObject::~ColorObject()
{

}

