#include "encoding.h"

string string_To_UTF8(const string & str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP,0,str.c_str(),-1,NULL,0);

	wchar_t * pwBuf = new wchar_t[nwLen+1];//一定要加1，不然会出现尾巴  
	ZeroMemory(pwBuf,nwLen*2+2);

	::MultiByteToWideChar(CP_ACP,0,str.c_str(),str.length(),pwBuf,nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8,0,pwBuf,-1,NULL,NULL,NULL,NULL);

	char * pBuf = new char[nLen+1];
	ZeroMemory(pBuf,nLen+1);

	::WideCharToMultiByte(CP_UTF8,0,pwBuf,nwLen,pBuf,nLen,NULL,NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}

string UtfToGbk(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8,0,utf8,-1,NULL,0);
	wchar_t* wstr = new wchar_t[len+1];
	memset(wstr,0,len+1);
	MultiByteToWideChar(CP_UTF8,0,utf8,-1,wstr,len);
	len = WideCharToMultiByte(CP_ACP,0,wstr,-1,NULL,0,NULL,NULL);
	char* str = new char[len+1];
	memset(str,0,len+1);
	WideCharToMultiByte(CP_ACP,0,wstr,-1,str,len,NULL,NULL);
	if (wstr) delete[] wstr;
	return str;
}