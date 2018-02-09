#pragma once
#include <fstream>
#include <codecvt>
#include <vector>
#include <string>
#include <iostream>

namespace Library {
	using namespace std;

	inline wstring GetSourceCode(const wchar_t* filePath) {
		wifstream sourceFile(filePath);
		if (sourceFile.fail()) {
			wstring empty = L"";
			return empty;
		}
		sourceFile.imbue(locale(locale(""), new codecvt_utf8_utf16<wchar_t, 0x10ffff, consume_header>()));
		istreambuf_iterator<wchar_t> iterator(sourceFile);
		istreambuf_iterator<wchar_t> last;
		wstring sourceCode(iterator, last);
		sourceFile.close();
		return sourceCode;
	}

	inline void MargeSourceCode(const wchar_t* fileName, wstring& sourceCode) {
		wstring from = L"#include \"" + wstring(fileName) + L"\"";
		wstring filePath = L"sources/" + wstring(fileName);

		wstring::size_type pos = sourceCode.find(from);
		sourceCode.replace(pos, from.size(), GetSourceCode(filePath.c_str()));
	}

	inline vector<wstring> GetSourceFileNameList(wstring& sourceCode) {
		vector<wstring> list;
		for (int i = 0; i < sourceCode.length(); i++) {
			if (sourceCode[i] != '#') continue;
			if (sourceCode.substr(i, 10) != L"#include \"") continue;
			i += 10;
			int end = i;
			while (sourceCode[end] != '"') end++;
			list.push_back(sourceCode.substr(i, end - i));
		}
		return list;
	}

	inline void Generate(const wchar_t* fileName) {
		wstring library = GetSourceCode(L"sources/App.hpp");

		vector<wstring> sourceFileNameList = GetSourceFileNameList(library);
		for (wstring fileName : sourceFileNameList) {
			MargeSourceCode(fileName.c_str(), library);
		}

		wofstream libraryFile(fileName);
		libraryFile.imbue(locale(locale(""), new codecvt_utf8_utf16<wchar_t, 0x10ffff, generate_header>()));
		libraryFile << L"namespace GameLibrary {\n" << library << L"\n}\n";
		libraryFile.close();
	}
}
