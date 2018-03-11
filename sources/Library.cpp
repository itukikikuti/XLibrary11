#pragma once
#include <fstream>
#include <codecvt>
#include <vector>
#include <string>
#include <iostream>
#include <regex>

namespace Library
{
    using namespace std;

    inline wstring GetSourceCode(const wchar_t* filePath)
    {
        wifstream sourceFile(filePath);
        if (sourceFile.fail())
        {
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

    inline void MargeSourceCode(const wchar_t* fileName, wstring& sourceCode)
    {
        wstring from = L"#include \"" + wstring(fileName) + L"\"";
        wstring filePath = L"sources/" + wstring(fileName);

        wstring::size_type pos = sourceCode.find(from);
        sourceCode.replace(pos, from.size(), GetSourceCode(filePath.c_str()));
    }

    inline vector<wstring> GetSourceFileNameList(wstring& sourceCode)
    {
        vector<wstring> list;
        for (size_t i = 0; i < sourceCode.length(); i++)
        {
            if (sourceCode[i] != '#') continue;
            if (sourceCode.substr(i, 10) != L"#include \"") continue;
            i += 10;
            int end = i;
            while (sourceCode[end] != '"') end++;
            list.push_back(sourceCode.substr(i, end - i));
        }
        return list;
    }

    inline void Generate(const wchar_t* inputFilePath, const wchar_t* outputFilePath)
    {
#if !defined(_DEBUG)
        return;
#endif

        wstring library = GetSourceCode(inputFilePath);

        vector<wstring> sourceFileNameList = GetSourceFileNameList(library);
        for (wstring fileName : sourceFileNameList)
        {
            MargeSourceCode(fileName.c_str(), library);
        }

        library = regex_replace(library, wregex(L"XLIBRARY_NAMESPACE_BEGIN"), L"namespace XLibrary11\n{");
        library = regex_replace(library, wregex(L"XLIBRARY_NAMESPACE_END"), L"}");

        wofstream libraryFile(outputFilePath);
        libraryFile.imbue(locale(locale(""), new codecvt_utf8_utf16<wchar_t, 0x10ffff, generate_header>()));
        libraryFile << library;
        libraryFile.close();
    }
}
