#include "pch.h"
#include "SceneTool.h"
#include "KeyManager.h"


SceneTool::SceneTool(HWND _hWnd)
	: Scene(_hWnd)
{

}

SceneTool::~SceneTool()
{
}


void SceneTool::Update()
{
	Scene::Update();

	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::START);
	}
}

void SceneTool::Enter()
{
}

void SceneTool::Exit()
{
}