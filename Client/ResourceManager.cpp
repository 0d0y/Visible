#include "pch.h"
#include "ResourceManager.h"

#include "PathManager.h"
#include "Texture.h"

ResourceManager::ResourceManager()
    : m_mainDC(0)
{

}

ResourceManager::~ResourceManager()
{
    SafeDeleteMap(m_mapTex);
}

void ResourceManager::Initialize(HDC _mainDC)
{
    m_mainDC = _mainDC;
}

void ResourceManager::ClearResource()
{
    SafeDeleteMap(m_mapTex);
}

Texture* ResourceManager::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
    Texture* pTex = FindTexture(_strKey);
    if (nullptr != pTex)
    {
        return pTex;
    }

    wstring strFilePath = PathManager::GetInst()->GetContentPath();
    strFilePath += _strRelativePath;

    pTex = new Texture;
    pTex->Load(strFilePath, m_mainDC);
    pTex->SetKey(_strKey);
    pTex->SetRelativePath(_strRelativePath);

    m_mapTex.insert(make_pair(_strKey, pTex));

    return pTex;
}

Texture* ResourceManager::CreateTexture(const wstring& _strKey, UINT _width, UINT _height)
{
    Texture* pTex = FindTexture(_strKey);
    if (nullptr != pTex)
    {
        return pTex;
    }

    pTex = new Texture;
    pTex->Create(_width, _height, m_mainDC);
    pTex->SetKey(_strKey);

    m_mapTex.insert(make_pair(_strKey, pTex));
    return pTex;
}

Texture* ResourceManager::FindTexture(const wstring& _strKey)
{
    map<wstring, Res*>::iterator iter = m_mapTex.find(_strKey);

    if(iter == m_mapTex.end())
    {
        return nullptr;
    }

    return (Texture*)iter->second;
}
