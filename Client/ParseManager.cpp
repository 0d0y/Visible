#include "pch.h"
#include "ParseManager.h"
#include "PathManager.h"
#include "resource.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>

using namespace std;


vector<vector<wstring>> ParseCSV(const wstring& filePath)
{
    vector<vector<wstring>> csvData;


	wstring strFilePath = PathManager::GetInst()->GetContentPath();
	strFilePath += filePath;
    // 파일 열기
    ifstream file(strFilePath, ios::binary);
    if (!file) {
        // 파일 열기 실패
        return csvData;
    }

    // 파일 크기 계산
    file.seekg(0, ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, ios::beg);

    // 파일 내용을 버퍼에 읽기
    vector<char> buffer(fileSize);
    file.read(buffer.data(), fileSize);

    // 버퍼 내용을 UTF-8로 변환하여 wstring으로 저장
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    wstring fileContent = converter.from_bytes(buffer.data(), buffer.data() + fileSize);

    // 파일 닫기
    file.close();

    // wstring으로 읽은 내용 파싱
    wstringstream ss(fileContent);
    wstring line;
    while (getline(ss, line)) {
        vector<wstring> row;
        wstringstream lineStream(line);
        wstring cell;

        while (getline(lineStream, cell, L',')) {
            row.push_back(cell);
        }

        csvData.push_back(row);
    }

    return csvData;
}

COLOR_TYPE StringToColorType(wstring& colorString)
{
	if (colorString == L"RED")
		return COLOR_TYPE::RED;
	else if (colorString == L"GREEN")
		return COLOR_TYPE::GREEN;
	else if (colorString == L"BLUE")
		return COLOR_TYPE::BLUE;
	else if (colorString == L"BLACK")
		return COLOR_TYPE::BLACK;
	else if (colorString == L"WHITE")
		return COLOR_TYPE::WHITE;
	else if (colorString == L"NONE")
		return COLOR_TYPE::NONE;
	else
		return COLOR_TYPE::BLOCK;
}
