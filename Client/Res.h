#pragma once

class Res
{
private:
	wstring m_strKey; // 리소스 키
	wstring m_strRelativePath; // 리소스 상대경로 

public: 
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	void SetRelativePath(const wstring& _strPath) { m_strRelativePath = _strPath;  }

	const wstring& GetKey() { return m_strKey; }
	const wstring& GetRealtivePath() { return m_strRelativePath;  }

public:
	Res();
	virtual ~Res();
};

