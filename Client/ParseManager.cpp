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
    // ���� ����
    ifstream file(strFilePath, ios::binary);
    if (!file) {
        // ���� ���� ����
        return csvData;
    }

    // ���� ũ�� ���
    file.seekg(0, ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, ios::beg);

    // ���� ������ ���ۿ� �б�
    vector<char> buffer(fileSize);
    file.read(buffer.data(), fileSize);

    // ���� ������ UTF-8�� ��ȯ�Ͽ� wstring���� ����
    wstring_convert<codecvt_utf8<wchar_t>> converter;
    wstring fileContent = converter.from_bytes(buffer.data(), buffer.data() + fileSize);

    // ���� �ݱ�
    file.close();

    // wstring���� ���� ���� �Ľ�
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
