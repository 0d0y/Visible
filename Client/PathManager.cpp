#include "pch.h"
#include "PathManager.h"
#include "GameProcess.h"


PathManager::PathManager()
	: m_szContentPath{}
{
}

PathManager::~PathManager()
{
}

void PathManager::Initialize()
{

	GetCurrentDirectory(255, m_szContentPath);
	
	int iLen = (int)wcslen(m_szContentPath);

	// 상위 폴더로 
	for (int i = iLen -1; 0 <= i ; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}
	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");
	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath); //타이틀 바에 작업 경로 표시
}
 