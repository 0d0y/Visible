#include "pch.h"
#include "SignPost.h"
#include "SelectGDI.h"
#include "Camera.h"

SignPost::SignPost(Scene* _ownerScene)
	: GameObject(_ownerScene)
{
	CreateCollider();
}

SignPost::~SignPost()
{
}

void SignPost::Update()
{
}

