#pragma once

#include "resource.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <locale>
#include <codecvt>

 vector<vector<wstring>> ParseCSV(const wstring& filePath);

 COLOR_TYPE StringToColorType(wstring& colorString);