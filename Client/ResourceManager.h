#pragma once

class Res;
class Texture;

#include "windows.h"

class ResourceManager
{
	SINGLE(ResourceManager);

private:
	map<wstring, Res*> m_mapTex;
	HDC m_mainDC;


public:
	void Initialize(HDC _mainDC);
	void ClearResource();

public:
	Texture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	Texture* CreateTexture(const wstring& _strKey, UINT _width, UINT _height);
	Texture* FindTexture(const wstring& _strKey);

};

