#include "pch.h"
#include "Arrow.h"
#include "Scene.h"


void Arrow::Update()
{

}

Arrow::Arrow(Scene* _ownerScene)
	: GameObject(_ownerScene)
	, m_ownerObject(nullptr)
{

}

Arrow::~Arrow()
{

}
