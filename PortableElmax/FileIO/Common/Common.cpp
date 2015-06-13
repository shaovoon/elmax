#include "Common.h"

std::map<int, std::wstring> errDict;
bool init = false;

std::map<int, std::string> errDictA;
bool initA = false;

void InitErrMap()
{
	errDict[ELMAX_UNKNOWN_ERROR] = L"Unknown Error!";
	errDict[ELMAX_NULL_POINTER] = L"Null Pointer!";
	errDict[ELMAX_FILE_NOT_OPENED] = L"File Not Opened!";
	errDict[ELMAX_WRITE_ERROR] = L"Write Failure!";
	errDict[ELMAX_READ_ERROR] = L"Read Failure!";
}

std::wstring GetErrorMsg(int errNum)
{
	if(init==false)
	{
		InitErrMap();
		init = true;
	}
	return errDict[errNum];
}

void InitErrMapA()
{
	errDictA[ELMAX_UNKNOWN_ERROR] = "Unknown Error!";
	errDictA[ELMAX_NULL_POINTER] = "Null Pointer!";
	errDictA[ELMAX_FILE_NOT_OPENED] = "File Not Opened!";
	errDictA[ELMAX_WRITE_ERROR] = "Write Failure!";
	errDictA[ELMAX_READ_ERROR] = "Read Failure!";
}

std::string GetErrorMsgA(int errNum)
{
	if(initA==false)
	{
		InitErrMapA();
		initA = true;
	}
	return errDictA[errNum];
}