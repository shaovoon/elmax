#include <string>

FILE* FileOpen(const std::wstring& file, const wchar_t* options);

FILE* FileOpen(const std::string& file, const char* options);

wchar_t* Wcscpy(wchar_t* dest, const wchar_t* src, size_t len);

char* Strcpy(char* dest, const char* src, size_t len);
